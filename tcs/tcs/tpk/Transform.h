/// \file Transform.h
/// \brief Definition of the Transform class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkTRANSFORM_H
#define tpkTRANSFORM_H

#include "Coordinates.h"

namespace tpk {

/// Instrument to focal plane transformation
/**
    A Transform object transforms points in one 2D coordinate system to
    another and vice-versa. They are used to transform instrument or
    guider coordinates to the focal plane (the forward
    transformation) and back (the backward transformation).

    The base class implements the identity transformation.

    \attention All classes derived from this class must implement
                    the clone method.

    All the methods of this class are thread safe.
*/
    class Transform {
        public:
            virtual ~Transform() {};

    /// Backwards transformation
    /**
        Transforms focal plane coordinates into instrument or guider
        coordinates.

        \returns position in instrument or guider coordinates
    */
            virtual instrcoord back(
                const focalplane& xy   ///< focal plane coordinates
            ) const {
                return xy;
            }

    /// Forwards transformation
    /**
        Transforms instrument or guider coordinates into focal plane
        coordinates.

        \returns position in focal plane
    */
            virtual focalplane forward(
                const instrcoord& xy   ///< instrument coordinates
            ) const {
                return xy;
            }

    /// Virtual copy constructor
            virtual Transform* clone() const {
                return new Transform(*this);
            }
    };
}
#endif

