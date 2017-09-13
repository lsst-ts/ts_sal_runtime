/// \file GalacticRefSys.h
/// \brief Definitions of the geocentric apparent coordinate reference system 
///        class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkGALACTICREFSYS_H
#define tpkGALACTICREFSYS_H

#include "ICRefSys.h"
#include "GalacticTarget.h"
#include "RefSys.h"

namespace tpk {
    class Site;
    class KernelRefSys;
    struct vector;

/// IAU 1950 Galactice Coordinate Reference System
    class GalacticRefSys : public RefSys {
        public:

        /// Virtual copy constructor
        /**
            \returns pointer to the new GalacticRefSys object
        */
            virtual GalacticRefSys* clone() const {
                return new GalacticRefSys(*this);
            }

        /// Create an galactic target from spherical coordinates
        /**
            \returns pointer to the new target
        */
            virtual GalacticTarget* target(
                const Site& site,          ///< telescope site
                const vector& p            ///< coordinates
            ) const {
                return new GalacticTarget(site, p);
            }

        /// Create an galactic target from a string
        /**
            \returns pointer to the new target
        */
            virtual GalacticTarget* target(
                const Site& site,          ///< telescope site
                const std::string& p       ///< position
            ) const {
                return new GalacticTarget(site, p);
            }


        /// Convert a position from Galactic.
        /**
            \returns position
        */
            virtual spherical fromGalactic(
                const double& t,           ///< time (TAI)
                const Site& site,          ///< site
                const spherical& p         ///< galactic position
            ) const {
                return p;
            }

        /// Convert a position from ICRS.
        /**
            \returns position
        */
            virtual spherical fromICRS(
                const double& t,           ///< time (TAI)
                const Site& site,          ///< site
                const spherical& p         ///< galactic position
            ) const {
                return fromICRS(p);
            }
            
            virtual spherical fromICRS(
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

            virtual spherical fromAzEl(
                const double& t,
                const Site& site,
                const spherical& p
            ) const;

            virtual KernelRefSys* kernelRefSys() const;
    };
}
#endif

