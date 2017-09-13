/// \file AzElRefSys.cpp
/// \brief Implementation of the az,el coordinate reference system class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "AzElRefSys.h"

#include "slalib.h"

#include "AzElTarget.h"
#include "KernelAzElRefSys.h"
#include "Site.h"

namespace tpk {

/// Create kernel equivalent reference system.
/**
    \returns pointer to the new kernel reference system object
*/
        KernelRefSys* AzElRefSys::kernelRefSys() const {
            return new KernelAzElRefSys(*this);
        }

/// Convert a position from geocentric apparent to az,el.
/**
    \returns position in topocentric az,el
*/
    spherical AzElRefSys::fromAppt(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< geocentric apparent position
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

    // Convert position to topocentric
        spherical s(p);
        double a, b, ha, dec, ra;
        slaAopqk( s.a, s.b, aoprms, &a, &b, &ha, &dec, &ra);

    // Convert from zenith distance to elevation.
        return spherical(a, TcsLib::d90 - b);
    }

/// Convert a position from ICRS to topocentric az,el.
/**
    \returns position in topocentric az,el
*/
    spherical AzElRefSys::fromICRS(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< ICRS position
    ) const {
        return fromAppt(t, site, ApptRefSys().fromICRS(t, site, p));
    };

/// Convert a position from FK5 to topocentric az,el.
/**
    \returns position in topocentric az,el
*/
    spherical AzElRefSys::fromFK5(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p,        ///< FK5 position
        const double equinox       ///< equinox of position (Julian year)
    ) const {
        return fromAppt(t, site, ApptRefSys().fromFK5(t, site, p, equinox));
    };

/// Convert a position from topocentric apparent to topocentric az,el.
/**
    \returns position in topocentric az,el
*/
    spherical AzElRefSys::fromTopoAppt(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< topocentric apparent position
    ) const {
        return fromAppt(t, site, ApptRefSys().fromTopoAppt(t, site, p));
    };

/// Convert a position from galactic to topocentric az, el.
/**
    \returns position in topocentric az,el
*/
    spherical AzElRefSys::fromGalactic(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< galactic position
    ) const {
        return fromAppt(t, site, ApptRefSys().fromGalactic(t, site, p));
    };
}

