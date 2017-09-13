#include <stdio.h>
#include <slalib.h>
#include "tcs.h"
#include "tcsmac.h"

void tcsFast_e ( int, int, double, double, double, double, double, double,
                 double, double, double, double, double, double, double,
                 double[2], double[2], FRAMETYPE, double[3][3],
                 double[3][3], double*, double* );

int main ( )

/*
**  - - - - - - - -
**   T C S _ E Q U
**  - - - - - - - -
**
**  Demonstration of TCSpk pointing kernel for the simple case of an
**  equatorial mount with no instrument rotator, supporting tracking in
**  J2000/FK5/ICRS RA/Dec only and with a single pointing-origin.  The
**  net pointing corrections are logged as well as HA/Dec demands.
**
**  The fundamental principle upon which the TCSpk design, and this
**  demonstration, rests, is that there are two threads with a shared
**  context.  One thread, at lower priority, maintains the context,
**  while the other, at higher priority or operating in a separate
**  processor, uses it to generate timestamped positions for the polar
**  and declination axes.  The low-priority thread is triggered by a
**  combination of (i) timer interrupts (typically every few seconds)
**  and (ii) notifications from the user-interface that something has
**  changed.  The high-priority thread is triggered at, say, 20 Hz by
**  timer interrupts.  In the present implementation, the high-priority
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
**                                tcsSlow and tcsMedium updates.
**                                Establish the means of reading the
**                                achieved rotator angle and
**                                velocity (unless this is all done in
**                                the high-priority thread).  Call
**                                tcsFast_e to cause it to copy the
**                                whole of the context.
**
**   Every 60s (or so)            Call tcsSlow.
**
**   Every 5s (or so)             Call tcsMedium, then call tcsFast_e
**                                to cause it to copy the whole
**                                context.
**
**   User supplies a new          Obtain the new information and then
**   target.                      call tcsTargup to calculate the
**                                current net position.  Call tcsMedium
**                                to update the transformation to
**                                match the new position, and then call
**                                tcsFast_e to cause it to copy the
**                                context items that have changed.  It
**                                is usually appropriate to zero the
**                                guiding corrections (ga,gb) at this
**                                point.
**
**   User updates the target      Obtain the new information and then
**   offsets from base or         call tcsFast_e to cause it to copy the
**   differential tracking        context items that have changed.  A
**   rates.                       refinement would be to test whether
**                                the target position had changed
**                                significantly (more than a few
**                                arcminutes) and, if so, to call
**                                tcsMedium before the call to tcsFast_e.
**
**   Guiding activity occurs.     Call tcsFast_e to cause it to copy the
**                                updated ga and gb values.
**
**   Every 50ms (or so).          Trigger tcsFast_e to cause it to
**                                calculate new mount HA and Dec
**                                demands.  A good time to choose is
**                                that of the next 20Hz interrupt.
**
** It is a good plan to combine the slow and medium processing rather
** than having separate scheduling arrangements.  On most occasions,
** tcsMedium alone can be called (followed by tcsFast_e), but once every
** so many invocations the call to tcsMedium can be preceded with a call
** to tcsSlow.
**
** -----------------
** DATA REQUIREMENTS
** -----------------
**
** Here is a summary of the information required to drive the TCS (in
** its present simplified form: equatorial mount, no rotator, no
** pointing-origin support).
**
**   INITIALIZATION
**
**   . Site longitude, latitude and height above sea level.
**
**       Inaccurate site coordinates will show up as spurious
**       ME and MA pointing coefficients.  If grossly wrong, the
**       refraction predictions will be unreliable.  Height makes
**       little difference (but air pressure does - see below).
**
**   . Telescope focal length.
**
**       If the TCS does not support the pointing-origin feature,
**       as is the case in this simple demonstration, the focal
**       length can be set to any sensible value (say 1.0).
**
**   . UT1-UTC.
**
**       Zero will do on equatorial telescopes that do not
**       have absolute encoding in RA.  The omission will be
**       canceled out at sync time.
**
**   . TAI-UTC.
**
**       Zero will do on equatorial telescopes that do not
**       have absolute encoding in RA.  The omission will be
**       canceled out at sync time, except for second-order
**       effects.
**
**   . TT-TAI.
**
**       Always 32.184s.
**
**   . Polar motion.
**
**       Zero will do on all but the most accurate telescopes.
**
**   . Refraction data.
**
**       Temperature, pressure and relative humidity are all
**       required, to whatever accuracy they are available.
**       Pressure is the most critical one, and high-accuracy
**       telescopes need it to 1 mB.  A fixed value for the
**       tropospheric lapse rate of 0.0065 degK/m is always
**       acceptable.  For radio applications high-accuracy
**       temperature and humidity are also needed.  Finally,
**       for optical/IR applications, a reference wavelength
**       needs to be chosen, for example 0.5 micrometers.
**
**   . Initial mount coordinates.
**
**       Some legal values are needed to start the system.  They
**       do not have to reflect the actual attitude.
**
**   . Frames.
**
**       A reference frame for controlling the telescope must be
**       specified.  FK5 is the sensible default.  Along with each
**       frame ID, an equinox is needed:  2000.0 is the obvious
**       choice.  A wavelength has to be chosen as well, perhaps
**       0.55 micrometers for visual use.
**
**   . Pointing model.
**
**       A pointing model is required.  It can be set up in two
**       different ways, either by reading the file that the TPOINT
**       command OUTMOD writes or by using calls to construct the
**       model term by term.  In this demonstration the OUTMOD
**       method is used.  It is possible to change the coefficient
**       values while running (or even the form of the model);  the
**       new corrections will take effect the next time the MEDIUM
**       process is run.
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
**       changes will take effect when the SLOW process is next
**       run.  On small telescopes of modest accuracy, though it
**       is worth getting a pressure reading it is unlikely to
**       need changing during the night.  If a pressure reading
**       is unavailable, it can be estimated from the observatory
**       hight above sea level (details on request).
**
**   FIELD ORIENTATION
**
**   This entire feature is omitted here because there is no
**   rotator.  All the angles involved (IAA, IPA, RMA) are set to
**   zero and then left alone.
**
**   POINTING ORIGIN
**
**   This demonstration omits the entire pointing-origin feature,
**   though it could be useful if both a viewing eyepiece and a
**   CCD are used - the star can be slewed into the eyepiece,
**   centered, and then sent to the CCD center simply by changing
**   the x,y.  The feature has been disabled here by setting the
**   base x,y and all the offsets to zero.
**
**   FRAMES AND TARGET
**
**   TCSpk supports selectable and individual coordinate systems
**   for controlling the mount and the instrument rotator.  The
**   present minimal implementation is a fixed frame of FK5/2000
**   (effectively the same thing as Hipparcos/ICRS) for the
**   mount.  The rotator is absent.
**
**   The information needed to specify a target is as follows:
**
**   . Mount frame (and equinox if needed).
**
**        In this simple demonstration fixed at FK5/2000.  For
**        tracking planets, geocentric apparent place may be a
**        useful enhancement, depending on how the ephemeris
**        data are being calculated.
**
**   . Color.
**
**        This allows atmospheric dispersion to be corrected.
**        In this simple demonstration it is fixed at 5500 A.
**
**   . Target coordinates.
**
**        The target RA,Dec (or Az,El) can be changed at any
**        time, on their own, causing the telescope to move
**        to the new coordinates.  Various other actions may
**        be required at the same time, for example resetting
**        the offsets from base, reverting to the rotator-
**        axis pointing-origin, resetting the guiding
**        corrections and so on.  It is up to the TCS designer
**        to decide.
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
**  TCSpk is based on a concept called the "virtual telescope".
**  This is a set of transformations that link a place in the
**  sky, called the "target", with a place in the focal plane,
**  called the "pointing origin", and with a mechanical pointing
**  direction for the telescope.  Complicated details such as
**  pointing corrections are hidden inside the virtual-telescope
**  routines, so that users (for example an instrument wishing to
**  offset the image in the focal plane) can do so simply by
**  adjusting the star or image coordinates.  A TCS always supports
**  at least one virtual telescope, that for the telescope mount
**  itself.  However, there may also be guiders, tip/tilt
**  subreflectors, choppers present, and these can be implemented
**  as separate virtual telescopes, albeit ones which are forced
**  to share the one mount position (because there is only one
**  mount).
**
**  In the case of the mount virtual telescope, tracking demands are
**  obtained by transforming the target position through a series of
**  intermediate states into encoder coordinates.  The transformations
**  require knowledge of site location, time, weather, pointing errors
**  and the orientation of the instrument rotator.  The following sets
**  of coordinates are involved, in this and any other virtual
**  telescopes that the TCS is using:
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
**                     contains the telescope, as defined by the rotator
**                     axis, and the "pitch" axis of the mount.
**
**    TELESCOPE        In the same coordinate frame as the boresight
**                     vector, the direction in which the telescope,
**                     as defined by the rotator axis, is pointing.
**                     This vector is [1,0,0], if the collimation error
**                     is zero.  Non-zero collimation error will affect
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
#include "tcsctx.h"

   int i, i4[4], j;
   char s;
   double tai, ra, dec, t, st, sst, cst, a1, b1, a2, b2, a, b,
          spm1_z[3][3], spm1_z_i[3][3], spm2_z[3][3], spm2_z_i[3][3],
          roll0, pitch0, a_z, b_z, xim, yim;


/* References to unused context variables to avoid compiler warnings. */
   rotl=OTA; r_cosys=APPT; r_eqx=0.0; r_wavel=m_wavel;
   npo=0; m_por_p0[npo][0]=0.0; m_por_ob[npo][0][0]=0.0; m_por_p[0]=0.0;
   sia=0.0; cia=0.0; pai=0.0; jf=0;
   rmat=0.0; rma=0.0; rmav=0.0; rota=0.0;

