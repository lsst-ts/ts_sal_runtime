/// \file OpticsVt.h
/// \brief Definition of the optics virtual telescope class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkOPTICSVT_H
#define tpkOPTICSVT_H

#include <stdexcept>

#include "BaseVt.h"
#include "Target.h"
#include "TcsMutex.h"
#include "Trajectory.h"

namespace tpk {
    class MountVt;

/// Tip/tilt optics virtual telescope
/**
    An OpticsVt object generates an tip/tilt demand for steerable optics from
    a target and wavelength and the roll and pitch of the mount. It can be
    used, for example, to generate chop throws for a chopping M2 or M1 tip
    and tilt for a telescope with more than one optical telescope assembly
    attached to a single mount.

    All the methods of this class are thread safe.
*/
    class OpticsVt : public BaseVt {
        public:
            OpticsVt(
                const MountVt& mount
            );
            OpticsVt(const OpticsVt&);
            OpticsVt(
                const MountVt& mount,
                const OpticsVt& src
            );

/// Update the sky patch matrices.
/**
    Updates the sky patch matrices from the current target and weather
    information.

    \exception std::runtime_error
*/
            void update() throw(std::runtime_error) {
                BaseVt::update( mMount );
            }
            int track(
                unsigned int samples,
                const Trajectory& roll,
                const Trajectory& pitch,
                const Trajectory& rma
            ) throw ();
            int track(
                unsigned int samples,
                const Trajectory& rma
            ) throw ();
            int track(
                unsigned int samples,
                const Trajectory& roll,
                const Trajectory& pitch
            ) throw ();
            int track(
                unsigned int samples
            ) throw ();
            Trajectory tip() const throw();
            Trajectory tilt() const throw();
        protected:
            const MountVt& mMount;          ///< Mount virtual telescope
            Trajectory mTip;                ///< predicted tip trajectory
            Trajectory mTilt;               ///< predicted tilt trajectory
        private:
        // There is no default constructor or assignment op.
            OpticsVt();
            OpticsVt& operator=(const OpticsVt&);
    };
}
#endif

