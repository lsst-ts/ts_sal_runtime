/// \file Wcs.cpp
/// \brief Implementation of the world coordinate system class.

#include <stdio.h>
#include <string.h>
#include "ICRefSys.h"
#include "FK5RefSys.h"
#include "ApptRefSys.h"
#include "TopoApptRefSys.h"
#include "AzElRefSys.h"
#include "GalacticRefSys.h"
#include "Wcs.h"

#include "slalib.h"
#include <stdexcept>

namespace {
    using namespace tpk;
    
// Frame types
    enum FRAMETYPE { AZEL_TOPO = 1, APPT_TOPO = 2, APPT = 3,
            FK4 = 4, FK5 = 5, GAL = 6};

// Epoch
    struct EPOCH {
            double year ;        /* Epoch in years */
            char   type ;        /* type of Epoch ('B' or 'J') */
    } ;

    int astFITSs ( struct WCS, FRAMETYPE, struct EPOCH, double,
            char*, char*, char*, char*, char*, char*, char*,
            char*, char*, char*, char*, char*, char* );
    int astFITSv ( struct WCS, FRAMETYPE, struct EPOCH, double,
            char*, double*, double*, char*, double*, double*, double*,
            double*, double*, double*, char*, double*, double* );
    int astInvtr ( struct WCS, struct WCS* );
    int astS2xyq ( double, double, struct WCS, double*, double* );
    int astXy2sq ( double, double, struct WCS, double*, double* );
}

