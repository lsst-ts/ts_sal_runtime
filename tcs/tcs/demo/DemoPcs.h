/// \file DemoPcs.h
/// \brief Definition of the DemoPcs class

#ifndef dpkDEMOPCS_H
#define dpkDEMOPCS_H

#include "tpk.h"
#include "dpk.h"

#include "SAL_rotator.h"
#include "SAL_MTMount.h"
#include "ccpp_sal_rotator.h"
#include "ccpp_sal_MTMount.h"
#include "os.h"


//#include "example_main.h"

class DemoPcs : public dpk::Pcs {
    public:

    // We need to implement a constructor and destructor...
        DemoPcs(Tcl_Interp* interp);
        ~DemoPcs();

    // the "fast" process...
        void update();

    // and the method that updates the user interface.
        void uiExport();
        
    // The method that calculates the remaining tracking time
        double limit();
        
    // Pointers to all the permanent tpk objects our pointing kernel needs.
        tpk::MountVt* mMount;
        tpk::PointingControl* mPcontrol;
        tpk::Filter* mAzFilter;
        tpk::Filter* mElFilter;
        tpk::Transform* mTransform;
        guider mGuider;
        
    // Mount, rotator and guider control systems.
        dpk::AltAzMountControl* mMcs;
        dpk::RotatorControl* mRcs;
        dpk::GuiderControl* mGcs;

    // Demand guider axis trajectories.
        tpk::Trajectory mGuider_x;
        tpk::Trajectory mGuider_y;
        
    // LimitCalc object for calculating the remaining tracking time.
        tpk::AltAzRotLimitCalc* mLimitCalc;

    // Sky view object for plotting the artifical star field.
        dpk::SkyView* mSkyView;

    // SAL tcs interface       
        SAL_MTMount* salMNT;
        SAL_rotator* salROT;

 
// Declare the copy constructor and assigment operators as private since
// the default implementations won't work and we don't want to bother writing
// versions that do work since we are not going to need them.
    private:
        DemoPcs(const DemoPcs&);
        DemoPcs& operator=(const DemoPcs&);
};

#endif

