/// \file opticsCmd.cpp
/// \brief Implementation of the Tcl optics command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <slalib.h>
#include <tcl.h>
#include "commands.h"
#include "tpk.h"
#include "Pcs.h"

namespace dpk {

/// Handler procedure for the tpk::optics command.
/**
    The offset command selects whether the optics tip and tilt takes account
    of the demand or achieved position of the telescope and takes the following
    form:
        - optics track_mount state
*/
    extern "C" int OpticsCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {

    // Command option names
        static const char* options[] = {"track_mount", NULL};
        enum { TRACK_MOUNT = 0};

    // Command argument positions
        enum {OPTION = 1, STATE = 2};

    // Get subcommand.
        int iopt;
        ASSERT_ARG_PRESENT(OPTION,"option");
            if ( Tcl_GetIndexFromObj( interp, objv[OPTION], options, "option", 0,
                &iopt) != TCL_OK ) return TCL_ERROR;
        switch (iopt) {

        // Track mount achieved position
            case TRACK_MOUNT: {

            // Get flag
                ASSERT_ARG_PRESENT(STATE,"state");
                ASSERT_NO_MORE_ARGS(STATE);
                int flag;
                if ( Tcl_GetBooleanFromObj( interp, objv[STATE], &flag ) != TCL_OK )
                        return TCL_ERROR;

            // Set the global flag.
                static_cast<Pcs*>(clientdata)->mTrackMount = (flag == 1);
                break;
            }
        }
        return TCL_OK;
    }
}

