/// \file DemoPcs.cpp
/// \brief Implementation of the demonstration PCS class

// D L Terrett
// Copyright STFC 2007

#include "DemoPcs.h"

#include "dpk.h"
#include "TclClock.h"

//#include "SAL_dome.h"
//#include "SAL_hexapod.h"
#include "SAL_MTMount.h"
#include "SAL_rotator.h"

using namespace DDS;
//using namespace dome;
using namespace rotator;
//using namespace hexapod;
using namespace MTMount;

DemoPcs::DemoPcs(
    Tcl_Interp* interp
) : Pcs(interp) {

// Initialize the SAL Telemetry
    salMNT = new SAL_MTMount();
    salMNT->salCommand("MTMount_command_trackTarget");
    salMNT->salTelemetryPub("MTMount_MotionParameters");
    salROT = new SAL_rotator();

// Rotator for SAL V3.0
    salROT->salCommand();
// Rotator for SAL V3.5 and onwards
//    salROT->salCommand("rotator_command_track");


//    salDOM = new SAL_dome();
//    salDOM->salCommand("dome_command_Move");
//    salDOM->salCommand("dome_command_Crawl");
//    salCAMHEX = new SAL_hexapod(1);
//    salCAMHEX->salCommand("hexapod_command_move");
//    salM2HEX = new SAL_hexapod(2);
//    salM2HEX->salCommand("hexapod_command_move");
    lastRotatorAngle=0.0; 
    last_az=0.0;
    last_el=0.0;
    last_azvel=0.0;
    last_elvel=0.0;
    last_azacc=0.0;
    last_elacc=0.0;

// Create the clock. At this time (09/02/2015) TAI is offset from UTC by
// 35 seconds.
    mClock = new tpk::TclClock(35.0);
    
// Set the current time member variable.
    mTai = mClock->read();
    lastRotatorAngle = 0.0;

// Create the "site"
    mSite = new tpk::Site( mTai,
            0.0,                          // UT1 - UTC
            35.0,                         // TAI - UTC
            32.184,                       // TT - TAI
            -70.749,                     // LSST East longitude
            -30.2444,                     // Latitude
            2650.00,                      // Height
            0.0, 0.0);                    // Polar motion
            
// Set the telescope focal length (mm).
    mFocalLength = 100000.0;

// Create the time keeper object.
    mTimeKeeper = new tpk::TimeKeeper(*mClock, *mSite);

// Create a mount virtual telescope.
    mMount = new tpk::MountVt( *mTimeKeeper, *mSite, tpk::Cassegrain(),
            tpk::AltAzMountType());

// Instrument (and guider) to focal plane coordinate transformation.
    mTransform = new tpk::AffineTransform( 0.0, 0.0, 1.0/mFocalLength, 0.0);

// Pointing controller and associated filters. The guide filter can be a local
// variable because the AutoGuider object makes a copy and the origonal filter
// object can then be discarded.
    mAzFilter = new tpk::PiFilter(0.05);
    mElFilter = new tpk::PiFilter(0.05);
    mPcontrol = new tpk::PointingControl( *mMount, *mAzFilter, *mElFilter );

// Create an auto-guider virtual telescope.
    mGuider.gvt = new tpk::AutoGuider( *mMount, *mPcontrol, *mTransform,
        tpk::Filter2D());
        
// Create an initial target for the mount and guider that matches the initial
// axes positions.
    tpk::AzElTarget deftarg(*mSite, 
            dpk::AltAzMountControl::AZ_INIT * tpk::TcsLib::d2r,
            dpk::AltAzMountControl::ALT_INIT * tpk::TcsLib::d2r);
    mMount->newTarget(deftarg);
    mGuider.gvt->newTarget(deftarg);
            
// Set the initial field orientation.
    mMount->setPai( 0.0, tpk::ICRefSys(),true);

// Create sky view for plotting the artifical star field for this mount.
    mSkyView = new dpk::SkyView(*mMount, *mTransform, *this, "sky", 
            mSkySamples);

   dpk::RotatorControl::ROT_LOLIM = -180.0;
   dpk::RotatorControl::ROT_HILIM = 180.0;
       
// Create the limit calcualtor
    mLimitCalc = new tpk::AltAzRotLimitCalc(*mSite, *mMount,
            dpk::AltAzMountControl::AZ_LOLIM,
            dpk::AltAzMountControl::AZ_HILIM,
            dpk::AltAzMountControl::ALT_LOLIM,
            dpk::AltAzMountControl::ALT_HILIM,
            dpk::RotatorControl::ROT_LOLIM,
            dpk::RotatorControl::ROT_HILIM);
 
    
// Initialise the context.
    mMount->track(1);
    mGuider.gvt->track(1);
    
// Create the mount and rotator control systems
    mMcs = new dpk::AltAzMountControl(*this, "azimuth", "elevation");
    mRcs = new dpk::RotatorControl(*this, "rotator");
    
// Create guider control system.
    mGcs = new dpk::GuiderControl(*this, "guider_x", "guider_y");

// Register the mount.
    registerMount(mMount, "mount");

// Register the pointing controller.
    registerPointingControl(mPcontrol, "mount");

// Register the guider.
    registerGuider(&mGuider, "guider");

  
}


