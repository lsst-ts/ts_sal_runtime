#include <stdio.h>
#include <slalib.h>
#include "tcs.h"
#include "tcsmac.h"

int main ( )

/*
**   - - - - - - - - -
**    T C S _ D E M O
**   - - - - - - - - -
**
**   Demonstration of TCSpk pointing kernel.
**
**   To switch between the equatorial, altazimuth and generalized
**   gimbal cases, edit the macro MOUNT to "ALTAZ", "EQUAT" or
**   "GIMBAL".
**
**   ----------------
**   REAL-TIME DESIGN
**   ----------------
**
**   The fundamental principle upon which the TCSpk design, and
**   this demonstration, rests is that there are two threads with
**   a shared context.  One thread, at lower priority, maintains the
**   context, while the other, at higher priority or operating in
**   a separate processor, uses it to generate timestamped positions
**   for the mount axes and the rotator.  The low-priority thread is
**   triggered by a combination of timer interrupts (typically every
**   few seconds) and notifications from the user-interface that
**   something has changed.  The high-priority thread is triggered at,
**   say, 20 Hz by timer interrupts.  In the present implementation,
**   the high-priority thread is also triggered by the low-priority
**   thread to cause it to download pieces of changed context.
**   Other schemes for managing the context can be substituted if
**   preferred.
**
**  ---------------
**  EXTERNAL EVENTS
**  ---------------
**
**  Here is a summary of what actions the TCS application needs to take
**  when various external events occur.
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
**                                tcsFast to cause it to copy the
**                                whole of the context.
**
**   Every 60s (or so)            Call tcsSlow.
**
**   Every 5s (or so)             Call tcsMedium, then call tcsFast
**                                to cause it to copy the whole
**                                context.
**
**   User asks for a              Obtain the new information and then
**   different position-angle.    call tcsFast to cause it to copy the
**                                context items that have changed.
**
**   User asks for a              Obtain the new information and then
**   different pointing-origin.   call tcsFast to cause it to copy the
**                                context items that have changed.
**
**   User updates the             Obtain the new information and then
**   pointing-origin or the       call tcsFast to cause it to copy the
**   associated offsets from      context items that have changed.
**   base.
**
**   User supplies a new          Obtain the new information and then
**   target.                      call tcsTargup to calculate the
**                                current net position.  Call tcsMedium
**                                to update the transformation to
**                                match the new position, and then call
**                                tcsFast to cause it to copy the
**                                context items that have changed.  It
**                                is usually appropriate to zero the
**                                guiding corrections (ga,gb) at this
**                                point.
**
**   User updates the target      Obtain the new information and then
**   offsets from base or         call tcsFast to cause it to copy the
**   differential tracking        context items that have changed.  A
**   rates.                       refinement would be to test whether
**                                the target position had changed
**                                significantly (more than a few
**                                arcminutes) and, if so, to call
**                                tcsMedium before the call to tcsFast.
**
**   Guiding activity occurs.     Call tcsFast to cause it to copy the
**                                updated ga and gb values.
**
**   Every 50ms (or so).          Trigger tcsFast to cause it to
**                                calculate new mount and rotator
**                                positions.  A good time to choose is
**                                that of the next 20Hz interrupt.
**
**  It is a good plan to combine the slow and medium processing rather
**  than having separate scheduling arrangements.  On most occasions,
**  tcsMedium alone can be called (followed by tcsFast), but once every
**  so many invocations the call to tcsMedium can be preceded with a
**  call to tcsSlow.
**
**  -----------------
**  DATA REQUIREMENTS
**  -----------------
**
**  Here is a summary of the information required to drive the TCS.
**
**   INITIALIZATION
**
**   . Site longitude, latitude and height above sea level.
**
**       Inaccurate site coordinates will show up as spurious
**       polar/azimuth/roll axis misalignment parameters.  If
**       grossly wrong, the refraction predictions will be
**       unreliable.  Height makes little difference (but air
**       pressure does - see below).
**
**   . Telescope focal length.
**
**       If the TCS does not support the pointing-origin feature,
**       this can be set to any sensible value (say 1.0).
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
**       telescopes need it to 1 HPa (=mB).  A fixed value for
**       the tropospheric lapse rate of 0.0065 K/m is always
**       acceptable.  For radio applications high-accuracy
**       temperature and humidity are also needed.  Finally,
**       for optical/IR applications, a reference wavelength
**       needs to be chosen, for example 0.5 micrometers.
**
**   . Mount type.
**
**       ALTAZ, EQUAT or GIMBAL needs to be specified.  If GIMBAL,
**       there are numerical parameters as well, to specify the
**       gimbal orientation.
**
**   . Rotator location.
**
**       Use OTA for ordinary non-Nasymyth, non-coude applications,
**       or where there is no rotator.
**
**   . Initial mount coordinates.
**
**       Some legal values are needed to start the system.  They
**       do not have to reflect the actual attitude.
**
**   . Zenith avoidance distance.
**
**       Tracks through the zenith will be diverted to comply with
**       this parameter.
**
**   . Frames.
**
**       Reference frames for controlling the telescope and rotator
**       must be specified.  FK5 is the sensible default.  Along
**       with each frame ID, an equinox is needed:  2000.0 is the
**       obvious choice.  A wavelength has to be chosen as well,
**       perhaps 0.55 micrometers for visual use.  (Note that
**       ICRS coordinates are the same as FK5 2000 coordinates to
**       the accuracy required here.)
**
**   . Pointing model.
**
**       A pointing model is required.  It can be set up in two
**       different ways (see the code).  It is possible to change
**       the coefficient values while running (or even the form of
**       the model);  the new corrections will take effect the
**       next time the MEDIUM routine is run.
**
**   . Guiding adjustments.
**
**       These should be initialized to zero (though this demo
**       program in fact sets one of them non-zero).
**
**   . Rotator readings.
**
**       The system needs a rotator angle, plus a velocity
**       and timestamp.  Simple equatorial applications where
**       there is no rotator should set all these to zero.
**
**   REFRACTION DATA
**
**   . Meteorological readings plus color.
**
**       The temperature, pressure, humidity, lapse rate and
**       reference wavelength can be changed at any time.  The
**       changes will take effect when the SLOW routine is next
**       run.  On small telescopes of modest accuracy, though it
**       is worth getting a pressure reading it is unlikely to
**       need changing during the night.  If a pressure reading
**       is unavailable, it can be estimated from the observatory
**       height above sea level using a standard atmosphere model.
**
**   FIELD ORIENTATION
**
**   This entire feature can be omitted if there is no rotator.
**   All the angles involved (IAA, IPA, RMA) should be set to
**   zero and then left alone.
**
**   . Instrument Alignment Angle.
**
**       The IAA is specified by its sine and cosine.  The
**       angle is nominated by the user and is likely to remain
**       fixed for the whole session.
**
**   . Instrument Position Angle.
**
**       The user may wish to change the angle on the sky of
**       the projection of his instrument.  On each occasion,
**       all that is needed is the new angle.  The angle can
**       be changed while tracking a target.
**
**   . De-rotation criterion.
**
**       The rotator demands that are generated can either freeze
**       the IPD on the sky ("slit-optimized") or can eliminate
**       any overall rotation component ("field-optimized").
**
**   POINTING ORIGIN
**
**   Small-telescope applications may omit the entire pointing-
**   origin feature, though it can be useful if both a viewing
**   eyepiece and a CCD are used - the star can be slewed into
**   the eyepiece, centered, and then sent to the CCD center
**   simply by changing the x,y.  To disable the feature, set
**   the first base x,y and all its offsets to zero, and set
**   npos to zero to select this pointing-origin.
**
**   . Base pointing-origins (NPOS of them).
**
**       The pointing-origin should be set to 0,0 by default,
**       corresponding to the rotator axis (if there is a
**       rotator).  Changing the x,y while tracking will cause
**       the star image to move to the specified location.
**
**   . Offsets from base in x,y (three for each base; they add).
**
**       This is an advanced feature, used for such things
**       as trailing the image along a spectrograph slit.
**       The offsets should be left at zero if the feature
**       is unwanted.
**
**   . Pointing-origin selection.
**
**       This integer, in the range 0 to NPOS-1, selects which
**       of the NPOS pointing-origins is to be used.  The target
**       image will then transfer to this place in the focal
**       plane automatically.
**
**   FRAMES AND TARGET
**
**   The coordinate systems for controlling the mount and the
**   instrument rotator are individually controllable.  The
**   minimum implementation would be a fixed frame of FK5/2000
**   (effectively the same thing as Hipparcos/ICRS) for the
**   mount and the same for the rotator.
**
**   Although a fixed frame can be used, all TCS applications
**   require the ability to change the target coordinates of
**   course.
**
**   . Mount frame (and equinox if needed).
**
**        FK5/2000 can be used for almost everything.  For
**        tracking planets, geocentric apparent place may
**        also be needed, depending on how the ephemeris
**        data are being calculated.
**
**   . Color for mount and rotator tracking.
**
**        This allows atmospheric dispersion to be corrected.
**        On small telescopes leave it set to (say)
**        0.55 micrometers.
**
**   . Rotator frame (and equinox if needed).
**
**        This controls which sort of "north" is being used.
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
**  TCSpk is based on a concept called the "virtual telescope".  This
**  is a set of transformations that link a place in the sky, called the
**  "target", with a place in the focal plane, called the "pointing
**  origin", and with a mechanical pointing direction for the telescope.
**  Complicated details such as pointing corrections are hidden inside
**  the virtual-telescope routines, so that clients (for example an
**  instrument wishing to offset the image in the focal plane) can do so
**  simply by adjusting the star or image coordinates.  A TCS always
**  supports at least one virtual telescope, that for the telescope
**  mount itself.  However, there may also be guiders, tip/tilt sub-
**  reflectors, and choppers present, and these can be implemented as
**  separate virtual telescopes, albeit ones which are forced to share
**  the one mount position (because there is only one mount).
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
**  Last revision:   24 July 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

#define MOUNT ALTAZ      /* Mount type for this demonstration */
#define RLOCN OTA        /* Instrument rotator location */