namespace tpk {
    Wcs::Wcs(
        const RefSys& refsys,
        const double wcsContext[8]
    ) {
    
    // Copy reference system
        mRefSys = refsys.clone();

    // Store forward transformation.
        mWcsTrans.ab0[0] = wcsContext[0];
        mWcsTrans.ab0[1] = wcsContext[1];
        for ( int i = 0; i < 6; i++ ) {
            mWcsTrans.coeffs[i] = wcsContext[i+2];
        }

    // Compute and store the inverse transformation.
        invtr();
    }

/// Transform instrument x,y to spherical coordinates.
    void Wcs::inst2sph(
        const double& x,     ///< instrument x coordinate
        const double& y,     ///< instrument y coordinate
        double& a,           ///< first spherical coordinate
        double& b            ///< second spherical coordinate
    ) const {
        (void)astXy2sq( x, y, mWcsTrans, &a, &b);
    }

/// Transform spherical coordinates to instrument x,y.
    void Wcs::sph2inst(
        const double& a,     ///< first spherical coordinate
        const double& b,     ///< second spherical coordinate
        double& x,           ///< instrument x coordinate
        double& y            ///< instrument y coordinate
    ) const {
        if ( astS2xyq( a, b, mWcsTrans_i, &x, &y) != 0 ) {
            throw std::runtime_error("position not in focal plane");
        }
    }

// Store inverse transformation.
    void Wcs::invtr( void ) {
        if ( astInvtr( mWcsTrans, &mWcsTrans_i ) != 0 ) {
            throw std::runtime_error("Unable to invert transformation");
        }
    }

/// Get Context.
/**
    The WCS context is returned as an array of doubles that can be transfered
    to another system and the WCS object re-created.
*/
    void Wcs::getContext(
        double wcsContext[8]       ///< WCS context array
    ) const {
        wcsContext[0] = mWcsTrans.ab0[0];
        wcsContext[1] = mWcsTrans.ab0[1];
        for ( int i = 0; i < 6; i++ ) {
            wcsContext[i+2] = mWcsTrans.coeffs[i];
        }
    }

/// Field Orientation
/**
    \returns field orientation (radians)
*/
    double Wcs::orientation( void ) const {
        double x0, y0, xs, ys, perp, orient;
        slaDcmpf( const_cast<double*>(mWcsTrans.coeffs), &x0, &y0, &xs, &ys,
                &perp, &orient);
        return orient;
    }

/// Get FITS header values
/**
    Generates FITS header values representing the world coordinate system.
*/
/// FITS headers
    void Wcs::getFITSvalues (
            double djm,                  ///< epoch of observation (MJD)
            std::string ctype1,          ///< value for FITS keyword CTYPE1
            double& crpix1,              ///< value for FITS keyword CRPIX1
            double& crval1,              ///< value for FITS keyword CRVAL1
            std::string ctype2,          ///< value for FITS keyword CTYPE1
            double& crpix2,              ///< value for FITS keyword CRPIX2
            double& crval2,              ///< value for FITS keyword CRVAL2
            double& cd1_1,               ///< value for FITS keyword CD1_1
            double& cd1_2,               ///< value for FITS keyword CD1_2
            double& cd2_1,               ///< value for FITS keyword CD2_1
            double& cd2_2,               ///< value for FITS keyword CD2_2
            std::string radecsys,        ///< value for FITS keyword RADECSYS
            double& equinox,             ///< value for FITS keyword EQUINOX
            double& mjdobs               ///< value for FITS keyword MJD-OBS
    ) const throw (std::runtime_error) {

    // Check the the coordinate system is supported.
        EPOCH epoch = {2000.0, 'J'};
        FRAMETYPE frame;
        if ( typeid(*mRefSys) == typeid(ICRefSys) ) {
            frame = FK5;
        } else if ( typeid(*mRefSys) == typeid(FK5RefSys) ) {
            frame = FK5;
            epoch.year = dynamic_cast<const FK5RefSys*>(&*mRefSys)->equinox();
        } else if ( typeid(*mRefSys) == typeid(ApptRefSys) ) {
            frame = APPT;
        } else if ( typeid(*mRefSys) == typeid(TopoApptRefSys) ) {
            frame = APPT_TOPO;
        } else if ( typeid(*mRefSys) == typeid(AzElRefSys) ) {
            frame = AZEL_TOPO;
        } else if ( typeid(*mRefSys) == typeid(GalacticRefSys) ) {
            frame = GAL;
        } else {
            throw std::runtime_error("frame not supported");
        }

    // Get header values
        char ctype1_c[9], ctype2_c[9], radecsys_c[9];
        if  (astFITSv( mWcsTrans, frame, epoch, djm, ctype1_c,
                &crpix1, &crval1, ctype2_c, &crpix2, &crval2, &cd1_1, 
                &cd1_2, &cd2_1, &cd2_2, radecsys_c, &equinox, &mjdobs) ) {
            throw std::runtime_error("illegal frame");
        }

    // Copy char arrays into strings.
        ctype1 = ctype1_c;
        ctype2 = ctype2_c;
        radecsys = radecsys_c;
    }

/// Get FITS headers
/**
    Generates FITS headers representing the world coordinate system.

    \returns vector of strings containing the header records
*/
    std::vector<std::string> Wcs::getFITSheaders (
            double djm                   ///< epoch of observation (MJD)
    ) const throw (std::runtime_error) {

    // Check the the coordinate system is supported.
        EPOCH epoch = {2000.0, 'J'};
        FRAMETYPE frame;
        if ( typeid(*mRefSys) == typeid(ICRefSys) ) {
            frame = FK5;
        } else if ( typeid(*mRefSys) == typeid(FK5RefSys) ) {
            frame = FK5;
            epoch.year = dynamic_cast<const FK5RefSys*>(&*mRefSys)->equinox();
        } else if ( typeid(*mRefSys) == typeid(ApptRefSys) ) {
            frame = APPT;
        } else if ( typeid(*mRefSys) == typeid(TopoApptRefSys) ) {
            frame = APPT_TOPO;
        } else if ( typeid(*mRefSys) == typeid(AzElRefSys) ) {
            frame = AZEL_TOPO;
        } else if ( typeid(*mRefSys) == typeid(GalacticRefSys) ) {
            frame = GAL;
        } else {
            throw std::runtime_error("frame not supported");
        }

    // Get headers
        char headers[13][81];
        if  (astFITSs( mWcsTrans, frame, epoch, djm, headers[0],
                headers[1], headers[2], headers[3], headers[4], headers[5],
                headers[6], headers[7], headers[8], headers[9], headers[10],
                headers[11], headers[12]) ) {
            throw std::runtime_error("illegal frame");
        }

    // Load headers into return value.
        std::vector<std::string> val;
        for (int i = 0; i < 13; i++ ) {
            val.insert(val.end(), std::string(headers[i]));
        }
        return val;
    }
}

namespace {
    using namespace tcspk;

