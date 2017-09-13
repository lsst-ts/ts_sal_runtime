/// \file PointingObs.h
/// \brief Defintion of the pointing observation class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkPOINTINGOBS_H
#define tpkPOINTINGOBS_H

#include "TcsLib.h"

namespace tpk {
    class MountVt;

/// Pointing observation
/**
    The Pointing Observation class is a base class for classes that log 
    pointing observations.
*/
    class PointingObs {
        public:
            PointingObs(
                const MountVt& mountvt
                ) throw();
            virtual ~PointingObs() {}
            void mark();
        protected:
            double mTaiStart;          ///< log start time (TAI, MJD)
            double mDelut;             ///< UT1 - UTC (days)
            double mDelat;             ///< TAI - UTC (days)
            double mTtmtai;            ///< TT -TAI (days)
            double mElongm;            ///< true east longitude (radians)
            double mLatm;              ///< true latitude (radians)
            double mHm;                ///< height (metres)
            double mXpm;               ///< polar motion x (radians)
            double mYpm;               ///< polar motion y (radians)
            TcsLib::mtype mMtype;      ///< Mount type
            double mGim1z;             ///< 1st gimbal angle (radians)
            double mGim2y;             ///< 2nd gimbal angle (radians)
            double mGim3x;             ///< 3rd gimbal angle
            const MountVt& mMount;     ///< mount virtual telescope
            double mTai;               ///< TAI (MJD) of obervation
            double mRa;                ///< ICRF right ascension of observation 
                                       //   (radians)
            double mDec;               ///< ICRF declination of observation 
                                       //   (radians)
            double mWavel;             ///< wavelength (microns)
            double mRoll;              ///< roll demand at Tai (radians)
            double mPitch;             ///< pitch demand at Tai (radians)
            double mCasspa;            ///< cass equivalent rotator angle 
                                       //   (radians)
            double mXr;                ///< pointing origin X coordinate (mm)
            double mYr;                ///< pointing origin Y coordinate (mm)
            double mFl;                ///< focal length (mm)
            double mTemp;              ///< temperature (deg K)
            double mPress;             ///< pressure (mbar)
            double mHumid;             ///< relative Humidity
            double mTlr;               ///< tropospheric lapse rate
            double mRcorr;             ///< correction to rotator angle (radians)
            double mAux[3];            ///< auxiliary readings
            bool mMarked;              ///< data available flag
        private:
        // No default constructor.
            PointingObs();
    };
}
#endif

