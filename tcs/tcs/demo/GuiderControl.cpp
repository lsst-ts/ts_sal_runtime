/// \file GuiderControl.cpp
/// \brief Implementation of the guider control class

// D L Terrett
// Copyright STFC. All rights reserved.

#include "GuiderControl.h"
#include "tpk.h"
#include "Axis.h"
#include "Pcs.h"

namespace dpk {
    void GuiderControl::track(
            double tai,                     ///< time (TAI, MJD)
            const tpk::Trajectory& x,      ///< x axis demand
            const tpk::Trajectory& y       ///< y axis demand
    ) {
    
    // Update the axis servos.
        mInPos1 = mAxis1->update(tai, x);
        mInPos2 = mAxis2->update(tai, y);
    }
    
    GuiderControl::GuiderControl(
        Pcs& pcs,                   ///< PCS
        const std::string& name1,   ///< first axis name
        const std::string& name2    ///< second axis name
    ) {
    
    // Create the axes.
        mAxis1 = new Axis( 0.05, 0.05, GUIDER_GS, GUIDER_GP, GUIDER_GI,
                GUIDER_PI, GUIDER_GD, GUIDER_PNEAR, GUIDER_LOLIM, 
                GUIDER_HILIM, GUIDER_DVMAX, GUIDER_DAMAX, GUIDER_DJMAX,
                GUIDER_INIT);
        mAxis2 = new Axis( 0.05, 0.05, GUIDER_GS, GUIDER_GP, GUIDER_GI,
                GUIDER_PI, GUIDER_GD, GUIDER_PNEAR, GUIDER_LOLIM, 
                GUIDER_HILIM, GUIDER_DVMAX, GUIDER_DAMAX, GUIDER_DJMAX,
                GUIDER_INIT);
                
    // Register the axis.
        pcs.registerAxis(mAxis1, name1);
        pcs.registerAxis(mAxis2, name2);
    }
    
// Guider axis servo parameters.
    double GuiderControl::GUIDER_LOLIM = -60.0;
    double GuiderControl::GUIDER_HILIM = 60.0;
    double GuiderControl::GUIDER_INIT = 60.0;
    double GuiderControl::GUIDER_DVMAX = 5.0;
    double GuiderControl::GUIDER_DAMAX = 10.0;
    double GuiderControl::GUIDER_DJMAX = 30.0;
    double GuiderControl::GUIDER_GS = 1.0;
    double GuiderControl::GUIDER_GP = 0.02;
    double GuiderControl::GUIDER_GI = 0.0;
    double GuiderControl::GUIDER_PI = 0.0;
    double GuiderControl::GUIDER_GD = 0.0;
    double GuiderControl::GUIDER_PNEAR = 0.01;
}

