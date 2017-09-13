/// \file TopoApptRefSys.cpp
/// \brief Implementation of the topocentric apparent coordinate reference 
///        system class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "TopoApptRefSys.h"

#include "slalib.h"

#include "TopoApptTarget.h"
#include "KernelTopoApptRefSys.h"

namespace tpk {

/// Create kernel equivalent reference system.
/**
    \returns pointer to the new kernel reference system object
*/
        KernelRefSys* TopoApptRefSys::kernelRefSys() const {
            return new KernelTopoApptRefSys(*this);
        }

// Convert a position from geocentric apparent to topocentric apparent.
/**
    \returns position in topocentric az,el
*/
    spherical TopoApptRefSys::fromAppt(
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
        return spherical(ra, dec);
    }

/// Convert a position from ICRS to topocentric apparent.
/**
    \returns position in topocentric apparent
*/
    spherical TopoApptRefSys::fromICRS(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< ICRS position
    ) const {
        return fromAppt(t, site, ApptRefSys().fromICRS(t, site, p));
    };

/// Convert a position from FK5 to topocentric apparent.
/**
    \returns position in topocentric apparent
*/
    spherical TopoApptRefSys::fromFK5(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p,        ///< FK5 position
        const double equinox       ///< equinox of position (Julian year)
    ) const {
        return fromAppt(t, site, ApptRefSys().fromFK5(t, site, p, equinox));
    };

/// Convert a position from topocentric az, el to topocentric appranet.
/**
    \returns position in topocentric apparent
*/
    spherical TopoApptRefSys::fromAzEl(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< topocentric az,el position
    ) const {
        return fromAppt(t, site, ApptRefSys().fromAzEl(t, site, p));
    };

/// Convert a position from galactic to topocentric apparent.
/**
    \returns position in topocentric apparent
*/
    spherical TopoApptRefSys::fromGalactic(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< galactic position
    ) const {
        return fromAppt(t, site, ApptRefSys().fromGalactic(t, site, p));
    };
}

