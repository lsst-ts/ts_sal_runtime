/// \file BaseVt.cpp
/// \brief Implementation of the BaseVt class

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "BaseVt.h"

#include <memory>
#include "slalib.h"

#include "Coordinates.h"
#include "ICRSTarget.h"
#include "MountVt.h"
#include "PointingOrigin.h"
#include "KernelRefSys.h"
#include "Site.h"
#include "Target.h"
#include "TcsLib.h"
#include "TcsMutex.h"
#include "TimeKeeper.h"

namespace tpk {

    extern double sampleint;
    extern double wavelr;
    extern double tlr;

/**
    The newly created BaseVt object has the target set to 0.0, 0.0 in the
    tracking frame and the pointing origin to the rotator axis.
*/
    BaseVt::BaseVt(
        const TimeKeeper& ticker,     ///< time keeper
        const Site& site,             ///< telescope site
        const RefSys& trackFrame      ///< tracking frame
    ) :
        mTimeKeeper(ticker),
        mSite(site),
        mKernelTF(trackFrame.kernelRefSys()),
        mTrackFrame(trackFrame.clone()),
        mNewTarget(false),
        mWavel(wavelr),
        mKernelOF(trackFrame.kernelRefSys()),
        mOffsetFrame(trackFrame.clone()),
        mTai(0.0),
        mSst(1.0),
        mCst(0.0)
    {

    // Create a default target.
        mTarget.reset(new ICRSTarget(mSite, 0.0, 0.0));
        mTarget->trackframe(*mTrackFrame);

    // Create an on-axis pointing origin.
        mPO.reset(new PointingOrigin(0.0, 0.0));
    }

/**
    The copy constructor makes a copy of the context protected
    by a the source mutex.
*/
    BaseVt::BaseVt(
        const TimeKeeper& ticker,   ///< timekeeper
        const Site& site,           ///< site
        const BaseVt& src           ///< source BaseVt
    ) :
        mTimeKeeper(ticker),
        mSite(site)
    {
    // Lock the source context.
        src.mMutex.lock();

    // Copy the context.
        mKernelTF.reset(src.mKernelTF->clone());
        mTrackFrame.reset(src.mTrackFrame->clone());
        mKernelOF.reset(src.mKernelOF->clone());
        mOffsetFrame.reset(src.mOffsetFrame->clone());
        mNewTarget = src.mNewTarget;
        mTarget.reset(src.mTarget->clone());
        mWavel = src.mWavel;
        mPO.reset(src.mPO->clone());
        mPosition = src.mPosition;
        mImxy = src.mImxy;
        mOffset = src.mOffset;
        mTemp = src.mTemp;
        mPress = src.mPress;
        mHumid = src.mHumid;
        mTLR = src.mTLR;
        mTai = src.mTai;
        mSst = src.mSst;
        mCst = src.mCst;

    // Release the source context.
        src.mMutex.unlock();
    }

/// Set new target
/**
    \exception std::runtime_error
*/
    void BaseVt::newTarget(
        const Target& target       ///< new target
    ) throw(std::runtime_error) {

    // Make a copy of the new target.
        Target* newTarget = target.clone();

    // Set the target's tracking frame.
        newTarget->trackframe(*mTrackFrame);

    // Store the new target in the context.
        mMutex.lock();
        mTarget.reset(newTarget);
        mNewTarget = true;
        mMutex.unlock();

    // Update the SPMs.
        update();
    }

/// Set new pointing origin
    void BaseVt::newPointingOrigin(
        const PointingOrigin& po      ///< new pointing origin
    ) throw () {

    // Make a copy of the pointing origin.
        PointingOrigin* newPo = po.clone();

    // Store a pointer to the new pointing origin in the context.
        mMutex.lock();
        mPO.reset(newPo);
        mMutex.unlock();
    }

/// Set effective wavelength
    void BaseVt::setWavelength(
        const double &wavelength       ///< wavelength (microns)
    ) throw() {

    // Store the new wavelength.
        mMutex.lock();
        mNewTarget = true;
        mWavel = wavelength;
        mMutex.unlock();

    // Update the SPMs.
        update();
    }

/// Update target and reference frames
/**
    The target is updated and copies of the tracking and offset reference
    frames updated. If a new target has not been set while this method
    was executing the updates reference frames are copied back into the
    virtual telescope context.

    \exception std::runtime_error
*/
    void BaseVt::update(
        const MountVt& mount    ///< mount virtual telescope
    ) throw(std::runtime_error) {

    // Copy context into local variables.
        mMutex.lock();
        const double tai = mTai;
        Target::Ptr target(mTarget->clone());
        KernelRefSys::Ptr kernelTF(mKernelTF->clone());
        RefSys::ConstPtr trackFrame(mTrackFrame->clone());
        KernelRefSys::Ptr kernelOF(mKernelOF->clone());
        RefSys::ConstPtr offsetFrame(mOffsetFrame->clone());
        xycoord offset = mOffset;
        const double wavel = mWavel;
        const double cst = mCst;
        const double sst = mSst;

    // Clear the "newTarget" flag. This flag will be used to detect if a new
    // target was set by another thread while we are updating the reference
    // frames.
        mNewTarget = false;
        mMutex.unlock();

    // Copy site site information from the Site object.
        mSite.mMutex.lock();
        const double lat = mSite.mLat;
        const double refa = mSite.mRefa;
        const double refb = mSite.mRefb;
        const double hm = mSite.mHm;
        const double temp = mSite.mTemp;
        const double press = mSite.mPress;
        const double humid = mSite.mHumid;
        const double ttj = mSite.mTtj;
        double amprms[21];
        TcsLib::copyAmprms(mSite.mAmprms, amprms);
        const double diurab = mSite.mDiurab;
        mSite.mMutex.unlock();

    // Copy the mount orientation from the associated MountVt object.
        mount.mMutex.lock();
        double ae2mt[3][3];
        TcsLib::copyMatrix(mount.mAe2mt, ae2mt);
        mount.mMutex.unlock();

    // Update the target.
        target->update(tai);

    // Get the target position at that time.
        vector tarp = target->position(tai);

    // Adjust refraction constants for color.
        double refac, refbc;
        slaAtmdsp( temp, press, humid, wavelr, refa, refb, wavel,
                &refac, &refbc);

    // Update the tracking reference frame.
        kernelTF->tartran( ttj, amprms, ae2mt, hm, lat, diurab,
                refac, refbc, temp, press, humid, tlr, wavel, sst, cst, tarp);

    // If the target and offset reference systems are not the same the
    // target position has to be transformed to the offset reference
    // frame before adding the offset.
        vector offtar = tarp;
        if ( *trackFrame != *offsetFrame ) {

        // Base aim vector.
            vector aim = kernelTF->sky2aim( tarp, sst, cst);

        // Target position in offset reference frame.
            offtar = kernelOF->ptrani( aim, ttj, amprms, ae2mt, hm, lat, diurab,
                    refac, refbc, temp, press, humid, tlr, wavel, sst, cst);

        // Add the offset
            offtar = offtar + offset;
        }

    // Update the offset reference frame.
        kernelOF->tartran( ttj, amprms, ae2mt, hm, lat, diurab, refac, refbc, 
                temp, press, humid, tlr, wavel, sst, cst, offtar);

    // Store updated reference systems and atmosphere parameters provided
    // that a new target hasn't appeared since we read the target position.
        mMutex.lock();
        if ( ! mNewTarget ) {
            mTarget = target;
            mKernelTF = kernelTF;
            mKernelOF = kernelOF;
            mTemp = temp;
            mPress = press;
            mHumid = humid;
            mTLR = tlr;
        }
        mMutex.unlock();
    }

/// Target position at a specified time
/**
    The target position includes any offset.

    \returns the position of the current target in the tracking frame
*/
    vector BaseVt::targetpos (
        double t,            ///< TAI (MJD)
        double sst,          ///< sine of sidereal time
        double cst           ///< cosine of sidereal time
    ) const throw() {
        mMutex.lock();
        Target::ConstPtr base(mTarget->clone());
        KernelRefSys::ConstPtr kernelTF(mKernelTF->clone());
        RefSys::ConstPtr trackFrame(mTrackFrame->clone());
        KernelRefSys::ConstPtr kernelOF(mKernelOF->clone());
        RefSys::ConstPtr offsetFrame(mOffsetFrame->clone());
        xycoord offset = mOffset;
        mMutex.unlock();

    // Base position at time t.
        vector target = base->position(t);

    // If the offset and tracking frames are different.
        if ( *trackFrame != *offsetFrame ) {

        // Base position to aim vector.
            vector aim = kernelTF->sky2aim( target, sst, cst);

        // Base position in offset reference frame.
            vector sky = kernelOF->aim2sky( aim, sst, cst);

        // Add offset.
            sky = sky + offset;

        // Convert back to the tracking frame.
            aim = kernelOF->sky2aim( sky, sst, cst);
            target = kernelTF->aim2sky( aim, sst, cst);
        } else {

        // Add offset.
            target = target + offset;
        }
        return target;
    }

/// Set target offset and reference frame.
/**
    The position that the virtual telescope is tracking can be offset from
    the target position by an amount in any reference frame. The offset in
    the tracking frame is re-calculate every time the pointing calculation
    runs.

    The offset is in the tangent plane and the tangent point is the base
    position of the current target.
*/
    void BaseVt::setOffset(
        const double& alpha,       ///< offset in alpha (radians)
        const double& beta,        ///< offset in beta (radians)
        const RefSys& offsetFrame  ///< reference system of offset
    ) throw () {

    // Store the new offset
        mMutex.lock();
        mOffset.a = alpha;
        mOffset.b = beta;
        KernelRefSys::Ptr kernelOF(offsetFrame.kernelRefSys());
        mKernelOF = kernelOF;
        RefSys::Ptr frame(offsetFrame.clone());
        mOffsetFrame = frame;
        mMutex.unlock();

    // Update the SPMs.
        update();
    }

/// Set target offset
/**
    The offset is set to the new values without changing the reference
    frame. If the frame has never been set it will default to be the
    same as the tracking frame.
*/
    void BaseVt::setOffset(
        const double& alpha,        ///< offset in alpha (radians)
        const double& beta          ///< offset in beta (radians)
    ) throw () {

    // Store the new offset
        mMutex.lock();
        mOffset.a = alpha;
        mOffset.b = beta;
        mMutex.unlock();
    }

/// Increment target offset
/**
    The specified offset is added to the existing offset. The reference
    frame is not changed.
*/
    void BaseVt::incrOffset(
        const double& alpha,        ///< offset in alpha (radians)
        const double& beta          ///< offset in beta (radians)
    ) throw () {

    // Store the new offset
        mMutex.lock();
        mOffset.a += alpha;
        mOffset.b += beta;
        mMutex.unlock();
    }
}

