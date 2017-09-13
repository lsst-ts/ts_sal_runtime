#include <string.h>

int tcsIterm ( int iterm, int maxtrm, int model[], char coeffn[][9],
               double coeffv[], char cname[9], double *cvalue )

/*
**  - - - - - - - - -
**   t c s I t e r m
**  - - - - - - - - -
**
**  Inquire name and value for a term in the pointing model.
**
**  Given (arguments):
**     iterm    int       number of term to inquire (first = 1)
**     maxtrm   int       maximum number of terms in model
**     model    int[]     term numbers (0 = end)
**     coeffn   char[][]  names of coefficients
**     coeffv   double[]  values of coefficients
**
**  Returned (arguments):
**     cname    char[]    name of inquired term
**     cvalue   double*   value of inquired term
**
**  Returned (function value):
**                                 -1 = specified term does not exist
**              int        status:  0 = OK
**
**  Last revision:   24 July 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/
{
   int n, i, m;



/* Count the number of terms in the model. */
   for ( n = 0; model[n] && n < maxtrm; n++ );

/* Look up the specified term. */
   if ( iterm > 0 && iterm <= n ) {
      i = iterm - 1;
      m = model[i] - 1;
      strncpy ( cname, coeffn[m], 9 );
      cname[8] = (char) '\0';
      *cvalue = coeffv[i];

   /* OK exit. */
      return 0;

   } else {

   /* Specified model term does not exist. */
      return -1;
   }
}
