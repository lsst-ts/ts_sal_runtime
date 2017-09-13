/// \file PointingControl.cpp
/// \brief Implementation of the PointingControl class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "PointingControl.h"

#include "Filter.h"
#include "MountVt.h"
#include "TcsLib.h"
#include "Trajectory.h"

namespace tpk {
/**
    The new PointingControl object as all pointing offsets set to zero.
*/
    PointingControl::PointingControl(
        MountVt& mount,      ///< mount to be guided
        Filter& rollFilter,  ///< filter for roll axis adjustments
        Filter& pitchFilter  ///< filter for pitch axis adjustments
    ) : mMount(mount),
        mRollFilter(rollFilter),
        mPitchFilter(pitchFilter),
        mAGuide(0.0),
        mBGuide(0.0),
        mALocal(0.0),
        mBLocal(0.0) {
    }

/// Update guiding
/**
    Any auto-guider adjustment is leaked into the guide level and
    the net guiding adjustment (the sum of all the levels) applied
    to the mount virtual telescope.
*/
    void PointingControl::update() {
        mMutex.lock();
        double a = mALocal + (mRollFilter << mAGuide);
        double b = mBLocal + (mPitchFilter << mBGuide);
        mMutex.unlock();
        mMount.setGuide(a, b);
    }

/// Set guiding adjustments.
/**
    Set the guiding adjustments to an x,y in the focal plane of a rotator
    at the specified focus and mechanical angle.
*/
    void PointingControl::setGuide(
        const focalplane& xy,          ///< adjustment in focal plane
        const Trajectory& rma,         ///< rotator mechanical angle
        const TcsLib::rotloc& rotl     ///< rotator location
    ) {

        // Copy mount context into local variables.
        mMount.mMutex.lock();
        const double t = mMount.mTai;
        const Trajectory roll = mMount.mRoll;
        const Trajectory pitch = mMount.mPitch;
        mMount.mMutex.unlock();

    // Rotate xy into xi, eta
        focalplane g = TcsLib::xy2xe( xy, rotl, rma.sample(t),
                roll.sample(t), pitch.sample(t));

    // Update guiding.
        mMutex.lock();
        mAGuide = g.xi;
        mBGuide = g.eta;
        mRollFilter.reset(mAGuide);
        mPitchFilter.reset(mBGuide);
        mMutex.unlock();
    }

/// Set guiding adjustments.
/**
    Set the guiding adjustments to an x,y in the focal plane of the rotator
    at the specified mechanical angle.
*/
    void PointingControl::setGuide(
        const focalplane& xy,            ///< focal plane adjustment
        const Trajectory& rma            ///< rotator mechanical angle
    ) {
        setGuide( xy, rma, mMount.mRotloc );
    }

/// Set guiding adjustments.
/**
    Set the guiding adjustments to an x,y in the focal plane of the rotator.
*/
    void PointingControl::setGuide(
        const focalplane& xy             ///< focal plane adjustment
    ) {
        mMount.mMutex.lock();
        const Trajectory rma = mMount.mRma;
        mMount.mMutex.unlock();
        setGuide( xy, rma, mMount.mRotloc );
    }

/// Increment guiding adjustments.
/**
    Increment the guiding adjustments by an x,y in the focal plane of the
    rotator at the specified mechanical angle and location.
*/
    void PointingControl::adjustGuide(
        const focalplane& xy,            ///< adjustment in focal plane
        const Trajectory& rma,           ///< rotator mechanical angle
        const TcsLib::rotloc& rotl       ///< rotator location
    ) {

        // Copy mount context into local variables.
        mMount.mMutex.lock();
        const double t = mMount.mTai;
        const Trajectory roll = mMount.mRoll;
        const Trajectory pitch = mMount.mPitch;
        mMount.mMutex.unlock();

    // Rotate xy into xi, eta
        focalplane g = TcsLib::xy2xe( xy, rotl, rma.sample(t),
                roll.sample(t), pitch.sample(t));

    // Update guiding.
        mMutex.lock();
        mAGuide += g.xi;
        mBGuide += g.eta;
        mRollFilter.reset(mAGuide);
        mPitchFilter.reset(mBGuide);
        mMutex.unlock();
    }

/// Increment guiding adjustments.
/**
    Increment the guiding adjustments by an x,y in the focal plane of the
    rotator at the specified mechanical angle.
*/
    void PointingControl::adjustGuide(
        const focalplane& xy,            ///< focal plane adjustment
        const Trajectory& rma            ///< rotator mechanical angle
    ) {
        adjustGuide( xy, rma, mMount.mRotloc );
    }

/// Increment guiding adjustments.
/**
    Increment the guiding adjustments by an x,y in the focal plane of a
    rotator at the specified focus and mechanical angle.
*/
    void PointingControl::adjustGuide(
        const focalplane& xy             ///< focal plane adjustment
    ) {
        mMount.mMutex.lock();
        const Trajectory rma = mMount.mRma;
        mMount.mMutex.unlock();
        adjustGuide( xy, rma, mMount.mRotloc );
    }

/// Set local adjustments.
/**
    Set the local adjustments to an x,y in the focal plane of a rotator
    at the specified focus and mechanical angle.
*/
    void PointingControl::setLocal(
        const focalplane& xy,          ///< adjustment in focal plane
        const Trajectory& rma,        ///< rotator mechanical angle
        const TcsLib::rotloc& rotl    ///< rotator location
    ) {

        // Copy mount context into local variables.
        mMount.mMutex.lock();
        const double t = mMount.mTai;
        const Trajectory roll = mMount.mRoll;
        const Trajectory pitch = mMount.mPitch;
        mMount.mMutex.unlock();

    // Rotate xy into xi, eta
        focalplane g = TcsLib::xy2xe( xy, rotl, rma.sample(t),
                roll.sample(t), pitch.sample(t));

    // Update local.
        mMutex.lock();
        mALocal = g.xi;
        mBLocal = g.eta;
        mRollFilter.reset(mAGuide);
        mPitchFilter.reset(mBGuide);
        mMutex.unlock();
    }

/// Set local adjustments.
/**
    Set the local adjustments to an x,y in the focal plane of the rotator
    at the specified mechanical angle.
*/
    void PointingControl::setLocal(
        const focalplane& xy,            ///< focal plane adjustment
        const Trajectory& rma            ///< rotator mechanical angle
    ) {
        setLocal( xy, rma, mMount.mRotloc );
    }

/// Set local adjustments.
/**
    Set the local adjustments to an x,y in the focal plane of the rotator.
*/
    void PointingControl::setLocal(
        const focalplane& xy             ///< focal plane adjustment
    ) {
        mMount.mMutex.lock();
        const Trajectory rma = mMount.mRma;
        mMount.mMutex.unlock();
        setLocal( xy, rma, mMount.mRotloc );
    }

/// Increment local adjustments.
/**
    Increment the local adjustments by an x,y in the focal plane of the
    rotator at the specified mechanical angle and location.
*/
    void PointingControl::adjustLocal(
        const focalplane& xy,            ///< adjustment in focal plane
        const Trajectory& rma,           ///< rotator mechanical angle
        const TcsLib::rotloc& rotl       ///< rotator location
    ) {

        // Copy mount context into local variables.
        mMount.mMutex.lock();
        const double t = mMount.mTai;
        const Trajectory roll = mMount.mRoll;
        const Trajectory pitch = mMount.mPitch;
        mMount.mMutex.unlock();

    // Rotate xy into xi, eta
        focalplane g = TcsLib::xy2xe( xy, rotl, rma.sample(t),
                roll.sample(t), pitch.sample(t));

    // Update local.
        mMutex.lock();
        mALocal += g.xi;
        mBLocal += g.eta;
        mRollFilter.reset(mAGuide);
        mPitchFilter.reset(mBGuide);
        mMutex.unlock();
    }

/// Increment local adjustments.
/**
    Increment the local adjustments by an x,y in the focal plane of the
    rotator at the specified mechanical angle.
*/
    void PointingControl::adjustLocal(
        const focalplane& xy,            ///< focal plane adjustment
        const Trajectory& rma            ///< rotator mechanical angle
    ) {
        adjustLocal( xy, rma, mMount.mRotloc );
    }

/// Increment local adjustments.
/**
    Increment the local adjustments by an x,y in the focal plane of a
    rotator at the specified focus and mechanical angle.
*/
    void PointingControl::adjustLocal(
        const focalplane& xy             ///< focal plane adjustment
    ) {
        mMount.mMutex.lock();
        const Trajectory rma = mMount.mRma;
        mMount.mMutex.unlock();
        adjustLocal( xy, rma, mMount.mRotloc );
    }

/// Absorb adjustments.
    void PointingControl::absorb() {
        mMutex.lock();
        mALocal += mAGuide;
        mBLocal += mBGuide;
        mAGuide = 0.0;
        mBGuide = 0.0;
        mRollFilter.reset(0.0);
        mPitchFilter.reset(0.0);
        mMutex.unlock();
    }

/// Guide
/**
    Guide the telescope by filtering adjustments from a guider mounted
    on a rotator at the specified mechanical angle and location
    into the pointing model.
*/
    void PointingControl::guide(
        const focalplane& xy,            ///< adjustment in focal plane
        const Trajectory& rma,           ///< rotator mechanical angle
        const TcsLib::rotloc& rotl       ///< rotator location
    ) {

    // Copy mount context into local variables.
        mMount.mMutex.lock();
        const double t = mMount.mTai;
        const Trajectory roll = mMount.mRoll;
        const Trajectory pitch = mMount.mPitch;
        mMount.mMutex.unlock();

    // Rotate xy into xi, eta
        focalplane g = TcsLib::xy2xe( xy, rotl, rma.sample(t),
                roll.sample(t), pitch.sample(t));

    // Update guiding.
        mMutex.lock();
        mAGuide = g.xi + mRollFilter.value();
        mBGuide = g.eta + mPitchFilter.value();
        mMutex.unlock();
    }

/// Guide
/**
    Guide the telescope by filtering adjustments from a guider mounted
    on the rotator at the specified rotator mechanical angle into the
    pointing model.
*/
    void PointingControl::guide(
        const focalplane& xy,            ///< focal plane adjustment
        const Trajectory& rma            ///< rotator mechanical angle
    ) {
        guide( xy, rma, mMount.mRotloc );
    }

/// Guide
/**
    Guide the telescope by filtering adjustments from a guider mounted
    on the rotator into the pointing model.
*/
    void PointingControl::guide(
        const focalplane& xy             ///< focal plane adjustment
    ) {
        mMount.mMutex.lock();
        const Trajectory rma = mMount.mRma;
        mMount.mMutex.unlock();
        guide( xy, rma, mMount.mRotloc );
    }


/// Get guide adjustments.
    focalplane PointingControl::getGuide() {
        mMutex.lock();
        focalplane guide(mAGuide, mBGuide);
        mMutex.unlock();
        return guide;
    }

/// Get local adjustments.
    focalplane PointingControl::getLocal() {
        mMutex.lock();
        focalplane local(mALocal, mBLocal);
        mMutex.unlock();
        return local;
    }
}

