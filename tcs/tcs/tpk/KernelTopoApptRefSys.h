/// \file KernelTopoApptRefSys.h
/// \brief Definition of the kernel topocentric apparent coordinate reference 
///        system class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkKERNELTOPOAPPTREFSYS_H
#define tpkKERNELTOPOAPPTREFSYS_H

#include "Coordinates.h"
#include "TopoApptRefSys.h"
#include "TcsLib.h"
#include "TcspkRefSys.h"

namespace tpk {

/// Topocentric Apparent Celestial Reference System
/**
    The implementations of all the tcspk interface methods are inherited from
    TcspkRefSys.
*/
    class KernelTopoApptRefSys : public TcspkRefSys {
        public:

        /// Default constructor
            KernelTopoApptRefSys() : TcspkRefSys(tcspk::APPT_TOPO) {}

        /// Constructor from a TopoApptRefSys
            KernelTopoApptRefSys(
                const TopoApptRefSys& refsys ///< topocentric apparent 
                                             ///  reference system
            ) : TcspkRefSys(tcspk::APPT_TOPO) {}

        /// Copy constructor
            KernelTopoApptRefSys* clone() const {
                return new KernelTopoApptRefSys(*this);
            }
     };
}
#endif

