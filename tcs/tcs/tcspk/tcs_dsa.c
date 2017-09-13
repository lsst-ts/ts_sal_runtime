#include <stdio.h>
#include <slalib.h>
#include "tcs.h"
#include "tcsmac.h"

/* Special radio refraction function */
void dsaRefsub ( int, double, double,
                 double, double, double, double, double, double, double,
                 double, double, double, double*, double*, double* );

/* Maximum size of scan polyline */
#define NSPMAX 400

/* Scan states */
typedef enum { SCAN_OFF = 0,     /* no scanning activity */
               SCAN_ARMED = 1,   /* begin at start time */
               SCAN_ACTIVE = 2,  /* scanning */
               SCAN_PAUSE = 3    /* halted */
             } SCAN_STATE;

/* Additional (replacement) codes for the FAST routine. */
#define SCANPARS  16   /* scan parameters */
#define SCANCTRL  32   /* scan control */

void tcsFast_dsa ( int, int, double, double, double, double, double,
                   double, double, double, double, double, double, double,
                   double, double[2], double[2], double, int,
                   float[NSPMAX][2], double, int, double, SCAN_STATE,
                   FRAMETYPE, double[3][3], double[3][3],
                   double*, double* );

int main ( )

/*
**  - - - - - - - -
**   T C S _ D S A
**  - - - - - - - -
**
**  Demonstration of TCSpk pointing kernel, oriented towards a deep-
**  space antenna application.
**
**  Disabled features:
**
**  . Altazimuth only.  Equatorial and generalized gimbal cases are
**    not supported.
**
**  . No instrument rotator (and no field-orientation support).
**
**  . Support for off-axis pointing-origins is absent.  The pointing-
**    origin concept is, however, used, to implement scanning.
**
**  . Polar motion corrections (~ 0.1 mdeg) are neglected.
**
**  ----------------
**  REAL-TIME DESIGN
**  ----------------
**
**  The fundamental principle upon which the TCSpk design, and
**  this demonstration, rests is that there are two threads with
**  a shared context.  One thread, at lower priority, maintains the
**  context, while the other, at higher priority or operating in
**  a separate processor, uses it to generate timestamped positions
**  for the mount axes.  The low-priority thread is triggered by a
**  combination of timer interrupts (typically every few seconds) and
**  notifications from the user-interface that something has changed.
**  The high-priority thread is triggered at, say, 10 Hz by timer
**  interrupts.  In the present implementation, the high-priority
**  thread is also triggered by the low-priority thread to cause it to
**  download pieces of changed context.  Other schemes for managing the
**  context can be substituted if preferred.
**
** ---------------
** EXTERNAL EVENTS
** ---------------
**
** Here is a summary of what actions the TCS application needs to take
** when various external events occur.
**
**   EVENT                        ACTION
**
**   Start-up                     Primary initialization of the context,
**                                then calls to tcsInit2, tcsSlow and
**                                tcsMedium.  Begin scheduling periodic
**                                tcsSlow and tcsMedium updates.  Call
**                                tcsFast_dsa to cause it to copy the
**                                whole of the context.
**
**   Every 10s (or so)            Call tcsSlow.
**
**   Every 5s (or so)             Call tcsMedium, then call tcsFast_dsa
**                                to cause it to copy the whole
**                                context.
**
**   User supplies a new          Obtain the new information and then
**   target.                      call tcsTargup to calculate the
**                                current net position.  Call tcsMedium
**                                to update the transformation to
**                                match the new position, and then call
**                                tcsFast_dsa to cause it to copy the
**                                context items that have changed.  It
**                                is usually appropriate to zero the
**                                guiding corrections (ga,gb) at this
**                                point.
**
**   User updates the target      Obtain the new information and then
**   offsets from base or         call tcsFast_dsa to cause it to copy
**   differential tracking        the context items that have changed.
**   rates.                       A refinement would be to test whether
**                                the target position had changed
**                                significantly (more than a few
**                                arcminutes) and, if so, to call
**                                tcsMedium before the call to
**                                tcsFast_dsa.
**
**   Guiding activity occurs.     Call tcsFast_dsa to cause it to copy
**                                the updated ga and gb values.
**
**   Every 100ms (or so).         Trigger tcsFast_dsa to cause it to
**                                calculate new mount positions.  A
**                                good time to choose is that of the
**                                next 10Hz iteration.
**
** It is a good plan to combine the slow and medium processing rather
** than having separate scheduling arrangements.  On most occasions,
** tcsMedium alone can be called (followed by tcsFast_dsa), but once
** every so many invocations the call to tcsMedium can be preceded with
** a call to tcsSlow.
**
** -----------------
** DATA REQUIREMENTS
** -----------------
**
** Here is a summary of the information required to drive the TCS.
**
**   INITIALIZATION
**
**   . Site longitude, latitude and height above sea level.
**
**       Inaccurate site coordinates will show up as spurious
**       azimuth-axis misalignment parameters.  If grossly wrong,
**       the refraction predictions will be unreliable.  Height
**       makes little difference (but air pressure does - see below).
**
**   . UT1-UTC.
**
**       Obtain from IERS predictions, which are available on the
**       WWW.  The value is always less than 0.9 seconds and can be
**       plus or minus.  It changes by 1 or 2 milliseconds per day
**       typically.
**
**   . TAI-UTC.
**
**       Likewise from IERS data.  Note that when leap seconds occur
**       TAI-UTC and UT1-UTC both change by exactly 1 second.  It is
**       permissible to use the same pair of values through the leap
**       second and for a few days afterwards.
**
**   . TT-TAI.
**
**       Always 32.184s.
**
**   . Refraction data.
**
**       Temperature, pressure and relative humidity are all
**       required, to whatever accuracy they are available.  The
**       observing wavelength should be specified if optical sighting
**       is to be used.
**
**   . Initial mount coordinates.
**
**       Some legal values are needed to start the system.  They
**       do not have to reflect the actual attitude.
**
**   . Frames.
**
**       A reference frame for controlling the antenna must be
**       specified.  FK5 is the sensible default.  Along with the
**       frame ID, an equinox is needed:  2000.0 is the obvious
**       choice.
**
**   . Pointing model.
**
**       A pointing model is required.  It can be set up in two
**       different ways (only one of which is used in this
**       demonstration.  It is possible to change the coefficient values
**       while running (or even the form of the model);  the new
**       corrections will take effect the next time the MEDIUM routine
**       is run.
**
**   . Guiding adjustments.
**
**       These should be initialized to zero.
**
**   REFRACTION DATA
**
**   . Meteorological readings plus color.
**
**       The temperature, pressure, humidity, lapse rate and
**       reference wavelength can be changed at any time.  The
**       changes will take effect when the SLOW routine is next
**       run.
**
**       Note:  the DSA application has stringent requirements in
**       this area, and frequent updates may be neeed in order to
**       track the changes in pressure, temperature and, especially,
**       humidity.  Furthermore, the radio refraction may be
**       predicted by a special routine (dsaRef) that bypasses the
**       two-coefficient model supported by the SLOW routine.  In
**       the end it may be best to rearrange the SLOW/MEDIUM logic.
**
**   SCANNING
**
**   . Scan unit.
**
**       The pointing-origin feature of TCSpk is in the present
**       application used for scanning rather than to control image
**       position in the focal plane.  (A "beamswitching" capability
**       can be implemented by dynamically changing the IE and CA terms
**       in the pointing model.)  Because of this, the "focal length" is
**       in fact the scan unit in radians, and the variable name is
**       "s_unit".  A value of 1.0 means the scan unit is radians;  a
**       value of about 0.01745 means the scan unit is degrees;  other
**       values would allow the scan to be specified in terms of
**       beamwidths; and so on.  To first order, an offset of 1.0 will
**       move the antenna s_unit radians on the sky.
**
**   . List of [x,y] offsets, and size of list.
**
**        The scan pattern is defined as a series of [x,y] offsets,
**        where x is left-right and y is up-down along great circles
**        in the tracking frame.  The offsets are floats in a unit of
**        choice (for example degrees) measured in the tangent plane.
**        It is assumed that the trajectory is linear between the
**        [x,y] offsets.
**
**   . Time per cycle.
**
**        The period of the scan is defined by the number of
**        seconds required to cycle through all the [x,y] positions.
**        Often, the period will be the length of the [x,y] list
**        multiplied by the interval between successive mount
**        trajectory calculations (e.g. 0.1 sec).
**
**   . Number of cycles.
**
**        Scans can be one or more cycles long, or can continue
**        indefinitely.
**
**   . Scan reference time.
**
**        The scan reference time, or "epoch", is the TAI MJD at which
**        the first offset position is demanded.
**
**   . Scan status/command.
**
**        Scan actions are controlled by sending a status flag.
**        Internally, the status changes as the scan progresses, though
**        this is not visible to the application.  The following actions
**        are available:
**
**        * Disengage scanning activity, returning to the un-offset
**          position.
**
**        * Begin scanning at the specified reference time.  If
**          the reference time is in the past, scanning begins
**          immediately at the offset that would have been reached
**          has the scan started at the reference time.
**
**        * Begin scanning immediately, starting from the phase
**          corresponding to the current time with respect to the
**          reference time.
**
**        * Halt the scan at its present offset.  (n.b. There is no
**          provision for resumption from the current offset;  phase
**          is always determined by the current and reference times.
**          Should such an effect be desired, it could be achieved
**          by sending a revised reference time.)
**
**        To scan indefinitely, specify a number of cycles less than
**        one.
**
**        To finish scanning at the end of the current cycle, send a
**        revised number of cycles.
**
**   FRAME AND TARGET
**
**   . Mount frame (and equinox if needed).
**
**        FK5/2000 can be used for almost everything.  For
**        tracking planets, geocentric apparent place may
**        also be needed, depending on how the ephemeris
**        data are being calculated.  Topocentric Az/El is
**        available and can be used when applying pointing and
**        refraction corrections to spacecraft predictions.
**
**   . Color for mount tracking.
**
**        This allows atmospheric dispersion to be corrected in
**        the optical case.
**
**   . Target coordinates.
**
**        The target RA,Dec (or Az,El) can be changed at any
**        time, on their own, causing the antenna to move
**        to the new coordinates.  Various other actions may
**        be required at the same time, for example resetting
**        the offsets from base, resetting the guiding corrections
**        and so on.  It is up to the TCS designer to decide.
**
**   . Differential rates and reference time.
**
**        These allow solar-system objects to be tracked.  The
**        reference time is the TAI MJD at which the supplied
**        RA,Dec was, or will be, correct.
**
**   . Offsets from base.
**
**        These allow advanced features such as scan patterns
**        to be implemented.  It is better to use the offsets
**        than the target coordinates, because the original
**        (base) target can be recovered simply by resetting
**        the offsets to zero.
**
**  VIRTUAL TELESCOPES
**
**  TCSpk is based on a concept called the "virtual telescope".  This
**  is a set of transformations that link a place in the sky, called the
**  "target", with a place in the focal plane, called the "pointing
**  origin", and with a mechanical pointing direction for the telescope
**  (or in this case the antenna).
**
**  Complicated details such as pointing corrections are hidden inside
**  the virtual-telescope routines, so that clients (for example an
**  instrument wishing to offset the image in the focal plane) can do so
**  simply by adjusting the star or image coordinates.  A TCS always
**  supports at least one virtual telescope, that for the telescope
**  mount itself.  However, there may also be guiders, tip/tilt sub-
**  reflectors, and choppers present, and these can be implemented as
**  separate virtual telescopes, albeit ones which are forced to share
**  the one mount position (because there is only one mount).  (Most of
**  these concepts have no role in the DSA application of course.)
**
**  In the case of the mount virtual telescope, tracking demands are
**  obtained by transforming the target position through a series of
**  intermediate states into encoder coordinates.  The transformations
**  require knowledge of site location, time, weather and pointing
**  errors.  The following sets of coordinates are involved, in this and
**  any other virtual telescopes that the TCS is using:
**
**    Label            Meaning
**
**    TARGET           Where in the sky is to be imaged.  This is
**                     typically an RA,Dec (usually a J2000/ICRS RA,Dec)
**                     but topocentric Az/El is also supported.
**
**    AIM              The line-of-sight to the target, with respect to
**                     the mount frame.  The latter is typically close
**                     to either Az/El or HA/Dec.
**
**    POINTING-ORIGIN  The x,y in the focal plane which is to
**                     receive the image of the target.
**
**    BORESIGHT        The direction towards the light entering the
**                     telescope and forming an image at the pointing
**                     origin.  The xy plane of the coordinate frame
**                     contains the telescope, as defined by the antenna
**                     feed horn, and the "pitch" axis of the mount.
**
**    TELESCOPE        In the same coordinate frame as the boresight
**                     vector, the direction in which the telescope,
**                     as defined by the feed horn, is pointing.  This
**                     vector is [1,0,0], if the collimation error is
**                     zero.  Non-zero collimation error will affect
**                     the x and y components.
**
**    ENCODER          The encoder readings that the servos are
**                     instructed to realize.
**
**  The TCSpk package includes a number of routines which transform
**  between these coordinates in various ways.  They are set out below;
**  the given coordinates are marked "in" and the computed coordinates are
**  marked "out".
**
**                    TAR     AIM     PO     BS     TEL    ENC
**
**    tcsAim2enc              in      in            in     out
**    tcsAim2s_c     *out     in
**    tcsAim2xe               in    **out           in
**    tcsAimtrk               in      in            in     out
**    tcsBs                           in     out    in
**    tcsEnc2aim              out            in            in
**    tcsSky2aim      in      out
**    tcsSky2a_c     *in      out
**    tcsTrack        in      out     in            in     out
**    tcsTrack_c     *in      out     in            in     out
**    tcsVTenc        in              in            in     out
**    tcsVTenc_c     *in              in            in     out
**    tcsVTsky        out             in            in     in
**    tcsVTsky_c     *out             in            in     in
**    tcsVTxe         in            **out           in     in
**    tcsVTxe_c      *in            **out           in     in
**    tcsVTxy         in            **out           in     in
**    tcsVTxy_c      *in            **out           in     in
**
**   *  The routines with names ending in "_c" omit a conversion
**      between Cartesian and spherical coordinates.
**
**   ** The tcsAim2xe, tcsVTxe and tcsVTxe_c functions return
**      coordinates (xi,eta) in the non-rotating focal plane.  The
**      tcsVTxy and tcsVTxy_c functions return coordinates (x,y) in the
**      rotating focal plane.  In all cases the results are in natural
**      units (i.e. unit focal length).
**
**  Last revision:   24 November 2006
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{
/* Context */
#include "dsactx.h"

   int i, i4[4], j;
   char s;
   double tai, ra, dec, t, st, sst, cst,
          a1, b1, a2, b2, a, b, r;

