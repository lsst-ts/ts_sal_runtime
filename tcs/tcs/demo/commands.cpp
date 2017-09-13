/// \file commands.cpp
/// \brief Implementation of createCommands

// D L Terrett
// Copyright STFC. All rights reserved.

#include <tcl.h>
#include "commands.h"
#include "Pcs.h"

namespace dpk {

/// Creates all the Tcl commands installed by the tpk extension.
    int createCommands( 
        Tcl_Interp* interp,         ///< Tcl interpreter
        Pcs* pcs                    ///< Pointing kernel
    ) {
        Tcl_CreateObjCommand( interp, "tpk::axis", AxisCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::ephempath", EphempathCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::fast", FastCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::guide", GuideCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::ipa", IpaCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::limittime", LimitTimeCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::medium", MediumCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::offset", OffsetCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::optics", OpticsCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::origin", OriginCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::pointing", PointingCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::pointingmodel", PointingModelCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::skysample", SkySampleCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::slow", SlowCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::stats", StatsCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::target", TargetCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::telinfo", TelInfoCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::wavelength", WavelengthCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
        Tcl_CreateObjCommand( interp, "tpk::wrap", WrapCmd,
                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
//        Tcl_CreateObjCommand( interp, "tpk::cameraHexapodMove", cameraHexapodMoveCmd,
//                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
//        Tcl_CreateObjCommand( interp, "tpk::m2HexapodMove", m2HexapodMoveCmd,
//                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
//        Tcl_CreateObjCommand( interp, "tpk::domeTrack", domeTrackCmd,
//                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );
//        Tcl_CreateObjCommand( interp, "tpk::domeCrawl", domeCrawlCmd,
//                (ClientData)pcs, (Tcl_CmdDeleteProc*)NULL );

        return TCL_OK;
    }
}

