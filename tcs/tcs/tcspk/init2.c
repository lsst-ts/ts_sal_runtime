#include <slalib.h>
#include "tcs.h"
#include "tcsmac.h"

int tcsInit2 ( double tlongm, double tlatm, double xpmr, double ypmr,
               double hm, MTYPE mount,
               double gim1z, double gim2y, double gim3x,
               double ae2nm[3][3], double* tlong, double* tlat,
               double* uau, double* vau,
               double* ukm, double* vkm, double* diurab )

/*
**  - - - - - - - - -
**   t c s I n i t 2
**  - - - - - - - - -
**
**  Secondary initialization.
**
**  Given:
**     tlongm  double          site mean east longitude (radians)
**     tlatm   double          site mean geodetic latitude (radians)
**     xpmr    double          polar-motion x angle (radians)
**     ypmr    double          polar-motion y angle (radians)
**     hm      double          site elevation, metres above sea-level
**     mount   MTYPE           mount type
**     gim1z   double          1st rotn, about z | generalized gimbal,
**     gim2y   double          2nd rotn, about y | orientn wrt [Az,El],
**     gim3x   double          3rd rotn, about x | terrestrial N
**
**  Returned (arguments):
**     ae2nm   double[3][3]    rotation matrix, [Az,El] to nominal mount
**     tlong   double*         telescope longitude (true)
**     tlat    double*         telescope latitude (true)
**     uau     double*         distance from spin axis (AU)
**     vau     double*         distance from equator (AU)
**     ukm     double*         distance from spin axis (km)
**     vkm     double*         distance from equator (km)
**     diurab  double*         diurnal aberration (radians)
**
**  Returned (function value):
**             int             status (0 = OK)
**
**  Defined in tcs.h:
**     MTYPE   enum            mount type codes
**     ALTAZ   MTYPE           altazimuth
**     GIMBAL  MTYPE           generalized gimbal
**
**  Defined in tcsmac.h:
**     PI2     double          2Pi
**     C       double          speed of light (AU/day)
**     AU2KM   double          AU to km
**     UTST    double          ratio of SI to ST second
**     D90     double          90 deg in radians
**
**  Called:  slaPolmo, slaGeoc, slaDeuler
**
**  Last revision:   4 May 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{
   double daz;


/* Correct the telescope latitude, longitude and azimuth for polar motion. */
   slaPolmo ( tlongm, tlatm, xpmr, ypmr, tlong, tlat, &daz );

/* Distance of observatory from Earth spin axis and equator. */
   slaGeoc ( *tlat, hm, uau, vau );
   *ukm = *uau * AU2KM;
   *vkm = *vau * AU2KM;
   *diurab = PI2 * *uau * UTST / C;

/* Rotation matrix, celestial [Az,El] to nominal mount. */
   if ( mount != GIMBAL ) {
      gim1z = 0.0;
      gim2y = mount == ALTAZ ? 0.0 : *tlat - D90;
      gim3x = 0.0;
   }
   slaDeuler ( "zyx", gim1z + daz, gim2y, gim3x, ae2nm );

   return 0;
}
