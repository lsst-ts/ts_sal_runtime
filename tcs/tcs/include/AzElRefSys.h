/// \file AzElRefSys.h
/// \brief Definition of the Az,El coordinate reference system class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkAZELREFSYS_H
#define tpkAZELREFSYS_H

#include "ApptRefSys.h"
#include "AzElTarget.h"
#include "RefSys.h"

namespace tpk {
    class Site;
    class KernelRefSys;
    struct vector;

/// Topocentric Az,El Reference System
/**
    The zero-point of azimuth is the celestial intermediate pole and azimuth
    increases to the East.
*/
    class AzElRefSys : public RefSys {
        public:

        /// Virtual copy constructor
        /**
            \returns pointer to the new AzElRefSys object
        */
            virtual AzElRefSys* clone() const {
                return new AzElRefSys(*this);
            }

        /// Create an Az,El target from spherical coordinates
        /**
            \returns pointer to the new target
        */
            virtual AzElTarget* target(
                const Site& site,          ///< telescope site
                const vector& p            ///< coordinates
            ) const {
                return new AzElTarget(site, p);
            }

        /// Create an Az,El target from a string
        /**
            \returns pointer to the new target
        */
            virtual AzElTarget* target(
                const Site& site,          ///< telescope site
                const std::string& p       ///< position
            ) const {
                return new AzElTarget(site, p);
            }

        /// Convert a position from az,el to az,el.
        /**
            \returns position in topocentric az,el
        */
            virtual spherical fromAzEl(
                const double& t,           ///< time (TAI)
                const Site& site,          ///< site
                const spherical& p         ///< galactic position
            ) const {
                return p;
            }

            virtual spherical fromICRS(
                const double& t,
                const Site& site,
                const spherical& p
            ) const;

            virtual spherical fromFK5(
                const double& t,
                const Site& site,
                const spherical& p,
                const double equinox
            ) const;

            virtual spherical fromAppt(
                const double& t,
                const Site& site,
                const spherical& p
            ) const;

            virtual spherical fromTopoAppt(
                const double& t,
                const Site& site,
                const spherical& p
            ) const;

            virtual spherical fromGalactic(
                const double& t,
                const Site& site,
                const spherical& p
            ) const;

            virtual KernelRefSys* kernelRefSys() const;
    };
}
#endif

