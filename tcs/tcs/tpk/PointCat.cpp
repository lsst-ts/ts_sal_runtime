/// \file PointCat.cpp
/// \brief Definition of the pointing catalogue class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "PointCat.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include "slalib.h"

#include "FK5Target.h"
#include "ICRefSys.h"
#include "Site.h"

using std::string;
using std::getline;
using std::ifstream;

namespace {
    void starob ( double, double, double, double, double, double,
            double*, double*, double*, double*  );
}

namespace tpk {
/**
    Creates a PointCat object and loads the contents of the specified
    file into it. The file must be in the format used by TPOINT for
    star catalogs.

    \exception std::runtime_error
*/
    PointCat::PointCat(
        const Site& site,                ///< telescope site
        const std::string& filename      ///< name of file containing catalog
    ) throw(std::runtime_error,std::ios::failure) : mSite(site) {

    // Open the file.
        ifstream file( filename.c_str() );
        if ( ! file ) {
            throw std::runtime_error("Unable to open catalog file");
        }
        file.exceptions(std::ios::badbit);

    // Get the first line from the file.
        string token("");

    // If it is the string "END" or we have reached the end of the file
    // then we are done.
        while ( ! file.eof() ) {

        // Read the first token from the line.
            file >> token;

        // If the token is "END" then we are done.
            if ( token == "END" ) break;

        // if the token is empty or the first character is a "!" then just skip
        // it.
            if ( token.empty() ) {
                continue;
            }
            if ( token.at(0) == '!' ) {
                getline( file, token, '\n');
                continue;
            }

        // Read the rest of the line into the catalogue entry.
            struct record e;
            getline( file, e.star, '\n');

        // Initialize the flag.
            e.flag = 0;

        // Create a target object from the string
            e.target = new FK5Target(mSite, e.star);

        // Insert the entry into the catalogue.
            mCatalog.push_back(e);
        }

    // Check that there were some stars in the catalogue.
        if (mCatalog.empty()) {
            throw std::runtime_error("catalog is empty");
        }
    }
    PointCat::~PointCat() {

    // Delete all the target objects the catalogue points to.
        for ( unsigned int i = 0; i < mCatalog.size(); i++ ) {
            delete mCatalog[i].target;
        }
    }

/// Get a star from the catalog
/**
    Returns the catalog entry, observed Az,El and flag for the entry with
    the specified index.

    \exception std::out_of_range
*/
    void PointCat::entry(
        const size_t& index, ///< index of entry (0..n)
        Target*& target,     ///< pointer to catalog entry
        double& azob,        ///< observed azimuth (radians)
        double& elob,        ///< observed elevation (radians)
        int& flag            ///< flag (general-purpose)
    ) throw(std::out_of_range)  {


    // Target.
        target = mCatalog[index].target;

    // RA, Dec.
        spherical tar = mCatalog[index].target->position(mSite.tai(),
                ICRefSys());

    // Approximate ICRS to apparent RA,Dec & Az,El (IAU 2000 conventions). */
        double hob, dob;
        starob ( mSite.tai() - mSite.delat() + mSite.delut(),
                    mSite.pressure(), mSite.elongitude(), 
                    mSite.latitude(), tar.a, tar.b, &azob, &elob, &hob, 
                    &dob );

    // Flag
        flag = mCatalog[index].flag;
    }

/// Set a flag value
/**
    Sets the value of the flag associated with the specified catalog entry.

    \exception std::out_of_range
*/
    void PointCat::flag(
        const size_t& index,  ///< index of entry
        const int& value      ///< new value for flag
    ) throw(std::out_of_range) {
        mCatalog.at(index).flag = value;
    }

/// Set all flag values
/**
    Sets the value of the flag associated with all catalog entry,

*/
    void PointCat::flag(
        const int& value      ///< new value for flag
    ) throw() {
        for (size_t j(0); j < mCatalog.size(); j++ ) {
            mCatalog[j].flag = value;
        }
    }

/// Get a flag value
/**
    Gets the value of the flag associated with the specified catalog entry.

    \returns flag value

    \exception std::out_of_range
*/
    int PointCat::flag(
        const size_t& index      ///< index of entry
    ) throw(std::out_of_range) {
        return mCatalog.at(index).flag;
    }
}

#include <math.h>

namespace {
    void starob ( double ut1, double press, double elong, double phi,
            double r2000, double d2000, double *aob, double *eob, double *hob, 
            double *dob )