/*
** --------------
** Initialization
** --------------
**
** An operational antenna control system needs to do all of the
** following before the system enters its real-time mode.  Normally
** the process would be controlled from an external agent such as a
** configuration file.
**
** n.b. C's default initialization to zero is assumed.
**
*/

/* Special refraction routine. */
   rfun = dsaRefsub;

/* Site and antenna. */
   tlongm = 116.191*D2R;             /* New Norcia (town) longitude... */
   tlatm = -30.953*D2R;              /* ...and latitude...*/
   hm = 200.0;                       /* ...and nominal height */
   rnogo = 0.5*D2R;                  /* Zenith avoidance distance */

/* Time. */
   delut = 0.746/86400.0;
   delat = 29.0/86400.0;
   ttmtai = 32.184/86400.0;
   xpmr = ypmr = 0.0;                /* Polar motion neglected */

/* Met. */
   temp = 275.0;
   press = 1000.0;
   humid = 0.8;
   tlr = 0.0065;
   wavelr = 1e6;

/* Mount type. */
   mount = ALTAZ;

/* Mount before/beyond zenith state. */
   jbp = 0;

/* Initial mount [roll,pitch] (arbitrary). */
   roll = 0.0;
   pitch = 1.0;

/* Tracking frame. */
   cosys = FK5;                    /* FK5 J2000 ... */
   eqx = 2000.0;                   /* ... = ICRS, more or less */
   wavel = 1e6;                    /* Radio refraction */

