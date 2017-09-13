// Configured to test different rotator control algorithms

#include <stdio.h>
#include <string.h>
#include <slalib.h>
#include "tcs.h"
#include "tcsmac.h"

int main ( )

/*
** - - - - -
**  L S S T
** - - - - -
**
** LSST star trails.
**
** I/O:
**    stdin     list of stars, each RA,Dec in degrees
**    stdout    report
**
** This revision:   19 January 2007
**
** Copyright P.T.Wallace.  All rights reserved.
*/

/*
** ------------------------
** Parameters defining test
** ------------------------
*/

#define YES 1
#define NO 0

#define VERBOSE YES           /* Full reporting */
#define REP_HEAD YES          /* Head the report */

#define MOUNT ALTAZ           /* Mount type */
#define RLOCN OTA             /* Instrument rotator location */
#define SITE_LAT -30.24075    /* Site latitude (deg) */
#define SITE_HM 2738.0        /* Site elevation (m) */
#define PMB 730.0             /* pressure (hPa) */

#define FIELD 3.5             /* Field width (deg) */
#define F_CIRC YES            /* Circular (rather than square) field */
#define FOCAL_L 10499.8       /* Focal length (mm) */

#define TPS 5L                /* Ticks per second */
#define T_SLOW (60L*TPS)      /* Ticks per slow update */
#define T_MED (5L*TPS)        /* Ticks per medium update */

#define PM_NOMINAL "lsst.nom" /* Nominal pointing model */
#define PM_TRUE "lsst.tru"    /* True pointing model */
#define DXI 0.0               /* Rotator axis error in xi (arcsec) */
#define DETA 0.0              /* Rotator axis error in eta (arcsec) */
#define PM_ENABLED YES        /* Pointing models enabled */

#define RMA_PAR NO            /* Control rotator using parallactic angle */
#define RMA_KECK NO           /* Control rotator using Keck formula */
#define RMA_SLIT NO           /* Control rotator for slit */
#define RMA_FIXED NO          /* Rotator motion disabled */

#define LEN_TEST (60L*TPS)    /* Duration of test (ticks) */
#define LOG_INT (1L*TPS)      /* Ticks per line of report */

#define REP_DIST NO           /* Whether to report distortions and shifts */
#define REP_TRAIL NO          /* Whether to report trailed image positions */
#define MAG 500               /* Trail magnification */
#define N_TOP YES             /* Whether north at the top */
#define E_LEFT YES            /* Whether east at the left */
#define ONE_STAR NO           /* One star or multiple stars */

#include "trails.ccc"
