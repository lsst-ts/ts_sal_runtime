/// \file limitTimeCmd.cpp
/// \brief Implementation of the Tcl limittime command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"
#include "Util.h"
#include "tpkobj.h"

namespace dpk {

/// Handler procedure for the tpk::limittime command.
/**
    The limittime command returns time at which the specified mount and rotator
    is expected to encounter a limit and takes the following form:
    
        - limittime 
*/
    extern "C" int LimitTimeCmd( ClientData clientdata, Tcl_Interp *interp, 
            int objc, Tcl_Obj *CONST objv[]) {

        ASSERT_NO_ARGS("limittime");
        
    // Get the name of the mount.
        Pcs* pcs = static_cast<Pcs*>(clientdata);
        
    // Set result
        Tcl_Obj* resv[2];
        resv[1] = Tcl_NewDoubleObj(pcs->limit());
        resv[0] = Tcl_NewStringObj(pcs->mLimitReason.c_str(), -1);                
        Tcl_SetObjResult(interp, Tcl_NewListObj(2, resv));

        return TCL_OK;
    }
}

