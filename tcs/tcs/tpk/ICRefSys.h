/// \file ICRefSys.h
/// \brief Definitions of the international coordinate reference system class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkICREFSYS_H
#define tpkICREFSYS_H

#include <string>

#include "ApptRefSys.h"
#include "RefSys.h"
#include "ICRSTarget.h"

namespace tpk {
    class Site;
    class KernelRefSys;
    struct vector;

/// International Celestial Reference System
/**
    This system is not yet supported by the kernel and is approximated by
    FK5/2000.0.
*/
    class ICRefSys : public RefSys {
        public:

        /// Virtual copy constructor
        /**
            \returns pointer to the new ICRefSys object
        */
            virtual ICRefSys* clone() const {
                return new ICRefSys(*this);
            }

        /// Create an ICRS target from spherical coordinates
        /**
            \returns pointer to the new target
        */
            virtual ICRSTarget* target(
                const Site& site,          ///< telescope site
                const vector& p            ///< coordinates
            ) const {
                return new ICRSTarget(site, p);
            }

        /// Create an ICRS target from a string
        /**
            \returns pointer to the new target
        */
            virtual ICRSTarget* target(
                const Site& site,          ///< telescope site
                const std::string& p       ///< position
            ) const {
                return new ICRSTarget(site, p);
            }

        /// Convert a position from ICRS.
        /**
            \returns position in ICRS
        */
            virtual spherical fromICRS(
                const double& t,           ///< time (TAI)
                const Site& site,          ///< site
                const spherical& p         ///< ICRS position
            ) const {
                return p;
            }

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

            virtual spherical fromAzEl(
                const double& t,
                const Site& site,
                const spherical& p
            ) const;

        /// Convert a position from Galactic.
        /**
            \returns position in ICRS
        */
            virtual spherical fromGalactic(
                const double& t,           ///< time (TAI)
                const Site& site,          ///< site
                const spherical& p         ///< ICRS position
            ) const {
                return fromGalactic(p);
            }
            
            virtual spherical fromGalactic(
                const spherical& p
            ) const;

            virtual KernelRefSys* kernelRefSys() const;
    };
}
#endif

