#ifndef TCSIC
#define TCSIC

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>

/*
**  - - - - - -
**   t c s . h
**  - - - - - -
**
**  TCS function prototypes.
**
**  Last revision:   15 August 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

/*
** ----------------
** Type definitions
** ----------------
*/

/* Supported reference frames */
typedef enum { AZEL_TOPO = 1,     /* topocentric Az/El */
               APPT_TOPO = 2,     /* topocentric apparent RA/Dec */
               APPT = 3,          /* geocentric apparent RA/Dec */
               FK5 = 4,           /* IAU 1976 RA/Dec, any equinox */
               FK4 = 5            /* pre IAU 1976 RA/Dec, any equinox */
             } FRAMETYPE;

/* Instrument rotator locations */
typedef enum { OTA = 1,           /* Prime, Newtonian, Cass, bent Cass */
               NASMYTH_L = 2,     /* Nasmyth (left) */
               NASMYTH_R = 3,     /* Nasmyth (right) */
               COUDE_L = 4,       /* Coude (left) */
               COUDE_R = 5        /* Coude (right) */
             } ROTLOC;

/* Mount type codes */
typedef enum { EQUAT = 1,         /* equatorial */
               ALTAZ = 2,         /* altazimuth */
               GIMBAL = 3         /* generalized gimbal */
             } MTYPE;

/* Pointers to (optional) refraction functions */
typedef void ( *PRF ) ( int, double, double, double, double,
                        double, double, double, double, double,
                        double, double, double, double*, double*, double* );

/*
** -------------------
** Function prototypes
** -------------------
*/

int tcsAddtrm ( int, int, char[9], double, int*, char[][9], char[][9],
                int[], double[] );

void tcsAim2enc ( double, double, double,
                  ROTLOC, double, double, double, double, double,
                  double, double, double,
                  double, double, double, double, double,
                  double*, double*,
                  double*, double*, int* );

void tcsAim2s_c ( double, double, double,
                  double[3][3], FRAMETYPE, double, double, double[3][3],
                  double*, double*, double* );

void tcsAim2xe ( double, double, double,
                 double, double, double,
                 double, double, double,
                 double*, double*, int* );

void tcsAimtrk ( double, double, double,
                 ROTLOC, double, double, double, double, double,
                 double, double, double, double,
                 double, double, double, double, double,
                 double*, double*, double*, double*, int* );

int tcsAstup ( double, double[3][3],
               FRAMETYPE, double, double,
               FRAMETYPE, double, double,
               double[2], double, double, double, double, double, double,
               double, double, double, double, PRF,
               double, double, double, double[21],
               double[3][3], double[3][3], double[3][3], double[3][3],
               double[3][3], double[3][3], double[3][3], double[3][3] );

void tcsBs ( double, double, double, ROTLOC, double, double, double,
             double, double, double, double,
             double*, double*, double* );

void tcsCasspa ( ROTLOC, double, double, double, double*, double* );

void tcsEnc2aim ( double, double,
                  double, double, double,
                  double, double, double,
                  double*, double*, double* );

void tcsFast ( int, int, double,
               ROTLOC, double, double, double,
               double, double,
               double, double, double, double, double, double,
               double, double, double,
               double, double[2], double[2],
               double, double[2],
               double, double, double, int,
               FRAMETYPE, double[3][3], double[3][3],
               FRAMETYPE, double[3][3], double[3][3],
               double*, double*, double* );

void tcsG2po ( double, double, double, double, double, double,
               ROTLOC, double, double[3][3], FRAMETYPE, double,
               double, double[3][3], double, double, double, double,
               double, double, double*, double*, int* );

void tcsG2tar ( double, double, double, double, double, double,
                ROTLOC, double, double[3][3], FRAMETYPE, double,
                double, double[3][3], double, double, double, double,
                double, double, double*, double* );

int tcsInit2 ( double, double, double, double, double, MTYPE, double,
               double, double, double[3][3], double*, double*, double*,
               double*, double*, double*, double* );

int tcsIntpm ( char*, int, int, int[], int*, int*, int*,
               char[][9], char[][9], double[] );

int tcsIterm ( int, int, int[], char[][9], double[], char[9], double* );

int tcsMedium ( double, int, int[], double[],
                int, int, int, char[][9], char[][9], MTYPE, double[3][3],
                double, double, int, double[3],
                FRAMETYPE, double, double,
                FRAMETYPE, double, double,
                double[2],
                double, double, double,
                double, double, double, double,
                double, double, double, PRF,
                double, double, double, double[21],
                double*, double*, double*,
                double*, double*, double*,
                double[3][3],
                double[3][3], double[3][3],
                double[3][3], double[3][3],
                double[3][3], double[3][3],
                double[3][3], double[3][3] );

int tcsPmt ( double[7], double[3][3], double[3], int,
             double*, double*, double*,
             double*, double*, double*,
             double[3][3] );

void tcsPorup ( double[2], double[3][2], double[2] );

void tcsPosture ( double, double, double, double [3][3] );

void tcsProbev ( double[3], double, double[3], double[3], double[3] );

