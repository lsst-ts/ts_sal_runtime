/// \file KernelApptRefSys.h
/// \brief Definition of the kernel geocentric apparent coordinate reference 
///        system class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkKERNELAPPTREFSYS_H
#define tpkKERNELAPPTREFSYS_H

#include "Coordinates.h"
#include "ApptRefSys.h"
#include "TcsLib.h"
#include "TcspkRefSys.h"

namespace tpk {

/// Geocentric Apparent Reference System
/**
    The implementations of all the tcspk interface methods are inherited from
    TcspkRefSys.
*/
    class KernelApptRefSys : public TcspkRefSys {
        public:

        /// Default constructor
            KernelApptRefSys() : TcspkRefSys(tcspk::APPT) {}

        /// Constructor from an ApptRefSys
            KernelApptRefSys(
                const ApptRefSys& refsys ///< geocentric apparent reference 
                                         //   system
            ) : TcspkRefSys(tcspk::APPT){}

        /// Copy constructor
            KernelApptRefSys* clone() const {
                return new KernelApptRefSys(*this);
            }
    };
}
#endif