DemoPcs::~DemoPcs() {
    delete mClock;
    delete mTimeKeeper;
    delete mSite;
    delete mMount;
    delete mTransform;
    delete mPcontrol;
    delete mAzFilter;
    delete mElFilter;
    delete mGuider.gvt;
    delete mSkyView;
    delete mMcs;
    delete mRcs;
    delete mGcs;
    delete mLimitCalc;
}

void DemoPcs::update () {

// Update the pointing controller
    mPcontrol->update();

// Track the mount. We request two position samples so that we can pass
// velocity information to the simulated axis servos.
    mMount->track(2, mRcs->getRma(mTai));

// Update the axes
    mMcs->track(mTai,  mMount->roll(), mMount->pitch());
    mRcs->track(mTai, mMount->rma());

    
// Track the auto-guider with or without the achieved rotator
// position according to the flag in the guider structure.
    if (mGuider.track_rot) {
        mGuider.gvt->track(2, mRcs->getRma(mTai));
    } else {
        mGuider.gvt->track(2);
    }

// Update the guider.
    mGuider_x = mGuider.gvt->x();
    mGuider_y = mGuider.gvt->y();
    mGcs->track(mTai, mGuider_x, mGuider_y);
    
// Update the skyView object to get an updated list of x/y positions of the
// sample star positions in the focal plane.
//    mSkyView->genxy( mMcs->getRoll(mTai), mMcs->getPitch(mTai), mRcs->getRma(mTai), 
//            mWindshake * tpk::TcsLib::as2r);
    
// Measure a star position with the guider.
    double xmeas, ymeas;
    tpk::Trajectory gx, gy;
    mGcs->xy(gx, gy);
    if ( mSkyView->measure( gx, gy, 2.0, xmeas, ymeas)) {
    
    // If a star was found pass the measured position to the guider.
        mGuider.gvt->measure(mTai, xmeas, ymeas);
        
    // If the guider is active send the correction to the pointing
    // controller.
        if (mGuider.guide) {
            mGuider.gvt->guidePM();
        }
    }
}


