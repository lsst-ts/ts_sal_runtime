/// \file RotaryAxis.h
/// \brief Definition of the Rotary Axis class

// D L Terrett
// Copyright STFC. All rights reserved.

#ifndef tpkROTARYAXIS_H
#define tpkROTARYAXIS_H

#include "Trajectory.h"

namespace tpk {
    class WrapControl;

/// Rotary axis
/**
    A Rotary Axis object converts a position demand in radians to a position
    of a rotary axis in "user" units (such as degrees) with logic for choosing 
    the correct overlap region and remaining within specified motion limits.
*/
    class RotaryAxis {
        public:
            
        /// Wrap logic options
            enum wraplogic {
                lowRange,           ///< Go to low overlap region
                highRange,          ///< Go to high overlap region
                nearestRange,       ///< Go to nearest accessible position
                limit               ///< Stay in limit
            };
            
        /// Reference position for wrap calculation        
            enum wrapref {
                lastDemand,         ///< Go to position closest to previous demand
                currentPosition     ///< Go to position closest to current position
            };  
            
        /// Position type
            enum postype {
                demand,             ///< Demanded position
                achieved            ///< achieved position
            };
            
        /// Units
            enum units {
                radians,            ///< radians
                axis                ///< axis units
            };
            
            RotaryAxis(
                double zeropoint,
                double scale,
                double lowlim,
                double highlim,
                double position = 0.0
            );
            Trajectory track(
                double t,
                const Trajectory& demandPos,
                WrapControl& wrapcontrol
            );
            Trajectory track(
                double t,
                const Trajectory& demandPos
            );
            bool position(
                double t,
                const Trajectory& pos,
                double posTol = 0.0,
                double velTol = 0.0
            );
            Trajectory getPosition(
                double t,
                postype type,
                units u
            ) const;
            
        /// Get in limit status
        /**
            \returns in limit status
        */
            bool isInLimit() {
                return mInLimit;
            }
        protected:
            double mZeroPoint;          ///< zero radians on axis
            double mScale;              ///< radians to user units scale factor
            double mLowLimit;           ///< low limit (user units)
            double mHighLimit;          ///< high limit (user units)
            bool mInLimit;              ///< in limit flag
            Trajectory mLastDemand;     ///< most recent demanded position
            Trajectory mPosition;       ///< axis position
    };
}
#endif

