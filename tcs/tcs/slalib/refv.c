#include "slalib.h"
#include "slamac.h"
void slaRefv ( double vu[3], double refa, double refb, double vr[3] )
/*
**  - - - - - - - -
**   s l a R e f v
**  - - - - - - - -
**
**  Adjust an unrefracted Cartesian vector to include the effect of
**  atmospheric refraction, using the simple A tan z + B tan^3 z
**  model.
**
**  Given:
**    vu    double    unrefracted position of the source (az/el 3-vector)
**    refa  double    A: tan z coefficient (radian)
**    refb  double    B: tan^3 z coefficient (radian)
**
**  Returned:
**    *vr   double    refracted position of the source (az/el 3-vector)
**
**  Notes:
**
**  1  This function applies the adjustment for refraction in the
**     opposite sense to the usual one - it takes an unrefracted
**     (in vacuo) position and produces an observed (refracted)
**     position, whereas the A tan Z + B tan^3 Z model strictly
**     applies to the case where an observed position is to have the
**     refraction removed.  The unrefracted to refracted case is
**     harder, and requires an inverted form of the text-book
**     refraction models;  the algorithm used here is equivalent to
**     one iteration of the Newton-Raphson method applied to the above
**     formula.
**
**  2  Though optimized for speed rather than precision, the present
**     function achieves consistency with the refracted-to-unrefracted
**     A tan Z + B tan^3 Z model at better than 1 microarcsecond within
**     30 degrees of the zenith and remains within 1 milliarcsecond to
**     beyond ZD 70 degrees.  The inherent accuracy of the model is, of
**     course, far worse than this - see the documentation for slaRefco
**     for more information.
**
**  3  At low elevations (below about 3 degrees) the refraction
**     correction is held back to prevent arithmetic problems and
**     wildly wrong results.  For optical/IR wavelengths, over a wide
**     range of observer heights and corresponding temperatures and
**     pressures, the following levels of accuracy (arcsec, worst case)
**     are achieved, relative to numerical integration through a model
**     atmosphere:
**
**              ZD    error
**
**              80      0.7
**              81      1.3
**              82      2.5
**              83      5
**              84     10
**              85     20
**              86     55
**              87    160
**              88    360
**              89    640
**              90   1100
**              91   1700         } relevant only to
**              92   2600         } high-elevation sites
**
**     The results for radio are slightly worse over most of the range,
**     becoming significantly worse below ZD=88 and unusable beyond
**     ZD=90.
**
**  4  See also the function slaRefz, which performs the adjustment to
**     the zenith distance rather than in Cartesian Az/El coordinates.
**     The present function is faster than slaRefz and, except very low
**     down, is equally accurate for all practical purposes.  However,
**     beyond about ZD 84 degrees slaRefz should be used, and for the
**     utmost accuracy iterative use of slaRefro should be considered.
**
**  Last revision:   22 October 2006
**
**  Copyright P.T.Wallace.  All rights reserved.
*/
{
   double x, y, z1, z, zsq, rsq, r, wb, wt, d, cd, f;

/* Initial estimate = unrefracted vector */
   x = vu[0];
   y = vu[1];
   z1 = vu[2];

/* Keep correction approximately constant below about 3 deg elevation */
   z = gmax ( z1, 0.05 );

/* One Newton-Raphson iteration */
   zsq = z * z;
   rsq = x * x + y * y;
   r = sqrt ( rsq );
   wb = refb * rsq / zsq;
   wt = ( refa + wb ) / ( 1.0 + ( refa + 3.0 * wb ) * ( zsq + rsq ) / zsq );
   d = wt * r / z;
   cd = 1.0 - d * d / 2.0;
   f = cd * ( 1.0 - wt );

/* Post-refraction x,y,z */
   vr[0] = x * f;
   vr[1] = y * f;
   vr[2] = cd * ( z + d * r ) + ( z1 - z );
}