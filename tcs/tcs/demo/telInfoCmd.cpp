/// \file telInfoCmd.cpp
/// \brief Implementation of the Tcl telinfo command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <tcl.h>
#include "commands.h"
#include "Pcs.h"
#include "tpkobj.h"

namespace dpk {


// Handler procedure for the tpk::telinfo command.
/**
    The telinfo command returns a list of tcs objects and takes the 
    folloing form
    
        - telinfo \<object\>
*/
    extern "C" int TelInfoCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {

    // Command argument positions
        enum {OPTION = 1};

    // options
        static const char* options[] = {
            "mounts", "telescopes", "targets", "origins", "axes",
            "guiders", "pointingcontrollers", "pointingmodels", NULL
        };
        enum {MOUNTS = 0, TELESCOPES = 1, TARGETS = 2, ORIGINS = 3,
            AXES = 4, GUIDERS = 5, POINTING = 6, MODELS = 7};
            
    // Get the option index
        ASSERT_ARG_PRESENT(OPTION,"option");
        ASSERT_NO_MORE_ARGS(OPTION);
        int iopt;
        if ( Tcl_GetIndexFromObj( interp, objv[OPTION], options,
                        "option", 0, &iopt)!= TCL_OK ) return TCL_ERROR;

    // Select hash table
        Tcl_HashTable* table;
        switch (iopt) {
            case MOUNTS:
                table = &static_cast<Pcs*>(clientdata)->mMounts->table;
                break;
            case TELESCOPES:
                table = &static_cast<Pcs*>(clientdata)->mTelescopes->table;
                break;
            case TARGETS:
                table = &static_cast<Pcs*>(clientdata)->mTargets->table;
                break;
            case ORIGINS:
                table = &static_cast<Pcs*>(clientdata)->mOrigins->table;
                break;
            case AXES:
                table = &static_cast<Pcs*>(clientdata)->mAxes->table;
                break;
            case GUIDERS:
                table = &static_cast<Pcs*>(clientdata)->mGuiders->table;
                break;
            case POINTING:
                table = &static_cast<Pcs*>(clientdata)->mPointing->table;
                break;
            case MODELS:
                table = &static_cast<Pcs*>(clientdata)->mModels->table;
                break;
        }

    // Create empty result
        Tcl_Obj* result = Tcl_NewListObj(-1, NULL);


    // Start search
        Tcl_HashSearch search;
        Tcl_HashEntry* ptr = Tcl_FirstHashEntry(table, &search);
        while ( ptr != NULL ) {

        // Get the key associated with this entry.
            char* key;
            key = Tcl_GetHashKey(table, ptr);

        // Append the key to the result.
            Tcl_ListObjAppendElement(interp, result, Tcl_NewStringObj(key, -1));

        // Get the next entry in the table.
            ptr = Tcl_NextHashEntry(&search);
        }
        Tcl_SetObjResult(interp, result);
        return TCL_OK;
    }
}

