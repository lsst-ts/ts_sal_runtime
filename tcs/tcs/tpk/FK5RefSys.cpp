/// \file FK5RefSys.cpp
/// \brief Implementation of the FK5 coordinate reference system class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "FK5RefSys.h"

#include "slalib.h"

#include "FK5Target.h"
#include "KernelFK5RefSys.h"

namespace tpk {

/// Create kernel equivalent reference system.
/**
    \returns pointer to the new kernel reference system object
*/
        KernelRefSys* FK5RefSys::kernelRefSys() const {
            return new KernelFK5RefSys(*this);
        }

/// Equal to operator
/**
    FK5 systems are only equal if their equinox's are equal.
*/
    bool FK5RefSys::operator==(
        const RefSys& rhs
    ) const {
        if ( typeid(FK5RefSys) == typeid(rhs) ) {
            return mEquinox == dynamic_cast<const FK5RefSys&>(rhs).mEquinox;
        } else {
            return false;
        }
    }

/// Convert a position from ICRS.
/**
    \returns position in FK5
*/
    spherical FK5RefSys::fromICRS(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< ICRS position
    ) const {

    // ICRS is equivalent to FK5/J2000
        return fromFK5(t, site, p, 2000.0);
    }

/// Convert a position from FK5.
/**
    \returns position in FK5
*/
    spherical FK5RefSys::fromFK5(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p,        ///< FK5 position
        const double equinox       ///< equinox of position (Julian year)
    ) const {

    // Precess to out equinox.
        vector v(p);
        double prepre[3][3];
        slaPrec( equinox, mEquinox, prepre);
        vector result;
        slaDmxv( prepre, &v.x, &result.x);
        return result;
    }

/// Convert a position from geocentric apparent.
/**
    \returns position in FK5
*/
    spherical FK5RefSys::fromAppt(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< geocentric apparent position
    ) const {
        return fromICRS(t, site, ICRefSys().fromAppt(t, site, p));
    };

/// Convert a position from topocentric apparent.
/**
    \returns position in FK5
*/
    spherical FK5RefSys::fromTopoAppt(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< topcentric apparent position
    ) const{
        return fromICRS(t, site, ICRefSys().fromTopoAppt(t, site, p));
    };

/// Convert a position from topocentric az,el.
/**
    \returns position in FK5
*/
    spherical FK5RefSys::fromAzEl(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< topcentric az,el position
    ) const{
        return fromICRS(t, site, ICRefSys().fromAzEl(t, site, p));
    };

/// Convert a position from Galactic.
/**
    \returns position in FK5
*/
    spherical FK5RefSys::fromGalactic(
        const double& t,           ///< time (TAI)
        const Site& site,          ///< site
        const spherical& p         ///< galactic position
    ) const{
        return fromICRS(t, site, ICRefSys().fromGalactic(t, site, p));
    };
}

