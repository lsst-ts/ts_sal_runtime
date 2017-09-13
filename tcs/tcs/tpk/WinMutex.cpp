/// \file WinMutex.cpp
/// \brief Implements the TcsMutex class using windows critical sections.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "TcsMutex.h"

namespace tpk {
    TcsMutex::TcsMutex() {
        mMutex = new CRITICAL_SECTION;
        InitializeCriticalSection((LPCRITICAL_SECTION)mMutex);
    };
    void TcsMutex::lock() {
        EnterCriticalSection((LPCRITICAL_SECTION)mMutex);
    };
    void TcsMutex::unlock () {
        LeaveCriticalSection((LPCRITICAL_SECTION)mMutex);
    };
}
