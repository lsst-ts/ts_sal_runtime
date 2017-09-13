void tcsPorup ( double por_p0[2], double por_ob[3][2], double por_p[2] )
/*
**  - - - - - - - - -
**   t c s P o r u p
**  - - - - - - - - -
**
**  The pointing-origin x,y coordinates are updated, taking into account
**  offsets from base.
**
**  Given:
**     por_p0   double[2]      base pointing-origin x,y
**     por_ob   double[3][2]   offsets from base
**
**  Returned:
**     por_p    double[2]      current pointing-origin x,y
**
**  Last revision:   2 January 2003
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

{
   int i, iob;


/* Pointing-origin x then y. */
   for ( i = 0; i < 2; i++ ) {

   /* Base. */
      por_p[i] = por_p0[i];

   /* Add the offsets from base. */
      for ( iob = 0; iob < 3; iob++ ) {
         por_p[i] += por_ob[iob][i];
      }
   }
}
