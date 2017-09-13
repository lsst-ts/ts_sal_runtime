/// \file AffineTransform.cpp
/// \brief Implementation of the AffineTransform class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "AffineTransform.h"

#include <cmath>
#include <stdexcept>

#include "slalib.h"

namespace tpk {

/// Default constructor
/**
    The transformation is initialised to the identity transformation.
*/
    AffineTransform::AffineTransform() throw()
    {
        mCoeffs[0] = 0.0;
        mCoeffs[1] = 1.0;
        mCoeffs[2] = 0.0;
        mCoeffs[3] = 0.0;
        mCoeffs[4] = 0.0;
        mCoeffs[5] = 1.0;
        for ( int i = 0; i < 6; i++ ) mInverse[i] = mCoeffs[i];
    }

/// Constructor for an arbitrary transformation
/**
    The tranformation is:

                    x2 = a + b * x1 + c * y1

                    y2 = d + e * x1 + f * y1

    \exception std::domain_error Transformation has no inverse.
*/
    AffineTransform::AffineTransform(
        const double& a,  ///< coefficient a
        const double& b,  ///< coefficient b
        const double& c,  ///< coefficient c
        const double& d,  ///< coefficient d
        const double& e,  ///< coefficient e
        const double& f   ///< coefficient f
    ) throw(std::domain_error) {
        mCoeffs[0] = a;
        mCoeffs[1] = b;
        mCoeffs[2] = c;
        mCoeffs[3] = d;
        mCoeffs[4] = e;
        mCoeffs[5] = f;
        int j;
        slaInvf( mCoeffs, mInverse, &j);
        if ( j ) throw std::domain_error("transformation has no inverse");
    }

/// Constructor for scale, shift and rotation with optional axis flip
/**
    The transformations are applied in the order: axis flip, scale, rotate,
    shift origin.
*/
    AffineTransform::AffineTransform(
        const double& x0,        ///< origin shift in first coordinate
        const double& y0,        ///< origin shift in second coordinate
        const double& scale,     ///< scale factor
        const double& rotation,  ///< rotation (radians)
        const bool& xflip,       ///< flip x axis
        const bool& yflip        ///< flip y axis
    ) throw (std::domain_error) {
        mCoeffs[0] = x0;
        mCoeffs[1] = scale * std::cos(rotation);
        mCoeffs[2] = scale * std::sin(rotation);
        mCoeffs[3] = y0;
        mCoeffs[4] = - mCoeffs[2];
        mCoeffs[5] = mCoeffs[1];
        if ( xflip ) {
            mCoeffs[1] *= -1.0;
            mCoeffs[4] *= -1.0;
        }
        if ( yflip ) {
            mCoeffs[2] *= -1.0;
            mCoeffs[5] *= -1.0;
        }
        int j;
        slaInvf( mCoeffs, mInverse, &j);
        if ( j ) throw std::domain_error("transformation has no inverse");
    }

/// Forwards transformation
/**
   Transforms instrument or guider coordinates into focal plane
   coordinates.

   \returns position in focal plane
*/
focalplane AffineTransform::forward(
        const instrcoord& xy  ///< instrument coordinates
    ) const throw() {
        double x2 = mCoeffs[0] + mCoeffs[1] * xy.x + mCoeffs[2] * xy.y;
        double y2 = mCoeffs[3] + mCoeffs[4] * xy.x + mCoeffs[5] * xy.y;
        return focalplane(x2,y2);
    }

/// Backwards transformation
/**
   Transforms focal plane coordinates into instrument or guider
   coordinates.

   \returns position in instrument or guider coordinates
*/
    instrcoord AffineTransform::back(
        const focalplane& xy  ///< focal plane coordinates
    ) const throw() {
        double x1 = mInverse[0] + mInverse[1] * xy.x + mInverse[2] * xy.y;
        double y1 = mInverse[3] + mInverse[4] * xy.x + mInverse[5] * xy.y;
        return instrcoord(x1,y1);
    }
}

