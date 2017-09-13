/// \file MountControl.h
/// \brief Definition of the simulated mount control system

// D L Terrett
// Copyright STFC. All rights reserved.

#ifndef dpkMOUNTCONTROL_H
#define dpkMOUNTCONTROL_H

#include <string>
#include "tpk.h"
#include "Pcs.h"
#include "Axis.h"

namespace dpk {

/// A mount control object simulates the two axes of a telescope mount.

    class MountControl {
        public:
            virtual ~MountControl() {
                delete mRollLinAxis;
                delete mPitchLinAxis;
                delete mRollRotAxis;
                delete mPitchRotAxis;
            }
    
            virtual void track(
                double tai,
                const tpk::Trajectory& roll,
                const tpk::Trajectory& pitch
            );
            
        /// Roll axis position
        /**
            \returns roll axis position trajectory
        */
            virtual tpk::Trajectory getRoll(
                double t                ///< time (MJD, TAI)
            ) {
                return mRollRotAxis->getPosition(t, tpk::RotaryAxis::achieved, 
                        tpk::RotaryAxis::radians);
            }
            
        /// Pitch axis position
        /**
            \returns pitch axis position trajectory
        */
            virtual tpk::Trajectory getPitch(
                double t                ///< time (MJD, TAI)
            ) {
                return mPitchRotAxis->getPosition(t, tpk::RotaryAxis::achieved, 
                        tpk::RotaryAxis::radians);
            }

        /// Roll axis in position status
        /**
            \returns in position status
        */
            virtual bool rollInPos() {
                return mRollInPos;
            }
            
        /// Pitch axis in position status
        /**
            \returns in position status
        */
            virtual bool pitchInPos() {
                return mPitchInPos;
            }
            
       protected:
       
       /// Convert roll axis trajectory to an encoder trajectory.
       /**
            The default implementation converts from degrees to arcsec.
       */
            virtual tpk::Trajectory rollAxis2enc(
                const tpk::Trajectory roll      ///< roll axis trajectory
            ) {
                return tpk::Trajectory(roll, 0.0, 1.0 * 3600.0);
            }
            
       /// Convert pitch trajectory to axis trajectory.
       /**
            The default implementation converts from degrees to arcsec.
       */
            virtual tpk::Trajectory pitchAxis2enc(
                const tpk::Trajectory pitch     ///< pitch axis trajectory
            ) {
                return tpk::Trajectory(pitch, 0.0, 1.0 * 3600.0);
            }
            
       /// Convert encoder trajectory to roll axis trajectory.
       /**
            The default implementation converts from arcsec to degrees.
       */
            virtual tpk::Trajectory enc2rollAxis(
                const tpk::Trajectory enc       ///< encoder trajectory
            ) {
                return tpk::Trajectory(enc, 0.0, 1.0 / 3600.0);
            }
            
       /// Convert encoder trajectory to pitch axis trajectory.
       /**
            The default implementation converts from arcsec to degrees.
       */
            virtual tpk::Trajectory enc2pitchAxis(
                const tpk::Trajectory enc       ///< encoder trajectory
            ) {
                return tpk::Trajectory(enc, 0.0, 1.0 / 3600.0);
            }            
            
            MountControl() {}
       
            tpk::Trajectory mRoll;          ///< achieved roll trajectory
            tpk::Trajectory mPitch;         ///< achieved pitch trajectory
            dpk::Axis* mRollLinAxis;        ///< roll axis
            dpk::Axis* mPitchLinAxis;       ///< pitch axis
            tpk::RotaryAxis* mRollRotAxis;  ///< azimuth wrap controller
            tpk::RotaryAxis* mPitchRotAxis; ///< elevation wrap controller
            tpk::WrapControl mRollWrap;     ///< azimuth wrap controller
            bool mRollInPos;                ///< roll in position status
            bool mPitchInPos;               ///< pitch in position status
   };
   
/// Az El Mount controller
   class AltAzMountControl : public MountControl {
       public:
            AltAzMountControl(
                Pcs& pcs,
                const std::string& roll,
                const std::string& pitch
            );
            
        /// Azimuth axis position
        /**
            \returns azimuth axis position (degrees)
        */
            virtual double getAzimuth(
                double t,                       ///< time (MJD, TAI)
                tpk::RotaryAxis::postype pos    ///< position type
            ) {
                return mRollRotAxis->getPosition(t, pos, 
                        tpk::RotaryAxis::axis);
            }
            
        /// Altitude axis position
        /**
            \returns altitude axis position (degrees)
        */
            virtual double getAltitude(
                double t,                       ///< time (MJD, TAI)
                tpk::RotaryAxis::postype pos    ///< position type
            ) {
                return mPitchRotAxis->getPosition(t, pos, 
                        tpk::RotaryAxis::axis);
            }
            
            static double AZ_LOLIM;   ///< Azimuth low limit
            static double AZ_HILIM;   ///< Azimuth high limit
            static double AZ_INIT;    ///< Azimuth initial position
            static double AZ_DVMAX;   ///< Azimuth maximum velocity
            static double AZ_DAMAX;   ///< Azimuth max acceleration
            static double AZ_DJMAX;   ///< Azimuth max jerk
            static double AZ_GS;      ///< Azimuth square root gain
            static double AZ_GP;      ///< Azimuth proportional gain
            static double AZ_GI;      ///< Azimuth integrator gain
            static double AZ_PI;      ///< Azimuth integrator window
            static double AZ_GD;      ///< Azimuth derivative gain
            static double AZ_PNEAR;   ///< Azimuth "near enougth"
            static double ALT_LOLIM;  ///< Altitude low limit
            static double ALT_HILIM;  ///< Altitude high limit
            static double ALT_INIT;   ///< Altitude initial value
            static double ALT_DVMAX;  ///< Altitude maximum velocity
            static double ALT_DAMAX;  ///< Altitude max acceleration
            static double ALT_DJMAX;  ///< Altitude max jerk
            static double ALT_GS;     ///< Altitude square root gain
            static double ALT_GP;     ///< Altitude proportional gain
            static double ALT_GI;     ///< Altitude integrator gain
            static double ALT_PI;     ///< Altitude integrator window
            static double ALT_GD;     ///< Altitude derivative gain
            static double ALT_PNEAR;  ///< Altitude "near enough" 
    };
}
#endif
