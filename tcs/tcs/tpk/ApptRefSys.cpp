/// \file ApptRefSys.cpp
/// \brief Implementation of the geocentric apparent coordinate reference 
//         system class.
   
// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "ApptRefSys.h"

#include "slalib.h"

#include "ApptTarget.h"
#include "KernelApptRefSys.h"

namespace tpk {

/// Create kernel equivalent reference system.
/**
    \returns pointer to the new kernel reference system object
*/
        KernelRefSys* ApptRefSys::kernelRefSys() const {
            return new KernelApptRefSys(*this);
        }
        
/// Convert a position from ICRS.
/**
    \returns position in geocentric apparent
*/
    spherical ApptRefSys::fromICRS(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< ICRS position
    ) const {

    // Get apparent to mean parameters from the site.
        double amprms[21];
        site.amprms(amprms);

    // Convert position to apparent place.
        double a, b;
        slaMapqkz( p.a, p.b, amprms, &a, &b);
        return spherical(a, b);
    }

/// Convert a position from topocentric apparent.
/**
    \returns position geocentric apparent
*/
    spherical ApptRefSys::fromTopoAppt(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< topcentric apparent position
    ) const {

    // Get apparent to observed parameters from the site.
        double aoprms[14];
        site.aoprms(aoprms);

    // Eliminate refraction.
        aoprms[6] = 0.0;
        aoprms[10] = 0.0;
        aoprms[11] = 0.0;

    // Update sidereal time.
        aoprms[13] = site.st(t);

    // Convert position to geocentric apparent.
        double a, b;
        slaOapqk( "R", p.a, p.b, aoprms, &a, &b);
        return spherical(a, b);
    }

/// Convert a position from topocentric az,el.
/**
    \returns position geocentric apparent
*/
    spherical ApptRefSys::fromAzEl(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< topcentric az,el position
    ) const {

    // Get apparent to observed parameters from the site.
        double aoprms[14];
        site.aoprms(aoprms);

    // Eliminate refraction.
        aoprms[6] = 0.0;
        aoprms[10] = 0.0;
        aoprms[11] = 0.0;

    // Update sidereal time.
        aoprms[13] = site.st(t);

    // Convert position to geocentric apparent.
        double a, b;
        slaOapqk( "A", p.a, TcsLib::d90 - p.b, aoprms, &a, &b);
        return spherical(a, b);
    }

/// Convert a position from FK5.
/**
    \returns position geocentric apparent
*/
    spherical ApptRefSys::fromFK5(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p,        ///< FK5 position
        const double equinox       ///< equinox of position (Julian year)
    ) const {
        return fromICRS(t, site, ICRefSys().fromFK5(t, site, p, equinox));
    };

/// Convert a position from Galactic.
/**
    \returns position geocentric apparent
*/
    spherical ApptRefSys::fromGalactic(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< galactic position
    ) const {
        return fromICRS(t, site, ICRefSys().fromGalactic(t, site, p));
    };
}