/* Initialize pointing model from TPOINT "OUTMOD" file. */
   if ( tcsIntpm ( "dsa.mod", MAXTRM, NTROOM, model,
                   &nterml, &ntermx, &nterms,
                   coeffn, coform, coeffv ) ) return -1;

/* Guiding adjustments. */
   ga = 0.0*AS2R;
   gb = 0.0*AS2R;

/* Secondary initialization. */
   if ( tcsInit2 ( tlongm, tlatm, xpmr, ypmr, hm,
                   mount, 0.0, 0.0, 0.0, ae2nm,
                   &tlong, &tlat, &uau, &vau, &ukm, &vkm, &diurab ) ) {
      printf ( "\nSecondary initialization has failed.\n" );
      return -1;
   }

/* Initialize the scan-pattern variables. */
   s_unit = D2R;
   nsp = 0;
   for ( i = 0; i < NSPMAX; i++ ) {
      for ( j = 0; j < 2; j++ ) {
         s_path[i][j] = 0.0f;
      }
   }
   s_period = 1.0;
   nsc = 0;
   s_epoch = 0.0;
   jscan = SCAN_OFF;

/*
** ------------------------------------------------
** Run the SLOW routine for the first of many times
** ------------------------------------------------
**
** From now on, the SLOW routine must be run from time to time
** (e.g. once every 10s) to update the things that are slowly changing
** and target-independent.  Because the SLOW routine is comparatively
** CPU-intensive, most implementations will choose to run it in a
** different thread and at a lower priority than the FAST routine (or
** even in a different processor).  However, it can and should be run
** in the same thread as the MEDIUM routine (see later), which will
** ensure that the context never becomes internally inconsistent.
**
*/

/* Get the (approximate) "current" time. */
   (void) tcsTime ( &tai );

/* Perform the slow update for that time. */
   tcsSlow ( tai, delut, delat, ttmtai,
             temp, press, humid, wavelr, tlong,
             &t0, &st0, &tt0, &ttj, amprms, &refa, &refb );

/*
** --------------------------------------------------
** Run the MEDIUM routine for the first of many times
** --------------------------------------------------
**
** From now on, the MEDIUM routine must be run from time to time
** (e.g. every 5 seconds) in the background.  It updates the pointing
** model and also recalculates the "Sky-Patch Matrices".  The SPMs are
** 3x3 matrices which summarize the astrometric transformation for the
** current location in the sky, enabling rapid and concise
** transformations within the high-frequency part of the pointing
** algorithm.  The MEDIUM routine must also be run immediately as part
** of setting up a new target (see later), in such a way that it is
** impossible for the FAST routine ever to see inconsistent target and
** SPMs.
**
*/

/* Get the (approximate) "current" time. */
   (void) tcsTime ( &tai );

/* Perform the medium update for that time. */
   (void) tcsMedium ( tai, MAXTRM, model, coeffv, nterml, ntermx, nterms,
                      coeffn, coform, mount, ae2nm, roll, pitch, jbp, aux,
                      cosys, eqx, wavel, cosys, eqx, wavel,
                      tar_p,
                      t0, st0, ttj, temp, press, humid, tlr, wavelr,
                      refa, refb, rfun, hm, tlat, diurab, amprms,
                      &ia, &ib, &np, &xt, &yt, &zt, ae2mt,
                      spm1, spm1_i, spm2, spm2_i,
                      spm1, spm1_i, spm2, spm2_i );

/* Tell the FAST routine about everything initialized so far. */
   tcsFast_dsa ( ALL, jbp, tai,
                 t0, st0,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 tar_t0, tar_op0, tar_dt,
                 s_unit, nsp, s_path, s_period, nsc,
                 s_epoch, jscan,
                 cosys, spm1, spm2,
                 &roll, &pitch );

/*
** ---------------------------------------------
** Obtain a target as if from the user interface
** ---------------------------------------------
**
** This demonstration uses hardwired constants.  An operational
** system would obtain targets from the user in a variety of ways,
** and would then set up the following context variables:
**
**    cosys    FRAMETYPE    mount frame
**    eqx      double       mount equinox
**    wavel    double       wavelength
**    tar_p0   double[2]    [RA,Dec] or [Az,El]
**
** It is the net target that is passed to the FAST routine in this
** demonstration.  This assumes that the main application provides
** the offsets-from-base facility.  An alternative is to place the
** facility in the FAST routine itself.
**
*/

   cosys = FK5;                         /* Target is J2000 FK5... */
   eqx = 2000.0;                        /* ...or ICRS, more or less */
   wavel = 1e6;                         /* Radio refraction */
   tar_p0 [ 0 ] = 5.2359877559829890;   /* Right Ascension */
   tar_p0 [ 1 ] = -0.3316125578789226;  /* Declination */
   tar_dt [ 0 ] = 0.0;
   tar_dt [ 1 ] = 0.0;
   tar_t0 = 0.0;
   tar_ob [ 0 ] [ 0 ] = 0.0 * AS2R;
   tar_ob [ 0 ] [ 1 ] = 0.0 * AS2R;

/* Get the (approximate) current time. */
   (void) tcsTime ( &tai );

/* Calculate target position. */
   tcsTargup ( tai, tar_t0, tar_p0, tar_dt, tar_ob, tar_op0, tar_p );

