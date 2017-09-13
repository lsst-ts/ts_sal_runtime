/// \file GalacticTarget.cpp
/// \brief Implementation of the galactic target class.

#include "GalacticTarget.h"

#include <cstdio>
#include "slalib.h"

#include "GalacticRefSys.h"
#include "ICRefSys.h"
#include "ICRSTarget.h"

/*
    A simple (if you have slalib to hand) conversion exists between galactic
    coordinate and ICRS so the constructors simply store the ICRS position
    and the position method just does the reverse transformation. The position
    in galactic coordinates isn't actually stored.

    Convertion to other coordinate systems is handled by the position method
    of the ICRSTarget class.
*/

namespace tpk {
/// Constructor from a vector position.
    GalacticTarget::GalacticTarget(
        const Site& site,                ///< telescope site
        const vector& pos                ///< target position
    ) : ICRSTarget(site, 0.0, 0.0) {
        spherical s = pos;
        init(s.a, s.b);
    }

/// Constructor from a longitude and latitude.
    GalacticTarget::GalacticTarget(
        const Site& site,                ///< telescope site
        const double& l,                 ///< galactic longitude (radians)
        const double& b                  ///< galactic latitude (radians)
    ) : ICRSTarget(site, 0.0, 0.0) {
        init(l, b);
    }

/// Constuctor from a string.
    GalacticTarget::GalacticTarget(
        const Site& site,              ///< telescope site
        const std::string& starget     ///< target position in degrees.
    ) : ICRSTarget(site, 0.0, 0.0)
    {

    // Decode the string.
        double l, b;
        if ( sscanf( starget.c_str(), "%lf %lf", &l, &b) != 2 ) {
            throw std::runtime_error("Unable to decode target");
        }
        init(l * TcsLib::d2r, b * TcsLib::d2r);
    }

// Store position in ICRS.
    void GalacticTarget::init(
        const double& l,
        const double& b
    ) {

    // Convert to ICRS.
        double ra, dec;
        slaGaleq( l, b, &ra, &dec );
        vector pos(ra, dec);

    // Store in member variables.
        mMutex.lock();
        mPositionICRS = pos;
        mMutex.unlock();
    }
}