void tcsPtran ( double, double[21], double[3][3], double, double,
                double, FRAMETYPE, double, double[3][3], double, double,
                double, double, double, double, double, PRF, double, double,
                double[3], double[3], double[3], double[3] );

void tcsPtrani ( double, double, double,
                 double, double[21], double[3][3], double, double,
                 double, FRAMETYPE, double, double, double,
                 double, double, double, double, double, PRF,
                 double, double, double[2] );

int tcsPup ( int, int[], double[], int, int, int, char[][9], char[][9],
             MTYPE, double[3][3], double, double, int, double[3], double,
             double*, double*, double*,
             double*, double*, double*,
             double[3][3] );

void tcsRotator ( double, double, double,
                  ROTLOC, double, int, double, double,
                  double, double, double, double, double,
                  double, double, double, double,
                  double, double, double,
                  double[3][3], FRAMETYPE, double, double, double[3][3],
                  double, int, double*, int* );

void tcsSky2a_c ( double, double, double,
                  double[3][3], FRAMETYPE, double, double, double[3][3],
                  double*, double*, double* );

void tcsSky2aim ( double, double,
                  double[3][3], FRAMETYPE, double, double, double[3][3],
                  double*, double*, double* );

void tcsSlow ( double, double, double, double, double, double,
               double, double, double,
               double*, double*, double*, double*,
               double[21], double*, double* );

int tcsSpm ( double[3], double[3], double[3],
             double[3], double[3], double[3],
             double[3][3] );

int tcsSterm ( char[9], double, int, int[], char[][9], double[] );

void tcsTargup ( double, double, double[2], double[2], double[3][2],
                 double[2], double[2] );

int tcsTartr_c ( double, double[21], double[3][3], double, double, double,
                 double, double,
                 double, double,double, double,double, PRF, double, double,
                 FRAMETYPE, double, double, double, double,
                 double[3][3], double[3][3], double[3][3], double[3][3] );

int tcsTartran ( double, double[21], double[3][3], double, double, double,
                 double, double,
                 double, double,double, double,double, PRF, double, double,
                 FRAMETYPE, double, double[2],
                 double[3][3], double[3][3], double[3][3], double[3][3] );

int tcsTime ( double* );

void tcsTrack ( double, double,
                double[3][3], FRAMETYPE, double, double, double[3][3],
                ROTLOC, double, double, double, double, double,
                double, double, double, double,
                double, double, double, double, double,
                double*, double*, double*, double*, double*,
                double*, double*, int* );

void tcsTrack_c ( double, double, double,
                  double[3][3], FRAMETYPE, double, double, double[3][3],
                  ROTLOC, double, double, double, double, double,
                  double, double, double, double,
                  double, double, double, double, double,
                  double*, double*, double*, double*, double*,
                  double*, double*, int* );

void tcsVTenc ( double, double,
                double[3][3], FRAMETYPE, double, double, double[3][3],
                ROTLOC, double, double, double, double,
                double, double, double, double, double,
                double, double, double, double, double,
                double*, double*, double*, double*, int* );

void tcsVTenc_c ( double, double, double,
                  double[3][3], FRAMETYPE, double, double, double[3][3],
                  ROTLOC, double, double, double, double,
                  double, double, double, double, double,
                  double, double, double, double, double,
                  double*, double*, double*, double*, int* );

void tcsVTsky ( double, double, ROTLOC, double, double, double,
                double[3][3], FRAMETYPE, double, double, double[3][3],
                double, double, double, double,
                double, double, double, double,
                double*, double* );

void tcsVTsky_c ( double, double, ROTLOC, double, double, double,
                  double[3][3], FRAMETYPE, double, double, double[3][3],
                  double, double, double, double,
                  double, double, double, double,
                  double*, double*, double* );

void tcsVTxe ( double, double,
               double[3][3], FRAMETYPE, double, double, double[3][3],
               double, double,
               double, double, double, double,
               double, double, double, double,
               double*, double*, int* );

void tcsVTxe_c ( double, double, double,
                 double[3][3], FRAMETYPE, double, double, double[3][3],
                 double, double,
                 double, double, double, double,
                 double, double, double, double,
                 double*, double*, int* );

void tcsVTxy ( double, double,
               double[3][3], FRAMETYPE, double, double, double[3][3],
               ROTLOC, double, double, double,
               double, double, double, double,
               double, double, double, double,
               double*, double*, int* );

void tcsVTxy_c ( double, double, double,
                 double[3][3], FRAMETYPE, double, double, double[3][3],
                 ROTLOC, double, double, double,
                 double, double, double, double,
                 double, double, double, double,
                 double*, double*, int* );

void tcsXe2xy ( double, double, ROTLOC, double, double, double,
                double*, double* );

void tcsXy2xe ( double, double, ROTLOC, double, double, double,
                double*, double* );

/* Directly-referenced TPOINT functions. */

int tptMinit ( int, int, int[], int*, int*, int*, char[][9] );

int tptTerm ( char*, int, int*, char[][9], char[][9] );

int tptPterm ( int, double, double[], int, double[3], double, double,
               int, double[3][3], int, int, int, char[][9], char[][9],
               int, double[3], double[8] );

int tptScomp ( char*, char* );

#ifdef __cplusplus
}
#endif

#endif
