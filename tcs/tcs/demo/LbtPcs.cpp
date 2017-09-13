/// \file LbtPcs.cpp
/// \brief Implementation of the LBT prototype PCS class

// D L Terrett
// Copyright STFC 2007

#include "LbtPcs.h"

#include "dpk.h"
#include "TclClock.h"

LbtPcs::LbtPcs(
    Tcl_Interp* interp
) : Pcs(interp), mTip_l(0.0), mTilt_l(0.0), mTip_r(0.0), mTilt_r(0.0) {

// Create the clock. At this time (27/07/2007) TAI is offset from UTC by
// 33 seconds.
    mClock = new tpk::TclClock(33.0);
    
// Set the current time member variable.
    mTai = mClock->read();

// Create the "site"
    mSite = new tpk::Site( mTai,
            0.0,                          // UT1 - UTC
            33.0,                         // TAI - UTC
            32.184,                       // TT - TAI
            -116.863889,                  // Longitude
            33.356111,                    // Latitude
            1760.0,                       // Height
            0.0, 0.0);                    // Polar motion
            
// Set the telescope focal length (mm).
    mFocalLength = 100000.0;

// Create the time keeper object.
    mTimeKeeper = new tpk::TimeKeeper(*mClock, *mSite);

// Create mount virtual telescopes for the two sides.
    mMount_l = new tpk::MountVt( *mTimeKeeper, *mSite, tpk::Cassegrain(),
            tpk::AltAzMountType());
    mMount_r = new tpk::MountVt(*mMount_l);

// Instrument (and guider) to focal plane coordinate transformation.
    mTransform = new tpk::AffineTransform( 0.0, 0.0, 1.0/mFocalLength, 0.0);

// Pointing controller and associated filters. The guide filter can be a local
// variable because the AutoGuider object makes a copy and the origonal filter
// object can then be discarded.
    mAzFilter_l = new tpk::PiFilter(0.05);
    mElFilter_l = new tpk::PiFilter(0.05);
    mPcontrol_l = new tpk::PointingControl( *mMount_l, *mAzFilter_l, *mElFilter_l );
    mAzFilter_r = new tpk::PiFilter(*mAzFilter_l);
    mElFilter_r = new tpk::PiFilter(*mElFilter_l);
    mPcontrol_r = new tpk::PointingControl( *mMount_r, *mAzFilter_r, *mElFilter_r );
    
// Create optics virtual telescopes.
    mOptics_l = new tpk::OpticsVt(*mMount_l);
    mOptics_r = new tpk::OpticsVt(*mMount_r);
    
// Create auto-guider virtual telescopes.
    mGuider_l.gvt = new tpk::AutoGuider( *mMount_l, *mPcontrol_l, *mTransform,
        tpk::Filter2D());
    mGuider_r.gvt = new tpk::AutoGuider( *mMount_r, *mPcontrol_r, *mTransform,
        tpk::Filter2D());
        
// Create an initial target for the mount and guider that matches the initial
// axes positions.
    tpk::AzElTarget deftarg(*mSite, 
            dpk::AltAzMountControl::AZ_INIT * tpk::TcsLib::d2r, 
            dpk::AltAzMountControl::ALT_INIT * tpk::TcsLib::d2r);
    mMount_l->newTarget(deftarg);
    mMount_r->newTarget(deftarg);
    mOptics_l->newTarget(deftarg);
    mOptics_r->newTarget(deftarg);
    mGuider_l.gvt->newTarget(deftarg);
    mGuider_r.gvt->newTarget(deftarg);
            
// Set the initial field orientation.
    mMount_l->setPai( 0.0, tpk::ICRefSys(),true);
    mMount_r->setPai( 0.0, tpk::ICRefSys(),true);
    
// Create sky view for plotting the artifical star field for this mount.
    mSkyView_l = new dpk::SkyView(*mMount_l, *mTransform, *this, "sky_left", 
            mSkySamples);
    mSkyView_r = new dpk::SkyView(*mMount_r, *mTransform, *this, "sky_right", 
            mSkySamples);
    
// Initialise the context.
    mMount_l->track(1);
    mMount_r->track(1);
    mOptics_l->track(1);
    mOptics_r->track(1);
    mGuider_l.gvt->track(1);
    mGuider_r.gvt->track(1);

// Create the control systems.
    mMcs = new dpk::AltAzMountControl(*this, "azimuth", "elevation");
    mRcs_l = new dpk::RotatorControl(*this, "rotator_left");
    mRcs_r = new dpk::RotatorControl(*this, "rotator_right");
    mGcs_l = new dpk::GuiderControl(*this, "guider_x_l", "guider_y_l");
    mGcs_r = new dpk::GuiderControl(*this, "guider_x_r", "guider_y_r");
    mOcs_l = new dpk::OpticsControl(*this, "", "");
    mOcs_r = new dpk::OpticsControl(*this, "", "");

// Register the mounts.
    registerMount(mMount_l, "left");
    registerMount(mMount_r, "right");
    
// Register the optics.
    registerOptics(mOptics_l, "optics_left");
    registerOptics(mOptics_r, "optics_right");

// Register the pointing controllers.
    registerPointingControl(mPcontrol_l, "left");
    registerPointingControl(mPcontrol_r, "right");

// Register the guiders.
    registerGuider(&mGuider_l, "guider_left");
    registerGuider(&mGuider_r, "guider_right");
}

