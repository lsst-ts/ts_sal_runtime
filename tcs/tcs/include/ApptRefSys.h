/// \file ApptRefSys.h
/// \brief Definitions of the Geocentric Apparent coordinate reference system 
///        classes.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkAPPTREFSYS_H
#define tpkAPPTREFSYS_H

#include "ICRefSys.h"
#include "ApptTarget.h"
#include "RefSys.h"

namespace tpk {
    class Site;
    class KernelRefSys;
    struct vector;

/// Geocentric Apparent Reference System
    class ApptRefSys : public RefSys {
        public:

        /// Virtual copy constructor
        /**
            \returns pointer to the new ApptRefSys object
        */
            virtual ApptRefSys* clone() const {
                return new ApptRefSys(*this);
            }

        /// Create an geocentric apparent target from spherical coordinates
        /**
            \returns pointer to the new target
        */
            virtual ApptTarget* target(
                const Site& site,          ///< telescope site
                const vector& p            ///< coordinates
            ) const {
                return new ApptTarget(site, p);
            }

        /// Create an geocentric apparent target from a string
        /**
            \returns pointer to the new target
        */
            virtual ApptTarget* target(
                const Site& site,          ///< telescope site
                const std::string& p       ///< position
            ) const {
                return new ApptTarget(site, p);
            }

        /// Convert a position from geocentric apparent.
        /**
            \returns position geocentric apparent
        */
            virtual spherical fromAppt(
                const double& t,           ///< time (TAI)
                const Site& site,          ///< site
                const spherical& p         ///< geocentric apparent position
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

            virtual spherical fromGalactic(
                const double& t,
                const Site& site,
                const spherical& p
            ) const;

            virtual KernelRefSys* kernelRefSys() const;
    };
}
#endif

