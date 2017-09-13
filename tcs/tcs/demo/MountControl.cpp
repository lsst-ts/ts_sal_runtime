/// \file MountControl.cpp
/// \brief Implementation of the mount control class

// D L Terrett
// Copyright STFC. All rights reserved.

#include "MountControl.h"
#include "tpk.h"
#include "Axis.h"
#include "Pcs.h"

namespace dpk {

/// Update the mount axis positions 
    void MountControl::track(
            double tai,                     ///< time (TAI, MJD)
            const tpk::Trajectory& roll,    ///< roll demand
            const tpk::Trajectory& pitch    ///< pitch demand
    ) {
    
    // Update the rotary axes.
        tpk::Trajectory r = mRollRotAxis->track(tai, roll, mRollWrap);
        tpk::Trajectory p = mPitchRotAxis->track(tai, pitch);
    
    // Update the axis servos.
        mRollInPos = mRollLinAxis->update(tai, rollAxis2enc(r)) ||
                mPitchRotAxis->isInLimit();
        mPitchInPos = mPitchLinAxis->update(tai, pitchAxis2enc(p))||
                mRollRotAxis->isInLimit();
        
    // Update the achieved axis positions
        mRollRotAxis->position(tai, enc2rollAxis(mRollLinAxis->position()));
        mPitchRotAxis->position(tai, enc2pitchAxis(mPitchLinAxis->position()));
    }
    
    AltAzMountControl::AltAzMountControl(
        Pcs& pcs,                   ///< PCS
        const std::string& roll,    ///< roll axis name
        const std::string& pitch    ///< pitch axis name
    ) {
    
    // Create the rotatary axis objects.
        mRollRotAxis = new tpk::RotaryAxis(-180.0, -tpk::TcsLib::r2d, 
                AZ_LOLIM, AZ_HILIM,AZ_INIT);
        mPitchRotAxis = new tpk::RotaryAxis(0.0, tpk::TcsLib::r2d, 
                ALT_LOLIM, ALT_HILIM, ALT_INIT);
    
    // Create the two axes.
        mRollLinAxis = new Axis( 0.05, 0.05, AZ_GS, AZ_GP, AZ_GI, AZ_PI, AZ_GD,
                AZ_PNEAR, rollAxis2enc(AZ_LOLIM), rollAxis2enc(AZ_HILIM), 
                rollAxis2enc(AZ_DVMAX), rollAxis2enc(AZ_DAMAX), 
                rollAxis2enc(AZ_DJMAX), rollAxis2enc(AZ_INIT));
        mPitchLinAxis = new Axis( 0.05, 0.05, ALT_GS, ALT_GP, ALT_GI, ALT_PI, 
                ALT_GD,ALT_PNEAR, pitchAxis2enc(ALT_LOLIM), 
                pitchAxis2enc(ALT_HILIM), pitchAxis2enc(ALT_DVMAX), 
                pitchAxis2enc(ALT_DAMAX), pitchAxis2enc(ALT_DJMAX),
                pitchAxis2enc(ALT_INIT));
                
    // Register the axes.
        pcs.registerAxis(mRollLinAxis, &mRollWrap, roll);
        pcs.registerAxis(mPitchLinAxis, pitch);
    }
    double AltAzMountControl::AZ_LOLIM = -180.0;
    double AltAzMountControl::AZ_HILIM = 360.0;
    double AltAzMountControl::AZ_INIT = 0.0;
    double AltAzMountControl::AZ_DVMAX = 2.0;
    double AltAzMountControl::AZ_DAMAX = 2.0;
    double AltAzMountControl::AZ_DJMAX = 10.0;
    double AltAzMountControl::AZ_GS = 1.5;
    double AltAzMountControl::AZ_GP = 0.1;
    double AltAzMountControl::AZ_GI = 0.01;
    double AltAzMountControl::AZ_PI = 1.0;
    double AltAzMountControl::AZ_GD = 0.2;
    double AltAzMountControl::AZ_PNEAR = 0.01;
    double AltAzMountControl::ALT_LOLIM = 15.0;
    double AltAzMountControl::ALT_HILIM = 85.0;
    double AltAzMountControl::ALT_INIT = 89.5;
    double AltAzMountControl::ALT_DVMAX = 1.0;
    double AltAzMountControl::ALT_DAMAX = 2.0;
    double AltAzMountControl::ALT_DJMAX = 10.0;
    double AltAzMountControl::ALT_GS = 1.2;
    double AltAzMountControl::ALT_GP = 0.1;
    double AltAzMountControl::ALT_GI = 0.01;
    double AltAzMountControl::ALT_PI = 1.0;
    double AltAzMountControl::ALT_GD = 0.2;
    double AltAzMountControl::ALT_PNEAR = 0.01;
}