    int astInvtr ( struct WCS wcs, struct WCS *iwcsp )
    /*
    **  - - - - - - - - -
    **   a s t I n v t r
    **  - - - - - - - - -
    **
    **  Invert a world coordinate system transformation, from x/y-to-sky
    **  to sky-to-x/y or vice versa.
    **
    **  GIVEN:
    **    wcs       struct     WCS transformation
    **
    **  RETURNED (argument):
    **    iwcsp     struct*    pointer to inverse WCS transformation
    **
    **  RETURNED (function value):
    **              int        0 = OK
    **                        -1 = (bad status from slaInvf)
    **
    **  Defined in Wcs.h:
    **    WCS       struct     WCS transformation parameters
    **
    **  Called:  slaInvf
    **
    **  P.T.Wallace   13 August 1999
    **
    **  Copyright CCLRC 1999.  All rights reserved.
    */

    {
        int j;

    /* Copy the field centre. */
        iwcsp->ab0[0] = wcs.ab0[0];
        iwcsp->ab0[1] = wcs.ab0[1];

    /* Invert the affine transformation. */
        slaInvf ( wcs.coeffs, iwcsp->coeffs, &j );
        if ( j ) return -1;

        return 0;
    }

    int astS2xyq ( double a, double b, struct WCS iwcs, double *x, double *y )
    /*
    **  - - - - - - - - -
    **   a s t S 2 x y q
    **  - - - - - - - - -
    **
    **  Transform celestial coordinates into a focal-plane x/y position
    **  using pre-computed WCS parameters.
    **
    **  GIVEN:
    **    a,b     double     RA/Dec or Az/El (radians)
    **    iwcs    struct     WCS parameters for the inverse transformation
    **
    **  RETURNED (argument):
    **    x,y     double*    x/y in focal plane (mm)
    **
    **  RETURNED (function value):
    **            int        0 = OK
    **                      -1 = error, star too far from axis
    **                      -2 = error, antistar on tangent plane
    **                      -3 = error, antistar too far from axis
    **
    **  Called:  slaDs2tp, slaXy2xy
    **
    **  Notes:
    **
    **   1  Azimuths are north-through-east.
    **
    **   2  The x/y coordinates are in the Cassegrain focal-plane and
    **      rotate with the instrument mount.
    **
    **  P.T.Wallace   13 August 1999
    **
    **  Copyright CCLRC 1999.  All rights reserved.
    */
    {
        int j;
        double xi, eta;


    /* Celestial coordinates to standard coordinates. */
        slaDs2tp ( a, b, iwcs.ab0[0], iwcs.ab0[1], &xi, &eta, &j );
        if ( j ) return -j;

    /* Standard coordinates to focal-plane coordinates. */
        slaXy2xy ( xi, eta, iwcs.coeffs, x, y );

        return 0;
    }

    int astXy2sq ( double x, double y, struct WCS wcs, double *a, double *b )
    /*
    **  - - - - - - - - -
    **   a s t X y 2 s q
    **  - - - - - - - - -
    **
    **  Transform a focal-plane x/y position into celestial coordinates
    **  using pre-computed WCS parameters.
    **
    **  GIVEN:
    **    x,y     double     x/y in focal plane (mm)
    **    wcs     struct     WCS parameters
    **
    **  RETURNED (argument):
    **    a,b     double*    RA/Dec or Az/El (radians)
    **
    **  RETURNED (function value):
    **            int        0 = OK (always)
    **
    **  Called:  slaXy2xy, slaDtp2s
    **
    **  Notes:
    **
    **   1  The x/y coordinates are in the Cassegrain focal-plane and
    **      rotate with the instrument mount.
    **
    **   2  Azimuths are north-through-east.
    **
    **  P.T.Wallace   13 August 1999
    **
    **  Copyright CCLRC 1999.  All rights reserved.
    */
    {
        double xi, eta;


    /* Focal-plane coordinates to standard coordinates. */
        slaXy2xy ( x, y, wcs.coeffs, &xi, &eta );

    /* Standard coordinates to celestial coordinates. */
        slaDtp2s ( xi, eta, wcs.ab0[0], wcs.ab0[1], a, b );

        return 0;
    }