/* Now run the MEDIUM routine to generate the new pointing model and SPMs. */
   (void) tcsMedium ( tai, MAXTRM, model, coeffv, nterml, ntermx, nterms,
                      coeffn, coform, mount, ae2nm, roll, pitch, jbp, aux,
                      cosys, eqx, wavel, cosys, eqx, wavel,
                      tar_p,
                      t0, st0, ttj, temp, press, humid, tlr, wavelr,
                      refa, refb, rfun, hm, tlat, diurab, amprms,
                      &ia, &ib, &np, &xt, &yt, &zt, ae2mt,
                      spm1, spm1_i, spm2, spm2_i,
                      spm1, spm1_i, spm2, spm2_i );

/* Report the target. */
   slaDr2tf ( 4, slaDranrm ( tar_p0[0] ), &s, i4 );
   printf ( "\nRA = %2.2i %2.2i %2.2i.%4.4i  ", i4[0], i4[1], i4[2], i4[3] );
   slaDr2af ( 3, tar_p0[1], &s, i4 );
   printf ( "Dec = %c%2.2i %2.2i %2.2i.%3.3i  <- test star\n",
                                             s, i4[0], i4[1], i4[2], i4[3] );
   slaDr2tf ( 4, slaDrange ( tar_ob[0][0] ), &s, i4 );
   printf ( "    %c%2.2i %2.2i %2.2i.%4.4i  ",
                                             s, i4[0], i4[1], i4[2], i4[3] );
   slaDr2af ( 3, tar_ob[0][1], &s, i4 );
   printf ( "      %c%2.2i %2.2i %2.2i.%3.3i  <- offset\n",
                                             s, i4[0], i4[1], i4[2], i4[3] );

/* Tell the FAST routine about the new target and SPMs. */
   tcsFast_dsa ( TARGET + TRANSFORM + MODEL, jbp, tai,
                 t0, st0,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 tar_t0, tar_op0, tar_dt,
                 s_unit, nsp, s_path, s_period, nsc,
                 s_epoch, jscan,
                 cosys, spm1, spm2,
                 &roll, &pitch );

/*
** From now on, the target and the various offsets from base can be
** changed at will.  Each time this happens appropriate steps must be
** taken to communicate the new information to the FAST routine.
**
** Whenever a completely new target is supplied, one that may involve
** a change of reference frame or a position in the sky outside the
** valid range of the current SPMs, the new target and new SPMs must
** be communicated to the FAST routine as an atomic unit.
*/

/*
** --------------------------------------------------------
** Run the FAST routine before repeating the call to MEDIUM
** --------------------------------------------------------
**
** The pointing corrections have, up to now, been calculated for a
** safe but arbitrary assumed antenna position.  As soon as the
** FAST routine runs, which it will do as a consequence of being
** invoked at some regular interval such as 100 ms, an accurate
** demanded position will be available.  The call to FAST below
** simulates this effect.  In reality, the pointing corrections
** will simply be slightly inaccurate for a few seconds as the
** system starts up.
**
*/

/* Read the clock */
   (void) tcsTime ( &tai );

/* Call FAST to obtain a reasonably accurate demand position. */
   tcsFast_dsa ( 0, jbp, tai,
                 t0, st0,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 tar_t0, tar_op0, tar_dt,
                 s_unit, nsp, s_path, s_period, nsc,
                 s_epoch, jscan,
                 cosys, spm1, spm2,
                 &roll, &pitch );

/* Calculate target position. */
   tcsTargup ( tai, tar_t0, tar_p0, tar_dt, tar_ob, tar_op0, tar_p );

/* Now run the MEDIUM routine to generate updated pointing coefficients. */
   (void) tcsMedium ( tai, MAXTRM, model, coeffv, nterml, ntermx, nterms,
                      coeffn, coform, mount, ae2nm, roll, pitch, jbp, aux,
                      cosys, eqx, wavel, cosys, eqx, wavel,
                      tar_p,
                      t0, st0, ttj, temp, press, humid, tlr, wavelr,
                      refa, refb, rfun, hm, tlat, diurab, amprms,
                      &ia, &ib, &np, &xt, &yt, &zt, ae2mt,
                      spm1, spm1_i, spm2, spm2_i,
                      spm1, spm1_i, spm2, spm2_i );

/* Finally tell the FAST routine about the updated pointing model and SPMs. */
   tcsFast_dsa ( TRANSFORM + MODEL, jbp, tai,
                 t0, st0,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 tar_t0, tar_op0, tar_dt,
                 s_unit, nsp, s_path, s_period, nsc,
                 s_epoch, jscan,
                 cosys, spm1, spm2,
                 &roll, &pitch );

/*
** --------------------------------
** Run the FAST routine a few times
** --------------------------------
**
** The FAST routine would normally be triggered by a timer interrupt,
** at a regular rate of 5-20 Hz.  This may happen in a different
** processor.  It is assumed here that the appropriate mechanisms are
** in place (a) to implement the above "update" calls to tcsFast_dsa
** and (b) to retrieve information from the mount controller as
** required.
**
*/

/* Read the clock. */
   (void) tcsTime ( &tai );

/* Simulate a few successive calls to FAST at 10Hz. */
   for ( i = -10; i < 3; i++ ) {
      t = tai + ( ( (double) i ) * 0.1 ) / 86400.0;

   /* Ask the FAST routine to calculate new demands. */
      tcsFast_dsa ( 0, jbp, t,
                    t0, st0,
                    ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                    tar_t0, tar_op0, tar_dt,
                    s_unit, nsp, s_path, s_period, nsc,
                    s_epoch, jscan,
                    cosys, spm1, spm2,
                    &roll, &pitch );

      if ( i >= 0 ) {
         printf ( "\ntimestamp       = %23.10f  MJD(TAI)\n", t );
         printf ( "Az demand       = %23.10f  degrees\n",
                                     slaDranrm ( PI - roll ) / D2R );
         printf ( "El demand       = %23.10f  degrees\n", pitch / D2R );
      }
   }

/* Functions of LAST for demonstrations. */
   st = st0 + ( t - t0 ) * STRPD;
   sst = sin ( st );
   cst = cos ( st );

/*
** ----------------------------------------------
** Demonstrate the sky-to-encoders transformation
** ----------------------------------------------
*/

   tcsVTenc ( tar_p[0], tar_p[1],
              spm1, cosys, sst, cst, spm2,
              OTA, 0.0, roll, pitch, 0.0, 0.0,
              ia, ib, np, xt, yt, zt, ga, gb, rnogo,
              &a1, &b1, &a2, &b2, &j );

/* In this demonstration we use only the first solution and ignore status. */
   a = a1;
   b = b1;

   printf ( "\nSky-to-encoders:\n" );

   switch ( mount ) {

   case EQUAT:
      printf ( "   HA demand    = %+23.10f  degrees\n", - a / D2R );
      printf ( "   Dec demand   = %+23.10f  degrees\n", b / D2R );
      break;

   case ALTAZ:
      printf ( "   Az demand    = %20.10f  degrees\n",
                                    slaDranrm ( PI - a ) / D2R );
      printf ( "   El demand    = %20.10f  degrees\n", b / D2R );
      break;

   default:
      printf ( "   Roll demand  = %20.10f  degrees\n", a / D2R );
      printf ( "   Pitch demand = %20.10f  degrees\n", b / D2R );

   }

