/// \file wavelengthCmd.cpp
/// \brief Implementation of the Tcl wavelength command handling procedure

// D L Terrett
// Copyright STFC. All rights reserved.

#include <slalib.h>
#include <tcl.h>
#include "tpk.h"
#include "commands.h"
#include "Pcs.h"
#include "tpkobj.h"

namespace dpk {


/// Handler procedure for the tpk::wavelength command.
/**
    The wavelength command sets the effective wavelength of a virtual telescope
    and takes the form:
        - wavelength \<telescope> \<microns\>
*/
    extern "C" int WavelengthCmd( ClientData clientdata, Tcl_Interp *interp,
            int objc, Tcl_Obj *CONST objv[]) {

    // Command argument positions
        enum { TELESCOPE = 1, WAVELENGTH = 2 };
    
    // Get the name of the telescope.
        ASSERT_ARG_PRESENT(TELESCOPE,"telescope wavelength");
        TpkObj<tpk::BaseVt>::Tpk_Obj* telObj =
                static_cast<Pcs*>(clientdata)->mTelescopes->
                GetObj(interp, objv[TELESCOPE]);
        if ( telObj == NULL ) return TCL_ERROR;

    // Get wavelength
        ASSERT_ARG_PRESENT(WAVELENGTH,"wavelength");
        ASSERT_NO_MORE_ARGS(WAVELENGTH);
        double wavel;
        if ( Tcl_GetDoubleFromObj( interp, objv[WAVELENGTH], &wavel ) != TCL_OK )
                return TCL_ERROR;

    // Set effective wavelength of virtual telescope
        telObj->obj->setWavelength( wavel );
        return TCL_OK;
    }
}

