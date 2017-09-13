#include <stdio.h>
#include <slalib.h>
#include "tcs.h"
#include "tcsmac.h"

int main ( )

/*
**  - - - - - - - - -
**   T C S _ T E S T
**  - - - - - - - - -
**
**  Test of TCSpk pointing kernel.
**
**  The MEDIUM and FAST pointing routines are repeatedly executed at
**  a fixed absolute time until a stable result is achieved.  The
**  results can then be used to verify the correctness of other
**  pointing kernel architectures.
**
**  To switch between the equatorial, altazimuth and generalized
**  gimbal cases, edit the macro MOUNT to either "ALTAZ", "EQUAT"
**  or "GIMBAL".
**
**  Last revision:   24 November 2006
**
**  Copyright P.T.Wallace, D.L.Terrett.  All rights reserved.
*/

#define MOUNT ALTAZ      /* Mount type for this demonstration */
#define RLOCN COUDE_R    /* Instrument rotator location */

/* Euler angles wrt terrestrial [Az,El] for generalized gimbal case */
#define GIM1Z 0.0        /* 1st rotation, about z-axis */
#define GIM2Y 0.0        /* 2nd rotation, about y-axis */
#define GIM3X 0.0        /* 3rd rotation, about x-axis */

{
/* Context */
#include "tcsctx.h"

   int i, i4[4];
   char s;
   double tai, aia, ra, dec, t, st;


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
      if ( tptMinit ( MAXTRM, NTROOM, model,
                      &nterml, &ntermx, &nterms, coeffn ) ) return -1;
   } else {

/* Altazimuth case:  demonstrate initialization by explicit calls. */
      if ( tptMinit ( MAXTRM, NTROOM, model,
                      &nterml, &ntermx, &nterms, coeffn ) ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "IA", 100.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "IE", -30.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "TF", 10.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "CRX", 15.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "CRY", 45.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "NRX", 25.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "NRY", -15.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "CA", -110.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "NPAE", 8.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "AW", -5.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "AN", -12.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
   }

/* Guiding adjustments. */
   ga = 0.0*AS2R;
   gb = 0.0*AS2R;

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
   tcsMedium ( tai, MAXTRM, model, coeffv, nterml, ntermx, nterms,
               coeffn, coform, mount, ae2nm, roll, pitch, jbp, aux,
               m_cosys, m_eqx, m_wavel, r_cosys, r_eqx, r_wavel, m_tar_p,
               t0, st0, ttj, temp, press, humid, tlr, wavelr,
               refa, refb, NULL, hm, tlat, diurab, amprms,
               &ia, &ib, &np, &xt, &yt, &zt, ae2mt,
               m_spm1, m_spm1_i, m_spm2, m_spm2_i,
               r_spm1, r_spm1_i, r_spm2, r_spm2_i );

/* Tell the FAST process about everything initialized so far. */
   tcsFast ( ALL, jbp, tai,
             rotl, rmat, rma, rmav,
             t0, st0,
             ia, ib, np, xt, yt, zt, ga, gb, rnogo,
             m_tar_t0, m_tar_op0, m_tar_dt,
             fl, m_por_p,
             sia, cia, pai, jf,
             m_cosys, m_spm1, m_spm2, r_cosys, r_spm1_i, r_spm2_i,
             &roll, &pitch, &rota );

/*
** --------------------------------------------------------
** Obtain a field-orientation as if from the user interface
** --------------------------------------------------------
**
** This demonstration uses hardwired constants.  An operational
** system would obtain the Instrument Alignment Angle (IAA) and the
** Instrument Position Angle (IPA) from the user in a variety
** of ways, and would then set up the following context variables:
**
**    pai        double      IPA
**    sia, cia   double      sine and cosine of IAA
**    jf         int          optimization: 0=slit, else=field
*/

   aia = 0.0;              /* IAA */

   pai = 0.0;              /* IPA */
   sia = sin ( aia );      /* sin(IAA) */
   cia = cos ( aia );      /* cos(IAA) */
   jf = 1;                 /* field-optimized */

/* Tell the FAST process. */
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

/* Tell the FAST process. */
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
**    r_cosys    double       rotator frame
**    r_eqx      double       rotator equinox
**    m_tar_p0   double[2]    [RA,Dec] or [Az,El]
**    m_tar_dt   double[2]    differential rates
**    m_tar_t0   double       reference time
**    m_tar_ob   double[3][2] offsets from base
**
** The frame in which the rotator is being controlled is dealt
** with here in addition to the target.
*/

   m_cosys = FK4;
   m_eqx = 1975.0;
   m_wavel = 0.5;
   r_cosys = m_cosys;
   r_eqx = m_eqx;
   r_wavel = m_wavel;
   m_tar_p0 [ 0 ] = 0.8890707209659084;
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

/* Now run the MEDIUM process to generate the new pointing model and SPMs. */
   tcsMedium ( tai, MAXTRM, model, coeffv, nterml, ntermx, nterms,
               coeffn, coform, mount, ae2nm, roll, pitch, jbp, aux,
               m_cosys, m_eqx, m_wavel, r_cosys, r_eqx, r_wavel, m_tar_p,
               t0, st0, ttj, temp, press, humid, tlr, wavelr,
               refa, refb, NULL, hm, tlat, diurab, amprms,
               &ia, &ib, &np, &xt, &yt, &zt, ae2mt,
               m_spm1, m_spm1_i, m_spm2, m_spm2_i,
               r_spm1, r_spm1_i, r_spm2, r_spm2_i );

/* Report the target. */
   slaDr2tf ( 4, slaDranrm ( m_tar_p0[0] ), &s, i4 );
   printf ( "\nRA = %2.2i %2.2i %2.2i.%4.4i  ", i4[0], i4[1], i4[2], i4[3] );
   slaDr2af ( 3, m_tar_p0[1], &s, i4 );
   printf ( "Dec = %c%2.2i %2.2i %2.2i.%3.3i  <- test star\n",
                                             s, i4[0], i4[1], i4[2], i4[3] );
   slaDr2tf ( 4, slaDranrm ( m_tar_ob[0][0] ), &s, i4 );
   printf ( "    %c%2.2i %2.2i %2.2i.%4.4i  ",
                                             s, i4[0], i4[1], i4[2], i4[3] );
   slaDr2af ( 3, m_tar_ob[0][1], &s, i4 );
   printf ( "      %c%2.2i %2.2i %2.2i.%3.3i  <- offset\n",
                                             s, i4[0], i4[1], i4[2], i4[3] );

/* Tell the FAST process about the new target and SPMs. */
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
** must be taken to communicate the new information to the FAST process.
**
** Whenever a completely new target is supplied, one that may involve
** a change of reference frame or a position in the sky outside the
** valid range of the current SPMs, the new target and new SPMs must
** be communicated to the FAST process as an atomic unit.
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

/* Execute the medium and fast loops a number of times. */
   for ( i = 0; i < 100; i++ ) {

/* Now run the MEDIUM process to generate updated pointing coefficients. */
      tcsMedium ( tai, MAXTRM, model, coeffv, nterml, ntermx, nterms,
                  coeffn, coform, mount, ae2nm, roll, pitch, jbp, aux,
                  m_cosys, m_eqx, m_wavel, r_cosys, r_eqx, r_wavel, m_tar_p,
                  t0, st0, ttj, temp, press, humid, tlr, wavelr,
                  refa, refb, NULL, hm, tlat, diurab, amprms,
                  &ia, &ib, &np, &xt, &yt, &zt, ae2mt,
                  m_spm1, m_spm1_i, m_spm2, m_spm2_i,
                  r_spm1, r_spm1_i, r_spm2, r_spm2_i );

   /* Finally tell the FAST process about the updated pointing model and SPMs. */
      tcsFast ( TRANSFORM + MODEL, jbp, tai,
                rotl, rmat, rma, rmav,
                t0, st0,
                ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                m_tar_t0, m_tar_op0, m_tar_dt,
                fl, m_por_p,
                sia, cia, pai, jf,
                m_cosys, m_spm1, m_spm2, r_cosys, r_spm1_i, r_spm2_i,
                &roll, &pitch, &rota );

      /* Read the clock */
         (void) tcsTime ( &tai );

         t = tai;

      /* Ask the FAST process to calculate new demands. */
         tcsFast ( 0, jbp, t,
                   rotl, rmat, rma, rmav,
                   t0, st0,
                   ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                   m_tar_t0, m_tar_op0, m_tar_dt,
                   fl, m_por_p,
                   sia, cia, pai, jf,
                   m_cosys, m_spm1, m_spm2, r_cosys, r_spm1_i, r_spm2_i,
                   &roll, &pitch, &rota );
   }

/* Print results. */
   printf ( "\ntimestamp       = %23.10f MJD (TAI)\n", t );

   printf ( "Roll demand     = %15.13f (%15.10f degrees )\n", roll,
            roll / D2R );
   printf ( "Pitch demand    = %15.13f (%15.10f degrees )\n", pitch,
            pitch / D2R );
   printf ( "Rotator demand  = %15.13f (%15.10f degrees )\n", rota,
            rota / D2R );

/*
** ---------------------------------------
** Demonstrate the upstream transformation
** ---------------------------------------
*/

   st = st0 + ( t - t0 ) * STRPD;
   tcsVTsky ( roll, pitch, rotl, rma, m_por_p[0] / fl, m_por_p[1] / fl,
              m_spm1_i, m_cosys, sin ( st ), cos ( st ), m_spm2_i,
              ia, ib, np, xt, yt, zt, ga, gb,
              &ra, &dec );

   slaDr2tf ( 4, slaDranrm ( ra ), &s, i4 );
   i4[0] = i4[0] % 24;
   printf ( "\nRA = %2.2i %2.2i %2.2i.%4.4i  ", i4[0], i4[1], i4[2], i4[3] );
   slaDr2af ( 3, dec, &s, i4 );
   printf ( "Dec = %c%2.2i %2.2i %2.2i.%3.3i  <- from upstream calculation\n",
                                             s, i4[0], i4[1], i4[2], i4[3] );

   return 0;

}
