/// \file Util.cpp
/// \brief implements utility procedures

// D L Terrett
// Copyright STFC. All rights reserved.

#include <string>
#include <tcl.h>
#include "Util.h"
#include "tpk.h"
#include "slalib.h"

namespace dpk {


/// Format RA, Dec.
/**
    \returns formated string suitable for display
*/
    std::string Util::formatRaDec(
        double a,            ///< right ascension (radians)
        double b             ///< declination (radians)
    ) {
        int hmsf[4], dmsf[4];
        char sign, str[28];
        slaDr2tf( 4, a, &sign, hmsf);
        slaDr2af( 3, b, &sign, dmsf);
        sprintf(str, "%02d %02d %02d.%04d %c%02d %02d %02d.%03d", hmsf[0],
                hmsf[1], hmsf[2], hmsf[3], sign, dmsf[0], dmsf[1], dmsf[2],
                dmsf[3] );
        return std::string(str);
    }

/// Format Az, El.
/**
    \returns formated string suitable for display
*/
    std::string Util::formatAzEl(
        double a,            ///< azimuth (radians)
        double b             ///< elevation (radians)
    ) {
        char str[26];
        sprintf(str, "%12.8f %12.8f", a / tpk::TcsLib::d2r,
                b / tpk::TcsLib::d2r );
        return std::string(str);
    }

/// Format an MJD as a calender date and time.
/**
    \returns formated string suitable for display.
*/
    std::string Util::formatMJD(
        double t            ///< Time (MJD)
    ) {
   // Format tai.
      int y, m, d, j; double f;
      slaDjcl( t, &y, &m, &d, &f, &j );
      int hmsf[4]; char sign;
      slaDd2tf( 1, f, &sign, hmsf );
      char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                     "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
      char tai_string[24];
      sprintf( tai_string, "%04d %s %02d %02d:%02d:%02d.%01d", y, months[m-1],
            d, hmsf[0], hmsf[1], hmsf[2], hmsf[3] );
      return std::string(tai_string);
    }

/// Format a time of day.
/**
    \returns formatted string suitable for display.
*/
    std::string Util::formatTOD(
        double tod            ///< Time of day (fraction)
    ) {
      int hmsf[4]; char sign;
      slaDr2tf( 1, tod, &sign, hmsf );
      char tod_string[11];
      sprintf( tod_string, "%02d:%02d:%02d.%01d", hmsf[0], hmsf[1], hmsf[2], 
            hmsf[3] );
      return std::string(tod_string);
    }

/// Gets a refsys object from a TclObj
/**
    * \returns tpk refsys object
*/
    tpk::RefSys* Util::refsysFromObj(
        Tcl_Interp* interp,		///< Tcl interpreter
        Tcl_Obj* refsys			///< TclObj
        ) {

    // Coordinate frames.
        static const char* frames[] = {"ICRS", "icrs", "FK5", "fk5", 
            "APPT", "appt", "APPT_TOPO", "topo_appt",
            "AZEL", "azel", "GALACTIC", "galactic", 0};

    /// Frame types
        enum {
            FRAME_ICRS, FRAME_icrs, FRAME_FK5, FRAME_fk5, FRAME_APPT, FRAME_appt, 
            FRAME_TOPO_APPT, FRAME_topo_appt, FRAME_AZEL, FRAME_azel,
            FRAME_GALACTIC, FRAME_galactic
        };

    // Reference system specification is a list.
        int objc;
        Tcl_Obj** objv;
        if ( Tcl_ListObjGetElements( interp, refsys, &objc, &objv) != TCL_OK )
            return 0;

    // The first element should be the frame type.
        if ( objc < 1 ) {
            Tcl_SetResult( interp, "Frame type is empty", TCL_VOLATILE);
            return 0;
        }
        int iframe;
        if ( Tcl_GetIndexFromObj( interp, objv[0], frames,
                "frame type", 0, &iframe)!= TCL_OK ) return 0;

        tpk::RefSys* sys;
        switch (iframe) {
            case FRAME_ICRS:
            case FRAME_icrs:
                sys = new tpk::ICRefSys;
                break;
            case FRAME_FK5:
            case FRAME_fk5:

            // An FK5 frame may have an equinox as the second element of
            // the list.
                if ( objc >= 2 ) {
                    double equinox;
                    if (Tcl_GetDoubleFromObj(interp, objv[1], &equinox) != TCL_OK )
                            return 0;
                    sys = new tpk::FK5RefSys(equinox);
                } else {
                    sys = new tpk::FK5RefSys;
                }
                break;
            case FRAME_APPT:
            case FRAME_appt:
                sys = new tpk::ApptRefSys;
                break;
            case FRAME_TOPO_APPT:
            case FRAME_topo_appt:
                sys = new tpk::TopoApptRefSys;
                break;
            case FRAME_AZEL:
            case FRAME_azel:
                sys = new tpk::AzElRefSys;
                break;
            case FRAME_GALACTIC:
            case FRAME_galactic:
                sys = new tpk::GalacticRefSys;
                break;
        }
        return sys;
    }
}

