/// \file AutoGuider.h
/// \brief Definition of the auto-guider virtual telescope class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkAUTOGUIDER_H
#define tpkAUTOGUIDER_H

#include <stdexcept>

#include "BaseVt.h"
#include "Trajectory.h"

namespace tpk {
    class Filter2D;
    class MountVt;
    class PointingControl;
    class Transform;

/// Auto-guider virtual telescope
/**
    The auto-guider class predicts the position in the focal plane that a guide
    star should be found and adjusts the telescope pointing model (via a 
    pointing controller) on the basis of the position at which the star is 
    actually detected.

    The adjustements are first smoothes by a filter to e.g. remove noise due to
    seeing.

    All the methods of this class are thread safe.
*/
    class AutoGuider : public BaseVt {
        public:
            AutoGuider(
                const MountVt& mount,
                PointingControl& pointing,
                const Transform& trans,
                const Filter2D& xyFilter
            );
            AutoGuider(
                const AutoGuider& src
            );
            AutoGuider(
                const MountVt& mount,
                PointingControl& pointing,
                const AutoGuider& src
            );
            ~AutoGuider();
            void update() throw(std::runtime_error) {
                BaseVt::update( mMount );
            }
            int track(
                unsigned int samples
            ) throw ();
            int track(
                unsigned int samples,
                const Trajectory& rma
            ) throw ();
            Trajectory x() const throw();
            Trajectory y() const throw();
            void measure(
                const double& time,
                const double& x,
                const double& y
            );
            void guidePM(
                bool filter = true
            );
            void guideTarget();
            void reset();
            Filter2D& filter();
        protected:
            const MountVt& mMount;      ///< mount virtual telescope
            PointingControl& mPointing; ///< pointing control for guiding 
                                        ///   telescope
            Transform& mTransf;         ///< transformation from guider focal 
                                        ///   plane
            Filter2D& mXyFilter;        ///< filter for smoothing measurements
            Trajectory mX;              ///< guider x trajectory
            Trajectory mY;              ///< guider y trajectory
            Trajectory mRma;            ///< achieved rotator trajectory
        private:
    // No default constructor or assignment operator.
            AutoGuider();
            AutoGuider& operator=(const AutoGuider&);
    };
}
#endif

