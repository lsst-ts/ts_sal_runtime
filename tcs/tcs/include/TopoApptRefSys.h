/// \file TopoApptRefSys.h
/// \brief Definition of the topocentric apparent coordinate reference system 
///        class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkTOPOAPPTREFSYS_H
#define tpkTOPOAPPTREFSYS_H

#include "ApptRefSys.h"
#include "AzElRefSys.h"
#include "FK5RefSys.h"
#include "GalacticRefSys.h"
#include "ICRefSys.h"
#include "TopoApptTarget.h"
#include "RefSys.h"

namespace tpk {
    class Site;
    class KernelRefSys;
    struct vector;

/// Topocentric Apparent Reference System
    class TopoApptRefSys : public RefSys {
        public:

        /// Virtual copy constructor
        /**
            \returns pointer to the new TopApptRefSys object
        */
            virtual TopoApptRefSys* clone() const {
                return new TopoApptRefSys(*this);
            }

        /// Create an topocentric apparent target from spherical coordinates
        /**
            \returns pointer to the new target
        */
            virtual TopoApptTarget* target(
                const Site& site,          ///< telescope site
                const vector& p            ///< coordinates
            ) const {
                return new TopoApptTarget(site, p);
            }

        /// Create an topocentric apparent target from a string
        /**
            \returns pointer to the new target
        */
            virtual TopoApptTarget* target(
                const Site& site,          ///< telescope site
                const std::string& p       ///< position
            ) const {
                return new TopoApptTarget(site, p);
            }

        /// Convert a position from topocentric apparent.
        /**
            \returns topocentric apparent position
        */
            virtual spherical fromTopoAppt(
                const double& t,           ///< time (TAI)
                const Site& site,          ///< site
                const spherical& p         ///< topocentric apparent position
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

