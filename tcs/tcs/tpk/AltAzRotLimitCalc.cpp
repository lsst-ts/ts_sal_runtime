/// \file AltAzLimitCalc.cpp
/// \brief Implementation of the generic Alt/Az and rotator limit calculator
/// class.

// D L Terrett
// Copyright STFC. All rights reserved.

#include <cmath>
#include <utility>

#include "AltAzRotLimitCalc.h"
#include "MountVt.h"
#include "TcsLib.h"

namespace tpk {

/// Get time at which mechanical limit is reached.
/**
    If no limit is reached in the maximum tracking time then a
    time of zero is returned.
    
    If the current demands would put the telescope into a limit
    immediately then the start time is returned.
    
    \returns limit code and absolute time (MJD, TAI)
*/
    std::pair<int,double> AltAzRotLimitCalc::limitTime(
        double t0,              ///< start time (TAI, MJD)
        double az,              ///< initial azimuth (degree)
        double alt,             ///< initial altitude (degrees)
        double rma              ///< initial rotator mechanical angle (degrees)
    ) {
    
    // Store initial position
        mRma = rma;
        
    // Call base class method.
        return AltAzLimitCalc::limitTime(t0, az, alt);
    }
   
/// Get in limit status
/**
    This method determines whether or not the the axes have 
    encountered a limit for a given position and returns a code
    that indicates which limit has been encountered.
    
    \returns limit code..
*/
    int AltAzRotLimitCalc::inLimit(
        double t                  ///< time (TAI, MJD)
    ) {
    
    // Test for mount limits
        int reason = AltAzLimitCalc::inLimit(t);
        
    // If the mount is not in a limit check the rotator.
        if ( reason == noLimit) {
            
        // Convert rma demand to degrees.
            double rma[2];
            rma[0] = mMountCopy->rma().sample(t)/TcsLib::d2r;
            rma[1] = mMountCopy->rma().sample(t,1)/TcsLib::d2r;
            
        // Pick nearest wrap to the current position.
            double d = rma[0] - std::fmod( mRma, 360.0 );
            if ( d > 180.0 ) {
                d -= 360.0;
            } else if ( d < -180.0 ) {
                d += 360.0;
            }
            rma[0] = mRma + d;
            mRma = Trajectory(t, t, rma, 2);
            
        // Test for outside limits.
            if ( mRma < mRotLowLim ) return rotatorLowLimit;
            if ( mRma > mRotHighLim ) return rotatorHighLimit;
            return noLimit;
        } else {
            return reason;
        }
    }
    
/// Get close to limit status
/**
    This method determines whether or not the the axes are 
    close to a limit by extrapolating the most recently
    calculated position by the specified time interval.
    
    \returns limit code. 0 means not in limit.
    */
    int AltAzRotLimitCalc::closeToLimit(
        double t                    ///< time (TAI, MJD)
    ) {
    
    // Check mount
        int reason = AltAzLimitCalc::closeToLimit(t);
        if (reason == noLimit) {
    
        // Get position at time t.
            double rma = mRma.sample(t);
            
        // Test for outside limits.
            if ( rma < mRotLowLim ) return rotatorLowLimit;
            if ( rma > mRotHighLim ) return rotatorHighLimit;
            return noLimit;
        } else {
            return reason;
        }
    }
}
