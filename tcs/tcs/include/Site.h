/// \file Site.h
/// \brief Definition of the site class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkSITE_H
#define tpkSITE_H

#include <stdexcept>

#include "TcsMutex.h"

namespace tpk {

/// Telecope site
/**
    A site defines the location of the telescope. It:

    -  Calculates the latitude and longitude of the telescope corrected
       for polar motion and the diurnal correction to azimuth.
    -  Maintains the parameter arrays used by the slalib quick mean to
       apparent and apparent to observed place routines.
    -  Maintains a reference time in a variety of time scales so that
       time conversions can be done with simple extrapolation.

    Its refresh method must be called at some suitable interval, typically
    once a minute, with the current temperature, atmospheric pressure
    and humidity.

    All the methods of this class are thread safe.
*/
    class Site {
        friend class AutoGuider;
        friend class BaseVt;
        friend class KernelWcs;
        friend class MountVt;
        friend class OpticsVt;
        friend class PointingObs;
        friend class TimeKeeper;
        public:
            Site(
                double tai,
                double delat,
                double delut,
                double ttmtai,
                double elongm,
                double latm,
                double hm,
                double xpm,
                double ypm
            ) throw(std::runtime_error);
            Site(const Site&);
            virtual ~Site() {}
            virtual void refresh(
                double tai,
                double temp,
                double press,
                double hum
            ) throw();
            virtual void earthOrientation(
                double delut,
                double delat,
                double xpm,
                double ypm
            ) throw(std::runtime_error);
            virtual void refresh(
                double tai
            ) throw();
            double tai() const throw() {return mTai;}
         
        /// Get TAI - UTC
        /**
            \returns TAI-UTC (days)
        */
            double delat() const throw() {return mDelat;}
         
        /// Get UT1 - UTC
        /**
            \returns UT1 -UTC (days)
        */
            double delut() const throw() {return mDelut;}
            
        /// Get current temperature
        /**
            \returns temperature (degrees K)
        */
            double temperature() const throw() {return mTemp;}
            
        /// Get current atmopheric pressure
        /**
            \returns pressure (mBar)
        */
            double pressure() const throw() {return mPress;}
            
        /// Get current humidity
        /**
            \returns relative humidity
        */
            double humidity() const throw() {return mHumid;}
            
        /// Get site longitude
        /**
            \returns true east longitude (radians)
        */
            double elongitude() const throw() {return mElong;}
            
        /// Get site latitude
        /**
            \returns true latitude (radians)
        */
            double latitude() const throw() {return mLat;}
            
        /// Get diurnal correction to azimuth
        /**
            \returns azimuth correction (terrestrial - celestial, radians)
        */
            double daz() const throw() {return mDaz;}
            
        /// Get diurnal aberration
        /**
            \returns diurnal aberration (radians)
        */
            double diurab() const throw() {return mDiurab;}
            
            double st( double t ) const throw();
            double tt( double t ) const throw();
            double ttj( double t ) const throw();
            void amprms(double amprms[21]) const throw();
            void aoprms(double aoprms[21]) const throw();
        protected:
            mutable TcsMutex mMutex;      ///< mutex
            const double mElongm;         ///< mean east longitude (radians)
            const double mLatm;           ///< mean latitude (radians)
            const double mHm;             ///< height (metres)
            const double mTtmtai;         ///< TT - TAI (days)
            double mXpm;                  ///< polar motion in x (radians)
            double mYpm;                  ///< polar motion in  y(radians)
            double mDelut;                ///< UT1 - UTC (days)
            double mDelat;                ///< TAI - UTC (days)
            double mElong;                ///< corrected east longitude (radians)
            double mLat;                  ///< corrected latitude (radians)
            double mUau;                  ///< distance from spin axis (AU)
            double mVau;                  ///< distance from equator (AU)
            double mUkm;                  ///< distance from spin axis (km)
            double mVkm;                  ///< distance from equator (km)
            double mDiurab;               ///< diurnal aberration (radians)
            double mTemp;                 ///< current temperature (deg K)
            double mPress;                ///< current pressure (mBar)
            double mHumid;                ///< current relative humidity
            double mTai;                  ///< current time (TAI, MJD)
            double mT0;                   ///< reference epoch (TAI, MJD)
            double mSt0;                  ///< reference siderial time (radians)
            double mTt0;                  ///< reference time (TT, MJD)
            double mTtj;                  ///< reference time (TT, Julian date)
            double mAmprms[21];           ///< apparent to mean parameters
            double mAoprms[15];           ///< apparent to observed parameters
            double mRefa;                 ///< tan refraction constant
            double mRefb;                 ///< tan**3 refraction constant
            double mDaz;                  ///< azimuth correction (radians)
        private:
        // No default constructor or assignment operator
            Site();
            Site& operator=(const Site&);
    };
}
#endif

