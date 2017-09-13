/// \file FK5Target.cpp
/// \brief Implementation of the FK5 target class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "FK5Target.h"

#include <stdexcept>
#include <string>
#include "slalib.h"

#include "FK5RefSys.h"
#include "FK5Target.h"
#include "ICRefSys.h"
#include "ICRSTarget.h"
#include "Site.h"

namespace {
    int starin ( char[], int*, double*, double*, double*, double*,
            char*, double*, char*, double*, double*, double* );
}

namespace tpk {

/// Constructor from a vector
    FK5Target::FK5Target(
        const Site& site,              ///< telescope site
        const vector& pos,             ///< position in FK5
        const double& equinox          ///< equinox of position (Julian epoch)
    ) :
        TrackingTarget(site),
        mPositionFK5(pos),
        mT0FK5(site.tai()),
        mVelocityFK5(0.0, 0.0, 0.0),
        mEquinox(equinox)
    {

    // Update tracking frame
        update(mT0FK5);
    }

/// Constructor from a vector positions and tracking rates.
    FK5Target::FK5Target(
        const Site& site,             ///< telescope site
        const double& t0,             ///< reference time (MJD)
        const vector& pos,            ///< FK5 position at t0
        const deltav& rate,           ///< displacement per day
        const double& equinox         ///< equinox of position (Julian epoch)
    ) :
        TrackingTarget(site),
        mPositionFK5(pos),
        mT0FK5(t0),
        mVelocityFK5(rate),
        mEquinox(equinox) {

    // Replace zero reference time with now.
        if ( mT0FK5 <= 0.0 ) {
            mT0FK5 = site.tai();
        }

    // Update tracking frame position and rates.
        update(site.tai());
    }

/// Constructor from a right ascension and a declination.
    FK5Target::FK5Target(
        const Site& site,              ///< telescope site
        const double& ra,              ///< FK5 right ascension (radians)
        const double& dec,             ///< FK5 declination (radians)
        const double& equinox          ///< equinox of position (Julian epoch)
    ) :
        TrackingTarget(site),
        mPositionFK5(ra, dec),
        mT0FK5(site.tai()),
        mVelocityFK5(0.0, 0.0, 0.0),
        mEquinox(equinox)
    {

    // Update tracking frame
        update(mT0FK5);
    }

/// Constructor from a right ascension and declination and rates.
    FK5Target::FK5Target(
        const Site& site,          ///< telescope site
        const double& t0,          ///< reference time (MJD)
        const double& ra,          ///< FK5 right ascension (radians)
        const double& dec,         ///< FK5 declination (radians)
        const double& radot,       ///< rate in right ascension (radians/day)
        const double& decdot,      ///< rate in declination (radians/day)
        const double& equinox      ///< equinox of position (Julian epoch)
    ) :
        TrackingTarget(site),
        mPositionFK5(ra, dec),
        mT0FK5(t0),
        mEquinox(equinox) {

    // Compute displacement.
        mVelocityFK5 = vector(ra + radot, dec + decdot) - vector(ra, dec);

    // Replace zero reference time with now.
        if ( mT0FK5 <= 0.0 ) {
            mT0FK5 = site.tai();
        }

    // Update tracking frame position and rates.
        update(site.tai());
    }

/// Constructor from RA, Dec and space motions
    FK5Target::FK5Target(
        const Site& site,              ///< telescope site
        const double& ra,              ///< FK5 Right ascension (radians)
        const double& dec,             ///< FK5 Declination (radians)
        const double& equinox,         ///< equinox of position (Julian epoch)
        const double& epoch,           ///< date of position (Julian epoch)
        const double& pmRA,            ///< dRA/dt (radians/Jyear)
        const double& pmDec,           ///< dDec/dt (radians/Jyear)
        const double& px,              ///< parallax (radians)
        const double& rv               ///< radial velocity (km/s)
    ) :
        TrackingTarget(site),
        mEquinox(equinox)
    {

    // Store position and rates at current epoch.
        init( ra, dec, pmRA, pmDec, px, rv, epoch);
    }

/// Constructor with target specified as a string
/**
    The target is assumed to be a star position specified as a
    free-format string.

    \exception std::runtime_error
*/
    FK5Target::FK5Target(
        const Site& site,              ///< telescope site
        const std::string& starget     ///< target description
    ) :
        TrackingTarget(site)
    {

    // Decode the string.
        int inptr = 1;
        char jbeq, jbep;
        double ra, dec, epoch, pmr, pmd, px, rv;
        if ( starin( const_cast<char*>(starget.c_str()), &inptr, &ra, &dec,
                &pmr, &pmd, &jbeq, &mEquinox, &jbep, &epoch, &px, &rv) ) {
            throw std::runtime_error("Unable to decode target");
        }

    // Check that the epoch and equinox are both Julian.
        if ( jbeq != 'J' ) {
            throw std::runtime_error("FK5 target must have Julian equinox");
        }
        if ( jbeq != 'J' ) {
            throw std::runtime_error("FK5 target must have Julian epoch");
        }

    // Store position and rates at current epoch.
        init( ra, dec, pmr, pmd, px, rv, epoch);
    }

/// Target position in another frame.
/**
    \returns target position in specified frame
*/
    vector FK5Target::position(
        const double& t,           ///< TAI (MJD)
        const RefSys& frame        ///< coordinate reference system.
    ) const {

    // Position in FK5 at time t.
        mMutex.lock();
        vector p = mPositionFK5 + mVelocityFK5 * (t - mT0FK5);
        mMutex.unlock();

        return frame.fromFK5(t, mSite, p, mEquinox);
    }


