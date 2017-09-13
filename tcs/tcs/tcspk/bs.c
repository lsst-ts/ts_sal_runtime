#include "tcs.h"

void tcsBs ( double xt, double yt, double zt,
             ROTLOC rotl, double rma, double a, double b,
             double ga, double gb,
             double xpo, double ypo, double *xb, double *yb, double *zb )

/*
**  - - - - - -
**   t c s B s
**  - - - - - -
**
**  Determine the telescope boresight direction, in a righthanded
**  Cartesian frame where the x,y plane contains the nominal telescope
**  and the pitch axis, and the x-axis is close to the telescope.
**
**  Given:
**     xt       double        telescope vector, x-component (Note 1)
**     yt       double        telescope vector, y-component (Note 1)
**     zt       double        telescope vector, z-component (Note 1)
**     rotl     ROTLOC        rotator location (Note 2)
**     rma      double        rotator mechanical angle
**     a        double        mount roll encoder reading (Note 3)
**     b        double        mount pitch encoder reading (Note 3)
**     ga       double        guiding correction, collimation
**     gb       double        guiding correction, pitch
**     xpo      double        pointing-origin x (in focal lengths)
**     ypo      double        pointing-origin y (in focal lengths)
**
**  Returned:
**     xb       double*       boresight x-coordinate (Note 4)
**     yb       double*       boresight y-coordinate (Note 4)
**     cb       double*       boresight z-coordinate (Note 4)
**
**  Defined in tcs.h:
**     ROTLOC   enum          rotator locations
**
**  Called:  tcsXy2xe
**
**  Notes:
**
**  1  The TELESCOPE vector [xt,yt,zt] is in this frame:
**
**       x-axis:  at right angles to both the roll and pitch axes
**       y-axis:  along the pitch axis
**       z-axis:  at right angles to the other two axes
**
**     In the absence of either collimation error or vertical deflection
**     the TELESCOPE vector is [1,0,0].
**
**  2  If an invalid rotator-location code is presented, the OTA case
**     (Cass etc) is assumed.
**
**  3  If the rotator location is OTA (Cass etc), the roll/pitch angles
**     are not used.
**
**  4  The boresight vector [xb,yb,zb] is expressed in a righthanded
**     Cartesian frame where the x,y plane contains the OTA and the
**     pitch axis, and the x-axis is close to the OTA.
**
**  Last revision:   8 June 2003
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{
   double xi, eta, f, r, w;



/* Pointing-origin position with respect to rotator axis. */
   tcsXy2xe ( xpo, ypo, rotl, rma, a, b, &xi, &eta );

/* Displace rotator axis to allow for guiding. */
   xi += ga;
   eta += gb;

/* Apply net pointing-origin to TELESCOPE, giving BORESIGHT. */
   f = sqrt ( 1.0 + xi * xi + eta * eta );
   r = sqrt ( xt * xt + yt * yt );
   if ( r == 0.0 ) {
      r = 1e-20;
      xt = r;
   }
   w = eta * zt;
   *xb = ( xt - ( xi * yt + w * xt ) / r ) / f;
   *yb = ( yt + ( xi * xt - w * yt ) / r ) / f;
   *zb = ( zt + eta * r ) / f;
}
