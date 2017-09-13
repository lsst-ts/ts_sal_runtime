#include <slalib.h>
#include "tcs.h"

void tcsPtran ( double tdbj, double amprms[21],
                double ae2mt[3][3], double hm, double tlat, double diurab,
                FRAMETYPE cosys, double usreqx, double prepre[3][3],
                double refa, double refb, double temp, double press,
                double humid, double tlr, double wavel, PRF refsub,
                double sst, double cst,
                double u[3], double a[3], double h[3], double e[3] )

/*
**  - - - - - - - - -
**   t c s P t r a n
**  - - - - - - - - -
**
**  Pointing transformation:  sky to AIM.
**
**  Given:
**     tdbj    double        TDB Julian Epoch (TT will do)
**     amprms  double[21]    mean to apparent parameters
**     ae2mt   double[3][3]  Az/El to mount roll/pitch matrix
**     hm      double        height above sea level (metres)
**     tlat    double        true geodetic latitude
**     diurab  double        diurnal aberration (radians)
**     cosys   FRAMETYPE     reference frame ID (see below)
**     usreqx  double        reference frame equinox (if a mean RA/Dec)
**     prepre  double[3][3]  user frame to B1950 or J2000 (if required)
**     refa    double        refraction constant A
**     refb    double        refraction constant B
**     temp    double        ambient temperature (K)
**     press   double        pressure (mB)
**     humid   double        relative humidity (0-1)
**     tlr     double        tropospheric lapse rate (K per metre)
**     wavel   double        wavelength (micrometres)
**     refsub  PRF           optional refraction function
**     sst     double        sine of LAST
**     cst     double        cosine of LAST
**     u       double[3]     target x,y,z in tracking reference frame
**
**  Returned:
**     a       double[3]     target x,y,z in pre-rotation frame
**     h       double[3]     target x,y,z in post-rotation frame
**     e       double[3]     target x,y,z in mount roll/pitch frame
**
**  Defined in tcs.h:
**     FRAMETYPE   enum         frame types
**     AZEL_TOPO   FRAMETYPE    topocentric Az/El
**     APPT_TOPO   FRAMETYPE    topocentric apparent RA/Dec
**     APPT        FRAMETYPE    geocentric apparent RA/Dec
**     FK5         FRAMETYPE    IAU 1976 RA/Dec, any equinox (Note 4)
**     FK4         FRAMETYPE    pre IAU 1976 RA/Dec, any equinox
**     PRF         void(*)()    pointers to refraction functions
**
**  Called:  slaDmxv, slaDcc2s, slaSubet, slaDcs2c, slaAddet,
**           slaFk45z, slaMapqkz, refsub
**
**  Notes:
**
**  1  The u vector is the "SKY" target;  the e vector is the "AIM".
**
**  2  In the typical case, cosys and usreqx are FK5 and J2000
**     respectively, the vector u is the nominated type of mean RA/Dec,
**     a is geocentric apparent RA/Dec, the rotation is sidereal time
**     and h is apparent -HA/Dec.
**
**  3  No check on cosys validity is made.  The serendipitous default
**     is FK4.
**
**  4  For ICRS coordinates use FK5 J2000, which is a good enough
**     approximation (better than 0.1 arcsec).
**
**  5  Topocentric and geocentric apparent RA,Dec differ in that the
**     former already contains diurnal aberration (and parallax) terms,
**     making it especially suitable for solar-system targets.
**
**  Last revision:   19 July 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

#define CELMIN 1e-6    /* Minimum cos(el) for refraction purposes. */
#define SELMIN 0.01    /* Minimum sin(el) for refraction purposes. */

