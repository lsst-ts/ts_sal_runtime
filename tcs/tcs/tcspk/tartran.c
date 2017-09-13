#include <slalib.h>
#include "tcs.h"

int tcsTartran ( double tdbj, double amprms[21],
                 double ae2mt[3][3],
                 double hm, double tlat, double diurab,
                 double refa, double refb, double temp, double press,
                 double humid, double tlr, double wavel, PRF refsub,
                 double sst, double cst,
                 FRAMETYPE cosys, double usreqx, double target[2],
                 double spm1[3][3], double spm1_i[3][3],
                 double spm2[3][3], double spm2_i[3][3] )

/*
**  - - - - - - - - - - -
**   t c s T a r t r a n
**  - - - - - - - - - - -
**
**  Update target transformation.
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
**     target   double[2]     target spherical coordinates, tracking frame
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
**     AZEL_TOPO   FRAMETYPE  topocentric Az/El
**     PRF         void(*)()  pointers to refraction functions
**
**  Called:  slaDcs2c, tcsTartran
**
**  Last revision:   7 May 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{
   double u[3];                       /* current tracking coordinates */



/* Get current tracking x,y,z (righthanded). */
   slaDcs2c ( target[0], target[1], u );
   if ( cosys == AZEL_TOPO ) u[0] = -u[0];

/* Generate the SPMs. */
   return tcsTartr_c ( tdbj, amprms, ae2mt, hm, tlat, diurab,
                       refa, refb, temp, press, humid, tlr, wavel,
                       refsub, sst, cst,
                       cosys, usreqx, u[0], u[1], u[2],
                       spm1, spm1_i, spm2, spm2_i );
}
