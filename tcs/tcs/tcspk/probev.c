#include <math.h>

void tcsProbev ( double v0[3], double del,
                 double v1[3], double v2[3], double v3[3] )

/*
**  - - - - - - - - - -
**   t c s P r o b e v
**  - - - - - - - - - -
**
**  Generate three probe vectors suitable for sampling the pointing
**  transformation.
**
**  Given:
**     v0      double[3]     central position
**     del     double        radial distance of probe vectors (Note 3)
**
**  Returned:
**     v1      double[3]     1st probe vector
**     v2      double[3]     2nd probe vector
**     v3      double[3]     3rd probe vector
**
**  Notes:
**
**  1  This routine returns three vectors surrounding the given one.
**     The pattern is essentially an equilateral triangle with one
**     vertex in the +z direction;  each probe vector is del radians
**     from v0.  Except for pathological cases, the method does not
**     depend critically on any particular pattern or spacing.
**
**  2  The probe vectors are intended to be transformed in the
**     application in order to explore the nature of the transformation
**     in the region, the end result being a 3x3 matrix called the
**     "sky-patch matrix".  The matrix is generated with the routine
**     tcsSpm.
**
**  3  If a del value less than zero is supplied, a pattern is returned
**     in which the third probe vector, v3, is coincident with the
**     central position, v0.  This will ultimately yield SPMs that give
**     perfect answers for the direction v0.
**
**  Last revision:   13 June 2003
**
**  Copyright P.T.Wallace.   All rights reserved.
*/

#define TINY 1e-10

{
   double r, sa, ca, sasb, casb, d, x, y, z, f;

/* Separation resolved into vertical and horizontal components */
   double dup, ddn, drl;

/* X,Y,Z components of separations */
   double dxup, dyup, dzup, dxdn, dydn, dzdn, dxrl, dyrl;



/* Central vector. */
   x = v0[0];
   y = v0[1];
   z = v0[2];

/* Useful functions. */
   r = sqrt ( x * x + y * y );
   if ( r >= TINY ) {
       sa = y / r;
       ca = x / r;
   } else {
       sa = 0.0;
       ca = 1.0;
   }
   sasb = sa * z;
   casb = ca * z;

/* Override too-small del. */
   d = fabs ( del ) > TINY ? del : TINY;

/* X,Y,Z shifts for generating the three probe vectors. */
   dup = d;
   ddn = d * 0.5;
   drl = d * 0.866025404;

   dxup = -dup * casb;
   dyup = -dup * sasb;
   dzup = dup * r;

   dxdn = -ddn * casb;
   dydn = -ddn * sasb;
   dzdn = ddn * r;

   dxrl = -drl * sa;
   dyrl = drl * ca;

/* Normalization factor. */
   f = 1.0 / sqrt ( 1.0 + d * d );

/* First probe vector: above the true vector. */
   v1[0] = f * ( x + dxup );
   v1[1] = f * ( y + dyup );
   v1[2] = f * ( z + dzup );

/* Is v0 to be central or at one corner? */
    if ( del > 0.0 ) {

   /* Central.  First probe vector: above the true vector. */
      v1[0] = f * ( x + dxup );
      v1[1] = f * ( y + dyup );
      v1[2] = f * ( z + dzup );

   } else {

   /* At one corner.  First probe vector is the true vector. */
      v1[0] = x;
      v1[1] = y;
      v1[2] = z;
   }

/* Second probe vector: down and to the left. */
   v2[0] = f * ( x - dxdn - dxrl );
   v2[1] = f * ( y - dydn - dyrl );
   v2[2] = f * ( z - dzdn );

/* Third probe vector: down and to the right. */
   v3[0] = f * ( x - dxdn + dxrl );
   v3[1] = f * ( y - dydn + dyrl );
   v3[2] = f * ( z - dzdn );

}
