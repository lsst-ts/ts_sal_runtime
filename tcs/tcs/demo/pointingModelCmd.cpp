/// \file pointingModelCmd.cpp
/// \brief Implementation of the Tcl pointingmodel command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <slalib.h>
#include <tcl.h>
#include <stdexcept>
#include <vector>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"
#include "tpkobj.h"

namespace dpk {


/// Handler procedure for the tpk::pointingmodel command
/**
        - pointingmodel load \<filename\> \<name\>
        - pointingmodel set \<mount\> \<model\>
        - pointingmodel show \<model\>
        - pointingmodel create \<model\> \<name\>
*/
    extern "C" int PointingModelCmd( ClientData clientdata, Tcl_Interp *interp,
        int objc, Tcl_Obj *CONST objv[]) {
        
    // pointingmodel command options
        static const char* options[] = {
            "create", "delete", "set", "show", "load", NULL
        };
        enum { CREATE = 0, DELETE = 1, SET = 2, SHOW = 3, LOAD = 4};

    // Command argument positions
        enum {OPTION = 1, LOAD_FILE =2, LOAD_NAME = 3, SET_MOUNT = 2,
                SET_NAME =3, SHOW_NAME =2, CREATE_MODEL = 2, CREATE_NAME = 3,
                DELETE_NAME = 2};
                
    // Get command option
        ASSERT_ARG_PRESENT(OPTION,"option");
        int iopt;
        if ( Tcl_GetIndexFromObj( interp, objv[OPTION], options, "option",
                0, &iopt) != TCL_OK ) {
            return TCL_ERROR;
        }
        TpkObj<tpk::PointingModel>* models =
                static_cast<Pcs*>(clientdata)->mModels;
        switch (iopt) {

        // Load a model from a file.
            case LOAD: {
                ASSERT_ARG_PRESENT(LOAD_FILE,"file");

            // Create new pointing model.
                tpk::PointingModel* model;
                try {
                    model = new tpk::PointingModel(Tcl_GetString(objv[LOAD_FILE]));
                } catch (std::runtime_error& error) {
                    Tcl_SetResult( interp, const_cast<char*>(error.what()),
                            TCL_VOLATILE );
                    return TCL_ERROR;
                }

            // Store in hash table.
                if ( ARG_PRESENT(LOAD_NAME) ) {
                    if ( ! LAST_ARG(LOAD_NAME) ) {
                        Tcl_WrongNumArgs( interp, LOAD_FILE, objv,
                            Tcl_GetString(objv[LOAD_NAME]) );
                        delete model;
                        return TCL_ERROR;
                    }
                    if ( models->NewObj( interp, model, objv[LOAD_NAME] ) == NULL ) {
                        delete model;
                        return TCL_ERROR;
                    }
                } else {
                    if ( models->NewObj( interp, model, 0 ) == NULL ) {
                        delete model;
                        return TCL_ERROR;
                    }
                }
                break;
            }
        // Create new model.
            case CREATE: {
                ASSERT_ARG_PRESENT(CREATE_MODEL,"model");

            // Check that model has an even number of arguments.
                Tcl_Obj** values;
                int c;
                if ( Tcl_ListObjGetElements( interp, objv[CREATE_MODEL], &c,
                        &values) != TCL_OK )return TCL_ERROR;
                if ( c%2 == 1 ) {
                    Tcl_SetResult(interp,
                        "list must have an even number of elements",
                        TCL_VOLATILE);
                    return TCL_ERROR;
                }

            // Create new pointing model.
                tpk::PointingModel* model = new tpk::PointingModel();

            // Set the pointing model terms.
                for ( int i = 0; i < c; i += 2) {
                    double v;
                    if ( Tcl_GetDoubleFromObj(interp, values[i+1], &v)
                            != TCL_OK) {
                        delete model;
                        return TCL_ERROR;
                            }
                    try {
                        model->addTerm(Tcl_GetString(values[i]), v * tpk::TcsLib::as2r);
                    }
                    catch (std::runtime_error& error) {
                        delete model;
                        Tcl_SetResult( interp, const_cast<char*>(error.what()),
                                TCL_VOLATILE );
                        return TCL_ERROR;
                    }
                }

            // Store in hash table.
                if ( ARG_PRESENT(CREATE_NAME) ) {
                    ASSERT_NO_MORE_ARGS(CREATE_NAME);
                    if ( models->NewObj( interp, model, objv[CREATE_NAME] ) == NULL ) {
                        delete model;
                        return TCL_ERROR;
                    }
                } else {
                    if ( models->NewObj( interp, model, 0 ) == NULL ) {
                        delete model;
                        return TCL_ERROR;
                    }
                }
                break;
            }

        // Delete pointing model
            case DELETE: {
                ASSERT_ARG_PRESENT(DELETE_NAME,"name");
                ASSERT_NO_MORE_ARGS(DELETE_NAME);
                TpkObj<tpk::PointingModel>::Tpk_Obj* modelObj =
                        models->GetObj( interp, objv[DELETE_NAME]);
                if ( modelObj == NULL ) return TCL_ERROR;
                return models->FreeObj( interp, modelObj );
                break;
            }

        // Set pointing model.
            case SET: {
                ASSERT_ARG_PRESENT(SET_MOUNT,"mount");
                ASSERT_ARG_PRESENT(SET_NAME,"name");
                ASSERT_NO_MORE_ARGS(SET_NAME);
                TpkObj<tpk::MountVt>::Tpk_Obj* mountObj =
                        static_cast<Pcs*>(clientdata)->mMounts->
                        GetObj(interp, objv[SET_MOUNT]);
                if ( mountObj == NULL ) return TCL_ERROR;
                TpkObj<tpk::PointingModel>::Tpk_Obj* modelObj =
                        models->GetObj( interp, objv[SET_NAME]);
                if ( modelObj == NULL ) return TCL_ERROR;
                mountObj->obj->newPointingModel(*modelObj->obj );
                break;
            }

        // Show model
            case SHOW: {
                ASSERT_ARG_PRESENT(SHOW_NAME,"model");
                ASSERT_NO_MORE_ARGS(SHOW_NAME);

            // Get model.
                TpkObj<tpk::PointingModel>::Tpk_Obj* modelObj =
                        models->GetObj( interp, objv[SHOW_NAME]);
                if ( modelObj == NULL ) return TCL_ERROR;

            // Get a list of the terms.
                Tcl_Obj* result = Tcl_NewListObj(0, NULL);
                std::vector<std::string> terms = modelObj->obj->listTerms();
                for (unsigned int i = 0; i < terms.size(); i++ ) {
                    Tcl_ListObjAppendElement(interp, result,
                            Tcl_NewStringObj(terms[i].c_str(),-1));
                    Tcl_ListObjAppendElement(interp, result,
                        Tcl_NewDoubleObj(modelObj->obj->getTerm(terms[i])/tpk::TcsLib::as2r));
                }
                Tcl_SetObjResult(interp, result);
                break;
            }
        }
        return TCL_OK;
    }
}