/*
** --------------
** Initialization
** --------------
**
** An operational TCS needs to do all of the following before the
** system enters its real-time mode.
**
** n.b. C's default initialization to zero is assumed.
**
*/

/* No special refraction routine. */
   rfun = NULL;

/* Site and telescope. */
   tlongm = -105.2166667*D2R;
   tlatm = 39.75000000*D2R;
   hm = 1676.0;
   fl = 5500.0;
   rnogo = 0.25*D2R;

/* Time. */
   delut = 0.746/86400.0;
   delat = 29.0/86400.0;
   ttmtai = 32.184/86400.0;
   xpmr = 0.0;             /* Polar motion is omitted from */
   ypmr = 0.0;             /* this simple demonstration.   */

/* Met. */
   temp = 275.0;
   press = 795.0;
   humid = 0.6;
   tlr = 0.0065;
   wavelr = 0.55;

/* Mount type. */
   mount = EQUAT;          /* This demonstration is for equatorial only. */

/* Mount above/below pole state. */
   jbp = 0;

/* Initial mount [roll,pitch] (arbitrary). */
   roll = 0.0;
   pitch = tlatm;

/* Tracking frame (fixed in this simple demonstration). */
   m_cosys = FK5;
   m_eqx = 2000.0;
   m_wavel = 0.55;

