/// \file slowCmd.cpp
/// \brief Implementation of the Tcl slow command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"

namespace dpk {

/// Handler procedure for the tpk::slow command.
    extern "C" int SlowCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {

// slow should have no arguments.
        ASSERT_NO_ARGS("slow");

// Get temperature pressure and humidity from tcl variables.
        Tcl_Obj* val;
        double temp, press, humid;
        val = Tcl_GetVar2Ex(interp, "tpk::temperature", "", TCL_GLOBAL_ONLY);
        if ( val ) {
            if ( Tcl_GetDoubleFromObj(interp, val, &temp) != TCL_OK ) {
                return TCL_ERROR;
            }
        } else {
            temp = 273.0;
        }
        val = Tcl_GetVar2Ex(interp, "tpk::pressure", "", TCL_GLOBAL_ONLY);
        if ( val ) {
            if ( Tcl_GetDoubleFromObj(interp, val, &press) != TCL_OK ) {
                return TCL_ERROR;
            }
        } else {
            press = 650.0;
        }
        val = Tcl_GetVar2Ex(interp, "tpk::humidity", "", TCL_GLOBAL_ONLY);
        if ( val ) {
            if ( Tcl_GetDoubleFromObj(interp, val, &humid) != TCL_OK ) {
                return TCL_ERROR;
            }
        } else {
            humid = 0.2;
        }

    // Call kernel slow process.
        static_cast<Pcs*>(clientdata)->slow(temp, press, humid);

        return TCL_OK;
    }
}

