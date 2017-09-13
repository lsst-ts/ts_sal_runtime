#include "slalib.h"
#include "slamac.h"
void slaM2av ( float rmat[3][3], float axvec[3] )
/*
**  - - - - - - - -
**   s l a M 2 a v
**  - - - - - - - -
**
**  From a rotation matrix, determine the corresponding axial vector.
**
**  (single precision)
**
**  A rotation matrix describes a rotation about some arbitrary axis,
**  called the Euler axis.  The "axial vector" returned by this function
**  has the same direction as the Euler axis, and its magnitude is the
**  amount of rotation in radians.  (The magnitude and direction can be
**  separated by means of the function slaVn.)
**
**  Given:
**    rmat   float[3][3]   rotation matrix
**
**  Returned:
**    axvec  float[3]      axial vector (radians)
**
**  The reference frame rotates clockwise as seen looking along
**  the axial vector from the origin.
**
**  If rmat is null, so is the result.
**
**  Last revision:   22 October 2006
**
**  Copyright P.T.Wallace.  All rights reserved.
*/
{
   float x, y, z, s2, c2, phi, f;

   x = rmat[1][2] - rmat[2][1];
   y = rmat[2][0] - rmat[0][2];
   z = rmat[0][1] - rmat[1][0];
   s2 = (float) sqrt ( (double) ( x * x + y * y + z * z ) );
   if ( s2 != 0.0f ) {
      c2 = rmat[0][0] + rmat[1][1] + rmat[2][2] - 1.0f;
      phi = (float) atan2 ( (double) s2 / 2.0, (double) c2 / 2.0 );
      f = phi / s2;
      axvec[0] = x * f;
      axvec[1] = y * f;
      axvec[2] = z * f;
   } else {
      axvec[0] = 0.0f;
      axvec[1] = 0.0f;
      axvec[2] = 0.0f;
   }
}
