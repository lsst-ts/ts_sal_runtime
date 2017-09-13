/// \file AzElTarget.h
/// \brief Definition of the az,el target class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkAZELTARGET_H
#define tpkAZELTARGET_H

#include <stdexcept>
#include <string>

#include "TrackingTarget.h"

namespace tpk {
    class Site;
    class RefSys;

/// Az,El target
/**
    An AzElTarget object represents a topocentric Az,El.

    All the methods of this class are thread safe.
*/
    class AzElTarget : public TrackingTarget {
        public:
            AzElTarget(
                const Site& site,
                const vector& pos
            );
            AzElTarget(
                const Site& site,
                const double& t0,
                const vector& pos,
                const deltav& rate
            );
            AzElTarget(
                const Site& site,
                const double& az,
                const double& el
            );
            AzElTarget(
                const Site& site,
                const double& t0,
                const double& az,
                const double& el,
                const double& azdot,
                const double& eldot
            );
            AzElTarget(
                const Site& site,
                const std::string& starget
            );

            virtual AzElTarget* clone() const {
                return new AzElTarget(*this);
            }
            using TrackingTarget::position;
            vector position(
                const double& t,
                const RefSys& frame
            ) const;
            virtual void adjust(
                const double& t,
                const vector& tar
            );
        protected:
            vector mPositionAzEl;       ///< Az, El position
            double mT0AzEl;             ///< reference time
            deltav mVelocityAzEl;       ///< velocity
    };
}
#endif

