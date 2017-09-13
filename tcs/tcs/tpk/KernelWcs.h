/// \file KernelWcs.h
/// \brief Definition of the kernel world coordinate system class.

// D L Terrett
// Copyright CLRC. All rights reserved.

#ifndef tpkKERNELWCS_H
#define tpkKERNELWCS_H

#include "Wcs.h"

namespace tpk {
    class MountVt;
    class TrackRefSys;
    class Trajectory;
    class Transform;
    struct xycoord;

/// Kernel world coordinate system
/**
    A KernelWcs object is a specialised form of a World Coordinate System
    object that is initialised by transforming a grid of test points with
    tcspk to generate the transformations.
*/
    class KernelWcs : public Wcs {
        public:
            KernelWcs(
                const MountVt& mount,
                const Trajectory roll,
                const Trajectory pitch,
                const Trajectory rma,
                const Trajectory aoa,
                const Trajectory aob,
                const RefSys& refsys,
                const double& wavel,
                const Transform& trans,
                const xycoord& xy,
                const double& gridsize
            );
            
        /// Get world coordinate transformation
        /**
            \returns transformation
        */
            struct WCS GetWcs() const {
                return mWcsTrans;
            }
    };
}
#endif

