/// \file skySampleCmd.cpp
/// \brief Implementation of the Tcl skysample command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <stdlib.h>
#include <slalib.h>
#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"
#include "Util.h"
#include "tpkobj.h"

namespace dpk {

/// Handler procedure for the tpk::skysample command
/**
    The skysample command generates a list of star coordinates randomly placed
    around the target position being tracked by a mount virtual telescope. The
    first star in the list is always at the target position and all lie within
    one arc-minute of that position. The form of the command is

        -  skysample \<mount\> \<number\>
*/
    extern "C" int SkySampleCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {
        Pcs* pcs = static_cast<Pcs*>(clientdata);
     
    // Command argumnent positions
        enum {MOUNT = 1, COUNT = 2 };

    // Get the name of the mount.
        ASSERT_ARG_PRESENT(MOUNT,"mount samples");
        TpkObj<tpk::MountVt>::Tpk_Obj* mountObj =
                static_cast<Pcs*>(clientdata)->mMounts->GetObj(interp, 
                objv[MOUNT]);
        if ( mountObj == NULL ) return TCL_ERROR;

    // get number of stars to fake.
        ASSERT_ARG_PRESENT(COUNT,"samples");
        ASSERT_NO_MORE_ARGS(COUNT);
        int count;
        if ( Tcl_GetIntFromObj( interp, objv[COUNT], &count) != TCL_OK ) {
            return TCL_ERROR;
        }
        if ( count < 1 ) {
            Tcl_SetResult( interp, "at least one star is required", TCL_VOLATILE );
            return TCL_ERROR;
        }

    // Clear the sample array.
        pcs->mSkySamples.clear();

    // List object for result.
        Tcl_Obj* result = Tcl_NewListObj( 0, NULL);

    // Get a copy of the current target.
        tpk::Target* target = mountObj->obj->getTarget();

    // First point is the target position.
        pcs->mSkySamples.push_back(target->position( pcs->mTai, 
                tpk::ICRefSys()));
        for ( int i = 1; i < count; i++ ) {
            pcs->mSkySamples.push_back( pcs->mSkySamples[0] + tpk::xycoord(
                    (rand()/double(RAND_MAX) * 120.0 - 60.0) * 
                    tpk::TcsLib::as2r,
                    (rand()/double(RAND_MAX) * 120.0 - 60.0) * 
                    tpk::TcsLib::as2r ));
        }

    // Format RA, Dec.
        for ( int i = 0; i < count; i++ ) {
            tpk::spherical s = pcs->mSkySamples[i];
            Tcl_ListObjAppendElement( interp, result,
                Tcl_NewStringObj(Util::formatRaDec(s.a, s.b ).c_str(), -1));
        }

    // Set result.
        Tcl_SetObjResult( interp, result );

    // Delete the target.
        delete target;

        return TCL_OK;
    }
}

