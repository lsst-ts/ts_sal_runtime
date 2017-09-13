/// \file targetCmd.cpp
/// \brief Implementation of the Tcl target command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <stdexcept>
#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"
#include "Util.h"
#include "tpkobj.h"

namespace dpk {


/// Handler procedure for the tpk::target command.
/**
    The target command creates and manipulates targets and takes the following
    forms:
        - target create \<target_description\> ?frame? ?name?
        - target delete \<target\>
        - target set \<telescope\> \<target\>
        - target format \<target\> ?frame?
*/
    extern "C" int TargetCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {
            
    // target command options
        static const char* options[] = {
            "create", "delete", "set", "format", NULL
        };
        enum { CREATE = 0, DELETE = 1, SET = 2, FORMAT = 3 };

    // Command argument positions
        enum { OPTION = 1,
                CREATE_FRAME = 2, POSITION = 3, CREATE_NAME = 4,
                DELETE_TARGET = 2,
                TELESCOPE = 2, SET_TARGET = 3,
                FORMAT_TARGET = 2, FORMAT_FRAME = 3
        };

    // Target types
        static const char* tartypes[] = {"orbit", NULL};
        enum {FRAME = -1, ORBIT = 0, PLANET = 1};

    // Planet names
        static const char* planets[] = {
            "mercury", "venus", "mars", "jupiter", "saturn", "uranus", 
            "neptune", "pluto", NULL
        };
        enum {
            MERCURY = 0, VENUS = 1, MARS = 2, JUPITER = 3, SATURN = 4,
            URANUS = 5, NEPTUNE =6, PLUTO = 7
        };

        static tpk::Planet::names tpkNames[] = {
            tpk::Planet::Mercury, tpk::Planet::Venus, tpk::Planet::Mars,
            tpk::Planet::Jupiter, tpk::Planet::Saturn, tpk::Planet::Uranus,
            tpk::Planet::Neptune, tpk::Planet::Pluto
        };
        
    // Get command option
        ASSERT_ARG_PRESENT(OPTION,"option");
        int iopt;
        if ( Tcl_GetIndexFromObj( interp, objv[OPTION], options, "option",
                    0, &iopt) != TCL_OK ) {
            return TCL_ERROR;
        }

        TpkObj<tpk::Target>* targets = static_cast<Pcs*>(clientdata)->mTargets;
        tpk::Site* site = static_cast<Pcs*>(clientdata)->mSite;
        double tai = static_cast<Pcs*>(clientdata)->mTai;
        switch (iopt) {

        // Create new target.
            case CREATE: {
                ASSERT_ARG_PRESENT(CREATE_FRAME,"type ?position? ?name?");
                tpk::RefSys* refsys;
                int type;
                int name = CREATE_NAME;

            // See if the type is a frame.
                refsys = Util::refsysFromObj( interp, objv[CREATE_FRAME]);
                if ( refsys != NULL ) {
                    type = FRAME;
                } else {

                // It isn't, try a target type.
                    if ( Tcl_GetIndexFromObj( interp, objv[CREATE_FRAME], 
                            tartypes, "", 0, &type) != TCL_OK ) {

                    // See if it looks like the name of a planet.
                        int planet;
                        if ( Tcl_GetIndexFromObj( interp, objv[CREATE_FRAME], 
                                planets, "", 0, &planet) == TCL_OK ) {
                            type = PLANET;
                            } else {
                            Tcl_SetResult(interp, "target type not recognised",
                                        TCL_VOLATILE);
                            return TCL_ERROR;
                        }
                    }
                }
                tpk::Target* target;
                try {
                    switch (type) {
                        case FRAME:
                    if ( ! ARG_PRESENT(POSITION) ) {
                                Tcl_WrongNumArgs( interp, POSITION, objv,
                                            "position ?name?" );
                                delete refsys;
                                return TCL_ERROR;
                            }
                            target = refsys->target( *site,
                                    Tcl_GetStringFromObj( objv[POSITION], 
                                    NULL ) );
                            delete refsys;
                            break;

                        case PLANET:
                            int planet;
                            if ( Tcl_GetIndexFromObj( interp, 
                                    objv[CREATE_FRAME], planets, "", 0, 
                                    &planet) != TCL_OK ) return TCL_ERROR;
                            target = new tpk::Planet(*site, tpkNames[planet]);
                            name = POSITION;
                            break;

                        case ORBIT:
                            Tcl_SetResult( interp, "Target type not implemented",
                                    TCL_VOLATILE);
                            return TCL_ERROR;
                            break;
                    }

                } catch (std::runtime_error& error) {
                    Tcl_SetResult( interp, const_cast<char*>(error.what()),
                            TCL_VOLATILE );
                        return TCL_ERROR;
                }
                if ( MORE_ARGS(name) ) {
                    Tcl_WrongNumArgs( interp, CREATE_NAME, objv, "" );
                    return TCL_ERROR;
                }

            // Create target with specified name.
                if ( ARG_PRESENT(name) ) {
                    if ( targets->NewObj( interp, target, objv[name] ) == 
                                NULL ) {
                        delete target;
                        return TCL_ERROR;
                    }
                } else {

                // If the target is a planet use the planet name as the target 
                // name.
                    if ( type == PLANET ) {
                        if ( targets->NewObj( interp, target, 
                                    objv[CREATE_FRAME] ) == NULL ) {
                            delete target;
                            return TCL_ERROR;
                        }
                    } else {
                        if ( targets->NewObj( interp, target, 0 ) == NULL ) {
                            delete target;
                            return TCL_ERROR;
                        }
                    }
                }
                break;
            }

        // Delete target
            case DELETE: {
                ASSERT_ARG_PRESENT(DELETE_TARGET,"target");
                ASSERT_NO_MORE_ARGS(DELETE_TARGET);
                TpkObj<tpk::Target>::Tpk_Obj* targetObj =
                        targets->GetObj( interp, objv[DELETE_TARGET]);
                if ( targetObj == NULL ) return TCL_ERROR;
                return targets->FreeObj( interp, targetObj );
                break;
            }

        // Set target
            case SET: {
                ASSERT_ARG_PRESENT(TELESCOPE,"telescope target");
                TpkObj<tpk::BaseVt>::Tpk_Obj* telObj =
                        static_cast<Pcs*>(clientdata)->mTelescopes->
                        GetObj(interp, objv[TELESCOPE]);
                if ( telObj == NULL ) return TCL_ERROR;
                ASSERT_ARG_PRESENT(SET_TARGET,"target");
                ASSERT_NO_MORE_ARGS(SET_TARGET);
                TpkObj<tpk::Target>::Tpk_Obj* targetObj =
                        targets->GetObj( interp, objv[SET_TARGET]);
                if ( targetObj == NULL ) return TCL_ERROR;
                telObj->obj->newTarget( *targetObj->obj );
                break;
            }

        // Format target
            case FORMAT: {
                tpk::RefSys* refsys;
                ASSERT_ARG_PRESENT(FORMAT_TARGET,"target ?frame?");
                if ARG_PRESENT(FORMAT_FRAME) {
                    ASSERT_NO_MORE_ARGS(FORMAT_FRAME);
                    refsys = Util::refsysFromObj( interp, objv[FORMAT_FRAME]);
                    if ( refsys == NULL ) return TCL_ERROR;
                } else {
                    refsys = tpk::defaultFrame->clone();
                }
                TpkObj<tpk::Target>::Tpk_Obj* targetObj =
                        targets->GetObj( interp, objv[FORMAT_TARGET]);
                if ( targetObj == NULL ) return TCL_ERROR;

            // Format the Target.
                tpk::spherical p = targetObj->obj->position( tai, *refsys);
                if (typeid(*refsys) == typeid(tpk::AzElRefSys)) {
                        Tcl_SetObjResult( interp, Tcl_NewStringObj(
                                Util::formatAzEl( p.a, p.b ).c_str(), -1));
                    } else {
                        Tcl_SetObjResult( interp, Tcl_NewStringObj(
                            Util::formatRaDec( p.a, p.b ).c_str(), -1 ));
                    }
                delete refsys;
            }
        }
        return TCL_OK;
    }
}