void DemoPcs::uiExport() {
    char tpos[128], rpos[128];
    int	 cmdId;
    MTMount_command_trackTargetC mount_track;
    MTMount_MotionParametersC    mount_motion;
    rotator_command_trackC       rotator_track;
    rotator::command 		 rotator_cmd;

// Axes "achieved" positions in degrees.
    setUiVar("az", mMcs->getAzimuth(mTai, tpk::RotaryAxis::achieved));
    setUiVar("el", mMcs->getAltitude(mTai, tpk::RotaryAxis::achieved));
//    setUiVar("rma", "mount", mRcs->getAxis(mTai, tpk::RotaryAxis::achieved));

// Axes "demand" positions in degrees.
    setUiVar("az_demand", mMcs->getAzimuth(mTai, tpk::RotaryAxis::demand));
    setUiVar("el_demand", mMcs->getAltitude(mTai, tpk::RotaryAxis::demand));
//    setUiVar("rma_demand", "mount", mRcs->getAxis(mTai, tpk::RotaryAxis::demand));

// Axis "in-position" states.
    setUiVar( "az_in_position", mMcs->rollInPos());
    setUiVar( "el_in_position", mMcs->pitchInPos());
    setUiVar( "rot_in_position", "mount", mRcs->inPos());

// Guider x/y position
    tpk::Trajectory gx, gy;
    mGcs->xy(gx, gy);
    setUiVar( "xguider", "guider", gx);
    setUiVar( "yguider", "guider", gy);
    setUiVar( "xguider_demand", "guider", mGuider_x);
    setUiVar( "yguider_demand", "guider", mGuider_y);

// Target position.
    tpk::Target* mtarg = mMount->getTarget();
    tpk::spherical tarpos = mtarg->position(mTai, tpk::ICRefSys());
    delete mtarg;
    setUiVar( "target_position", "mount", 
            dpk::Util::formatRaDec( tarpos.a, tarpos.b));
  
// Telescope position.
    tpk::spherical telpos = mMount->position( mMcs->getRoll(mTai),
            mMcs->getPitch(mTai), mRcs->getRma(mTai));
    setUiVar( "telescope_position", "mount", 
            dpk::Util::formatRaDec( telpos.a, telpos.b));


// Field orientation.
    double field_orient = mMount->orientation(mMcs->getRoll(mTai),
            mMcs->getPitch(mTai), mRcs->getRma(mTai));
    setUiVar( "field_orient", "mount", field_orient);
    setUiVar( "field_orientation", "mount", 
            field_orient / tpk::TcsLib::d2r);

// No tip/tilt for this demonstration examples.
    setUiVar( "tip_demand", "mount", 0.0);
    setUiVar( "tilt_demand", "mount", 0.0);
    setUiVar( "tip", "mount", 0.0);
    setUiVar( "tilt", "mount", 0.0);

// Focal plane positions of sample stars.
    mSkyView->uiExport("sample", "mount");

// Update telemetry
//	publish_kernel_Target->t0     = gx.timestamp();
//	publish_kernel_Target->az     = mMcs->getAzimuth(mTai, tpk::RotaryAxis::demand);
//	publish_kernel_Target->el     = mMcs->getAltitude(mTai, tpk::RotaryAxis::demand);
//	publish_kernel_Target->Wavel  = 0.5;
//	publish_kernel_Target->azdot  = tarpos.a;
//	publish_kernel_Target->eldot  = tarpos.b;
//	publish_kernel_Target->XOffset= gx;
//	publish_kernel_Target->YOffset= gy;
//	publish_kernel_Target->Tai    = mTai;
//	publish_kernel_Target->TLR    = 5.0;
//	publish_kernel_Target->Humid  = mSite->humidity();
//	publish_kernel_Target->Press  = mSite->pressure();
//	publish_kernel_Target->Temp   = mSite->temperature();
//	salTCS->putSample_kernel_Target(publish_kernel_Target);
    double rotatorAngle,rotatorVelocity,rawTAI,fixTAI;
    double filterTai = floor(mTai * 1728000.0) / 1728000.0;
    double az_vel , el_vel;
    double az_acc , el_acc;
    double az_jerk , el_jerk;
    rawTAI = (filterTai - 40587.0) * 86400.0;
//    fixTAI = (double)(int(rawTAI/20.) * 20.0);
    fixTAI=rawTAI;
//   printf("mTai, filterTai, rawTAI, fixTAI = %16.6lf %16.6lf %16.6lf %16.6lf  \n",mTai,filterTai,rawTAI,fixTAI); 


// Rotator for SAL V3.0
    rotator_cmd.device = DDS::string_dup("target");
    rotator_cmd.property = DDS::string_dup("position");
    rotator_cmd.action = DDS::string_dup("set");
    rotatorAngle = mRcs->getAxis(filterTai, tpk::RotaryAxis::demand);

    double vel_scale = 1.0;
    if (rotatorAngle < -180.0) {rotatorAngle = rotatorAngle+360.0;}
    if (rotatorAngle > 180.0)  {rotatorAngle = rotatorAngle-360.0;}
    if (rotatorAngle < -180.0) {rotatorAngle = rotatorAngle+360.0;}
    if (rotatorAngle > 180.0)  {rotatorAngle = rotatorAngle-360.0;}

    if(rotatorAngle < 0) vel_scale = -1.0;
    rotatorAngle = (abs(rotatorAngle) - 90);

    rotatorVelocity = vel_scale*mMount->rma().sample(mTai,1)*(180./3.1415926535/24./3600.);

    if (rotatorVelocity > 1.0) {rotatorVelocity = 1.0;}
    if (rotatorVelocity < -1.0) {rotatorVelocity = -1.0;}
    lastRotatorAngle = rotatorAngle;
    sprintf(rpos,"angle=%lf velocity=%lf tai=%lf", rotatorAngle, rotatorVelocity, fixTAI);
    rotator_cmd.modifiers = DDS::string_dup(rpos);
    cmdId = salROT->issueCommand(rotator_cmd);

    setUiVar("rma", "mount", rotatorAngle);
    setUiVar("rma_demand", "mount", rotatorAngle);


// Rotator for SAL V3.5 and onwards
    rotator_track.device = DDS::string_dup("rotator");
    rotator_track.property = DDS::string_dup("position");
    rotator_track.action = DDS::string_dup("set");
//    rotatorAngle = mRcs->getAxis(filterTai, tpk::RotaryAxis::demand);
//    rotatorVelocity = (rotatorAngle - lastRotatorAngle) * 20.0;
//    lastRotatorAngle = rotatorAngle;
//    sprintf(rpos,"tai=%16.3lf , angle=%16.6lf , velocity=%16.6lf", fixTAI, rotatorAngle, rotatorVelocity);
    rotator_track.angle = rotatorAngle;
    rotator_track.velocity = rotatorVelocity;
    rotator_track.tai = fixTAI;
    cmdId = salROT->issueCommand_track(&rotator_track);




    mount_track.device = DDS::string_dup("target");
    mount_track.property = DDS::string_dup("position");
    mount_track.action = DDS::string_dup("set");
//    sprintf(tpos,"azimuth=%16.6lf elevation=%16.6lf az_vel=%16.6lf  el_vel=%16.6lf",
//                  mMcs->getAzimuth(filterTai, tpk::RotaryAxis::demand),
//                  mMcs->getAltitude(filterTai, tpk::RotaryAxis::demand),az_vel,el_vel); 
    mount_track.az_angle = mMcs->getAzimuth(filterTai, tpk::RotaryAxis::demand);
    mount_track.el_angle = mMcs->getAltitude(filterTai, tpk::RotaryAxis::demand);
    mount_track.time = fixTAI;
    mount_track.az_velocity = mMount->roll().sample(mTai,1)*180./3.1415926535/24./3600.;
    mount_track.el_velocity = mMount->pitch().sample(mTai,1)*180./3.1415926535/24./3600.;
    mount_track.time = fixTAI;
    if ( rotator_track.velocity > 0.0 ) {
       mount_track.cablewrap_orientation="CW";
    } else {
       mount_track.cablewrap_orientation="CCW";
    }
    cmdId = salMNT->issueCommand_trackTarget(&mount_track);

//    last_az = mount_track.az_angle;
//    last_el = mount_track.el_angle;

//    az_acc = (az_vel - last_azvel);
//    el_acc = (el_vel - last_elvel);
//    last_azvel = az_vel;
//    last_elvel = el_vel;

//    az_jerk = (az_acc - last_azacc);
//    el_jerk = (el_acc - last_elacc);
//    last_azacc = az_acc;
//    last_elacc = el_acc;

    mount_motion.Azimuth_Position = mount_track.az_angle;
    mount_motion.Azimuth_Velocity = mount_track.az_velocity;
    mount_motion.Azimuth_Acceleration = az_acc;
    mount_motion.Azimuth_Jerk = az_jerk;
    mount_motion.Elevation_Position = mount_track.el_angle;
    mount_motion.Elevation_Velocity = mount_track.el_velocity;
    mount_motion.Elevation_Acceleration = el_acc;
    mount_motion.ElevationJerk = el_jerk;
    salMNT->putSample_MotionParameters(&mount_motion);


} 

