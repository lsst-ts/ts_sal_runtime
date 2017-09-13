/// \file KernelFK5RefSys.cpp
/// \brief Implementation of the kernel FK5 coordinate reference system class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "KernelFK5RefSys.h"

#include <stdexcept>

namespace tpk {

/// Inverse pointing transformation
/**
    \returns sky vector
*/
    vector KernelFK5RefSys::ptrani(
        const vector& aim,         ///< aim vector
        const double& tdbj,        ///< TDB Julian epoch
        const double amprms[21],   ///< mean to apparent parameters
        const double ae2mt[3][3],  ///< mount orientation matrix
        const double& hm,          ///< height (metres)
        const double& tlat,        ///< true latitude (radians)
        const double& diurab,      ///< diurnal aberration (radians)
        const double& refa,        ///< refraction constant A
        const double& refb,        ///< refraction constant B
        const double& temp,        ///< temperature (deg K)
        const double& press,       ///< pressure (mBar)
        const double& humid,       ///< relative humidity
        const double& tlr,         ///< tropospheric lapse rate
        const double& wavel,       ///< wavelength (microns)
        const double& sst,         ///< sine of siderial time
        const double& cst          ///< cosine of siderial time
    ) const throw() {
        double pos[2];
        tcspk::tcsPtrani ( aim.x, aim.y, aim.z, tdbj, 
                const_cast<double*>(amprms), const_cast<double(*)[3]>(ae2mt), 
                hm, tlat, diurab, mFrame, mEquinox, refa, refb, 
                temp, press, humid, tlr, wavel, refsub, sst, cst, pos );
        return vector(pos[0], pos[1]);
    }

/// Update target transformation
    void KernelFK5RefSys::tartran(
        const double& ttj,         ///< TT Julian epoch
        const double amprms[21],   ///< mean to apparent parameters
        const double ae2mt[3][3],  ///< mount orientation matrix
        const double& hm,          ///< height (metres)
        const double& lat,         ///< true latitude (radians)
        const double& diurab,      ///< diurnal aberration
        const double& refac,       ///< refraction constant A
        const double& refbc,       ///< refraction constant B
        const double& temp,        ///< temperature (deg K)
        const double& press,       ///< pressure (mBar)
        const double& humid,       ///< relative humidity
        const double& tlr,         ///< troposheric lapse rate
        const double& wavel,       ///< wavelength (microns)
        const double& sst,         ///< sine of siderial time
        const double& cst,         ///< cosine of siderial time
        const vector& tar          ///< target vector
    ) throw(std::runtime_error) {
        if ( tcspk::tcsTartr_c( ttj, const_cast<double*>(amprms),
                const_cast<double(*)[3]>(ae2mt), hm, lat, diurab,
                refac, refbc, temp, press, humid, tlr, wavel, refsub,
                sst, cst, mFrame, mEquinox, tar.x, tar.y, tar.z,
                mSPM1, mSPM1_i, mSPM2, mSPM2_i) ) {
            throw( std::runtime_error("fatal error in tcsTartran"));
        }
    }
}

