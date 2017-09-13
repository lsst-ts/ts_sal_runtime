/// \file offsetCmd.cpp
/// \brief Implementation of the Tcl offset command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <slalib.h>
#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"
#include "Util.h"
#include "tpkobj.h"

namespace dpk {

/// Handler procedure for the tpk::offset command.
/**
    The offset command sets the target offset for a virtual telescope and takes
    the following forms:
        - offset \<telescope\> \<x\> \<y\> ?frame?
*/
    extern "C" int OffsetCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {

    // Command argument positions
        enum {TELESCOPE = 1, X = 2, Y = 3, FRAME = 4};

    // Get the name of the telescope.
        ASSERT_ARG_PRESENT(TELESCOPE,"telescope");
        TpkObj<tpk::BaseVt>::Tpk_Obj* telObj =
                static_cast<Pcs*>(clientdata)->mTelescopes->
                GetObj( interp, objv[TELESCOPE]);
        if ( telObj == NULL ) return TCL_ERROR;

        // Get x and y.
        ASSERT_ARG_PRESENT(X,"x y ?frame?");
        double x;
        if ( Tcl_GetDoubleFromObj( interp, objv[X], &x ) != TCL_OK ) {
                return TCL_ERROR;
        }
        ASSERT_ARG_PRESENT(Y,"y ?frame?");
        double y;
        if ( Tcl_GetDoubleFromObj( interp, objv[Y], &y ) != TCL_OK ) {
                return TCL_ERROR;
        }
        x *= tpk::TcsLib::as2r;
        y *= tpk::TcsLib::as2r;

    // Look for a frame.
        tpk::RefSys* refsys;

        if ( ARG_PRESENT(FRAME) ) {
            ASSERT_NO_MORE_ARGS(FRAME);
            refsys = Util::refsysFromObj( interp, objv[FRAME]);
            if ( refsys == NULL ) return TCL_ERROR;

        // Set the new offset and frame in the telescope.
            telObj->obj->setOffset( x, y, *refsys);

        // Delete the reference frame.
            delete refsys;
        } else {

        // Set the new offset in the telescope without changing frame.
            telObj->obj->setOffset( x, y);
        }
        return TCL_OK;
    }
}

