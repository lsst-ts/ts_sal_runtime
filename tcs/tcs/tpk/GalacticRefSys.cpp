/// \file GalacticRefSys.cpp
/// \brief Implementation of the IAU 1950 Galactic coordinate reference system
///        class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "GalacticRefSys.h"

#include "slalib.h"

#include "GalacticTarget.h"
#include "KernelGalacticRefSys.h"

namespace tpk {

/// Create kernel equivalent reference system.
/**
    \returns pointer to the new kernel reference system object
*/
        KernelRefSys* GalacticRefSys::kernelRefSys() const {
            return new KernelGalacticRefSys(*this);
        }

/// Convert a position from ICRS.
/**
    \returns position
*/
    spherical GalacticRefSys::fromICRS(
        const spherical& p         ///< ICRS position
    ) const {
        double l, b;
        slaEqgal(p.a, p.b, &l, &b);
        return spherical(l, b);
    }

/// Convert a position from FK5.
/**
    \returns position
*/
    spherical GalacticRefSys::fromFK5(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p,        ///< FK5 position
        const double equinox       ///< equinox of position (Julian year)
    ) const {
        return fromICRS(t, site, ICRefSys().fromFK5(t, site, p, equinox));
    };

/// Convert a position from geocentric apparent.
/**
    \returns position
*/
    spherical GalacticRefSys::fromAppt(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< geocentric apparent position
    ) const {
        return fromICRS(t, site, ICRefSys().fromAppt(t, site, p));
    };

/// Convert a position from topocentric apparent.
/**
    \returns position
*/
    spherical GalacticRefSys::fromTopoAppt(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< topcentric apparent position
    ) const {
        return fromICRS(t, site, ICRefSys().fromTopoAppt(t, site, p));
    };

/// Convert a position from topocentric az,el.
/**
    \returns position
*/
    spherical GalacticRefSys::fromAzEl(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< topcentric az,el position
    ) const {
        return fromICRS(t, site, ICRefSys().fromAzEl(t, site, p));
    };
}

