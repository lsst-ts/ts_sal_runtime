/// \file SolSysTargets.cpp
/// \brief Implemetation of the solar systm target classes.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "SolSysTargets.h"

#include <stdexcept>
#include "slalib.h"

#include "ICRSTarget.h"
#include "Site.h"
#include "TcsLib.h"

namespace tpk {

    void SolarSystemTarget::update(
        const double& t
    ) {
        mMutex.lock();
        deltav offset = mOffset;
        mMutex.unlock();

    // Get site context.
        const double elong = mSite.elongitude();
        const double lat = mSite.latitude();
        double amprms[21];
        mSite.amprms( amprms );

    // Get target position for now and 1 minute in the future.
        double tt[2];
        vector p[2];
        tt[0] = mSite.tt(t);
        tt[1] = mSite.tt(t + 1.0 / 1400.0);
        for ( int i = 0; i < 2; i++ ) {

        // Topocentric apparent position.
            int stat;
            double r, a, b;
            slaPlante(tt[i], elong, lat, mForm, mEpochOfEl, mOrbInc, mANode, mPerih,
                    mAorQ, mE, mAorL, mDailyMot, &a, &b, &r, &stat);
            if ( stat ) {
                throw std::runtime_error("fatal error in slaPlante");
            }
            p[i] = vector(a, b) + offset;
        }

    // Compute rates.
        spherical p1 = p[0];
        spherical p2 = p[1];
        double radot = (p2.a - p1.a) / (tt[1] - tt[0]);
        double decdot = (p2.b - p1.b) / (tt[1] - tt[0]);

    // Update position and rates of position target.
        mMutex.lock();
        delete mPosition;
        mPosition = new TopoApptTarget(mSite, t, p1.a, p1.b, radot, decdot);
        mMutex.unlock();

    // Update position target.
        mPosition->update(t);
    }

    void SolarSystemTarget::adjust(
        const double& t,
        const vector& pos
    ) {

    // Get position at time t in the tracking frame.
        vector oldpos = position(t);

    // Get existing rates.
        deltav rate = position(t + 1.0) - oldpos;

    // Difference between old and new is the change in offset.
        deltav diff = pos - oldpos;

    // Store the new offset and adjust the target position.
        mMutex.lock();
        delete mPosition;
        mPosition = new TopoApptTarget(mSite, t, pos, rate);
        mOffset = mOffset + diff;
        mMutex.unlock();

    // Update tracking frame position and rates.
        update(t);
    }

/// Constructor
    AsAmajorPlanet::AsAmajorPlanet(
        const Site& site,             ///< telescope site
        double epochofel,             ///< epoch of elements (TT, MJD)
        double orbinc,                ///< orbital inclination (degrees)
        double longascnode,           ///< longitude of ascending node (degrees)
        double longofperih,           ///< longitude of perihelion (degrees)
        double meandist,              ///< mean distance (AU)
        double eccentricity,          ///< eccentricity
        double meanlong,              ///< mean longitude (degrees)
        double dailymot               ///< daily motion (degrees)
    ) : SolarSystemTarget(site) {
        mForm = 1;
        mEpochOfEl = epochofel;
        mOrbInc = orbinc * TcsLib::d2r;
        mANode = longascnode * TcsLib::d2r;
        mPerih = longofperih * TcsLib::d2r;
        mAorQ = meandist;
        mE = eccentricity;
        mAorL = meanlong * TcsLib::d2r;
        mDailyMot = dailymot * TcsLib::d2r;
        update(site.tai());
    }

/// Constructor
    JPLmajorPlanet::JPLmajorPlanet(
        const Site& site,             ///< telescope site
        double epochofel,             ///< epoch of elements (MJD)
        double orbinc,                ///< orbital inclination (degrees)
        double longascnode,           ///< longitude of ascending node (degrees)
        double argofperih,            ///< argument of perihelion (degrees)
        double meandist,              ///< mean distance (AU)
        double eccentricity,          ///< eccentricity
        double meananom,              ///< mean anomoly (degrees)
        double dailymot               ///< daily motion (degrees)
    ) : AsAmajorPlanet(site, epochofel, orbinc, longascnode,
            longascnode + argofperih, meandist, eccentricity,
            longascnode + argofperih + meananom, dailymot) {};

/// Constructor
    MinorPlanet::MinorPlanet(
        const Site& site,             ///< telescope site
        double epochofel,             ///< epoch of elements (MJD)
        double orbinc,                ///< orbital inclination (degrees)
        double longascnode,           ///< longitude of ascending node (degrees)
        double argofperih,            ///< argument of perihelion (degrees)
        double meandist,              ///< mean distance (AU)
        double eccentricity,          ///< eccentricity
        double meananom               ///< mean anomoly (degrees)
    ) : SolarSystemTarget(site) {
        mForm = 2;
        int stat;
        double t = site.tai();
        slaPertel( mForm, epochofel, site.tt(t), epochofel, orbinc * TcsLib::d2r,
                longascnode * TcsLib::d2r, argofperih * TcsLib::d2r, meandist,
                eccentricity, meananom * TcsLib::d2r, &mEpochOfEl, &mOrbInc, 
                &mANode, &mPerih, &mAorQ, &mE, &mAorL, &stat);
        if ( stat ) {
            throw std::runtime_error("fatal error in slaPertel");
        }
        update(t);
    }

/// Constructor
    MinorSolarSystemBody::MinorSolarSystemBody(
        const Site& site,             ///< telescope site
        double epochofel,             ///< epoch of elements (MJD)
        double orbinc,                ///< orbital inclination (degrees)
        double longascnode,           ///< longitude of ascending node (degrees)
        double argofperih,            ///< argument of perihelion (degrees)
        double perihdist,             ///< perihelion distance (AU)
        double eccentricity,          ///< eccentricity
        double epochofperih           ///< epoch of perihelion (MJD)
    ) : SolarSystemTarget(site) {

    // Apply planetary perturbation.
        mForm = 3;
        int stat;
        double t = site.tai();
        slaPertel( mForm, epochofel, site.tt(t), epochofperih,
                orbinc * TcsLib::d2r, longascnode * TcsLib::d2r,
                argofperih * TcsLib::d2r, perihdist, eccentricity, 0.0,
                &mEpochOfEl, &mOrbInc, &mANode, &mPerih, &mAorQ, &mE, &mAorL, 
                &stat);
        if ( stat ) {
            throw std::runtime_error("fatal error in slaPertel");
        }
        update(t);
    }
}

