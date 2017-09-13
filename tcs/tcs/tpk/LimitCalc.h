/// \file LimitCalc.h
/// \brief Definition of the limit calculator class.

// D L Terrett
// Copyright STFC. All rights reserved.

#ifndef tpkLIMITCALC_H
#define tpkLIMITCALC_H


#include "Clock.h"
#include "TcsLib.h"

namespace tpk {
    class MountVt;
    class Site;
    class TimeKeeper;

/// Time to limit calculator class
/**
    A LimitCalc object calculates the absolute time that the telescope mount
    or image rotator will reach one of its limits of travel given an initial
    roll, pitch and rotator mechanical angle. Full account is taken of 
    non-sidereal motions of the target that is being tracked.
    
    The method used is to take a copy of the mount virtual telescope and
    "fast-forward" time until one of the limits is reached. However, choosing
    a suitable time interval is not straight-forward. Too small an interval
    results in execessive computation whereas too large an interval risks 
    missing cases where an axis runs into a limit but then reverses direction
    and comes out of the limit again. (both a rotator and and pitch axis with
    a high limit less than 90 degress exhibit this behaviour).
    
    The strategy adopted here is to start with a fairly large interval (by
    by default around 10 minutes) and at each sample time test both the
    position at that time and the position extrapolated to the next sample
    time. If the extrapolated sample is beyond a limit, the sample interval
    is reduced so that the next sample cannot lie beyond the "turning point".
    
    It is still possible to miss a limit if the axis remains in the limit for
    less than the mimum sample interval (by default 1 second) but, in any case,
    the reliability of these calculations is limited by unpredictable effects
    such as changes in atmospheric conditions, guiding inputs and auxiliary
    inputs to the pointing model. Also, where the target tracks very close to
    the pole of the mount it is possible for the results to be completely
    wrong because it is impossible to predict which side of the pole the
    telescope will track.
    
    Calculating the mechanical position of an axis given a current position
    and a demand (taking into account cable wraps and the like) and
    determining whether a mechanical position is reachable or not are
    delegated to protected virtual methods.
*/
    class LimitCalc {
        public:       
            LimitCalc(
                const Site& site            ///< Telescope site
            ) : mSite(site),
                mDefStep(600.0 / 86400.0),  // 10 minutes
                mMinStep(0.5 /86400.0),     // half a second
                mMaxTrack(0.5)              // 12 hours
            {}
            virtual ~LimitCalc() {}                                    
        protected:
            double limitTimeCalc(
                double t0
            );        
        
        /// Start loop
        /**
            Performs any initialisation required before the search
            loop starts.
            
            The default implementation does nothing.
        */
            virtual void startLoop(
                const Site& site,                 ///< site
                const TimeKeeper& timeKeeper      ///< time keeper
            ) {}
        
        /// End loop
        /**
            Performs any cleanup needed after the search loop 
            completes.
            
            The default implementation does nothing.
        */
            virtual void endLoop() {}
        
        /// Get in limit status
        /**
            This method determines whether or not the the axes have 
            encountered a limit at the specified time.
            
            \returns limit flags
         */
            virtual int inLimit(
                double t                    ///< time (TAI, MJD)
           ) = 0;
            
        /// Get in limit status
        /**
            This method determines whether or not the the axes might
            have encountered a limit at the specified offset from the
            time of the last call to inLimit. This method is normally
            implemented by extrapolating the from the position last
            calculated by inLimit() using the velocity at that time.
            
            \returns limit flags
         */
            virtual int closeToLimit(
                double t                   ///< time (TAI, MJD)
            ) = 0;
            
        protected:
            const Site& mSite;              ///< telescope site
            int mReason;                    ///< limit reason
        public:
            double mDefStep;                ///< default step size (days)
            double mMinStep;                ///< minimum step size (days)
            double mMaxTrack;               ///< maximum tracking time (days)
            static const int noLimit = 0;   ///< limit reason - no limit
        private:
            LimitCalc();
            
        // A special clock class that always returns the time that the
        // public data member mT was set to.
            class FakeClock : public Clock {
                public:
                    FakeClock(double t0) : mT(t0) {}
                    double read() throw() {
                        return mT;
                    }
                    double mT;
            };
    };
}
#endif

