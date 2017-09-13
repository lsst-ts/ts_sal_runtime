/// \file KalmanFilter.h
/// \brief Definition of the Kalman filter class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkKALMANFILTER_H
#define tpkKALMANFILTER_H

#include "Filter.h"

namespace tpk {

/// 1D Kalman filter
    class KalmanFilter : public Filter {
        public:

    /// Constructor.
            KalmanFilter(
                double sigmaXp,
                double sigmaXv,
                double sigmaNoise
            );

    /// Clone object
            virtual KalmanFilter* clone() const {
                return new KalmanFilter(*this);
            }

            virtual double operator<<(
                double input
            );

    /// Reset to initial state.
            virtual void reset( double value = 0.0 );
            
        protected:
            const double mSigmaXpInit;
            const double mSigmaXvInit;
            const double mSigmaXp;
            const double mSigmaXv;
            const double mQpp;
            const double mQvv;
            const double mPee;
            double mXpNew;
            double mXvNew;
            double mXpErr;
            double mPppNew;
            double mPpvNew;
            double mPvpNew;
            double mPvvNew;

        private:
    // No default constructor.
            KalmanFilter();
    };
}
#endif

