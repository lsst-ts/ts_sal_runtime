#include <stdlib.h>
#include <slalib.h>
#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"
#include "Util.h"
#include "tpkobj.h"
#include "SAL_hexapod.h"
#define CAMERA_HEXAPOD 1
#define M2_HEXAPOD     2
using namespace DDS;
using namespace hexapod;
extern int hexapodCalculator ( int deviceId, double elevation, 
                        hexapod_command_moveC *newPosition );

namespace dpk {

/// Handler procedure for the tpk::m2HexapodMoveCmd command

//    extern "C" 
    int m2HexapodMoveCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {
        Pcs* pcs = static_cast<Pcs*>(clientdata);
     
    double elevation, w,x,y,z,aa,ab;
    int status=0;
    hexapod_command_moveC newPosition;

    // Command argument positions
    enum {ELEVATION = 1 };
    ASSERT_ARG_PRESENT(ELEVATION,"elevation");
    ASSERT_NO_MORE_ARGS(ELEVATION);
    if ( Tcl_GetDoubleFromObj( interp, objv[ELEVATION], &elevation) != TCL_OK ) {
        return TCL_ERROR;
    }

    status = hexapodCalculator(M2_HEXAPOD,elevation,&newPosition);    
    newPosition.device = DDS::string_dup("target");
    newPosition.property = DDS::string_dup("position");
    newPosition.action = DDS::string_dup("set");
    newPosition.sync=true;
    int salcmd = static_cast<Pcs*>(clientdata)->salM2HEX->issueCommand_move(&newPosition);

    return TCL_OK;
  }
}


