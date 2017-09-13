/// \file OpticsVt.cpp
/// \brief Implementation of the optics virtual telescope class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "OpticsVt.h"

#include "slalib.h"

#include "Coordinates.h"
#include "MountVt.h"
#include "PointingOrigin.h"
#include "TimeKeeper.h"
#include "TcsLib.h"
#include "TcsMutex.h"
#include "Trajectory.h"

namespace tpk {

    extern double sampleint;

    OpticsVt::OpticsVt(
        const MountVt& mount         ///< mount virtual telescope
    ) :
        BaseVt(mount.mTimeKeeper, mount.mSite, *mount.mTrackFrame),
        mMount(mount)
    {

    // Initialise the SPMs
        update();
    };
    OpticsVt::OpticsVt(
        const OpticsVt& src
    ) :
        BaseVt(src.mTimeKeeper, src.mSite, src),
        mMount(src.mMount)
    {
        src.mMutex.lock();
        mTip = src.mTip;
        mTilt = src.mTilt;
        src.mMutex.unlock();
    }

/**
    Creates a copy of an optics virtual telescope attached to a different mount.
*/
    OpticsVt::OpticsVt(
        const MountVt& mount,      ///< mount virtual telescope
        const OpticsVt& src
    ) :
        BaseVt(mount.mTimeKeeper, mount.mSite, src),
        mMount(mount)
    {
        src.mMutex.lock();
        mTip = src.mTip;
        mTilt = src.mTilt;
        src.mMutex.unlock();
    }

/// Calculate optics tip/tilt trajectory
/*
    Predicts the optics tip and tilt required to track the target for a
    specified mount roll, pitch and rotator trajectories.

    \returns status
    \retval 0 success
    \retval !=0 target cannot be imaged
*/
    int OpticsVt::track(
        unsigned int samples,         ///< number of samples to generate
        const Trajectory& roll,       ///< roll trajectory
        const Trajectory& pitch,      ///< pitch trajectory
        const Trajectory& rma         ///< rotator trajectory
    ) throw ()
    {

    // Check for samples being out of range.
        samples = samples < 1 ? 1 : (samples > maxsamp ? maxsamp : samples);

    // Copy time context.
        mTimeKeeper.mMutex.lock();
        double tai = mTimeKeeper.mTai;
        double sst = mTimeKeeper.mSst;
        double cst = mTimeKeeper.mCst;
        double dsst = mTimeKeeper.mDsst;
        double dcst = mTimeKeeper.mDcst;
        mTimeKeeper.mMutex.unlock();

    // Copy mount context into local variables.
        mMount.mMutex.lock();
        const double ia = mMount.mIa;
        const double ib = mMount.mIb;
        const double np = mMount.mNp;
        const vector tel = mMount.mTelVec;
        const double ga = mMount.mGa;
        const double gb = mMount.mGb;
        mMount.mMutex.unlock();

        mMutex.lock();
        KernelRefSys::ConstPtr kernelTF(mKernelTF->clone());
        mMutex.unlock();

    // Predict x,y in focal plane.
        vector tar[maxsamp];
        focalplane tt[maxsamp], xe2[maxsamp];
        double xsamp[maxsamp], esamp[maxsamp];
        int stat = 0;

    // Sample that corresponds to the timestamp. Either the middle sample (if
    // samples is odd) or the one before the middle (if samples is even).
        int ntai = (samples - 1)/2;

    // Time for first sample.
        double t1 = tai - sampleint * ntai;

    // Time for second sample.
        double t2 = t1 + sampleint;

        for (unsigned int i = 0; i < samples; i++) {

        // Time for this sample.
            double t = t1 + sampleint * i;

        // sine and cosine of sidereal time.
            double sstt = sst + dsst * (t - tai);
            double cstt = cst + dcst * (t - tai);

        // target position at this time.
            tar[i] = targetpos(t, sstt, cstt);

        // Transform target to xi, eta in the focal plane. The existing AO
        // collimation is not used so that the result is the absolute correction
        // required to put the target on the pointing origin.
            focalplane xe1;
            stat = kernelTF->vtxe( tar[i], sstt, cstt, roll.sample(t), 
                    pitch.sample(t), ia, ib, np, tel, ga, gb, xe1);
            if ( stat ) break;

        // Pointing origin at this time.
            focalplane po = mPO->xy(t);

        // Rotate into xi, eta.
            xe2[i] = TcsLib::xy2xe( po,  mMount.mRotloc, rma.sample(tai),
                    roll.sample(tai), pitch.sample(tai));

        // Difference is the required xi,eta displacement from the optics.
            tt[i] = xe1 - xe2[i];

        // Add the current tip/tilt at this time.
            xsamp[i] = tt[i].xi;
            esamp[i] = tt[i].eta;
        }

    // Compute trajectories
        Trajectory tip, tilt;
        if ( stat == 0 ) {
            tip = Trajectory(tai, t1, t2 - t1, samples, xsamp);
            tilt = Trajectory(tai, t1, t2 - t1, samples, esamp);
        }

    // Store in context.
        mMutex.lock();
        if ( stat == 0 ) {
            mTip = tip;
            mTilt = tilt;
        }
        mPosition = tar[ntai];
        mImxy = xe2[ntai];
        mTai = tai;
        mSst = sst;
        mCst = cst;
        mMutex.unlock();

        return stat;
    }

/// Calculate optics tip and tilt trajectories.
/**
    The mount and rotator are assumed to be at their last demand positions.

    \returns status
    \retval 0 success
    \retval !=0 target cannot be imaged
*/
    int OpticsVt::track(
        unsigned int samples,         ///< number of samples to generate
        const Trajectory& rma         ///< rotator trajectory
    ) throw () {

    // Copy mount trajectory.
        mMount.mMutex.lock();
        const Trajectory roll = mMount.mRoll;
        const Trajectory pitch = mMount.mPitch;
        mMutex.unlock();

    // Call track.
        return track(samples, roll, pitch, rma);
    }

/// Calculate optics tip and tilt trajectories.
/**
    The rotator is assumed to be at it last demand position.

    \returns status
    \retval 0 success
    \retval !=0 target cannot be imaged
*/
    int OpticsVt::track(
        unsigned int samples,         ///< number of samples to generate
        const Trajectory& roll,       ///< roll trajectory
        const Trajectory& pitch       ///< pitch trajectory
    ) throw () {

    // Copy mount trajectory.
        mMount.mMutex.lock();
        const Trajectory rma = mMount.mRma;
        mMount.mMutex.unlock();

    // Call track.
        return track(samples, roll, pitch, rma);
    }

/// Calculate optics tip and tilt trajectories.
/**
    The mount and rotator are assumed to be at their last demand positions.

    \returns status
    \retval 0 success
    \retval !=0 target cannot be imaged
*/
    int OpticsVt::track(
        unsigned int samples          ///< number of samples to generate
    ) throw () {

    // Copy mount trajectory.
        mMount.mMutex.lock();
        const Trajectory roll = mMount.mRoll;
        const Trajectory pitch = mMount.mPitch;
        const Trajectory rma = mMount.mRma;
        mMount.mMutex.unlock();

    // Call track.
        return track(samples, roll, pitch, rma);
    }

/// Get last xi demand calculated by track,
/**
    The units of the trajectory are radians and days.

    \returns xi coordinate trajectory
*/
    Trajectory OpticsVt::tip() const throw () {
        mMutex.lock();
        const Trajectory tip = mTip;
        mMutex.unlock();
        return tip;
    }

/// Get last eta demand calculated by track
/**
    The units of the trajectory are radians and days.

    \returns eta coordinate trajectory
*/
    Trajectory OpticsVt::tilt() const throw () {
        mMutex.lock();
        const Trajectory tilt = mTilt;
        mMutex.unlock();
        return tilt;
    }
}

