/// \file AutoGuider.cpp
/// \brief Implementation of the auto-guider virtual telescope class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "AutoGuider.h"

#include "Coordinates.h"
#include "Filter2D.h"
#include "MountVt.h"
#include "PointingControl.h"
#include "RotatorLoc.h"
#include "Site.h"
#include "Target.h"
#include "TcsLib.h"
#include "TcsMutex.h"
#include "TimeKeeper.h"
#include "Trajectory.h"
#include "Transform.h"

namespace tpk {

    extern double sampleint;

    AutoGuider::AutoGuider(
        const MountVt& mount,      ///< mount virtual telescope
        PointingControl& pointing, ///< pointing controller
        const Transform& transf,   ///< transformation from guider to focal 
                                   //   plane
        const Filter2D& xyFilter   ///< filter for x,y position
    ) :
        BaseVt(mount.mTimeKeeper, mount.mSite, *mount.mTrackFrame),
        mMount(mount),
        mPointing(pointing),
        mTransf(*transf.clone()),
        mXyFilter(*xyFilter.clone()) {};

/// Copy constructor
    AutoGuider::AutoGuider(
        const AutoGuider& src      ///< auto-guider
    ) :
        BaseVt(src.mTimeKeeper, src.mSite, src),
        mMount(src.mMount),
        mPointing(src.mPointing),
        mTransf(*src.mTransf.clone()),
        mXyFilter(*src.mXyFilter.clone())
    {
        src.mMutex.lock();
        mX = src.mX;
        mY = src.mY;
        src.mMutex.unlock();
    }

/// Copy constructor
/**
    Creates a copy of an auto-guider attached to a different mount and
    pointing controller.
*/
    AutoGuider::AutoGuider(
        const MountVt& mount,      ///< mount virtual telescope
        PointingControl& pointing, ///< pointing controller
        const AutoGuider& src      ///< auto-guider
    ) :
        BaseVt(mount.mTimeKeeper, mount.mSite, src),
        mMount(mount),
        mPointing(pointing),
        mTransf(*src.mTransf.clone()),
        mXyFilter(*src.mXyFilter.clone())
    {
        src.mMutex.lock();
        mX = src.mX;
        mY = src.mY;
        src.mMutex.unlock();
    }
    AutoGuider::~AutoGuider() {

    // Delete the tranformation.
        delete &mTransf;

    // Delete the filter.
        delete &mXyFilter;
    }

/// Predict guide star trajectory for an in-position rotator
/**
    Predicts the x,y in the guider coordinate frame of the guide star at the
    time of the last "tick" of the kernel fast loop.

    The guider prediction assumes that the rotator is at its demanded position.

    The units of the trajectories are millimeters and seconds.

    \returns status
    \retval 0 success
    \retval !=0 target cannot be imaged
*/
    int AutoGuider::track(
        unsigned int samples             ///< number of samples to generate
    ) throw () {

    // Copy rotator demand into local variables.
        mMount.mMutex.lock();
        const Trajectory rma = mMount.mRma;
        mMount.mMutex.unlock();

    // Call track with this demand.
        return track( samples, rma );
    }

/// Predict guide star position
/**
    Predicts the x,y in the guider coordinate frame of the guide star at the
    time of the last "tick" of the kernel fast loop for a rotator at the
    specified position.

    The units of the trajectories are millimeters and seconds.

    \returns status
    \retval 0 success
    \retval !=0 target cannot be imaged
*/
    int AutoGuider::track(
        unsigned int samples,            ///< number of samples to generate
        const Trajectory& rma            ///< rotator trajectory
    ) throw () {

    // Check for samples being out of range.
        samples = samples < 1 ? 1 : (samples > maxsamp ? maxsamp : samples);

    // Copy timekeeper context.
        mTimeKeeper.mMutex.lock();
        double tai = mTimeKeeper.mTai;
        double sst = mTimeKeeper.mSst;
        double cst = mTimeKeeper.mCst;
        double dsst = mTimeKeeper.mDsst;
        double dcst = mTimeKeeper.mDcst;
        mTimeKeeper.mMutex.unlock();

    // Copy mount context into local variables.
        mMount.mMutex.lock();
        const Trajectory roll = mMount.mRoll;
        const Trajectory pitch = mMount.mPitch;
        const double ia = mMount.mIa;
        const double ib = mMount.mIb;
        const double np = mMount.mNp;
        const vector tel = mMount.mTelVec;
        const double ga = mMount.mGa;
        const double gb = mMount.mGb;
        const Trajectory aoa = mMount.mAoa;
        const Trajectory aob = mMount.mAob;
        mMount.mMutex.unlock();

    // Copy guider context into local variables.
        mMutex.lock();
        KernelRefSys::Ptr kernelTF(mKernelTF->clone());
        mMutex.unlock();

    // Predict x,y in focal plane.
        vector tar[maxsamp];
        instrcoord xy[maxsamp];
        double xsamp[maxsamp], ysamp[maxsamp];
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

        // Collimation changes from AO and guiding at this time
            double ca = ga + aoa.sample(t);
            double cb = gb + aob.sample(t);

        // Target position in focal plane.
            focalplane f;
            stat = kernelTF->vtxy( tar[i], sstt, cstt,
                    mMount.mRotloc, rma.sample(t),roll.sample(t), 
                    pitch.sample(t), ia, ib, np, tel, ca, cb, f);
            if ( stat ) break;

        // Transform into the guider coordinate system.
            xy[i] = mTransf.back(f);

        // Copy samples.
            xsamp[i] = xy[i].x;
            ysamp[i] = xy[i].y;
        }

