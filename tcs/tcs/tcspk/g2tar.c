#include "tcs.h"
#include <slalib.h>

void tcsG2tar ( double tara, double tarb,
                double xpo, double ypo,
                double enca, double encb,
                ROTLOC rotl, double rma,
                double spm1_i[3][3],
                FRAMETYPE frame, double sst, double cst,
                double spm2_i[3][3],
                double ia, double ib, double np,
                double xt, double yt, double zt,
                double *obtara, double *obtarb )

/*
**  - - - - - - - - -
**   t c s G 2 t a r
**  - - - - - - - - -
**
**  Transform the guiding adjustments into target coordinate offsets.
**
**  Given:
**
**   State before absorb operation
**     tara     double        target "roll" coordinate (e.g. RA)
**     tarb     double        target "pitch" coordinate (e.g. Dec)
**     xpo      double        pointing-origin x (in focal lengths)
**     ypo      double        pointing-origin y (in focal lengths)
**     enca     double        mount "roll" encoder demand (Note 2)
**     encb     double        mount "pitch" encoder demand (Note 2)
**
**   Rotator
**     rotl     ROTLOC        rotator location
**     rma      double        rotator mechanical angle
**
**   Celestial transformation
**     spm1_i   double[3][3]  inverse SPM #1 (Note 4)
**     frame    FRAMETYPE     reference frame for the target (Note 4)
**     sst      double        sine of sidereal time (Notes 3,4)
**     cst      double        cosine of sidereal time (Notes 3,4)
**     spm2_i   double[3][3]  inverse SPM #2
**
**   Pointing model
**     ia       double        roll zero point (radians)
**     ib       double        pitch zero point (radians)
**     np       double        mount axes nonperpendicularity (radians)
**     xt       double        telescope vector, x-component (Note 5)
**     yt       double        telescope vector, y-component (Note 5)
**     zt       double        telescope vector, z-component (Note 5)
**
**  Returned:
**     obtara   double*       required change to target "roll" (Note 1)
**     obtarb   double*       required change to target "pitch" (Note 1)
**
**  Called:  tcsVTsky, slaDrange
**
**  Notes:
**
**  1  The "absorb" operation supported by the present routine re-
**     expresses the current guiding adjustments as changes obtara,
**     obtarb (in radians) to the target coordinates.  The latter are
**     typically some form of RA,Dec, and so obtara,obtarb are typically
**     dRA,dDec.
**
**     Following the call, if the guiding adjustments are reset to zero
**     and obtara,obtarb are added to the current target, the telescope
**     will continue to track as if nothing has happened.
**
**     A convenient way to apply the offsets is as "offsets from base",
**     leaving the original target coordinates intact.
**
**  2  If the mount is an altazimuth and the chosen frame is an
**     [RA,Dec], enca is pi-azimuth, encb is elevation, tara is right
**     ascension and tarb is declination.  If the mount is an
**     equatorial, enca is -HA and encb is declination.  If the chosen
**     frame is topocentric [Az,El], enca is azimuth (n.b. not pi-
**     azimuth) and encb is elevation.
**
**  3  The arguments sst and cst are the sine and cosine of the local
**     apparent sidereal time.  Neither is used if the target frame is
**     topocentric Az/El.
**
**  4  The way frame, spm1_i, sst, cst and spm2_i are used depends on
**     the type of target coordinates:
**
**       frame        FK4
**       target       Bxxxx RA,Dec, current date
**       spm1_i       mean RA,Dec <- geocentric apparent RA,Dec
**       sst,cst      RA,Dec <- HA,Dec
**       spm2_i       geocentric HA,Dec <- AIM
**
**       frame        FK5
**       target       Jxxxx RA,Dec, current date
**       spm1_i       mean RA,Dec <- geocentric apparent RA,Dec
**       sst,cst      RA,Dec <- HA,Dec
**       spm2_i       geocentric HA,Dec <- AIM
**
**       frame        APPT
**       target       geocentric apparent RA,Dec
**       spm1_i       identity matrix
**       sst,cst      RA,Dec <- HA,Dec
**       spm2_i       geocentric HA,Dec <- AIM
**
**       frame        APPT_TOPO
**       target       topocentric apparent RA,Dec
**       spm1_i       identity matrix
**       sst,cst      RA,Dec <- HA,Dec
**       spm2_i       topocentric HA,Dec <- AIM
**
**       frame        AZEL_TOPO
**       target       topocentric Az,El (N thru E)
**       spm1_i       identity matrix
**       sst,cst      not used
**       spm2_i       topocentric Az,El <- AIM
**
**     ICRS = FK5 J2000 to better than 25 mas.
**
**  5  The TELESCOPE vector [xt,yt,zt] is in this frame:
**
**       x-axis:  at right angles to both the roll and pitch axes
**       y-axis:  along the pitch axis
**       z-axis:  at right angles to the other two axes
**
**     In the absence of either collimation error or vertical deflection
**     the TELESCOPE vector is [1,0,0].
**
**  6  See also tcsG2po, which absorbs the guiding corrections into the
**     pointing origin rather than the target coordinates.
**
**  Last revision:   5 March 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{
   double a, b;


/* Adjusted target coordinates for zero guiding corrections. */
   tcsVTsky ( enca, encb, rotl, rma, xpo, ypo,
              spm1_i, frame, sst, cst, spm2_i,
              ia, ib, np, xt, yt, zt, 0.0, 0.0,
              &a, &b );

/* Return the offsets with respect to the current target. */
   *obtara = slaDrange ( a - tara );
   *obtarb = b - tarb;

}
