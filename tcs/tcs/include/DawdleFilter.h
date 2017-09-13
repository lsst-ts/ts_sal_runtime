/// \file DawdleFilter.h
/// \brief Definition of the DawdleFilter class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkDAWDLEFILTER_H
#define tpkDAWDLEFILTER_H

#include "Coordinates.h"

namespace tpk {

/// Dawdle mode filter
/**
    A DawdleFilter is used to implement "dawdle mode" where telescope movements
    that cause the image to move in the focal plane are filtered so that
    mechanisms like guiders and active optics sensors can track the movement
    of the image. This allows offsets to be performed without having to open
    guider and active optics loops.

    In this implementation the filtering is achieved by limiting the rate of
    change of both the target positon and the pointing origin. The tuning
    parameter is simply the maximum change (in radians per day).

    The target position and pointing origin change are limited independently
    so in the worst case the image in the focal plane could move at twice
    the limiting velocity.
*/
    class DawdleFilter {
        public:
            DawdleFilter(
                double tunepar = 0.0                ///< tuning parameter
            ) : mTunePar(tunepar), mBypass(true) {};
            double tune(
                const double& tunepar
            );
            bool bypass(
                const bool& bypass
            );
            bool limit(
                const double& t,
                const vector& inTarget,
                const focalplane& inPo,
                vector& outTarget,
                focalplane& outPo
            );
        protected:
            double mTunePar;      ///< tuning parameter (maximum velocity)
            bool mBypass;         ///< bypass flag
            double mT;            ///< last time filter ran
            vector mTarget;       ///< target position last time
            focalplane mPO;       ///< pointing origin last time
    };
}
#endif

