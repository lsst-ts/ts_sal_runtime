/// \file FK5RefSys.h
/// \brief Definitions of the FK5 coordinate reference system classes.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkFK5REFSYS_H
#define tpkFK5REFSYS_H

#include "ICRefSys.h"
#include "RefSys.h"
#include "FK5Target.h"

namespace tpk {
    class KernelRefSys;
    class Site;
    struct vector;

/// FK5 reference frame
    class FK5RefSys : public RefSys {
        protected:
            const double mEquinox;         ///< equinox of frame
        public:

        /// Default constructor
            FK5RefSys(
                double eqx = 2000.0        ///< equinox of frame
            ) : mEquinox(eqx) {}

        /// Virtual copy constructor
        /**
            \returns pointer to the new FK5RefSys object
        */
            virtual FK5RefSys* clone() const {
                return new FK5RefSys(*this);
            }

        /// Equinox
        /*
            \returns equinox of frame as Julian year
        */
            virtual double equinox() const {
                return mEquinox;
            }

        /// Create an FK5 target from spherical coordinates
        /**
            \returns pointer to the new target
        */
            virtual FK5Target* target(
                const Site& site,          ///< telescope site
                const vector& p            ///< coordinates
            ) const {
                return new FK5Target(site, p, mEquinox);
            }

        /// Create an FK5 target from a string
        /**
            \returns pointer to the new target
        */
            virtual FK5Target* target(
                const Site& site,          ///< telescope site
                const std::string& p       ///< position
            ) const {
                return new FK5Target(site, p);
            }

            virtual bool operator==(
                const RefSys& rhs
            ) const;

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

