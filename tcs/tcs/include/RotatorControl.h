/// \file RotatorControl.h
/// \brief Definition of the simulated rotator control system

// D L Terrett
// Copyright STFC. All rights reserved.

#ifndef dpkROTATORCONTROL_H
#define dpkROTATORCONTROL_H

#include <string>
#include "tpk.h"
#include "Pcs.h"
#include "Axis.h"

namespace dpk {

/// A rotator control object simulates the axis of an instrument or image rotator.

    class RotatorControl {
        public:
            RotatorControl(
                Pcs& pcs,
                const std::string& name
            );           
            virtual ~RotatorControl() {
                delete mLinAxis;
                delete mRotAxis;
            }
            virtual void track(
                double tai,
                const tpk::Trajectory& rma
            );
            
        /// Rotator mechanical angle
        /**
            \returns mechanical angle trajectory
        */
            virtual tpk::Trajectory getRma(
                double t                ///< time (MJD, TAI)
            ) {
                return mRotAxis->getPosition(t, tpk::RotaryAxis::achieved, 
                        tpk::RotaryAxis::radians);
            }
                        
        ///  axis in position status
        /**
            \returns in position status
        */
            virtual bool inPos() {
                return mInPos;
            }
            
        /// Axis position
        /**
            \returns axis position (degrees)
        */
            virtual double getAxis(
                double t,                       ///< time (MJD, TAI)
                tpk::RotaryAxis::postype pos    ///< position type
            ) {
                return mRotAxis->getPosition(t, pos, tpk::RotaryAxis::axis);
            }
            
       protected:
       
       /// Convert rotator axis trajectory to encoder trajectory.
       /**
            The default implementation converts from degrees to arcsec.
       */
            virtual tpk::Trajectory axis2enc(
                const tpk::Trajectory axis  ///< axis position
            ) {
                return tpk::Trajectory(axis, 0.0, 3600.0);
            }
                        
       /// Convert encoder trajectory to axis trajectory.
       /**
            The default implementation converts from arcsec to degrees.
       */
            virtual tpk::Trajectory enc2axis(
                const tpk::Trajectory enc
            ) {
                return tpk::Trajectory(enc, 0.0, 1.0 / 3600.0);
            }
            
            tpk::Trajectory mRma;       ///< achieved rotator trajectory
            tpk::RotaryAxis* mRotAxis;  ///< rotary axis
            dpk::Axis* mLinAxis;        ///< rotator axis
            tpk::WrapControl mWrap;     ///< wrap controller
            bool mInPos;                ///< in position flag
            
        public:
            static double ROT_LOLIM;  ///< Rotator low limit
            static double ROT_HILIM;  ///< Rotator high limit
            static double ROT_INIT;   ///< Rotator initial position
            static double ROT_DVMAX;  ///< Rotator maximum velocity
            static double ROT_DAMAX;  ///< Rotator max acceleration
            static double ROT_DJMAX;  ///< Rotator max jerk
            static double ROT_GS;     ///< Rotator square root gain
            static double ROT_GP;     ///< Rotator proportional gain
            static double ROT_GI;     ///< Rotator integral gain
            static double ROT_PI;     ///< Rotator integrator window
            static double ROT_GD;     ///< Rotator derivative gain
            static double ROT_PNEAR;  ///< Rotator "near enough"
    };
}
#endif
