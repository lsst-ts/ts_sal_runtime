/// \file TClClock.cpp
/// \brief Implementation of the TclClock class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "TclClock.h"

#include <tcl.h>

namespace tpk {

/// Constructor with offset.
/**
    The offset parameter defines the time difference between the system
    clock and TAI (in the sense TAI - clock). For a clock running on UTC
    the offset is currently (January 2004) 32s and increases by 1s every
    time UTC undergoes a leap second. For a clock synchronized with GPS
    time the offset is a fixed 19s.
*/

    TclClock::TclClock(
        const double& offset ///< offset between system clock and TAI (seconds).
    ) throw() : mOffset(offset) {}

/// Read system clock
/**
    Reads the system clock and returns the current TAI as a
    Modified Julian Date.

    \returns TAI (MJD)
*/
    double TclClock::read( void ) throw () {

    // Get seconds since midnight 1970 January 1 from system clock.
        Tcl_Time timeb;
        Tcl_GetTime( &timeb );

    // Convert to MJD.
        double mjd = (double(timeb.sec) + mOffset) / 86400.0 + 40587.0 +
                double(timeb.usec) / 1000000.0 / 86400.0;
        return mjd;
    }
}

