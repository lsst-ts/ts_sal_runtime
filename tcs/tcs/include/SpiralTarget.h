/// \file SpiralTarget.h
/// \brief Definition of the spiral target class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkSPIRALTARGET_H
#define tpkSPIRALTARGET_H

#include "Target.h"

namespace tpk {

/// Spiral target.
/**
    A spiral target is a target that executes an "square" spiral around the
    position of some other target. Not something that a modern telescope
    should need but it is an illustation of how "scan patterns" of varous
    sorts can be implemented.

    The reference point for the scan (the centre in the case of a spiral) is
    another Target object so can be a moving object, a solar system body or
    even another scan.

    All the methods of this class are thread safe.
*/
    class SpiralTarget : public Target {
        public:
            SpiralTarget(
                Target& target,
                double pitch,
                double speed,
                double t0 = 0.0
            );
            void update(
                const double& t
            );
            vector position(
                const double& t
            ) const;
            vector position(
                const double& t,
                const RefSys& frame
            ) const;
            void adjust(
                const double& t,
                const vector& tar
            );
            SpiralTarget* clone() const {
                return new SpiralTarget(*this);
            }
            SpiralTarget(const SpiralTarget& src);
            void trackframe(
                const RefSys& frame
            );

        protected:
            virtual focalplane xyposition(
                double t
            ) const;
            Target* const mCentre;   ///< centre target position.
            const double mPitch;     ///< pitch of spiral
            const double mSpeed;     ///< velocity along spiral
            double mT0;              ///< start time for spiral
    };
}
#endif

