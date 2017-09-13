#include "tcs.h"

void tcsCasspa ( ROTLOC rotl, double rma, double a, double b,
                 double *spa, double *cpa )

/*
**  - - - - - - - - - -
**   t c s C a s s p a
**  - - - - - - - - - -
**
**  Transform the rotator mechanical angle into the equivalent for
**  rotator mounted at Cassegrain.  The angle is returned in the form
**  of the sine and cosine.
**
**  Given:
**     rotl     ROTLOC        rotator location
**     rma      double        rotator mechanical angle
**     a        double        mount roll encoder reading
**     b        double        mount pitch encoder reading
**
**  Returned:
**     spa      double*       sine of rotator angle
**     cpa      double*       cosine of rotator angle
**
**  Defined in tcs.h:
**     ROTLOC          enum         rotator locations
**     NASMYTH_L       ROTLOC       Nasmyth (left)
**     NASMYTH_R       ROTLOC       Nasmyth (right)
**     COUDE_L         ROTLOC       Coude (left)
**     COUDE_R         ROTLOC       Coude (right)
**
**  Note:
**
**     If an invalid rotator-location code is presented, the Cass
**     case is assumed.
**
**  Last revision:   8 June 2003
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{
   double pa;



/* Rotator mechanical angle. */
   pa = rma;

/* If Nasmyth or coude, convert into Cassegrain equivalent. */
   switch ( rotl ) {
   case NASMYTH_L:
      pa -= b;
      break;
   case NASMYTH_R:
      pa += b;
      break;
   case COUDE_L:
      pa += a - b;
      break;
   case COUDE_R:
      pa += a + b;
      break;
   default:
      break;
   }

/* Sine and cosine of rotator angle. */
   *spa = sin ( pa );
   *cpa = cos ( pa );

}
