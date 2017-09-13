/// \file GalacticTarget.h
/// \brief Definition of the galactic target class.

// D L Terrett
// Copyright CCLRC. All rights reserved

#ifndef tpkGALACTICTARGET_H
#define tpkGALACTICTARGET_H

#include "ICRSTarget.h"
#include "RefSys.h"
#include "Target.h"

namespace tpk {

/// Galactic coordinate target
/**
    An FK5Target object represents a fixed position in IAU 1958 galactic
    coordinates.

    All the methods of this class are thread safe.
*/
    class GalacticTarget : public ICRSTarget {
        public:
            GalacticTarget(
                const Site& site,
                const vector& pos
            );
            GalacticTarget(
                const Site& site,
                const double& l,
                const double& b
            );
            GalacticTarget(
                const Site& site,
                const std::string& starget
            );

            GalacticTarget* clone() const {
                return new GalacticTarget(*this);
            }
        private:
            void init(
                const double& l,
                const double& b
            );
    };
}
#endif

