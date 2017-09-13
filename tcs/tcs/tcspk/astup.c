#include <slalib.h>
#include "tcs.h"
#include "tcsmac.h"

int tcsAstup ( double tai, double ae2mt[3][3],
               FRAMETYPE m_cosys, double m_eqx, double m_wavel,
               FRAMETYPE r_cosys, double r_eqx, double r_wavel,
               double m_tar_p[2], double t0, double st0, double ttj,
               double temp, double press, double humid, double tlr,
               double wavelr, double refa, double refb,
               PRF refsub, double hm,
               double tlat, double diurab, double amprms[21],
               double m_spm1[3][3], double m_spm1_i[3][3],
               double m_spm2[3][3], double m_spm2_i[3][3],
               double r_spm1[3][3], double r_spm1_i[3][3],
               double r_spm2[3][3], double r_spm2_i[3][3] )

/*
**  - - - - - - - - -
**   t c s A s t u p
**  - - - - - - - - -
**
**  Update the local astrometry.
**
**  The sky-patch matrices are recalculated.  Together with an
**  intermediate rotation about the z-axis, they summarize the
**  transformation between target coordinates in the tracking frame
**  and mount [roll,pitch].
**
**  Given:
**     tai        double          time (TAI MJD = JD-2400000.5)
**     ae2mt      double[3][3]    rotation matrix, [Az,El] to mount
**     m_cosys    FRAMETYPE       mount frame type
**     m_eqx      double          mount frame equinox
**     m_wavel    double          mount wavelength
**     r_cosys    FRAMETYPE       rotator orientation frame type
**     r_eqx      double          rotator orientation frame equinox
**     r_wavel    double          rotator orientation wavelength
**     m_tar_p    double[2]       target coordinates
**     t0         double          raw clock time at reference time
**     st0        double          LAST at reference time (radians)
**     ttj        double          TT at reference time (Julian epoch)
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
**     m_spm1     double[3][3]    SPM #1, mount
**     m_spm1_i   double[3][3]    inverse SPM #1, mount
**     m_spm2     double[3][3]    SPM #2, mount
**     m_spm2_i   double[3][3]    inverse SPM #2, mount
**     r_spm1     double[3][3]    SPM #1, rotator
**     r_spm1_i   double[3][3]    inverse SPM #1, rotator
**     r_spm2     double[3][3]    SPM #2, rotator
**     r_spm2_i   double[3][3]    inverse SPM #2a, rotator
**
**  Returned (function value):
**                int             status:  0 = OK
**                                        -1 = internal error (fatal)
**
**  Defined in tcsmac.h:
**     STRPD      double          ST change (radians) per UT day
**     FRAMETYPE  enum            frame types
**     PRF        void(*)()       pointers to refraction functions
**
**  Called:  slaAtmdsp, tcsTartran, tcsSky2aim, tcsPtrani
**
**  Last revision:   4 May 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{
   double st, sst, cst, refac, refbc, xa, ya, za, r_tar_p[2];



/* LAST (radians) and functions. */
   st = st0 + ( tai - t0 ) * STRPD;
   sst = sin ( st );
   cst = cos ( st );

/*
** -----
** MOUNT
** -----
*/

/* Adjust refraction constants for color. */
   slaAtmdsp ( temp, press, humid, wavelr, refa, refb, m_wavel,
               &refac, &refbc );

/* Generate SPMs. */
   if ( tcsTartran ( ttj, amprms, ae2mt, hm, tlat, diurab,
                     refac, refbc, temp, press, humid, tlr, m_wavel, refsub,
                     sst, cst, m_cosys, m_eqx, m_tar_p,
                     m_spm1, m_spm1_i, m_spm2, m_spm2_i ) ) return -1;

/*
** -------
** ROTATOR
** -------
*/

/* Adjust refraction constants for color. */
   slaAtmdsp ( temp, press, humid, wavelr, refa, refb, r_wavel,
               &refac, &refbc );

/* Transform target coordinates from tracking frame to mount frame. */
   tcsSky2aim ( m_tar_p[0], m_tar_p[1],
                m_spm1, m_cosys, sst, cst, m_spm2,
                &xa, &ya, &za );

/* Mount frame to sky, giving target coordinates in rotator frame. */
   tcsPtrani ( xa, ya, za, ttj, amprms, ae2mt, hm, tlat, diurab,
               r_cosys, r_eqx, refac, refbc,
               temp, press, humid, tlr, r_wavel, refsub, sst, cst,
               r_tar_p );

/* Generate SPMs for rotator. */
   if ( tcsTartran ( ttj, amprms, ae2mt, hm, tlat, diurab,
                     refac, refbc, temp, press, humid, tlr, r_wavel, refsub,
                     sst, cst, r_cosys, r_eqx, r_tar_p,
                     r_spm1, r_spm1_i, r_spm2, r_spm2_i ) ) return -1;

/* Success. */
   return 0;

}
