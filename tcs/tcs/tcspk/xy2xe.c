#include "tcs.h"

void tcsXy2xe ( double x, double y,
                ROTLOC rotl, double rma, double a, double b,
                double *xi, double *eta )

/*
**  - - - - - - - - -
**   t c s X y 2 x e
**  - - - - - - - - -
**
**  Rotate x,y rotator coordinates into non-rotating focal-plane
**  coordinates xi,eta.
**
**  Given:
**     x        double        x (in focal lengths)
**     y        double        y (in focal lengths)
**     rotl     ROTLOC        rotator location (Note 2)
**     rma      double        rotator mechanical angle
**     a        double        mount roll encoder reading (Note 3)
**     b        double        mount pitch encoder reading (Note 3)
**
**  Returned:
**     xi       double        focal-plane xi coordinate
**     eta      double        focal-plane eta coordinate
**
**  Defined in tcs.h:
**     ROTLOC   enum          rotator locations
**
**  Called:  tcsCasspa
**
**  Notes:
**
**  1  The x,y coordinates are fixed to the rotator and are in units of
**     1 focal length.
**
**     The focal-plane coordinates xi,eta are fixed to the OTA structure
**     and differ from x,y only in orientation (i.e. not scale).
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
**  4  This function can be used for transforming dx,dy signals from a
**     rotator-mounted autoguider into guiding corrections (called ga
**     and gb in routines such as tcsTrack).
**
**  Last revision:   13 March 2002
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{
   double spa, cpa;


/* Cass-equivalent rotator angle. */
   tcsCasspa ( rotl, rma, a, b, &spa, &cpa );

/* Transform x,y to xi,eta. */
   *xi = - x * cpa - y * spa;
   *eta = x * spa - y * cpa;
}
