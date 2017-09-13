/// \file LbtPcs.h
/// \brief Definition of the LbtPcs class

#ifndef dpkLBTPCS_H
#define dpkLBTPCS_H

#include "dpk.h"
#include "TclClock.h"

class LbtPcs : public dpk::Pcs {
    public:

    // We need to implement a constructor and destructor...
        LbtPcs(Tcl_Interp* interp);
        ~LbtPcs();

    // the "fast" process...
        void update();

    // and the method that updates the user interface.
        void uiExport();
        
    // The method that calculates the remaining tracking time
        //double limit();      

    // Pointers to all the permanent tpk objects our pointing kernel needs.
        tpk::MountVt* mMount_l;
        tpk::MountVt* mMount_r;
        tpk::OpticsVt* mOptics_l;
        tpk::OpticsVt* mOptics_r;
        tpk::PointingControl* mPcontrol_l;
        tpk::PointingControl* mPcontrol_r;
        tpk::PiFilter* mAzFilter_l;
        tpk::PiFilter* mAzFilter_r;
        tpk::PiFilter* mElFilter_l;
        tpk::PiFilter* mElFilter_r;
        tpk::Transform* mTransform;
        guider mGuider_l;
        guider mGuider_r;

    // Az, el, rotator and guider control systems.
        dpk::AltAzMountControl* mMcs;
        dpk::RotatorControl* mRcs_l;
        dpk::RotatorControl* mRcs_r;
        dpk::GuiderControl* mGcs_l;
        dpk::GuiderControl* mGcs_r;
        dpk::OpticsControl* mOcs_l;
        dpk::OpticsControl* mOcs_r;
        
        tpk::Trajectory mRoll_d;
        tpk::Trajectory mPitch_d;
        tpk::Trajectory mTip_l;
        tpk::Trajectory mTilt_l;
        tpk::Trajectory mTip_r;
        tpk::Trajectory mTilt_r;

    // Demand and achieved guider axis trajectories.
        tpk::Trajectory mGuider_x_l;
        tpk::Trajectory mGuider_x_r;
        tpk::Trajectory mGuider_y_l;
        tpk::Trajectory mGuider_y_r;
                
    // Sky view object for plotting the artifical star field.
        dpk::SkyView* mSkyView_l;
        dpk::SkyView* mSkyView_r;

// Declare the copy constructor and assigment operators as private since
// the default implementations won't work and we don't want to bother writing
// versions that do work since we are not going to need them.
    private:
        LbtPcs(const LbtPcs&);
        LbtPcs& operator=(const LbtPcs&);
};

#endif

