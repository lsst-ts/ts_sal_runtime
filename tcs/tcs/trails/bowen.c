#include <stdio.h>
#include <string.h>
#include <slalib.h>
#include "tcs.h"
#include "tcsmac.h"

int main ( )

/*
** - - - - - -
**  B O W E N
** - - - - - -
**
** I.S.Bowen's 1966 plots.
**
** I/O:
**    stdin     list of stars, each HA,Dec in degrees
**    stdout    report
**
** This revision:   22 January 2007
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

#define VERBOSE NO           /* Full reporting */
#define REP_HEAD YES         /* Head the report */

#define MOUNT EQUAT          /* Mount type */
#define RLOCN OTA            /* Instrument rotator location */
#define SITE_LAT 30.0        /* Site latitude (deg) */
#define SITE_HM 1892.0       /* Site elevation (m) */
#define PMB 819.0            /* pressure (hPa) */

#define FIELD 2.0            /* Field width (deg) */
#define F_CIRC YES           /* Circular (rather than square) field */
#define FOCAL_L 3048.0       /* Focal length (mm) */

#define TPS 1L               /* Ticks per second */
#define T_SLOW (60L*TPS)     /* Ticks per slow update */
#define T_MED (5L*TPS)       /* Ticks per medium update */

#define PM_NOMINAL "bowen.mod" /* Nominal pointing model */
#define PM_TRUE PM_NOMINAL     /* True pointing model */
#define DXI 0.0              /* Rotator axis error in xi (arcsec). */
#define DETA 0.0             /* Rotator axis error in eta (arcsec). */
#define PM_ENABLED YES       /* Pointing models enabled */

#define RMA_PAR NO           /* Control rotator using parallactic angle */
#define RMA_KECK NO          /* Control rotator using Keck formula */
#define RMA_SLIT NO          /* Control rotator for slit case */
#define RMA_FIXED YES        /* Rotator motion enabled */

#define LEN_TEST (8L*60L*60L*TPS) /* Duration of test (ticks) */
#define LOG_INT (60L*60L*TPS)     /* Ticks per line of report */

#define REP_DIST NO          /* Whether to report distortions and shifts */
#define REP_TRAIL YES        /* Whether to report trailed image positions */
#define MAG 500              /* Trail magnification */
#define N_TOP YES            /* Whether north at the top */
#define E_LEFT NO            /* Whether east at the left */
#define ONE_STAR YES         /* One star or multiple stars */

#include "trails.ccc"
