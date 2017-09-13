#include <stdlib.h>
#include <slalib.h>
#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"
#include "Util.h"
#include "tpkobj.h"
#include "SAL_dome.h"
using namespace DDS;
using namespace dome;

namespace dpk {

/// Handler procedure for the tpk::domeTrack command

//    extern "C" 
    int domeTrackCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {
        Pcs* pcs = static_cast<Pcs*>(clientdata);
     
    double az_vel,el_vel;
    int status=0;
    dome_command_CrawlC newPosition;

    // Command argument positions
    enum {AZIMUTH=1 , ELEVATION=2 };
    ASSERT_ARG_PRESENT(AZIMUTH,"azimuth-velocity");
    ASSERT_ARG_PRESENT(ELEVATION,"elevation-velocity");
    ASSERT_NO_MORE_ARGS(ELEVATION);
    if ( Tcl_GetDoubleFromObj( interp, objv[AZIMUTH], &az_vel) != TCL_OK ) {
        return TCL_ERROR;
    }
    if ( Tcl_GetDoubleFromObj( interp, objv[ELEVATION], &el_vel) != TCL_OK ) {
        return TCL_ERROR;
    }

    newPosition.device = DDS::string_dup("crawl");
    newPosition.property = DDS::string_dup("velocity");
    newPosition.action = DDS::string_dup("set");
    newPosition.azVelocity = az_vel;
    newPosition.elVelocity = el_vel;
    int salcmd = static_cast<Pcs*>(clientdata)->salDOME->issueCommand_Crawl(&newPosition);

    return TCL_OK;
  }
}