    int astFITSs ( struct WCS wcsij,
                        FRAMETYPE frame, struct EPOCH eqx, double djm,
                        char* ctype1, char* crpix1, char* crval1,
                        char* ctype2, char* crpix2, char* crval2,
                        char* cd1_1, char* cd1_2,
                        char* cd2_1, char* cd2_2,
                        char* radecsys, char* equinox, char* mjdobs )
    /*
    **  - - - - - - - - -
    **   a s t F I T S s
    **  - - - - - - - - -
    **
    **  Express a world coordinate system transformation as FITS header
    **  strings.
    **
    **  GIVEN:
    **    wcsij     struct     WCS transformation, pixels to sky
    **    frame     FRAMETYPE  type of sky coordinate system
    **    eqx       struct     equinox (mean RA/Decs only)
    **    djm       double     epoch of observation (MJD: JD-2400000.5)
    **
    **  RETURNED (arguments):
    **    ctype1    char[81]   FITS header record:  CTYPE1
    **    crpix1    char[81]   FITS header record:  CRPIX1
    **    crval1    char[81]   FITS header record:  CRVAL1
    **    ctype2    char[81]   FITS header record:  CTYPE1
    **    crpix2    char[81]   FITS header record:  CRPIX2
    **    crval2    char[81]   FITS header record:  CRVAL2
    **    cd1_1     char[81]   FITS header record:  CD1_1
    **    cd1_2     char[81]   FITS header record:  CD1_2
    **    cd2_1     char[81]   FITS header record:  CD2_1
    **    cd2_2     char[81]   FITS header record:  CD2_2
    **    radecsys  char[81]   FITS header record:  RADECSYS
    **    equinox   char[81]   FITS header record:  EQUINOX
    **    mjdobs    char[81]   FITS header record:  MJD-OBS
    **
    **  RETURNED (function value):
    **              int        0 = OK
    **                        -1 = illegal frame
    **
    **  Called:  astFITSv
    **
    **  Notes:
    **
    **  1  The output strings are exactly 81 characters long.  They have
    **     trailing nulls but no trailing spaces.  (If used to write a
    **     FITS file, trailing spaces must be appended.)
    **
    **  2  The keywords EQUINOX and/or RADECSYS may not be required.  An
    **     empty string is returned in such cases.
    **
    **  3  The timescale for the epoch of observation, djm, is not defined
    **     by the current FITS standard.  TAI is a suitable choice;  UTC
    **     is not, strictly speaking, because expressing UTC as MJD leads
    **     to ambiguities during leap seconds.
    **
    **  4  The present function returns strings.  Another function, astFITSv,
    **     returns values.
    **
    **  5  Here is an example of the set of 13 strings returned by this routine:
    **
    **     CTYPE1  = 'RA---TAN'           / gnomonic projection
    **     CRPIX1  =           984.048024 / pixel i-coordinate at rotator axis
    **     CRVAL1  =       36.00179953283 / RA or Az at rotator axis
    **     CTYPE2  = 'DEC--TAN'           / gnomonic projection
    **     CRPIX2  =           438.647662 / pixel j-coordinate at rotator axis
    **     CRVAL2  =       44.99795763567 / Dec or El at rotator axis
    **     CD1_1   = -0.00001007236440932 / xi rotation/skew/scale matrix element
    **     CD1_2   =  0.00000000574196532 / xj rotation/skew/scale matrix element
    **     CD2_1   = -0.00000000499131497 / yi rotation/skew/scale matrix element
    **     CD2_2   =  0.00001012093669430 / yj rotation/skew/scale matrix element
    **     RADECSYS= 'FK5     '           / type of RA/Dec
    **     EQUINOX =            2000.0000 / epoch of mean equator & equinox
    **     MJD-OBS =     49560.6433912037 / epoch of observation (TAI MJD)
    **
    **  P.T.Wallace   13 August 1999
    **
    **  Copyright CCLRC 1999.  All rights reserved.
    */

