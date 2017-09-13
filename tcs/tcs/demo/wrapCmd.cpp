/// \file wrapCmd.cpp
/// \brief Implementation of the Tcl wrap command handling procedure
// D L Terrett
// Copyright STFC. All rights reserved.

#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"
#include "tpkobj.h"

namespace dpk {
 
/// Handler procedure for the tpk::wrap command
/**

    The wrap command sets the wrap control parameters of an axis with an 
    overlap region. The following forms:
        - wrap \<axis\> \<logic\> \<reference\> ?permanent?
*/
    extern "C" int WrapCmd( ClientData clientdata, Tcl_Interp *interp, 
            int objc, Tcl_Obj *CONST objv[]) {

    // Command argument positions
        enum { WRAP = 1, LOGIC = 2, REFERENCE = 3, PERM = 4};
        
    // Logic options
        static const char* logicopt[] = {
            "lowrange", "highrange", "nearestrange", "limit", NULL
        };
        
    // Reference position options
        static const char* refopt[] = {
            "demand", "achieved", NULL
        };
        
    // Get wrap from hash table
        ASSERT_ARG_PRESENT(WRAP,"axis");
        TpkObj<tpk::WrapControl>::Tpk_Obj* wrapObj =
                static_cast<Pcs*>(clientdata)->mWraps->GetObj( 
                interp, objv[WRAP]);
        if ( wrapObj == NULL ) return TCL_ERROR;
        
    // Get the wrap logic.
        ASSERT_ARG_PRESENT(LOGIC,"logic");
        int ilogic;
        if ( Tcl_GetIndexFromObj( interp, objv[LOGIC], logicopt,
                    "wrap logic", 0, &ilogic)!= TCL_OK ) return TCL_ERROR;

    // Get the position reference.
        ASSERT_ARG_PRESENT(REFERENCE,"reference");
        int iref;
        if ( Tcl_GetIndexFromObj( interp, objv[REFERENCE], refopt,
                    "reference position", 0, &iref)!= TCL_OK ) return TCL_ERROR;
                    
    // Get permanent flag
        int perm(0);
        if (ARG_PRESENT(PERM)) {
            ASSERT_NO_MORE_ARGS(PERM);
            if ( Tcl_GetBooleanFromObj( interp, objv[PERM], &perm ) 
                    != TCL_OK ) return TCL_ERROR;
        }
        
    // Configure wrap logic.
        if (perm) {
            wrapObj->obj->set(
                    static_cast<tpk::RotaryAxis::wraplogic>(ilogic),
                    static_cast<tpk::RotaryAxis::wrapref>(iref));
        } else {
            wrapObj->obj->setTemporary(
                    static_cast<tpk::RotaryAxis::wraplogic>(ilogic),
                    static_cast<tpk::RotaryAxis::wrapref>(iref));
        }
        return TCL_OK;
    }
}

