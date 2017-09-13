/// \file AltAzLimitCalc.cpp
/// \brief Implementation of the generic Alt/Az limit calculator class.

// D L Terrett
// Copyright STFC. All rights reserved.

#include <cmath>
#include <utility>

#include "AltAzLimitCalc.h"
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
    std::pair<int,double> AltAzLimitCalc::limitTime(
        double t0,                      ///< start time (TAI, MJD)
        double az,                      ///< initial azimuth (degrees)
        double alt                      ///< initial altitude (degress)
    ) {
    
    // Store initial position
        mAz = az;
        mAlt = alt;
        
    // Call base class method.
        double t = limitTimeCalc(t0);
        return std::make_pair(mReason, t);
    }

/// Start search loop
    void AltAzLimitCalc::startLoop(
        const Site& site,               ///< site
        const TimeKeeper& timeKeeper    ///< time keeper
    ) {
    
    // Copy Mount
        mMountCopy.reset(new MountVt(timeKeeper, site, mMount));       
    }
    
/// End search loop
    void AltAzLimitCalc::endLoop() {
    
    // Delete the mount copy
        mMountCopy.reset();
    }

/// Get in limit status
/**
    This method determines whether or not the the axes have 
    encountered a limit for a given position and returns a code
    that indicates which limit has been encountered.
    
    \returns limit code.
*/
    int AltAzLimitCalc::inLimit(
        double t                    ///< time (TAI, MJD)
    ) {
    
    // Update mount
        mMountCopy->update();
        mMountCopy->updatePM();
        mMountCopy->track(2);
        
    // Store updated mechanical positions. For the azimuth we need to
    // handle the cable wrap.
    
    // Convert roll demand to azimuth in degrees.
        double az[2];
        az[0] = 180.0 - mMountCopy->roll().sample(t)*TcsLib::r2d;
        az[1] = - mMountCopy->roll().sample(t,1)*TcsLib::r2d;
        
    // Pick nearest wrap to the current position.
        double d = az[0] - std::fmod( mAz, 360.0 );
        if ( d > 180.0 ) {
            d -= 360.0;
        } else if ( d < -180.0 ) {
            d += 360.0;
        }
        az[0] = mAz + d;
        mAz = Trajectory(t, t, az, 2);
        
    // Convert elevation to degrees.
        mAlt = Trajectory(mMountCopy->pitch(),0.0,TcsLib::r2d);
        
    // Test for outside limits.
        if ( mAz < mAzLowLim ) return azimuthLowLimit;
        if ( mAz > mAzHighLim ) return azimuthHighLimit;
        if ( mAlt < mAltLowLim ) return horizonLimit;
        if ( mAlt > mAltHighLim ) return zenithLimit;
        return noLimit;
    }
    
/// Get close to limit status
/**
    This method determines whether or not the the axes are 
    close to a limit by extrapolating the most recently
    calculated position by the specified time interval.
    
    \returns limit code. 0 means not in limit.
    */
    int AltAzLimitCalc::closeToLimit(
        double t                    ///< time (TAI, MJD)
    ) {
    
    // Get position at time t.
        double az = mAz.sample(t);                
        double el = mAlt.sample(t);
        
    // Test for outside limits.
        if ( az < mAzLowLim ) return azimuthLowLimit;
        if ( az > mAzHighLim ) return azimuthHighLimit;
        if ( el < mAltLowLim ) return horizonLimit;
        if ( el > mAltHighLim ) return zenithLimit;
        return noLimit;
    }
}

