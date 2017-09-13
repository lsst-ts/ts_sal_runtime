#include <slalib.h>
#include "tcs.h"

void tcsSlow ( double tai, double delut, double delat,
               double ttmtai, double temp, double press, double humid,
               double wavelr, double tlong,
               double* t0, double* st0, double* tt0, double* ttj,
               double amprms[21], double* refa, double* refb )

/*
**  - - - - - - - -
**   t c s S l o w
**  - - - - - - - -
**
**  The SLOW process.
**
**  Updates things which are slowly-changing and target independent.
**
**  Given:
**     tai      double      time (TAI Modified Julian Date, JD-2000000.5)
**     delut    double      current UT1-UTC (day)
**     delat    double      TAI-UTC (day)
**     ttmtai   double      TT-TAI (day)
**     temp     double      ambient temperature (K)
**     press    double      pressure (mB)
**     humid    double      relative humidity (0-1)
**     tlr      double      tropospheric lapse rate (K per metre)
**     wavelr   double      reference wavelength (micrometres)
**     tlong    double      telescope longitude (true)
**
**  Returned:
**     t0       double*     reference time (TAI MJD)
**     st0      double*     LAST at reference time (radians)
**     tt0      double*     TT at reference time (MJD)
**     ttj      double*     TT at reference time (Julian time)
**     amprms   double[21]  target-independent MAP parameters
**     refa     double*     tan refraction constant
**     refb     double*     tan^3 refraction constant
**
**  Called:  slaEpj, slaDranrm, slaGmsta, slaEqeqx, slaMappa, slaRefcoq
**
**  Last revision:   12 March 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{
   double tt, d;



/* The reference time for the fast LAST and TT calculation. */
   *t0 = tai;

/* TT (MJD). */
   tt = tai + ttmtai;
   *tt0 = tt;

/* TT (Julian Epoch). */
   *ttj = slaEpj ( tt );

/* LAST (radians). */
   d = floor ( tai );
   *st0 = slaDranrm ( slaGmsta ( d, ( tai - d ) - delat + delut )
                      + tlong + slaEqeqx ( tt ) );

/* Target-independent mean to apparent place parameters. */
   slaMappa ( 2000.0, tt, amprms );

/* Refraction parameters. */
   slaRefcoq ( temp, press, humid, wavelr, refa, refb );
}
