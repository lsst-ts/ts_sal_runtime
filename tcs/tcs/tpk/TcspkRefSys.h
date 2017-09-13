/// \file TcspkRefSys.h
/// \brief Definition of the tcspk tracking coordinate reference system class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkTCSPKREFSYS_H
#define tpkTCSPKREFSYS_H

#include <stdexcept>

#include "KernelRefSys.h"
#include "TcsLib.h"

namespace tpk {
    class Site;
    class Target;

/// Virtual base class for tcspk coordinate reference systems
/**
    The TcspkRefSys class is a virtual base class for all the coordinate
    reference system classes that are supported by TCSpk and can be used
    as the tracking frame for a virtual telescope.

    It provides a implementations for all the methods that are identical
    for all tcspk reference systems.

    It stores the TCSpk frame type and a set of sky patch matrices.
*/
    class TcspkRefSys : public KernelRefSys {
        public:

    /// Get frame type
    /**
        \returns The TCKpk frame type
    */
            virtual TcsLib::frametype frame() const throw() {
                return mFrame;
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
                const bool& slit,
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

    /// Constructor
    /**
        The constructor is protected so that only derived classes can call it.
    */
            TcspkRefSys(
                TcsLib::frametype frame ///< TCSpk frame type.
            ) : mFrame(frame) {}
            const TcsLib::frametype mFrame;   ///< TCSpk frame type
            double mSPM1[3][3];               ///< SPM 1
            double mSPM1_i[3][3];             ///< inverse SPM 1
            double mSPM2[3][3];               ///< SPM 2
            double mSPM2_i[3][3];             ///< inverse SPM 2
    };
}
#endif

