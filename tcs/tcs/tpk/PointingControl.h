/// \file PointingControl.h
/// \brief Definition of the PointingControl class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkPOINTINGCONTROL_H
#define tpkPOINTINGCONTROL_H

#include "TcsMutex.h"
#include "Coordinates.h"
#include "TcsLib.h"

namespace tpk {
    class Filter;
    class MountVt;
    class Trajectory;

/// Pointing controller
/**
    A pointing control object manages pointing corrections from
    auto-guiders and handsets. The guiding corrections applied to
    the mount consists of two levels.

    - The "local" adjustment that applies to a small area of sky around the
        current target perhaps determined by pointing at a nearby astrometric
        reference star.
    - The "guiding" adjustment coming from an auto-guider active optics system.

    Adjustments can be "absorbed" from guiding to local. I.e. the guide values
    are added to local and guide set to zero so that the net pointing
    adjustment remains the same.

    The filter objects must not be destroyed during the lifetime of the
    PointingControl object.

    All the methods of this class are thread safe.
*/
    class PointingControl {
        public:
            PointingControl(
                MountVt& mount,
                Filter& rollFilter,
                Filter& pitchFilter
            );
            void update();
            void absorb();
            void adjustGuide(
                const focalplane& xy
            );
            void adjustGuide(
                const focalplane& xy,
                const Trajectory& rma
            );
            void adjustGuide(
                const focalplane& xy,
                const Trajectory& rma,
                const TcsLib::rotloc& rotl
            );
            void setGuide(
                const focalplane& xy
            );
            void setGuide(
                const focalplane& xy,
                const Trajectory& rma
            );
            void setGuide(
                const focalplane& xy,
                const Trajectory& rma,
                const TcsLib::rotloc& rotl
            );
            focalplane getGuide();
            void adjustLocal(
                const focalplane& xy
            );
            void adjustLocal(
                const focalplane& xy,
                const Trajectory& rma
            );
            void adjustLocal(
                const focalplane& xy,
                const Trajectory& rma,
                const TcsLib::rotloc& rotl
            );
            void setLocal(
                const focalplane& xy
            );
            void setLocal(
                const focalplane& xy,
                const Trajectory& rma
            );
            void setLocal(
                const focalplane& xy,
                const Trajectory& rma,
                const TcsLib::rotloc& rotl
            );
            focalplane getLocal();
            void guide (
                const focalplane& xy
            );
            void guide (
                const focalplane& xy,
                const Trajectory& rma
            );
            void guide (
                const focalplane& xy,
                const Trajectory& rma,
                const TcsLib::rotloc& rotl
            );
        /// Get roll filter
        /**
            \returns roll filter
        */
            Filter& rollFilter() const {
                return mRollFilter;
            }

        /// Get pitch filter
        /**
            \returns pitch filter
        */
            Filter& pitchFilter() const {
                return mPitchFilter;
            }
        protected:
            MountVt& mMount;         ///< mount virtual telescope
            Filter& mRollFilter;     ///< filter for roll axis
            Filter& mPitchFilter;    ///< filter for pitch axis
            TcsMutex mMutex;         ///< mutex
            double mAGuide;          ///< guide correction in roll
            double mBGuide;          ///< guide correction in pitch
            double mALocal;          ///< local correction in roll
            double mBLocal;          ///< local correction in pitch
        private:
        // There is no default constructor.
            PointingControl();
    };
}
#endif

