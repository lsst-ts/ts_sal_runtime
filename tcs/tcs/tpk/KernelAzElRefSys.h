/// \file KernelAzElRefSys.h
/// \brief Definition of the kernel az,el coordinate reference system class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkKERNELAZELREFSYS_H
#define tpkKERNELAZELREFSYS_H

#include "Coordinates.h"
#include "AzElRefSys.h"
#include "TcsLib.h"
#include "TcspkRefSys.h"

namespace tpk {

/// Az,El Reference System
    class KernelAzElRefSys : public TcspkRefSys {
        public:

        /// Default constructor
            KernelAzElRefSys() : TcspkRefSys(tcspk::AZEL_TOPO) {}

        /// Constructor from an ApptRefSys
            KernelAzElRefSys(
                const AzElRefSys& refsys          ///< Az,el reference system
            ) : TcspkRefSys(tcspk::AZEL_TOPO) {}

        /// Copy constructor
            KernelAzElRefSys* clone() const {
                return new KernelAzElRefSys(*this);
            }

            virtual vector aim2sky(
                const vector& aim,
                const double& sst,
                const double& cst
            ) const throw();

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


            virtual int rotator(
                const vector& aim,
                const TcsLib::rotloc& rotl,
                const double& rdp,
                const bool& bp,
                const double& ad,
                const double& bd,
                const focalplane& xy,
                const double& ia,
                const double& ib,
                const double& np,
                const vector& tel,
                const double& ga,
                const double& gb,
                const double& sia,
                const double& cia,
                const double& sst,
                const double& cst,
                const double& pai,
                const bool& fo,
                double& rma
            ) const throw ();

            virtual vector sky2aim(
                const vector& sky,
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

            virtual int track(
                const vector& tar,
                const double& sst,
                const double& cst,
                const TcsLib::rotloc& rotl,
                const double& rma,
                const double& roll,
                const double& pitch,
                const double& xr,
                const double& yr,
                const double& ia,
                const double& ib,
                const double& np,
                const vector& tel,
                const double& ga,
                const double& gb,
                const double& rnogo,
                vector& aim,
                double& ad1,
                double& bd1,
                double& ad2,
                double& bd2
            ) const throw ();

            virtual vector vtsky(
                const double& roll,
                const double& pitch,
                const TcsLib::rotloc& rotl,
                const double& rma,
                const focalplane& xy,
                const double& sst,
                const double& cst,
                const double& ia,
                const double& ib,
                const double& np,
                const vector& tel,
                const double& ga,
                const double& gb
            ) const throw ();

            virtual int vtxe(
                const vector& tar,
                const double& sst,
                const double& cst,
                const double& roll,
                const double& pitch,
                const double& ia,
                const double& ib,
                const double& np,
                const vector& tel,
                const double& ga,
                const double& gb,
                focalplane& xieta
            ) const throw ();

            virtual int vtxy(
                const vector& tar,
                const double& sst,
                const double& cst,
                const TcsLib::rotloc& rotl,
                const double& rma,
                const double& roll,
                const double& pitch,
                const double& ia,
                const double& ib,
                const double& np,
                const vector& tel,
                const double& ga,
                const double& gb,
                focalplane& xy
            ) const throw ();
    };
}
#endif

