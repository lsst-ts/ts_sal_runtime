/// \file mediumCmd.cpp
/// \brief Implementation of the Tcl medium command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"

namespace dpk {

/// Handler procedure for the tpk::medium command.
    extern "C" int MediumCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {

// medium should have no arguments.
        ASSERT_NO_ARGS("medium");

    // Call kernel medium process.
        static_cast<Pcs*>(clientdata)->medium();

        return TCL_OK;
    }
}

