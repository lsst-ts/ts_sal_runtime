/// \file TrackingTarget.h
/// \brief Definition of the tracking target class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkTRACKINGTARGET_H
#define tpkTRACKINGTARGET_H

#include "Coordinates.h"
#include "Target.h"

namespace tpk {
    class RefSys;
    class Site;

/// Virtual base class for tracking frame targets
/**
    Tracking targets are targets that can be adequately be represented by a
    position and rate in the tracking frame. If necessary the position and
    rates can be updated by implementing the update method which is called
    from the "medium" process.
*/
    class TrackingTarget : public Target {
        public:
            using Target::position;
            virtual vector position(
                const double& t
            ) const;
            virtual void update(
                const double& t
            );
            virtual TrackingTarget* clone() const = 0;
        protected:
            TrackingTarget(const Site& site) : Target(site) {};
            vector mPosition;     ///< position in tracking frame
            double mT0;           ///< reference time
            deltav mVelocity;     ///< tracking rate in tracking frame
    };
}
#endif

