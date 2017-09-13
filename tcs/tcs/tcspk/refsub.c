/* This is the dsaRef version. */

#include <stdio.h>
#include <slalib.h>
#include "tcs.h"

void dsaRef ( double, double, double, double, double* );

void dsaRefsub ( int mode,
                 double refa, double refb,
                 double hm, double tlat, double temp, double press,
                 double humid, double tlr, double wavel,
                 double xin, double yin, double zin,
                 double *xout, double *yout, double *zout )

/*
**  - - - - - - - - - -
**   d s a R e f s u b
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
**  2  This particular implementation uses the dsaRef function, for
**     radio wavelengths, and takes no action for optical/IR cases.
**
**  3  There is no error status.  The function is called in the
**     tcsPtran and tcsPtrani routines, which run in real time and are
**     not equipped to deal with errors.
**
**  Last revision:   25 November 2006
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

#define ZMIN 0.01                 /* Minimum sin(el) */
#define D90D 1.5707963267948966   /* 90 degrees in radians */
#define NITS 6    /* Number of iterations, observed to topocentric */

{
   int i;
   double v[3], az, el, zd, ztop, ref, zobs;


/* Take no action for excessively low elevations. */
   if ( zin < ZMIN ) return;

/* Radio case? */
   if ( wavel > 100.0 ) {

   /* Yes.  Transform starting vector to spherical. */
      v[0] = xin;
      v[1] = yin;
      v[2] = zin;
      slaDcc2s ( v, &az, &el );
      zd = D90D - el;

   /* Which direction is the transformation to proceed in? */
      if ( mode ) {

      /* Refracted to unrefracted. */
         zobs = ztop = zd;
         for ( i = 1; i < NITS; i++ ) {
            dsaRef ( ztop, temp, press, humid, &ref );
            ztop = zobs + ref;
         }
         el -= ref;

      } else {

      /* Unrefracted to refracted. */
         ztop = zd;
         dsaRef ( ztop, temp, press, humid, &ref );
         el += ref;
      }

   /* Back to Cartesian. */
      slaDcs2c ( az, el, v );
      *xout = v[0];
      *yout = v[1];
      *zout = v[2];
   }
}

#include <math.h>

void dsaRef ( double ztop, double tdk, double pmb, double rh, double *ref )

/*
**  - - - - - - -
**   d s a R e f
**  - - - - - - -
**
**  Atmospheric refraction for radio wavelengths.
**
**  Given:
**    ztop   double   topocentric zenith distance of the source (radian)
**    tdk    double   ambient temperature at the observer (K)
**    pmb    double   pressure at the observer (millibar)
**    rh     double   relative humidity at the observer (range 0-1)
**
**  Returned:
**    ref    double*  refraction: observed ZD minus in vacuo ZD (radian)
**
**  Notes:
**
**  1  The function predicts the radio refraction only and will not be
**     accurate if used in the optical/IR.
**
**     Because the algorithm takes no account of the ionosphere, the
**     accuracy deteriorates at low frequencies, below about 30 MHz.
**
**     Water bands may cause errors of up to 1% above a few tens of GHz.
**
**  2  The errors are small down to about 5 deg elevation.  Compared
**     with the SLALIB ray-trace routine slaRefro, the errors are as
**     follows (for 23C, 1013.3 mB and 50%):
**
**            Etopo      slaRefro     dsaRef      diff
**
**             90.0         0.000      0.000      0.000
**             80.0         3.296      3.299      0.003
**             70.0         6.802      6.809      0.006
**             60.0        10.788     10.798      0.010
**             50.0        15.670     15.685      0.015
**             40.0        22.235     22.256      0.021
**             30.0        32.248     32.280      0.032
**             20.0        50.850     50.905      0.055
**             18.0        56.820     56.884      0.064
**             16.0        64.165     64.242      0.076
**             14.0        73.434     73.528      0.094
**             12.0        85.505     85.625      0.120
**             10.0       101.867    102.025      0.158
**              9.0       112.425    112.609      0.184
**              8.0       125.226    125.438      0.212
**              7.0       141.031    141.268      0.238
**              6.0       160.965    161.208      0.243
**              5.0       186.741    186.924      0.183
**              4.5       202.609    202.710      0.100
**              4.0       221.061    221.025     -0.036
**              3.5       242.706    242.486     -0.220
**              3.0       268.337    267.979     -0.359
**              2.5       298.998    298.991     -0.007
**              2.0       336.070    338.717      2.647
**              1.5       381.405    397.021     15.616
**              1.0       437.511    459.145     21.634
**              0.5       507.827    459.145    -48.682
**
**              deg         mdeg       mdeg       mdeg
**
**     The errors worsen for higher humidity and temperature, but
**     are unlikely to approach the limits set by knowledge of the
**     atmospheric conditions.  For an extreme case of a sea-level
**     site at 40 deg C and 100% humidity, the error is 1.5 mdeg
**     at an elevation of 10 deg and 4 mdeg at elevation 5 deg.  A
**     reduction of humidity to 75% or of temperature to 35 deg C is
**     enough to halve the errors
**
**  3  The routine is designed for speed.  Minimal validation of input
**     arguments is performed, and zenith distances beyond 89 deg will
**     give unreliable results.
**
**  4  The routine starts with topocentric (i.e. in vacuo) zenith
**     distance.  It is thus optimized for the case where the
**     unrefracted elevation of the source has been computed and a
**     demand elevation for the antenna is required.  Should it be
**     necessary to take antenna elevation and from it deduce the
**     unrefracted elevation, some form of iterative solution will
**     be required.
**
**  5  It should be noted that the relative humidity rh is formally
**     defined in terms of "mixing ratio" rather than pressures or
**     densities as is often stated.  It is the mass of water per unit
**     mass of dry air divided by that for saturated air at the same
**     temperature and pressure (see Gill 1982).
**
**  Last revision:   15 June 2003
**
**  Copyright European Space Agency and P.T.Wallace.  All rights reserved.
*/

#define ZMAX 1.55         /* Maximum ZD supported (radians) */
#define PMIN 1e-6         /* Minimum non-zero pressure */

{
   double z, ps, pw, b, s, c;


   if ( pmb < PMIN ) {
      *ref = 0.0;
      return;
   }
   z = ztop < ZMAX ? ztop : ZMAX;
   ps = pow ( 10.0,
              ( ( 0.03477 * tdk - 8.71170 ) /
                ( 0.00412 * tdk - 0.12540 ) ) * ( 1.0 + pmb * 4.5e-6 ) );
   pw = rh * ps / ( 1.0 - ( 1.0 - rh ) * ps / pmb );
   b = 4.4474e-6 * tdk * ( 1.0 - 0.0074 * pw );
   s = sin ( z );
   c = cos ( z );
   *ref = ( ( 77.6890e-6 * pmb - ( 6.3938e-6 - 0.375463 / tdk ) * pw )
          / tdk ) * ( 1.0 - b ) * s
          / sqrt ( c * c + 0.001908 + 0.6994 * b - 0.00003117 * s / c );
}