    void FK5Target::adjust(
        const double& t,
        const vector& tar
    ) {

    // Create a temporary target in the tracking frame.
        Target* target = mTrackFrame->target( mSite, tar);

    // Get the target's position in FK5.
        vector pos = target->position(t, FK5RefSys(mEquinox));

    // Store the new position and reference time.
        mMutex.lock();
        mPositionFK5 = pos;
        mT0FK5 = t;
        mMutex.unlock();

    // Delete the temporary target.
        delete target;

    // Update tracking frame position and rates.
        update(t);
    }

// Convert position to position and rates at the current epoch.
    void FK5Target::init(
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

    // Rates
        deltav dv = (p2 - p1) / dt;

    // Store in member variables.
        mPositionFK5 = p1;
        mT0FK5 = t;
        mVelocityFK5 = dv;

    // Update tracking frame position and rates.
        update(t);
    }
}

/*----------------------------------------------------------------------*/

namespace {
    int starin ( char string[], int* iptr, double* ra, double* dec,
        double* pmr, double* pmd, char* jbeq, double* eq,
        char* jbep, double* ep, double* px, double* rv )

    /*
    **  - - - - - - -
    **   s t a r i n
    **  - - - - - - -
    **
    **  Decode a string representing a star position.
    **
    **  The string contains the following fields:
    **
    **    RA Dec [ [ [ [ [ pmRA pmDec ] Equinox ] Epoch ] Px ] RV ]
    **
    **  where
    **
    **    RA      = right ascension in hours, minutes, seconds
    **    Dec     = declination in degrees, minutes, seconds
    **    pmRA    = proper motion in RA, seconds per year
    **    pmDec   = proper motion in Dec, arcseconds per year
    **    Equinox = equinox of the catalog entry
    **    Epoch   = epoch of the catalog entry
    **    Px      = parallax in arcseconds
    **    RV      = radial velocity in km/s
    **
    **  Example strings:
    **
    **    "12 34 56.789 -01 23 45.67 -0.0034 +0.056 2000 2000 0.032 +21.0"
    **    "12 34 56.789 -01 23 45.67 -0.0034 +0.056 2000 2000 0.032"
    **    "12 34 56.789 -01 23 45.67 -0.0034 +0.056 2000 2000"
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
    **     jbeq    char*    equinox type: 'J' or 'B'
    **     eq      double*  equinox (years)
    **     jbep    char*    epoch type: 'J' or 'B'
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
    **  1)  Decoding is free-format, using the SLALIB/C functions slaDafin,
    **      slaDbjin and slaDfltin.  Separators can be whitespace or commas.
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
    **  4)  The equinox identifies the coordinate system.  Almost always
    **      it will be J2000 and will imply ICRS.  If it is absent, J2000 is
    **      returned.
    **
    **  5)  The epoch, the time at which the RA,Dec is correct and from
    **      which the proper motion is reckoned, is distinct from the
    **      "equinox", which identifies the coordinate system (see the
    **      previous note).  The Hipparcos and Tycho-2 catalogs are both
    **      (in effect) equinox J2000, but the Hipparcos epoch is 1991.25
    **      while Tycho-2 is epoch J2000;  both catalogs are supported by
    **      the present function.  If the epoch is absent, the equinox value
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
        double pr, pd, equ, epo, p, v, r, d;
        int jr, jd, jpr, jpd, jequ1, jequ2, jepo1, jepo2, jp, jv, j;


    /* Set defaults. */
        pr = 0.0;
        pd = 0.0;
        equ = 2000.0;
        epo = 0.0;
        p = 0.0;
        v = 0.0;

    /* Decode. */
        slaDafin ( string, iptr, &r, &jr );
        slaDafin ( string, iptr, &d, &jd );
        slaDfltin ( string, iptr, &pr, &jpr );
        slaDfltin ( string, iptr, &pd, &jpd );
        slaDbjin ( string, iptr, &equ, &jequ1, &jequ2 );
        slaDbjin ( string, iptr, &epo, &jepo1, &jepo2 );
        slaDfltin ( string, iptr, &p, &jp );
        slaDfltin ( string, iptr, &v, &jv );

    /* Check for omissions and errors. */
        if ( jr    > 0 ||
                jd    > 0 ||
                jpr   > 1 ||
                jpd   > 1 ||
                jequ1 > 1 ||
                jepo1 > 1 ||
                jp    > 1 ||
                jv    > 1    ) return -1;

    /* Equinox and epoch defaults. */
        if ( jepo1 > 0 ) {
            jepo2 = jequ2;
            epo = equ;
        }

    /* Results. */
        *ra = r * 15.0;
        *dec = d;
        *pmr = pr * S2R;
        *pmd = pd * AS2R;
        slaKbj ( jequ2, equ, jbeq, &j );
        *eq = equ;
        slaKbj ( jepo2, epo, jbep, &j );
        *ep = epo;
        *px = p <= 0.0 ? 0.0 : p * AS2R;
        *rv = v;

        return 0;
    }
}

