/// \file AltAzLimitCalc.h
/// \brief Definition of the generic Alt/Az limit calculator class.

// D L Terrett
// Copyright STFC. All rights reserved.

#ifndef tpkALTAZROTLIMITCALC_H
#define tpkALTAZROTLIMITCALC_H

#include <utility>

#include "AltAzLimitCalc.h"

namespace tpk {
    class MountVt;
    class Site;

/// Alt Az and rotator Time to limit calculator class
/**
    This is a limit calculator for a generic Alt/Az mount with a rotator. 
    The azimuth and rotator axes are assumed to have a range to travel of 
    up to two revolutions.
*/
    class AltAzRotLimitCalc : public AltAzLimitCalc {
        public:
            AltAzRotLimitCalc(
                const Site& site,        ///< Telescope site
                const MountVt& mount,    ///< mount virtual telescope
                double azlowlim,         ///< azimuth low limit (degrees)
                double azhighlim,        ///< azimuth high limit (degrees)
                double altlowlim,        ///< altitude low limit (degrees)
                double althighlim,       ///< altitude high limit (degrees)
                double rotlowlim,        ///< rototor low limit (degrees)
                double rothighlim        ///< rotator high limit (degrees)
            ) : AltAzLimitCalc(site,mount,azlowlim,azhighlim,altlowlim,althighlim),
                    mRotLowLim(rotlowlim), mRotHighLim(rothighlim) {}
            virtual std::pair<int,double> limitTime(
                double t0,
                double az,
                double alt,
                double rma
            );        
                    
            static const int rotatorLowLimit = 5;     ///< limit code
            static const int rotatorHighLimit = 6;    ///< limit code

        protected:
            int inLimit(
                double t
            );
            int closeToLimit(
                double t
            );
            Trajectory mRma;            ///< rotator trajectory
            double mRotLowLim;          ///< low limit (degrees)
            double mRotHighLim;         ///< high limit (degrees)
        private:
            AltAzRotLimitCalc();
    };
}
#endif

