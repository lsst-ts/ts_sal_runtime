/// \file guideCmd.cpp
/// \brief Implementation of the Tcl guide command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <slalib.h>
#include <tcl.h>
#include "tpk.h"

#include "commands.h"
#include "Pcs.h"
#include "tpkobj.h"

namespace dpk {

/// Handler procedure for the tpk::guide command.
/**
    The guider command takes the following forms:
        - guide \<guider\> enable
        - guide \<guider\> disable
        - guide \<guider\> capture
        - guide \<guider\> track_rotator \<state\>
*/
    extern "C" int GuideCmd( ClientData clientdata, Tcl_Interp *interp, int objc,
            Tcl_Obj *CONST objv[]) {

    // guide command options
        static const char* options[] = {
            "enable", "disable", "capture", "track_rotator", NULL
        };
        enum { ENABLE =0 , DISABLE = 1, CAPTURE = 2 , TRACK_ROTATOR = 3 };

    // Command argument positions
        enum {GUIDER = 1, OPTION = 2, STATE = 3};

    // Get guider
        ASSERT_ARG_PRESENT(GUIDER,"guider");
        TpkObj<Pcs::guider>::Tpk_Obj* guiderObj =
                static_cast<Pcs*>(clientdata)->mGuiders->GetObj( interp, 
                objv[GUIDER]);
        if ( guiderObj == NULL ) return TCL_ERROR;

    // Get subcommand.
        int iopt;
        ASSERT_ARG_PRESENT(OPTION,"option");
            if ( Tcl_GetIndexFromObj( interp, objv[OPTION], options, "option", 
                0, &iopt) != TCL_OK ) return TCL_ERROR;
        switch (iopt) {

        // Enable guiding
            case ENABLE: {
                ASSERT_NO_MORE_ARGS(OPTION);

            // Set the global flag.
                guiderObj->obj->guide = true;
                break;
            }

        // Disable guiding
            case DISABLE: {
                ASSERT_NO_MORE_ARGS(OPTION);

            // Set the global flag.
                guiderObj->obj->guide = false;
                break;
            }

        // Capture target position.
            case CAPTURE: {
                ASSERT_NO_MORE_ARGS(OPTION);
                guiderObj->obj->gvt->guideTarget();
                break;
            }

        // Track rotator achieved position
            case TRACK_ROTATOR: {

            // Get flag
                ASSERT_ARG_PRESENT(STATE,"state");
                ASSERT_NO_MORE_ARGS(STATE);
                int flag;
                if ( Tcl_GetBooleanFromObj( interp, objv[STATE], &flag ) != TCL_OK )
                        return TCL_ERROR;

            // Set the global flag.
                guiderObj->obj->track_rot = (flag == 1);
                break;
            }
        }
        return TCL_OK;
    }
}

