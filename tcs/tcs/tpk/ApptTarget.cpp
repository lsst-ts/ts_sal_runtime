/// \file ApptTarget.cpp
/// \brief Implementation of the geocentric apparent target class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "ApptTarget.h"

#include <stdexcept>
#include <string>
#include "slalib.h"

#include "AzElRefSys.h"
#include "AzElTarget.h"
#include "ApptRefSys.h"
#include "ApptTarget.h"
#include "ICRefSys.h"
#include "ICRSTarget.h"
#include "Site.h"
#include "TcsMutex.h"
#include "TopoApptRefSys.h"
#include "TopoApptTarget.h"

namespace {
    int starin ( char[], int*, double*, double*);
}

namespace tpk {

/// Constructor from a position
    ApptTarget::ApptTarget(
        const Site& site,    ///< telescope site
        const vector& pos    ///< geocentric apparent RA, Dec
    ) :
        TrackingTarget(site),
        mPositionAppt(pos),
        mT0Appt(site.tai()),
        mVelocityAppt(0.0, 0.0, 0.0) {

    // Update tracking frame position and rates.
        update(mT0Appt);
    }

/// Constructor from a position and tracking rates.
    ApptTarget::ApptTarget(
        const Site& site,    ///< telescope site
        const double& t0,    ///< reference time (MJD)
        const vector& pos,   ///< geocentric apparent RA, Dec at t0
        const deltav& rate   ///< tracking rate (radians/day)
    ) :
        TrackingTarget(site),
        mPositionAppt(pos),
        mT0Appt(t0),
        mVelocityAppt(rate) {

    // Replace zero reference time with now.
        if ( mT0Appt <= 0.0 ) {
            mT0Appt = site.tai();
        }

    // Update tracking frame position and rates.
        update(site.tai());
    }


/// Constructor from a right ascension and declination
    ApptTarget::ApptTarget(
        const Site& site,    ///< telescope site
        const double& ra,    ///< geocentric apparent right ascension (radians)
        const double& dec    ///< geocentric apparent declination (radians)
    ) :
        TrackingTarget(site),
        mPositionAppt(ra, dec),
        mT0Appt(site.tai()),
        mVelocityAppt(0.0, 0.0, 0.0) {

    // Update tracking frame position and rates.
        update(mT0Appt);
    }

/// Constructor from a right ascension and declination and rates.
    ApptTarget::ApptTarget(
        const Site& site,    ///< telescope site
        const double& t0,    ///< reference time (MJD)
        const double& ra,    ///< geocentric apparent right ascension (radians)
        const double& dec,   ///< geocentric apparent declination (radians)
        const double& radot, ///< rate in right ascension (radians/day)
        const double& decdot ///< rate in declination (radians/day)
    ) :
        TrackingTarget(site),
        mPositionAppt(ra, dec),
        mT0Appt(t0) {

    // Compute displacement.
        mVelocityAppt = vector(ra + radot, dec + decdot) - vector(ra, dec);

    // Replace zero reference time with now.
        if ( mT0Appt <= 0.0 ) {
            mT0Appt = site.tai();
        }

    // Update tracking frame position and rates.
        update(site.tai());
    }

/// Constructor with target specified as a string
/**
    The target is assumed to be a star position specified as a
    free-format string.
*/
    ApptTarget::ApptTarget(
        const Site& site,              ///< telescope site
        const std::string& starget     ///< target position
    ) :
        TrackingTarget(site)
    {

    // Decode the string.
        int inptr = 1;
        double ra, dec;
        if ( starin( const_cast<char*>(starget.c_str()), &inptr, &ra, &dec ) ) {
            throw std::runtime_error("Unable to decode target");
        }

    // Current time.
        double t = site.tai();

    // Store position.
        mPositionAppt = vector(ra, dec);
        mT0Appt = t;
        mVelocityAppt = deltav(0.0, 0.0, 0.0);

    // Update tracking frame position and rates.
        update(t);
    }

/// Target position in another frame.
/**
    \returns target position in specified frame
*/
    vector ApptTarget::position(
        const double& t,           ///< TAI (MJD)
        const RefSys& refsys       ///< coordinate reference system.
    ) const {

    // Position in apparent at time t.
        mMutex.lock();
        vector p = mPositionAppt + mVelocityAppt * (t - mT0Appt);
        mMutex.unlock();

        return refsys.fromAppt(t, mSite, p);
    }

    void ApptTarget::adjust(
        const double& t,
        const vector& pos
    ) {

    // Create a temporary tracking frame target.
        Target* target = mTrackFrame->target( mSite, pos);

    // Get the target's position in Appt.
        vector p = target->position(t, ApptRefSys());

    // Store the new position and reference time.
        mMutex.lock();
        mPositionAppt = p;
        mT0Appt = t;
        mMutex.unlock();

    // Delete the temporary target.
        delete target;

    // Update tracking frame position and rates.
        update(t);
    }
}

/*----------------------------------------------------------------------*/

namespace {
    int starin ( char string[], int* iptr, double* ra, double* dec)

    /*
    **  - - - - - - -
    **   s t a r i n
    **  - - - - - - -
    **
    **  Decode a string representing a star position.
    **
    **  The string contains the following fields:
    **
    **    RA Dec
    **
    **  where
    **
    **    RA      = right ascension in hours, minutes, seconds
    **    Dec     = declination in degrees, minutes, seconds
    **
    **  Example strings:
    **
    **    "12 34 56.789 -01 23 45.67"
    **
    **  Given:
    **     string  char*    string to be decoded
    **     iptr    int*     where to start decode (1 = first character)
    **
    **  Returned:
    **     iptr    int*     advanced past decoded portion of string
    **     ra      double*  right ascension (radians)
    **     dec     double*  declination (radians)
    **
    **  Function value:
    **             int      status:  0 = OK
    **                              -1 = error
    **
    **  Called:  slaDafin, slaDfltin, slaDbjin, slaKbj
    **
    **  Notes:
    **
    **  1)  Decoding is free-format, using the SLALIB/C functions slaDafin
    **      and slaDfltin.  Separators can be whitespace or commas.
    **      Only minimal validation is performed.
    **
    **  2)  Both RA and Dec must be present.
    **
    **  Last revised December 17, 2003.
    **  Copyright CLRC and P.T.Wallace;  all rights reserved.
    */

    {
        double r, d;
        int jr, jd;

    /* Decode. */
        slaDafin ( string, iptr, &r, &jr );
        slaDafin ( string, iptr, &d, &jd );

    /* Check for omissions and errors. */
        if ( jr > 0 || jd > 0 ) return -1;

    /* Results. */
        *ra = r * 15.0;
        *dec = d;

        return 0;
    }
}

