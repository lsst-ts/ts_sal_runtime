/// \file TimeKeeper.cpp
/// \brief Implementation of the TimeKeeper class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "TimeKeeper.h"

#include <cmath>
#include <stdexcept>
#include "slalib.h"

#include "Clock.h"
#include "Site.h"
#include "TcsMutex.h"
#include "TcsLib.h"

namespace tpk {

    extern double transdelay;

/**
    \exception std::runtime_error
*/
    TimeKeeper::TimeKeeper(
        Clock& clock,              ///< clock
        const Site& site           ///< site
    ) throw(std::runtime_error) :
        mClock(clock),
        mSite(site)
    {
        update();
    }
/**
    The copy constructor makes a copy of the context protected
    by a the source object's mutex.
*/
    TimeKeeper::TimeKeeper(const TimeKeeper& src) :
        mClock(src.mClock),
        mSite(src.mSite)
    {
    // Lock the source context.
        src.mMutex.lock();

    // Copy the context.
        mTai = src.mTai;
        mTt = src.mTt;
        mCst = src.mCst;
        mSst = src.mSst;
        mDcst = src.mDcst;
        mDsst = src.mDsst;

    // Release the source context.
        src.mMutex.unlock();
    }

/// update
/**
    Reads the real-time clock and generates the time for the next kernel
    tick.

    The time read from the clock is advanced by the estimate of the time that
    it will take the timestampled demands to reach the TCS subsystems that
    control the actual mechanism and then rounded up to the nearest milli-
    second so that the resulting time is always between the delay and
    delay + one millisecond in the future.
*/
    void TimeKeeper::update() throw() {

    // Get time bases from the Site.
        mSite.mMutex.lock();
        double t0 = mSite.mT0;
        double tt0 = mSite.mTt0;
        double st0 = mSite.mSt0;
        mSite.mMutex.unlock();

    // Read clock.
        double tai = mClock.read();

    // Add the estimated delay in transmitting the demands to the
    // mechanism controllers.
        tai += transdelay;

    // Round to the next millisecond.
        double t = tai * 1000.0 * 86400.0;
        t = floor( t + 1.0 );
        tai = t / 1000.0 / 86400.0;

    // Terrestrial time at TAI.
        double tt = tt0 + (tai - t0);

    // sine and cosine of sidereal time.
        double st = st0 + (tai - t0) * TcsLib::strpd;
        double sst = sin(st);
        double cst = cos(st);

    // Rate of change.
        double dsst = TcsLib::strpd * cst;
        double dcst = - TcsLib::strpd * sst;

    // Copy the result back to the context.
        mMutex.lock();
        mTai = tai;
        mTt = tt;
        mSst = sst;
        mCst = cst;
        mDsst = dsst;
        mDcst = dcst;
        mMutex.unlock();
    }

// tai
/**
    Returns the time of the latest tick.

    \return TAI (MJD)
*/
    double TimeKeeper::tai() const throw () {
        mMutex.lock();
        double tai = mTai;
        mMutex.unlock();
        return tai;
    }
}