LbtPcs::~LbtPcs() {
    delete mClock;
    delete mTimeKeeper;
    delete mSite;
    delete mMount_l;
    delete mMount_r;
    delete mOptics_l;
    delete mOptics_r;
    delete mTransform;
    delete mPcontrol_l;
    delete mPcontrol_r;
    delete mAzFilter_l;
    delete mAzFilter_r;
    delete mElFilter_l;
    delete mElFilter_r;
    delete mGuider_l.gvt;
    delete mGuider_r.gvt;
    delete mSkyView_l;
    delete mSkyView_r;
    delete mMcs;
    delete mRcs_l;
    delete mRcs_r;
    delete mGcs_l;
    delete mGcs_r;
    delete mOcs_l;
    delete mOcs_r;
}

void LbtPcs::update () {

// Update the pointing controllers
    mPcontrol_l->update();
    mPcontrol_r->update();

// Track the two mounts. This gives us the desired position of the mount
// from the two sides assuming that the optics has the correct alignment
// for when the mount is in position.
    mMount_l->track(2, mRcs_l->getRma(mTai), mTip_l, mTilt_l);
    mMount_r->track(2, mRcs_r->getRma(mTai), mTip_r, mTilt_r);
    
// Combine left and right roll and pitch demands to get the demand
// position for the mount. Here we pick a point mid way between the
// two demands but it doesn't really matter which point we pick as the
// final mount orientation is dictated by the "tip/tilt arbitrator".
    double c[2];
    c[0] = (mMount_l->roll().sample(mTai,0) + 
        mMount_r->roll().sample(mTai,0)) / 2.0;
    c[1] = (mMount_l->roll().sample(mTai,1) + 
        mMount_r->roll().sample(mTai,1)) / 2.0;
    mRoll_d = tpk::Trajectory(mTai, mTai, c, 1);
    c[0] = (mMount_l->pitch().sample(mTai,0) + 
        mMount_r->pitch().sample(mTai,0)) / 2.0;
    c[1] = (mMount_l->pitch().sample(mTai,1) + 
        mMount_r->pitch().sample(mTai,1)) / 2.0;
    mPitch_d = tpk::Trajectory(mTai, mTai, c, 1);
    
// Update the mount control system
    mMcs->track(mTai, mRoll_d, mPitch_d);
              
// Update the rotators.
    mRcs_l->track(mTai, mMount_l->rma());
    mRcs_r->track(mTai, mMount_r->rma());
                      
// Track the optics virtual telescopes with the demand position of the
// real mount. This gives us the tip/tilts that will point both telescopes
// correctly when the mount is in position.
    mOptics_l->track(1, mRoll_d, mPitch_d, mRcs_l->getRma(mTai));
    mOptics_r->track(1, mRoll_d, mPitch_d, mRcs_r->getRma(mTai));
    
// Extract the demand tip/tilts
    double tip_l, tip_r, tilt_l, tilt_r;
    tip_l = mOptics_l->tip();
    tip_r = mOptics_r->tip();
    tilt_l = mOptics_l->tilt();
    tilt_r = mOptics_r->tilt();
    
// Equalise the tip/tilt for the two telescopes to get the optics
// configuration we want when the mount is in position. This is the
// tip/tilt that is fed back into the mount position calculations at the
// next iteration so that the mount eventually settles with equal
// tip and tilt for the two telescopes.
    mTip_l = ( tip_l - tip_r ) / 2.0;
    mTilt_l = ( tilt_l - tilt_r ) / 2.0;
    mTip_r = ( tip_r - tip_l ) / 2.0;
    mTilt_r = ( tilt_r - tilt_l ) / 2.0;

// If we are tracking the actual mount position we need to modify
// the tilts to take account of the difference between the actual
// and demand mount positions and offset the optics accordingly.
// Without this, an offset applied to one side which causes the mount
// to go out of position will cause the image to move on the other
// side.
    if ( mTrackMount ) {

    // Calculate the optics tip and tilt that would correct the pointing
    // given the actual mount position.
        mOptics_l->track(1, mMcs->getRoll(mTai), mMcs->getPitch(mTai), 
                mRcs_l->getRma(mTai));
        mOptics_r->track(1, mMcs->getRoll(mTai), mMcs->getPitch(mTai), 
                mRcs_r->getRma(mTai));

    // Update the optics control systems.
        mOcs_l->track(mTai, mOptics_l->tip(), mOptics_l->tilt());
        mOcs_r->track(mTai, mOptics_r->tip(), mOptics_r->tilt());
    } else {
    
    // Update the optics control systems with the balanced demands.
        mOcs_l->track(mTai, mTip_l, mTilt_l);
        mOcs_r->track(mTai, mTip_r, mTilt_r);
    }
            
// Track the auto-guider with or without the achieved rotator
// position according to the flag in the guider structure.
    if (mGuider_l.track_rot) {
        mGuider_l.gvt->track(2, mRcs_l->getRma(mTai));
    } else {
        mGuider_l.gvt->track(2);
    }
    if (mGuider_r.track_rot) {
        mGuider_r.gvt->track(2, mRcs_r->getRma(mTai));
    } else {
        mGuider_r.gvt->track(2);
    }

// Update the guider.
    mGuider_x_l = mGuider_l.gvt->x();
    mGuider_x_r = mGuider_r.gvt->x();
    mGuider_y_l = mGuider_l.gvt->y();
    mGuider_y_r = mGuider_r.gvt->y();
    mGcs_l->track(mTai, mGuider_x_l, mGuider_y_l);
    mGcs_r->track(mTai, mGuider_x_r, mGuider_y_r);
        
// Update the skyViews object to get an updated list of x/y positions of the
// sample star positions in the focal plane.
    tpk::Trajectory tip, tilt;
    mOcs_l->tiptilt(tip, tilt);
    mSkyView_l->genxy( mMcs->getRoll(mTai), mMcs->getPitch(mTai), 
            mRcs_l->getRma(mTai), mWindshake * tpk::TcsLib::as2r, 
            tip, tilt );
    mOcs_r->tiptilt(tip, tilt);
    mSkyView_r->genxy( mMcs->getRoll(mTai), mMcs->getPitch(mTai), 
            mRcs_r->getRma(mTai), mWindshake * tpk::TcsLib::as2r, 
            tip, tilt );
    
// Measure a star position with the guider.
    double xmeas, ymeas;
    tpk::Trajectory gx, gy;
    mGcs_l->xy(gx, gy);
    if ( mSkyView_l->measure( gx, gx, 2.0, xmeas, ymeas)) {
    
    // If a star was found pass the measured position to the guider.
        mGuider_l.gvt->measure(mTai, xmeas, ymeas);
        
    // If the guider is active send the correction to the pointing
    // controller.
        if (mGuider_l.guide) {
            mGuider_l.gvt->guidePM();
        }
    }
    
// Repeat for the other guider
    mGcs_r->xy(gx, gy);
    if ( mSkyView_r->measure( gx, gy, 2.0,xmeas, ymeas)) {
        mGuider_r.gvt->measure(mTai, xmeas, ymeas);
        if (mGuider_r.guide) {
            mGuider_r.gvt->guidePM();
        }
    }
}

