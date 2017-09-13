/// \file TclClock.h
/// \brief Definition of the TclClock class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkTCLCLOCK_H
#define tpkTCLCLOCK_H

#include "Clock.h"

namespace tpk {

/// A Clock that reads the system clock using the Tcl API
/**
    The TclClock is an implementation of Clock that reads the system
    clock which is a assumed to be some fixed number of seconds offset
    from TAI.
*/
    class TclClock: public virtual Clock {
        public:
            TclClock(
                const double& offset = 0.0
            ) throw();
            double read( void ) throw();
        private:
            double mOffset;    ///< System clock offset from TAI (sec)
    };
}
#endif

