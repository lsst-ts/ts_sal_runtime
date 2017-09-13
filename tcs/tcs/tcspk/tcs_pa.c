#include <stdio.h>
#include <slalib.h>
#include "tcs.h"
#include "tcsmac.h"

int main ( )

/*
**  - - - - - - -
**   T C S _ P A
**  - - - - - - -
**
**  Demonstration of TCSpk pointing kernel:  determine the position
**  angle of the Instrument Principal Direction by sampling the
**  focal plane either side of the pointing origin.
**
**  Last revision:   4 May 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

#define MOUNT ALTAZ      /* Mount type for this demonstration */
#define RLOCN NASMYTH_L  /* Instrument rotator location */

/* Euler angles wrt terrestrial [Az,El] for generalized gimbal case */
#define GIM1Z 0.0        /* 1st rotation, about z-axis */
#define GIM2Y 0.0        /* 2nd rotation, about y-axis */
#define GIM3X 0.0        /* 3rd rotation, about x-axis */

{
/* Context */
#include "tcsctx.h"

   int i;
   double tai, aia, ra, dec, t, st, sst, cst, xim, yim, w, wx, wy, ra2, dec2;

/*
** --------------
** Initialization
** --------------
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
      if ( tcsAddtrm ( MAXTRM, NTROOM, "NRX", -7.0*AS2R,
         &nterms, coeffn, coform, model, coeffv ) <= 0 ) return -1;
      if ( tcsAddtrm ( MAXTRM, NTROOM, "NRY", 4.0*AS2R,
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
   rma = 0.0*D2R;    /* Rotator angle (n.b. achieved, NOT demanded) */
   rmav = 0.0;       /* Velocity (achieved). */
   rmat = 0.0;       /* Timestamp. */

/*
** ------------------------------------------------
** Run the SLOW routine for the first of many times
** ------------------------------------------------
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
             sia, cia, pai, 0,
             m_cosys, m_spm1, m_spm2, r_cosys, r_spm1_i, r_spm2_i,
             &roll, &pitch, &rota );

/*
** --------------------------------------------------------
** Obtain a field-orientation as if from the user interface
** --------------------------------------------------------
*/

   aia = 10.0*D2R;         /* IAA */
   pai = 45.0*D2R;         /* IPA */
   sia = sin ( aia );      /* sin(IAA) */
   cia = cos ( aia );      /* cos(IAA) */
   jf = 0;                 /* slit-optimized */

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
*/

   npo = 1;
   m_por_p0[npo][0] = 180.0;
   m_por_p0[npo][1] = -150.0;
   m_por_ob[npo][0][0] = 0.0;
   m_por_ob[npo][0][1] = 0.0;

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
*/

   m_cosys = FK5;
   m_eqx = 2000.0;
   m_wavel = 0.5;
   r_cosys = m_cosys;
   r_eqx = m_eqx;
   m_tar_p0 [ 0 ] = 25.0 * D2R;
   m_tar_p0 [ 1 ] = 20.0 * D2R;
   m_tar_dt [ 0 ] = 0.0;
   m_tar_dt [ 1 ] = 0.0;
   m_tar_t0 = 0.0;
   m_tar_ob [ 0 ] [ 0 ] = 0.0*AS2R;
   m_tar_ob [ 0 ] [ 1 ] = 0.0*AS2R;

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
** --------------------------------------------------------
** Run the FAST routine before repeating the call to MEDIUM
** --------------------------------------------------------
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
*/

/* Read the clock */
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

   /* Make the rotator achieve the demand (immediately). */
      rmav = slaDrange ( rota - rma ) / ( 0.05 / 86400.0 );
      rmat = t;
      rma = rota;
      tcsFast ( ROTATOR, jbp, t,
                rotl, rmat, rma, rmav,
                t0, st0,
                ia, ib, np, xt, yt, zt, ga, gb, rnogo,
                m_tar_t0, m_tar_op0, m_tar_dt,
                fl, m_por_p,
                sia, cia, pai, jf,
                m_cosys, m_spm1, m_spm2, r_cosys, r_spm1_i, r_spm2_i,
                &roll, &pitch, &rota );
   }

/*
** ---------------------------------------------------------------
** Report the Position Angle of the Instrument Principal Direction
** ---------------------------------------------------------------
**
*/

/* Latest timestamp. */
   t = rmat;

/* Functions of LAST. */
   st = st0 + ( t - t0 ) * STRPD;
   sst = sin ( st );
   cst = cos ( st );

/* Scale the pointing-origin into natural units. */
   xim = m_por_p[0] / fl;
   yim = m_por_p[1] / fl;

/* Get the RA,Dec of two points along the IPD either side of the PO. */
   w = 1e-7;
   wx = w * sia;
   wy = w * cia;

   tcsVTsky ( roll, pitch, rotl, rma, xim - wx, yim - wy,
              m_spm1_i, m_cosys, sst, cst, m_spm2_i,
              ia, ib, np, xt, yt, zt, ga, gb,
              &ra, &dec );

   tcsVTsky ( roll, pitch, rotl, rma, xim + wx, yim + wy,
              m_spm1_i, m_cosys, sst, cst, m_spm2_i,
              ia, ib, np, xt, yt, zt, ga, gb,
              &ra2, &dec2 );

/* Report the position-angle. */
   printf ( "\nThe Instrument Principal Direction"
            " is at position-angle %+13.9f deg\n\n",
            slaDbear( ra, dec, ra2, dec2 ) / D2R );

   return 0;

}
