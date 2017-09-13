/// \file PointingOrigin.h
/// \brief Definition of the pointing origin class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkPOINTINGORIGIN_H
#define tpkPOINTINGORIGIN_H

#include <memory>
#include <stdexcept>

#include "Coordinates.h"

namespace tpk {
    class Transform;

/// Pointing origin
/**
    A pointing origin represents a point in the focal plane that a virtual
    telescope is tracking. It is defined by an x,y position in some instrument
    related coordinate system, typically but not necessarily pixels on an
    area detector, and the transformation from that coordinate system
    to the focal plane x,y of the pointing kernel. The focal plane coordinate
    system rotates with the instrument rotator so this transformation can
    usually be determined by a one-off calibration procedure and then remains
    fixed for any particular instrument configuration.

    The position in "pixel" coordinates consists of a base position and zero
    or more offsets-from-base. There as well as the usual methods for getting
    and setting these quantities there is a method that absorbs offsets into
    the base position i.e. adds the offset to the base and sets the offset to
    zero such that the net position is unchanged.

    The method for retrieving the focal plane x,y (used inside the pointing
    kernel) takes a time as an argument so that pointing origin classes
    derived from this one can support time varying components such as
    differential rates or scan patterns.

    All classes derived from PointingOrigin must implement the clone method.
*/
    class PointingOrigin {
        public:
        /// PointingOrigin auto_ptr
            typedef std::auto_ptr<PointingOrigin> Ptr;
        /// Const PointingOrigin auto_ptr
            typedef std::auto_ptr<const PointingOrigin> ConstPtr;
            PointingOrigin();
            PointingOrigin(
                const double& xp,
                const double& yp,
                const int& numOffsets = 0
            ) throw (std::domain_error);
            PointingOrigin(
                const double& xp,
                const double& yp,
                const Transform& transf,
                const int& numOffsets = 0
            ) throw (std::domain_error);
            PointingOrigin(
                const PointingOrigin& po
            ) throw();
            virtual PointingOrigin& operator=(
                const PointingOrigin& rhs
            ) throw();
            virtual ~PointingOrigin();

    /// Clone object
            virtual PointingOrigin* clone() const {
                return new PointingOrigin(*this);
            }
            virtual void setBase(
                const double& xp = 0.0,
                const double& yp = 0.0
            );
            virtual focalplane base() const;
            virtual void setOffset(
                const int& n,
                const double& dxp = 0.0,
                const double& dyp = 0.0
            ) throw (std::out_of_range);
            virtual focalplane offset(
                const int& n
            ) const throw (std::out_of_range);
            virtual void absorbOffset(
                const int& n
            ) throw (std::out_of_range);
            virtual focalplane xy(
                const double& t
            ) const;
        protected:
            double mBaseXp;         ///< base position, x
            double mBaseYp;         ///< base position, y
            int mNumOffsets;        ///< number of offsets
            double* mXoffsets;      ///< offsets, x
            double* mYoffsets;      ///< offsets, y
            Transform* mTransf;     ///< focal plane to instrument
                                    ///  coordinate transformation
    };
}
#endif

