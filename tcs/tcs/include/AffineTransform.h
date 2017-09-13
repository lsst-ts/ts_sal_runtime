/// \file AffineTransform.h
/// \brief Definition of the AffineTransform class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkAFFINETRANSFORM_H
#define tpkAFFINETRANSFORM_H

#include <stdexcept>

#include "Coordinates.h"
#include "Transform.h"

namespace tpk {

/// Affine transformation
/**
    An AffineTransform object transforms a points in instrument (or guider)
    coordinates to the equivalent point in the focal plane coordinates
    and vice-versa with an affine transformation (i.e. rotation, scaling
    and shear).

    All the methods of this class are thread safe.
*/
    class AffineTransform : public Transform {
        public:
            AffineTransform() throw();
            AffineTransform(
                const double& a,
                const double& b,
                const double& c,
                const double& d,
                const double& e,
                const double& f
            ) throw (std::domain_error);
            AffineTransform(
                const double& x0,
                const double& y0,
                const double& scale,
                const double& rotation,
                const bool& xflip = false,
                const bool& yflip = false
            ) throw (std::domain_error);
            virtual focalplane forward(
                const instrcoord& xy
            ) const throw();
            virtual instrcoord back(
                const focalplane& xy
            ) const throw();
            virtual AffineTransform* clone() const {
                return new AffineTransform(*this);
            }

        protected:
            double mCoeffs[6];                ///< forward tranformation matrix
            double mInverse[6];               ///< inverse tranformation matrix
    };
}
#endif

