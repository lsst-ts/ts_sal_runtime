/// \file UnixClock.cpp
/// \brief Implementation of the Unix clock class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "UnixClock.h"

#include <sys/time.h>
#include <time.h>

namespace tpk {

/// Constructor with offset.
/**
    The offset parameter defines the time difference between the system
    clock and TAI (in the sense TAI - clock). For a clock running on UTC
    the offset is currently (January 2004) 32s and increases by 1s every
    time UTC undergoes a leap second. For a clock synchronized with GPS
    time the offset is a fixed 19s.
*/

    UnixClock::UnixClock(
        const double& offset ///< offset between system clock and TAI (seconds).
    ) throw() : mOffset(offset) {}

/// Read system clock
/**
    Reads the system clock and returns the current TAI as a
    Modified Julian Date.

    \returns TAI (MJD)

    \exception UnixClock::timeofday_error
*/
    double UnixClock::read( void ) throw (timeofday_error) {

    // Read the system clock.
        struct timeval time;
        struct timezone tz;
        int code = gettimeofday( &time, &tz );
        if ( code ) {
            throw timeofday_error( code );
        }

    // Convert to MJD.
        double mjd = (double(time.tv_sec) + mOffset) / 86400.0 + 40587.0 +
                double(time.tv_usec) / 1000000.0 / 86400.0;
        return mjd;
    }
}

