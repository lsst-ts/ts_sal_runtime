/// \file KernelICRefSys.h
/// \brief Definitions of the kernel international coordinate reference system 
///        class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkKERNELICREFSYS_H
#define tpkKERNELICREFSYS_H

#include "Coordinates.h"
#include "ICRefSys.h"
#include "TcsLib.h"
#include "TcspkRefSys.h"

namespace tpk {

/// International Celestial Reference System
/**
    This system is not yet supported by the TCSpk and is approximated by
    FK5/2000.0.

    The implementations of all the tcspk interface methods are inherited from
    TcspkRefSys.
*/
    class KernelICRefSys : public TcspkRefSys {
        public:

        /// Default constructor
            KernelICRefSys() : TcspkRefSys(tcspk::FK5) {}

        /// Constructor from an ICRefSys
            KernelICRefSys(
                const ICRefSys& refsys ///< International celestial reference i
                                       //   system
            ) : TcspkRefSys(tcspk::FK5) {}

        /// Copy constructor
            KernelICRefSys* clone() const {
                return new KernelICRefSys(*this);
            }
    };
}
#endif