/*
** ----------------------------------------------
** Demonstrate the encoders-to-sky transformation
** ----------------------------------------------
*/

   tcsVTsky ( a, b, OTA, 0.0, 0.0, 0.0,
              spm1_i, cosys, sst, cst, spm2_i,
              ia, ib, np, xt, yt, zt, ga, gb,
              &ra, &dec );

   printf ( "\nEncoders-to-sky:\n" );
   slaDr2tf ( 4, slaDranrm ( ra ), &s, i4 );
   printf ( "   RA = %2.2i %2.2i %2.2i.%4.4i  ", i4[0], i4[1], i4[2], i4[3] );
   slaDr2af ( 3, dec, &s, i4 );
   printf ( "   Dec = %c%2.2i %2.2i %2.2i.%3.3i\n",
                                              s, i4[0], i4[1], i4[2], i4[3] );

/*
** ---------------------------------------
** Demonstrate two cycles of line scanning
** ---------------------------------------
*/

/* Scan parameters. */
   s_unit = D2R;                 /* units are degrees */
   nsp = 2;                      /* the pattern is two points */
   s_period = 10.0;              /* each cycle lasts 10 sec */
   nsc = 2;                      /* two cycles */

/* Construct the scan pattern. */
   s_path[0][0] = 0.1f;          /* start 0.1 deg to the left */
   s_path[0][1] = 0.0f;
   s_path[1][0] = -0.1f;         /* then scan rightwards */
   s_path[1][1] = 0.0f;

/* Tell the FAST routine. */
   tcsFast_dsa ( SCANPARS, jbp, t,
                 t0, st0,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 tar_t0, tar_op0, tar_dt,
                 s_unit, nsp, s_path, s_period, nsc,   /* scan parameters */
                 s_epoch, jscan,
                 cosys, spm1, spm2,
                 &roll, &pitch );

/* Ask for a scan 5 sec hence. */
   s_epoch = tai + 5.0 / 86400.0;
   jscan = SCAN_ARMED;

/* Tell the FAST routine. */
   tcsFast_dsa ( SCANCTRL, jbp, t,
                 t0, st0,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 tar_t0, tar_op0, tar_dt,
                 s_unit, nsp, s_path, s_period, nsc,
                 s_epoch, jscan,                       /* scan control */
                 cosys, spm1, spm2,
                 &roll, &pitch );

/* Simulate a 30 sec span of calls to FAST at 10Hz. */
   printf ( "\n\n  t         "
            "Az           "
            "El            "
            "RA            "
            "Dec           "
            "R\n\n" );
   for ( i = -10; i <= 300; i++ ) {
      t = tai + ( ( (double) i ) * 0.1 ) / 86400.0;

   /* Ask the FAST routine to calculate new demands. */
      tcsFast_dsa ( 0, jbp, t,
                    t0, st0,
                    ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                    tar_t0, tar_op0, tar_dt,
                    s_unit, nsp, s_path, s_period, nsc,
                    s_epoch, jscan,
                    cosys, spm1, spm2,
                    &roll, &pitch );

   /* Report (at each new second only). */
      if ( i >= 0 && ! ( i % 10 ) ) {

      /* Relative time in seconds. */
         printf ( "%4.1f", ( t - tai ) * 86400.0 );

      /* Azimuth demand. */
         printf ( "%15.8f", slaDranrm ( PI - roll ) / D2R );

      /* Elevation demand. */
         printf ( "%13.8f", pitch / D2R );

      /* Functions of LAST. */
         st = st0 + ( t - t0 ) * STRPD;
         sst = sin ( st );
         cst = cos ( st );

      /* Calculate sky coordinates of antenna. */
         tcsVTsky ( roll, pitch, OTA, 0.0, 0.0, 0.0,
                    spm1_i, cosys, sst, cst, spm2_i,
                    ia, ib, np, xt, yt, zt, ga, gb,
                    &ra, &dec );

      /* Right ascension. */
         slaDr2tf ( 4, slaDranrm ( ra ), &s, i4 );
         printf ( "%4.2i %2.2i %2.2i.%4.4i",
                  i4[0], i4[1], i4[2], i4[3] );

      /* Declination. */
         slaDr2af ( 3, dec, &s, i4 );
         printf ( " %c%2.2i %2.2i %2.2i.%3.3i",
                  s, i4[0], i4[1], i4[2], i4[3] );

      /* Scan radial distance (neglecting differential tracking). */
         printf ( "%9.4f\n",
                  slaDsep ( ra, dec, tar_op0[0], tar_op0[1] ) / D2R );
      }
   }

/*
** ----------------------------------------
** Demonstrate indefinite circular scanning
** ----------------------------------------
*/

/* Scan parameters. */
   s_unit = D2R;                 /* units are degrees */
   nsp = NSPMAX;                 /* the pattern is NSPMAX points */
   s_period = 15.0;              /* each cycle lasts 15 sec */
   nsc = -1;                     /* indefinite */

/* Construct the scan pattern. */
   r = 0.1;
   for ( i = 0; i < nsp; i++ ) {
      t = PI2 * (double) i / (double) NSPMAX;
      s_path[i][0] = (float) ( r * cos ( t ) );
      s_path[i][1] = (float) ( r * sin ( t ) );
   }

/* Tell the FAST routine. */
   tcsFast_dsa ( SCANPARS, jbp, t,
                 t0, st0,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 tar_t0, tar_op0, tar_dt,
                 s_unit, nsp, s_path, s_period, nsc,   /* scan parameters */
                 s_epoch, jscan,
                 cosys, spm1, spm2,
                 &roll, &pitch );

/* Ask for a scan that begins a new cycle 5 sec hence. */
   s_epoch = tai + 5.0 / 86400.0;
   jscan = SCAN_ARMED;

/* Tell the FAST routine. */
   tcsFast_dsa ( SCANCTRL, jbp, t,
                 t0, st0,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 tar_t0, tar_op0, tar_dt,
                 s_unit, nsp, s_path, s_period, nsc,
                 s_epoch, jscan,                       /* scan control */
                 cosys, spm1, spm2,
                 &roll, &pitch );

/* Simulate a 30 sec span of calls to FAST at 10Hz. */
   printf ( "\n\n  t         "
            "Az           "
            "El            "
            "RA            "
            "Dec           "
            "R\n\n" );
   for ( i = -10; i <= 300; i++ ) {
      t = tai + ( ( (double) i ) * 0.1 ) / 86400.0;

   /* Ask the FAST routine to calculate new demands. */
      tcsFast_dsa ( 0, jbp, t,
                    t0, st0,
                    ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                    tar_t0, tar_op0, tar_dt,
                    s_unit, nsp, s_path, s_period, nsc,
                    s_epoch, jscan,
                    cosys, spm1, spm2,
                    &roll, &pitch );

   /* Report (at each new second only). */
      if ( i >= 0 && ! ( i % 10 ) ) {

      /* Relative time in seconds. */
         printf ( "%4.1f", ( t - tai ) * 86400.0 );

      /* Azimuth demand. */
         printf ( "%15.8f", slaDranrm ( PI - roll ) / D2R );

      /* Elevation demand. */
         printf ( "%13.8f", pitch / D2R );

      /* Functions of LAST. */
         st = st0 + ( t - t0 ) * STRPD;
         sst = sin ( st );
         cst = cos ( st );

      /* Calculate sky coordinates of antenna. */
         tcsVTsky ( roll, pitch, OTA, 0.0, 0.0, 0.0,
                    spm1_i, cosys, sst, cst, spm2_i,
                    ia, ib, np, xt, yt, zt, ga, gb,
                    &ra, &dec );

      /* Right ascension. */
         slaDr2tf ( 4, slaDranrm ( ra ), &s, i4 );
         printf ( "%4.2i %2.2i %2.2i.%4.4i",
                  i4[0], i4[1], i4[2], i4[3] );

      /* Declination. */
         slaDr2af ( 3, dec, &s, i4 );
         printf ( " %c%2.2i %2.2i %2.2i.%3.3i",
                  s, i4[0], i4[1], i4[2], i4[3] );

      /* Scan radial distance (neglecting differential tracking). */
         printf ( "%9.4f\n",
                  slaDsep ( ra, dec, tar_op0[0], tar_op0[1] ) / D2R );
      }
   }

