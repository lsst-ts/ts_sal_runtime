#include <stdio.h>
#include <string.h>
#include "tcs.h"
#include "tcsmac.h"

int tcsIntpm ( char *file, int maxtrm, int ntroom,
               int model[], int *nterml, int *ntermx, int *nterms,
               char coeffn[][9], char coform[][9],
               double coeffv[] )
/*
**  - - - - - - - - -
**   t c s I n t p m
**  - - - - - - - - -
**
**  Replace the current pointing model with one read from a file.
**
**  The file must conform strictly to the format produced by the
**  OUTMOD command in the TPOINT package, except that certain records
**  and fields are ignored (Notes 1,2).
**
**  Given (arguments):
**     file     char[]    the name of the file to be read
**     maxtrm   int       maximum number of terms in model
**     ntroom   int       maximum number of terms in repertoire
**
**  Returned (arguments):
**     model    int[]     term numbers for current model (0 = end)
**     nterml   int*      number of local terms
**     ntermx   int*      number of terms implemented explicitly (loc+std)
**     nterms   int*      number of terms available currently (loc+std+gen)
**     coeffn   char[][]  coefficient names (local, standard, generic)
**     coform   char[][]  format of generic terms added to coeffn
**     coeffv   double[]  coefficient values
**
**  Returned (function value):
**              int       status:  0 = OK
**                                -1 = unable to initialize model
**                                -2 = unable to open input file
**                                -3 = I/O error or premature EOF
**                                -4 = unrecognized record
**                                -5 = unable to add term to model
**
**  Defined in tcsmac.h:
**     AS2R     double    arcseconds to radians
**
**  Notes:
**
**  1  The file containing the pointing model must, as far as the basic
**     layout is concerned, be exactly as written by the TPOINT's
**     OUTMOD command (which indeed is the ideal way of generating
**     the file).  However, unlike TPOINT's INMOD command, the present
**     routine does not support format changes and the insertion of
**     comment records.  The first two records, which are ignored, may
**     be used to record comments;  however, both must be present, as
**     must the END marker.  In the term records, the term name must
**     start in column 3, and the coefficient value must not start
**     before column 11.
**
**  2  Here is an example file (for an equatorial):
**
**            AAT  f/15  1979/06/11
**            T   49   1.1206   52.015  -0.0624
**              IH       +174.7543     1.18854
**             =ZH         +3.5100
**              ID        +23.0464     0.35693
**            &=HFX        +1.0000
**            &=HFD        +1.0000
**            & HF        -18.7283     0.48982
**            & X2HC       -3.1122     0.26477
**            & NP         +2.9636     0.79658
**            & CH        -18.6889     1.20785
**             =ZE         +0.7000
**            & ME        +58.2504     0.43977
**            & MA         +2.9518     0.24207
**              TF         +8.9655     0.54629
**            & TFP        +1.1686     0.47733
**            END
**
**     Note the two initial records, which must be present but which are
**     not interpreted, and the mandatory END record.  Each of the
**     remaining records defines a term and the corresponding
**     coefficient value (in arcseconds).  For example, the record
**
**            & ME        +58.2504     0.43977
**
**     defines a term called ME with a value of +58.2504 arcsec.  The
**     additional flag and number are ignored.
**
**  3  If any invalid record is detected, the pointing model
**     is reset and the rest of the input file is ignored.
**
**  Called:  tptMinit, tptScomp, tcsAddtrm
**
**  Last revision:   9 May 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

#define LSTRNG 81   /* Length of buf string */
#define LNAME 9     /* Length of name string */

{
   FILE* fp;
   char buf[LSTRNG], name[LNAME];
   double value;


/*
** Initialize the pointing model
** -----------------------------
*/

   if ( tptMinit ( maxtrm, ntroom, model,
                   nterml, ntermx, nterms, coeffn ) ) return -1;

/*
** Open the model file
** -------------------
*/

   if ( ( fp = fopen ( file, "r" ) ) == NULL ) return -2;

/*
** Read and ignore the caption record
** ----------------------------------
*/

   if ( fgets ( buf, LSTRNG, fp ) == NULL ) return -3;

/*
** Read and ignore the method, statistics and refraction record
** ------------------------------------------------------------
*/

   if ( fgets ( buf, LSTRNG, fp ) == NULL ) return -3;

/*
** Term records
** ------------
*/

   for ( ; ; ) {

   /* Read one record. */
      if ( fgets ( buf, LSTRNG, fp ) == NULL ) return -3;

   /* OK exit if end marker (mandatory). */
      if ( ! tptScomp ( buf, "END" ) ) {
         fclose ( fp );
         return 0;
      }

   /* Extract and decode the term name and coefficient value. */
      if ( sscanf ( buf+2, "%8s %lf", name, &value ) != 2 ) {

      /* If suspect, reset the model and error-exit. */
         model[0] = 0;
         fclose ( fp );
         return -4;
      }

   /* Add the term to the model. */
      if ( tcsAddtrm ( maxtrm, ntroom, name, value*AS2R, nterms,
                       coeffn, coform, model, coeffv ) <= 0 ) {

      /* Error exit if new term can't be added. */
         fclose ( fp );
         return -5;
      }
   }
}