/* Initialize the pointing model from a TPOINT file. */
   if ( tcsIntpm ( "specimen.mod", MAXTRM, NTROOM, model,
                   &nterml, &ntermx, &nterms,
                   coeffn, coform, coeffv ) ) return -1;

/* Reset the guiding adjustments. */
   ga = 0.0*AS2R;
   gb = 0.0*AS2R;

/* Secondary initialization. */
   if ( tcsInit2 ( tlongm, tlatm, xpmr, ypmr, hm,
                   EQUAT, 0.0, 0.0, 0.0, ae2nm,
                   &tlong, &tlat, &uau, &vau, &ukm, &vkm, &diurab ) ) {
      printf ( "\n"
               "Secondary initialization has failed.\n" );
      return -1;
   }

/*
** ------------------------------------------------
** Run the SLOW process for the first of many times
** ------------------------------------------------
**
** From now on, the SLOW process must be run from time to time
** (e.g. once a minute) to update the things that are slowly changing
** and target-independent.  Because the SLOW process is comparatively
** CPU-intensive, most TCS implementations will choose to run it in a
** different thread and at a lower priority than the FAST process (or
** even in a different processor).  However, it can and should be run
** in the same thread as the MEDIUM process (see later), which will
** ensure that the context never becomes internally inconsistent.
**
*/

/* Get the (approximate) current time. */
   (void) tcsTime ( &tai );

/* Perform the slow update for that time. */
   tcsSlow ( tai, delut, delat, ttmtai,
             temp, press, humid, wavelr, tlong,
             &t0, &st0, &tt0, &ttj, amprms, &refa, &refb );

/*
** --------------------------------------------------
** Run the MEDIUM process for the first of many times
** --------------------------------------------------
**
** From now on, the MEDIUM process must be run from time to time
** (e.g. every 5 seconds) in the background.  It updates the pointing
** model and also recalculates the "Sky-Patch Matrices".  The SPMs are
** 3x3 matrices which summarize the astrometric transformation for the
** current location in the sky, enabling rapid and concise
** transformations within the high-frequency part of the pointing
** algorithm.  The MEDIUM process must also be run immediately as part
** of setting up a new target (see later), in such a way that it is
** impossible for the FAST process ever to see inconsistent target and
** SPMs.
**
*/

/* Get the (approximate) current time. */
   (void) tcsTime ( &tai );

