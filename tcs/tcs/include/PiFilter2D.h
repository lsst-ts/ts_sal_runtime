/// \file PiFilter2D.h
/// \brief Definition of the PiFilter class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkPIFILTER2D_H
#define tpkPIFILTER2D_H

#include "Coordinates.h"
#include "Filter2D.h"

namespace tpk {

/// 2D proportional/integrator filter
/**
    A 2D "proportional integrator" filter.

    Setting any of the integrator gain, window or saturation to zero
    disables the integrator.
*/
    class PiFilter2D : public Filter2D {
        protected:
            double mPgain;
            double mIgain;
            double mWindow2;
            double mSaturate;
            xycoord mIntegrator;
        public:
            PiFilter2D(
                const double pgain,     ///< proportional gain
                const double igain,     ///< integrator gain
                const double window,    ///< integrator window
                const double saturate   ///< integrator saturation value
            ) : mPgain(pgain),
                mIgain(igain),
                mWindow2(window * window),
                mSaturate(saturate),
                mIntegrator(0.0, 0.0) {};
            PiFilter2D(
                const PiFilter2D& src
            ) : Filter2D(src) {
                src.mMutex.lock();
                mPgain = src.mPgain;
                mIgain = src.mIgain;
                mWindow2 = src.mWindow2;
                mSaturate = src.mSaturate;
                mIntegrator = src.mIntegrator;
                src.mMutex.unlock();
            }

    /// Constructor for proportional only filter.
            PiFilter2D(
                const double pgain      ///< proportional gain
            ) : mPgain(pgain),
                mIgain(0.0),
                mWindow2(0.0),
                mSaturate(0.0),
                mIntegrator(0.0, 0.0) {};

    /// Clone object
            virtual PiFilter2D* clone() const {
                return new PiFilter2D(*this);
            }

    /// << operator
            virtual xycoord operator<<(
                const xycoord& input
            );

    /// Reset to initial state.
            virtual void reset(
                const xycoord& xy     ///< filter value
            ) {
                mMutex.lock();
                mValue = xy;
                mIntegrator = xycoord(0.0, 0.0);
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
    // There is no default constructor.
            PiFilter2D();
    };
}
#endif

