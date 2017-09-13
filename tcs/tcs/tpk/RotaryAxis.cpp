/// \file RotaryAxis.h
/// \brief Implementation of the Rotary Axis class

// D L Terrett
// Copyright STFC. All rights reserved.

#include "RotaryAxis.h"

#include <cstdlib>

#include "TcsLib.h"
#include "Trajectory.h"
#include "WrapControl.h"

namespace tpk {

/// Constructor for an axis with limits
    RotaryAxis::RotaryAxis(
        double zeropoint,   ///< position of axis corresponding to zero radians
        double scale,       ///< scale factor converting radians to axis units
        double lowlim,      ///< low limit (axis units)
        double highlim,     ///< high limit (axis units)
        double position     ///< initial position (axis units)
    ) : mZeroPoint(zeropoint), mScale(scale), mLowLimit(lowlim), 
        mHighLimit(highlim), mInLimit(false), mLastDemand(position),
        mPosition(mLastDemand) {}

 /// Get new axis position
 /**
    \returns Axis position for new demand orientation (axis units)
 */
    Trajectory RotaryAxis::track(
        double t,                    ///< time (MJD, TAI)
        const Trajectory& demandPos, ///< demand position (radians)
        WrapControl& wrapcontrol     ///< Wrap control
    ) {
    
    // Get wrap logic and reference position.
        wraplogic wrap(wrapcontrol.getLogic());
        wrapref ref(wrapcontrol.getReference());
    
    // New demand in axis units.
        Trajectory newDemand(demandPos, mZeroPoint/mScale, mScale);

    // Position at time t
        double pnew(newDemand.sample(t));
        
    // One revolution in axis units
        double rev(TcsLib::pi2 * std::abs(mScale));
        
    // Initially not in a limit and no adjustment.
        mInLimit = false;
        double wrapAdjust(0.0);
/*       
    // Low range requested...
        if ( wrap == lowRange ) {
        
        // Add one rev if below the low limit
            if ( pnew < mLowLimit ) wrapAdjust = rev;
        
        // Subtract one rev if it still leaves it clear of the low limit.
            else if (pnew - rev > mLowLimit) wrapAdjust = -rev;
            
    // Similarly for high range.   
        } else if ( wrap == highRange ) {
            if (pnew > mHighLimit) wrapAdjust = -rev;
            else if (pnew + rev < mHighLimit) wrapAdjust = rev;
        } else {
        
        // Select current position for wrap calculation.
            double pold;
            if ( ref == lastDemand ) {
                pold = mLastDemand.sample(t);
            } else {
                pold = mPosition.sample(t);
            }
            
        // Distance axis should move
            double delta = pnew - pold;
            if ( delta < - rev/2.0 ) {
                wrapAdjust = rev;
            } else if ( delta > rev/2.0 ) {
                wrapAdjust = -rev;
            }
            
        // If nearestRange is specified add or subtract a rev to get clear
        // of the limits.
            if ( wrap == nearestRange ) {
                if ( pnew + wrapAdjust < mLowLimit )
                    wrapAdjust += rev;
                else if ( pnew + wrapAdjust > mHighLimit )
                    wrapAdjust -= rev;
            }
        }     
 */        
       
    // Save current demand adjusted for wrap for next time
        mLastDemand = Trajectory(newDemand, -wrapAdjust, 1.0);
        
    // Return new position
        return mLastDemand;
    }
    
 /// Get new axis position
 /**
    The wrap control settings default to nearest range and last demand
    which are suitable for axes with no overlap region.
    
    \returns Axis position for new demand orientation (axis units)
 */
    Trajectory RotaryAxis::track(
        double t,                    ///< time (MJD, TAI)
        const Trajectory& demandPos  ///< demand position (radians)
    ) {
        WrapControl wc(nearestRange, lastDemand);
        return track(t, demandPos, wc);
    }
    
/// Set actual position of axis.
/**
    \returns in position status
*/
    bool RotaryAxis::position(
        double t,               ///< time (MJD, TAI)
        const Trajectory& pos,  ///< position trajectory (axis units)
        double posTol,          ///< position tolerance (axis units)
        double velTol           ///< velocity tolerance (axis units/day)
    ) {
    
    // Store updated position
        mPosition = pos;
        
    // Compare position and demand
        bool inPos = true;
        if ( posTol > 0.0 ) {
            if ( std::abs( mPosition.sample(t) - mLastDemand.sample(t) ) >
                    posTol ) {
                inPos = false;
            } else if ( std::abs( mPosition.sample(t,1) - 
                    mLastDemand.sample(t,1) > velTol )) {
                    inPos = false;
            }
        }
        return inPos;
    }
    
    
    Trajectory RotaryAxis::getPosition(
        double t,               ///< time (MJD, TAI)
        postype type,           ///< position type (demand or achieved)
        units  uni              ///< units (radians or axis)
    ) const {

        Trajectory pos( type == demand ? mLastDemand : mPosition );       
               
        if ( uni == radians ) { 
        
        // Convert to radians.
            pos = Trajectory(pos, -mZeroPoint, 1.0/mScale);                
            
        // Wrap into range 0-pi.
            double p(pos.sample(t));
            double wrapAdjust(0.0);
            if ( p > TcsLib::pi2 ) wrapAdjust = -1.0;
            else if ( p < - TcsLib::pi2 ) wrapAdjust = 1.0;
            
        // Return adjusted trajectory
            return Trajectory(pos, -wrapAdjust, 1.0);
        } else {
            return pos;
        } 
    }
}
