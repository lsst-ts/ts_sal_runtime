/// \file Util.h
/// \brief Defines utility methods

// D L Terrett
// Copyright STFC. All rights reserved.

#ifndef dpkUTIL_H
#define dpkUTIL_H

#include <string>
#include "tcl.h"
#include "tpk.h"

namespace dpk {

    /// Utilities functions
    class Util {
        public:
            static std::string formatRaDec( double a, double b);
            static std::string formatAzEl( double a, double b);
            static std::string formatMJD( double t);
            static std::string formatTOD( double tod);
            static tpk::RefSys* refsysFromObj(Tcl_Interp* interp, 
                    Tcl_Obj* frame);
    };
}
#endif