    {
        char ctype1_v[9], ctype2_v[9], radecsys_v[9];
        double crpix1_v, crval1_v, crpix2_v, crval2_v,
                    cd1_1_v, cd1_2_v, cd2_1_v, cd2_2_v,
                    equinox_v, mjdobs_v;
        int j;


    /* Get the values. */
        j = astFITSv ( wcsij, frame, eqx, djm,
                                    ctype1_v, &crpix1_v, &crval1_v,
                                    ctype2_v, &crpix2_v, &crval2_v,
                                    &cd1_1_v, &cd1_2_v, &cd2_1_v, &cd2_2_v,
                                    radecsys_v, &equinox_v, &mjdobs_v );
        if ( j ) return j;

    /* Build the strings. */
        sprintf ( ctype1,
                        "CTYPE1  = '%8s'           / gnomonic projection",
                        ctype1_v );
        sprintf ( crpix1,
                        "CRPIX1  = %20.6f / pixel i-coordinate at rotator axis",
                        crpix1_v );
        sprintf ( crval1,
                        "CRVAL1  = %20.11f / RA or Az at rotator axis",
                        crval1_v );
        sprintf ( ctype2,
                        "CTYPE2  = '%8s'           / gnomonic projection",
                        ctype2_v );
        sprintf ( crpix2,
                        "CRPIX2  = %20.6f / pixel j-coordinate at rotator axis",
                        crpix2_v );
        sprintf ( crval2,
                        "CRVAL2  = %20.11f / Dec or El at rotator axis",
                        crval2_v );
        sprintf ( cd1_1,
                        "CD1_1   = %20.17f / xi rotation/skew/scale matrix element",
                        cd1_1_v );
        sprintf ( cd1_2,
                        "CD1_2   = %20.17f / xj rotation/skew/scale matrix element",
                        cd1_2_v );
        sprintf ( cd2_1,
                        "CD2_1   = %20.17f / yi rotation/skew/scale matrix element",
                        cd2_1_v );
        sprintf ( cd2_2,
                        "CD2_2   = %20.17f / yj rotation/skew/scale matrix element",
                        cd2_2_v );
        sprintf ( radecsys,
                        "RADECSYS= '%8s'           / type of RA/Dec",
                        radecsys_v );
        sprintf ( equinox,
                        "EQUINOX = %20.4f / epoch of mean equator & equinox",
                        equinox_v );
        sprintf ( mjdobs,
                        "MJD-OBS = %20.10f / epoch of observation (TAI MJD)",
                        mjdobs_v );

    /* Empty any records which are superfluous for this case. */
        if ( !*radecsys_v ) radecsys[0] = (char) '\0';
        if ( equinox_v < 0.0 ) equinox[0] = (char) '\0';

        return 0;
    }

    int astFITSv ( struct WCS wcsij, FRAMETYPE frame, struct EPOCH eqx, 
            double djm, char* ctype1, double* crpix1, double* crval1,
            char* ctype2, double* crpix2, double* crval2, double* cd1_1, 
            double* cd1_2, double* cd2_1, double* cd2_2, char* radecsys, 
            double* equinox, double* mjdobs )
    /*
    **  - - - - - - - - -
    **   a s t F I T S v
    **  - - - - - - - - -
    **
    **  Express a world coordinate system transformation as FITS keyword
    **  values.
    **
    **  GIVEN:
    **    wcsij     struct     WCS transformation, pixels to sky
    **    frame     FRAMETYPE  type of sky coordinate system
    **    eqx       struct     equinox (mean RA/Decs only)
    **    djm       double     epoch of observation (MJD: JD-2400000.5)
    **
    **  RETURNED (arguments):
    **    ctype1    char[9]    value for FITS keyword CTYPE1
    **    crpix1    double*    value for FITS keyword CRPIX1
    **    crval1    double*    value for FITS keyword CRVAL1
    **    ctype2    char[9]    value for FITS keyword CTYPE1
    **    crpix2    double*    value for FITS keyword CRPIX2
    **    crval2    double*    value for FITS keyword CRVAL2
    **    cd1_1     double*    value for FITS keyword CD1_1
    **    cd1_2     double*    value for FITS keyword CD1_2
    **    cd2_1     double*    value for FITS keyword CD2_1
    **    cd2_2     double*    value for FITS keyword CD2_2
    **    radecsys  char[9]    value for FITS keyword RADECSYS
    **    equinox   double*    value for FITS keyword EQUINOX
    **    mjdobs    double*    value for FITS keyword MJD-OBS
    **
    **  RETURNED (function value):
    **              int        0 = OK
    **                        -1 = illegal frame
    **
    **  Called:  slaDranrm, slaEpco
    **
    **  Notes:
    **
    **  1  The string arguments, ctype1, ctype2 and radecsys, are exactly
    **     nine characters long (i.e. eight characters plus the terminating
    **     null).  They are left-justified, with trailing spaces.
    **
    **  2  The keywords EQUINOX and/or RADECSYS may not be required.  In
    **     such cases, a negative value is returned for equinox and an
    **     empty string for radecsys.
    **
    **  3  The timescale for the epoch of observation, djm, is not defined
    **     by the current FITS standard.  TAI is a suitable choice;  UTC
    **     is not, strictly speaking, because expressing UTC as MJD leads
    **     to ambiguities during leap seconds.
    **
    **  4  The present function returns values.  Another function, astFITSs,
    **     returns strings.  (Note that the argument djm is simply copied to
    **     the argument mjd-obs as it is.  It is included merely to make the
    **     calls to the two functions match.)
    **
    **  5  Here is an example of the set of 13 values returned by this routine:
    **
    **     ctype1    "RA---TAN"            gnomonic projection
    **     crpix1    984.048024            pixel i-coordinate at rotator axis
    **     crval1    36.00179953283        RA or El at rotator axis
    **     ctype2    "DEC--TAN"            gnomonic projection
    **     crpix2    438.647662            pixel j-coordinate at rotator axis
    **     crval2    44.99795763567        Dec or El at rotator axis
    **     cd1_1     -0.00001007236440932  xi rotation/skew/scale matrix element
    **     cd1_2     0.00000000574196532   xj rotation/skew/scale matrix element
    **     cd2_1     -0.00000000499131497  yi rotation/skew/scale matrix element
    **     cd2_2     0.00001012093669430   yj rotation/skew/scale matrix element
    **     radecsys  "FK5     "            type of RA/Dec
    **     equinox   2000.0000             epoch of mean equator & equinox
    **     mjd-obs   49560.6433912037      epoch of observation (TAI MJD)
    **
    **  P.T.Wallace   13 August 1999
    **
    **  Copyright CCLRC 1999.  All rights reserved.
    */

