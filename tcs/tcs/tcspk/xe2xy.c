#include "tcs.h"

void tcsXe2xy ( double xi, double eta,
                ROTLOC rotl, double rma, double a, double b,
                double *x, double *y )

/*
**  - - - - - - - - -
**   t c s X e 2 x y
**  - - - - - - - - -
**
**  Rotate non-rotating focal-plane coordinates xi,eta into x,y rotator
**  coordinates.
**
**  Given:
**     xi       double        focal-plane xi coordinate (Note 1)
**     eta      double        focal-plane eta coordinate (Note 1)
**     rotl     ROTLOC        rotator location (Note 2)
**     rma      double        rotator mechanical angle
**     a        double        mount roll encoder reading (Note 3)
**     b        double        mount pitch encoder reading (Note 3)
**
**  Returned:
**     x        double*       x (in focal lengths)
**     y        double*       y (in focal lengths)
**
**  Defined in tcs.h:
**     ROTLOC      enum       rotator locations
**
**  Called:  tcsCasspa
**
**  Notes:
**
**  1  The focal-plane coordinates xi,eta are fixed to the OTA structure
**     and differ from x,y only in orientation (i.e. not scale).
**
**     The x,y coordinates are fixed to the rotator and are in units of
**     1 focal length.
**
**     In cases such as Cass, where the rotator is mounted on the OTA,
**     xi = x and eta = y for rma = 180 deg.
**
**  2  If an invalid rotator-location code is presented, the OTA case
**     (Cass etc) is assumed.
**
**  3  If the rotator location is OTA (Cass etc), the roll/pitch angles
**     are not used.
**
**  Last revision:   13 March 2002
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{
   double spa, cpa;



/* Cass-equivalent rotator angle. */
   tcsCasspa ( rotl, rma, a, b, &spa, &cpa );

/* Rotate the xi,eta into x,y. */
   *x = - xi * cpa + eta * spa;
   *y = - xi * spa - eta * cpa;

}
