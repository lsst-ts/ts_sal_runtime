/// \file PiFilter.h
/// \brief Definition of the PiFilter class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkPIFILTER_H
#define tpkPIFILTER_H

#include "Filter.h"

namespace tpk {

/// 1D proportional/integrator filter
/**
    A "proportional integrator" filter.

    Setting any of the integrator gain, window or saturation to zero
    disables the integrator.
*/
    class PiFilter : public Filter {
        protected:
            double mPgain;
            double mIgain;
            double mWindow2;
            double mSaturate;
            double mIntegrator;
        public:
            PiFilter(
                const double pgain,     ///< proportional gain
                const double igain,     ///< integrator gain
                const double window,    ///< integrator window
                const double saturate   ///< integrator saturation value
            ) : mPgain(pgain),
                mIgain(igain),
                mWindow2(window * window),
                mSaturate(saturate),
                mIntegrator(0.0) {}
            PiFilter(
                const PiFilter& src
            ) : Filter(src) {
                src.mMutex.lock();
                mPgain = src.mPgain;
                mIgain = src.mIgain;
                mWindow2 = src.mWindow2;
                mSaturate = src.mSaturate;
                mIntegrator = src.mIntegrator;
                src.mMutex.unlock();
            }

    /// Constructor for proportional only filter.
            PiFilter(
                const double pgain      ///< proportional gain
            ) : mPgain(pgain),
                mIgain(0.0),
                mWindow2(0.0),
                mSaturate(0.0),
                mIntegrator(0.0) {}

    /// Clone object
            virtual PiFilter* clone() const {
                return new PiFilter(*this);
            }

    /// << operator
            virtual double operator<<(
                double input
            );

    /// Reset to initial state.
            virtual void reset(
                double value = 0.0   ///< filter value
            ) {
                mMutex.lock();
                mValue = value;
                mIntegrator = 0.0;
                mMutex.unlock();
            }

    /// Tune filter
            virtual void tune(
                const double pgain,     ///< proportional gain
                const double igain,     ///< integrator gain
                const double window,    ///< integrator window
                const double saturate   ///< integrator saturation value
            ) {
                mMutex.lock();
                mPgain = pgain;
                mIgain = igain;
                mWindow2 = window * window;
                mSaturate = saturate;
                mMutex.unlock();
            }

            private:
    /// There is no default constructor.
            PiFilter();
    };
}
#endif