/* Euler angles wrt terrestrial [Az,El] for generalized gimbal case */
#define GIM1Z 0.0        /* 1st rotation, about z-axis */
#define GIM2Y 0.0        /* 2nd rotation, about y-axis */
#define GIM3X 0.0        /* 3rd rotation, about x-axis */

{
/* Context */
#include "tcsctx.h"

   int i, i4[4], j;
   char sterm[9], s;
   double vterm, tai, aia, ra, dec, t, st, sst, cst, xim, yim,
          a1, b1, a2, b2, a, b;

/*
** --------------
** Initialization
** --------------
**
** An operational TCS needs to do all of the following before the
** system enters its real-time mode.  Normally the process would
** be controlled from an external agent such as a configuration file.
**
** n.b. C's default initialization to zero is assumed.
**
*/

/* No special refraction routine. */
   rfun = NULL;

/* Site and telescope. */
   tlongm = -155.471667*D2R;
   tlatm = 19.826667*D2R;
   hm = 4145.0;
   fl = 128000.0;
   rnogo = 0.25*D2R;

/* Time. */
   delut = 0.746/86400.0;
   delat = 29.0/86400.0;
   ttmtai = 32.184/86400.0;
   xpmr = 0.25*AS2R;
   ypmr = 0.4*AS2R;

/* Met. */
   temp = 275.0;
   press = 605.0;
   humid = 0.8;
   tlr = 0.0065;
   wavelr = 0.5;

/* Mount type. */
   mount = MOUNT;

/* Rotator location. */
   rotl = RLOCN;

/* Mount above/below pole state. */
   jbp = 0;

/* Initial mount [roll,pitch] (arbitrary). */
   roll = 0.0;
   pitch = 1.0;

/* Frames. */
   m_cosys = FK5;
   m_eqx = 2000.0;
   m_wavel = 1.0;
   r_cosys = m_cosys;
   r_eqx = m_eqx;
   r_wavel = m_wavel;

/* Pointing model. */
   if ( mount == EQUAT ) {

   /* Equatorial case:  demonstrate initialization from a TPOINT file. */
      if ( tcsIntpm ( "specimen.mod", MAXTRM, NTROOM, model,
                      &nterml, &ntermx, &nterms,
                      coeffn, coform, coeffv ) ) return -1;
   } else {

   /* Altazimuth case:  demonstrate initialization by explicit calls. */
      if ( tptMinit ( MAXTRM, NTROOM, model,
                      &nterml, &ntermx, &nterms, coeffn ) ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "IA", 25.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "IE", 15.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "TF", 10.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "CA", -110.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "NPAE", 8.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "AW", 999.9*AS2R,      /* temp */
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "AN", -12.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;

   /* Demonstrate changing coefficient value. */
      if ( tcsSterm ( "AW", -5.0*AS2R,
                      MAXTRM, model, coeffn, coeffv ) ) return -1;
   }

/* List the model. */
   printf ( "\nPointing model:\n\n" );
   for ( i = 1; ! tcsIterm ( i,
                             MAXTRM, model, coeffn, coeffv,
                             sterm, &vterm ); i++ ) {
      printf ( "%3d    %-8s%+10.2f\n", i, sterm, vterm/AS2R );
   }

/* Guiding adjustments. */
   ga = 0.0*AS2R;
   gb = 22.0*AS2R;

/* Secondary initialization. */
   if ( tcsInit2 ( tlongm, tlatm, xpmr, ypmr, hm,
                   mount, GIM1Z, GIM2Y, GIM3X, ae2nm,
                   &tlong, &tlat, &uau, &vau, &ukm, &vkm, &diurab ) ) {
      printf ( "\nSecondary initialization has failed.\n" );
      return -1;
   }

/* Simulate (for this demo) hardware that by now would be running. */
   rma = 30.0*D2R;   /* Rotator angle (n.b. achieved, NOT demanded) */
   rmav = 0.0;       /* Velocity (achieved). */
   rmat = 0.0;       /* Timestamp. */

/*
** ------------------------------------------------
** Run the SLOW routine for the first of many times
** ------------------------------------------------
**
** From now on, the SLOW routine must be run from time to time
** (e.g. once a minute) to update the things that are slowly changing
** and target-independent.  Because the SLOW routine is comparatively
** CPU-intensive, most TCS implementations will choose to run it in a
** different thread and at a lower priority than the FAST routine (or
** even in a different processor).  However, it can and should be run
** in the same thread as the MEDIUM routine (see later), which will
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

/* Get the (approximate) current time. */
   (void) tcsTime ( &tai );

/* Perform the medium update for that time. */
   (void) tcsMedium ( tai, MAXTRM, model, coeffv, nterml, ntermx, nterms,
                      coeffn, coform, mount, ae2nm, roll, pitch, jbp, aux,
                      m_cosys, m_eqx, m_wavel, r_cosys, r_eqx, r_wavel,
                      m_tar_p,
                      t0, st0, ttj, temp, press, humid, tlr, wavelr,
                      refa, refb, rfun, hm, tlat, diurab, amprms,
                      &ia, &ib, &np, &xt, &yt, &zt, ae2mt,
                      m_spm1, m_spm1_i, m_spm2, m_spm2_i,
                      r_spm1, r_spm1_i, r_spm2, r_spm2_i );

/* Tell the FAST routine about everything initialized so far. */
   tcsFast ( ALL, jbp, tai,
             rotl, rmat, rma, rmav,
             t0, st0,
             ia, ib, np, xt, yt, zt, ga, gb, rnogo,
             m_tar_t0, m_tar_op0, m_tar_dt,
             fl, m_por_p,
             sia, cia, pai, 1,
             m_cosys, m_spm1, m_spm2, r_cosys, r_spm1_i, r_spm2_i,
             &roll, &pitch, &rota );

/*
** --------------------------------------------------------
** Obtain a field-orientation as if from the user interface
** --------------------------------------------------------
**
** This demonstration uses hardwired constants.  An operational
** system would obtain the Instrument Alignment Angle (IAA), the
** Instrument Position Angle (IPA), the reference frame in which
** IPA is expressed (r_cosys), the frame's equinox (r_eqx) and the
** wavelength for rotator tracking (r_wavel) from the user in a
** variety of ways, and would then set up the following context
** variables:
**
**    r_cosys    FRAMETYPE    rotator frame
**    r_eqx      double       rotator equinox
**    r_wavel    double       wavelength
**    pai        double       IPA
**    sia, cia   double       sine and cosine of IAA
**    jf         int          optimization: 0=slit, else=field
**
*/

   aia = 0.0;              /* IAA */

   pai = 0.0;              /* IPA */
   sia = sin ( aia );      /* sin(IAA) */
   cia = cos ( aia );      /* cos(IAA) */
   jf = 1;                 /* field-optimized */

/* Tell the medium routine. */
   (void) tcsMedium ( tai, MAXTRM, model, coeffv, nterml, ntermx, nterms,
                      coeffn, coform, mount, ae2nm, roll, pitch, jbp, aux,
                      m_cosys, m_eqx, m_wavel, r_cosys, r_eqx, r_wavel,
                      m_tar_p,
                      t0, st0, ttj, temp, press, humid, tlr, wavelr,
                      refa, refb, rfun, hm, tlat, diurab, amprms,
                      &ia, &ib, &np, &xt, &yt, &zt, ae2mt,
                      m_spm1, m_spm1_i, m_spm2, m_spm2_i,
                      r_spm1, r_spm1_i, r_spm2, r_spm2_i );

/* Tell the FAST routine. */
   tcsFast ( PA, jbp, tai,
             rotl, rmat, rma, rmav,
             t0, st0,
             ia, ib, np, xt, yt, zt, ga, gb, rnogo,
             m_tar_t0, m_tar_op0, m_tar_dt,
             fl, m_por_p,
             sia, cia, pai, jf,
             m_cosys, m_spm1, m_spm2, r_cosys, r_spm1_i, r_spm2_i,
             &roll, &pitch, &rota );

/*
** ------------------------------------------------------
** Obtain a pointing-origin as if from the user interface
** ------------------------------------------------------
**
** This demonstration uses hardwired constants.  An operational
** system would obtain pointing-origins from the user in a variety
** of ways, and would then set up the following context variables:
**
**    m_por_p0   double[npo][2]      pointing-origin [x,y]
**    m_por_ob   double[npo][3][2]   offsets from base
**
** The units are as for the focal length.
**
** Several pointing-origins (NPOS in number) are stored, selectable by
** means of the index npo.  It is up to the application to select the
** one that is required.  For example, npo=1 could be the center of the
** acquisition TV and npo=2 could be the entrance aperture of the
** instrument.
**
** Certain calibration procedures require that the pointing-origin be
** reset to [0,0], the rotator axis.  A good plan is to reserve
** pointing-origin #0 for the rotator axis and to fix all the values
** at zero.
**
** It is the net pointing-origin that is passed to the FAST routine
** in this demonstration.  This assumes that the main application
** provides the offsets-from-base facility.  An alternative is to
** place the facility in the FAST routine itself.
*/

   npo = 1;
   m_por_p0[npo][0] = 180.0;
   m_por_p0[npo][1] = -150.0;
   m_por_ob[npo][0][0] = -1.0;
   m_por_ob[npo][0][1] = -2.0;

/* Incorporate the offsets from base. */
   tcsPorup ( m_por_p0[npo], m_por_ob[npo], m_por_p );

/* Tell the FAST routine. */
   tcsFast ( PO, jbp, tai,
             rotl, rmat, rma, rmav,
             t0, st0,
             ia, ib, np, xt, yt, zt, ga, gb, rnogo,
             m_tar_t0, m_tar_op0, m_tar_dt,
             fl, m_por_p,
             sia, cia, pai, jf,
             m_cosys, m_spm1, m_spm2, r_cosys, r_spm1_i, r_spm2_i,
             &roll, &pitch, &rota );

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
** It is the net target that is passed to the FAST routine in this
** demonstration.  This assumes that the main application provides
** the offsets-from-base facility.  An alternative is to place the
** facility in the FAST routine itself.
**
*/

   m_cosys = FK4;
   m_eqx = 1975.0;
   m_wavel = 0.5;
   r_cosys = m_cosys;
   r_eqx = m_eqx;
   m_tar_p0 [ 0 ] = 0.3654719453676126;
   m_tar_p0 [ 1 ] = 0.3316125578789226;
   m_tar_dt [ 0 ] = 0.0;
   m_tar_dt [ 1 ] = 0.0;
   m_tar_t0 = 0.0;
   m_tar_ob [ 0 ] [ 0 ] = 15.0*AS2R;
   m_tar_ob [ 0 ] [ 1 ] = 60.0*AS2R;

/* Get the (approximate) current time. */
   (void) tcsTime ( &tai );

/* Calculate target position. */
   tcsTargup ( tai, m_tar_t0, m_tar_p0, m_tar_dt, m_tar_ob,
               m_tar_op0, m_tar_p );

/* Now run the MEDIUM routine to generate the new pointing model and SPMs. */
   (void) tcsMedium ( tai, MAXTRM, model, coeffv, nterml, ntermx, nterms,
                      coeffn, coform, mount, ae2nm, roll, pitch, jbp, aux,
                      m_cosys, m_eqx, m_wavel, r_cosys, r_eqx, r_wavel,
                      m_tar_p,
                      t0, st0, ttj, temp, press, humid, tlr, wavelr,
                      refa, refb, rfun, hm, tlat, diurab, amprms,
                      &ia, &ib, &np, &xt, &yt, &zt, ae2mt,
                      m_spm1, m_spm1_i, m_spm2, m_spm2_i,
                      r_spm1, r_spm1_i, r_spm2, r_spm2_i );

/* Report the target. */
   slaDr2tf ( 4, slaDranrm ( m_tar_p0[0] ), &s, i4 );
   printf ( "\nRA = %2.2i %2.2i %2.2i.%4.4i  ", i4[0], i4[1], i4[2], i4[3] );
   slaDr2af ( 3, m_tar_p0[1], &s, i4 );
   printf ( "Dec = %c%2.2i %2.2i %2.2i.%3.3i  <- test star\n",
                                             s, i4[0], i4[1], i4[2], i4[3] );
   slaDr2tf ( 4, slaDrange ( m_tar_ob[0][0] ), &s, i4 );
   printf ( "    %c%2.2i %2.2i %2.2i.%4.4i  ",
                                             s, i4[0], i4[1], i4[2], i4[3] );
   slaDr2af ( 3, m_tar_ob[0][1], &s, i4 );
   printf ( "      %c%2.2i %2.2i %2.2i.%3.3i  <- offset\n",
                                             s, i4[0], i4[1], i4[2], i4[3] );

/* Tell the FAST routine about the new target and SPMs. */
   tcsFast ( TARGET + TRANSFORM + MODEL, jbp, tai,
             rotl, rmat, rma, rmav,
             t0, st0,
             ia, ib, np, xt, yt, zt, ga, gb, rnogo,
             m_tar_t0, m_tar_op0, m_tar_dt,
             fl, m_por_p,
             sia, cia, pai, jf,
             m_cosys, m_spm1, m_spm2, r_cosys, r_spm1_i, r_spm2_i,
             &roll, &pitch, &rota );

/*
** From now on, the pointing-origin and the various offsets from base
** can be changed at will.  Each time this happens appropriate steps
** must be taken to communicate the new information to the FAST routine.
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
** safe but arbitrary assumed telescope position.  As soon as the
** FAST routine runs, which it will do as a consequence of being
** invoked at some regular interval such as 50 ms, an accurate
** demanded position will be available.  The call to FAST, below,
** simulates this effect.  In reality, the pointing corrections
** will simply be slightly inaccurate for a few seconds as the
** system starts up.
**
*/

/* Read the clock */
   (void) tcsTime ( &tai );

/* Call FAST to obtain a reasonably accurate demand position. */
   tcsFast ( 0, jbp, tai,
             rotl, rmat, rma, rmav,
             t0, st0,
             ia, ib, np, xt, yt, zt, ga, gb, rnogo,
             m_tar_t0, m_tar_op0, m_tar_dt,
             fl, m_por_p,
             sia, cia, pai, jf,
             m_cosys, m_spm1, m_spm2, r_cosys, r_spm1_i, r_spm2_i,
             &roll, &pitch, &rota );

/* Calculate target position. */
   tcsTargup ( tai, m_tar_t0, m_tar_p0, m_tar_dt, m_tar_ob,
               m_tar_op0, m_tar_p );

/* Now run the MEDIUM routine to generate updated pointing coefficients. */
   (void) tcsMedium ( tai, MAXTRM, model, coeffv, nterml, ntermx, nterms,
                      coeffn, coform, mount, ae2nm, roll, pitch, jbp, aux,
                      m_cosys, m_eqx, m_wavel, r_cosys, r_eqx, r_wavel,
                      m_tar_p,
                      t0, st0, ttj, temp, press, humid, tlr, wavelr,
                      refa, refb, rfun, hm, tlat, diurab, amprms,
                      &ia, &ib, &np, &xt, &yt, &zt, ae2mt,
                      m_spm1, m_spm1_i, m_spm2, m_spm2_i,
                      r_spm1, r_spm1_i, r_spm2, r_spm2_i );

/* Finally tell the FAST routine about the updated pointing model and SPMs. */
   tcsFast ( TRANSFORM + MODEL, jbp, tai,
             rotl, rmat, rma, rmav,
             t0, st0,
             ia, ib, np, xt, yt, zt, ga, gb, rnogo,
             m_tar_t0, m_tar_op0, m_tar_dt,
             fl, m_por_p,
             sia, cia, pai, jf,
             m_cosys, m_spm1, m_spm2, r_cosys, r_spm1_i, r_spm2_i,
             &roll, &pitch, &rota );

/*
** --------------------------------
** Run the FAST routine a few times
** --------------------------------
**
** The FAST routine would normally be triggered by a timer interrupt,
** at a regular rate of 5-20 Hz.  This may happen in a different
** processor.  It is assumed here that the appropriate mechanisms are
** in place (a) to implement the above "update" calls to tcsFast and
** (b) to retrieve information from the mount controller as required.
**
*/

/* Read the clock. */
   (void) tcsTime ( &tai );

/* Simulate a few successive calls to FAST at 20Hz. */
   for ( i = -20; i < 3; i++ ) {
      t = tai + ( ( (double) i ) * 0.05 ) / 86400.0;

   /* Ask the FAST routine to calculate new demands. */
      tcsFast ( 0, jbp, t,
                rotl, rmat, rma, rmav,
                t0, st0,
                ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                m_tar_t0, m_tar_op0, m_tar_dt,
                fl, m_por_p,
                sia, cia, pai, jf,
                m_cosys, m_spm1, m_spm2, r_cosys, r_spm1_i, r_spm2_i,
                &roll, &pitch, &rota );

   /*
   ** Note:  it may be appropriate at this point to tell the FAST
   ** process that the rotator has moved (always assuming the
   ** telescope is equipped with a rotator).  When to do so depends
   ** on whether the rotator is being driven and the current speed
   ** at which it is moving.  The FAST routine linearly extrapolates
   ** the achieved rotator position, and frequent updates of the
   ** context may well be unnecessary.  The present demonstration
   ** has a fixed rotator.
   */

      if ( i >= 0 ) {
         printf ( "\ntimestamp       = %23.10f  MJD(TAI)\n", t );
         switch ( mount ) {

         case EQUAT:
            printf ( "HA demand       = %+23.10f  degrees\n", - roll / D2R );
            printf ( "Dec demand      = %+23.10f  degrees\n", pitch / D2R );
            break;

         case ALTAZ:
            printf ( "Az demand       = %23.10f  degrees\n",
                                           slaDranrm ( PI - roll ) / D2R );
            printf ( "El demand       = %23.10f  degrees\n", pitch / D2R );
            break;

         default:
            printf ( "Roll demand     = %23.10f  degrees\n", roll / D2R );
            printf ( "Pitch demand    = %23.10f  degrees\n", pitch / D2R );

         }
         printf ( "rotator demand  = %23.10f  degrees\n", rota / D2R );
      }
   }

/* Functions of LAST for demonstrations. */
   st = st0 + ( t - t0 ) * STRPD;
   sst = sin ( st );
   cst = cos ( st );

/* Scale the pointing-origin into natural units. */
   xim = m_por_p[0] / fl;
   yim = m_por_p[1] / fl;

/*
** ----------------------------------------------
** Demonstrate the sky-to-encoders transformation
** ----------------------------------------------
*/

   tcsVTenc ( m_tar_p[0], m_tar_p[1],
              m_spm1, m_cosys, sst, cst, m_spm2,
              rotl, rma, roll, pitch, xim, yim,
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

   tcsVTsky ( a, b, rotl, rma, xim, yim,
              m_spm1_i, m_cosys, sst, cst, m_spm2_i,
              ia, ib, np, xt, yt, zt, ga, gb,
              &ra, &dec );

   printf ( "\nEncoders-to-sky:\n" );
   slaDr2tf ( 4, slaDranrm ( ra ), &s, i4 );
   printf ( "   RA = %2.2i %2.2i %2.2i.%4.4i  ", i4[0], i4[1], i4[2], i4[3] );
   slaDr2af ( 3, dec, &s, i4 );
   printf ( "   Dec = %c%2.2i %2.2i %2.2i.%3.3i\n",
                                              s, i4[0], i4[1], i4[2], i4[3] );

/*
** -------------------------------------------
** Demonstrate the image-to-sky transformation
** -------------------------------------------
**
*/

/* Use the pointing-origin itself, to recover the original target. */
   tcsVTsky ( a, b, rotl, rma, xim, yim,
              m_spm1_i, m_cosys, sst, cst, m_spm2_i,
              ia, ib, np, xt, yt, zt, ga, gb,
              &ra, &dec );

   printf ( "\nImage-to-sky:\n" );

   printf ( "   x  = %+12.6f mm ", xim * fl );
   printf ( "  y   = %+12.6f mm\n", yim * fl );

   slaDr2tf ( 4, slaDranrm ( ra ), &s, i4 );
   printf ( "   RA = %2.2i %2.2i %2.2i.%4.4i  ", i4[0], i4[1], i4[2], i4[3] );
   slaDr2af ( 3, dec, &s, i4 );
   printf ( "   Dec = %c%2.2i %2.2i %2.2i.%3.3i\n",
                                             s, i4[0], i4[1], i4[2], i4[3] );

/*
** -------------------------------------------
** Demonstrate the sky-to-image transformation
** -------------------------------------------
*/

   printf ( "\nSky-to-image:\n" );

   ra = 0.3665191431;
   dec = 0.3316125579;

   slaDr2tf ( 4, slaDranrm ( ra ), &s, i4 );
   printf ( "   RA = %2.2i %2.2i %2.2i.%4.4i  ",
                                      i4[0], i4[1], i4[2], i4[3] );
   slaDr2af ( 3, dec, &s, i4 );
   printf ( "   Dec = %c%2.2i %2.2i %2.2i.%3.3i\n",
                                   s, i4[0], i4[1], i4[2], i4[3] );

   tcsVTxy ( ra, dec,
             m_spm1, m_cosys, sst, cst, m_spm2,
             rotl, rma, a, b,
             ia, ib, np, xt, yt, zt, ga, gb,
             &xim, &yim, &j );

   printf ( "   x  = %+12.6f mm ", xim * fl );
   slaDr2af ( 3, dec, &s, i4 );
   printf ( "  y   = %+12.6f mm\n", yim * fl );

   tcsVTsky ( a, b, rotl, rma, xim, yim,
              m_spm1_i, m_cosys, sst, cst, m_spm2_i,
              ia, ib, np, xt, yt, zt, ga, gb,
              &ra, &dec );

   printf ( "\nImage-to-sky:\n" );

   printf ( "   x  = %+12.6f mm ", xim * fl );
   slaDr2af ( 3, dec, &s, i4 );
   printf ( "  y   = %+12.6f mm\n", yim * fl );

   slaDr2tf ( 4, slaDranrm ( ra ), &s, i4 );
   printf ( "   RA = %2.2i %2.2i %2.2i.%4.4i  ", i4[0], i4[1], i4[2], i4[3] );
   slaDr2af ( 3, dec, &s, i4 );
   printf ( "   Dec = %c%2.2i %2.2i %2.2i.%3.3i\n",
                                             s, i4[0], i4[1], i4[2], i4[3] );

/*
** The TCS demonstration terminates here.  An operational system would
** execute continuously, with tcsSlow being executed once every minute or
** so, tcsMedium running every few seconds and also to conclude a change
** of target, and tcsFast running at maybe 20 Hz.
*/

   return 0;

}
