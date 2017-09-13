/// \file ICRefSys.cpp
/// \brief Implementation of the international coordinate reference system 
///        class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "ICRefSys.h"

#include "slalib.h"

#include "FK5RefSys.h"
#include "ICRSTarget.h"
#include "KernelICRefSys.h"

namespace tpk {

/// Create kernel equivalent reference system.
/**
    \returns pointer to the new kernel reference system object
*/
    KernelRefSys* ICRefSys::kernelRefSys() const {
        return new KernelICRefSys(*this);
    }

/// Convert a position from FK5.
/**
    \returns position in ICRS
*/
    spherical ICRefSys::fromFK5(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p,        ///< FK5 position
        const double equinox       ///< equinox of position (Julian year)
    ) const {

    // ICRS is equivalent to FK5/J2000
        return FK5RefSys(2000.0).fromFK5(t, site, p, equinox);
    }

/// Convert a position from geocentric apparent.
/**
    \returns position in ICRS
*/
    spherical ICRefSys::fromAppt(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< geocentric apparent position
    ) const {

    // Get apparent to mean parameters from the site.
        double amprms[21];
        site.amprms(amprms);

    // Convert position to ICRF.
        double a, b;
        slaAmpqk( p.a, p.b, amprms, &a, &b);
        return spherical(a, b);
    }

/// Convert a position from Galactic.
/**
    \returns position in ICRS
*/
    spherical ICRefSys::fromGalactic(
        const spherical& p         ///< galactic position
    ) const {
        double a, b;
        slaGaleq(p.a, p.b, &a, &b);
        return spherical(a, b);
    }

/// Convert a position from topocentric apparent.
/**
    \returns position in ICRS
*/
    spherical ICRefSys::fromTopoAppt(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< topcentric apparent position
    ) const {
        return fromAppt(t, site, ApptRefSys().fromTopoAppt(t, site, p));
    };

/// Convert a position from topocentric az,el.
/**
    \returns position in ICRS
*/
    spherical ICRefSys::fromAzEl(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< topcentric az,el position
    ) const {
        return fromAppt(t, site, ApptRefSys().fromAzEl(t, site, p));
    };
}

