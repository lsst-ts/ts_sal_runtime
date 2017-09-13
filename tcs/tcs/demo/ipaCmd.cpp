/// \file ipaCmd.cpp
/// \brief Implementation of the Tcl ipa command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"
#include "Util.h"
#include "tpkobj.h"

namespace dpk {

/// Handler procedure for the tpk::ipa command.
/**
    The ipa command sets the instrument position angle for a mount virtual telescope
    and takes the following forms:
        - ipa \<mount\> \<angle\>
        - ipa \<mount\> \<angle\> \<frame\>
*/
    extern "C" int IpaCmd( ClientData clientdata, Tcl_Interp *interp, int objc,
            Tcl_Obj *CONST objv[]) {

    // Command argument positions
        enum {MOUNT = 1, ANGLE = 2, FRAME = 3};
        
    // Get the name of the mount.
        ASSERT_ARG_PRESENT(MOUNT,"mount");
        TpkObj<tpk::MountVt>::Tpk_Obj* mountObj =
                static_cast<Pcs*>(clientdata)->mMounts->GetObj( interp, 
                objv[MOUNT]);
        if ( mountObj == NULL ) return TCL_ERROR;

    // Get angle.
        ASSERT_ARG_PRESENT(ANGLE,"angle");
        double angle;
        if ( Tcl_GetDoubleFromObj( interp, objv[ANGLE], &angle ) != TCL_OK )
                return TCL_ERROR;

    // Get the coordinate frame.
        tpk::RefSys* refsys;
        if ARG_PRESENT(FRAME) {
            ASSERT_NO_MORE_ARGS(FRAME);
            refsys = Util::refsysFromObj( interp, objv[FRAME]);
            if ( refsys == NULL ) return TCL_ERROR;
        } else {
            refsys = tpk::defaultFrame->clone();
        }

    // Set IPA.
        mountObj->obj->setPai( angle * tpk::TcsLib::d2r, *refsys, true);
        delete refsys;
        return TCL_OK;
    }
}

