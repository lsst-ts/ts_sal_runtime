void tcsTargup ( double tai, double tar_t0, double tar_p0[2],
                 double tar_dt[2], double tar_ob[3][2],
                 double tar_op0[2], double tar_p[2] )
/*
**  - - - - - - - - - -
**   t c s T a r g u p
**  - - - - - - - - - -
**
**  The target coordinates are updated, taking into account
**  differential tracking and offsets from base.
**
**  Given:
**     tai      double        time (TAI MJD = JD-2400000.5)
**     tar_t0   double        reference time (TAI MJD)
**     tar_p0   double[2]     position at reference time (spherical
**                                 coordinates, e.g. RA,Dec, in radians)
**     tar_dt   double[2]     differential rates (radians/day)
**     tar_ob   double[3][2]  offset(s) from base (radians)
**
**  Returned:
**     tar_op0  double[2]     target coordinates at reference time
**     tar_p    double[2]     current target coordinates
**
**  Note:
**     The coordinates tar_op0 include offsets from base but do not
**     include the effects of differential tracking.  The coordinates
**     tar_p include both.
**
**  Last revision:   12 March 2003
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{
   double dt;
   int i, iob;


/* Time interval for differential tracking. */
   dt = tai - tar_t0;

/* Do each coordinate separately. */
   for ( i = 0; i < 2; i++ ) {

   /* The base position at the reference time. */
      tar_op0[i] = tar_p0[i];

   /* Add in the offsets from base. */
      for ( iob = 0; iob < 3; iob++ ) {
         tar_op0[i] += tar_ob[iob][i];
      }

   /* Include differential tracking. */
      tar_p[i] = tar_op0[i] + dt * tar_dt[i];
   }

}
