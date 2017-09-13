/// \file originCmd.cpp
/// \brief Implementation of the Tcl optics command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <stdexcept>
#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"
#include "tpkobj.h"

namespace dpk {


/// Handler procedure for the tpk::origin command
/**
    The origin command creates and manipulates pointing origins and takes
    the following forms:
        - origin create \<x\> \<y\> ?name?
        - origin delete \<name\>
        - origin set \<telescope\> \<name\>
*/
    extern "C" int OriginCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {
            
    // origin command options
        static const char* options[] = {
            "create", "delete", "set", NULL
        };
        enum { CREATE = 0, DELETE = 1, SET = 2 };

    // Command argument positions
        enum {OPTION = 1, TELESCOPE = 2, DELNAME = 2, SETNAME = 3,
                X = 2, Y = 3, NEWNAME = 4};
        
    // Get command option
        ASSERT_ARG_PRESENT(OPTION,"option");
        int iopt;
        if ( Tcl_GetIndexFromObj( interp, objv[OPTION], options, "option",
                0, &iopt) != TCL_OK ) {
            return TCL_ERROR;
        }
        TpkObj<tpk::PointingOrigin>* origins =
                static_cast<Pcs*>(clientdata)->mOrigins;
        TpkObj<tpk::PointingOrigin>::Tpk_Obj* originObj;
        switch (iopt) {

        // Create new pointing origin.
            case CREATE: {
                if ( ! ARG_PRESENT(Y) ) {
                    Tcl_WrongNumArgs( interp, X, objv, "x y" );
                    return TCL_ERROR;
                }
                ASSERT_ARG_PRESENT(X,"x y ?name?");
                ASSERT_ARG_PRESENT(Y,"y ?name?");
                double x, y;
                if ( Tcl_GetDoubleFromObj( interp, objv[X], &x) != TCL_OK ||
                        Tcl_GetDoubleFromObj( interp, objv[Y], &y) != TCL_OK) {
                    return TCL_ERROR;
                }

            // Create new pointing origin.
                tpk::PointingOrigin* origin = new tpk::PointingOrigin(x, y,
                        tpk::AffineTransform(0.0, 0.0,
                        1.0/static_cast<Pcs*>(clientdata)->focalLength(), 0.0));

            // Store in hash table.
                if ( ARG_PRESENT(NEWNAME) ) {
                    ASSERT_NO_MORE_ARGS(NEWNAME);
                    if ( origins->NewObj( interp, origin, objv[NEWNAME] ) == NULL ) {
                        delete origin;
                        return TCL_ERROR;
                    }
                } else {
                    if ( origins->NewObj( interp, origin, 0 ) == NULL ) {
                        delete origin;
                        return TCL_ERROR;
                    }
                }
                break;
            }

        // Delete pointing origin
            case DELETE: {
                ASSERT_ARG_PRESENT(DELNAME,"name");
                ASSERT_NO_MORE_ARGS(DELNAME);
                originObj = origins->GetObj( interp, objv[DELNAME]);
                if ( originObj == NULL ) return TCL_ERROR;
                return origins->FreeObj( interp, originObj );
                break;
            }

        // Set pointing origin.
            case SET: {
                ASSERT_ARG_PRESENT(TELESCOPE,"telescope name");
                ASSERT_ARG_PRESENT(SETNAME,"name");
                ASSERT_NO_MORE_ARGS(SETNAME);
                TpkObj<tpk::BaseVt>::Tpk_Obj* telObj =
                        static_cast<Pcs*>(clientdata)->mTelescopes->
                        GetObj(interp, objv[TELESCOPE]);
                if ( telObj == NULL ) return TCL_ERROR;
                originObj = origins->GetObj( interp, objv[SETNAME]);
                if ( originObj == NULL ) return TCL_ERROR;
                telObj->obj->newPointingOrigin(*originObj->obj );
                break;
            }
        }
        return TCL_OK;
    }
}


