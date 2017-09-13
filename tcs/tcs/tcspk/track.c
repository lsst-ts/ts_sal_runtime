#include "tcs.h"

void tcsTrack ( double tara, double tarb,
                double spm1[3][3],
                FRAMETYPE frame, double sst, double cst,
                double spm2[3][3],
                ROTLOC rotl, double rotap, double ap, double bp,
                double xim, double yim,
                double ia, double ib, double np,
                double xt, double yt, double zt,
                double ga, double gb, double rnogo,
                double *xa, double *ya, double *za,
                double *enca1, double *encb1,
                double *enca2, double *encb2, int *j )

/*
**  - - - - - - - - -
**   t c s T r a c k
**  - - - - - - - - -
**
**  The main telescope tracking routine:  in a "virtual telescope",
**  calculate the encoder demands required to image a given target
**  at a specified place in the focal plane.
**
**  The routine also returns the AIM vector, needed for the rotator
**  predictions.
**
**  Given:
**     tara     double        target "roll" coordinate (Note 1)
**     tarb     double        target "pitch" coordinate (Note 1)
**     spm1     double[3][3]  SPM #1 (Note 3)
**     frame    FRAMETYPE     reference frame for the target (Note 3)
**     sst      double        sine of sidereal time (Notes 2,3)
**     cst      double        cosine of sidereal time (Notes 2,3)
**     spm2     double[3][3]  SPM #2 (Note 3)
**     rotl     ROTLOC        rotator location
**     rotap    double        predicted rotator mechanical angle (Note 4)
**     ap       double        predicted roll (Note 5)
**     bp       double        predicted pitch (Note 5)
**     xim      double        pointing origin x (in focal lengths)
**     yim      double        pointing origin y (in focal lengths)
**     ia       double        roll zero point (radians)
**     ib       double        pitch zero point (radians)
**     np       double        mount axes nonperpendicularity (radians)
**     xt       double        telescope vector, x-component (Note 6)
**     yt       double        telescope vector, y-component (Note 6)
**     zt       double        telescope vector, z-component (Note 6)
**     ga       double        guiding correction, collimation
**     gb       double        guiding correction, pitch
**     rnogo    double        radius of "no go" region (radians, Note 7)
**
**  Returned:
**     xa       double        AIM x-coordinate (Note 1)
**     ya       double        AIM y-coordinate (Note 1)
**     za       double        AIM z-coordinate (Note 1)
**     enca1    double        roll coordinate, first solution (Note 8)
**     encb1    double        pitch coordinate, first solution (Note 8)
**     enca2    double        roll coordinate, second solution (Note 8)
**     encb2    double        pitch coordinate, second solution (Note 8)
**     j        int           status: +1 = pole avoidance (Note 9)
**                                     0 = OK
**                                    -1 = no solutions (Note 9)
**
**  Defined in tcs.h:
**     FRAMETYPE    enum      frame types
**     ROTLOC       enum      rotator locations
**
**  Called:  tcsSky2aim, tcsAimtrk
**
**  Notes:
**
**  1  A "virtual telescope" is a group of transformations that link
**     three sets of coordinates:
**
**       (i)  the target (where in the sky the source is);
**
**      (ii)  the pointing-origin (where in the focal plane the image
**            appears);
**
**     (iii)  the mount encoder readings (that cause the image of the
**            target to fall in the specified place in the focal plane).
**
**     The transformations are specified by various time-dependent
**     rotation matrices, pointing corrections, functions of rotator
**     angle and so on.  They form a chain:
**
**
**                [ TARGET ]             <- target [a,b]
**                     v
**        astronomical transformations   <- time, site
**                     v
**                 refraction            <- weather
**                     v
**              mount orientation        <- ae2mt
**                     v
**                  [ AIM ]
**                     |                 }
**                   roll                }
**                     |                 } -> encoder [a,b]
**            roll/pitch nonperp         }
**                     |                 } <- np, ia, ib
**                   pitch               }
**                     |                 }
**               [ BORESIGHT ]
**                     ^
**                  guiding              <- ga, gb
**                     ^
**               pointing origin         <- [x,y] and rotator angle
**                     ^
**               [ TELESCOPE ]
**                     ^
**                   flop                <- vertical deflection terms
**                     ^
**             tel/pitch nonperp         <- collimation terms
**                     ^
**                 [ 1,0,0 ]
**
**
**     Given any two of the three sets of coordinates (sky, pointing-
**     origin, mount), the missing coordinates can be deduced.  There is
**     only one mount, and hence all the virtual telescopes must share
**     the same encoder demands, namely those generated by the main
**     "mount tracking" virtual telescope.  The remaining virtual
**     telescopes implement such features as autoguiding and tip/tilt
**     secondary optics, either by deducing the image position for a
**     given target, or deducing the sky coordinates that correspond to
**     a given place in the focal plane.
**
**     In the present case, the encoder demands required to image the
**     specified sky target at the specified pointing-origin are
**     calculated.  The AIM vector, an intermediate result, is also
**     returned, so that it can be used in a subsequent call to the
**     tcsRotator function.
**
**  2  The arguments sst and cst are the sine and cosine of the local
**     apparent sidereal time.  Neither is used if the target frame is
**     topocentric Az/El.
**
**  3  The way frame, spm1, sst, cst and spm2 are used depends on the
**     type of target coordinates:
**
**       frame        FK4
**       target       Bxxxx RA,Dec, current date
**       spm1         mean RA,Dec -> geocentric apparent RA,Dec
**       sst,cst      RA,Dec -> HA,Dec
**       spm2         geocentric HA,Dec -> AIM
**
**       frame        FK5
**       target       Jxxxx RA,Dec, current date
**       spm1         mean RA,Dec -> geocentric apparent RA,Dec
**       sst,cst      RA,Dec -> HA,Dec
**       spm2         geocentric HA,Dec -> AIM
**
**       frame        APPT
**       target       geocentric apparent RA,Dec
**       spm1         identity matrix
**       sst,cst      RA,Dec -> HA,Dec
**       spm2         geocentric HA,Dec -> AIM
**
**       frame        APPT_TOPO
**       target       topocentric apparent RA,Dec
**       spm1         identity matrix
**       sst,cst      RA,Dec -> HA,Dec
**       spm2         topocentric HA,Dec -> AIM
**
**       frame        AZEL_TOPO
**       target       topocentric Az,El (N thru E)
**       spm1         identity matrix
**       sst,cst      not used
**       spm2         topocentric Az,El -> AIM
**
**     ICRS = FK5 J2000 to better than 25 mas.
**
**  4  The predicted rotator angle rotap is the orientation that the
**     mechanical rotator (whether at a coude or Nasmyth focus, or
**     mounted on the OTA) is expected to reach at the time for which
**     the prediction is being made.  Note that it is the predicted
**     achieved position, not a demand position.
**
**  5  The arguments ap and bp are an estimate of the coordinates
**     a and b which are being computed.  The results are not very
**     sensitive to the values used.
**
**  6  The TELESCOPE vector [xt,yt,zt] is in this frame:
**
**       x-axis:  at right angles to both the roll and pitch axes
**       y-axis:  along the pitch axis
**       z-axis:  at right angles to the other two axes
**
**     In the absence of either collimation error or vertical deflection
**     the TELESCOPE vector is [1,0,0].
**
**  7  Near the pole of the mounting (i.e. the zenith in the case of an
**     altazimuth) a variety of problems arises.  These include
**     confusion about which way round to go, rivalry between the mount
**     and rotator, and cases for which there are no solutions (see also
**     Note 9).  In any event, there are limits to what speeds and
**     accelerations the mechanical drives can achieve.  The present
**     routine provides one strategy for avoiding difficulties in this
**     region.
**
**     The argument rnogo specifies how close to the pole of the
**     mounting the target is allowed to be.  If the target is too
**     close, the routine aims instead for a fictitious target further
**     out, on the edge of the forbidden region.  A warning status is
**     set when this "pole avoidance" action is taken.
**
**     It is permissible to set rnogo to zero, and to handle any pole
**     problems in the TCS application itself.  Two strategies that
**     might be considered as an alternative to the rnogo approach are
**     (i) progressive scaling back of certain of the pointing
**     coefficients so that close to the pole the mount becomes
**     nominally perfect, and (ii) substituting a fictitious target that
**     makes the telescope loiter on the edge of the awkward region
**     until the real target catches up.
**
**  8  If the mount is an altazimuth, the roll coordinate is pi-azimuth
**     and the pitch coordinate is elevation.  If the mount is an
**     equatorial, roll is -HA and pitch is declination.  For any
**     accessible target, there are two solutions; depending on the type
**     of mount, the two solutions correspond to above/below the pole,
**     nearside/farside of the zenith, east/west of the pier, and so on.
**
**  9  Near the pole of the mounting, especially when the collimation
**     error or nonperpendicularity are large, there may be no mount
**     posture that images the target at the desired place.  In these
**     cases, the status j is set to the "no solutions" value, and the
**     returned roll and pitch are set to safe values.
**
**     The "no solution" status overrides the "pole avoidance" status
**     (see Note 7).
**
**  Last revision:   5 March 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/
{

/* SKY target coordinates to AIM vector. */
   tcsSky2aim ( tara, tarb, spm1, frame, sst, cst, spm2, xa, ya, za );

/* AIM vector to ENCODER readings. */
   tcsAimtrk ( *xa, *ya, *za, rotl, rotap, ap, bp, xim, yim,
               ia, ib, np, xt, yt, zt, ga, gb, rnogo,
               enca1, encb1, enca2, encb2, j );

}