/* Disable scanning. */
   jscan = SCAN_OFF;

/* Tell the FAST routine. */
   tcsFast_dsa ( SCANCTRL, jbp, t,
                 t0, st0,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 tar_t0, tar_op0, tar_dt,
                 s_unit, nsp, s_path, s_period, nsc,
                 s_epoch, jscan,                       /* scan control */
                 cosys, spm1, spm2,
                 &roll, &pitch );

/*
** ----------------------
** Demonstrate az/el mode
** ----------------------
*/


   printf ( "\nTopocentric az,el mode:\n\n" );

/* Specify a topocentric az/el. */
   cosys = AZEL_TOPO;                   /* Coordinate system */
   eqx = 0.0;                           /* Just for neatness */
   wavel = 1e6;                         /* Radio refraction */
   tar_p0 [ 0 ] = 120.0 * D2R;          /* Azimuth */
   tar_p0 [ 1 ] = 10.0 * D2R;           /* Elevation */
   tar_dt [ 0 ] = 0.0;
   tar_dt [ 1 ] = 0.0;
   tar_t0 = 0.0;
   tar_ob [ 0 ] [ 0 ] = 0.0 * AS2R;
   tar_ob [ 0 ] [ 1 ] = 0.0 * AS2R;

   printf ( "Target Az  = %15.10f  degrees\n",
                                   slaDranrm ( tar_p0[0] ) / D2R );
   printf ( "Target El  = %15.10f  degrees\n\n", tar_p0[1] / D2R );

/* Calculate target position. */
   tcsTargup ( tai, tar_t0, tar_p0, tar_dt, tar_ob, tar_op0, tar_p );

/* Run the MEDIUM routine to generate updated pointing coefficients. */
   (void) tcsMedium ( tai, MAXTRM, model, coeffv, nterml, ntermx, nterms,
                      coeffn, coform, mount, ae2nm, roll, pitch, jbp, aux,
                      cosys, eqx, wavel, cosys, eqx, wavel,
                      tar_p,
                      t0, st0, ttj, temp, press, humid, tlr, wavelr,
                      refa, refb, rfun, hm, tlat, diurab, amprms,
                      &ia, &ib, &np, &xt, &yt, &zt, ae2mt,
                      spm1, spm1_i, spm2, spm2_i,
                      spm1, spm1_i, spm2, spm2_i );

/* Tell the FAST routine about the updated target, pointing model and SPMs. */
   tcsFast_dsa ( TRANSFORM + MODEL + TARGET, jbp, tai,
                 t0, st0,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 tar_t0, tar_op0, tar_dt,
                 s_unit, nsp, s_path, s_period, nsc,
                 s_epoch, jscan,
                 cosys, spm1, spm2,
                 &roll, &pitch );

/* Run the FAST routine. */
   tcsFast_dsa ( 0, jbp, t,
                 t0, st0,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 tar_t0, tar_op0, tar_dt,
                 s_unit, nsp, s_path, s_period, nsc,
                 s_epoch, jscan,
                 cosys, spm1, spm2,
                 &roll, &pitch );

   printf ( "Az demand  = %15.10f  degrees\n",
                          slaDranrm ( PI - roll ) / D2R );
   printf ( "El demand  = %15.10f  degrees\n", pitch / D2R );

/*
** The DSA pointing control system demonstration terminates here.  An
** operational system would execute continuously, with tcsSlow being
** executed once every 10s or so, tcsMedium running every few seconds
** and also to conclude a change of target, and tcsFast_dsa running at
** maybe 10 Hz.
*/

   return 0;

}

/*------------------------------------------------------------------------*/

#include "tcs.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                      *
*  The main TCS_DSA routine, a single, multi-purpose function, starts  *
*  here.                                                               *
*                                                                      *
*  It is written on the assumption that it is called in a single       *
*  thread;  multiple, overlapping invocations must not occur.          *
*                                                                      *
*  The actions comprise (i) inserting new data into the internal       *
*  context and (ii) calculating the next set of mount pointing         *
*  demands.  Context updates, which can be carried out piecemeal       *
*  or wholesale, are usually the result of a request from the host     *
*  application, in order to supply new target coordinates or to        *
*  refresh the pointing transformation parameters for example.         *
*  Calculation of antenna mount demands, typically at 10 Hz, are       *
*  usually the result of timer activity.                               *
*                                                                      *
*  The code is designed to be usable in a computer or DSP local to the *
*  antenna, with the host application running in another computer.     *
*  It is up to the implementor to provide the required interprocessor  *
*  link software to transmit context changes as required.  It is also  *
*  up to the implementor to provide the servo software that realizes   *
*  the mount demands.                                                  *
*                                                                      *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void tcsFast_dsa ( int mode,
                   int isol,
                   double tai,

                   double T0,
                   double St0,

                   double Ia,
                   double Ib,
                   double Np,
                   double Xt,
                   double Yt,
                   double Zt,
                   double Ga,
                   double Gb,
                   double Rnogo,

                   double Tar_t0,
                   double Tar_p0[2],
                   double Tar_dt[2],

                   double S_unit,
                   int Nsp,
                   float S_path[NSPMAX][2],
                   double S_period,
                   int Nsc,

                   double S_epoch,
                   SCAN_STATE Jscan,

                   FRAMETYPE Cosys,
                   double Spm1[3][3],
                   double Spm2[3][3],

                   double *roll,
                   double *pitch )

