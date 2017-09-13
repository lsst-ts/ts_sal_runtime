/// \file GuiderControl.h
/// \brief Definition of the simulated guider control system

// D L Terrett
// Copyright STFC. All rights reserved.

#ifndef dpkGUIDERCONTROL_H
#define dpkGUIDERCONTROL_H

#include <string>
#include "tpk.h"
#include "Pcs.h"
#include "Axis.h"

namespace dpk {

/// A guider control object simulates the axes of a guide probe.
/***
    This implementation simulates an X/Y slider mechanism so that
    the two axes map onto the x and y axes of the guider coordinate
    system.
*/
    class GuiderControl {
        public:
            GuiderControl(
                Pcs& pcs,
                const std::string& name1,
                const std::string& name2
            );           
            virtual ~GuiderControl() {
                delete mAxis1;
                delete mAxis2;
            }
            virtual void track(
                double tai,
                const tpk::Trajectory& x,
                const tpk::Trajectory& y
            );
            
        ///  axis position
            virtual void xy(
                tpk::Trajectory& x,
                tpk::Trajectory& y
            ) {
                x = mAxis1->position(); 
                y = mAxis2->position();
            }
                
        ///  guider in position status
        /**
            \returns in position status
        */
            virtual bool inPos() {
                return mInPos1 && mInPos2;
            }
                        
        protected:
            tpk::Trajectory mX;
            tpk::Trajectory mY;
            dpk::Axis* mAxis1;
            dpk::Axis* mAxis2;
            bool mInPos1;
            bool mInPos2;
        
        public:
            static double GUIDER_LOLIM;   ///< Guider low limit
            static double GUIDER_HILIM;   ///< Guider high limit
            static double GUIDER_INIT;    ///< Guider initial position
            static double GUIDER_DVMAX;   ///< Guider maximum velocity
            static double GUIDER_DAMAX;   ///< Guider max acceleration
            static double GUIDER_DJMAX;   ///< Guider max jerk
            static double GUIDER_GS;      ///< Guider square root gain
            static double GUIDER_GP;      ///< Guider proportional gain
            static double GUIDER_GI;      ///< Guider integral gain
            static double GUIDER_PI;      ///< Guider integrator window
            static double GUIDER_GD;      ///< Guider derivative gain
            static double GUIDER_PNEAR;   ///< Guider "near enough"
     };
}
#endif
