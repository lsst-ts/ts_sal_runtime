/// \file KernelGalacticRefSys.cpp
/// \brief Implementation of the kernel galactic reference system class.

#include "KernelGalacticRefSys.h"

#include "slalib.h"

namespace tpk {

/// Aim vector to sky vector
/**
    \returns sky vector
*/
    vector KernelGalacticRefSys::aim2sky(
        const vector& aim,         ///< aim vector
        const double& sst,         ///< sine of siderial time
        const double& cst          ///< cosine of siderial time
    ) const throw() {

    // Aim to ICRS
        spherical icrs = mKernelICRefSys.aim2sky(aim, sst, cst);

    // ICRS to Galactic
        return mGalacticRefSys.fromICRS(icrs);
    }

/// Inverse pointing transformation
/**
    \returns sky vector
*/
    vector KernelGalacticRefSys::ptrani(
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

    // Aim to ICRS
        spherical icrs = mKernelICRefSys.ptrani(aim, tdbj, amprms, ae2mt, 
                hm, tlat, diurab, refa, refb, temp, press, humid, tlr, wavel, 
                sst, cst);

    // ICRS to Galactic
        return mGalacticRefSys.fromICRS(icrs);
    }

/// Predict rotator demand
/**
        \returns status
        \retval 0 success
*/
    int KernelGalacticRefSys::rotator(
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

    // Aim to galactic.
        spherical g0 = aim2sky(aim, sst, cst);

    // galactic position to ICRS.
        spherical icrs0(mICRefSys.fromGalactic(g0));

    // trial point displaced towards the galactic pole to ICRS.
        spherical g1(spherical(g0.a, g0.b + 0.0001));
        spherical icrs1(mICRefSys.fromGalactic(g1));

    // Add the bearing of the trial point in ICRS to the position angle
    // of the instrument.
        return mKernelICRefSys.rotator(aim, rotl, rdp, bp, ad, bd, xy,
                ia, ib, np, tel, ga, gb, sia, cia, sst, cst, 
                pai + slaDbear(icrs0.a, icrs0.b, icrs1.a, icrs1.b), 
                slit, rma);
    }

/// Sky vector to aim vector
/**
    \returns aim vector
*/
    vector KernelGalacticRefSys::sky2aim(
        const vector& sky,         ///< sky vector
        const double& sst,         ///< sine of siderial time
        const double& cst          ///< cosine of siderial time
    ) const throw() {
        return mKernelICRefSys.sky2aim(mICRefSys.fromGalactic(sky), sst, cst);
    }

/// Update target transformation
    void KernelGalacticRefSys::tartran(
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
        mKernelICRefSys.tartran(ttj, amprms, ae2mt, hm, lat, diurab, 
                refac, refbc, temp, press, humid, tlr, wavel, 
                sst, cst, mICRefSys.fromGalactic(tar));
    }

/// target vector to mount roll and pitch
/**
    \returns status (0 => success)
*/
    int KernelGalacticRefSys::track(
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
        return mKernelICRefSys.track(mICRefSys.fromGalactic(tar), sst, cst, 
                rotl, rma, roll, pitch, xr, yr, ia, ib, np, tel, ga, gb, 
                rnogo, aim, ad1, bd1, ad2, bd2);
    }

/// Focal plane x,y to sky coordinates
/**
    \returns sky vector
*/
    vector KernelGalacticRefSys::vtsky(
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

    // sky vector in ICRS.
        spherical icrs = mKernelICRefSys.vtsky(roll, pitch, rotl, rma, xy, 
                sst, cst, ia, ib, np, tel, ga, gb);

    // ICRS to Galactic
        return mGalacticRefSys.fromICRS(icrs);
    }

/// Sky coordinates to non rotating focal plane x,y
    int KernelGalacticRefSys::vtxe(
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
        return mKernelICRefSys.vtxe(mICRefSys.fromGalactic(tar), sst, cst, 
                roll, pitch, ia, ib, np, tel, ga, gb, xieta);
    }

/// Sky coordinates to rotating focal plane x,y
    int KernelGalacticRefSys::vtxy(
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
        return mKernelICRefSys.vtxy(mICRefSys.fromGalactic(tar), sst, cst, 
                rotl, rma, roll, pitch, ia, ib, np, tel, ga, gb, xy);
    }
}

