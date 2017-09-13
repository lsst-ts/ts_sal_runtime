/// \file TcsMutex.h
/// \brief Defines a generic interface to mutex implementations

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkTCSMUTEX_H
#define tpkTCSMUTEX_H

#include <tcl.h>

namespace tpk {

/// Wrapper for implementation specific mutex implementation.
/**
    This implementation use the Tcl mutex facility.
*/
    class TcsMutex {
        public:
            mMutex() {
                mMutex = 0;
            }
            void lock( void ) {
                Tcl_MutexLock( mMutex );
            }
            void unlock ( void) {
                Tcl_MutexUnlock( mMutex );
            }
        private:
    Tcl_Mutex* mMutex;
    };
}
#endif

