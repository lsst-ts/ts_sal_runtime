/// \file LimitCalc.cpp
/// \brief Implementation of the limit calculator class.

// D L Terrett
// Copyright STFC. All rights reserved.

#include <cstdlib>

#include "LimitCalc.h"
#include "MountVt.h"
#include "Site.h"
#include "TimeKeeper.h"

namespace tpk {

    /// Get time at which mechanical limit is reached.
    /**
        If no limit is reached in the maximum tracking time then a
        time of zero is returned.
        
        If the current demands would put the telescope into a limit
        immediately then the start time is returned.
        
        \returns absolute time (MJD, TAI)
    */
    double LimitCalc::limitTimeCalc(
        double t0               ///< start time (TAI, MJD)
    ) {
        
     // Create a clock that allows us to set the time.
        FakeClock clock(t0);
        
     // Make a copy of the mount and site and a new timekeeper that we can 
     // use to "fast-forward" in time.
        Site site(mSite);
        TimeKeeper timeKeeper(clock, site);
        
    // Call derived class initialisation method.
        startLoop(site, timeKeeper);
        
     // Check for the current demand putting us in a limit.
        mReason = inLimit(t0);
        if ( mReason != noLimit ) return t0;
        
    // Fast-forward time.
        bool hunting = false;       
        double step = mDefStep;
        double tresume = 0.0;
        for (;;) {
               
        // Move the clock to the next time step.
            clock.mT += step;
            
        // If we are in the normal fast forward mode (i.e. the step size is
        // the default) update the site with the new time.
            if ( step >= mDefStep ) site.refresh(clock.mT);
             
        // Update the time keeper.
            timeKeeper.update();
            
        // If we have gone past a limit we need to back out to find where the
        // limit is by halving the step size.
            int reason = inLimit(clock.mT);
            if ( reason != noLimit ) {
                mReason = reason;
                hunting = true;         
                 
            // We are beyond the limit so back out by half the previous step.
                if ( step > 0.0 ) step = -step;
                step *= 0.5;
                
            // If the step is now less than the minimum step we are within the
            // minimum step of the limit so we are done.
                if ( std::abs(step) < mMinStep ) break;
            } else {
            
            // We are not in a limit but we are hunting which means that there
            // is a limit close by. So, move forward half of the previous step.
                if ( hunting ) {
                    if ( step < 0.0 ) step = -step;
                    step *= 0.5;
                    
            // If the step is now less than the minimum step we are within the
            // minimum step of the limit so we are done.
                    if ( std::abs(step) < mMinStep ) break;
                } else {
                
                // We've not run into a limit yet but it is possible that we 
                // have just stepped past a region where the track runs into 
                // a limit and then backs out. We test for the possibility of 
                // this condition by extrapolating back to the previous step 
                // using the current velocity.                     
                           
                // The extrapolated point is beyond a limit so we must back 
                // up to the previous point and move forward with a smaller 
                // step size in order to check.
                   if ( closeToLimit(clock.mT - step) != noLimit ) {
                   
                   // Record the time at which searching started.
                        if ( tresume <= 0.0 ) tresume = clock.mT;
                    
                    // Set the time back to the previous step.
                        clock.mT -= step;
                    
                    // Halve the step size and make sure it is a forward step.
                        step = std::abs(step) * 0.5; 
                        
                    // If the step size is now less than the minimum, reset
                    // everything so that we resume normal fast forwarding.
                        if ( step < mMinStep ) {
                            step = mDefStep;
                            clock.mT = tresume;
                            tresume = 0.0;
                        }                 
                    }
                  
                // If the time is now past the resume point then give up
                // search in and resume normal fast forward.
                    if ( tresume > 0.0 && clock.mT >= tresume ) {
                        step = mDefStep;
                        tresume = 0.0;
                    }                
                }
            }
            
        // If the step size is the default and we've reached the maximum 
        // track length, give up.
            if ( step >= mDefStep && clock.mT > t0 + mMaxTrack ) {
                clock.mT = 0.0;
                break;
            }
        }
        
    // Call derived class cleanup method.
        endLoop();
        
    // Return time at which the loop terminated.
        return clock.mT;
    }
}

