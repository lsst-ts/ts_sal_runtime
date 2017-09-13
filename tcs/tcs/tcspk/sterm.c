#include <string.h>

int tptScomp ( char*, char* );

int tcsSterm ( char cname[9], double cvalue,
               int maxtrm, int model[],
               char coeffn[][9], double coeffv[] )

/*
**  - - - - - - - - -
**   t c s S t e r m
**  - - - - - - - - -
**
**  Set the coefficient value for a specified pointing term.
**
**  Given (arguments):
**     cname    char[]    name of term
**     cvalue   double    new coefficient value
**     maxtrm   int       maximum number of terms in model
**     model    int[]     term numbers (0 = end)
**     coeffn   char[][]  names of coefficients
**     coeffv   double[]  values of coefficients
**
**  Returned (function value):
**                                 -1 = specified term is not in model
**              int        status:  0 = OK
**
**  Called:  tptScomp
**
**  Last revision:   24 July 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/
{
   int i, n;



/* Step term by term through the model. */
   for ( i = 0; i < maxtrm; i++ ) {

   /* Term number;  error exit of end of model. */
      if ( ! ( n = model[i] ) ) break;

   /* Is this the named term? */
      if ( ! tptScomp ( cname, coeffn[n-1] ) ) {

      /* Yes:  set the value and exit. */
         coeffv[i] = cvalue;
         return 0;
      }

/* Next term in model. */
   }

/* Specified model term does not exist. */
   return -1;

}
