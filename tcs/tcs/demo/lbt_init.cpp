/// \file lbt_init.cpp
/// \brief Tcl loadable extension initialisation procedure for the LBT PCS.
/*
    This file contains the initialisation procedure for the tcl loadable
    extension that is the core for the LBT prototype pointing kernel. The
    procedure is called Tpk_Init so that the extension can be loaded into
    a tcl interpreter with the command:

        load  tpkLbt.so tpk

    There are two versions, one for Microsoft windows and one for Linux
    (and other Unix like systems).
*/

// D L Terrett
// Copyright STFC. All rights reserved.

#include <tcl.h>
#include "dpk.h"

// Include the definition of LBT PCS class.
#include "LbtPcs.h"

#ifdef _WIN32  /* Windows */

#include <windows.h>

#ifndef DECLSPEC_EXPORT
#define DECLSPEC_EXPORT __declspec(dllexport)
#endif

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved){
    return TRUE;
}

EXTERN_C int DECLSPEC_EXPORT Tpk_Init(Tcl_Interp* interp) {

#else    /* Unix */

extern "C" int Tpk_Init(Tcl_Interp* interp) {

#endif

// This procedure is called every time that the extension is loaded into a
// Tcl interpreter but we only want one Pcs object so a pointer to the Pcs
// object is stored in a static variable which is initialised to the null
// pointer.
    static LbtPcs* lbt = NULL;

// Only create the Pcs object if it doesn't already exist.
    if ( ! lbt ) {

    // Create demonstration PCS object.
        try {
            lbt = new LbtPcs(interp);
        }
        catch (...) {

        // Any exception thown by the constructor is turned into a error
        // status return. A description of the error should have been stored
        // in the Tcl interpreter result already.
            return TCL_ERROR;
        }
    }

// Create Tcl commands.
    return createCommands( interp, lbt );
}


