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

void tcsFast ( int mode,
               int isol,
               double tai,

               ROTLOC Rotl,
               double Rmat,
               double Rma,
               double Rmav,

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

               double M_tar_t0,
               double M_tar_p0[2],
               double M_tar_dt[2],

               double Fl,
               double M_por_p[2],

               double Sia,
               double Cia,
               double Pai,
               int Jf,

               FRAMETYPE M_cosys,
               double M_spm1[3][3],
               double M_spm2[3][3],
               FRAMETYPE R_cosys,
               double R_spm1_i[3][3],
               double R_spm2_i[3][3],

               double *roll,
               double *pitch,
               double *rota )

/*
**  - - - - - - - -
**   t c s F a s t
**  - - - - - - - -
**
**  The heart of the TCS.
**
**  Given (control):
**     mode       int           action(s) required (Note 1)
**     isol       int           TRUE selects "below pole" solution
**     tai        double        timestamp (TAI MJD = JD-2400000.5)
**
**  Given (context):
**
**   ROTATOR group (Note 2)
**     Rotl       ROTLOC        focal station
**     Rmat       double        timestamp for Rma and Rmav
**     Rma        double        achieved rotator angle at time Rmat
**     Rmav       double        achieved rotator velocity at time Rmat
**
**   TIME group (Note 3)
**     T0         double        timestamp for LAST and TT
**     St0        double        LAST at time T0
**
**   MODEL group (Note 4)
**     Ia         double        roll zero-point
**     Ib         double        pitch zero-point
**     Np         double        mount axes nonperpendicularity
**     Xt         double        telescope vector, x-coordinate
**     Yt         double        telescope vector, y-coordinate
**     Zt         double        telescope vector, z-coordinate
**     Ga         double        guiding correction, collimation
**     Gb         double        guiding correction, pitch
**     Rnogo      double        mount pole avoidance radius
**
**   TARGET group (Note 5)
**     M_tar_t0   double        target reference time
**     M_tar_p0   double[2]     target coordinates at reference time
**     M_tar_dt   double[2]     target differential rates
**
**   POINTING ORIGIN group (Note 6)
**     Fl         double        focal length
**     M_por_p    double[2]     pointing-origin
**
**   FIELD ORIENTATION group (Note 7)
**     Sia        double        sine of instrument alignment angle
**     Cia        double        cosine of instrument alignment angle
**     Pai        double        instrument position-angle
**     Jf         int           optimization: 0=slit, else=field
**
**   TRANSFORM group (Note 8)
**     M_cosys    FRAMETYPE     frame for mount control
**     M_spm1     double[3][3]  mount SPM #1
**     M_spm2     double[3][3]  mount SPM #2
**     R_cosys    FRAMETYPE     frame for rotator control
**     R_spm1_i   double[3][3]  rotator inverse SPM #1
**     R_spm2_i   double[3][3]  rotator inverse SPM #2
**
**  Returned (Notes 9,10):
**     roll       double*       mount roll (righthanded "south"-zero)
**     pitch      double*       mount pitch
**     rota       double*       rotator angle
**
**  Defined in tcsmac.h:
**     PI         double        Pi
**     PI2        double        2Pi
**     FRAMETYPE  enum          frame types
**     ROTLOC     enum          rotator locations
**
**  Called:  tcsTrack, tcsRotator
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
**      0000001     1      update the rotator achieved position/velocity
**      0000010     2      update the sidereal time parameters
**      0000100     4      update the pointing model coefficients
**      0001000     8      update the target position
**      0010000    16      update the pointing origin
**      0100000    32      update the field orientation
**      1000000    64      update the transformation matrices
**
**     Bits above 1111111 (decimal 127) are ignored.
**
**     Examples:
**
**        mode              action
**
**          0       calculate new mount and rotator coordinates
**          2       store new ST parameters in the context
**          8       supply new RA,Dec
**         64       update the transformations
**         72       new target and transformation
**        127       update the whole context
**
**     The "calculate new coordinates" action is intended to be
**     invoked at a regular frequency of no less than 5 Hz, preferably
**     10 Hz and ideally 20 Hz.  The higher the frequency, the more
**     immediate the response to guiding and offsetting demands.
**
**     The tai argument is accessed only if mode = 0.
**
**   2 The rotator readings, the source of which is highly dependent
**     on the particular TCS implementation, enable the pointing
**     calculation to estimate  the orientation for the time to which
**     its predictions apply.  The information is needed in order
**     to calculate where to point the mount so that the star remains
**     in position even when the rotator is moving.
**
**     If there is no rotator, these parts of the context, once
**     initialized, need not be touched again.
**
**     The focal station has to be identified in order to apply the
**     appropriate field rotation.  If there is no rotator, OTA, the
**     simplest case, should be specified.
**
**   3 The time parameters enable fast computation of the Local Apparent
**     Sidereal Time and the Terrestrial Time by the pointing kernel.
**     The parameters must be supplied by the host application.  Once
**     every five minutes is more than often enough.
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
**     done all in one call (mode=72) to ensure consistency.
**
**   6 The pointing-origin (where in the focal plane we want the image
**     of the target to be) will need to be updated whenever a
**     "beamswitch" (movement of the image in the focal plane without
**     the target coordinates or the pointing model changing) is
**     requested.  For most types of observation, however, it will be
**     calibrated at the beginning of the session and left alone.
**
**     The pointing-origin coordinates are in the same units as the
**     focal length.
**
**   7 The field orientation (how the instrument is oriented with
**     respect to the rotator and the sky respectively) will need to be
**     updated whenever the image orientation is to be adjusted.  In
**     most cases this will be established at the beginning of the
**     session and left alone.
**
**     The field orientation is specified in the following way:
**
**     . The user has chosen some direction on the instrument that is
**       convenient to work with.  This is called the Instrument
**       Principal Direction (IPD).  A typical choice of IPD would be
**       the pixel +y direction on a CCD.
**
**     . Through either mechanical preparation or calibration, the user
**       has provided the orientation of the IPD with respect to the +y
**       axis of the instrument rotator.  This angle is called the
**       Instrument Alignment Angle (IAA), and it is supplied to the
**       present routine in the form of sin(IAA) and cos(IAA).
**
**     . The user then specifies what position-angle on the sky the IPD
**       is to assume.  This called the Instrument Position-Angle (IPA)
**       and is supplied to the present routine directly.
**
**     . Two slightly different field rotation compromises are
**       available, suitable for instruments with a slit and a 2D field
**       respectively.  "Field-optimized" produces a rotator angle that
**       does not favor the IPD itself but minimizes field rotation
**       overall.  The TCS might allow this choice to be made
**       dynamically, to suit the current instrument, and an appropriate
**       Jf argument passed to this routine.  In default, use Jf=1.
**
**     The rotator demand that the present routine generates is called
**     the Rotator Mechanical Angle (RMA).  It achieves the requested
**     IPA at the pointing-origin and in the specified frame.
**
**   8 The transformations will be updated every few seconds by the
**     "medium" process running in the host, and summarize the pointing
**     across the patch of sky at which the telescope is being aimed.
**     Included in these transformations are any pointing-model
**     adjustments which affect the roll axis misalignment,
**     complementing the other model terms (see the previous note).
**
**   9 The mount and rotator demands are timetagged and should be
**     regarded as samples of a trajectory rather than simply the
**     position for "now".  The servo controller software would use two
**     or more such samples to interpolate or extrapolate the required
**     position for the current time.
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
**     pi-Az for an altazimuth mount.  It is in the range +/-pi.  Where
**     the mechanical range is greater than 360 deg, for example where
**     there is a cable wrap, selection of the correct range must take
**     place outside the present routine.
**
**     ***  It is the host application's responsibility not to  ***
**     ***  enable the calculation of mount coordinates until   ***
**     ***  all of the context has been initialized.            ***
**
**  Latest revision:   4 May 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

#define SPIN 6.30038809892                   /* HA change per SI day */

