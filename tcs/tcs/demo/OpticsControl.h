/// \file OpticsControl.h
/// \brief Definition of the simulated optics control system

// D L Terrett
// Copyright STFC. All rights reserved.

#ifndef dpkOPTICSCONTROL_H
#define dpkOPTICSCONTROL_H

#include <string>
#include "tpk.h"
#include "Pcs.h"

namespace dpk {

/// A guider control object simulates the axes of a tip/tilt optics system.
/**
    This simulation simply sets the actual position to the demand
    position as if the system reacts instantaneously.
*/
    class OpticsControl {
        public:
            OpticsControl(
                Pcs& pcs,                   ///< PCS
                const std::string& name1,   ///< first axis name
                const std::string& name2    ///< second axis name
            ) : mX(0.0), mY(0.0), mInPosX(true), mInPosY(true) {}         
            virtual ~OpticsControl() {}
            virtual void track(
            double tai,
            const tpk::Trajectory& tip,
            const tpk::Trajectory& tilt
            );
            
        ///  axis position
            virtual void tiptilt(
                tpk::Trajectory& tip,
                tpk::Trajectory& tilt
            ) {
                tip = mX; 
                tilt = mY;
            }
                
        ///  optics in position status
        /**
            \returns in position status
        */
            virtual bool inPos() {
                return mInPosX && mInPosY;
            }
                        
       protected:
            tpk::Trajectory mX;     ///< achieved x axis trajectory
            tpk::Trajectory mY;     ///< achieved y axis trajectory
            bool mInPosX;           ///< x axis in position flag
            bool mInPosY;           ///< y axis in position flag
    
       public:
            static double X_LOLIM;   ///< tip low limit
            static double X_HILIM;   ///< tip high limit
            static double Y_LOLIM;   ///< tilt low limit
            static double Y_HILIM;   ///< tilt high limit
     };
 
}
#endif