/*
**  - - - - - - - - - - - -
**   t c s F a s t _ d s a
**  - - - - - - - - - - - -
**
**  The heart of the DSA control system.
**
**  Given (control):
**     mode              int        action(s) required (Note 1)
**     isol              int        TRUE selects "below pole" solution
**     tai               double     timestamp (TAI MJD = JD-2400000.5)
**
**  Given (context):
**
**   TIME group (Note 3)
**     T0                double     timestamp for LAST and TT
**     St0               double     LAST at time T0
**
**   MODEL group (Note 4)
**     Ia                double     roll zero-point
**     Ib                double     pitch zero-point
**     Np                double     mount axes nonperpendicularity
**     Xt                double     telescope vector, x-coordinate
**     Yt                double     telescope vector, y-coordinate
**     Zt                double     telescope vector, z-coordinate
**     Ga                double     guiding correction, collimation
**     Gb                double     guiding correction, pitch
**     Rnogo             double     mount pole avoidance radius
**
**   TARGET group (Note 5)
**     Tar_t0            double     target reference time
**     Tar_p0[2]         double     target coordinates at reference time
**     Tar_dt[2]         double     target differential rates
**
**   SCAN PARAMETERS group (Note 6)
**     S_unit            double     radians per [x,y] unit
**     Nsp               int        number of [x,y] offsets
**     S_path[NSPMAX][2] float      list of [x,y] offsets (in scan units)
**     S_period          double     time per cycle (sec)
**     Nsc               int        number of cycles (< 1 = indefinite)
**
**   SCAN CONTROL group (Note 7)
**     S_epoch           double     scan reference time (TAI MJD)
**     Jscan             SCAN_STATE scan status/command
**
**   TRANSFORM group (Notes 8)
**     Cosys             FRAMETYPE  frame for mount control
**     Spm1[3][3]        double     mount SPM #1
**     Spm2[3][3]        double     mount SPM #2
**
**  Returned (Notes 9-11):
**     roll              double*    mount roll (righthanded "south"-zero)
**     pitch             double*    mount pitch
**
**  Defined in tcs.h:
**     FRAMETYPE         enum       frame types
**     ROTLOC            enum       rotator locations
**
**  Defined in tcsmac.h:
**     PI                double     Pi
**     PI2               double     2Pi
**
**  Defined elsewhere:
**     NSPMAX            int        maximum number of scan [x,y] offsets
**     SCAN_STATE        enum       scan states
**
**  Called:  tcsTrack
**
**  Notes:
**
**   1 The mode argument defines which of the repertoire of actions are
**     to be performed during this invocation.  Each action has a bit to
**     flag that it is to be performed:
**
**        bit    decimal            action
**
**      0000000     0      calculate new mount coordinates
**      0000001     1      not used
**      0000010     2      update the sidereal time parameters
**      0000100     4      update the pointing model coefficients
**      0001000     8      update the transformation matrices
**      0010000    16      update the target position
**      0000001    32      update the scan parameters
**      1000000    64      control scanning
**
**     Bits above 1111111 (decimal 127) are ignored.
**
**     Examples:
**
**        mode              action
**
**          0       calculate new mount coordinates
**          2       store new ST parameters in the context
**          8       update the transformation
**         16       supply new RA,Dec
**         24       new target and transformation
**        127       update the whole context
**
**     The "calculate new coordinates" action is intended to be
**     invoked at a regular frequency of no less than 5 Hz, preferably
**     10 Hz and ideally 20 Hz.  The higher the frequency, the more
**     immediate the response to guiding and offsetting demands.
**
**     The tai argument is accessed only if mode = 0.
**
**   3 The time parameters enable fast computation of the Local Apparent
**     Sidereal Time and the Terrestrial Time by the pointing kernel.
**     parameters must be supplied by the host application.  Once every
**     five minutes is more than often enough.
**
**   4 The pointing coefficients will change slowly, as other pointing
**     terms introduce small adjustments to the basic ones.  An update
**     once every few seconds is frequent enough.
**
**   5 The target (where in the sky we want to look) will need to be
**     updated whenever a new object is selected, for example.  If the
**     new target is distant from the old one, or in a different frame,
**     the transformations and pointing model will also need updating.
**     It is important that the target and transformation updates be
**     done all in one call (mode=24) to ensure consistency.
**
**   6 The scan parameters define a trajectory and cycle time for a scan
**     manoeuvre.  The scan is implemented by offsetting the target
**     image in the focal plane;  neither the target position nor the
**     pointing model are affected.  The scan, which can last one cycle,
**     a specified number of cycles, or continue forever, is initiated
**     and controlled separately (next note).
**
**   7 Scanning is controlled by specifying a reference time and setting
**     a state flag.  The flag is itself changed by the scanning
**     activity, though this is not visible to the application.  The
**     different states are as follows:
**
**       SCAN_OFF       No scanning activity;  offsets zeroed.
**       SCAN_ARMED     Begin scanning when the start time is reached.
**       SCAN_ACTIVE    Scanning.
**       SCAN_PAUSE     Scanning halted at its current offset.
**
**     To start scanning at the reference time:  SCAN_ARMED.
**     To start scanning immediately:  SCAN_ACTIVE.
**     To freeze the scan:  SCAN_PAUSE.
**     To resume the scan:  SCAN_ACTIVE with zero-time moved on.
**     To rejoin the scan:  SCAN_ACTIVE with original zero-time.
**     To stop at end of current cycle:  send revised number of cycles.
**     To abort:  SCAN_OFF.
**
**     The reference time, which must always be supplied, defines the
**     phase of the scan under all circumstances.
**
**   8 The transformations will be updated every few seconds by the
**     "medium" process running in the host, and summarize the pointing
**     across the patch of sky at which the antenna is being aimed.
**     Included in these transformations are any pointing-model
**     adjustments which affect the roll axis misalignment,
**     complementing the other model terms (see the previous note).
**
**   9 The mount demands are timetagged and should be regarded as
**     samples of a trajectory rather than simply the position for
**     "now".  The servo controller software would use two or more such
**     samples to interpolate or extrapolate the required position for
**     the current time.
**
**     Regarding the servo controller software, note the following:
**
**     * Although all components of the system need reasonably accurate
**       time, only the servo controller itself needs the exact time.
**
**     * It is important that the earliest of the samples being used
**       for the interpolation lies *before* the time for which the
**       trajectory calculation is being carried out.  If this condition
**       is not met, so that both (or all) of the samples lie in the
**       future, any step in the demand will for a while be extrapolated
**       backwards, producing a spurious initial jump in the wrong
**       direction.  Measures must be taken avoid this condition.  The
**       most complete method is to retain all of the samples, no matter
**       how far into the future they extend, until they are no longer
**       required.  A cruder approach is to continue to use the same
**       "earliest" sample until a replacement arrives that predates the
**       current time, simply discarding any potential replacements that
**       are for later than the current time.
**
**  10 The mount "roll" coordinate is pi-Az for the present, altazimuth
**     mount only, case.  It is in the range +/-pi.  Where the
**     mechanical range is greater than 360 deg, for example where there
**     is a cable wrap, selection of the correct range must take place
**     outside the present routine.
**
**     ***  It is the host application's responsibility not to  ***
**     ***  enable the calculation of mount coordinates until   ***
**     ***  all of the context has been initialized.            ***
**
**  Latest revision:   24 November 2006
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

#define SPIN 6.30038809892         /* HA change per SI day */

