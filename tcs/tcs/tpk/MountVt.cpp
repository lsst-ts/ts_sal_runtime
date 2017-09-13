//// \file MountVt.cpp
/// \brief Implementation of the mount virtual telescope class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "MountVt.h"

#include <memory>
#include <stdexcept>
#include "slalib.h"

#include "Coordinates.h"
#include "DawdleFilter.h"
#include "KernelAzElRefSys.h"
#include "MountType.h"
#include "PointingLog.h"
#include "PointingModel.h"
#include "PointingOrigin.h"
#include "RotatorLoc.h"
#include "Site.h"
#include "Target.h"
#include "TcsMutex.h"
#include "TcsLib.h"
#include "TimeKeeper.h"
#include "Trajectory.h"
#include "Transform.h"



namespace tpk {

    extern double sampleint;
    extern double rnogo;
    extern double tlr;
    extern double wavelr;
    extern const RefSys* defaultFrame;
/**
    The time keeper, site, dawdle filter and tracking frame objects must
    not be destroyed during the lifetime of the MountVt object.

    The newly created MountVt object has guiding offsets set to zero, no
    rotator reference target (i.e. the reference point is the target being
    tracked), the instrument position angle and instrument alignment angle
    are zero, the "beyond the pole" flag is false and the field optimised
    rotator algorithm is selected.

    \exception std::runtime_error
*/
    MountVt::MountVt(
        const TimeKeeper& ticker,     ///< time keeper
        const Site& site,             ///< telescope site
        const RotatorLoc& rotl,       ///< rotator location
        const MountType& mtype,       ///< mount type
        DawdleFilter* dawdle,         ///< dawdle filter
        const RefSys& trackframe      ///< tracking frame
    ) :
        BaseVt(ticker, site, trackframe),
        mRotloc(rotl),
        mMtype(mtype),
        mDawdle(dawdle),
        mGa(0.0),
        mGb(0.0),
        mRotTarget(0),
        mKernelRF(new KernelAzElRefSys),
        mRotFrame(new AzElRefSys),
        mKernelRTF(trackframe.kernelRefSys()),
        mRtarFrame(trackframe.clone()),
        mPai(0.0),
        mCia(1.0),
        mSia(0.0),
        mBp(false),
        mSlit(false)
    {

    // Rotation matrix, celestial [Az,El] to nominal mount.
        double gim1z, gim2y, gim3x;
        if ( mtype.mMtype == tcspk::GIMBAL ) {
            gim1z = mtype.mGim1z;
            gim2y = mtype.mGim2y;
            gim3x = mtype.mGim3x;
        } else {
            gim1z = 0.0;
            gim2y = ( mtype.mMtype == tcspk::ALTAZ ) ? 0.0 :
                    site.mLat - TcsLib::d90;
            gim3x = 0.0;
        }
        slaDeuler ( "zyx", gim1z + site.mDaz, gim2y, gim3x, mAe2nm );

    // Create a default empty pointing model.
        mPm.reset(new PointingModel);

    // Set auxiliary pointing data to zero.
        for ( int i = 0; i < 3; i++ ) mAux[i] = 0.0;

    // Update the pointing model and initialise SPMs .
        updatePM();
        update();

    }