    // Compute trajectories
        Trajectory x, y;
        if ( stat == 0 ) {
            x = Trajectory(tai, t1, t2 - t1, samples, xsamp);
            y = Trajectory(tai, t1, t2 - t1, samples, ysamp);
        }

    // Store in context.
        mMutex.lock();
        if ( stat == 0 ) {
            mX = x;
            mY = y;
        }
        mPosition = tar[ntai];
        mImxy = xy[ntai];
        mTai = tai;
        mSst = sst;
        mCst = cst;
        mRma = rma;
        mMutex.unlock();

        return stat;
    }

/// Get x demand trajectory calculated by track
/**
    \returns X coordinate trajectory
*/
    Trajectory AutoGuider::x() const throw () {
        mMutex.lock();
        const Trajectory x = mX;
        mMutex.unlock();
        return x;
    }

/// Get y demand trajectory calculated by track
/**
    \returns Y coordinate trajectory
*/
    Trajectory AutoGuider::y() const throw () {
        mMutex.lock();
        const Trajectory y = mY;
        mMutex.unlock();
        return y;
    }

/// Updates measured position of guide star.
/**
    The difference between the measured position and the predicted position
    at that time is pushed into the filter.
*/
    void AutoGuider::measure(
        const double& t,        ///< TAI of measurement (MJD)
        const double& xm,       ///< measured x position (guider coordinates)
        const double& ym        ///< measured y position (guider coordinates)
    ) {

    // Get x,y and rotator trajectories from guider context.
        mMutex.lock();
        const Trajectory x = mX;
        const Trajectory y = mY;
        const Trajectory rma = mRma;
        mMutex.unlock();

    // Transform measured x,y into focal plane.
        focalplane meas = mTransf.forward(instrcoord(xm, ym));

    // Transform predicted x,y into focal plane.
        focalplane pred = mTransf.forward(instrcoord(x.sample(t), y.sample(t)));

    // Push x,y error into filter and save rotator trajectory.
        mMutex.lock();
        mXyFilter << pred - meas;
        mRma = rma;
        mMutex.unlock();
    }

/// Guide target position
/**
    Updates the target position from the x,y measured by the guider.
*/
void AutoGuider::guideTarget() {

    // Copy kernel context into local variables.
        mTimeKeeper.mMutex.lock();
        double tai = mTimeKeeper.mTai;
        double sst = mTimeKeeper.mSst;
        double cst = mTimeKeeper.mCst;
        mTimeKeeper.mMutex.unlock();
        mMount.mMutex.lock();
        const Trajectory roll = mMount.mRoll;
        const Trajectory pitch = mMount.mPitch;
        const double ia = mMount.mIa;
        const double ib = mMount.mIb;
        const double np = mMount.mNp;
        const vector tel = mMount.mTelVec;
        const double ga = mMount.mGa;
        const double gb = mMount.mGb;
        const Trajectory aoa = mMount.mAoa;
        const Trajectory aob = mMount.mAob;
        mMount.mMutex.unlock();

    // Copy guider context into local variables.
        mMutex.lock();
        focalplane error = mXyFilter.value();
        const Trajectory rma = mRma;
        const Trajectory x = mX;
        const Trajectory y = mY;
        KernelRefSys::ConstPtr kernelTF(mKernelTF->clone());
        mMutex.unlock();

    // Collimation changes from AO and guiding at this time
        double ca = ga + aoa.sample(tai);
        double cb = gb + aob.sample(tai);

    // Transform predicted x,y into focal plane.
        focalplane pred = mTransf.forward(instrcoord(x.sample(tai), 
                y.sample(tai)));

    // Convert measured position to RA, Dec.
        vector tar = kernelTF->vtsky( roll.sample(tai), pitch.sample(tai),
                mMount.mRotloc, rma.sample(tai), pred - error,
                    sst, cst, ia, ib, np, tel, ca, cb);

    // Update target.
        mMutex.lock();
        mTarget->adjust(tai, tar);
        mMutex.unlock();
    }

/// Guide the telescope by adjusting the pointing model
/**
    The current value of the filter is applied to the pointing
    controller.
*/
    void AutoGuider::guidePM(
        bool filter        ///< Apply mount axes filters
    ) {
        mMutex.lock();
        focalplane error = mXyFilter.value();
        const Trajectory rma = mRma;
        mMutex.unlock();

    // Update the guiding through filters.
        if (filter) {
            mPointing.guide(error, rma);

    // Or directly.
        } else {
            mPointing.adjustGuide(error, rma);
        }
    }
    
/// Reset the filter
    void AutoGuider::reset() {
        mXyFilter.reset();
    };

/// Get reference to filter
/**
    Filter2D is a polymorphic type so it is up to the caller to cast the
    reference to the correct type before using any of its methods.
*/
    Filter2D& AutoGuider::filter() {
        return mXyFilter;
    };
}

