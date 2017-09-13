/// \file KernelAzElRefSys.cpp
/// \brief Implementation of the kernel az,el coordinate reference system class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "KernelAzElRefSys.h"

#include <stdexcept>

namespace tpk {

/// Aim vector to sky vector
/**
    \returns sky vector
*/
    vector KernelAzElRefSys::aim2sky(
        const vector& aim,         ///< aim vector
        const double& sst,         ///< sine of siderial time
        const double& cst          ///< cosine of siderial time
    ) const throw() {
        double x, y, z;
        tcspk::tcsAim2s_c( aim.x, aim.y, aim.z, 
                const_cast<double(*)[3]>(mSPM1_i), mFrame, sst, cst, 
                const_cast<double(*)[3]>(mSPM2_i), &x, &y, &z);
        return vector(-x, y, z);
    }

/// Inverse pointing transformation
/**
    \returns sky vector
*/
    vector KernelAzElRefSys::ptrani(
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
                hm, tlat, diurab, mFrame, 0.0, refa, refb, temp, press, humid, 
                tlr, wavel, refsub, sst, cst, pos );
        return vector(pos[0], pos[1]);
    }

/// Predict rotator demand
/**
        \returns status (0 => success)
*/
    int KernelAzElRefSys::rotator(
        const vector& aim,         ///< aim vector
        const TcsLib::rotloc& rotl,///< rotator location
        const double& rdp,         ///< predicted demand (radians)
        const bool& bp,            ///< beyond pole flag
        const double& ad,          ///< demand roll (radians)
        const double& bd,          ///< demand pitch (radians)
        const focalplane& xy,      ///< pointing origin
        const double& ia,          ///< roll index error (radians)
        const double& ib,          ///< pitch index error (radians)
        const double& np,          ///< axis non-perpendicularity (radians)
        const vector& tel,         ///< telescope vector
        const double& ga,          ///< roll guiding adjustment (radians)
        const double& gb,          ///< Pitch guiding adjustment (radians)
        const double& sia,         ///< sine of instrument alignment angle
        const double& cia,         ///< cosine of instrument alignment angle
        const double& sst,         ///< sine of siderial time
        const double& cst,         ///< cosine of siderial time
        const double& pai,         ///< instrument position angle (radians)
        const bool& slit,          ///< slit optimize
        double& rma                ///< rotator demand (radians)
    ) const throw () {
        int k;
        tcspk::tcsRotator( aim.x, aim.y, aim.z, rotl, rdp, bp ? 1 : 0, ad, bd,
                xy.x, xy.y, ia, ib, np, tel.x, tel.y, tel.z, ga, gb, sia, cia,
                const_cast<double(*)[3]>(mSPM1_i), mFrame, sst, cst,
                const_cast<double(*)[3]>(mSPM2_i), pai, slit ? 0 : 1, &rma, &k);
        return k;
    }

/// Sky vector to aim vector
/**
    \returns aim vector
*/
    vector KernelAzElRefSys::sky2aim(
        const vector& sky,         ///< sky vector
        const double& sst,         ///< sine of siderial time
        const double& cst          ///< cosine of siderial time
    ) const throw() {
        vector aim;
        tcspk::tcsSky2a_c( -sky.x,sky.y, sky.z, const_cast<double(*)[3]>(mSPM1),
                mFrame, sst, cst, const_cast<double(*)[3]>(mSPM2), 
                &aim.x, &aim.y, &aim.z);
        return aim;
    }

/// Update target transformation
    void KernelAzElRefSys::tartran(
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
                sst, cst, mFrame, 0.0, -tar.x, tar.y, tar.z,
                mSPM1, mSPM1_i, mSPM2, mSPM2_i ) ) {
            throw( std::runtime_error("fatal error in tcsTartran"));
        }
    }

