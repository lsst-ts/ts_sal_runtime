/// \file opticsControl.cpp
/// \brief Implementation of the optics control class

// D L Terrett
// Copyright STFC. All rights reserved.

#include "OpticsControl.h"
#include "Pcs.h"

namespace dpk {

/// Update optics tip/tilt
/**
    The x and y axes are set to the tip and tilt demands subjects
    to the low and high limits.
*/
    void OpticsControl::track(
        double tai,                     ///< time (TAI, MJD)
        const tpk::Trajectory& tip,     ///< tip demand
        const tpk::Trajectory& tilt     ///< tilt demand
    ) {
        mX = tip;
        if ( mX.sample(tai) < X_LOLIM ) {
            mX = X_LOLIM;
        } else if ( mX.sample(tai) > X_HILIM ) {
            mX = X_HILIM;
        }
        mY = tilt;
        if ( mY.sample(tai) < Y_LOLIM ) {
            mY = Y_LOLIM;
        } else if ( mY.sample(tai) > Y_HILIM ) {
            mX = Y_HILIM;
        }
    }
    
    double OpticsControl::X_LOLIM = -300 * tpk::TcsLib::as2r;
    double OpticsControl::X_HILIM =  300 * tpk::TcsLib::as2r;
    double OpticsControl::Y_LOLIM = -300 * tpk::TcsLib::as2r;
    double OpticsControl::Y_HILIM =  300 * tpk::TcsLib::as2r;
}