void LbtPcs::uiExport() {

// Axes "achieved" positions in degrees.
    setUiVar( "az", mMcs->getAzimuth(mTai, tpk::RotaryAxis::achieved));
    setUiVar( "el", mMcs->getAltitude(mTai, tpk::RotaryAxis::achieved));
    setUiVar( "rma", "left", mRcs_l->getAxis(mTai, tpk::RotaryAxis::achieved));
    setUiVar( "rma", "right", mRcs_r->getAxis(mTai, tpk::RotaryAxis::achieved));

// Axes "demand" positions in degrees.
    setUiVar( "az_demand", mMcs->getAzimuth(mTai, tpk::RotaryAxis::demand));
    setUiVar( "el_demand", mMcs->getAltitude(mTai, tpk::RotaryAxis::demand));
    setUiVar( "rma_demand", "left", mRcs_l->getAxis(mTai, tpk::RotaryAxis::demand));
    setUiVar( "rma_demand", "right", mRcs_r->getAxis(mTai, tpk::RotaryAxis::demand));

// Axis "in-position" states.
    setUiVar( "az_in_position", mMcs->rollInPos());
    setUiVar( "el_in_position", mMcs->pitchInPos());
    setUiVar( "rot_in_position", "left", mRcs_l->inPos());
    setUiVar( "rot_in_position", "right", mRcs_r->inPos());

// Guider x/y position
    tpk::Trajectory gx, gy;
    mGcs_l->xy(gx, gy);
    setUiVar( "xguider", "left", gx);
    setUiVar( "yguider", "left", gy);
    mGcs_r->xy(gx, gy);
    setUiVar( "xguider", "right", gx);
    setUiVar( "yguider", "right", gy);
    setUiVar( "xguider_demand", "left", mGuider_x_l);
    setUiVar( "yguider_demand", "left", mGuider_x_l);
    setUiVar( "xguider_demand", "right", mGuider_y_r);
    setUiVar( "yguider_demand", "right", mGuider_y_r);

// Target position.
    tpk::Target* mtarg = mMount_l->getTarget();
    tpk::spherical tarpos = mtarg->position(mTai, tpk::ICRefSys());
    delete mtarg;
    setUiVar( "target_position", "left", 
            dpk::Util::formatRaDec( tarpos.a, tarpos.b));
    mtarg = mMount_r->getTarget();
    tarpos = mtarg->position(mTai, tpk::ICRefSys());
    delete mtarg;
    setUiVar( "target_position", "right", 
            dpk::Util::formatRaDec( tarpos.a, tarpos.b));
  
// Telescope position.
    tpk::Trajectory tip_l, tilt_l, tip_r, tilt_r;
    mOcs_l->tiptilt(tip_l, tilt_l);
    mOcs_r->tiptilt(tip_r, tilt_r);
    tpk::spherical telpos = mMount_l->position( mMcs->getRoll(mTai),
            mMcs->getPitch(mTai), mRcs_l->getRma(mTai), tip_l, tilt_l);
    setUiVar( "telescope_position", "left", 
            dpk::Util::formatRaDec( telpos.a, telpos.b));
    telpos = mMount_l->position( mMcs->getRoll(mTai),
            mMcs->getPitch(mTai), mRcs_r->getRma(mTai), tip_r, tilt_r);
    setUiVar( "telescope_position", "right", 
            dpk::Util::formatRaDec( telpos.a, telpos.b));

// Field orientation.
    double field_orient = mMount_l->orientation( mMcs->getRoll(mTai),
            mMcs->getPitch(mTai), mRcs_l->getRma(mTai), tip_l, tilt_l);
    setUiVar( "field_orient", "left", field_orient);
    setUiVar( "field_orientation", "left", field_orient / tpk::TcsLib::d2r);
    field_orient = mMount_r->orientation( mMcs->getRoll(mTai),
            mMcs->getPitch(mTai), mRcs_r->getRma(mTai), tip_r, tilt_r);
    setUiVar( "field_orient", "right", field_orient);
    setUiVar( "field_orientation", "right", field_orient / tpk::TcsLib::d2r);

// tip/tilt
    setUiVar( "tip", "left", mTip_l / tpk::TcsLib::as2r);
    setUiVar( "tip", "right", mTip_r / tpk::TcsLib::as2r);
    setUiVar( "tilt", "left", mTilt_l / tpk::TcsLib::as2r);
    setUiVar( "tilt", "right", mTilt_r / tpk::TcsLib::as2r);
    setUiVar( "tip_demand", "left", mTip_l / tpk::TcsLib::as2r);
    setUiVar( "tip_demand", "right", mTip_r / tpk::TcsLib::as2r);
    setUiVar( "tilt_demand", "left", mTilt_l / tpk::TcsLib::as2r);
    setUiVar( "tilt_demand", "right", mTilt_r / tpk::TcsLib::as2r);

// Focal plane positions of sample stars.
    mSkyView_l->uiExport("sample", "left");
    mSkyView_r->uiExport("sample", "right");
} 