    {
        double a, b, c, d, e, f, det;


    /* Axis types. */
        switch ( frame ) {

        case AZEL_TOPO:
            strcpy ( ctype1, "AZ---TAN" );
            strcpy ( ctype2, "EL---TAN" );
            break;

        case APPT:
        case APPT_TOPO:
        case FK5:
        case FK4:
            strcpy ( ctype1, "RA---TAN" );
            strcpy ( ctype2, "DEC--TAN" );
            break;
            
        case GAL:
            strcpy ( ctype1, "GLON-TAN" );
            strcpy ( ctype2, "GLAT-TAN" );
            break;

        default:
            return -1;
        }

    /* Pixel coordinates of reference point. */
        a = wcsij.coeffs[0];
        b = wcsij.coeffs[1];
        c = wcsij.coeffs[2];
        d = wcsij.coeffs[3];
        e = wcsij.coeffs[4];
        f = wcsij.coeffs[5];
        det = c * e - b * f;
        *crpix1 = ( a * f - c * d ) / det;
        *crpix2 = ( b * d - a * e ) / det;

    /* Sky coordinates of reference point. */
        *crval1 = slaDranrm ( wcsij.ab0[0] ) / TcsLib::d2r;
        *crval2 = wcsij.ab0[1] / TcsLib::d2r;

    /* CD-matrix. */
        *cd1_1 = b / TcsLib::d2r;
        *cd1_2 = c / TcsLib::d2r;
        *cd2_1 = e / TcsLib::d2r;
        *cd2_2 = f / TcsLib::d2r;

    /* RA/Dec system. */
        switch ( frame ) {

        case AZEL_TOPO:
        case GAL:
            radecsys[0] = (char) '\0';
            break;

        case APPT:
        case APPT_TOPO:
            strcpy ( radecsys, "GAPPT   " );
            break;

        case FK5:
            strcpy ( radecsys, "FK5     " );
            break;

        case FK4:
            strcpy ( radecsys, "FK4     " );
            break;

        default:                    /* To suppress compiler warning. */
            break;
        }

    /* Equinox. */
        switch ( frame ) {

        case FK4:
        case FK5:
            *equinox = slaEpco ( frame == FK4 ? 'B' : 'J' , eqx.type, eqx.year );
            break;

        default:
            *equinox = -1.0;
        }

    /* Epoch. */
        *mjdobs = djm;

        return 0;
    }
}