    MountVt::MountVt(const MountVt& src) :
        BaseVt(src.mTimeKeeper, src.mSite, src),
        mRotloc(src.mRotloc),
        mMtype(src.mMtype)
    {
    // Lock the source context.
        src.mMutex.lock();

    // Copy the kernel context.
        for ( int i = 0; i < 3; i++ ) mAux[i] = src.mAux[i];
        mGa = src.mGa;
        mGb = src.mGb;
        mAoa = src.mAoa;
        mAob = src.mAob;
        TcsLib::copyMatrix(src.mAe2nm, mAe2nm);
        TcsLib::copyMatrix(src.mAe2mt, mAe2mt);
        mIa = src.mIa;
        mIb = src.mIb;
        mNp = src.mNp;
        mTelVec = src.mTelVec;
        mRoll = src.mRoll;
        mPitch = src.mPitch;
        mRma = src.mRma;
        mBp = src.mBp;
        mSlit = src.mSlit;
        mKernelRF.reset(src.mKernelRF->clone());
        mRotFrame.reset(src.mRotFrame->clone());
        mKernelRTF.reset(src.mKernelRTF->clone());
        mRtarFrame.reset(src.mRtarFrame->clone());
        mPai = src.mPai;
        mCia = src.mCia;
        mSia = src.mSia;
        mPm.reset(src.mPm->clone());

    // Create a new dawdle filter if the source VT had one otherwise set
    // the pointer to zero.
        if (src.mDawdle ) {
            mDawdle = new DawdleFilter(*src.mDawdle);
        } else {
            mDawdle = 0;
        }

    // Create a new rotator target if the source VT had one otherwise set
    // the pointer to zero.
        if (src.mRotTarget.get() ) {
            mRotTarget.reset(src.mRotTarget->clone());
        }

    // Release the source context.
        src.mMutex.unlock();
    }
/**
    Create a copy of a mount with a new timekeep and site.
*/
    MountVt::MountVt(
        const TimeKeeper& ticker,  ///< timekeeper
        const Site& site,          ///< telescope site
        const MountVt& src         ///< mount
    ) :
        BaseVt(ticker, site, src),
        mRotloc(src.mRotloc),
        mMtype(src.mMtype)
    {
    // Lock the source context.
        src.mMutex.lock();

    // Copy the kernel context.
        for ( int i = 0; i < 3; i++ ) mAux[i] = src.mAux[i];
        mGa = src.mGa;
        mGb = src.mGb;
        mAoa = src.mAoa;
        mAob = src.mAob;
        TcsLib::copyMatrix(src.mAe2nm, mAe2nm);
        TcsLib::copyMatrix(src.mAe2mt, mAe2mt);
        mIa = src.mIa;
        mIb = src.mIb;
        mNp = src.mNp;
        mTelVec = src.mTelVec;
        mRoll = src.mRoll;
        mPitch = src.mPitch;
        mRma = src.mRma;
        mBp = src.mBp;
        mSlit = src.mSlit;
        KernelRefSys::Ptr kernelRF(src.mKernelRF->clone());
        mKernelRF = kernelRF;
        RefSys::Ptr rotFrame(src.mRotFrame->clone());
        mRotFrame = rotFrame;
        KernelRefSys::Ptr kernelRTF(src.mKernelRTF->clone());
        mKernelRTF = kernelRTF;
        RefSys::Ptr rtarFrame(src.mRtarFrame->clone());
        mRtarFrame = rtarFrame;
        mPai = src.mPai;
        mCia = src.mCia;
        mSia = src.mSia;
        mPm.reset(src.mPm->clone());

    // Create a new dawdle filter if the source VT had one otherwise set
    // the pointer to zero.
        if (src.mDawdle ) {
            mDawdle = new DawdleFilter(*src.mDawdle);
        } else {
            mDawdle = 0;
        }

    // Create a new rotator target if the source VT had one otherwise set
    // the pointer to zero.
        if (src.mRotTarget.get() ) {
            mRotTarget.reset(src.mRotTarget->clone());
        } else {
            mRotTarget.reset();
        }
    // Release the source context.
        src.mMutex.unlock();
    }

/// Update the sky patch matrices.
/**
    Updates the sky patch matrices from the current target and weather
    information.

    The MountVt has its own implementation of updateSPM because in
    addition to the usual SPMs for the target it requires inverse
    SPMs that to transform focal plane positions into the rotator
    tracking frame.

    \exception std::runtime_error
*/
    void MountVt::update() throw(std::runtime_error) {

    // Copy context into local variables.
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

        mMutex.lock();
        const double tai = mTai;
        double ae2mt[3][3];
        TcsLib::copyMatrix(mAe2mt, ae2mt);
        const double sst = mSst;
        const double cst = mCst;
        Target::Ptr rottarget;
        if (mRotTarget.get()) {
            rottarget.reset(mRotTarget->clone());
        } else {
            rottarget.reset(mTarget->clone());
        }
        KernelRefSys::Ptr kernelRF(mKernelRF->clone());
        KernelRefSys::Ptr kernelRTF(mKernelRTF->clone());
        const double wavel = mWavel;

    // Clear the "newTarget" flag to show that we have the latest target
    // position.
        mNewTarget = false;
        mMutex.unlock();

    // Call BaseVt method to generate the target SPMs.
        BaseVt::update(*this);

    // Update the rotator reference target.
        rottarget->update(tai);
        vector rtar = rottarget->position(tai);

    // Adjust refraction constants for color.
        double refac, refbc;
        slaAtmdsp( temp, press, humid, wavelr, refa, refb, wavel, &refac,
                &refbc);

    // Generate rotator reference target SPMs.
        kernelRTF->tartran( ttj, amprms, ae2mt, hm, lat, diurab,
                refac, refbc, temp, press, humid, tlr, wavel, sst, cst, rtar);

    // Compute aim vector.
        vector aim = kernelRTF->sky2aim( rtar,  sst, cst);

    // Transform aim vector to rotator tracking frame.
        vector tar = kernelRF->ptrani( aim, ttj, amprms, ae2mt, hm, lat, diurab,
                refac, refbc, temp, press, humid, tlr, wavel, sst, cst);

    // Generate field orientation reference frame SPMs.
        kernelRF->tartran( ttj, amprms, ae2mt, hm, lat, diurab,
                refac, refbc, temp, press, humid, tlr, wavel, sst, cst, tar);

    // Store new SPMs provided that a new target hasn't appeared since we
    // read the target position.
        mMutex.lock();
        if ( ! mNewTarget ) {
            if ( mRotTarget.get()) mRotTarget = rottarget;
            mKernelRF = kernelRF;
            mKernelRTF = kernelRTF;
        }
        mMutex.unlock();
    }

/// Update the summary pointing model
/**
    Re-computes the summary (seven term) pointing model from the full
    pointing model and current telescope position.

    \exception std::runtime_error
*/
    void MountVt::updatePM() throw(std::runtime_error) {

    // Copy context into local variables.
        mMutex.lock();
        double aux[3];
        for ( int i = 0; i < 3; i++ ) aux[i] = mAux[i];
        const double tai = mTai;
        double ae2nm[3][3];
        TcsLib::copyMatrix(mAe2nm, ae2nm);
        const Trajectory roll = mRoll;
        const Trajectory pitch = mPitch;
        const TcsLib::mtype mtype = mMtype.mMtype;
        const bool bp = mBp;

    // Copy the the pointing model
        PointingModel::ConstPtr pm(mPm->clone());
        mMutex.unlock();

        mSite.mMutex.lock();
        const double lat = mSite.mLat;
        mSite.mMutex.unlock();

    // Recalculate the summary pointing model terms.
        double ia, ib, np, ae2mt[3][3];
        vector tel;
        pm->summerize( mtype, ae2nm, roll.sample(tai), pitch.sample(tai), bp,
                aux, lat, ia, ib, np, tel, ae2mt);

    // Store updated summary model.
        mMutex.lock();
        mIa = ia;
        mIb = ib;
        mNp = np;
        mTelVec = tel;
        TcsLib::copyMatrix(ae2mt, mAe2mt);
        mMutex.unlock();
    }

/// Calculate mount and rotator trajectories
/**
    The fast update performs the main pointing calculation and returns
    the azimuth, elevation and rotator position (radians), velocity
    (radians/second) and acceleration (radians/second/second) demands
    and associated time-stamp (MJD).

    If the function return value is -1 the position and velocity demands
    and timestamp are not updated.

    \return status
    \retval 0 Success
    \retval 1 Out of position because zenith avoidance is in effect
    \retval 2 Out of position because of dawdle filter
    \retval -1 Target position is inaccessible
*/
    int MountVt::track(
        unsigned int samples,         ///< number of samples to generate
        const Trajectory& rma,        ///< rotator trajectory
        const Trajectory& aoa,        ///< optics collimation in xi
        const Trajectory& aob         ///< optics collimation in eta
    ) throw() {

    // Check for samples being out of range.
        samples = samples < 1 ? 1 : (samples > maxsamp ? maxsamp : samples);

    // Copy context into local variables.
        mMutex.lock();
        KernelRefSys::ConstPtr kernelTF(mKernelTF->clone());
        const double ia = mIa;
        const double ib = mIb;
        const double np = mNp;
        const vector tel = mTelVec;
        const double ga = mGa;
        const double gb = mGb;
        Trajectory roll= mRoll;
        Trajectory pitch = mPitch;
        const bool bp = mBp;
        Target::ConstPtr rottarget;
        if (mRotTarget.get()) {
            rottarget.reset(mRotTarget->clone());
        } else {
            rottarget.reset();
        }
        PointingOrigin::ConstPtr po(mPO->clone());
        const KernelRefSys::ConstPtr kernelRF(mKernelRF->clone());
        KernelRefSys::ConstPtr kernelRTF(mKernelRTF->clone());
        const double sia = mSia;
        const double cia = mCia;
        const double pai = mPai;
        const bool slit = mSlit;
        mMutex.unlock();

        mTimeKeeper.mMutex.lock();
        double tai = mTimeKeeper.mTai;
        double sst = mTimeKeeper.mSst;
        double cst = mTimeKeeper.mCst;
        double dsst = mTimeKeeper.mDsst;
        double dcst = mTimeKeeper.mDcst;
        mTimeKeeper.mMutex.unlock();

    // Select which of the two pointing solutions to use.
        int sol = bp ? 1: 0;

    // Generate roll & pitch samples.
        double ad[2][maxsamp], bd[2][maxsamp];
        double rot[maxsamp];
        vector tar[maxsamp], rtar[maxsamp];
        focalplane p[maxsamp];
        int status = 0;
        bool dawdling = false;

    // Sample that corresponds to the timestamp. Either the middle sample (if
    // samples is odd) or the one before the middle (if samples is even).
        unsigned int ntai = (samples - 1)/2;

    // Time for first sample.
        double t1 = tai - sampleint * ntai;

    // Time for second sample.
        double t2 = t1 + sampleint;

        for ( unsigned int i = 0; i < samples; i++ ) {

        // Time for this sample.
            double t = t1 + sampleint * i;

        // pointing origin at this time.
            p[i] = po->xy(t);

        // sine and cosine of sidereal time.
            double sstt = sst + dsst * (t - tai);
            double cstt = cst + dcst * (t - tai);

        // target position at this time.
            tar[i] = targetpos(t, sstt, cstt);

        // Apply dawdle filter.
            if ( mDawdle ) {
                dawdling = mDawdle->limit( t, tar[i], p[i],
                        tar[i], p[i]) || dawdling;
            }

        // Rotator reference position.
            if ( rottarget.get() ) {
                rtar[i] = rottarget->position(t);
            } else {
                rtar[i] = tar[i];
            }

        // Collimation changes from AO and guiding at this time
            double ca = ga + aoa.sample(t);
            double cb = gb + aob.sample(t);

        // Compute mount demands.
            vector aim;
            int trackok = kernelTF->track( tar[i], sstt, cstt,  mRotloc,
                    rma.sample(t), roll.sample(t), pitch.sample(t), 
                    p[i].x, p[i].y, ia, ib, np, tel, ca, cb, rnogo, aim,
                    ad[0][i], bd[0][i], ad[1][i], bd[1][i]);

        // If the status is less than zero we have attempted to track into the
        // inaccessable region close to the pole of the mount so we use the
        // extrapolated roll, pitch and rotator demand instead.
            if ( trackok < 0 ) {
                ad[sol][i] = roll.sample(t);
                bd[sol][i] = pitch.sample(t);
                rot[i] = rma.sample(t);
            } else {

            // Transform target to focal plane to get the point around which the
            // rotation calculation will be done.
                focalplane f;
                int rotok = kernelRTF->vtxy( rtar[i], sstt, cstt, mRotloc,
                        rma.sample(t), ad[sol][i], bd[sol][i], ia, ib, np,
                        tel, ca, cb, f);
                if ( rotok == 0 ) {

                // Compute rotator demands.
                    rotok = kernelRF->rotator( aim, mRotloc, rma.sample(t), bp,
                            ad[sol][i], bd[sol][i], f, ia, ib, np, tel, ca, cb,
                            sia, cia, sstt, cstt, pai, slit, rot[i]);
                } else {
                    rot[i] = rma.sample(t);
                }
            }


        // Update overall status.
            status |= trackok;
        }

    // Deal with cases where the roll has wrapped from -pi to +pi or the 
    // rma from 0 to 2pi or vice-versa.
        for ( unsigned int i = 0; i < samples; i++ ) {
            if ( i != ntai ) {
                if ( ad[sol][i] - ad[sol][ntai] > TcsLib::pi ) {
                    ad[sol][i] -= TcsLib::pi2;
                } else if ( ad[sol][i] - ad[sol][ntai] < -TcsLib::pi ) {
                    ad[sol][i] += TcsLib::pi2;
                }
                if ( rot[i] - rot[ntai] > TcsLib::pi ) {
                    rot[i] -= TcsLib::pi2;
                } else if ( rot[i] - rot[ntai] < -TcsLib::pi ) {
                    rot[i] += TcsLib::pi2;
                }
            }
        }
    // Compute roll and pitch trajectories.
        roll = Trajectory( tai, t1, t2 - t1, samples, ad[sol] );
        pitch = Trajectory( tai, t1, t2 - t1, samples, bd[sol] );

    // Compute rotator trajectory.
        Trajectory rmad( tai, t1, t2 - t1, samples, rot );

    // Copy the result back to the context.
        mMutex.lock();
        mRoll = roll;
        mPitch = pitch;
        mRma = rmad;

    // Store the updated target position and pointing origin.
        mPosition = tar[ntai];
        mImxy = p[ntai];
        mTai = tai;
        mCst = cst;
        mSst = sst;
        mAoa = aoa;
        mAob = aob;

	
        mMutex.unlock();
	
    // Return the status.
        return dawdling ? 2 : status;
    }

/// Track rotator demand position.
    int MountVt::track(
        unsigned int samples,         ///< number of samples to generate
        const Trajectory& aoa,        ///< optics collimation in xi
        const Trajectory& aob         ///< optics collimation in eta
    ) throw() {

    // Get the rotator demand from the rotator object.
        mMutex.lock();
        const Trajectory rma = mRma;
        mMutex.unlock();

    // Call track.
        return track(samples, rma, aoa, aob);
    }

/// Track rotator mechanical position with no AO collimation.
/**
    The mount and rotator trajectories are calculated assuming that the
    that the active optics have not changed the optical collimation.

    \return status
    \retval 0 success
    \retval 1 out of position because zenith avoidance is in effect
    \retval 2 out of position because of dawdle filter
    \retval -1 target position is inaccessible
*/
    int MountVt::track(
        unsigned int samples,         ///< number of samples to generate
        const Trajectory& rma         ///< rotator trajectory
    ) throw() {
        return track(samples, rma, Trajectory(0.0), Trajectory(0.0));
    }

/// Track rotator demand position with no ao collimation
/**
    The mount and rotator trajectories are calculated assuming that the
    rotator is at its last demanded position and that the active optics
    have not changed the optical collimation.

    \return status
    \retval 0 Success
    \retval 1 Out of position because zenith avoidance is in effect
    \retval 2 Out of position because of dawdle filter
    \retval -1 Target position is inaccessible
*/
    int MountVt::track(
        unsigned int samples          ///< number of samples to generate
    ) throw() {
        return track(samples, Trajectory(0.0), Trajectory(0.0));
    }

/// Get last roll demand calculated by track.
/**
    The roll is in radians in the range -pi to pi and the timescale is days.

    \returns roll coordinate trajectory
*/
    Trajectory MountVt::roll() const throw () {
        mMutex.lock();
        const Trajectory roll = mRoll;
        mMutex.unlock();
        return roll;
    }

/// Get last pitch demand calculated by track.
/**
    The pitch is in radians in the range 0 to pi/2 and the timescale is days.

    \returns pitch coordinate trajectory
*/
    Trajectory MountVt::pitch() const throw () {
        mMutex.lock();
        const Trajectory pitch = mPitch;
        mMutex.unlock();
        return pitch;
    }

/// Get last rotator mechanical angle demand calculated by track,
/**
    The rotator angle is in radians in the range 0 to 2*pi and the timescale
    is days.

    \returns rotator mechanical angle coordinate trajectory
*/
    Trajectory MountVt::rma() const throw () {
        mMutex.lock();
        const Trajectory rma = mRma;
        mMutex.unlock();
        return rma;
    }

/// Get the telescope position for a given roll, pitch, rma and optics tip/tilt
/**
    \returns telescope position in the tracking frame.
*/
    vector MountVt::position(
        const Trajectory& roll,    ///< mount roll
        const Trajectory& pitch,   ///< mount pitch
        const Trajectory& rma,     ///< motator mechanical angle
        const Trajectory& aoa,     ///< optics tip
        const Trajectory& aob      ///< optics tilt
    ) const throw() {

    // Get context.
        mMutex.lock();
        const double ia = mIa;
        const double ib = mIb;
        const double np = mNp;
        const vector tel = mTelVec;
        const double ga = mGa;
        const double gb = mGb;
        const focalplane imxy = mImxy;
        KernelRefSys::ConstPtr kernelTF(mKernelTF->clone());
        mMutex.unlock();

        mTimeKeeper.mMutex.lock();
        double tai = mTimeKeeper.mTai;
        double sst = mTimeKeeper.mSst;
        double cst = mTimeKeeper.mCst;
        mTimeKeeper.mMutex.unlock();

        return kernelTF->vtsky( roll.sample(tai), pitch.sample(tai),
            mRotloc, rma.sample(tai), imxy, sst, cst,ia, ib, np, tel,
            ga + aoa.sample(tai), gb + aob.sample(tai));
    }

/// Get the telescope position for a given roll, pitch and rma.
/**
    \returns telescope position in the tracking frame.
*/
    vector MountVt::position(
        const Trajectory& roll,    ///< mount roll
        const Trajectory& pitch,   ///< mount pitch
        const Trajectory& rma      ///< rotator mechanical angle
    ) const throw() {
        return position( roll, pitch, rma, Trajectory(0.0), Trajectory(0.0));
    }

/// Get the field orientation for a given roll, pitch, rma and optics tip/tilt.
/**
    \returns field orientation in the rotator tracking frame (radians).

    The reference point for the rotation calculation is the pointing origin.
*/
    double MountVt::orientation(
        const Trajectory& roll,    ///< mount roll
        const Trajectory& pitch,   ///< mount pitch
        const Trajectory& rma,     ///< rotator mechanical angle
        const Trajectory& aoa,     ///< optics tip
        const Trajectory& aob      ///< optics tilt
        ) const throw() {

    // Copy context into local variables.
        mMutex.lock();
        KernelRefSys::ConstPtr kernelTF(mKernelTF->clone());
        const double ia = mIa;
        const double ib = mIb;
        const double np = mNp;
        const vector tel = mTelVec;
        PointingOrigin::ConstPtr po(mPO->clone());
        const double ga = mGa;
        const double gb = mGb;
        const double sia = mSia;
        const double cia = mCia;
        const bool bp = mBp;
        mMutex.unlock();

        mTimeKeeper.mMutex.lock();
        double tai = mTimeKeeper.mTai;
        double sst = mTimeKeeper.mSst;
        double cst = mTimeKeeper.mCst;
        mTimeKeeper.mMutex.unlock();

    // Roll, pitch, rma at tai.
        double a = roll.sample(tai);
        double b = pitch.sample(tai);
        double r = rma.sample(tai);

    // Pointing origin at this time.
        focalplane p = po->xy(tai);

    // Collimation changes from AO and guiding at this time
        double ca = ga + aoa.sample(tai);
        double cb = gb + aob.sample(tai);

    // Boresite vector
        vector bs = TcsLib::bs(tel, mRotloc, r, a, b, ca, cb, p);

    // Aim vector
        vector aim = TcsLib::enc2aim(a, b, bs, ia, ib, np);

    // Compute rotator demands for an instrument position angle of zero.
        double rot;
        (void)kernelTF->rotator( aim, mRotloc, r, bp, a, b, p, ia, ib, np, tel,
                ca, cb, sia, cia, sst, cst, 0.0, true, rot);

    // The difference between the demand and the actual position is the field 
    // orientation.
        return slaDranrm(r - rot);
    }

/// Get the field orientation for a given roll, pitch and rma.
/**
    The optics tip/tilt is assumed to be zero.

    \returns field orientation in the rotator tracking frame (radians).

    \exception std::runtime_error
*/
    double MountVt::orientation(
        const Trajectory& roll,    ///< mount roll
        const Trajectory& pitch,   ///< mount pitch
        const Trajectory& rma      ///< rotator mechanical angle
        ) const throw() {
        return orientation( roll, pitch, rma, Trajectory(0.0), Trajectory(0.0));
    }

/// New pointing model
/**
    Load a new pointing model.

    \exception std::runtime_error
*/
    void MountVt::newPointingModel(
        const PointingModel& pm      ///< new pointing model
    ) throw(std::runtime_error) {
        mMutex.lock();
        mPm.reset(pm.clone());
        mMutex.unlock();

    // Update the model.
        updatePM();
    }

/// Set the Position Angle of the Instrument
/**
    Sets the position angle of the instrument principle direction on the
    sky (relative to the pole of the coordinate frame).
*/
    void MountVt::setPai(
        const double& pai,               ///< position angle (radians)
        const RefSys& refsys,            ///< coordinate reference system
        const bool slit                  ///< use slit optimised algorithm
    ) throw() {

    // Store the new position angle and frame.
        mMutex.lock();
        mKernelRF.reset(refsys.kernelRefSys());
        mRotFrame.reset(refsys.clone());
        mPai = pai;
        mSlit = slit;
        mNewTarget = true;
        mMutex.unlock();

    // Update the SPMs to generate new rotator SPMs
        update();
    }

/// Set the Alignment Angle of the Instrument
/**
    Sets the orientation of the instrument principle direction in the
    instrument coordinate system.
*/
    void MountVt::setIaa(
        const double &iaa,      ///< alignment angle (radians)
        const Transform& transf ///< transformation from instrument coords to i
                                ///  focal plane.
    ) throw() {

    // Transform unit vector at the given angle to the focal plane.
        focalplane scia = transf.forward(instrcoord(sin(iaa), cos(iaa)));

    // Store cos & sin in FP coordinates.
        mMutex.lock();
        mSia = scia.x;
        mCia = scia.y;
        mMutex.unlock();
    }

/// Set the rotation reference position.
/**
    Sets the reference position for rotation calculations.
*/
    void MountVt::setRotRef(
        const Target* rottarget    ///< pointer to reference target
    ) throw() {

        if ( rottarget ) {

        // Make a copy of the new target.
            Target::Ptr newTarget(rottarget->clone());

        // Set its tracking frame.
            newTarget->trackframe(*mTrackFrame);

        // Store the new target and ra,dec.
            mMutex.lock();
            mRotTarget = newTarget;
            mNewTarget = true;
            mMutex.unlock();
        } else {
            mMutex.lock();
            mRotTarget.reset();
            mNewTarget = true;
            mMutex.unlock();
        }

    // Update the SPMs with the new target position.
        update();
    }

/// Set guiding offset
/**
    Sets the guiding offsets in azimuth*cosE and elevation.
*/
    void MountVt::setGuide(
        const double& ga,     ///< guide offset in azimuth*cosE (radians)
        const double& gb      ///< guide offset in elevation (radians)
    ) throw() {
        mMutex.lock();
        mGa = ga;
        mGb = gb;
        mMutex.unlock();
    }

/// Get guiding offset
/**
    Gets the current guiding offsets in azimuth*cosE and elevation.
*/
    void MountVt::getGuide(
        double &ga,    ///< guide offset in azimuth*cosE (radians)
        double &gb     ///< guide offset in elevation (radians)
    ) const throw() {
        mMutex.lock();
        ga = mGa;
        gb = mGb;
        mMutex.unlock();
    }

/// Set dawdle mode and tuning parameter.
/**
    Sets the state of the dawdle filter and its tuning parameter.

    This method has no effect if the mount was created without a dawdle
    filter.
*/
    void MountVt::dawdle(
        const bool& bypass,           ///< filter state
        const double& tunepar         ///< tuning parameter.
    ) throw () {
        if ( mDawdle ) {
            mDawdle->bypass( bypass );
            mDawdle->tune( tunepar );
        }
    };

/// Set dawdle mode
/**
    Sets the state of the dawdle filter.

    If the mount virtual telescope was created without a dawdle filter,
    the previous state is always returned as false.

    \returns previous state of the dawdle filter
*/
    bool MountVt::dawdle(
        const bool& on           ///< dawdle state
    ) throw () {
        if ( mDawdle ) {
            return !(mDawdle->bypass( !on ));
        } else {
            return false;
        }
    };

/// Transform focal plane position to sky coordinates.
/**
    \returns Equivalant sky position
*/
    vector MountVt::xy2sky(
        const xycoord& xy,            ///< position in focal plane
        const RefSys& refsys,         ///< reference system for sky position
        const double& wavel           ///< effective wavelength (microns)
    ) const throw(std::runtime_error) {
        mMutex.lock();
        TcsLib::rotloc rotl = mRotloc;
        vector tel = mTelVec;
        Trajectory rma = mRma;
        Trajectory roll = mRoll;
        Trajectory pitch = mPitch;
        double ga = mGa;
        double gb = mGb;
        Trajectory aoa = mAoa;
        Trajectory aob = mAob;
        double ia = mIa;
        double ib = mIb;
        double np = mNp;
        double ae2mt[3][3];
        TcsLib::copyMatrix(mAe2mt, ae2mt);
        const double cst = mCst;
        const double sst = mSst;
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

    // Adjust the x,y by any optics collimation and convert to a boresite
    // vector
        vector bs = TcsLib::bs( tel, rotl, rma, roll, pitch, ga, gb,
                xy + xycoord(aoa, aob));

    // Boresight to aim.
        vector aim = TcsLib::enc2aim( roll, pitch, bs, ia, ib, np);

    // Aim to sky
        KernelRefSys::Ptr krefsys(refsys.kernelRefSys());
        vector sky = krefsys->ptrani( aim, ttj, amprms, ae2mt, hm, lat, diurab,
                refa, refb, temp, press, humid, tlr, wavel, sst, cst);

        return sky;
    }

/// Set beyond pole flag
/**
    The "beyond the pole" flag determines which of the two pointing solutions
    is calculated by the track methods. The beyond the pole solution has a
    pitch axis demand greater than 90 degrees.
*/
    void MountVt::setBeyondPole(
        const bool& state    ///< state of beyond pole flag
    ) {
        mMutex.lock();
        mBp = state;
        mMutex.unlock();
    }
}
