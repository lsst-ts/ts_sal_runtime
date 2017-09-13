#ifndef TCSCTXIC
#define TCSCTXIC

#ifdef __cplusplus
extern "C" {
#endif

/*
**  - - - - - - - - -
**   t c s c t x . h
**  - - - - - - - - -
**
**  TCS context.
**
**  Initialization occurs in three phases:
**
**  1  Default initialization to zero.
**  2  Initial assignments made by the application.
**  3  Secondary initialization.
**
**  Last revision:   12 March 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/


/* Site and telescope constants */
   static double tlongm;       /* site mean east longitude (radians) */
   static double tlatm;        /* site mean geodetic latitude (radians) */
   static double hm;           /* site elevation, metres above sea-level */
   static double fl;           /* telescope focal length */

/* Time and Earth orientation constants */
   static double delut;        /* current UT1-UTC (day) */
   static double delat;        /* TAI-UTC (day) */
   static double ttmtai;       /* TT-TAI (day) */
   static double xpmr,ypmr;    /* polar-motion angles x and y */

/* Atmospheric refraction */
   static double temp;         /* ambient temperature (K) */
   static double press;        /* pressure (mB=hPa) */
   static double humid;        /* relative humidity (0-1) */
   static double tlr;          /* tropospheric lapse rate (K per metre) */
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

/* Location of instrument rotator */
   static ROTLOC rotl;         /* OTA, Nasmyth L/R, or coude L/R */

/* Pointing control (all radians) */
   static double ia;           /* roll zero point */
   static double ib;           /* pitch zero point */
   static double np;           /* mount axes nonperpendicularity */
   static double xt;           /* telescope vector, x-coordinate */
   static double yt;           /* telescope vector, y-coordinate */
   static double zt;           /* telescope vector, z-coordinate */
   static double ae2mt[3][3];  /* rotation matrix, [Az,El] to mount */
   static double ga;           /* guiding adjustment, collimation */
   static double gb;           /* guiding adjustment, pitch */
   static double rnogo;        /* mount pole avoidance radius */

/* Site parameters, current */
   static double tlong,        /* telescope longitude (true, radians) */
                 tlat;         /* telescope latitude (true, radians) */
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
**  equinox.  The mount and the rotator have independent frames,
**  allowing for example tracking in J2000 [RA,Dec] while stabilizing
**  the instrument with respect to [Az,El].  There is a wavelength
**  (for mount and rotator separately) which specifies which colour
**  in the dispersed image is being tracked.
*/

   static FRAMETYPE m_cosys;   /* mount tracking frame type */
   static double m_eqx;        /* mount tracking frame equinox */
   static double m_wavel;      /* mount tracking wavelength */
   static FRAMETYPE r_cosys;   /* rotator orientation frame type */
   static double r_eqx;        /* rotator orientation frame equinox */
   static double r_wavel;      /* rotator orientation frame wavelength */

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
**  . position at reference time including offsets from base
**  . current position including offsets and differential tracking
**
*/

/* Mount */
   static double m_tar_p0[2], m_tar_dt[2], m_tar_t0,
                 m_tar_ob[3][2],
                 m_tar_op0[2],m_tar_p[2];

/*
**  Pointing Origins
**  ----------------
**
**  A pointing origin (where in the focal plane the image will be
**  delivered) consists of:
**
**  . x,y position
**  . offsets from base (threefold, additive)
**
**  The unit is focal lengths.
**
**  A list of NPOS such pointing-origins is held;  #0 is fixed at the
**  rotator axis [0,0].  The currently selected pointing-origin is
**  specified by the index npo and produces:
**
**  . net current x,y position
**
*/

#define NPOS 6                 /* Rotator axis plus five deployable */
   int npo;
   static double m_por_p0[NPOS][2],
                 m_por_ob[NPOS][3][2],
                 m_por_p[2];

/*
**  Field Orientation
**  -----------------
**
**  The field orientation (how the image is oriented on the instrument)
**  is specified in three stages:
**
**  . The user chooses some direction on the instrument that is
**    convenient to work with.  This is called the Instrument Principal
**    Direction (IPD).  A typical choice of IPD would be the pixel +y
**    direction on a CCD.
**
**  . Through either mechanical preparation or on-the-sky calibration,
**    the user provides the orientation of the IPD with respect to the
**    +y axis of the instrument rotator.  This angle is called the
**    Instrument Alignment Angle (IAA).
**
**  . The user then specifies what position-angle on the sky the IPD is
**    to assume.  This is called the Instrument Position-Angle (IPA).
**
**  . The resulting rotator demands can either match the IPD strictly
**    (called "slit-optimized") or can minimize the overall residual
**    field rotation (called "field-optimized").  This is controlled
**    with the jf flag.
**
**  The TCS controls the rotator to achieve the requested IPA (at the
**  pointing-origin).  The demand to the rotator is called the Rotator
**  Mechanical Angle (RMA).
*/

   static double sia, cia;     /* sine, cosine of IAA */
   static double pai;          /* Instrument Position-Angle */
   static int jf;              /* Optimization: 0=slit, else=field */

/*
**  Sky-Patch Matrices
**  ------------------
**
**  SPM #1 usually describes the transformation from the user frame
**  to apparent RA/Dec.  Usually, SPM #2 describes the transformation
**  from apparent -HA/Dec to mount coordinates;  however, the SPMs can
**  also be used to control the telescope in an Az/El frame.
**
**  Each SPM has a corresponding inverse, used for "upstream"
**  transformations.
**
**  One pair of SPMs is for the mount and one pair is for the rotator
**  orientation.
**
**  Between SPM #1 and SPM #2 there is a rotation about the z-axis.
**  For the usual case where the user frame is an RA/Dec, the
**  rotation angle is the local apparent sidereal time.  For the
**  case where the user frame is an Az/El, the rotation angle is
**  zero.
*/

/* Mount */
   static double m_spm1[3][3], m_spm1_i[3][3],
                 m_spm2[3][3], m_spm2_i[3][3];

/* Rotator orientation */
   static double r_spm1[3][3], r_spm1_i[3][3],
                 r_spm2[3][3], r_spm2_i[3][3];

/*
**  Mount/Rotator Status
**  --------------------
**
**  The demanded and achieved mount and rotator positions.
*/

   static double roll;   /* demand mount roll (radians, lefthanded) */
   static double pitch;  /* demand mount pitch (radians) */
   static double rota;   /* demand rotator angle */
   static int jbp;       /* TRUE = "below the pole" */
   static double aux[3]; /* auxiliary readings */

   static double rmat;   /* timestamp for rotator position & velocity */
   static double rma;    /* rotator mechanical angle (radians) */
   static double rmav;   /* rotator velocity (radians per tick)*/

#ifdef __cplusplus
}
#endif

#endif