/// Calculate remaining tracking time
/**
    \returns time at which the first limit is encountered
*/
double DemoPcs::limit() {

// Calculate limit time
    std::pair<int,double> lim = mLimitCalc->limitTime(mTai,
        mMcs->getAzimuth(mTai, tpk::RotaryAxis::achieved),
        mMcs->getAltitude(mTai, tpk::RotaryAxis::achieved),
        mRcs->getAxis(mTai, tpk::RotaryAxis::achieved));

// Convert reason to a string.
    switch (lim.first) {
        case tpk::LimitCalc::noLimit:
            mLimitReason = "";
            break;
        case tpk::AltAzLimitCalc::azimuthLowLimit:
            mLimitReason = "Azimuth low limit";
            break;
        case tpk::AltAzLimitCalc::azimuthHighLimit:
            mLimitReason = "Azimuth high limit";
            break;
        case tpk::AltAzLimitCalc::zenithLimit:
            mLimitReason = "Zenith limit";
            break;
        case tpk::AltAzLimitCalc::horizonLimit:
            mLimitReason = "Horizon limit";
            break;
        case tpk::AltAzRotLimitCalc::rotatorLowLimit:
            mLimitReason = "Rotator low limit";
            break;
        case tpk::AltAzRotLimitCalc::rotatorHighLimit:
            mLimitReason = "Rotator high limit";
            break;
    }
    return lim.second;
}
