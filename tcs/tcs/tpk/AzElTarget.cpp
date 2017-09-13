/// \file AzElTarget.cpp
/// \brief Implementation of the az,el target class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "AzElTarget.h"

#include <stdexcept>
#include <cstdio>
#include <string>
#include "slalib.h"

#include "ApptRefSys.h"
#include "ApptTarget.h"
#include "AzElRefSys.h"
#include "AzElTarget.h"
#include "Site.h"
#include "TcsMutex.h"

namespace tpk {

/// Constructor from a vector position.
    AzElTarget::AzElTarget(
        const Site& site,    ///< telescope site
        const vector& pos    ///< AzEl position
    ) :
        TrackingTarget(site),
        mPositionAzEl(pos),
        mT0AzEl(site.tai()),
        mVelocityAzEl(0.0, 0.0, 0.0) {

    // Update tracking frame position and rates.
        update(mT0AzEl);
    }

/// Constructor from a vector positions and tracking rates.
    AzElTarget::AzElTarget(
        const Site& site,    ///< telescope site
        const double& t0,    ///< reference time (MJD)
        const vector& pos,   ///< AzEl position at t0
        const deltav& rate   ///< Displacement per day
    ) :
        TrackingTarget(site),
        mPositionAzEl(pos),
        mT0AzEl(t0),
        mVelocityAzEl(rate) {

    // Replace zero reference time with now.
        if ( mT0AzEl <= 0.0 ) {
            mT0AzEl = site.tai();
        }

    // Update tracking frame position and rates.
        update(site.tai());
    }


/// Constructor from an azimuth and an elevation
    AzElTarget::AzElTarget(
        const Site& site,    ///< telescope site
        const double& az,    ///< azimuth (radians)
        const double& el     ///< elevation (radians)
    ) :
        TrackingTarget(site),
        mPositionAzEl(az, el),
        mT0AzEl(site.tai()),
        mVelocityAzEl(0.0, 0.0, 0.0) {

    // Update tracking frame position and rates.
        update(mT0AzEl);
    }

/// Constructor from an azimuth and elevation and rates.
    AzElTarget::AzElTarget(
        const Site& site,    ///< telescope site
        const double& t0,    ///< reference time (MJD)
        const double& az,    ///< azimuth (radians)
        const double& el,    ///< elevation (radians)
        const double& azdot, ///< rate in azimuth (radians/day)
        const double& eldot  ///< rate in elevation (radians/day)
    ) :
        TrackingTarget(site),
        mPositionAzEl(az, el),
        mT0AzEl(t0) {

    // Compute displacement.
        mVelocityAzEl = vector(az + azdot, el + eldot) - vector(az, el);

    // Replace zero reference time with now.
        if ( mT0AzEl <= 0.0 ) {
            mT0AzEl = site.tai();
        }

    // Update tracking frame position and rates.
        update(site.tai());
    }

/// Constructor with target specified as a string
/**
    The target is assumed to be a az and el specified as a
    free-format string.
*/
    AzElTarget::AzElTarget(
        const Site& site,              ///< telescope site
        const std::string& starget     ///< new target
    ) :
        TrackingTarget(site)
    {

    // Decode the string.
        double az, el;
        if ( sscanf( starget.c_str(), "%lf %lf", &az, &el) != 2 ) {
            throw std::runtime_error("Unable to decode target");
        }
        az *= TcsLib::d2r;
        el *= TcsLib::d2r;

    // Current time.
        double t = site.tai();

    // Store position.
        mPositionAzEl = vector(az, el);
        mT0AzEl = t;
        mVelocityAzEl = deltav(0.0, 0.0, 0.0);

    // Update tracking frame position and rates.
        update(t);
    }

/// Target position in another frame.
/**
    \returns target position in specified frame
*/
    vector AzElTarget::position(
        const double& t,           ///< TAI (MJD)
        const RefSys& frame        ///< coordinate reference system.
    ) const {

    // Position in az,el at time t.
        mMutex.lock();
        vector p = mPositionAzEl + mVelocityAzEl * (t - mT0AzEl);
        mMutex.unlock();

        return frame.fromAzEl(t, mSite, p);
    }

    void AzElTarget::adjust(
        const double& t,
        const vector& pos
    ) {

    // Create a temporary tracking frame target.
        Target* target = mTrackFrame->target( mSite, pos);

    // Get the target's position in AzEl.
        vector p = target->position(t, AzElRefSys());

    // Store the new position and reference time.
        mMutex.lock();
        mPositionAzEl = p;
        mT0AzEl = t;
        mMutex.unlock();

    // Delete the temporary target.
        delete target;

    // Update tracking frame position and rates.
        update(t);
    }
}

