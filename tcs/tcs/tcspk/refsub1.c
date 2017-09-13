/* Slow but accurate refraction, using the slaRefro function */

#include <slalib.h>
#include "tcs.h"

void tcsRefsub ( int mode,
                 double refa, double refb,
                 double hm, double tlat, double temp, double press,
                 double humid, double tlr, double wavel,
                 double xin, double yin, double zin,
                 double *xout, double *yout, double *zout )

/*
**  - - - - - - - - - -
**   t c s R e f s u b
**  - - - - - - - - - -
**
**  Special radio refraction function for TCS_DSA application.  For
**  radio wavelengths, it overrides the results from the default
**  refraction calculations, which are optimized for speed and which
**  do not cater for extremely low elevations.
**
**  Given:
**     mode     int        0 = observed to topocentric, else vice versa
**     refa     double     refraction constant A (tan)
**     refb     double     refraction constant B (tan^3)
**     hm       double     telescope height above sea level (metres)
**     tlat     double     telescope latitude (true)
**     temp     double     ambient temperature (K)
**     press    double     pressure (mB)
**     humid    double     relative humidity (0-1)
**     tlr      double     tropospheric lapse rate (K per metre)
**     wavel    double     wavelength (micrometres)
**     xin      double     input vector - x
**     yin      double     input vector - y
**     zin      double     input vector - z
**
**  Returned:
**     xout     double*    output vector - x
**     yout     double*    output vector - y
**     zout     double*    output vector - z
**
**  Called:  slaDcc2s, slaDcs2c, dsaRef
**
**  Notes:
**
**  1  For the present function to be called, it must be "declared"
**     when the TCSpk context is set up and/or specified in the calls
**     to tcsMedium that ultimately cause the pointing to be
**     calculated.
**
**  2  This particular implementation uses the slaRefro function, for
**     all wavelengths.
**
**  3  There is no error status.  The function is called in the
**     tcsPtran and tcsPtrani routines, which run in real time and are
**     not equipped to deal with errors.
**
**  Last revision:   29 November 2005
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

#define ZMIN -0.07                /* Minimum sin(el) */
#define D90D 1.5707963267948966   /* 90 degrees in radians */
#define NITS 6        /* Number of iterations, observed to topocentric */

{
   int i;
   double v[3], az, el, zd, ztop, ref, zobs;



/* Take no action for excessively low elevations. */
   if ( zin < ZMIN ) return;

/* Transform starting vector to spherical. */
   v[0] = xin;
   v[1] = yin;
   v[2] = zin;
   slaDcc2s ( v, &az, &el );
   zd = D90D - el;

/* Which direction is the transformation to proceed in? */
   if ( mode ) {

   /* Refracted to unrefracted. */
      zobs = zd;
      slaRefro ( zobs, hm, temp, press, humid, wavel, tlat, tlr, 1e-8,
                 &ref );
      el -= ref;

   } else {

   /* Unrefracted to refracted. */
      ztop = zd;
      zobs = zd;
      for ( i = 1; i < NITS; i++ ) {
         slaRefro ( zobs, hm, temp, press, humid, wavel, tlat, tlr, 1e-8,
                    &ref );
         zobs = ztop - ref;
      }
      el += ref;
   }

/* Back to Cartesian. */
   slaDcs2c ( az, el, v );
   *xout = v[0];
   *yout = v[1];
   *zout = v[2];
}
