/// \file TcsMutex.h
/// \brief Defines a generic interface to mutex implementations

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkTCSMUTEX_H
#define tpkTCSMUTEX_H

namespace tpk {

/// Wrapper for implementation specific mutex implementation.
/**
    This implementation use the Windows critical section facility.
*/
    class TcsMutex {
        public:
            TcsMutex();
            void lock();
            void unlock();
        private:
            void* mMutex;
    };
}
#endif

