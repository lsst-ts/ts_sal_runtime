/// \file TcsMutex.h
/// \brief Defines a generic interface to mutex implementations.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkTCSMUTEX_H
#define tpkTCSMUTEX_H

#include <stdexcept>

namespace tpk {

/// Wrapper for implementation specific mutex implementation.
/**
    This implementation is a dummy that checks that a mutex is never
    locked more than once and is never unlocked when not locked.
*/
    class TcsMutex {
        private:
            int c;
        public:
            TcsMutex::TcsMutex() : c(0) {};
            void lock( void ) {
                if ( c ) {
                    throw std::runtime_error("mutex already locked");
                } else {
                    c++;
                }
            }
            void unlock ( void) {
                if ( c ) {
                    c--;
                } else {
                    throw std::runtime_error("mutex not locked");
                }
            }
    };
}
#endif

