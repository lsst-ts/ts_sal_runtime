/// \file PiFilter.cpp
/// \brief Implementation of the PiFilter class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "PiFilter.h"

namespace tpk {

/// Insert value into filter
    double PiFilter::operator<<( double input ) {
        mMutex.lock();

    // Difference between current value and the input
        double diff = input - mValue;

    // If the difference is outside the window, set the integrator to zero.
        if ( diff * diff > mWindow2 ) {
            mIntegrator = 0.0;
        } else {

    // Add the difference to the integrator
            mIntegrator += diff;

    // Limit the integrator at the saturation value.
            if ( mIntegrator > mSaturate ) {
                mIntegrator = mSaturate;
            } else if ( mIntegrator < -mSaturate ) {
                mIntegrator = -mSaturate;
            }
        }

    // Multiply difference and integrator by the gains to get the filter value.
        mValue += diff * mPgain + mIntegrator * mIgain;
        double v = mValue;
        mMutex.unlock();

        return v;
    }
}

