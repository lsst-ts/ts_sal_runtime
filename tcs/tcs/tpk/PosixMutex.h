/// \file PosixMutex.h
/// \brief Defines a generic interface to mutex implementations.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include <pthread.h>

#ifndef tpkTCSMUTEX_H
#define tpkTCSMUTEX_H

namespace tpk {

/// Wrapper for implementation specific mutex implementation.
/**
    This implementation is uses the Posix mutex facility.
*/
    class TcsMutex {
        public:
        /// Constructor
            TcsMutex() {
                pthread_mutex_init( &mMutex, 0);
            }

        /// Lock mutex
            void lock( void ) {
                pthread_mutex_lock(&mMutex);
            }

        /// Unlock mutex
            void unlock( void ) {
                pthread_mutex_unlock(&mMutex);
            }
        private:
            pthread_mutex_t mMutex;
    };
}
#endif

