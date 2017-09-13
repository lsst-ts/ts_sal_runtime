#include <slalib.h>
#include "tcs.h"

int tcsPup ( int maxtrm, int model[], double coeffv[],
             int nterml, int ntermx, int nterms,
             char coeffn[][9], char coform[][9],
             MTYPE mount, double ae2nm[3][3], double roll, double pitch,
             int jbp, double aux[3], double tlat,
             double *ia, double *ib, double *np,
             double *xt, double *yt, double *zt, double ae2mt[3][3] )

/*
**  - - - - - - -
**   t c s P u p
**  - - - - - - -
**
**  Update the pointing model.
**
**  Given:
**     maxtrm  int             maximum number of terms in model
**     model   int[]           term numbers for current model (0 = end)
**     coeffv  double[]        coefficient values
**     nterml  int             number of local terms
**     ntermx  int             number of terms implemented explicitly (loc+std)
**     nterms  int             number of terms avail. currently (loc+std+gen)
**     coeffn  char[][9]       coefficient names (local, standard, generic)
**     coform  char[][9]       format of generic term
**     mount   MTYPE           mount type
**     ae2nm   double[3][3]    rotation matrix, [Az,El] to nominal mount
**     roll    double          demand mount roll (radians, righthanded)
**     pitch   double          demand mount pitch (radians)
**     jbp     int             TRUE = "below the pole"
**     aux     double[3]       auxiliary readings
**     tlat    double          telescope latitude (true)
**
**  Returned (arguments):
**     ia      double*         roll zero point
**     ib      double*         pitch zero point
**     np      double*         mount axes nonperpendicularity
**     xt      double*         telescope vector, x-component (Note 2)
**     yt      double*         telescope vector, y-component (Note 2)
**     zt      double*         telescope vector, z-component (Note 2)
**     ae2mt   double[3][3]    rotation matrix, [Az,El] to mount
**
**  Returned (function value):
**             int             0 = OK
**
**  Defined in tcs.h:
**     MTYPE   enum            mount type codes
**     EQUAT   MTYPE           equatorial
**     ALTAZ   MTYPE           altazimuth
**
**  Called:  slaDcs2c, slaDimxv, tcsPmt, tptPterm
**
**  Notes:
**
**  1  The chained/parallel option for the TPOINT pointing terms is
**     not supported by the present routine.  The model is built by
**     starting with the latest mount demands and calculating each
**     term as a function of the current coordinates, as affected by
**     the previous terms.  The resulting 7-term "summary" model is
**     then used by starting with the observed place and working
**     towards demanded mount roll and pitch.  The TPOINT options
**     that provide the best match to this behaviour are "adjust
**     telescope" and "all terms chained".
**
**  2  The TELESCOPE vector [xt,yt,zt] is in this frame:
**
**       x-axis:  at right angles to both the roll and pitch axes
**       y-axis:  along the pitch axis
**       z-axis:  at right angles to the other two axes
**
**     In the absence of either collimation error or vertical deflection
**     the TELESCOPE vector is [1,0,0].
**
**  Last revision:   4 May 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

#define METHOD 1

{

/*
**  The array "pmodel", which receives data from the function tptPterm,
**  is a list of seven coefficients which comprise a basic pointing
**  model:
*/
   double pmodel[7];
/*                                            term names
**     element    meaning               equatorial     other
**
**      [0,1]   index errors              -IH,ID       IA,IE
**       [2]    vertical error             FLOP        FLOP
**       [3]    collimation error          -CH          CA
**       [4]    nonperpendicularity        -NP         NPAE
**      [5,6]   misalignment              -MA,ME       AW,AN
**
**  This 7-term basic model combines the contributions from all the
**  terms in the actual, operational, model.
*/

   int i, n, j;
   double slat, clat, vw[3], x, z, vc[3];



/* Functions of telescope latitude. */
   slat = sin ( tlat );
   clat = cos ( tlat );

/* Reset the basic model. */
   for ( i = 0; i < 7; i++ ) {
      pmodel[i] = 0.0;
   }

/* Mount vector, which we want to express as [-HA,Dec]. */
   slaDcs2c ( roll, pitch, vw );

/* Already [-HA,Dec]? */
   if ( mount != EQUAT ) {

   /* No.  Already [Az,El]? */
      if ( mount != ALTAZ ) {
      /* No (i.e. gimbal), so mount to [Az,El]. */
         slaDimxv ( ae2nm, vw, vw );
      }

   /* [Az,El] to [-HA,Dec]. */
      x = vw[0];
      z = vw[2];
      vw[0] = slat * x + clat * z;
      vw[2] = - clat * x + slat * z;
   }

/* Copy the working vector to the current vector. */
   vc[0] = vw[0];
   vc[1] = vw[1];
   vc[2] = vw[2];

/* Apply the operational model, term by term, building pmodel. */
   for ( i = 0; i < maxtrm; i++ ) {
      if ( ( n = model[i] ) ) {

      /* Apply one term. */
         if ( ( j = tptPterm ( n, coeffv[i], aux, jbp, vw, slat, clat,
                               mount, ae2nm,
                               nterml, ntermx, nterms, coeffn, coform, METHOD,
                               vc, pmodel ) ) ) return j;

      /* Chain the term to the next one by updating the working vector. */
         vw[0] = vc[0];
         vw[1] = vc[1];
         vw[2] = vc[2];

      } else {
         break;
      }
   }

/* Obtain the final (best estimate) observed [Az,El] vector -> vw. */
   vw[0] = slat * vc[0] - clat * vc[2];
   vw[1] = vc[1];
   vw[2] = clat * vc[0] + slat * vc[2];

/* Translate the model into the required form. */
   return tcsPmt ( pmodel, ae2nm, vw, jbp, ia, ib, np, xt, yt, zt, ae2mt );

}
