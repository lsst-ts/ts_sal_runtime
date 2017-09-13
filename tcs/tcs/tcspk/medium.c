#include <slalib.h>
#include "tcs.h"

int tcsMedium ( double tai, int maxtrm, int model[], double coeffv[],
                int nterml, int ntermx, int nterms,
                char coeffn[][9], char coform[][9],
                MTYPE mount, double ae2nm[3][3],
                double roll, double pitch, int jbp, double aux[3],
                FRAMETYPE m_cosys, double m_eqx, double m_wavel,
                FRAMETYPE r_cosys, double r_eqx, double r_wavel,
                double m_tar_p[2],
                double t0, double st0, double ttj,
                double temp, double press, double humid, double tlr,
                double wavelr, double refa, double refb,
                PRF refsub, double hm,
                double tlat, double diurab, double amprms[21],
                double* ia, double* ib, double* np,
                double* xt, double* yt, double* zt,
                double ae2mt[3][3],
                double m_spm1[3][3], double m_spm1_i[3][3],
                double m_spm2[3][3], double m_spm2_i[3][3],
                double r_spm1[3][3], double r_spm1_i[3][3],
                double r_spm2[3][3], double r_spm2_i[3][3] )

/*
**  - - - - - - - - - -
**   t c s M e d i u m
**  - - - - - - - - - -
**
**  The MEDIUM process.
**
**  The pointing corrections are updated and the sky-patch matrices
**  recalculated.
**
**  Given:
**     tai        double          time (TAI MJD = JD-2400000.5)
**     maxtrm     int             maximum number of terms in model
**     model      int[maxtrm]     term numbers for current model (0 = end)
**     coeffv     double[maxtrm]  coefficient values
**     nterml     int             no. of local terms
**     ntermx     int             no. of terms implemented explicitly (loc+std)
**     nterms     int             no. of terms avail. currently (loc+std+gen)
**     coeffn     char[][9]       coefficient names (local, standard, generic)
**     coform     char[][9]       format of generic term
**     mount      MTYPE           mount type
**     ae2nm      double[3][3]    rotation matrix: [Az,El] to nominal mount
**     roll       double          demand mount roll (radians, righthanded)
**     pitch      double          demand mount pitch (radians)
**     jbp        int             TRUE = "below the pole"
**     aux        double[3]       auxiliary readings
**     m_cosys    FRAMETYPE       mount frame type
**     m_eqx      double          mount frame equinox
**     m_wavel    double          mount wavelength
**     r_cosys    FRAMETYPE       rotator orientation frame type
**     r_eqx      double          rotator orientation frame equinox
**     r_wavel    double          rotator orientation wavelength
**     m_tar_p[2] double          target coordinates
**     t0         double          raw clock time at reference time
**     st0        double          LAST at reference time (radians)
**     ttj        double          TT at reference time (Julian date)
**     temp       double          ambient temperature (K)
**     press      double          pressure (mB)
**     humid      double          relative humidity (0-1)
**     tlr        double          tropospheric lapse rate (K per metre)
**     wavelr     double          reference wavelength (micrometres)
**     refa       double          tan refraction constant
**     refb       double          tan^3 refraction constant
**     refsub     PRF             optional refraction function
**     hm         double          telescope height above sea level (metres)
**     tlat       double          telescope latitude (true)
**     diurab     double          diurnal aberration (radians)
**     amprms     double[21]      target-independent MAP parameters
**
**  Returned (arguments):
**     ia         double*         roll zero point
**     ib         double*         pitch zero point
**     np         double*         mount axes nonperpendicularity
**     xt         double*         telescope vector, x-component
**     yt         double*         telescope vector, y-component
**     zt         double*         telescope vector, z-component
**     ae2mt      double[3][3]    rotation matrix, [Az,El] to mount
**     m_spm1     double[3][3]    SPM #1, mount
**     m_spm1_i   double[3][3]    inverse SPM #1, mount
**     m_spm2     double[3][3]    SPM #2, mount
**     m_spm2_i   double[3][3]    inverse SPM #2, mount
**     r_spm1     double[3][3]    SPM #1, rotator
**     r_spm1_i   double[3][3]    inverse SPM #1, rotator
**     r_spm2     double[3][3]    SPM #2, rotator
**     r_spm2_i   double[3][3]    inverse SPM #2, rotator
**
**  Returned (function value):
**                int             status:  0 = OK
**                                        -1 = internal error (fatal)
**
**  Defined in tcs.h:
**     FRAMETYPE  enum            frame types
**     MTYPE      enum            mount type codes
**     PRF        void(*)()       pointers to refraction functions
**
**  Called:  tcsPup, tcsAstup
**
**  Note:
**
**     In the normal case, where there is no user-supplied refraction
**     function, the argument refsub should be set to zero (or NULL).
**     If this is achieved by referring to a function pointer variable,
**     it is vital that it be initialized to zero (or NULL).  This can
**     be achieved by an explicit declaration or by using static and
**     relying on default initialization.  Failure to do this will
**     result in undefined behaviour.
**
**  Last revision:   7 May 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{

/* Update the pointing model. */
   if ( tcsPup ( maxtrm, model, coeffv, nterml, ntermx, nterms,
                 coeffn, coform, mount, ae2nm,
                 roll, pitch, jbp, aux, tlat,
                 ia, ib, np, xt, yt, zt, ae2mt ) ) return -1;

/* Generate SPMs for mount and rotator. */
   if ( tcsAstup ( tai, ae2mt, m_cosys, m_eqx, m_wavel,
                   r_cosys, r_eqx, r_wavel, m_tar_p,
                   t0, st0, ttj, temp, press, humid,
                   tlr, wavelr, refa, refb,
                   refsub, hm, tlat, diurab, amprms,
                   m_spm1, m_spm1_i, m_spm2, m_spm2_i,
                   r_spm1, r_spm1_i, r_spm2, r_spm2_i ) ) return -1;

/* Success. */
   return 0;
}
