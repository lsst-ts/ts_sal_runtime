/// \file UnixClock.h
/// \brief Definition of the Unix clock class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkUNIXCLOCK_H
#define tpkUNIXCLOCK_H

#include <stdexcept>

#include "Clock.h"

namespace tpk {

/// Error returned by gettimeofday
    class timeofday_error : public std::runtime_error {
        public:
            int code;         ///< Error code
            timeofday_error( int c ) :
                std::runtime_error("error returned by gettimeofday"),
                        code(c) {}
    };

/// A Clock that reads the Unix system clock
/**
    The UnixClock is an implementation of Clock that reads the Unix system
    clock which is a assumed to be some fixed number of seconds offset
    from TAI.
*/

    class UnixClock: public virtual Clock {
        public:
            UnixClock(
                const double& offset = 0.0
            ) throw();
            double read( void ) throw(timeofday_error);
        private:
            double mOffset;       ///< System clock offset from TAI (sec)
    };
}
#endif

