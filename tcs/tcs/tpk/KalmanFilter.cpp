/// \file KalmanFilter.cpp
/// \brief Implementation of the Kalman filter class.

// Copyright CCLRC. All rights reserved.

#include "KalmanFilter.h"

namespace tpk {
    KalmanFilter::KalmanFilter(
        double sigmaXp,
        double sigmaXv,
        double sigmaNoise
    ) : mSigmaXpInit(sigmaXp),
        mSigmaXvInit(sigmaXv),
        mSigmaXp(sigmaXp),
        mSigmaXv(sigmaXv),
        mQpp(sigmaXp * sigmaXp),
        mQvv(sigmaXv * sigmaXv),
        mPee(sigmaNoise * sigmaNoise) {
        reset();
    };

/// Insert value into filter
/**
    \returns New filter value
*/
    double KalmanFilter::operator<<(
        double input               ///< input value
    ) {

    // Save old filter state
        double xpOld = mXpNew;
        double xvOld = mXvNew;
        double pppOld = mPppNew;
        double ppvOld = mPpvNew;
        double pvvOld = mPvvNew;
        double pvpOld = mPvpNew;

    // Extrapolate covariance matrix
        double ppp = pppOld +  ppvOld + pvpOld  + pvvOld + mQpp;
        double ppv = ppvOld + pvvOld;
        double pvp = pvpOld + pvvOld;
        double pvv = pvvOld + mQvv;

    // Extrapolate position and velocity
        double xp = xpOld + xvOld;
        double xv = xvOld;

    // Calculate new position and velocity gains
        double gainXp = ppp / (ppp + mPee);
        double gainXv = pvp / (ppp + mPee);

    // Calculate new position and velocity from measurement using gains
        mXpErr = input - xp;
        mXpNew = xp  + gainXp * mXpErr;
        mXvNew = xv  + gainXv * mXpErr;

    // Calculate new covarience matrix
        mPppNew = (1.0 - gainXp) * ppp;
        mPpvNew = (1.0 - gainXp) * ppv;
        mPvpNew = - gainXv * ppp + pvp;
        mPvvNew = - gainXv * ppv + pvv;

    // Store and return new value
        mValue = mXpNew;
        return mValue;
    }

/// Reset to initial state
    void KalmanFilter::reset(
        double value               ///< Initial filter value
    ) {
        mXpNew = value;
        mXvNew = 0.0;
        mPppNew = mSigmaXpInit * mSigmaXpInit;
        mPvvNew = mSigmaXvInit * mSigmaXvInit;
        mPpvNew = 0.0;
        mPvpNew = 0.0;
        mXpErr = 0.0;
    }
}

