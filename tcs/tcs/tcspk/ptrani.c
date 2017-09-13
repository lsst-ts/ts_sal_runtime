#include <slalib.h>
#include "tcs.h"

void tcsPtrani ( double xa, double ya, double za,
                 double tdbj, double amprms[21],
                 double ae2mt[3][3],
                 double hm, double tlat, double diurab,
                 FRAMETYPE cosys, double usreqx,
                 double refa, double refb, double temp, double press,
                 double humid, double tlr, double wavel, PRF refsub,
                 double sst, double cst,
                 double target[2] )

/*
**  - - - - - - - - - -
**   t c s P t r a n i
**  - - - - - - - - - -
**
**  Inverse pointing transformation:  AIM to sky.
**
**  Given:
**     xa      double        AIM vector (mount frame) x
**     ya      double        AIM vector (mount frame) y
**     za      double        AIM vector (mount frame) z
**     tdbj    double        TDB Julian Epoch (TT will do)
**     amprms  double[21]    mean to apparent parameters
**     ae2mt   double[3][3]  Az/El to mount roll/pitch matrix
**     hm      double        height above sea level (metres)
**     tlat    double        true geodetic latitude
**     diurab  double        diurnal aberration (radians)
**     cosys   FRAMETYPE     reference frame ID (see below)
**     usreqx  double        reference frame equinox (if a mean RA/Dec)
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
**
**  Returned:
**     target  double[2]     sky spherical coordinates, tracking frame
**
**  Defined in tcs.h:
**     FRAMETYPE   enum         frame types
**     AZEL_TOPO   FRAMETYPE    topocentric Az/El
**     APPT_TOPO   FRAMETYPE    topocentric apparent RA/Dec
**     APPT        FRAMETYPE    geocentric apparent RA/Dec
**     FK5         FRAMETYPE    IAU 1976 RA/Dec, any equinox (Note 3)
**     FK4         FRAMETYPE    pre IAU 1976 RA/Dec, any equinox
**     PRF         void(*)()    pointers to refraction functions
**
**  Called:  slaDimxv, slaDcc2s, slaDcs2c, slaAmpqk, slaPrec,
**           slaDmxv, slaFk54z, slaSubet, slaPrebn, slaAddet, refsub
**
**  Notes:
**
**  1  In the typical case, cosys and usreqx are FK5 and J2000
**     respectively, the coordinates are RA and Dec and the rotation is
**     sidereal time.
**
**  2  No check on cosys validity is made.  The serendipitous default
**     is FK4.
**
**  3  For ICRS coordinates use FK5 J2000, which is a good enough
**     approximation (better than 0.1 arcsec).
**
**  4  Topocentric and geocentric apparent RA,Dec differ in that the
**     former already contains diurnal aberration (and parallax) terms,
**     making it especially suitable for solar-system targets.
**
**  Last revision:   19 July 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

#define SELMIN 0.01    /* Minimum sin(el) for refraction purposes. */

{
   double v[3], x, y, z, a, b, t, s, c, xhdt, yhdt, zhdt,
          f, prepre[3][3], fpr, fpd;



/* AIM mount roll/pitch to observed Az/El. */
   v[0] = xa;
   v[1] = ya;
   v[2] = za;
   slaDimxv ( ae2mt, v, v );

/* Refraction, giving topocentric Az/El. */
   slaDcc2s ( v, &a, &b );
   x = v[0];
   y = v[1];
   z = v[2];
   t = sqrt ( x * x + y * y ) / ( z > SELMIN ? z : SELMIN );
   b -= ( refa + refb * t * t ) * t;

/* Call any optional refraction function. */
   if ( refsub ) {
      refsub ( 1, refa, refb, hm, tlat, temp, press, humid, tlr, wavel,
               x, y, z, &x, &y, &z );
      b = atan2 ( z, sqrt ( x * x + y * y ) );
   }

/* Is the target frame topocentric Az/El, as opposed to an RA/Dec? */
   if ( cosys == AZEL_TOPO ) {

   /* Az/El.  Return the results. */
      target[0] = a;
      target[1] = b;

   } else {

   /* Some sort of RA/Dec.  Transform the Az/El to -HA/Dec. */
      slaDcs2c ( a, b, v );
      x = v[0];
      z = v[2];
      s = sin ( tlat );
      c = cos ( tlat );
      xhdt = s * x + c * z;
      yhdt = v[1];
      zhdt = - c * x + s * z;

   /* Is the target frame topocentric apparent RA/Dec? */
      if ( cosys == APPT_TOPO ) {

      /* Yes.  The -HA/Dec is already in the correct form. */
         x = xhdt;
         y = yhdt;
         z = zhdt;

      } else {

      /* No.  Remove diurnal aberration, giving geocentric -HA/Dec. */
         f = ( 1.0 + diurab * yhdt );
         x = f * xhdt;
         y = f * ( yhdt - diurab );
         z = f * zhdt;
      }

   /* Apparent -HA,Dec to apparent RA,Dec. */
      v[0] = cst * x - sst * y;
      v[1] = sst * x + cst * y;
      v[2] = z;

   /* Is the target frame an apparent RA/Dec or a mean RA/Dec? */
      if ( cosys == APPT || cosys == APPT_TOPO ) {

      /* Apparent RA/Dec.  Return the current position. */
         slaDcc2s ( v, &target[0], &target[1] );

      } else {

      /* Mean RA,Dec.  Transform the apparent RA/Dec to J2000. */
         slaDcc2s ( v, &a, &b );
         slaAmpqk ( a, b, amprms, &a, &b );

      /* FK5? */
         if ( cosys == FK5 ) {

         /* Yes.  Precess to specified equinox, giving the final result. */
            slaDcs2c ( a, b, v );
            slaPrec ( 2000.0, usreqx, prepre );
            slaDmxv ( prepre, v, v );
            slaDcc2s ( v, &target[0], &target[1] );

         } else {

         /* No.  FK5 to FK4. */
            slaFk54z ( a, b, tdbj, &a, &b, &fpr, &fpd );

         /* Subtract the e-terms. */
            slaSubet ( a, b, usreqx, &a, &b );

         /* Precess to specified equinox. */
            slaDcs2c ( a, b, v );
            slaPrebn ( 1950.0, usreqx, prepre );
            slaDmxv ( prepre, v, v );
            slaDcc2s ( v, &a, &b );

         /* Add the e-terms, giving the final result. */
            slaAddet ( a, b, usreqx, &target[0], &target[1] );
         }
      }
   }
}