{
   int i;
   double xaet, yaet, zaet, rd[3], v3[3], rm5, dm5, rm1, dm1,
          rm2, dm2, v2[3], rm3, dm3, rm4, dm4, ra, da,
          xrd, yrd, zrd, xhd, yhd, zhd, f, xhdt, yhdt, zhdt,
          slat, clat, r, z, tz, w, del, cosdel, x, y, aeo[3];
 


/* Examine tracking frame ID. */
   if ( cosys == AZEL_TOPO ) {

   /* Tracking frame is topocentric Az/El. */

   /* Copy the input vector to all but the final result. */
      xaet = h[0] = a[0] = u[0];
      yaet = h[1] = a[1] = u[1];
      zaet = h[2] = a[2] = u[2];

   } else {

      if ( cosys == APPT || cosys == APPT_TOPO ) {

      /* Tracking frame is an apparent RA/Dec. */

      /* Copy the input vector to the apparent RA/Dec. */
         for ( i = 0; i < 3; i++ ) {
            rd[i] = u[i];
         }

      } else {

         if ( cosys == FK5 ) {

         /* Tracking frame is mean RA/Dec, FK5. */

         /* Precess to J2000. */
            slaDmxv ( prepre, u, v3 );

         /* Cartesian to spherical. */
            slaDcc2s ( v3, &rm5, &dm5 );

         } else {

         /* Tracking frame is mean RA/Dec, FK4. */

         /* Cartesian to spherical. */
            slaDcc2s ( u, &rm1, &dm1 );

         /* Remove E-terms. */
            slaSubet ( rm1, dm1, usreqx, &rm2, &dm2 );

         /* To Cartesian. */
            slaDcs2c ( rm2, dm2, v2 );

         /* Precess to B1950. */
            slaDmxv ( prepre, v2, v3 );

         /* To spherical. */
            slaDcc2s ( v3, &rm3, &dm3 );

         /* Add E-terms. */
            slaAddet ( rm3, dm3, 1950.0, &rm4, &dm4 );

         /* Transform to J2000 FK5. */
            slaFk45z ( rm4, dm4, tdbj, &rm5, &dm5 );
         }

      /* Tracking frame is some kind of mean RA/Dec. */

      /* Mean to apparent. */
         slaMapqkz ( rm5, dm5, amprms, &ra, &da );

      /* Apparent RA/Dec to Cartesian. */
         slaDcs2c ( ra, da, rd );
      }

   /* Tracking frame is some kind of RA/Dec. */

   /* First result. */
      for ( i = 0; i < 3; i++ ) {
         a[i] = rd[i];
      }

   /* Earth rotation. */
      xrd = rd[0];
      yrd = rd[1];
      zrd = rd[2];
      xhd =  cst * xrd + sst * yrd;
      yhd = -sst * xrd + cst * yrd;
      zhd = zrd;

   /* Second result. */
      h[0] = xhd;
      h[1] = yhd;
      h[2] = zhd;

   /* Diurnal aberration, unless already accounted for. */
      if ( cosys == APPT_TOPO ) {
         xhdt = xhd;
         yhdt = yhd;
         zhdt = zhd;
      } else {
         f = ( 1.0 - diurab * yhd );
         xhdt = f * xhd;
         yhdt = f * ( yhd + diurab );
         zhdt = f * zhd;
      }

   /* -HA/Dec to Az/El (celestial rather than terrestrial north). */
      slat = sin ( tlat );
      clat = cos ( tlat );
      xaet = slat * xhdt - clat * zhdt;
      yaet = yhdt;
      zaet = clat * xhdt + slat * zhdt;
   }

/* Refraction (giving third result). */
   r = sqrt ( xaet * xaet + yaet * yaet );
   r = r > CELMIN ? r : CELMIN;
   z = zaet > SELMIN ? zaet : SELMIN;
   tz = r / z;
   w = refb * tz * tz;
   del = ( refa + w ) * tz / ( 1.0 + ( refa + 3.0 * w ) / ( z * z ) );
   cosdel = 1.0 - del * del / 2.0;
   f = cosdel - del * z / r;
   x = xaet * f;
   y = yaet * f;
   z = cosdel * zaet + del * r;

/* Call any optional refraction function. */
   if ( refsub ) refsub ( 0, refa, refb,
                          hm, tlat, temp, press, humid, tlr, wavel,
                          xaet, yaet, zaet, &x, &y, &z );

/* Precise normalization to finish up. */
   f = sqrt ( x * x + y * y + z * z );
   aeo[0] = x / f;
   aeo[1] = y / f;
   aeo[2] = z / f;

/* Observed Az/El to mount Roll/Pitch. */
   slaDmxv ( ae2mt, aeo, e );

}
