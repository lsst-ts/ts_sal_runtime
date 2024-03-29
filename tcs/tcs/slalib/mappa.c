#include "slalib.h"
#include "slamac.h"
void slaMappa ( double eq, double date, double amprms[21] )
/*
**  - - - - - - - - -
**   s l a M a p p a
**  - - - - - - - - -
**
**  Compute star-independent parameters in preparation for
**  conversions between mean place and geocentric apparent place.
**
**  The parameters produced by this function are required in the
**  parallax, light deflection, aberration, and precession/nutation
**  parts of the mean/apparent transformations.
**
**  The reference frames and timescales used are post IAU 1976.
**
**  Given:
**     eq       double      epoch of mean equinox to be used (Julian)
**     date     double      TDB (JD-2400000.5)
**
**  Returned:
**     amprms   double[21]  star-independent mean-to-apparent parameters:
**
**       (0)      time interval for proper motion (Julian years)
**       (1-3)    barycentric position of the Earth (AU)
**       (4-6)    heliocentric direction of the Earth (unit vector)
**       (7)      (grav rad Sun)*2/(Sun-Earth distance)
**       (8-10)   abv: barycentric Earth velocity in units of c
**       (11)     sqrt(1-v**2) where v=modulus(abv)
**       (12-20)  precession/nutation (3,3) matrix
**
**  References:
**     1984 Astronomical Almanac, pp B39-B41.
**     (also Lederle & Schwan, Astron. Astrophys. 134, 1-6, 1984)
**
**  Notes:
**
**  1)  For date, the distinction between the required TDB and TT
**      is always negligible.  Moreover, for all but the most
**      critical applications UTC is adequate.
**
**  2)  The vectors amprms(1-3) and amprms(4-6) are referred to the
**      mean equinox and equator of epoch eq.
**
**  3)  The parameters AMPRMS produced by this function are used by
**      slaAmpqk, slaMapqk and slaMapqkz.
**
**  4)  The accuracy is sub-milliarcsecond, limited by the
**      precession-nutation model (IAU 1976 precession, Shirai &
**      Fukushima 2001 forced nutation and precession corrections).
**
**  5)  A further limit to the accuracy of functions using the parameter
**      array AMPRMS is imposed by the function slaEvp, used here to
**      compute the Earth position and velocity by the methods of
**      Stumpff.  The maximum error in the resulting aberration
**      corrections is about 0.3 milliarcsecond.
**
**  Called:
**     slaEpj, slaEvp, slaDvn, slaPrenut
**
**  Last revision:   22 October 2006
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

#define CR 499.004782     /* Light time for 1 AU (sec) */
#define GR2 1.974126e-8   /* Gravitational radius of the Sun x 2:
                                                  (2*mu/c**2, au) */
{
   int i;

   double ebd[3], ehd[3], eh[3], e, vn[3], vm;

/* Time interval for proper motion correction */
   amprms[0] = slaEpj ( date ) - eq;

/* Get Earth barycentric and heliocentric position and velocity */
   slaEvp ( date, eq, ebd, &amprms[1], ehd, eh );

/* Heliocentric direction of Earth (normalized) and modulus */
   slaDvn ( eh, &amprms[4], &e );

/* Light deflection parameter */
   amprms[7] = GR2 / e;

/* Aberration parameters */
   for ( i = 0; i < 3; i++ ) {
      amprms[i+8] = ebd[i] * CR;
   }
   slaDvn ( &amprms[8], vn, &vm );
   amprms[11] = sqrt ( 1.0 - vm * vm );

/* Precession/nutation matrix */
   slaPrenut ( eq, date, (double(*)[3]) &amprms[12] );
}