/// Calculate remaining tracking time
/**
    \returns time at which the first limit is encountered
*/
//double LbtPcs::limit() {
//
//// Calculate limit time
//    std::pair<int,double> lim = mLimitCalc->limitTime(
//            mTai,180.0 - mRoll_a/tpk::TcsLib::d2r,
//            mPitch_a/tpk::TcsLib::d2r, mRma_a/tpk::TcsLib::d2r);
//
//// Convert reason to a string.
//    switch (lim.first) {
//        case tpk::LimitCalc::noLimit:
//            mLimitReason = "";
//            break;
//        case tpk::AltAzLimitCalc::azimuthLowLimit:
//            mLimitReason = "Azimuth low limit";
//            break;
//        case tpk::AltAzLimitCalc::azimuthHighLimit:
//            mLimitReason = "Azimuth high limit";
//            break;
//        case tpk::AltAzLimitCalc::zenithLimit:
//            mLimitReason = "Zenith limit";
//            break;
//        case tpk::AltAzLimitCalc::horizonLimit:
//            mLimitReason = "Horizon limit";
//            break;
//        case LbtLimitCalc::LeftRotatorLowLimit:
//            mLimitReason = "Left Rotator low limit";
//            break;
//        case LbtLimitCalc::LeftRotatorHighLimit:
//            mLimitReason = "Left Rotator high limit";
//            break;
//        case LbtLimitCalc::RightRotatorLowLimit:
//            mLimitReason = "Right Rotator low limit";
//            break;
//        case LbtLimitCalc::RightRotatorHighLimit:
//            mLimitReason = "Right Rotator high limit";
//            break;
//    }
//    return lim.second;
//}
