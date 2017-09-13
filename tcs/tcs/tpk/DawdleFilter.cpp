/// \file DawdleFilter.cpp
/// \brief Implementation of the Dawdle Filter class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "DawdleFilter.h"

#include <cmath>
#include "slalib.h"

#include "Coordinates.h"

namespace tpk {

/// Limit target and pointing origin movement
/**
    The requested target and pointing origin are modified to limit
    the change in each to the maximum velocity specified by the
    tuning parameter.

    \returns status
    \retval true Filter has modified target or pointing origin.
    \retval false Filter has not modified target or pointing origin.
*/
    bool DawdleFilter::limit(
        const double& t,              ///< TAI (MJD)
        const vector& srcTarget,      ///< requested target position
        const focalplane& srcPo,      ///< requested pointing origin
        vector& destTarget,           ///< limited target position
        focalplane& destPo            ///< limited pointing origin
    ) {
        const double tiny = 1e-10;
        bool active = false;

    // Bypass in effect.
        if ( mBypass ) {
            mTarget = srcTarget;
            mPO = srcPo;

    // Normal operation
        } else {

        // Maximum movement allowed.
            double lmax = fabs(mTunePar * (t - mT));

        // Requested pointing origin change.
            focalplane dp = srcPo - mPO;
            double l = dp.len();

        // Desired move is less than maximum.
            if ( l < tiny || l < lmax ) {
                mPO = srcPo;

        // Apply limit.
            } else {
                active = true;
                mPO = mPO + dp * (lmax / l);
            }

        // Requested target position change in tangent plane.
            deltav dt = srcTarget - mTarget;
            l = dt.len();

        // Desired move is less than maximum.
            if ( l < tiny || l < lmax ) {
                mTarget = srcTarget;

        // Apply limit.
            } else {
                active = true;
                dt = dt * (lmax / l );
                mTarget = mTarget + dt * (lmax / l);
            }
        }

    // Copy new target and pointing origin to outputs.
        destTarget = mTarget;
        destPo = mPO;

    // Store time.
        mT = t;
        return active;
    }

/// Set tuning parameter.
/**
    \returns previous value of tuning parameter
*/
    double DawdleFilter::tune(
        const double& tunepar               ///< tuning parameter
    ) {
        double prev = mTunePar;
        mTunePar = tunepar;
        return prev;
    }

/// Set bypass flag
/**
    \returns previous bypass state
*/
    bool DawdleFilter::bypass(
        const bool& bypass                  ///< bypass flag
    ) {
        bool prev = mBypass;
        mBypass = bypass;
        return prev;
    }
}

