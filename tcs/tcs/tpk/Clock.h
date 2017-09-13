/// \file Clock.h
/// \brief Definition of the Clock class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkCLOCK_H
#define tpkCLOCK_H

#include <stdexcept>

namespace tpk {

/// Pure virtual base class for clocks
/**
    Clock is an abstract base class that defines the interface to the real-time
    clock.
*/
    class Clock {
        public:
            virtual ~Clock() {}

    /// Returns the current TAI as a Modified Julian Date
            virtual double read() throw(std::runtime_error) = 0;
    };
}
#endif

