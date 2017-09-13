/// \file ICRSTarget.cpp
/// \brief Implementation of the international coordinate system target class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "ICRSTarget.h"

#include <stdexcept>
#include <string>
#include "slalib.h"

#include "ApptRefSys.h"
#include "ApptTarget.h"
#include "AzElRefSys.h"
#include "AzElTarget.h"
#include "FK5RefSys.h"
#include "FK5Target.h"
#include "ICRefSys.h"
#include "Site.h"
#include "TcsMutex.h"
#include "TopoApptRefSys.h"
#include "TopoApptTarget.h"

namespace {
    int starin ( char[], int*, double*, double*, double*, double*,
            double*, double*, double* );
}

namespace tpk {

/// Constructor from a vector position.
    ICRSTarget::ICRSTarget(
        const Site& site,    ///< telescope site
        const vector& pos    ///< ICRS position
    ) :
        TrackingTarget(site),
        mPositionICRS(pos),
        mT0ICRS(site.tai()),
        mVelocityICRS(0.0, 0.0, 0.0) {

    // Update tracking frame position and rates.
        update(mT0ICRS);
    }

/// Constructor from a vector positions and tracking rates.
    ICRSTarget::ICRSTarget(
        const Site& site,    ///< telescope site
        const double& t0,    ///< reference time (MJD)
        const vector& pos,   ///< ICRS position at t0
        const deltav& rate   ///< displacement per day
    ) :
        TrackingTarget(site),
        mPositionICRS(pos),
        mT0ICRS(t0),
        mVelocityICRS(rate) {

    // Replace zero reference time with now.
        if ( mT0ICRS <= 0.0 ) {
            mT0ICRS = site.tai();
        }

    // Update tracking frame position and rates.
        update(site.tai());
    }

/// Constructor from a right ascension and declination
    ICRSTarget::ICRSTarget(
        const Site& site,    ///< telescope site
        const double& ra,    ///< ICRS right ascension (radians)
        const double& dec    ///< ICRS declination (radians)
    ) :
        TrackingTarget(site),
        mPositionICRS(ra, dec),
        mT0ICRS(site.tai()),
        mVelocityICRS(0.0, 0.0, 0.0) {

    // Update tracking frame position and rates.
        update(mT0ICRS);
    }

/// Constructor from a right ascension and declination and rates.
    ICRSTarget::ICRSTarget(
        const Site& site,    ///< telescope site
        const double& t0,    ///< reference time (MJD)
        const double& ra,    ///< ICRS right ascension (radians)
        const double& dec,   ///< ICRS declination (radians)
        const double& radot, ///< rate in right ascension (radians/day)
        const double& decdot ///< rate in declination (radians/day)
    ) :
        TrackingTarget(site),
        mPositionICRS(ra, dec),
        mT0ICRS(t0) {

    // Compute displacement.
        mVelocityICRS = vector(ra + radot, dec + decdot) - vector(ra, dec);

    // Replace zero reference time with now.
        if ( mT0ICRS <= 0.0 ) {
            mT0ICRS = site.tai();
        }

    // Update tracking frame position and rates.
        update(site.tai());
    }

/// Constructor RA, Dec and space motions
    ICRSTarget::ICRSTarget(
        const Site& site,              ///< telescope site
        const double& ra,              ///< ICRS Right ascension (radians)
        const double& dec,             ///< ICRS Declination (radians)
        const double& epoch,           ///< date of position (Julian epoch)
        const double& pmRA,            ///< dRA/dt (radians/Jyear)
        const double& pmDec,           ///< dDec/dt (radians/Jyear)
        const double& px,              ///< parallax (radians)
        const double& rv               ///< radial velocity (km/s)
    ) : TrackingTarget(site) {

    // Store position and rates at current epoch.
        init( ra, dec, pmRA, pmDec, px, rv, epoch);
    }

/// Constructor with target specified as a string
/**
    The target is assumed to be a star position specified as a
    free-format string.
*/
    ICRSTarget::ICRSTarget(
        const Site& site,              ///< telescope site
        const std::string& starget     ///< new target
    ) :
        TrackingTarget(site)
    {

    // Decode the string.
        int inptr = 1;
        double ra, dec, epoch, pmr, pmd, px, rv;
        if ( starin( const_cast<char*>(starget.c_str()), &inptr, &ra, &dec,
                &pmr, &pmd, &epoch, &px, &rv) ) {
            throw std::runtime_error("Unable to decode target");
        }

    // Store position and rates at current epoch.
        init( ra, dec, pmr, pmd, px, rv, epoch);
    }

/// Target position in another frame.
/**
    \returns target position in specified frame
*/
    vector ICRSTarget::position(
        const double& t,           ///< TAI (MJD)
        const RefSys& frame        ///< coordinate reference system.
    ) const {

    // Position in ICRS at time t.
        mMutex.lock();
        vector p = mPositionICRS + mVelocityICRS * (t - mT0ICRS);
        mMutex.unlock();

        return frame.fromICRS(t, mSite, p);
    }

