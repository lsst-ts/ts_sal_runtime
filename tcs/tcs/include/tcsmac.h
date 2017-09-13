#ifndef TCSMIC
#define TCSMIC

#ifdef __cplusplus
extern "C" {
#endif

/*
**  - - - - - - - - -
**   t c s m a c . h
**  - - - - - - - - -
**
**  TCS macros.
**
**  Last revision:   4 May 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

/* Mathematical constants */
#define D90    1.57079632679489661923132      /* Pi/2 */
#define PI     3.14159265358979323846264      /* Pi */
#define PI2    6.28318530717958647692529      /* 2Pi */
#define D2R  0.0174532925199432957692369      /* degrees to radians */
#define S2R    7.27220521664303990384871e-5   /* seconds to radians */
#define AS2R   4.84813681109535993589914e-6   /* arcseconds to radians */

/* Physical constants */
#define C 173.14463331            /* speed of light (AU/day) */
#define AU2KM 149597870.66        /* AU to km */
#define UTST 1.00273790934        /* ratio of SI to ST second */
#define STRPD (UTST*S2R*86400.0)  /* Earth spin rate (radians/UT day) */

/* System constants */
#define TINY 1e-10    /* a small number */
#define TINY2 1e-20   /* a much smaller number */
#define DEL 0.005     /* probe-vector spacing (rad) for SPM generation */

/* Command codes for the FAST process */
#define ROTATOR    1   /* achieved rotator angle and speed */
#define ST         2   /* sidereal time */
#define MODEL      4   /* pointing model */
#define TARGET     8   /* target */
#define PO        16   /* pointing origin */
#define PA        32   /* field orientation */
#define TRANSFORM 64   /* transformation matrices */
#define ALL      127   /* everything */

#ifdef __cplusplus
}
#endif

#endif
