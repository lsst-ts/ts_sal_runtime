/// \file commands.h
/// \brief Prototypes for Tcl command handling procedures

// D L Terrett
// Copyright STFC. All rights reserved.

#ifndef dpkCOMMANDS_H
#define dpkCOMMANDS_H

#include <tcl.h>

// Macros for testing for the presence of command arguments.
#define ARG_PRESENT(ARGN) ( objc > ARGN )
#define ARG_NOT_PRESENT(ARGN) ( objc <= ARGN )
#define MORE_ARGS(ARGN) ( objc > ARGN + 1 )
#define LAST_ARG(ARGN) ( objc == ARGN + 1 )

#define ASSERT_ARG_PRESENT(ARGN,NAME) \
    if (ARG_NOT_PRESENT(ARGN)) { \
        Tcl_WrongNumArgs( interp, ARGN, objv, NAME ); \
        return TCL_ERROR; \
    }

#define ASSERT_NO_MORE_ARGS(ARGN) \
    if (MORE_ARGS(ARGN)) { \
        Tcl_WrongNumArgs( interp, ARGN, objv, Tcl_GetString(objv[ARGN]) ); \
        return TCL_ERROR; \
    }

#define ASSERT_NO_ARGS(NAME) \
    if (objc != 1) { \
        Tcl_WrongNumArgs( interp, 0, objv, NAME ); \
        return TCL_ERROR; \
    }

namespace dpk {
    class Pcs;
    int createCommands( Tcl_Interp* interp, Pcs* pcs);

    extern "C" {
        int AxisCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int EphempathCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int FastCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int GuideCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int IpaCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int LimitTimeCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int MediumCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int OffsetCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int OpticsCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int OriginCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int PointingCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int PointingModelCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int SkySampleCmd( ClientData clientdata, Tcl_Interp* interp,
                int objc, Tcl_Obj *CONST objv[]);
        int SlowCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int StatsCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int TargetCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int TelInfoCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int WavelengthCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
        int WrapCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
                Tcl_Obj *CONST objv[]);
//        int cameraHexapodMoveCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
//                Tcl_Obj *CONST objv[]);
//        int m2HexapodMoveCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
//                Tcl_Obj *CONST objv[]);
//        int domeTrackCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
//                Tcl_Obj *CONST objv[]);
//        int domeCrawlCmd( ClientData clientdata, Tcl_Interp* interp, int objc,
//                Tcl_Obj *CONST objv[]);
    }
}
#endif

