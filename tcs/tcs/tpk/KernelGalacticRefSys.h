/// \file KernelGalacticRefSys.h
/// \brief Definition of the kernel galactic reference system class.

// D L Terrett
// Copyright CCLRC. All rights reserved

#ifndef tpkKERNELGALACTICREFSYS_H
#define tpkKERNELGALACTICREFSYS_H

#include <stdexcept>

#include "GalacticRefSys.h"
#include "KernelICRefSys.h"
#include "KernelRefSys.h"
#include "RefSys.h"
namespace tpk {

/// IAU 1958 Galactic coordinate reference system
/**
    Galactic coordinates are not supported by TCSpk so an ICRefSys object
    is created by the constructor and each method uses slalib to convert
    the galactic coordinates to and from ICRS before and after calling
    the equavalent method of the ICRefSys object.
*/
    class KernelGalacticRefSys : public KernelRefSys {
        public:

        /// Constructor from a galactic reference system
            KernelGalacticRefSys(
                const GalacticRefSys& refsys   ///< galactic reference system
            ) {}

        /// Copy constructor
            KernelGalacticRefSys* clone() const {
                return new KernelGalacticRefSys(*this);
            }

            virtual vector aim2sky(
                const vector& aim,
                const double& sst,
                const double& cst
            ) const throw();

            virtual vector ptrani(
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

            virtual void tartran(
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
        protected:
            KernelICRefSys mKernelICRefSys;  ///< International celestial
                                             ///  reference system
            const ICRefSys mICRefSys;
            const GalacticRefSys mGalacticRefSys;
    };
}
#endif

