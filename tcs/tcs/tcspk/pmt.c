#include <slalib.h>
#include "tcs.h"

int tcsPmt ( double pmodel[7], double ae2nm[3][3], double ota[3], int jbp,
             double *ia, double *ib, double *np,
             double *xt, double *yt, double *zt, double ae2mt[3][3] )

/*
**  - - - - - - -
**   t c s P m t
**  - - - - - - -
**
**  Translate the pointing model from geometrical coefficients into the
**  form needed for use.
**
**  Given:
**     pmodel  double[7]       basic pointing model (Note 1)
**     ae2nm   double[3][3]    nominal mount orientation matrix (Note 2)
**     ota     double[3]       telescope [Az,El] vector (Note 3)
**     jbp     int             TRUE = "below the pole"
**
**  Returned (arguments):
**     ia      double*         roll zero point (radians)
**     ib      double*         pitch zero point (radians)
**     np      double*         mount axes nonperpendicularity (radians)
**     xt      double*         telescope vector, x-component (Note 4)
**     yt      double*         telescope vector, y-component (Note 4)
**     zt      double*         telescope vector, z-component (Note 4)
**     ae2mt   double[3][3]    rotation matrix, [Az,El] to mount
**
**  Returned (function value):
**             int             0 = OK
**
**  Defined in tcs.h:
**     ROTLOC  enum            rotator locations
**     OTA     ROTLOC          Cass etc
**
**  Called:  slaDeuler, slaDmxm, slaDcc2s, slaDcs2c, slaDmxv, slaDtp2v,
**           tcsAim2enc, tcsAim2xe
**
**  Notes:
**
**  1  The array pmodel is a list of seven coefficients which comprise
**     the basic pointing model:
**                                            term names
**     element    meaning               equatorial     other
**
**      [0,1]   index errors              -IH,ID       IA,IE
**       [2]    vertical error             FLOP        FLOP
**       [3]    collimation error          -CH          CA
**       [4]    nonperpendicularity        -NP         NPAE
**      [5,6]   misalignment              -MA,ME       AW,AN
**
**     This 7-term basic model combines the contributions from all the
**     terms in the actual, operational, model.
**
**  2  The matrix ae2nm is the nominal [Az,El] to [roll,pitch] rotation
**     matrix.
**
**  3  The vector ota is the best estimate of the current orientation of
**     the (deflected) telescope optical axis in the [Az,El] frame.  It
**     is used to calculate the correction that must be applied to the
**     demanded [roll,pitch] to compensate for vertical deflection.
**
**  4  The TELESCOPE vector [xt,yt,zt] is in this frame:
**
**       x-axis:  at right angles to both the roll and pitch axes
**       y-axis:  along the pitch axis
**       z-axis:  at right angles to the other two axes
**
**     In the absence of either collimation error or vertical deflection
**     the TELESCOPE vector is [1,0,0].
**
**  Last revision:   15 June 2002
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

#define IA pmodel[0]
#define IE pmodel[1]
#define VD pmodel[2]
#define CA pmodel[3]
#define NP pmodel[4]
#define AW pmodel[5]
#define AN pmodel[6]

{
   int j;
   double axmis[3][3], v[3], az, el, u[3], x, y, z, a, b, a2, b2,
          xi, eta, f, w;



/* Return the basic model components that are used directly. */
   *ia = IA;
   *ib = IE;
   *np = NP;

/* Use the misalignment terms to adjust the [Az,El] to mount matrix. */
   slaDeuler ( "zyx", 0.0, -AN, AW, axmis );
   slaDmxm ( axmis, ae2nm, ae2mt );

/* Rotate the deflected OTA direction into the mount frame. */
   slaDmxv ( ae2mt, ota, v );

/* Express the deflected OTA direction as azimuth and elevation angles. */
   slaDcc2s ( ota, &az, &el );

/* Remove the vertical deflection and convert to x,y,z. */
   slaDcs2c ( az, el + VD, u );

/* Rotate the undeflected OTA direction into the mount frame. */
   slaDmxv ( ae2mt, u, u );

/* TELESCOPE vector for undeflected telescope. */
   x = cos ( CA );
   y = sin ( CA );
   z = 0.0;

/* Undeflected OTA direction to [roll,pitch]. */
   tcsAim2enc ( u[0], u[1], u[2],
                OTA, 0.0, 0.0, 0.0,
                0.0, 0.0,
                0.0, 0.0, NP,
                x, y, z,
                0.0, 0.0,
                &a, &b, &a2, &b2, &j );

/* Select the right solution. */
   if ( jbp ) {
      a = a2;
      b = b2;
   }

/* Deflected OTA direction as [xi,eta]. */
   tcsAim2xe ( v[0], v[1], v[2], a, b, NP, x, y, z, &xi, &eta, &j );

/* Use [xi,eta] to determine deflected TELESCOPE vector. */
   f = sqrt ( 1.0 + xi * xi + eta * eta );
   w = eta * z;
   *xt = ( x - xi * y - w * x ) / f;
   *yt = ( y + xi * x - w * y ) / f;
   *zt = ( z + eta ) / f;

/* Finished. */
   return j;

}
