/// \file PiFilter2D.cpp
/// \brief Implementation of the PiFilter2D class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "Coordinates.h"
#include "PiFilter2D.h"

namespace tpk {

/// Insert value into filter
    xycoord PiFilter2D::operator<<( const xycoord& input ) {
        mMutex.lock();

    // Difference between current value and the input
        xycoord diff = input - mValue;

    // If the difference is outside the window, set the integrator to zero.
        if ( diff.len2() > mWindow2 ) {
            mIntegrator = xycoord(0.0,0.0);
        } else {

    // Add the difference to the integrator
            mIntegrator = mIntegrator + diff;

    // Limit the integrator at the saturation value.
            if ( mIntegrator.len() > mSaturate ) {
                mIntegrator = mIntegrator * ( mSaturate / mIntegrator.len() );
            }
        }

    // Multiply difference and integrator by the gains to get the filter value.
        mValue = mValue + diff * mPgain + mIntegrator * mIgain;
        xycoord v = mValue;
        mMutex.unlock();

        return v;
    }
}

