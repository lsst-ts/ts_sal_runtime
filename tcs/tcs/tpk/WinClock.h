/// \file WinClock.h
/// \brief Definition of the the Windows clock class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkWINCLOCK_H
#define tpkWINCLOCK_H

#include <stdexcept>

#include "Clock.h"

namespace tpk {

/// A Clock that reads the Windows system clock
/**
    The WinClock is an implementation of Clock that reads the Windows system
    clock which is a assumed to be some fixed number of seconds offset
    from TAI.
*/
    class WinClock: public virtual Clock {
        public:
            WinClock(
                const double& offset = 0.0
            ) throw();
            double read() throw();
        protected:
            double mOffset;       ///< System clock offset from TAI (sec)
    };
}
#endif

