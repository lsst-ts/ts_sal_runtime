/// \file PointingObs.cpp
/// \brief Implementation of the pointing observation class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "PointingObs.h"

#include <fstream>
#include <ios>
#include <string>
#include "slalib.h"

#include "ICRefSys.h"
#include "MountVt.h"
#include "Site.h"
#include "TcsLib.h"
#include "TcsMutex.h"

namespace tpk {
/**
    Stores the information that applies to all pointing obervations
    in member variables.
*/
    PointingObs::PointingObs(
        const MountVt& mount             ///< mount virtual telescope
    ) throw() :
            mMount(mount)
    {

    // Get data needed for the header from the mount virtual telescope.
        mMount.mSite.mMutex.lock();
        mTaiStart = mMount.mSite.mTai;
        mDelut = mMount.mSite.mDelut;
        mDelat = mMount.mSite.mDelat;
        mTtmtai = mMount.mSite.mTtmtai;
        mElongm = mMount.mSite.mElongm;
        mLatm = mMount.mSite.mLatm;
        mHm = mMount.mSite.mHm;
        mXpm = mMount.mSite.mXpm;
        mYpm = mMount.mSite.mYpm;
        mMount.mSite.mMutex.unlock();
        mMtype = mMount.mMtype.mMtype;
        mGim1z = mMount.mMtype.mGim1z;
        mGim2y = mMount.mMtype.mGim2y;
        mGim3x = mMount.mMtype.mGim3x;

    // Mark no data available
        mMarked = false;
    }

/// Mark pointing observation
/**
    Captures all the data needed for logging a pointing observation in
    member variables.
*/
    void PointingObs::mark()
    {

    // Get data to log from the mount virtual telescope.
        mMount.mMutex.lock();
        mTai = mMount.mTai;
        vector tar = mMount.mPosition;
        mXr = mMount.mImxy.x;
        mYr = mMount.mImxy.y;
        mWavel = mMount.mWavel;
        Trajectory roll = mMount.mRoll;
        Trajectory pitch = mMount.mPitch;
        Trajectory rma = mMount.mRma;
        Trajectory aoa = mMount.mAoa;
        Trajectory aob = mMount.mAob;
        mTemp = mMount.mTemp;
        mPress = mMount.mPress;
        mHumid = mMount.mHumid;
        mTlr = mMount.mTLR;
        double ga = mMount.mGa;
        double gb = mMount.mGb;
        double ia = mMount.mIa;
        double ib = mMount.mIb;
        double np = mMount.mNp;
        vector tel = mMount.mTelVec;
        for ( int i = 0; i < 3; i++ ) mAux[i] = mMount.mAux[i];
        RefSys::ConstPtr trackSys(mMount.mTrackFrame->clone());
        mMount.mMutex.unlock();

    // Convert target coordinates to ICRF.
        Target* target = trackSys->target(mMount.mSite, tar);
        spherical icrf = target->position(mTai, ICRefSys());
        mRa = icrf.a;
        mDec = icrf.b;
        delete target;

    // Roll, pitch and rma demands.
        mRoll = roll.sample(mTai);
        mPitch = pitch.sample(mTai);
        double rot = rma.sample(mTai);

    // Convert the rotator angle to the "Cass equivalent" angle.
        double spa, cpa;
        TcsLib::casspa( mMount.mRotloc, rot, mRoll, mPitch, spa, cpa);
        mCasspa = atan2(spa, cpa);

    // Rotate optics tip/tilt from xi,eta to rotating x,y and adjust the
    // pointing origin as if the tip/tilt has displaced the rotator axis.
        focalplane ao = TcsLib::xe2xy(focalplane(aoa.sample(mTai),
                aob.sample(mTai)), mMount.mRotloc, rot, mRoll, mPitch);
        mXr += ao.x;
        mYr += ao.y;

    // Assume a focal length of 1 metre and scale the pointing origin
    // accordingly.
        mFl = 1000.0;
        mXr *= mFl;
        mYr *= mFl;

    // Get aim vector for the rotator axis.
        vector bs = TcsLib::bs( tel, mMount.mRotloc, rot, mRoll,
                mPitch, ga, gb, focalplane(0.0, 0.0));
        vector aim0 = TcsLib::enc2aim( mRoll, mPitch, bs, ia, ib, np);

    // And for a pointing origin displaced from the rotator axis.
        bs = TcsLib::bs( tel, mMount.mRotloc, rma, mRoll, mPitch, ga, gb,
                focalplane(0.0, -1.0e-5));
        vector aim1 = TcsLib::enc2aim( mRoll, mPitch, bs, ia, ib, np);

    // Orientation in xi, eta frame.
        mRcorr = slaDrange(aim0.bearing(aim1) - rot);

    // Flag data available.
        mMarked = true;
    }
}
