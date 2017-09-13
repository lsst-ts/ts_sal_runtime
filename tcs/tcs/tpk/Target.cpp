/// \file Target.cpp
/// \brief Implementation of the target class

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "Target.h"

#include "Coordinates.h"
#include "RefSys.h"

namespace tpk {

/// Get position
/**
    The target position at the specified time is converted to the specified
    coordinate frame.

    \returns target position at time t
*/
    vector Target::position(
        const double& t,           ///< TAI (MJD)
        const RefSys& frame        ///< coordinate frame
    ) const {

    // Get position in tracking frame.
        vector pos = position(t);

    // If the requested frame is not the same as the tracking frame, create
    // a target object of the type of the tracking frame and get its position
    // in the requested frame.
        if ( *mTrackFrame != frame ) {
            Target* target = mTrackFrame->target( mSite, pos);
            pos = target->position(t, frame);
        }
        return pos;
    }
}

