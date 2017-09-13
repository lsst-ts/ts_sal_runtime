#ifndef TCSCTXIC
#define TCSCTXIC

#ifdef __cplusplus
extern "C" {
#endif

/*
**  - - - - - - - - -
**   d s a c t x . h
**  - - - - - - - - -
**
**  Deep-space-antenna control system context.
**
**  Initialization occurs in three phases:
**
**  1  Default initialization to zero.
**  2  Initial assignments made by the application.
**  3  Secondary initialization.
**
**  Last revision:   1 February 2007
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

/* Site constants */
   static double tlongm;       /* site mean east longitude (radians) */
   static double tlatm;        /* site mean geodetic latitude (radians) */
   static double hm;           /* site elevation, metres above sea-level */

/* Time and Earth orientation constants */
   static double delut;        /* current UT1-UTC (day) */
   static double delat;        /* TAI-UTC (day) */
   static double ttmtai;       /* TT-TAI (day) */
   static double xpmr,ypmr;    /* polar-motion angles x and y */

/* Atmospheric refraction */
   static double temp;         /* ambient temperature (deg K) */
   static double press;        /* pressure (mB) */
   static double humid;        /* relative humidity (0-1) */
   static double tlr;          /* tropospheric lapse rate (deg K per metre) */
   static double wavelr;       /* reference wavelength (micrometres) */
   static PRF rfun;            /* optional refraction function */

/* Operational pointing model */
#define MAXTRM 30              /* maximum number of terms in model */
#define NTROOM 100             /* maximum number of terms in repertoire */
   static int model[MAXTRM];   /* term numbers for current model (0 = end) */
   static double coeffv[MAXTRM]; /* coefficient values */
   static int nterml;          /* # local terms */
   static int ntermx;          /* # terms implemented explicitly (loc+std) */
   static int nterms;          /* # terms avail. currently (loc+std+gen) */
   static char coeffn[NTROOM][9]; /* coeff. names (local, standard, generic) */
   static char coform[NTROOM][9]; /* format of generic term */

/* Mount */
   static MTYPE mount;         /* mount type */
   static double ae2nm[3][3];  /* rotation matrix, [Az,El] to nominal mount */

/* Basic pointing model coefficients (radians) */
   static double ia;           /* roll zero point */
   static double ib;           /* pitch zero point */
   static double np;           /* mount axes nonperpendicularity */
   static double xt;           /* antenna vector, x-coordinate */
   static double yt;           /* antenna vector, y-coordinate */
   static double zt;           /* antenna vector, z-coordinate */
   static double ae2mt[3][3];  /* rotation matrix, [Az,El] to mount */
   static double ga;           /* guiding adjustment, collimation */
   static double gb;           /* guiding adjustment, pitch */
   static double rnogo;        /* mount pole avoidance radius (radians) */

/* Site parameters, session */
   static double tlong,        /* antenna longitude (true) */
                 tlat;         /* antenna latitude (true) */
   static double uau,vau,      /* distances from spin axis */
                 ukm,vkm;      /*  and equator (AU & km)   */
   static double diurab;       /* diurnal aberration (radians) */

/* Slowly changing target-independent items */
   static double t0;           /* raw clock time at reference time */
   static double st0;          /* LAST at reference time (radians) */
   static double tt0;          /* TT at reference time (MJD) */
   static double ttj;          /* TT at reference time (Julian Epoch) */
   static double amprms[21];   /* target-independent MAP parameters */
   static double refa,refb;    /* refraction coefficients for wavelr */

/*
**  Tracking Frames
**  ---------------
**
**  A reference frame consists of a type and, in some cases, an
**  equinox.  There is a wavelength, which selects either radio or
**  optical operation and in the optical case specifies which colour
**  in the dispersed image is being tracked.
*/

   static FRAMETYPE cosys;   /* mount tracking frame type */
   static double eqx;        /* mount tracking frame equinox */
   static double wavel;      /* mount tracking wavelength */

/*
**  Target
**  ------
**
**  The target (where in the sky to point) consists of:
**
**  . position at reference time (spherical coordinates, radians)
**  . differential rates (radians/day)
**  . reference time (TAI MJD)
**  . offsets from base (radians, threefold, additive)
**  . position at reference date including offsets from base
**  . current position including offsets and differential tracking
**
*/

/* Mount */
   static double tar_p0[2], tar_dt[2], tar_t0,
                 tar_ob[3][2],
                 tar_op0[2],tar_p[2];

/*
**  Sky-Patch Matrices
**  ------------------
**
**  SPM #1 usually describes the transformation from the user frame
**  to apparent RA/Dec.  Usually, SPM #2 describes the transformation
**  from apparent -HA/Dec to mount coordinates;  however, the SPMs can
**  also be used to control the antenna in an Az/El frame.
**
**  Each SPM has a corresponding inverse, used for "upstream"
**  transformations.
**
**  Between SPM #1 and SPM #2 there is a rotation about the z-axis.
**  For the usual case where the user frame is an RA/Dec, the
**  rotation angle is the local apparent sidereal time.  For the
**  case where the user frame is an Az/El, the rotation angle is
**  zero.
*/

   static double spm1[3][3], spm1_i[3][3],
                 spm2[3][3], spm2_i[3][3];

/*
**  MOUNT STATUS
**  ------------
**
**  The demanded and achieved mount position.
*/

   static double roll;   /* demand mount roll (radians, lefthanded) */
   static double pitch;  /* demand mount pitch (radians) */
   static int jbp;       /* TRUE = "beyond the zenith" */
   static double aux[3]; /* auxiliary readings */

/*
**  SCANNING
**  --------
**
**  Parameters for antenna scanning.
*/

   int nsp;                 /* Number of [x,y] offsets */
   float s_path[NSPMAX][2]; /* List of [x,y] offsets (in scan units) */
   double s_unit;           /* Radians per [x,y] unit */
   double s_period;         /* Time per cycle (sec) */
   int nsc;                 /* Cycles (< 1 = indefinite) */
   double s_epoch;          /* Start time (TAI MJD) */
   SCAN_STATE jscan;        /* Command/status */

#ifdef __cplusplus
}
#endif

#endif