    void ICRSTarget::adjust(
        const double& t,
        const vector& pos
    ) {

    // Create a temporary tracking frame target.
        Target* target = mTrackFrame->target( mSite, pos);

    // Get the target's position in ICRS.
        vector p = target->position(t, ICRefSys());

    // Store the new position and reference time.
        mMutex.lock();
        mPositionICRS = p;
        mT0ICRS = t;
        mMutex.unlock();

    // Delete the temporary target.
        delete target;

    // Update tracking frame position and rates.
        update(t);
    }

// Convert position to position and rates at the current epoch.
    void ICRSTarget::init(
        const double& ra,
        const double& dec,
        const double& pmr,
        const double& pmd,
        const double& px,
        const double& rv,
        const double& epoch
    ) {

    // Apply proper motions to current epoch.
        double a1, b1;
        double t = mSite.tai();
        slaPm(ra, dec, pmr, pmd, px/TcsLib::as2r, rv, epoch, mSite.ttj(t),
                &a1, &b1 );
        vector p1(a1, b1);

    // Position in 10 seconds time.
        double a2, b2;
        double dt = 10.0/86400.0;
        slaPm(ra, dec, pmr, pmd, px/TcsLib::as2r, rv, epoch, 
                mSite.ttj(t + dt), &a2, &b2 );
        vector p2(a2, b2);

    // Store in member variables.
        mPositionICRS = p1;
        mT0ICRS = t;
        mVelocityICRS = (p2 - p1) / dt;

    // Update tracking frame position and rates.
        update(t);
    }
}

/*----------------------------------------------------------------------*/

namespace {
    int starin ( char string[], int* iptr, double* ra, double* dec,
        double* pmr, double* pmd, double* ep, double* px, double* rv )

    /*
    **  - - - - - - -
    **   s t a r i n
    **  - - - - - - -
    **
    **  Decode a string representing a star position.
    **
    **  The string contains the following fields:
    **
    **    RA Dec [ [ [ [ pmRA pmDec ] Epoch ] Px ] RV ]
    **
    **  where
    **
    **    RA      = right ascension in hours, minutes, seconds
    **    Dec     = declination in degrees, minutes, seconds
    **    pmRA    = proper motion in RA, seconds per year
    **    pmDec   = proper motion in Dec, arcseconds per year
    **    Epoch   = epoch of the catalog entry
    **    Px      = parallax in arcseconds
    **    RV      = radial velocity in km/s
    **
    **  Example strings:
    **
    **    "12 34 56.789 -01 23 45.67 -0.0034 +0.056 2000 0.032 +21.0"
    **    "12 34 56.789 -01 23 45.67 -0.0034 +0.056 2000 0.032"
    **    "12 34 56.789 -01 23 45.67 -0.0034 +0.056 2000"
    **    "12 34 56.789 -01 23 45.67 -0.0034 +0.056"
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
    **     pmr     double*  right ascension proper motion (radians/year)
    **     pmd     double*  declination proper motion (radians/year)
    **     eq      double*  equinox (years)
    **     ep      double*  epoch (years)
    **     px      double*  parallax (radians)
    **     rv      double*  radial velocity (km/s)
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
    **  3)  The proper motions, which default to zero, are per year.  Many
    **      catalogs give proper motions per century, which must be divided
    **      by 100 to be interpreted correctly by the present function.
    **
    **      The RA proper motion is in terms of dRA, not distance on the
    **      sky.  In catalogs that specify RA proper motions in arcseconds
    **      (per year or century), a scaling by 1/cos(Dec) must be applied
    **      before use by the present function (or, more rigorously, a
    **      tangent-plane transformation must be applied).
    **
    **  5)  The epoch, the time at which the RA,Dec is correct and from
    **      which the proper motion is reckoned. If the epoch is absent J2000
    **      is returned.
    **
    **  6)  If the parallax is absent or negative, zero is returned.
    **
    **  7)  Positive radial velocity means the target is receding.  If
    **      absent, zero is returned.
    **
    **  8)  Further fields after the expected twelve are not treated as an
    **      error.  The pointer iptr is left in the correct state for
    **      further decoding with with slaDfltin etc.
    **
    **  Last revised December 17, 2003.
    **  Copyright CLRC and P.T.Wallace;  all rights reserved.
    */

#define S2R 7.2722052166430399e-5
#define AS2R 4.8481368110953599e-6

    {
        double pr, pd, epo, p, v, r, d;
        int jr, jd, jpr, jpd, jepo, jp, jv;


    /* Set defaults. */
        pr = 0.0;
        pd = 0.0;
        epo = 0.0;
        p = 0.0;
        v = 0.0;

    /* Decode. */
        slaDafin ( string, iptr, &r, &jr );
        slaDafin ( string, iptr, &d, &jd );
        slaDfltin ( string, iptr, &pr, &jpr );
        slaDfltin ( string, iptr, &pd, &jpd );
        slaDfltin ( string, iptr, &epo, &jepo );
        slaDfltin ( string, iptr, &p, &jp );
        slaDfltin ( string, iptr, &v, &jv );

    /* Check for omissions and errors. */
        if ( jr    > 0 ||
                jd    > 0 ||
                jpr   > 1 ||
                jpd   > 1 ||
                jepo  > 1 ||
                jp    > 1 ||
                jv    > 1    ) return -1;

    /* Epoch default. */
        if ( jepo > 0 ) {
            epo = 2000.0;
        }

    /* Results. */
        *ra = r * 15.0;
        *dec = d;
        *pmr = pr * S2R;
        *pmd = pd * AS2R;
        *ep = epo;
        *px = p <= 0.0 ? 0.0 : p * AS2R;
        *rv = v;

        return 0;
    }
}

