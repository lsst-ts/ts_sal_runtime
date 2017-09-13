/// \file statsCmd.cpp
/// \brief Implementation of the Tcl stats command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"

namespace dpk {

/// Handler procedure for the tpk::stats command.
    extern "C" int StatsCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {

    // stats should have no arguments.
        ASSERT_NO_ARGS("stats");

    // Call kernel stats process.
        static_cast<Pcs*>(clientdata)->stats();

        return TCL_OK;
    }
}