    /*
    **  - - - - - - -
    **   s t a r o b
    **  - - - - - - -
    **
    **  Star RA,Dec (ICRS) to observed Az,El and HA,Dec, accurate to
    **  about 1 arcsecond for dates between 1950 and 2100, elevations
    **  above 25 deg and V color.
    **
    **  Given:
    **     ut1      d    UT1 as Modified Julian Date (JD-2400000.5)
    **     press    d    air pressure in mB (=hPa)
    **     elong    d    longitude (radians, E +ve)
    **     phi      d    latitude (radians)
    **     r2000    d    ICRF (i.e. J2000) right ascension (radians)
    **     d2000    d    ICRF (i.e. J2000) declination (radians)
    **     ht       d    topocentric hour angle (radians)
    **     dt       d    topocentric declination (radians)
    **
    **  Returned:
    **     aob      d*   observed azimuth (radians, N thru E)
    **     eob      d*   observed elevation (radians)
    **     hob      d*   observed hour angle (radians)
    **     dob      d*   observed declination (radians)
    **
    **  Notes:
    **
    **  1  The distinction between UT1 and UTC is important for this
    **     routine, given the 1 arcsec accuracy goal.  Starting with UTC
    **     read from a clock, it is necessary to add the current UT1-UTC
    **     value, which can be obtained from the IERS.  However, in a
    **     telescope without absolute encoders that is always zeroed
    **     on the first star, neglecting UT1-UTC will automatically be
    **     canceled out.
    **
    **  2  Starting with RA,Dec from a star catalog, the star position
    **     must be updated for proper motion before the present function
    **     is called.
    **
    **  3  The "observed" place is where the telescope needs to be
    **     pointed in order to see the star (not counting instrumental
    **     effects).
    **
    **  Latest revision:   21 December 2003
    **
    **  Copyright P.T.Wallace, Tpoint Software, UK.  All rights reserved.
    */

    {
        double c, x0, y0, z0, t, a, b, n, d, e, p, q, l, w, xc, yc, z,
                    eral, s, xt, y, xh, zh, xe, ze;


    /* ---------------------------------------------------------------- */
    /* Approximate ICRS RA,Dec to apparent place (IAU 2000 conventions) */
    /* ---------------------------------------------------------------- */

    /* J2000 RA,Dec to vector. */
        c = cos(d2000);
        x0 = cos(r2000)*c;
        y0 = sin(r2000)*c;
        z0 = sin(d2000);

    /* Precession, nutation and aberration quantities. */
        t = ut1 - 51544.5;            /* Days since fundamental epoch. */
        a = 2.66e-7*t;                /* Precession X */
        b = -8.14e-14*t*t;            /* Precession Y */
        n = 2.182 - 9.242e-4*t;       /* Longitude of Moon's ascending node */
        d = -33e-6*sin(n);            /* Nutation X */
        e = 45e-6*cos(n);             /* Nutation Y */
        p = a + d;                    /* X */
        q = b + e;                    /* Y */
        l = 4.895 + 1.72021e-2*t;     /* Sun's geometric longitude */

    /* Apply precession/nutation/aberration to give NRO-based apparent. */
        c = cos(l);
        w = 1.0 - p*p/2.0;
        xc = w*x0 - p*z0 + 0.99e-4*sin(l);
        yc = y0 - q*z0 - 0.91e-4*c;
        z = p*x0 + q*y0 + w*z0 - 0.40e-4*c;

    /* ----------------------------------------------------- */
    /* Celestial to terrestrial (using Earth Rotation Angle) */
    /* ----------------------------------------------------- */

        eral = elong + 6.2831853071796 *
                    fmod ( 0.7790572732640 + 1.00273781191135448 * t, 1.0 );
        s = sin(eral);
        c = cos(eral);
        xt = xc*c + yc*s;
        y = -xc*s + yc*c;

    /* -------------------------------------------------------- */
    /* Approximate refraction, giving observed Az,El and HA,Dec */
    /* -------------------------------------------------------- */

    /* Rotate into horizon coordinates. */
        s = sin(phi);
        c = cos(phi);
        xh = xt*s - z*c;
        zh = xt*c + z*s;

    /* Apply the refraction (fixed below about 6 deg elevation. */
        zh += 2.82e-7*press/(zh>0.1 ? zh : 0.1);

    /* Vector to observed Az,El. */
        *aob = y !=0.0 || xh != 0.0 ? atan2(y,-xh) : 0.0;
        *eob = atan2(zh,sqrt(xh*xh+y*y));

    /* Rotate into equator coordinates. */
        xe = xh*s + zh*c;
        ze = -xh*c + zh*s;

    /* Vector to observed HA,Dec. */
        *hob = y !=0.0 || xe != 0.0 ? atan2(y,xe) : 0.0;
        *dob = atan2(ze,sqrt(xe*xe+y*y));

    }
}

