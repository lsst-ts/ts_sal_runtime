/// \file TimeKeeper.h
/// \brief Definition of the TimeKeeper class

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkTIMEKEEPER_H
#define tpkTIMEKEEPER_H

#include <exception>
#include <stdexcept>

#include "TcsMutex.h"

namespace tpk {
    class Clock;
    class Site;

/// Time keeper
/**
    A TimeKeeper object provides the instant in time that all the kernel
    calculations are done. Its update method, which reads the real-time
    clock should be called before calling the update methods of all the
    kernel virtual telescopes and other objects.

    A TimeKeeper is associated with a Clock (which it reads each time the 
    update method is called) and a Site.

    All the methods of this class are thread safe.
*/
    class TimeKeeper {
        friend class AutoGuider;
        friend class BaseVt;
        friend class MountVt;
        friend class OpticsVt;
        friend class PointingLog;
        public:
            TimeKeeper(
                Clock& clock,
                const Site& site
            ) throw(std::runtime_error);
            TimeKeeper(const TimeKeeper&);
            void update() throw();
            double tai() const throw();
        protected:
            Clock& mClock;              ///< clock
            const Site& mSite;          ///< telescope site
            mutable TcsMutex mMutex;    ///< mutex
            double mTai;                ///< time TAI (MJD)
            double mTt;                 ///< TT time at Tai (MJD)
            double mCst;                ///< cosine of sidereal time
            double mSst;                ///< sine of sidereal time
            double mDcst;               ///< rate of change of Cst per sample 
                                        ///  interval
            double mDsst;               ///< rate of change of Sst per sample 
                                        ///  interval
        private:
        // No assigment operator
            TimeKeeper& operator=(const TimeKeeper&);
    };
}
#endif

