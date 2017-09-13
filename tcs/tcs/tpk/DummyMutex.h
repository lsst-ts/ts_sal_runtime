/// \file TcsMutex.h
/// \brief Defines a generic interface to mutex implementations.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkTCSMUTEX_H
#define tpkTCSMUTEX_H

namespace tpk {

/// Wrapper for implementation specific mutex implementation.
/**
    This implementation is suitable for off-line applications
    and does nothing.
*/
    class TcsMutex {
        public:

        /// Lock mutex
            void lock( void ) {}

        /// Unlock mutex
            void unlock( void ) {}
    };
}
#endif

