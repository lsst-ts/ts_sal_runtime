/// \file pointingCmd.cpp
/// \brief Implementation of the Tcl pointing command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <slalib.h>
#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"
#include "tpkobj.h"

namespace dpk {


// Handler procedure for the tpk::pointing command.
/**
    The pointing cpmmand controls the pointing of a mount virtual telescope and
    takes the following forms:
        - pointing \<controller\> set \<level\> \<roll\> \<pitch\>
        - pointing \<controller\> adjust \<level\> \<roll\> \<pitch\>
        - pointing \<controller\> absorb \<level\>
        - pointing \<controller\> tune \<axis\> \<values\>
*/
    extern "C" int PointingCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {

    // Command options
        static const char* options[] = {
            "set", "adjust", "absorb", "show", "tune", NULL
        };
        enum { SET = 0, ADJUST = 1, ABSORB = 2, SHOW = 3, TUNE = 4 };

    // Levels
        static const char* levelnames[] = {"guide", "local", NULL};
        enum { GUIDE = 0, LOCAL = 1};

    // Axes
        static const char* axes[] = {"azimuth", "elevation", NULL};
        enum { AZIMUTH = 0, ELEVATION = 1 };

    // Command argument positions
        enum {CONTROLLER = 1, OPTION = 2, LEVEL = 3, AXIS = 3, ROLL = 4,
                VALUES = 4, PITCH = 5};
                
    // Get pointing controller
        ASSERT_ARG_PRESENT(CONTROLLER,"controller option");
        TpkObj<tpk::PointingControl>::Tpk_Obj* pointObj =
                static_cast<Pcs*>(clientdata)->mPointing->GetObj( interp,
                objv[CONTROLLER]);
        if ( pointObj == NULL ) return TCL_ERROR;

    // Get subcommand.
        int iopt;
        ASSERT_ARG_PRESENT(OPTION,"option");
        if ( Tcl_GetIndexFromObj( interp, objv[OPTION], options, "option", 0,
                    &iopt) != TCL_OK ) return TCL_ERROR;

    // Absorb.
        switch (iopt) {
            case ABSORB: {
                ASSERT_NO_MORE_ARGS(OPTION);
                pointObj->obj->absorb();
                break;
            }
            case SHOW: {

            // Decode level.
                int level;
                ASSERT_ARG_PRESENT(LEVEL,"level");
                if ( Tcl_GetIndexFromObj( interp, objv[LEVEL], levelnames,
                        "level", 0, &level) != TCL_OK ) return TCL_ERROR;
                        Tcl_Obj* result = Tcl_NewListObj(-1, NULL);

                tpk::focalplane s;
                switch (level) {
                    case GUIDE:
                        s = pointObj->obj->getGuide();
                        break;
                    case LOCAL:
                        s = pointObj->obj->getLocal();
                        break;
                }
                Tcl_ListObjAppendElement(interp, result,
                        Tcl_NewDoubleObj(s.a/tpk::TcsLib::as2r));
                Tcl_ListObjAppendElement(interp, result,
                        Tcl_NewDoubleObj(s.b/tpk::TcsLib::as2r));
                Tcl_SetObjResult(interp, result);
                break;
            }
            case SET:
            case ADJUST: {

            // Decode level.
                int level;
                ASSERT_ARG_PRESENT(LEVEL,"level roll pitch");
                if ( Tcl_GetIndexFromObj( interp, objv[LEVEL], levelnames,
                        "level", 0, &level) != TCL_OK ) return TCL_ERROR;

            // Decode a & b
                ASSERT_ARG_PRESENT(ROLL,"roll pitch");
                ASSERT_ARG_PRESENT(PITCH,"pitch");
                ASSERT_NO_MORE_ARGS(PITCH);
                double ga, gb;
                if ( Tcl_GetDoubleFromObj( interp, objv[ROLL], &ga ) != TCL_OK )
                        return TCL_ERROR;
                if ( Tcl_GetDoubleFromObj( interp, objv[PITCH], &gb ) != TCL_OK )
                        return TCL_ERROR;
                if ( iopt == SET ) {

                // Set
                    switch (level) {
                        case GUIDE:
                            pointObj->obj->setGuide( tpk::focalplane( ga * tpk::TcsLib::as2r,
                                    gb * tpk::TcsLib::as2r), 0.0, tpk::OTA());
                            break;
                        case LOCAL:
                            pointObj->obj->setLocal( tpk::focalplane( ga * tpk::TcsLib::as2r,
                                    gb * tpk::TcsLib::as2r), 0.0, tpk::OTA());
                            break;
                    }
                } else {

                // Adjust
                    switch (level) {
                        case 0:
                            pointObj->obj->adjustGuide(tpk::focalplane( ga * tpk::TcsLib::as2r,
                                    gb * tpk::TcsLib::as2r), 0.0, tpk::OTA());
                            break;
                        case 1:
                            pointObj->obj->adjustLocal(tpk::focalplane( ga * tpk::TcsLib::as2r,
                                    gb * tpk::TcsLib::as2r), 0.0, tpk::OTA());
                            break;
                    }
                }
                break;
            }
            case TUNE: {

            // Decode axis
                ASSERT_ARG_PRESENT(AXIS,"axis values");
                int axis;
                if ( Tcl_GetIndexFromObj( interp, objv[AXIS], axes, "axis", 0,
                        &axis) != TCL_OK ) return TCL_ERROR;
                tpk::PiFilter* f;
                switch (axis) {
                    case AZIMUTH:
                        f = &dynamic_cast<tpk::PiFilter&>(pointObj->obj->rollFilter());
                        break;
                    case ELEVATION:
                        f = &dynamic_cast<tpk::PiFilter&>(pointObj->obj->pitchFilter());
                        break;
                }

            // Get parameter values
                ASSERT_ARG_PRESENT(VALUES,"values");
                ASSERT_NO_MORE_ARGS(VALUES);
                Tcl_Obj** values;
                int c;
                if ( Tcl_ListObjGetElements( interp, objv[VALUES], &c, &values)
                        != TCL_OK )return TCL_ERROR;
                if ( c != 4 ) {
                    Tcl_SetResult(interp, "parameter list must have 4 elements",
                            TCL_VOLATILE);
                    return TCL_ERROR;
                }
                double vals[4];
                for ( int i = 0; i < 4; i++ ) {
                    if ( Tcl_GetDoubleFromObj(interp, values[i], &vals[i]) != TCL_OK )
                            return TCL_ERROR;
                }

            // Set filter parameters
                f->tune(vals[0], vals[1], vals[2], vals[3]);
                break;
            }
        }
        return TCL_OK;
    }
}

