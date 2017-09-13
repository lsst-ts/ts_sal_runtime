/// \file TrackingTarget.cpp
/// \brief Implementation of the tracking target class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "TrackingTarget.h"

#include "slalib.h"

namespace tpk {

/// Get target position in the tracking frame.
/**
    This method is called by the kernel "fast" routines an must therefore be
    efficient. The base class implementation assumes that the position and
    rates in the tracking frame have been stored in the data members Position
    T0 and Velocity by the object constructor and are kept up-to-date by the
    update method (if required).

    \returns the target position in the tracking frame at the specified time.
*/
    vector TrackingTarget::position(
        const double& t            ///< TAI (MJD)
    ) const {
        mMutex.lock();
        vector p = mPosition;
        deltav v = mVelocity;
        double t0 = mT0;
        mMutex.unlock();
        return p + v * (t - t0);
    }

/// Update position in the tracking frame
/**
    Recomputes the tracking frame position and rates by
    computing the positions 10 seconds apart.
*/
    void TrackingTarget::update(
            const double& t1               ///< TAI (MJD)
    ) {

    // Position in tracking frame "now".
        vector p1 = position(t1, *mTrackFrame);

    // Position in tracking frame in 10 sec time.
        double dt = 10.0/86400.0;
        vector p2 = position(t1 + dt, *mTrackFrame);

    // Rates
        deltav v = (p2 - p1) / dt;

    // Store.
        mMutex.lock();
        mPosition = p1;
        mT0 = t1;
        mVelocity = v;
        mMutex.unlock();
    }
}