{

/*--------- The context for the fast process -------------------------------*/

/* TIME: sidereal and dynamical time */
   static double t0;               /* timestamp for LAST */
   static double st0;              /* LAST at time t0 */

/* MODEL: pointing model */
   static double ia;               /* roll zero-point */
   static double ib;               /* pitch zero-point */
   static double np;               /* mount axes nonperpendicularity */
   static double xt;               /* telescope vector, x-coordinate */
   static double yt;               /* telescope vector, y-coordinate */
   static double zt;               /* telescope vector, z-coordinate */
   static double ga;               /* guiding correction, collimation */
   static double gb;               /* guiding correction, pitch */
   static double rnogo;            /* mount pole avoidance radius */

/* TRANSFORM: transformation matrices etc. */
   static FRAMETYPE cosys;         /* frame for mount control */
   static double spm1[3][3];       /* mount SPM #1 */
   static double spm2[3][3];       /* mount SPM #2 */

/* TARGET: what place in the sky is to be imaged */
   static double tar_t0;           /* target reference time (TAI MJD) */
   static double tar_p0[2];        /* target coordinates at reference time */
   static double tar_dt[2];        /* target differential rates */

/* SCAN PARAMETERS: how the image is to move in the focal plane */
   static int nsp;                 /* number of [x,y] offsets */
   static float s_path[NSPMAX][2]; /* list of [x,y] offsets (natural units) */
   static double s_period;         /* time per cycle (days) */
   static int nsc;                 /* number of cycles (< 1 = indefinite) */
   static double dnsp;             /* nsp as a double */
   static double s_segment;        /* time per path step */
   static double s_duration;       /* total duration (days) */

/* SCAN CONTROL: the state of any scanning manoeuvre */
   static double s_epoch;          /* reference time (TAI MJD) */
   static SCAN_STATE jscan;        /* state flag */

/* LATEST DEMANDS and their derivatives */
   static double tlast = 0.0;      /* timestamp */
   static int islast = 0;          /* above/below pole */
   static double adp = 0.0;        /* roll demand */
   static double adv = 0.0;        /* derivative of adp */
   static double bdp = 0.0;        /* pitch demand */
   static double bdv = 0.0;        /* derivative of bdp */

/*--------------------------------------------------------------------------*/

/* Extrapolated demands */
   double adpx;                    /* predicted roll */
   double bdpx;                    /* predicted pitch */

/* Target vectors */
   double tar[2];                  /* spherical coordinates (final) */
   double xa, ya, za;              /* AIM vector */

   int i, j;
   double dt, st, sst, cst, dtlast, dtdt, sdt, p, f, xr, yr,
          ad1, bd1, ad2, bd2, ad, bd;



/*
**  --------------
**  UPDATE CONTEXT
**  --------------
*/

   if ( mode & 2 ) {

   /* Update TIME context. */

      t0 = T0;
      st0 = St0;
   }

   if ( mode & 4 ) {

   /* Update MODEL context. */

      ia = Ia;
      ib = Ib;
      np = Np;
      xt = Xt;
      yt = Yt;
      zt = Zt;
      ga = Ga;
      gb = Gb;
      rnogo = Rnogo;
   }

   if ( mode & 8 ) {

   /* Update TARGET context. */

      tar_t0 = Tar_t0;
      for ( i = 0; i < 2; i++ ) {
         tar_p0[i] = Tar_p0[i];
      }
      for ( i = 0; i < 2; i++ ) {
         tar_dt[i] = Tar_dt[i];
      }
   }

   if ( mode & 16 ) {

   /* Update and develop SCAN PARAMETERS context. */
      nsp = Nsp <= NSPMAX ? Nsp : NSPMAX;
      for ( i = 0; i < nsp; i++ ) {
         for ( j = 0; j < 2; j++ ) {
            s_path[i][j] = S_path[i][j] * S_unit;
         }
      }
      s_period = S_period / 86400.0;
      nsc = Nsc;
      dnsp = (double) nsp;
      s_duration = (double) nsc * s_period;
      if ( s_period <= 0.0 ) nsp = 0;
      if ( nsp > 0 )
         s_segment = s_period / (double) nsp;
   }

   if ( mode & 32 ) {

   /* Update SCAN CONTROL context. */
      s_epoch = S_epoch;
      jscan = nsp > 0 ? Jscan : SCAN_OFF;
   }

   if ( mode & 64 ) {

   /* Update TRANSFORM context. */

      cosys = Cosys;
      for ( j = 0; j < 3; j++ ) {
         for ( i = 0; i < 3; i++ ) {
            spm1[j][i] = Spm1[j][i];
         }
      }
      for ( j = 0; j < 3; j++ ) {
         for ( i = 0; i < 3; i++ ) {
            spm2[j][i] = Spm2[j][i];
         }
      }
   }

/*
**  -------------------
**  THE POINTING KERNEL
**  -------------------
*/

   if ( ! ( mode & 63 ) ) {

   /*
   ** ----
   ** TIME
   ** ----
   */

   /* Time relative to reference time (days). */
      dt = tai - t0;

   /* Local Apparent Sidereal Time (radians), and functions. */
      st = st0 + dt * SPIN;
      sst = sin ( st );
      cst = cos ( st );

   /*
   ** --------------
   ** EXTRAPOLATIONS
   ** --------------
   */

   /* Time since previous iteration (days). */
      dtlast = tai - tlast;

   /* Extrapolated roll,pitch position demands next time. */
      adpx = adp + dtlast * adv;
      bdpx = bdp + dtlast * bdv;

   /* Differential tracking. */
      dtdt = tai - tar_t0;
      for ( i = 0; i < 2; i++ ) {
         tar[i] = tar_p0[i] + dtdt * tar_dt[i];
      }

   /*
   ** --------
   ** SCANNING
   ** --------
   */

   /* If required, time since scan epoch. */
      if ( ! ( jscan == SCAN_OFF ||
               jscan == SCAN_PAUSE ) ) sdt = tai - s_epoch;

   /* Revise the scan status according to events. */
      switch ( jscan ) {

      case SCAN_ARMED:
         if ( tai >= s_epoch || nsc < 1 ) jscan = SCAN_ACTIVE;

      case SCAN_ACTIVE:
         if ( sdt >= s_duration && nsc > 0 ) jscan = SCAN_OFF;

      default:
         break;

      }

   /* On the basis of the revised status, decide what offsets to demand. */
      switch ( jscan ) {

      case SCAN_PAUSE:
         break;

      case SCAN_OFF:
      case SCAN_ARMED:
         xr = 0.0;
         yr = 0.0;
         break;

      default:

      /* Scan phase, in segments with respect to s_path[0][0]. */
         if ( ( p = fmod ( sdt / s_segment, dnsp ) ) < 0.0 ) p += dnsp;

      /* Indices to previous and next [x,y]s. */
         i = (int) p;
         j = ( i + 1 ) % nsp;

      /* How far through the current segment we are. */
         f = p - (double) i;

      /* Offsets at start of current segment. */
         xr = (double) s_path[i][0];
         yr = (double) s_path[i][1];

      /* Add change since start of current segment. */
         xr += f * ( (double) s_path[j][0] - xr );
         yr += f * ( (double) s_path[j][1] - yr );

      }

   /*
   **
   ** -------------
   ** MOUNT DEMANDS
   ** -------------
   **
   */

      tcsTrack ( tar[0], tar[1],
                 spm1, cosys, sst, cst, spm2,
                 OTA, 0.0, adpx, bdpx, xr, yr,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 &xa, &ya, &za,
                 &ad1, &bd1, &ad2, &bd2, &j );

   /* (In this implementation we ignore status.) */

   /* Select the appropriate solution. */
      ad = isol ? ad2 : ad1;
      bd = isol ? bd2 : bd1;

   /*
   ** -------
   ** RESULTS
   ** -------
   */

   /* Save the latest velocities (if credible). */
      if ( dtlast != 0.0 && isol == islast ) {
         adv = ( ad - adp ) / dtlast;
         if ( fabs ( adv ) >= PI ) adv -= adv < 0.0 ? PI2 : - PI2;
         bdv = ( bd - bdp ) / dtlast;
      }

   /* Save the new timestamp and solution choice. */
      tlast = tai;
      islast = isol;

   /* Save and return the latest demands. */
      *roll = adp = ad;
      *pitch = bdp = bd;

   }
}

/*------------------------------------------------------------------------*/
