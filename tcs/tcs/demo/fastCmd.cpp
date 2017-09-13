/// \file fastCmd.cpp
/// \brief Implementation of the Tcl fast command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"

namespace dpk {

/// Handler procedure for the tpk::fast command.
    extern "C" int FastCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {

    // fast should have no arguments.
        ASSERT_NO_ARGS("fast");

    // Call kernel fast process.
        static_cast<Pcs*>(clientdata)->fast();

        return TCL_OK;
    }
}

