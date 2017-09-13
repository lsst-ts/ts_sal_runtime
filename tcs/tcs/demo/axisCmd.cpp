/// \file axisCmd.cpp
/// \brief Implementation of the Tcl axis command handling procedure
// D L Terrett
// Copyright STFC. All rights reserved.

#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Axis.h"
#include "Pcs.h"
#include "tpkobj.h"

namespace dpk {
 
/// Handler procedure for the tpk::axis command
/**

    The axis command manipulates the state of a mechanism axis and takes
    the following forms:
        - axis \<axis\> enable
        - axis \<axis\> disable
        - axis \<axis\> tune par val
*/
    extern "C" int AxisCmd( ClientData clientdata, Tcl_Interp *interp, int objc,
            Tcl_Obj *CONST objv[]) {

    // Command argument positions
        enum { AXIS = 1, OPTION = 2, TUNEPAR = 3, TUNEVAL = 4};

    // Command options
        static const char* options[] = {
            "enable", "disable", "tune", NULL
        };
        enum {ENABLE = 0, DISABLE = 1, TUNE = 2};

    // Tuning parameters.
        static const char* tunepars[] = {
            "vcale", "gs", "gp", "gi", "pi", "gd", "pnear",
            "dpmin", "dpmax", "dvmax", "damax", "djmax", NULL
        };
        enum {
            VCALE = 0, GS = 1, GP = 2, GI = 3, PI = 4, GD = 5, PNEAR= 6,
            DPMIN = 7, DPMAX = 8, DVMAX = 9, DAMAX = 10, DJMAX = 11
        };
    // Get axis from hash table
            ASSERT_ARG_PRESENT(AXIS,"axis");
            TpkObj<Axis>::Tpk_Obj* axisObj =
                    static_cast<Pcs*>(clientdata)->mAxes->GetObj( 
                    interp, objv[AXIS]);
            if ( axisObj == NULL ) return TCL_ERROR;
            
    // Get the option index
        ASSERT_ARG_PRESENT(OPTION,"option");
        int iopt;
        if ( Tcl_GetIndexFromObj( interp, objv[OPTION], options,
                        "option", 0, &iopt)!= TCL_OK ) return TCL_ERROR;

        switch (iopt) {
             case ENABLE:
                ASSERT_NO_MORE_ARGS(OPTION);
                axisObj->obj->enable(true);
                break;

            case DISABLE:
                ASSERT_NO_MORE_ARGS(OPTION);
                axisObj->obj->enable(false);
                break;

            case TUNE:

            // Get the parameter index
                ASSERT_ARG_PRESENT(TUNEPAR,"parameter");
                int ipar;
                if ( Tcl_GetIndexFromObj( interp, objv[TUNEPAR], tunepars,
                        "parameter value", 0, &ipar)!= TCL_OK ) 
                        return TCL_ERROR;

            // Get the value.
                ASSERT_ARG_PRESENT(TUNEVAL,"value");
                ASSERT_NO_MORE_ARGS(TUNEVAL);
                double val;
                if ( Tcl_GetDoubleFromObj( interp, objv[TUNEVAL], &val) != 
                        TCL_OK ) return TCL_ERROR;

            // Update the servo.
                double tick = axisObj->obj->Tick * 86400.0;
                switch (ipar) {
                    case VCALE:
                        axisObj->obj->Vcale = val;
                        break;
                    case GS:
                        axisObj->obj->Gs = val;
                        break;
                    case GP:
                        axisObj->obj->Gp = val;
                        break;
                    case GI:
                        axisObj->obj->Gi = val;
                        break;
                    case PI:
                        axisObj->obj->Pi = val;
                        break;
                    case GD:
                        axisObj->obj->Gd = val;
                        break;
                    case PNEAR:
                        axisObj->obj->Pnear = val;
                        break;
                    case DPMIN:
                        axisObj->obj->DpMin = val;
                        break;
                    case DPMAX:
                        axisObj->obj->DpMax = val;
                        break;
                    case DVMAX:
                        axisObj->obj->DvMax = val * tick;
                        break;
                    case DAMAX:
                        axisObj->obj->DaMax = val * tick * tick;
                        break;
                    case DJMAX:
                        axisObj->obj->DjMax = val * tick * tick * tick;
                        break;
                }
        }
        return TCL_OK;
    }
}