/* Perform the medium update for that time. */
   (void) tcsMedium ( tai, MAXTRM, model, coeffv, nterml, ntermx, nterms,
                      coeffn, coform, EQUAT, ae2nm, roll, pitch, jbp, aux,
                      m_cosys, m_eqx, m_wavel, m_cosys, m_eqx, m_wavel,
                      m_tar_p,
                      t0, st0, ttj, temp, press, humid, tlr, wavelr,
                      refa, refb, rfun, hm, tlat, diurab, amprms,
                      &ia, &ib, &np, &xt, &yt, &zt, ae2mt,
                      m_spm1, m_spm1_i, m_spm2, m_spm2_i,
                      r_spm1, r_spm1_i, r_spm2, r_spm2_i );

/* Tell the FAST process about everything initialized so far. */
   tcsFast_e ( ALL, jbp, tai,
               t0, st0,
               ia, ib, np, xt, yt, zt, ga, gb, rnogo,
               m_tar_t0, m_tar_op0, m_tar_dt,
               m_cosys, m_spm1, m_spm2,
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
**    m_cosys    FRAMETYPE    mount frame
**    m_eqx      double       mount equinox
**    m_wavel    double       wavelength
**    m_tar_p0   double[2]    [RA,Dec] or [Az,El]
**    m_tar_dt   double[2]    differential rates
**    m_tar_t0   double       reference time
**    m_tar_ob   double[3][2] offsets from base
**
*/

   m_tar_p0 [ 0 ] = 0.3654719453676126;
   m_tar_p0 [ 1 ] = 0.3316125578789226;
   m_tar_dt [ 0 ] = 0.0;
   m_tar_dt [ 1 ] = 0.0;
   m_tar_t0 = 0.0;
   m_tar_ob [ 0 ] [ 0 ] = 15.0 * AS2R;
   m_tar_ob [ 0 ] [ 1 ] = 60.0 * AS2R;

/* Get the (approximate) current time. */
   (void) tcsTime ( &tai );

/* Calculate target position. */
   tcsTargup ( tai, m_tar_t0, m_tar_p0, m_tar_dt, m_tar_ob,
               m_tar_op0, m_tar_p );

/* Now run the MEDIUM process to generate the new pointing model and SPMs. */
   (void) tcsMedium ( tai, MAXTRM, model, coeffv, nterml, ntermx, nterms,
                      coeffn, coform, EQUAT, ae2nm, roll, pitch, jbp, aux,
                      m_cosys, m_eqx, m_wavel, m_cosys, m_eqx, m_wavel,
                      m_tar_p,
                      t0, st0, ttj, temp, press, humid, tlr, wavelr,
                      refa, refb, rfun, hm, tlat, diurab, amprms,
                      &ia, &ib, &np, &xt, &yt, &zt, ae2mt,
                      m_spm1, m_spm1_i, m_spm2, m_spm2_i,
                      r_spm1, r_spm1_i, r_spm2, r_spm2_i );

/* Report the target. */
   slaDr2tf ( 4, slaDranrm ( m_tar_p0[0] ), &s, i4 );
   printf ( "\n"
            "RA = %2.2i %2.2i %2.2i.%4.4i  ", i4[0], i4[1], i4[2], i4[3] );
   slaDr2af ( 3, m_tar_p0[1], &s, i4 );
   printf ( "Dec = %c%2.2i %2.2i %2.2i.%3.3i  <- test star\n",
                                             s, i4[0], i4[1], i4[2], i4[3] );
   slaDr2tf ( 4, slaDrange ( m_tar_ob[0][0] ), &s, i4 );
   printf ( "    %c%2.2i %2.2i %2.2i.%4.4i  ",
                                             s, i4[0], i4[1], i4[2], i4[3] );
   slaDr2af ( 3, m_tar_ob[0][1], &s, i4 );
   printf ( "      %c%2.2i %2.2i %2.2i.%3.3i  <- offset\n",
                                             s, i4[0], i4[1], i4[2], i4[3] );

/* Tell the FAST process about the new target and SPMs. */
   tcsFast_e ( TARGET + TRANSFORM + MODEL, jbp, tai,
               t0, st0,
               ia, ib, np, xt, yt, zt, ga, gb, rnogo,
               m_tar_t0, m_tar_op0, m_tar_dt,
               m_cosys, m_spm1, m_spm2,
               &roll, &pitch );

/*
** From now on, the target offsets from base can be changed at will,
** to achieve offsetting and scanning effects.  Each time this happens,
** appropriate steps must be taken to communicate the new information to
** the FAST process.
**
** Whenever a completely new target is supplied, one that may involve
** a position in the sky outside the valid range of the current SPMs, the
** new target and new SPMs must be communicated to the FAST process as an
** atomic unit.
*/

/*
** --------------------------------------------------------
** Run the FAST process before repeating the call to MEDIUM
** --------------------------------------------------------
**
** The pointing corrections have, up to now, been calculated for a
** safe but arbitrary assumed telescope position.  As soon as the
** FAST process runs, which it will do as a consequence of being
** invoked at some regular interval such as 50 ms, an accurate
** demanded position will be available.  The call to FAST below
** simulates this effect.  In reality, the pointing corrections
** will simply be slightly inaccurate for a few seconds as the
** system starts up.
**
*/

/* Read the clock */
   (void) tcsTime ( &tai );

/* Call FAST to obtain a reasonably accurate demand position. */
   tcsFast_e ( 0, jbp, tai,
               t0, st0,
               ia, ib, np, xt, yt, zt, ga, gb, rnogo,
               m_tar_t0, m_tar_op0, m_tar_dt,
               m_cosys, m_spm1, m_spm2,
               &roll, &pitch );

/* Calculate target position. */
   tcsTargup ( tai, m_tar_t0, m_tar_p0, m_tar_dt, m_tar_ob,
               m_tar_op0, m_tar_p );

/* Now run the MEDIUM process to generate updated pointing coefficients. */
   (void) tcsMedium ( tai, MAXTRM, model, coeffv, nterml, ntermx, nterms,
                      coeffn, coform, EQUAT, ae2nm, roll, pitch, jbp, aux,
                      m_cosys, m_eqx, m_wavel, m_cosys, m_eqx, m_wavel,
                      m_tar_p,
                      t0, st0, ttj, temp, press, humid, tlr, wavelr,
                      refa, refb, rfun, hm, tlat, diurab, amprms,
                      &ia, &ib, &np, &xt, &yt, &zt, ae2mt,
                      m_spm1, m_spm1_i, m_spm2, m_spm2_i,
                      r_spm1, r_spm1_i, r_spm2, r_spm2_i );

/* Finally tell the FAST process about the updated pointing model and SPMs. */
   tcsFast_e ( TRANSFORM + MODEL, jbp, tai,
               t0, st0,
               ia, ib, np, xt, yt, zt, ga, gb, rnogo,
               m_tar_t0, m_tar_op0, m_tar_dt,
               m_cosys, m_spm1, m_spm2,
               &roll, &pitch );

/*
** ------------------------------------------------------------
** Run the demonstration twice, primary then secondary solution
** ------------------------------------------------------------
*/

   for ( jbp = 0; jbp < 2; jbp++ ) {

      printf ( "\n%sARY SOLUTION:\n", jbp ? "SECOND" : "PRIM" );

   /*
   ** --------------------------------
   ** Run the FAST process a few times
   ** --------------------------------
   **
   ** The FAST process would normally be triggered by a timer interrupt,
   ** at a regular rate of 5-20 Hz.  This may happen in a different
   ** processor.  It is assumed here that the appropriate mechanisms are
   ** in place (a) to implement the above "update" calls to tcsFast_e and
   ** (b) to retrieve information from the mount controller as required.
   **
   */

   /* Read the clock */
      (void) tcsTime ( &tai );

   /* Simulate a few successive calls to FAST at 20Hz. */
      for ( i = -20; i < 3; i++ ) {
         t = tai + ( ( (double) i ) * 0.05 ) / 86400.0;

      /* Ask the FAST process to calculate new demands. */
         tcsFast_e ( 0, jbp, t,
                     t0, st0,
                     ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                     m_tar_t0, m_tar_op0, m_tar_dt,
                     m_cosys, m_spm1, m_spm2,
                     &roll, &pitch );

      /* Report. */
         if ( i >= 0 ) {
            printf ( "\n"
                     "timestamp       = %23.10f  MJD(TAI)\n", t );
            printf ( "HA demand       = %+23.10f  degrees\n",
                                                            - roll / D2R );
            printf ( "Dec demand      = %+23.10f  degrees\n",
                                                             pitch / D2R );
         /* Save roll and pitch for rate calculation. */
            if ( i == 0 ) {
               roll0 = roll;
               pitch0 = pitch;
            } else if ( i == 2 ) {

            /* If last time through, report rates. */
               printf ( "\n"
                        "HA drift        =%+16.3f arcsec per sec\n",
                                                    (roll0-roll)*600.0/AS2R
                                                   -900.0/1.002737909350795 );
               printf ( "Dec drift       =%+16.3f arcsec per sec\n",
                                                  (pitch-pitch0)*600.0/AS2R );
            }
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

      tcsVTenc ( m_tar_p[0], m_tar_p[1],
                 m_spm1, m_cosys, sst, cst, m_spm2,
                 OTA, 0.0, 0.0, 0.0, 0.0, 0.0,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 &a1, &b1, &a2, &b2, &j );

   /* ("No solutions" status ignored.) */
      a = jbp ? a2 : a1;
      b = jbp ? b2 : b1;

      printf ( "\n"
               "Sky-to-encoders:\n" );

      printf ( "   HA demand    = %+23.10f  degrees\n", - a / D2R );
      printf ( "   Dec demand   = %+23.10f  degrees\n", b / D2R );

   /*
   ** -----------------------------------
   ** Report the net pointing corrections
   ** -----------------------------------
   */

   /* Generate SPMs for perfect mount and no refraction. */
      tcsTartran ( ttj, amprms, ae2nm, hm, tlat, diurab, 0.0, 0.0,
                   temp, 0.0, humid, tlr, wavelr, rfun,
                   sst, cst, m_cosys, m_eqx, m_tar_p,
                   spm1_z, spm1_z_i,
                   spm2_z, spm2_z_i );

   /* Transform the target coordinates into a perfect-mount vector. */
      tcsVTenc ( m_tar_p[0], m_tar_p[1],
                 spm1_z, m_cosys, sst, cst, spm2_z,
                 OTA, 0.0, 0.0, 0.0, 0.0, 0.0,
                 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                 &a1, &b1, &a2, &b2, &j );
      a_z = jbp ? a2 : a1;
      b_z = jbp ? b2 : b1;

   /* Report the pointing corrections. */
      printf ( "\n"
               "   HA correction  = %+17.6f      arcsec\n",
                                                      ( a_z - a ) / AS2R );
      printf ( "   Dec correction = %+17.6f      arcsec\n",
                                                      ( b - b_z ) / AS2R );


   /*
   ** ----------------------------------------------
   ** Demonstrate the encoders-to-sky transformation
   ** ----------------------------------------------
   */

      tcsVTsky ( a, b, OTA, 0.0, 0.0, 0.0,
                 m_spm1_i, m_cosys, sst, cst, m_spm2_i,
                 ia, ib, np, xt, yt, zt, ga, gb,
                 &ra, &dec );

      printf ( "\n"
               "Encoders-to-sky:\n" );
      slaDr2tf ( 4, slaDranrm ( ra ), &s, i4 );
      printf ( "   RA = %2.2i %2.2i %2.2i.%4.4i  ",
                                              i4[0], i4[1], i4[2], i4[3] );
      slaDr2af ( 3, dec, &s, i4 );
      printf ( "   Dec = %c%2.2i %2.2i %2.2i.%3.3i\n",
                                           s, i4[0], i4[1], i4[2], i4[3] );
   /*
   ** -------------------------------------------
   ** Demonstrate the sky-to-image transformation
   ** -------------------------------------------
   */

      printf ( "\n"
               "Sky-to-image:\n" );

      ra = 21.0*D2R;
      dec = 18.9*D2R;

      slaDr2tf ( 4, slaDranrm ( ra ), &s, i4 );
      printf ( "   RA = %2.2i %2.2i %2.2i.%4.4i  ",
                                         i4[0], i4[1], i4[2], i4[3] );
      slaDr2af ( 3, dec, &s, i4 );
      printf ( "   Dec = %c%2.2i %2.2i %2.2i.%3.3i\n",
                                      s, i4[0], i4[1], i4[2], i4[3] );

      tcsVTxy ( ra, dec,
                m_spm1, m_cosys, sst, cst, m_spm2,
                OTA, 0.0, a, b,
                ia, ib, np, xt, yt, zt, ga, gb,
                &xim, &yim, &j );

      printf ( "   x  = %+12.6f mm ", xim * fl );
      slaDr2af ( 3, dec, &s, i4 );
      printf ( "  y   = %+12.6f mm\n", yim * fl );

   /*
   ** -------------------------------------------
   ** Demonstrate the image-to-sky transformation
   ** -------------------------------------------
   */

      tcsVTsky ( a, b, OTA, 0.0, xim, yim,
                 m_spm1_i, m_cosys, sst, cst, m_spm2_i,
                 ia, ib, np, xt, yt, zt, ga, gb,
                 &ra, &dec );

      printf ( "\n"
               "Image-to-sky:\n" );

      printf ( "   x  = %+12.6f mm ", xim * fl );
      slaDr2af ( 3, dec, &s, i4 );
      printf ( "  y   = %+12.6f mm\n", yim * fl );

      slaDr2tf ( 4, slaDranrm ( ra ), &s, i4 );
      printf ( "   RA = %2.2i %2.2i %2.2i.%4.4i  ",
                                              i4[0], i4[1], i4[2], i4[3] );
      slaDr2af ( 3, dec, &s, i4 );
      printf ( "   Dec = %c%2.2i %2.2i %2.2i.%3.3i\n",
                                           s, i4[0], i4[1], i4[2], i4[3] );

   /* Next solution. */
   }

/*
** The TCS demonstration terminates here.  An operational system would
** execute continuously, with tcsSlow being executed once every minute or
** so, tcsMedium running every few seconds and also to conclude a change
** of target, and tcsFast_e running at maybe 20 Hz.
*/

   return 0;

}
/*------------------------------------------------------------------------*/

#include "tcs.h"
#include "tcsmac.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                      *
*  The main routine, a single, multi-purpose function, starts here.    *
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
*  Calculation of mount demands, typically at 10 or 20 Hz, are         *
*  usually the result of timer activity.                               *
*                                                                      *
*  The code is designed to be usable in a computer or DSP local to the *
*  telescope, with the host application running in another computer.   *
*  It is up to the implementor to provide the required interprocessor  *
*  link software to transmit context changes as required.  It is also  *
*  up to the implementor to provide the servo software that realizes   *
*  the mount demands.                                                  *
*                                                                      *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void tcsFast_e ( int mode, int isol, double tai,
                 double T0, double St0,
                 double Ia, double Ib, double Np,
                 double Xt, double Yt, double Zt,
                 double Ga, double Gb, double Rnogo,
                 double M_tar_t0, double M_tar_p0[2], double M_tar_dt[2],
                 FRAMETYPE M_cosys, double M_spm1[3][3], double M_spm2[3][3],
                 double *roll, double *pitch )

/*
**  - - - - - - - - - -
**   t c s F a s t _ e
**  - - - - - - - - - -
**
**  The heart of the TCS.
**
**  ----------------------------------------------
**  Special simplified version of tcsFast - no
**  rotator or pointing-origin support is included
**  ----------------------------------------------
**
**  Given (control):
**     mode          int        action(s) required (Note 1)
**     isol          int        TRUE selects "beyond pole" solution
**     tai           double     specimen time (TAI MJD = JD-2400000.5)
**
**  Given (context):
**
**   TIME group (Note 3)
**     T0            double     timestamp for LAST and TT
**     St0           double     LAST at time T0
**
**   MODEL group (Note 4)
**     Ia            double     roll zero-point
**     Ib            double     pitch zero-point
**     Np            double     mount axes nonperpendicularity
**     Xt            double     telescope vector, x-component (Note 1)
**     Yt            double     telescope vector, y-component (Note 1)
**     Zt            double     telescope vector, z-component (Note 1)
**     Ga            double     guiding correction, collimation
**     Gb            double     guiding correction, pitch
**     Rnogo         double     mount pole avoidance radius
**
**   TARGET group (Note 5)
**     M_tar_t0      double     target reference time
**     M_tar_p0[2]   double     target coordinates at reference time
**     M_tar_dt[2]   double     target differential rates
**
**   TRANSFORM group (Notes 8)
**     M_cosys       FRAMETYPE frame for mount control
**     M_spm1[3][3]  double     mount SPM #1
**     M_spm2[3][3]  double     mount SPM #2
**
**  Returned (Notes 9-11):
**     roll          double*    mount roll (righthanded "south"-zero)
**     pitch         double*    mount pitch
**
**  Defined in tcs.h:
**     FRAMETYPE     enum       frame types
**     ROTLOC        enum       rotator locations
**
**  Defined in tcsmac.h:
**     STRPD         double     ST change per UT day (radians)
**     PI            double     Pi
**     PI2           double     2Pi
**
**  Called:  tcsVTenc
**
**  Notes:
**
**   1 The mode argument defines which of the repertoire of actions are
**     to be performed during this invocation.  Each action has a bit to
**     flag that it is to be performed:
**
**        bit    decimal            action
**
**      0000000     0      calculate new mount and rotator coordinates
**      0000010     2      update the sidereal time parameters
**      0000100     4      update the telescope pointing model coefficients
**      0001000     8      update the transformation matrices
**      0010000    16      update the target position
**
**     Unused bits are ignored.
**
**     Examples:
**
**        mode              action
**
**          0       calculate new mount and rotator coordinates
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
**   2 There is no support for instrument rotator in this version.
**
**   3 The time parameters enable fast computation of the Local Apparent
**     Sidereal Time and the Terrestrial Time by the pointing kernel.  The
**     parameters must be supplied by the host application.  Once every
**     five minutes is more than often enough.
**
**   4 The pointing coefficients will change slowly as other pointing
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
**   6 There is no support for pointing origin in this version.
**
**   7 There is no support for field orientation in this version.
**
**   8 The transformations will be updated every few seconds by the
**     "medium" process running in the host, and summarize the pointing
**     across the patch of sky at which the telescope is being aimed.
**     Included in these transformations are any pointing-model
**     adjustments which affect the roll axis misalignment, complementing
**     the other model terms (see the previous note).
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
**  10 The mount "roll" coordinate is -HA for an equatorial mount and
**     pi-Az for an altazimuth mount.  It is in the range +/-pi.
**
**  11 The mount coordinates are always "above the pole".  Handling for
**     "below the pole", "beyond the zenith", "the other side of the
**     pier" etc cases happens outside the present routine, as does
**     treatment of cablewraps.
**
**     ***  It is the host application's responsibility not to  ***
**     ***  enable the calculation of mount coordinates until   ***
**     ***  all of the context has been initialized.            ***
**
**  Latest revision:   4 May 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{

/*--------- The context for the fast process -------------------------------*/

/* TIME: sidereal and dynamical time */
   static double t0;             /* timestamp for LAST */
   static double st0;            /* LAST at time t0 */

/* MODEL: pointing model */
   static double ia;             /* roll zero-point */
   static double ib;             /* pitch zero-point */
   static double np;             /* mount axes nonperpendicularity */
   static double xt;             /* telescope vector, x-coordinate */
   static double yt;             /* telescope vector, y-coordinate */
   static double zt;             /* telescope vector, z-coordinate */
   static double ga;             /* guiding correction, collimation */
   static double gb;             /* guiding correction, pitch */
   static double rnogo;          /* mount pole avoidance radius */

/* TRANSFORM: transformation matrices etc */
   static FRAMETYPE m_cosys;     /* frame for mount control */
   static double m_spm1[3][3];   /* mount SPM #1 */
   static double m_spm2[3][3];   /* mount SPM #2 */

/* TARGET: what place in the sky is to be imaged */
   static double m_tar_t0;       /* target reference time (TAI MJD) */
   static double m_tar_p0[2];    /* target coordinates at reference time */
   static double m_tar_dt[2];    /* target differential rates */

/* LATEST TIMESTAMP */
   static double tlast = 0.0;             /* timestamp */

/*--------------------------------------------------------------------------*/

/* Target vectors */
   double tar[2];                  /* spherical coordinates (final) */

   int i, j;
   double dt, st, sst, cst, dtlast, dtdt, ad1, bd1, ad2, bd2;


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

      m_tar_t0 = M_tar_t0;
      for ( i = 0; i < 2; i++ ) {
         m_tar_p0[i] = M_tar_p0[i];
      }
      for ( i = 0; i < 2; i++ ) {
         m_tar_dt[i] = M_tar_dt[i];
      }
   }

   if ( mode & 64 ) {

   /* Update TRANSFORM context. */

      m_cosys = M_cosys;
      for ( j = 0; j < 3; j++ ) {
         for ( i = 0; i < 3; i++ ) {
            m_spm1[j][i] = M_spm1[j][i];
         }
      }
      for ( j = 0; j < 3; j++ ) {
         for ( i = 0; i < 3; i++ ) {
            m_spm2[j][i] = M_spm2[j][i];
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
      st = st0 + dt * STRPD;
      sst = sin ( st );
      cst = cos ( st );

   /*
   ** --------------
   ** EXTRAPOLATIONS
   ** --------------
   */

   /* Time since previous iteration (days). */
      dtlast = tai - tlast;

   /* Differential tracking. */
      dtdt = tai - m_tar_t0;
      for ( i = 0; i < 2; i++ ) {
         tar[i] = m_tar_p0[i] + dtdt * m_tar_dt[i];
      }

   /*
   **
   ** -------------
   ** MOUNT DEMANDS
   ** -------------
   **
   */

      tcsVTenc ( tar[0], tar[1],
                 m_spm1, m_cosys, sst, cst, m_spm2,
                 OTA, 0.0, 0.0, 0.0, 0.0, 0.0,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 &ad1, &bd1, &ad2, &bd2, &j );

   /* (We are ignoring the status.) */

   /*
   ** -------
   ** RESULTS
   ** -------
   */

   /* Save the new timestamp. */
      tlast = tai;

   /* Return the encoder demands (for the selected solution). */
      *roll = isol ? ad2 : ad1;
      *pitch = isol ? bd2 : bd1;

   }
}
