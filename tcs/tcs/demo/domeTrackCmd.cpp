#include <stdlib.h>
#include <slalib.h>
#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"
#include "Util.h"
#include "tpkobj.h"
#include "DemoPcs.h"
#include "SAL_dome.h"
using namespace DDS;
using namespace dome;

namespace dpk {

/// Handler procedure for the tpk::domeTrackCmd command

//    extern "C" 
    int domeTrackCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) 
    {
        Pcs* pcs = static_cast<Pcs*>(clientdata);
     
    double azimuth,elevation;
    int status=0;
    dome_command_MoveC newPosition;

    // Command argument positions
    enum {AZIMUTH=1 , ELEVATION=2 };
    ASSERT_ARG_PRESENT(AZIMUTH,"azimuth");
    ASSERT_ARG_PRESENT(ELEVATION,"elevation");
    ASSERT_NO_MORE_ARGS(ELEVATION);
    if ( Tcl_GetDoubleFromObj( interp, objv[AZIMUTH], &azimuth) != TCL_OK ) {
        return TCL_ERROR;
    }
    if ( Tcl_GetDoubleFromObj( interp, objv[ELEVATION], &elevation) != TCL_OK ) {
        return TCL_ERROR;
    }

    newPosition.device = DDS::string_dup("target");
    newPosition.property = DDS::string_dup("position");
    newPosition.action = DDS::string_dup("track");
    newPosition.azimuth = azimuth;
    newPosition.elevation = elevation;
    int salcmd = static_cast<Pcs*>(clientdata)->salDOME->issueCommand_Move(&newPosition);

    return TCL_OK;
   }
}