{

/*--------- The context for the fast process -------------------------------*/

/* ROTATOR: achieved rotator position & velocity */
   static ROTLOC rotl;           /* focal station */
   static double rmat;           /* timestamp for rma and rmav */
   static double rma;            /* achieved rotator angle at time rmat */
   static double rmav;           /* rotator velocity at time rmat */

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
   static FRAMETYPE r_cosys;     /* frame for rotator control */
   static double r_spm1_i[3][3]; /* rotator inverse SPM #1 */
   static double r_spm2_i[3][3]; /* rotator inverse SPM #2 */

/* TARGET: what place in the sky is to be imaged */
   static double m_tar_t0;       /* target reference time (TAI MJD) */
   static double m_tar_p0[2];    /* target coordinates at reference time */
   static double m_tar_dt[2];    /* target differential rates */

/* POINTING-ORIGIN: where the image is to arrive in the focal plane */
   static double fl;             /* focal length */
   static double m_por_p[2];     /* pointing-origin (units as for fl) */

/* FIELD ORIENTATION: which way up the image is to be */
   static double sia;            /* sine of Instrument Alignment Angle */
   static double cia;            /* cosine of Instrument Alignment Angle */
   static double pai;            /* Instrument Position Angle */
   static int jf;                /* Optimization: 0=slit, else=field */

/* LATEST DEMANDS and their derivatives */
   static double tlast = 0.0;    /* timestamp */
   static int islast = 0;        /* above/below pole */
   static double adp = 0.0;      /* roll demand */
   static double adv = 0.0;      /* derivative of adp */
   static double bdp = 0.0;      /* pitch demand */
   static double bdv = 0.0;      /* derivative of bdp */
   static double rdp = 0.0;      /* rotator demand */
   static double rdv = 0.0;      /* derivative of rdp */

/*--------------------------------------------------------------------------*/

/* Extrapolated demands */
   double adpx;                    /* predicted roll */
   double bdpx;                    /* predicted pitch */
   double rdpx;                    /* predicted rotator */

/* Target vectors */
   double tar[2];                  /* spherical coordinates (final) */
   double xa, ya, za;              /* AIM vector */

   int i, j;
   double dt, st, sst, cst, rotax, dtlast, dtdt, xr, yr,
          ad1, bd1, ad2, bd2, ad, bd, rd;



/*
**  --------------
**  UPDATE CONTEXT
**  --------------
*/

   if ( mode & 1 ) {

   /* Update ROTATOR context. */

      rotl = Rotl;
      rmat = Rmat;
      rma = Rma;
      rmav = Rmav;
   }

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

   if ( mode & 16 ) {

   /* Update POINTING-ORIGIN context. */

      fl = Fl;
      for ( i = 0; i < 2; i++ ) {
         m_por_p[i] = M_por_p[i];
      }
   }

   if ( mode & 32 ) {

   /* Update FIELD ORIENTATION context. */

      sia = Sia;
      cia = Cia;
      pai = Pai;
      jf = Jf;
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
      r_cosys = R_cosys;
      for ( j = 0; j < 3; j++ ) {
         for ( i = 0; i < 3; i++ ) {
            r_spm1_i[j][i] = R_spm1_i[j][i];
         }
      }
      for ( j = 0; j < 3; j++ ) {
         for ( i = 0; i < 3; i++ ) {
            r_spm2_i[j][i] = R_spm2_i[j][i];
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

   /* Predicted achieved rotator angle this time. */
      rotax = rma + ( tai - rmat ) * rmav;

   /* Time since previous iteration (days). */
      dtlast = tai - tlast;

   /* Extrapolated roll,pitch,rotator position demands next time. */
      adpx = adp + dtlast * adv;
      bdpx = bdp + dtlast * bdv;
      rdpx = rdp + dtlast * rdv;

   /* Differential tracking. */
      dtdt = tai - m_tar_t0;
      for ( i = 0; i < 2; i++ ) {
         tar[i] = m_tar_p0[i] + dtdt * m_tar_dt[i];
      }

   /*
   ** ---------------
   ** POINTING ORIGIN
   ** ---------------
   */

   /* Scale into natural units. */
      xr = m_por_p[0] / fl;
      yr = m_por_p[1] / fl;

   /*
   **
   ** -------------
   ** MOUNT DEMANDS
   ** -------------
   **
   */

      tcsTrack ( tar[0], tar[1],
                 m_spm1, m_cosys, sst, cst, m_spm2,
                 rotl, rotax, adpx, bdpx, xr, yr,
                 ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                 &xa, &ya, &za,
                 &ad1, &bd1, &ad2, &bd2, &j );

   /* (In this implementation we ignore status.) */

   /* Select the appropriate solution. */
      ad = isol ? ad2 : ad1;
      bd = isol ? bd2 : bd1;

   /*
   ** ---------------
   ** ROTATOR DEMANDS
   ** ---------------
   **
   */

      tcsRotator ( xa, ya, za, rotl, rdpx, isol, ad, bd, xr, yr,
                   ia, ib, np, xt, yt, zt, ga, gb, sia, cia,
                   r_spm1_i, r_cosys, sst, cst, r_spm2_i, pai, jf,
                   &rd, &j );

   /* (In this implementation we ignore status.) */

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
         rdv = ( rd - rdp ) / dtlast;
         if ( fabs ( rdv ) >= PI ) rdv -= rdv < 0.0 ? PI2 : - PI2;
      }

   /* Save the new timestamp and solution choice. */
      tlast = tai;
      islast = isol;

   /* Save and return the latest demands. */
      *roll = adp = ad;
      *pitch = bdp = bd;
      *rota = rdp = rd;

   }
}
