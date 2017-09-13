/// \file TcsLib.cpp
/// \brief Implementation of the TcsLib class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "TcsLib.h"

#include "tcsmac.h"

#include "Coordinates.h"

namespace tpk {

// Mathematical constants from tcs.h.
    const double TcsLib::pi = PI;              ///< pi
    const double TcsLib::pi2 = PI2;            ///< 2pi
    const double TcsLib::d2r = D2R;            ///< degrees to radians
    const double TcsLib::r2d = 1.0/D2R;        ///< radians to degrees
    const double TcsLib::as2r = AS2R;          ///< arcsec to radians
    const double TcsLib::r2as = 1.0/AS2R;      ///< radians to arcsec 
    const double TcsLib::d90 = D90;            ///< pi/2

// Physical constants from tcs.h .
    const double TcsLib::strpd = STRPD;        ///< Earth spin rate (rad/UT day)
    const double TcsLib::c = C;                ///< speed of light (AU/day)
    const double TcsLib::au2km = AU2KM;        ///< AU to km
    const double TcsLib::utst = UTST;          ///< ratio of SI to ST second

/// \internal
/// Slow update
    void TcsLib::slow(
        const double& tai,      ///< TAI (MJD)
        const double& delut,    ///< current UT1-UTC (day)
        const double& delat,    ///< TAI-UTC (day)
        const double& ttmtai,   ///< TT-TAI (day)
        const double& temp,     ///< ambient temperature (K)
        const double& press,    ///< pressure (mB)
        const double& humid,    ///< relative humidity (0-1)
        const double& wavelr,   ///< reference wavelength (micrometres)
        const double& elong,    ///< telescope longitude (true)
        double& t0,             ///< reference epoch (TAI MJD)
        double& st0,            ///< LAST at reference epoch (radians)
        double& tt0,            ///< TT at reference epoch (MJD)
        double& ttj,            ///< TT at reference epoch (Julian Epoch)
        double amprms[21],      ///< target-independent MAP parameters
        double& refa,           ///< tan refraction constant
        double& refb            ///< tan^3 refraction constant
    ) throw() {
        tcspk::tcsSlow( tai, delut, delat, ttmtai, temp, press, humid, wavelr,
                    elong, &t0, &st0, &tt0, &ttj, amprms, &refa, &refb);
    }


/// \internal
/// Telescope to boresight
    vector TcsLib::bs(
        const vector& tel,            ///< Telescope vector
        const rotloc& rotl,           ///< Rotator location
        const double& rma,            ///< Rotator mechanical angle
        const double& roll,           ///< Roll
        const double& pitch,          ///< Pitch
        const double& ga,             ///< Roll guiding adjustment
        const double& gb,             ///< Pitch guiding adjustment
        const focalplane& xy          ///< Focal plane x,y
    ) throw() {
        vector bs;
        tcspk::tcsBs( tel.x, tel.y, tel.z, rotl, rma, roll, pitch, ga, gb,
                xy.x, xy.y, &bs.x, &bs.y, &bs.z);
        return bs;
    }

/// \internal
/// Encoder to aim.
    vector TcsLib::enc2aim(
        const double& roll,        ///< Roll
        const double& pitch,       ///< Pitch
        const vector& bs,          ///< Boresight vector
        const double& ia,          ///< Roll index error
        const double& ib,          ///< Pitch index error
        const double& np           ///< Axis non-perpendicularity
    ) throw() {
        vector aim;
        tcspk::tcsEnc2aim( roll, pitch, bs.x, bs.y, bs.z, ia, ib, np,
                &aim.x, &aim.y, &aim.z);
        return aim;
    }

/// \internal
/// Rotate xi,eta into x,y.
/**
    \returns x,y in focal plane
*/
    focalplane TcsLib::xe2xy(
        const focalplane& xieta,      ///< xi, eta
        const rotloc& rotl,           ///< rotator location
        const double& rma,            ///< rotator mechanical angle (radians)
        const double& roll,           ///< mount roll angle (radians)
        const double& pitch           ///< mount pitch angle (radians)
    ) throw () {
        focalplane xy;
        tcspk::tcsXe2xy( xieta.xi, xieta.eta, rotl, rma, roll, pitch,
                &xy.x, &xy.y);
        return xy;
    }

/// \internal
/// Rotate x,y into xi,eta
/**
    \returns xi,eta in focal plane
*/
    focalplane TcsLib::xy2xe(
        const focalplane& xy,         ///< x,y
        const rotloc& rotl,           ///< rotator location
        const double& rma,            ///< rotator mechanical angle (radians)
        const double& roll,           ///< mount roll angle (radians)
        const double& pitch           ///< mount pitch angle (radians)
    ) throw () {
        focalplane xieta;
        tcspk::tcsXy2xe( xy.x, xy.y, rotl, rma, roll, pitch,
                &xieta.xi, &xieta.eta);
        return xieta;
    }

/// \internal
/// Convert rotator angle to Cassegrain equivalent.
    void TcsLib::casspa(
        const rotloc& rotl,           ///< rotator location
        const double& rma,            ///< rotator mechanical angle (radians)
        const double& roll,           ///< mount roll angle (radians)
        const double& pitch,          ///< mount pitch angle (radians)
        double& spa,                  ///< sine of Cass equivalent angle
        double& cpa                   ///< cosine of Cass equivalent angle
    ) throw () {
        tcspk::tcsCasspa( rotl, rma, roll, pitch, &spa, &cpa);
    }

/// \internal
/// Update summary pointing model
    void TcsLib::pup(
        int maxtrm,                 ///< maximum number of terms in model
        const int model[],          ///< term numbers for current model
        const double* coeffv,       ///< coefficient values
        int nterml,                 ///< number of local terms
        int ntermx,                 ///< number of terms implemented explicitly
        int nterms,                 ///< number of terms available currently
        const char coeffn[][9],     ///< coefficient names
        const char coform[][9],     ///< format of generic term
        mtype mtype,                ///< mount type
        const double ae2nm[3][3],   ///< matrix, [Az,El] to nominal mount
        double roll,                ///< demand mount roll (radians)
        double pitch,               ///< demand mount pitch (radians)
        bool bp,                    ///< beyond the pole flag
        const double aux[3],        ///< auxiliary readings
        double lat,                 ///< telescope latitude (true)
        double& ia,                 ///< roll zero point
        double& ib,                 ///< pitch zero point
        double& np,                 ///< mount axes nonperpendicularity
        vector& tel,                ///< telescope vector
        double ae2mt[3][3]          ///< rotation matrix, [Az,El] to mount
    ) throw(std::runtime_error) {
        if ( tcspk::tcsPup( maxtrm, const_cast<int*>(model),
                const_cast<double*>(coeffv), nterml, ntermx, nterms,
                const_cast<char(*)[9]>(coeffn), const_cast<char(*)[9]>(coform),
                mtype, const_cast<double(*)[3]>(ae2nm), roll, pitch, bp,
                const_cast<double*>(aux), lat, &ia, &ib, &np,
                &tel.x, &tel.y, &tel.z, ae2mt) ) {

        // Model update failed. Throw exception.
            throw std::runtime_error("fatal error in tcsPup");
        }
    }

/// \internal
/// Load pointing model from file
    void TcsLib::intpm(
        const std::string& filename, ///< model file name
        int maxtrm,                  ///< maximum number of terms in model
        int ntroom,                  ///< number of known terms
        int model[],                 ///< term numbers for current model
        int& nterml,                 ///< number of local terms
        int& ntermx,                 ///< number of terms implemented explicitly
        int& nterms,                 ///< number of terms available currently
        char coeffn[][9],            ///< coefficient names
        char coform[][9],            ///< format of generic term
        double coeffv[]              ///< coefficient values
    ) throw(std::runtime_error) {
        if ( int code = tcspk::tcsIntpm( const_cast<char*>(filename.c_str()),
                maxtrm, ntroom, model, &nterml, &ntermx, &nterms, coeffn, 
                coform, coeffv) ) {
            switch (code) {
                case -1:
                    throw std::runtime_error(
                            "unable to initialise pointing model");
                case -2:
                    throw std::runtime_error(
                            "unable to open pointing model file");
                case -3:
                    throw std::runtime_error(
                           "I/O error or premature EOF in pointing model file");
                case -4:
                    throw std::runtime_error(
                            "unrecognized record in pointing model file");
                case -5:
                    throw std::runtime_error(
                            "unable to add term to pointing model");
            }
        }
    }

/// \internal
/// Initialise pointing model
    void TcsLib::minit(
        int maxtrm,                ///< maximum number of terms in model
        int ntroom,                ///< number of known terms
        int model[],               ///< term numbers for current model
        int& nterml,               ///< number of local terms
        int& ntermx,               ///< number of terms implemented explicitly
        int& nterms,               ///< number of terms available currently
        char coeffn[][9]           ///< coefficient names
    ) throw () {
        tcspk::tptMinit( maxtrm, ntroom, model, &nterml, &ntermx, &nterms,
                coeffn);
    }

/// \internal
/// Add term to pointing model
    void TcsLib::addtrm(
        int maxtrm,                   ///< maximum number of terms in model
        int ntroom,                   ///< number of known terms
        const std::string& name,      ///< name of term
        double value,                 ///< value of term (radians)
        int& nterms,                  ///< number of terms available currently
        char coeffn[][9],             ///< coefficient names
        char coform[][9],             ///< format of generic term
        int model[],                  ///< term numbers for current model
        double coeffv[]               ///< coefficient values
    ) throw (std::runtime_error) {
        int code = tcspk::tcsAddtrm( maxtrm, ntroom,
                const_cast<char*>(name.c_str()), value, &nterms, coeffn, coform,
                model, coeffv );
        if ( code <= 0 ) {
            switch (code) {
                case 0:
                    throw std::runtime_error(
                            "no room in repertoire for new generic term");
                case -1: {
                    std::string error("unknown term \"");
                    error += name;
                    error += "\"";
                    throw std::runtime_error(error);
                }
                case -2:
                    throw std::runtime_error("no room left in model");
            }
        }
    }

/// \internal
/// Set term in pointing model
    void TcsLib::sterm(
        const std::string& name,      ///< name of term
        double value,                 ///< value of term (radians)
        int maxtrm,                   ///< maximum number of terms in model
        int model[],                  ///< term numbers for current model
        char coeffn[][9],             ///< coefficient names
        double coeffv[]               ///< coefficient values
    ) throw (std::runtime_error) {
        int code = tcspk::tcsSterm( const_cast<char*>(name.c_str()), value, 
                    maxtrm, model, coeffn, coeffv);
        if ( code ) {
            switch (code) {
                case -1:
                    std::string error("\"");
                    error += name;
                    error += "\" is not in model";
                    throw std::runtime_error(error);
            }
        }
    }

/// \internal
/// Inquire value of term.
    void TcsLib::iterm(
        int iterm,                    ///< index of term
        int maxtrm,                   ///< maximum number of terms in model
        const int model[],            ///< term numbers for current model
        const char coeffn[][9],       ///< coefficient names
        const double coeffv[],        ///< coefficient values
        std::string& name,            ///< term name
        double& value                 ///< term value
    ) throw (std::runtime_error) {
        char cname[9];
        int code = tcspk::tcsIterm( iterm, maxtrm, const_cast<int*>(model),
                const_cast<char(*)[9]>(coeffn), const_cast<double*>(coeffv),
                cname, &value);
        if ( code ) {
            switch (code) {
                case -1:
                    std::string error("term \"");
                    error += name;
                    error += "\" is not in model";
                    throw std::runtime_error(error);
            }
        }
        name = std::string(cname);
    }
}