/// target vector to mount roll and pitch
/**
    \returns status (0 => success)
*/
    int KernelAzElRefSys::track(
        const vector& tar,            ///< target coordinates
        const double& sst,            ///< sine of sidereal time
        const double& cst,            ///< cosine of sidereal time
        const TcsLib::rotloc& rotl,   ///< rotator location
        const double& rma,            ///< predicted rotator mechanical angle 
                                      ///  (radians)
        const double& roll,           ///< predicted roll (radians)
        const double& pitch,          ///< predicted pitch (radians)
        const double& xr,             ///< pointing origin x (in focal lengths)
        const double& yr,             ///< pointing origin y (in focal lengths)
        const double& ia,             ///< roll zero point (radians)
        const double& ib,             ///< pitch zero point (radians)
        const double& np,             ///< mount axes nonperp (radians)
        const vector& tel,            ///< telescope vector
        const double& ga,             ///< guiding correction, roll (radians)
        const double& gb,             ///< guiding correction, pitch (radians)
        const double& rnogo,          ///< radius of "no go" region (radians)
        vector& aim,                  ///< aim vector
        double& ad1,                  ///< roll coordinate, first solution 
                                      ///  (radians)
        double& bd1,                  ///< pitch coordinate, first solution 
                                      ///  (radians)
        double& ad2,                  ///< roll coordinate, second solution 
                                      ///  (radians)
        double& bd2                   ///< pitch coordinate, second solution 
                                      ///  (radians)
    ) const throw () {
        int j;
        tcspk::tcsTrack_c( -tar.x,tar.y, tar.z, const_cast<double(*)[3]>(mSPM1),
                mFrame, sst, cst, const_cast<double(*)[3]>(mSPM2), rotl, rma, 
                roll, pitch, xr, yr, ia, ib, np, tel.x, tel.y, tel.z, ga, gb, 
                rnogo, &aim.x, &aim.y, &aim.z, &ad1, &bd1, &ad2, &bd2, &j );
        return j;
    }

/// Focal plane x,y to sky coordinates
/**
    \returns sky vector
*/
    vector KernelAzElRefSys::vtsky(
        const double& roll,           ///< roll (radians)
        const double& pitch,          ///< pitch (radians)
        const TcsLib::rotloc& rotl,   ///< rotator location
        const double& rma,            ///< rotator mechanical angle (radians)
        const focalplane& xy,         ///< x,y position
        const double& sst,            ///< sine of sidereal time
        const double& cst,            ///< cosine of sidereal time
        const double& ia,             ///< roll zero point (radians)
        const double& ib,             ///< pitch zero point (radians)
        const double& np,             ///< mount axes nonperp (radians)
        const vector& tel,            ///< telescope vector
        const double& ga,             ///< guiding correction, roll (radians)
        const double& gb              ///< guiding correction, pitch (radians)
    ) const throw () {
        double x, y, z;
        tcspk::tcsVTsky_c( roll, pitch, rotl, rma, xy.x, xy.y,
                const_cast<double(*)[3]>(mSPM1_i), mFrame, sst, cst,
                const_cast<double(*)[3]>(mSPM2_i), ia, ib, np,
                tel.x, tel.y, tel.z, ga, gb, &x, &y, &z);
        return vector(-x, y, z);
    }

/// Sky coordinates to non rotating focal plane x,y
    int KernelAzElRefSys::vtxe(
        const vector& tar,        ///< target coordinates
        const double& sst,        ///< sine of sidereal time
        const double& cst,        ///< cosine of sidereal time
        const double& roll,       ///< roll (radians)
        const double& pitch,      ///< pitch (radians)
        const double& ia,         ///< roll zero point (radians)
        const double& ib,         ///< pitch zero point (radians)
        const double& np,         ///< mount axes nonperpendicularity (radians)
        const vector& tel,        ///< telescope vector
        const double& ga,         ///< guiding correction, roll (radians)
        const double& gb,         ///< guiding correction, pitch (radians)
        focalplane& xieta         ///< image position
    ) const throw () {
        int j;
        tcspk::tcsVTxe_c(-tar.x, tar.y, tar.z, const_cast<double(*)[3]>(mSPM1),
                mFrame, sst, cst, const_cast<double(*)[3]>(mSPM2), roll, pitch, 
                ia, ib, np, tel.x, tel.y, tel.z, ga, gb, &xieta.xi, &xieta.eta,
                &j);
        return j;
    }

/// Sky coordinates to rotating focal plane x,y
    int KernelAzElRefSys::vtxy(
        const vector& tar,            ///< target coordinates
        const double& sst,            ///< sine of sidereal time
        const double& cst,            ///< cosine of sidereal time
        const TcsLib::rotloc& rotl,   ///< rotator location
        const double& rma,            ///< rotator mechanical angle (radians)
        const double& roll,           ///< roll (radians)
        const double& pitch,          ///< pitch (radians)
        const double& ia,             ///< roll zero point (radians)
        const double& ib,             ///< pitch zero point (radians)
        const double& np,             ///< mount axes nonperpendicularity 
                                      ///  (radians)
        const vector& tel,            ///< telescope vector
        const double& ga,             ///< guiding correction, roll (radians)
        const double& gb,             ///< guiding correction, pitch (radians)
        focalplane& xy                ///< x,y position
    ) const throw () {
        int j;
        tcspk::tcsVTxy_c( -tar.x, tar.y, tar.z, const_cast<double(*)[3]>(mSPM1),
                mFrame, sst, cst, const_cast<double(*)[3]>(mSPM2), rotl, rma,
                roll, pitch, ia, ib, np, tel.x, tel.y, tel.z,  ga, gb, 
                &xy.x, &xy.y, &j);
        return j;
    }
}

