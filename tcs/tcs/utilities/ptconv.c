#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <slalib.h>

/*--------------------------------------------------------------------------*/

int main ( )
/*
**  - - - - - - -
**   p t c o n v
**  - - - - - - -
**
**  Convert tpk pointing-test data into TPOINT format.
**
**  I/O:
**     stdin    input    pointing-test file generated by tpk
**     stdout   output   TPOINT/INDAT file
**     stderr   output   error messages
**
**  Last revision:  15 November 2006
**
**  Copyright 2006 CCLRC and P.T.Wallace and D.L.Terrett.
*/

/*--------------------------------------------------------------------------*/

#define PI     3.14159265358979323846    /* Pi */
#define D90    (PI/2.0)                  /* 90 degrees in radians */
#define D2R    (PI/180.0)                /* Degrees to radians */
#define AS2R   (PI/648000.0)             /* Arcseconds to radians */
#define S2DAYS (1.0/86400.0)             /* Seconds to days */

#define LS 80                            /* Default length of strings */

#define EQUAT 1                          /* equatorial */
#define ALTAZ 2                          /* altazimuth */
#define GIMBAL 3                         /* generalized gimbal */

/*--------------------------------------------------------------------------*/

{
   FILE *fp;
   char buf [ LS ], c, *id, *val;
   int n, i, idmsf [ 4 ], num, ill, nmin, nmax;
   size_t nc, ic;
   double w, djmtai, djmtt, djmutc, ra, da,
          as, zs, h, d, r, tlong, tlat, daz,
          ae2nm[3][3], es, spa, cpa, xr, yr, xi, eta, am, em, 
          sm[3], s[3], s1, s2,
          am2, em2, m[3], ae[3], az, el;

/*
** Global parameters
** -----------------
*/

/* Strings */
   char date [ LS ], utc [ LS ], tel [ LS ];
   struct {
      char *id;       /* identifier */
      int exist;      /* presence flag */
      char *value;    /* value */
   } globc [ ] = {
      {"DATE",    0, NULL},
      {"UTC",     0, NULL},
      {"TELNAME", 0, NULL}
   };

/* Synonyms */
#define DATE     globc[0].value    /* Calender data. */
#define UTC      globc[1].value    /* UTC. */
#define TELNAME  globc[2].value    /* Telescope name. */
#define TELNAME_EXIST globc[2].exist

/* Number of string global parameters */
#define NGLOBC (sizeof globc / sizeof globc [ 0 ] )

/* Numbers */
   struct {
      char *id;       /* identifier */
      int exist;      /* presence flag */
      double value;   /* value */
      double vmin;    /* minimum accepted (given units) */
      double vmax;    /* maximum accepted (given units) */
      double factor;  /* conversion factor, given units to working units */
   } globn [ ] = {
      {"TLATM",  0, 0.0,  -90.0,  90.0, D2R},
      {"TLONGM", 0, 0.0, -360.0, 360.0, D2R},
      {"HEIGHT", 0, 0.0,    0.0,   5e3, 1.0},
      {"XPM",    0, 0.0,  -10.0,  10.0, AS2R},
      {"YPM",    0, 0.0,  -10.0,  10.0, AS2R},
      {"TTMTAI", 0, 0.0,   -1e2, 100.0, S2DAYS},
      {"DJMLS",  0, 0.0,    0.0,  1e30, 1.0},
      {"DELAT",  0, 0.0,    0.0, 100.0, S2DAYS},
      {"DELUT",  0, 0.0,  -10.0,  10.0, 1.0},
      {"MTYPE",  0, 0.0,    1.0,   3.0, 1.0},
      {"GIM1Z",  0, 0.0,    0.0, 360.0, D2R},
      {"GIM2Y",  0, 0.0,    0.0, 360.0, D2R},
      {"GIM3X",  0, 0.0,    0.0, 360.0, D2R},
      {"VERSION", 0, 0.0,   1.0, 1.1, 1.0}
   };

/* Number of numeric global parameters */
#define NGLOBN (sizeof globn / sizeof globn [ 0 ] )

/* Synonyms */
#define TLATM   globn[0].value    /* Mean geodetic latitude (radians) */
#define TLONGM  globn[1].value    /* Mean longitude, (radians, east +ve) */
#define HM      globn[2].value    /* Height AMSL (metres) */
#define XP      globn[3].value    /* Polar motion x-component (radians) */
#define YP      globn[4].value    /* Polar motion y-component (radians) */
#define TTMTAI  globn[5].value    /* TT minus TAI (days) */
#define DJMLS   globn[6].value    /* MJD of next UTC leap second */
#define DELAT   globn[7].value    /* UTC-TAI (days, prior to DJMLS) */
#define DELUT   globn[8].value    /* UT1-UTC (sec, prior to DJMLS) */
#define MTYPE   globn[9].value    /* Mount type */
#define MTYPE_EXIST globn[9].exist
#define GIM1Z   globn[10].value   /* First gimbal angle */
#define GIM1Z_EXIST globn[10].exist
#define GIM2Y   globn[11].value   /* Second gimbal angle */
#define GIM2Y_EXIST globn[11].exist
#define GIM3X   globn[12].value   /* Third gimbal angle */
#define GIM3X_EXIST globn[12].exist
#define VERSION globn[13].value   /* File format version */


/*
** Per-observation parameters
** --------------------------
*/

   struct {
      double value;   /* value */
      double vmin;    /* minimum accepted */
      double vmax;    /* maximum accepted */
      char* label;    /* label */
   } obsvn [ ] = {
      {0.0,    4e4,    9e5, "MJD"},
      {0.0,   -1.0,    1e5, "TAI (sec)"},
      {0.0,   -0.1,    6.3, "J2000 RA (radians)"},
      {0.0,   -D90,    D90, "J2000 Dec (radians)"},
      {0.0,    0.2,   99.0, "wavelength (microns)"},
      {0.0,   -4.0,    8.0, "roll (radians)"},
      {0.0,   -D90,    D90, "pitch (radians)"},
      {0.0,   -5.0,    7.0, "P.A. (radians)"},
      {0.0, -500.0,  500.0, "pointing origin x"},
      {0.0, -500.0,  500.0, "pointing origin y"},
      {0.0,      1,    5e5, "focal length (mm)"},
      {0.0,  200.0,  350.0, "temperature (deg K)"},
      {0.0,  500.0, 1000.0, "pressure (mB)"},
      {0.0,   -0.1,    1.1, "relative humidity (0-1)"},
      {0.0,  0.005,   0.01, "lapse rate (deg/metre)"},
      {0.0,   -5.0,    7.0, "P.A. correction (radians)"}
   };

/* Synonyms */
#define MJD   obsvn[ 0].value     /* MJD part of TAI */
#define TAI   obsvn[ 1].value     /* Seconds part of TAI */
#define R2000 obsvn[ 2].value     /* RA (FK5, J2000, radians) */
#define D2000 obsvn[ 3].value     /* Dec (FK5, J2000, radians) */
#define WL    obsvn[ 4].value     /* Effective wavelength (microns) */
#define ROLL  obsvn[ 5].value     /* Roll demand (radians) */
#define AZ    obsvn[ 5].value     /* Azimuth demand (radians) */
#define PITCH obsvn[ 6].value     /* Pitch demand (radians) */
#define EL    obsvn[ 6].value     /* Elevation demand (radians) */
#define RPA   obsvn[ 7].value     /* Rotator demand (radians) */
#define POX   obsvn[ 8].value     /* Pointing origin x (mm) */
#define POY   obsvn[ 9].value     /* Pointing origin y (mm) */
#define FL    obsvn[10].value     /* Focal length (mm) */
#define TDK   obsvn[11].value     /* Temperature (deg K) */
#define PMB   obsvn[12].value     /* Pressure (mB) */
#define RH    obsvn[13].value     /* Relative humidity (0-1) */
#define TLR   obsvn[14].value     /* Lapse rate (deg K per metre) */
#define RPAC  obsvn[15].value     /* Rotator correction (radians) */

/*--------------------------------------------------------------------------*/


/* Plug addresses into the string globals table. */
   globc [ 0 ] . value = date;
   globc [ 1 ] . value = utc;
   globc [ 2 ] . value = tel;

/*
** ------------------------------
** Copy input into a scratch file
** ------------------------------
*/

/* Create and open the scratch file. */
   if ( ( fp = tmpfile ( ) ) == NULL ) return -1;

/* Copy until EOF. */
   for ( ; ; ) {

   /* Read a line from standard input. */
      if ( ( fgets ( buf, LS - 1, stdin ) ) == NULL ) break;

   /* Determine its length. */
      nc = strlen ( buf );

   /* Replace TABs etc with spaces. */
      for ( ic = 0; ic < nc; ic++ )
         buf [ ic ] = (char) ( isspace ( (int) ( c = buf [ ic ] ) ) ? ' ' : c );

   /* Eliminate trailing spaces and add a newline. */
      for ( ic = nc - 1; ic >= 0 && isspace ( (int) buf [ ic ] ); ic-- );
      buf [ ++ic ] = (char) '\n';
      buf [ ++ic ] = (char) '\0';

   /* Write the record to the scratch file. */
      if ( fputs ( buf, fp ) == EOF ) return -1;

   /* Next record from standard input. */
   }

/*
** ------------------------
** Decode global parameters
** ------------------------
*/

/* Read the scratch file.*/
   rewind ( fp );
   for ( ; ; ) {

   /* Get the next line of input. */
      if ( ( fgets ( buf, LS, fp ) ) == NULL ) break;

   /* Eliminate the newline. */
      buf [ strlen ( buf ) - 1 ] = (char) '\0';

   /* Point to the identifier and value. */
      id = buf + strspn ( buf, " " );
      val = id + strcspn ( id, " " );
      nc = strspn ( val, " ");
      *val = (char) '\0';
      val += nc;

   /* Ignore comments. */
      c = id [ 0 ];
      if ( c == (char) '!' || c == (char) '\0' ) continue;

   /* Fold identifier to uppercase. */
      nc = strlen ( id );
      for ( ic = 0; ic < nc; ic++ )
         id [ ic ] = (char) toupper ( id [ ic ] );

   /* Test for no more global parameters. */
      if ( ! strncmp ( id, "OBS", 3 ) || ! strncmp ( id, "END", 3 ) ) break;

   /*
   ** Identify, decode, validate and store the global parameter
   ** ---------------------------------------------------------
   */

   /* Set flag to "identifier not recognized". */
      ill = 1;

   /* Look for string global. */
      for ( i = 0; i < NGLOBC; i++ ) {
         if ( ! strcmp ( id, globc [ i ] . id ) ) {

         /* Found.  Check for repeat. */
            if ( globc [ i ] . exist )
               fprintf ( stderr,
                         "Warning: multiple %ss.\n", id );

         /* Check for null value. */
            if ( ! strlen ( val ) )
               fprintf ( stderr,
                         "Warning: empty %s.\n", id );

         /* Store the value and set the presence flag. */
            strncpy ( globc [ i ] . value, val, LS - 1 );
            globc [ i ] . exist = 1;

         /* Flag global parameter accepted, and stop searching. */
            ill = 0;
            break;
         }
      }

   /* If string global not found, look for numeric global. */
      if ( ill ) {
         for ( i = 0; i < NGLOBN; i++ ) {
            if ( ! strcmp ( id, globn [ i ] . id ) ) {

            /* Found.  Check for repeat. */
               if ( globn [ i ] . exist )
                  fprintf ( stderr,
                            "Warning: multiple %ss.\n", id );

            /* Decode and validate the value. */
               if ( sscanf ( val, "%lf", &w ) != 1 ||
                    w < globn [ i ] . vmin ||
                    w > globn [ i ] . vmax ) {

               /* Report error and set flag to "illegal value". */
                  fprintf ( stderr,
                            "%s = %s is illegal.\n",
                            id, val );
                     ill = -1;
               } else {

               /* Store scaled value and set the presence flag. */
                  globn [ i ] . value = w * globn [ i ] . factor;
                  globn [ i ] . exist = 1;
               }

            /* Flag global parameter accepted, and stop searching. */
               ill = 0;
               break;
            }
         }

      /* Report unrecognized identifier. */
         if ( ill > 0 )
            fprintf ( stderr, "<%s> not recognized.\n", buf);
      }

   /* Next line of input. */
   }

/* Make sure all the global parameters are there. */

/* Version 1.0 files only come from Gemini and don't have MTYPE or
   TELNAME keywords. */
   if ( VERSION == 1.0 ) {
      MTYPE = ALTAZ;
      MTYPE_EXIST = 1;
      if ( TLATM > 0.0 ) {
         strcpy( TELNAME, "Gemini north" );
      } else {
         strcpy( TELNAME, "Gemini south" );
      }
      TELNAME_EXIST = 1;
   }

/* A mount type other than GIMBAL means that the gimbal angles can 
   be calculated so the GIMxx keywords aren't required. */
   ill = 0;
   if ( MTYPE != GIMBAL ) {
      GIM1Z_EXIST = 1;
      GIM2Y_EXIST = 1;
      GIM3X_EXIST = 1;
   }
   for ( i = 0; i < NGLOBN; i++ )
      if ( ! globn [ i ] . exist ) {
         fprintf ( stderr, "No %s is available.\n", globn [ i ] . id );
         ill = 1;
      }
   for ( i = 0; i < NGLOBC; i++ )
      if ( ! globc [ i ] . exist ) {
         fprintf ( stderr, "No %s is available.\n", globc [ i ] . id );
         ill = 1;
      }
   if ( ill ) {
      fputs ( "Aborting.\n", stderr );
      return -1;
   }

/* Define the minimum and maximum number of numeric fields in each 
   observation. Version 1.0 files have no RPA correction. */
   nmin = (sizeof obsvn / sizeof obsvn [ 0 ] );
   nmax = (nmin + 2);
   if ( VERSION <= 1.0 ) {
      nmin--;
      nmax--;;
   }

/* Allow for polar motion. */
   slaPolmo ( TLONGM, TLATM, XP, YP, &tlong, &tlat, &daz );

/* Generate gimbal angles and mount orientation matrix. */
   if ( MTYPE != GIMBAL ) {
      GIM1Z = 0.0;
      GIM2Y = ( MTYPE == ALTAZ ) ? 0.0 : tlat - D90;
      GIM3X = 0.0;
   }
   slaDeuler ( "zyx", GIM1Z, GIM2Y, GIM3X, ae2nm );

/*
** -----------------
** Write caption etc
** -----------------
*/

/* Assemble and write the caption. */
   if ( fputs ( tel, stdout ) == EOF ||
        fputs ( ", ", stdout ) == EOF ||
        fputs ( date, stdout ) == EOF ||
        fputs ( "\n", stdout ) == EOF ) return -1;

/* Write the option record. */
    switch ( (int) MTYPE ) {
       case GIMBAL:
          if ( fprintf ( stdout, ": GIMBAL %f %f %f\n", 
                GIM1Z / D2R, GIM2Y / D2R, GIM3X / D2R) < 0 ) return -1;
          break;
       case ALTAZ:
          if ( fprintf ( stdout, ": ALTAZ\n" ) < 0 ) return -1;
          break;
       case EQUAT:
          if ( fprintf ( stdout, ": EQUAT\n" ) < 0 ) return -1;
          break;
    }

/* Format and write the run parameters record. */
   slaDr2af ( 1, tlat, &c, idmsf );
   if ( fprintf ( stdout, "%c%2.2d %2.2d %2.2d.%d\n", c, idmsf [ 0 ],
                  idmsf [ 1 ], idmsf [ 2 ], idmsf [ 3 ] ) < 0 )
      return -1;

/*
** --------------------------------------
** Generate and write observation records
** --------------------------------------
*/

/* Initialize the numeric value index and illegal field flag. */
   num = 0;
   ill = 0;

/* Continue to read the scratch file.*/
   do {

   /* Get the next line of input. */
      if ( ( fgets ( buf, LS, fp ) ) == NULL ) {
         fprintf ( stderr, "END record missing from input file\n");
         strcpy( buf, "END\n");
      }

   /* Eliminate the newline. */
      buf [ strlen ( buf ) - 1 ] = (char) '\0';

   /* Point to the identifier or value. */
      id = buf + strspn ( buf, " " );

   /* Ignore comments. */
      c = id [ 0 ];
      if ( c == (char) '!' || c == (char) '\0' ) continue;

   /* Fold identifier to uppercase. */
      nc = strlen ( id );
      for ( ic = 0; ic < nc; ic++ )
         id [ ic ] = (char) toupper ( id [ ic ] );

   /* End of sequence of numbers? */
      if ( ! strncmp ( id, "OBS", 3 ) || ! strncmp ( id, "END", 3 ) ) {

      /* Yes.  Report any errors. */
         if ( num >= 0 && ( num < nmin || num > nmax ) ) {
            fprintf ( stderr,
                      "Wrong number of observation fields: %d.\n", num );
            ill = 1;
         }
         if ( ill ) {
            fputs ( "Observation rejected.\n", stderr );
         } else {

         /*
         ** Generate a TPOINT observation record
         ** ------------------------------------
         */

         /* TAI, TT, UTC. */
            djmtai = MJD + TAI * S2DAYS;
            djmtt = djmtai + TTMTAI;
            djmutc = djmtai - DELAT;

         /* J2000-to-apparent-to-observed. */
            slaMap ( R2000, D2000, 0.0, 0.0, 0.0, 0.0,
                     2000.0, djmtt, &ra, &da );
            slaAop ( ra, da, djmutc, DELUT, TLONGM, TLATM, HM, XP, YP,
                          TDK, PMB, RH, WL, TLR, &as, &zs, &h, &d, &r );

         /* Star azimuth (wrt terrestrial north) and elevation. */
            as += daz;
            es = D90 - zs;

         /* Apply correction to rotator angle */
            if ( VERSION <= 1.0 ) {
               RPAC = 0.0;
            }
               
         /* Pointing origin position wrt rotator axis. */
            spa = sin ( RPA + RPAC );
            cpa = cos ( RPA + RPAC );
            xr = POX / FL;                 /* n.b. tangent-plane  */
            yr = POY / FL;                 /* projection assumed. */
            xi = - xr * cpa - yr * spa;
            eta = xr * spa - yr * cpa;

         /* Star position in mount frame. */
            slaDcs2c ( as, es, s );
            s[0] = - s[0];
            slaDmxv ( ae2nm, s, sm );
            slaDcc2s ( sm, &s1, &s2 );

         /* Rotator axis pointing direction, for a perfect mount. */
            slaDtps2c ( xi, eta, s1, s2, &am, &em, &am2, &em2, &n );
            if ( n == 0 ) {
               fprintf ( stderr, 
                 "Skipping observation too close to the pole of the mount.\n");
               break;
            }

         /* Back to Az/El. */
            slaDcs2c ( am, em, sm );
            slaDimxv ( ae2nm, sm, s );
            s[0] = - s[0];
            slaDcc2s ( s, &as, &es );

         /* Version 1.1 and above files contain Roll/Pitch which must be
            converted to Az/El. */
            if ( VERSION >= 1.1 ) {
               slaDcs2c ( ROLL, PITCH, m );
               slaDimxv ( ae2nm, m, ae );
               ae[0] = - ae[0]; 
               slaDcc2s ( ae, &az, &el );
            } else {
               az = AZ;
               el = EL;
            }

         /* Write out the ideal Az/El and the telescope raw Az/El. */
            if ( ( fprintf ( stdout, "%11.7f %11.7f %11.7f %11.7f",
                             slaDranrm ( as ) / D2R, es / D2R,
                             slaDranrm ( az ) / D2R, 
                             el / D2R ) ) < 0 )
               return -1;

         /* Write out any auxiliary values. */
            for ( i = nmin; i < num; i++ )
               if ( ( fprintf ( stdout, " %15.10g",
                                obsvn [ i ] . value ) ) < 0 )
                  return -1;

         /* Complete the output record. */
            if ( fputs ( "\n", stdout ) == EOF ) return -1;
         }

      /* Reset the field count and illegal field flag. */
         num = 0;
         ill = 0;

      } else {

      /* Not OBS or end; decode a number. */
         sscanf ( id, "%lf", &w );

      /* Validate (unless auxiliary reading). */
         if ( num < nmin && ( w <= obsvn [ num ] . vmin ||
                              w >= obsvn [ num ] . vmax ) ) {
            fprintf ( stderr,
                      "<%s> is illegal %s value.\n",
                      buf, obsvn [ num ] . label );
            ill = 1;
         }

      /* Store the number (whether OK or not). */
         obsvn [ num++ ] . value = w;
      }

   /* Next line of input, if any. */
   } while ( strcmp ( id, "END" ) );

/*
** ----------------------------------------------
** Write an endmark, then append original records
** ----------------------------------------------
*/

   if ( fputs ( "END\n\n", stdout ) == EOF ) return -1;
   rewind ( fp );
   for ( ; ; ) {
      if ( ( fgets ( buf, LS, fp ) ) == NULL ) break;
      if ( fputs ( buf, stdout ) == EOF ) return -1;
   }

/* Wrap up. */
   return 0;
}
