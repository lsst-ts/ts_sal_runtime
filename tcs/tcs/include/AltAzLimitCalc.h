/// \file AltAzLimitCalc.h
/// \brief Definition of the generic Alt/Az limit calculator class.

// D L Terrett
// Copyright STFC. All rights reserved.

#ifndef tpkALTAZLIMITCALC_H
#define tpkALTAZLIMITCALC_H

#include <utility>

#include "LimitCalc.h"
#include "MountVt.h"
#include "Trajectory.h"

namespace tpk {
    class Site;

/// Alt Az Time to limit calculator class
/**
    This is a limit calculator for a generic Alt/Az mount. The azimuth
    axis is assumed to have a range to travel of up to two revolutions.
    The rotator is assumed not to have any limits.
*/
    class AltAzLimitCalc : public LimitCalc {
        public:
            AltAzLimitCalc(
                const Site& site,        ///< Telescope site
                const MountVt& mount,    ///< mount virtual telescope
                double azlowlim,         ///< azimuth low limit (degrees)
                double azhighlim,        ///< azimuth high limit (degrees)
                double altlowlim,        ///< altitude low limit (degrees)
                double althighlim        ///< altitude high limit (degrees)
            ) : LimitCalc(site), mMount(mount), mAzLowLim(azlowlim), 
                    mAzHighLim(azhighlim), mAltLowLim(altlowlim), 
                    mAltHighLim(althighlim) {}                                 
            virtual std::pair<int,double> limitTime(
                double t0,
                double az,
                double el
            );        
                    
            static const int azimuthLowLimit = 1;     ///< limit code
            static const int azimuthHighLimit = 2;    ///< limit code
            static const int horizonLimit = 3;        ///< limit code
            static const int zenithLimit = 4;         ///< limit code

        protected:
            int inLimit(
                double t
            );
            int closeToLimit(
                double t
            );
            void startLoop(
                const Site& site,
                const TimeKeeper& timeKeeper
            );
            void endLoop();
            const MountVt& mMount;          ///< mount virtual telescope
            MountVt::Ptr mMountCopy;        ///< copy of virtual telescope
            Trajectory mAz;                 ///< azimuth trajectory
            Trajectory mAlt;                 ///< altitude trajectory
            double mAzLowLim;               ///< azimuth axis low limit
            double mAzHighLim;              ///< azimuth axis high limit
            double mAltLowLim;               ///< altitude axis low limit
            double mAltHighLim;              ///< altitude axis high limit
        private:
            AltAzLimitCalc();
    };
}
#endif

