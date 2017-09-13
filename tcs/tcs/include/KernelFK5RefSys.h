/// \file KernelFK5RefSys.h
/// \brief Definitions of the kernel FK5 coordinate reference system class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkKERNELFK5REFSYS_H
#define tpkKERNELFK5REFSYS_H

#include <stdexcept>

#include "Coordinates.h"
#include "FK5RefSys.h"
#include "TcsLib.h"
#include "TcspkRefSys.h"

namespace tpk {

/// International Celestial Reference System
/**
    The implementation of all the tcspk interface method are inherited from
    TcspkRefSys.
*/
    class KernelFK5RefSys : public TcspkRefSys {
        public:
        
        /// Contructor from an FK5 reference system.
            KernelFK5RefSys(const FK5RefSys& refsys) :
                    TcspkRefSys(tcspk::FK5), mEquinox(refsys.equinox()) {}
            KernelFK5RefSys* clone() const {
                return new KernelFK5RefSys(*this);
            }
            vector ptrani(
                const vector& aim,
                const double& tdbj,
                const double amprms[21],
                const double ae2mt[3][3],
                const double& hm,
                const double& tlat,
                const double& diurab,
                const double& refa,
                const double& refb,
                const double& temp,
                const double& press,
                const double& humid,
                const double& tlr,
                const double& wavel,
                const double& sst,
                const double& cst
            ) const throw();
            void tartran(
                const double& ttj,
                const double amprms[21],
                const double ae2mt[3][3],
                const double& hm,
                const double& lat,
                const double& diurab,
                const double& refac,
                const double& refbc,
                const double& temp,
                const double& press,
                const double& humid,
                const double& tlr,
                const double& wavel,
                const double& sst,
                const double& cst,
                const vector& tar
            ) throw(std::runtime_error);
        protected:
            double mEquinox;     ///< equinox of frame (Julian year)
    };
}
#endif

