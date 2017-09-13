/// \file Site.cpp
/// \brief Implementation of the site class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "Site.h"

#include <stdexcept>
#include "slalib.h"

#include "TcsLib.h"
#include "TcsMutex.h"

namespace tpk {

    extern double tlr;
    extern double wavelr;

/**
    \exception std::runtime_error
*/
    Site::Site(
        double tai,         ///< current TAI (MJD)
        double delut,       ///< current UT1-UTC (seconds)
        double delat,       ///< TAI-UTC (seconds)
        double ttmtai,      ///< TT-TAI (seconds)
        double elongm,      ///< longitude of site (degrees, east +ve)
        double latm,        ///< geodetic latitude of site (degrees)
        double hm,          ///< site elevation (meters above sea level)
        double xpm,         ///< polar motion x (arcseconds)
        double ypm          ///< polar motion y (arcseconds)
    ) throw(std::runtime_error) :
        mElongm(elongm * TcsLib::d2r),
        mLatm(latm * TcsLib::d2r),
        mHm(hm),
        mTtmtai(ttmtai / 86400.0)
    {

    // Correct obervatory location for polar motions
        earthOrientation( delut, delat, xpm, ypm);

    // Initialise remaining context with nominal atmospheric parameters.
        double pressure = 1013.15 * exp( -hm / (29.3 * (278 + 0.0065 * hm)));
        refresh(tai, 278.0, pressure, 0.5);
    }
/**
    The copy constructor makes a copy of the context protected
    by a the source mutex.
*/
    Site::Site(const Site& src) :
        mElongm(src.mElongm),
        mLatm(src.mLatm),
        mHm(src.mHm),
        mTtmtai(src.mTtmtai)
    {
    // Lock the source context.
        src.mMutex.lock();

    // Copy the context.
        mTemp = src.mTemp;
        mPress = src.mPress;
        mHumid = src.mHumid;
        mXpm = src.mXpm;
        mYpm = src.mYpm;
        mDelut = src.mDelut;
        mDelat = src.mDelat;
        mElong = src.mElong;
        mLat = src.mLat;
        mUau = src.mUau;
        mVau = src.mVau;
        mUkm = src.mUkm;
        mVkm = src.mVkm;
        mDiurab = src.mDiurab;
        mT0 = src.mT0;
        mSt0 = src.mSt0;
        mTt0 = src.mTt0;
        mTtj = src.mTtj;
        TcsLib::copyAmprms(src.mAmprms, mAmprms);
        TcsLib::copyAoprms(src.mAoprms, mAoprms);

    // Release the source context.
        src.mMutex.unlock();
    }
/**
    \exception std::runtime_error
*/
    void Site::earthOrientation(
        double delut,       ///< current UT1-UTC (seconds)
        double delat,       ///< TAI-UTC (seconds)
        double xpm,         ///< polar motion x (arcseconds)
        double ypm          ///< polar motion y (arcseconds)
    ) throw(std::runtime_error) {
    
    // Copy context into local variables.
        mMutex.lock();
        double elongm = mElongm;
        double latm = mLatm;
        double hm = mHm;
        mMutex.unlock();
        
    // UT1-UTC and TAI-UTC to days.
        delut /= 86400.0;
        delat /= 86400.0;
        
    // Polar motions to radians
        xpm *= TcsLib::as2r;
        ypm *= TcsLib::as2r;

    // Correct the telescope latitude, longitude and azimuth for polar motion.
        double elong, lat, daz;
        slaPolmo ( elongm, latm, xpm, ypm, &elong, &lat, &daz );

    // Distance of observatory from Earth spin axis and equator.
        double uau, vau;
        slaGeoc ( lat, hm, &uau, &vau );
        double ukm = uau * TcsLib::au2km;
        double vkm = vau * TcsLib::au2km;
        double diurab = TcsLib::pi2 * uau * TcsLib::utst / TcsLib::c;
        
    // Copy results back to the context.
        mMutex.lock();
        mDelut = delut;
        mDelat = delat;
        mXpm = xpm,
        mYpm = ypm;
        mElong = elong;
        mLat = lat;
        mDiurab = diurab;
        mDaz = daz;
        mUau = uau;
        mVau = vau;
        mUkm = ukm;
        mVkm = vkm;
        mMutex.unlock();
    }

/// The "slow" update.
/**
    The slow update maintains those things that are slowly changing and
    target independent such as the refraction constants, the mean to
    apparent place parameters and a reference time in various time-scales.
    It can be executed at intervals of about 1 minute, depending mainly
    on the desired response to changes in the weather data.

    If the temperature, pressure and humidity are coming from a sensor
    of some sort, the measurements should have some degree of smoothing
    and range checking applied to prevent bad measurements upsetting
    the tracking of the telescope.  If real measurements are not
    available then:

    -# Guess or estimate the temperature = temp, e.g. 278.0
    -# Guess or estimate the humidity    = hum, e.g. 0.5
    -# Predict the pressure     = press

        = 1013.25 * exp ( -hm / ( 29.3 * ( tempc + 0.0065*hm ) ) )

        where temp is the estimated ambient temperature (K = C+273.15)
        and hm the site elevation in meters.
*/
    void Site::refresh(
        double tai,    ///< current TAI (MJD)
        double temp,   ///< current temperature (Kelvin)
        double press,  ///< current atmospheric pressure (mBar=hPa)
        double humid   ///< current relative humidity (fraction, 0.0-1.0)
    ) throw() {

    // Copy context into local variables.
        mMutex.lock();
        double elongm = mElongm;
        double latm = mLatm;
        double hm = mHm;
        double delut = mDelut;
        double delat = mDelat;
        double ttmtai = mTtmtai;
        double elong = mElong;
        double lat = mLat;
        double xpm = mXpm;
        double ypm = mYpm;
        mMutex.unlock();

        double t0, st0, tt0, ttj, amprms[21], refa, refb;
        TcsLib::slow( tai, delut, delat, ttmtai, temp, press, humid,
                wavelr, elong, t0, st0, tt0, ttj, amprms, refa, refb);

    // Target independent apparent to observed parameters.
        double aoprms[14];
        slaAoppa(tai - delat, delut * 86400.0, elongm, latm, hm, xpm, ypm,
                temp, press, humid, wavelr, tlr, aoprms);

    // Replace tlat etc with more rigourous values.
        aoprms[0] = lat;
        aoprms[1] = sin(lat);
        aoprms[2] = cos(lat);

    // Copy results back to the context.
        mMutex.lock();
        mTemp = temp;
        mPress = press;
        mHumid = humid;
        mTai = tai;
        mT0 = t0;
        mSt0 = st0;
        mTt0 = tt0;
        mTtj = ttj;
        TcsLib::copyAmprms(amprms, mAmprms);
        TcsLib::copyAoprms(aoprms, mAoprms);
        mRefa = refa;
        mRefb = refb;
        mMutex.unlock();
    }

/// Slow update with no change to atmospheric parameters.
/**
    The reference time and precession are updated without changing the
    refraction constants.
*/
    void Site::refresh(
        double tai     ///< current TAI (MJD)
    ) throw() {

    // Copy atmospheric parameters from context.
        mMutex.lock();
        double temp = mTemp;
        double press = mPress;
        double humid = mHumid;
        mMutex.unlock();

    // Refresh.
        refresh( tai, temp, press, humid);
    }

/// Convert TAI to sidereal time
/**
    \returns sidereal time (radians)
*/
    double Site::st(
        double tai       /// TAI (MJD)
    ) const throw () {
        mMutex.lock();
        double t0 = mT0;
        double st0 = mSt0;
        mMutex.unlock();
        return st0 + (tai - t0) * TcsLib::strpd;
    }

/// Convert TAI to terrestrial time
/**
    \returns TT (MJD)
*/
    double Site::tt(
        double tai       /// time TAI (MJD)
    ) const throw () {
        mMutex.lock();
        double t0 = mT0;
        double tt0 = mTt0;
        mMutex.unlock();
        return tt0 + tai - t0;
    }

/// Convert TAI to terrestrial time
/**
    \returns TT (Julian epoch)
*/
    double Site::ttj(
        double tai       /// TAI (MJD)
    ) const throw () {
        mMutex.lock();
        double t0 = mT0;
        double ttj = mTtj;
        mMutex.unlock();
        return ttj + (tai - t0) / 365.25;
    }

/// return apparent to mean parameters.
    void Site::amprms(
        double amprms[21]      ///< apparent to mean parameters.
    ) const throw() {
        mMutex.lock();
        TcsLib::copyAmprms(mAmprms, amprms);
        mMutex.unlock();
    }

/// return apparent to observed parameters.
    void Site::aoprms(
        double aoprms[21]      ///< apparent to observed parameters.
    ) const throw() {
        mMutex.lock();
        TcsLib::copyAoprms(mAoprms, aoprms);
        mMutex.unlock();
    }
}

