/// \file ephempathcmd.cpp
/// \brief Implementation of the Tcl ephempath command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <tcl.h>
#include "tpk.h"

#include "commands.h"

namespace dpk {

/// Handler procedure for the tpk::ephempath command.
/**
    The ephempath command sets the set the path to the planetary ephemeris
    files and takes the form:
        - ephempath \<path\>
*/
    extern "C" int EphempathCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {
            
    // Command argument positions
        enum { PATH = 1 };

    // Set the path.
        ASSERT_ARG_PRESENT(PATH,"path");
        ASSERT_NO_MORE_ARGS(PATH);
        tpk::Planet::ephemPath(Tcl_GetString(objv[1]));
        return TCL_OK;
    }
}

