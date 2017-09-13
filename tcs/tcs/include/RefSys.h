/// \file RefSys.h
/// \brief Definition of the coordinate reference system class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkREFSYS_H
#define tpkREFSYS_H

#include <memory>
#include <stdexcept>
#include <typeinfo>

#include "Coordinates.h"
#include "TcsLib.h"

namespace tpk {
    class Site;
    class Target;
    class KernelRefSys;

/// Virtual base class reference systems
/**
    The RefSys class is a virtual base class for sky coordinate reference
    systems.

    Reference systems implement methods for creating a new target in that
    reference system and for creating an equivalent kernel reference system
    object.

    \attention All classes derived from RefSys must implement the kernelRefSys
               and clone methods.
*/
    class RefSys {
        public:
        
        /// RefSys auto_ptr
            typedef std::auto_ptr<RefSys> Ptr;
        /// Const RefSys auto_ptr
            typedef std::auto_ptr<const RefSys> ConstPtr;
        
        protected:
        /// Default constructor
        /**
            The default constructor is protected so that only derived classes
            can call it.
        */
            RefSys() {}
        public:

        /// Virtual copy constructor
        /**
            \returns pointer to the new RefSys object
        */
            virtual RefSys* clone() const = 0;

        /// Virtual destructor
            virtual ~RefSys() {}

        /// Create kernel equivalent reference system.
        /**
            \returns pointer to the new kernel reference system object
        */
            virtual KernelRefSys* kernelRefSys() const = 0;

        /// Create target from spherical coordinates
        /**
            Creates a new target in the reference coordinate system.

            \returns pointer to the new target
        */
            virtual Target* target(
                const Site& site,          ///< telescope site
                const vector& p            ///< coordinates
            ) const = 0;

        /// Create target from a string
        /**
            Creates a new target in the reference coordinate system.

            \returns pointer to the new target
        */
            virtual Target* target(
                const Site& site,          ///< telescope site
                const std::string& p       ///< position
            ) const = 0;

        /// Equal to operator
        /**
            The default behaviour is to assume that all object of the same
            class are identical.
        */
            virtual bool operator==(
                const RefSys& rhs
            ) const {
                return (typeid(*this) == typeid(rhs)) != 0;
            }

        /// Not equal to operator
        /**
            The default behaviour is to assume that all object of the same
            class are identical.
        */
            virtual bool operator!=(
                const RefSys& rhs
            ) const {
                return !(*this == rhs);
            }

        /// Convert a position from ICRS.
        /**
            \returns position
        */
            virtual spherical fromICRS(
                const double& t,           ///< time (TAI)
                const Site& site,          ///< site
                const spherical& p         ///< ICRS position
            ) const = 0;

        /// Convert a position from FK5.
        /**
            \returns position
        */
            virtual spherical fromFK5(
                const double& t,          ///< time (TAI)
                const Site& site,         ///< site
                const spherical& p,       ///< FK5 position
                const double equinox      ///< equinox of position (Julian year)
            ) const = 0;

        /// Convert a position from geocentric apparent.
        /**
            \returns position
        */
            virtual spherical fromAppt(
                const double& t,          ///< time (TAI)
                const Site& site,         ///< site
                const spherical& p        ///< geocentric apparent position
            ) const = 0;

        /// Convert a position from topocentric apparent.
        /**
            \returns position
        */
            virtual spherical fromTopoAppt(
                const double& t,           ///< time (TAI)
                const Site& site,          ///< site
                const spherical& p         ///< topcentric apparent position
            ) const = 0;

        /// Convert a position from topocentric az,el.
        /**
            \returns position
        */
            virtual spherical fromAzEl(
                const double& t,           ///< time (TAI)
                const Site& site,          ///< site
                const spherical& p         ///< topcentric az,el position
            ) const = 0;

        /// Convert a position from Galactic.
        /**
            \returns position
        */
            virtual spherical fromGalactic(
                const double& t,           ///< time (TAI)
                const Site& site,          ///< site
                const spherical& p         ///< galactic position
            ) const = 0;
    };
}
#endif

