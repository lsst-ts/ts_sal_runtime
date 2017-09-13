#include <slalib.h>
#include "tcs.h"
#include "tcsmac.h"

int tcsTartr_c ( double tdbj, double amprms[21],
                 double ae2mt[3][3],
                 double hm, double tlat, double diurab,
                 double refa, double refb, double temp, double press,
                 double humid, double tlr, double wavel, PRF refsub,
                 double sst, double cst,
                 FRAMETYPE cosys, double usreqx,
                 double xtar, double ytar, double ztar,
                 double spm1[3][3], double spm1_i[3][3],
                 double spm2[3][3], double spm2_i[3][3] )

/*
**  - - - - - - - - - - -
**   t c s T a r t r _ c
**  - - - - - - - - - - -
**
**  Update target transformation.  The target is specified in Cartesian
**  form.
**
**  Given (arguments):
**     tdbj     double        TDB Julian Epoch (TT will do)
**     amprms   double[21]    mean to apparent parameters
**     ae2mt    double[3][3]  rotation matrix, [Az,El] to mount
**     hm       double        height above sea level (metres)
**     tlat     double        true geodetic latitude
**     diurab   double        diurnal aberration (radians)
**     refa     double        refraction constants A and...
**     refb     double        ...B for tracking wavelength (radians)
**     temp     double        ambient temperature (K)
**     press    double        pressure (mB)
**     humid    double        relative humidity (0-1)
**     tlr      double        tropospheric lapse rate (K per metre)
**     wavel    double        wavelength (micrometres)
**     refsub   PRF           optional refraction function
**     sst      double        sine of LAST
**     cst      double        cosine of LAST
**     cosys    FRAMETYPE     tracking frame ID
**     usreqx   double        tracking frame equinox (mean RA/Dec only)
**     xtar     double        target x-coordinate (see note)
**     ytar     double        target y-coordinate (see note)
**     ztar     double        target z-coordinate (see note)
**
**  Returned (arguments):
**     spm1     double[3][3]  SPM #1
**     spm1_i   double[3][3]  inverse of SPM #1
**     spm2     double[3][3]  SPM #2
**     spm2_i   double[3][3]  inverse of SPM #2
**
**  Returned (function value):
**              int           status:  0 = OK
**                                    -1 = internal error (fatal)
**
**  Defined in tcs.h:
**     FRAMETYPE   enum       frame types
**     FK4         FRAMETYPE  pre IAU 1976 RA/Dec, any equinox
**     FK5         FRAMETYPE  IAU 1976 RA/Dec, any equinox (also ICRS)
**     PRF         void(*)()  pointers to refraction functions
**
**  Defined in tcsmac.h:
**     DEL         double     probe-vector spacing (radians from centre)
**
**  Called:  slaPrebn, slaPrec, tcsProbev, tcsPtran, tcsSpm
**
**  Note:
**
**     The target vector is right-handed, so special care must be taken
**     if using Az/El, which is a left-handed system.  The procedure in
**     this case is to perform the standard spherical-to-Cartesian
**     transformation and then to reverse the sign of the x-coordinate.
**
**  Last revision:   7 May 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{
   double u[3];                        /* current tracking coordinates */
   double prepre[3][3];                /* preliminary precession matrix */
   double u1[3], a1[3], h1[3], e1[3];  /* probe vector #1 */
   double u2[3], a2[3], h2[3], e2[3];  /* probe vector #2 */
   double u3[3], a3[3], h3[3], e3[3];  /* probe vector #3 */



/* The tracking coordinates. */
   u[0] = xtar;
   u[1] = ytar;
   u[2] = ztar;

/* Generate preliminary precession matrix if required. */
   if ( cosys == FK4 ) {

   /* Nominated FK4 equinox to B1950. */
       slaPrebn ( usreqx, 1950.0, prepre );

   } else if ( cosys == FK5 ) {

   /* Nominated FK5 equinox to J2000. */
       slaPrec ( usreqx, 2000.0, prepre );
   }

/* Generate three probe vectors. */
   tcsProbev ( u, DEL, u1, u2, u3 );

/* Put the probe vectors through the pointing transformation */
   tcsPtran ( tdbj, amprms, ae2mt, hm, tlat, diurab,
              cosys, usreqx, prepre, refa, refb,
              temp, press, humid, tlr, wavel, refsub, sst, cst,
              u1, a1, h1, e1 );
   tcsPtran ( tdbj, amprms, ae2mt, hm, tlat, diurab,
              cosys, usreqx, prepre, refa, refb,
              temp, press, humid, tlr, wavel, refsub, sst, cst,
              u2, a2, h2, e2 );
   tcsPtran ( tdbj, amprms, ae2mt, hm, tlat, diurab,
              cosys, usreqx, prepre, refa, refb,
              temp, press, humid, tlr, wavel, refsub, sst, cst,
              u3, a3, h3, e3 );

/* Generate the sky-patch matrices. */
   if ( tcsSpm ( u1, u2, u3, a1, a2, a3, spm1 ) ) return -1;
   if ( tcsSpm ( a1, a2, a3, u1, u2, u3, spm1_i ) ) return -1;
   if ( tcsSpm ( h1, h2, h3, e1, e2, e3, spm2 ) ) return -1;
   if ( tcsSpm ( e1, e2, e3, h1, h2, h3, spm2_i ) ) return -1;

/* Success. */
   return 0;
}
