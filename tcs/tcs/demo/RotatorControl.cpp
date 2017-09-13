/// \file RotatorControl.cpp
/// \brief Implementation of the rotator control class

// D L Terrett
// Copyright STFC. All rights reserved.

#include "RotatorControl.h"
#include "tpk.h"
#include "Axis.h"
#include "Pcs.h"

namespace dpk {
    void RotatorControl::track(
            double tai,                     ///< time (TAI, MJD)
            const tpk::Trajectory& rma      ///< rotator demand
    ) {
    
    // Update the rotary axis controller.
        tpk::Trajectory r = mRotAxis->track(tai, rma, mWrap);
    
    // Update the axis servos.
        mInPos = mLinAxis->update(tai, axis2enc(r)) || 
                mRotAxis->isInLimit();
        
    // Update the achieved axis position
        mRotAxis->position(tai, enc2axis(mLinAxis->position()));
    }
    
    RotatorControl::RotatorControl(
        Pcs& pcs,                   ///< PCS
        const std::string& name     ///< axis name
    ) {
    
    // Create the rotatary axis object.
        mRotAxis = new tpk::RotaryAxis(0.0, tpk::TcsLib::r2d, 
                ROT_LOLIM ,ROT_HILIM, ROT_INIT);
                
    // Create the axes.
        mLinAxis = new Axis( 0.05, 0.05, ROT_GS, ROT_GP, ROT_GI, ROT_PI, ROT_GD,
                ROT_PNEAR, axis2enc(ROT_LOLIM), axis2enc(ROT_HILIM),
                axis2enc(ROT_DVMAX), axis2enc(ROT_DAMAX), axis2enc(ROT_DJMAX),
                axis2enc(ROT_INIT));
                
    // Register the axis.
        pcs.registerAxis(mLinAxis, &mWrap, name);
    }
    double RotatorControl::ROT_LOLIM = -90.0;
    double RotatorControl::ROT_HILIM = 90.0;
    double RotatorControl::ROT_INIT = 0.0;
    double RotatorControl::ROT_DVMAX = 2.0;
    double RotatorControl::ROT_DAMAX = 2.0;
    double RotatorControl::ROT_DJMAX = 10.0;
    double RotatorControl::ROT_GS = 1.5;
    double RotatorControl::ROT_GP = 0.1;
    double RotatorControl::ROT_GI = 0.01;
    double RotatorControl::ROT_PI = 1.0;
    double RotatorControl::ROT_GD = 0.2;
    double RotatorControl::ROT_PNEAR = 0.01;
}

