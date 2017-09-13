/// \file AvgFilter2D.h
/// \brief Definition of the AvgFilter2D class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkAVGFILTER2D_H
#define tpkAVGFILTER2D_H

#include "AvgFilter.h"
#include "Filter2D.h"

#include "Coordinates.h"

namespace tpk {

/// 2D averaging filter
/**
    The output of an AvgFilter2D is a running average of the input values.
*/
    class AvgFilter2D : public Filter2D {
        public:
            AvgFilter2D(
                const unsigned int nsamplemax
            ) : mFilter1(nsamplemax),
                mFilter2(nsamplemax) {}
            AvgFilter2D(
                const AvgFilter2D& src
            ) : Filter2D(src),
                mFilter1(src.mFilter1),
                mFilter2(src.mFilter2) {}

        /// Clone object
            virtual AvgFilter2D* clone() const {
                return new AvgFilter2D(*this);
            }

        /// << operator
        /**
            Inserts a new value into the filter.

            \returns output value
        */
            virtual xycoord operator<<(
                xycoord input               ///< input value
            ) {
                mFilter1 << input.x;
                mFilter2 << input.y;
                xycoord output(mFilter1.value(), mFilter2.value());
                mMutex.lock();
                mValue = output;
                mMutex.unlock();
                return output;
            }

        /// Reset to initial state.
            virtual void reset(
                xycoord xy = xycoord(0.0, 0.0)   ///< initial value
            ) {
                mFilter1.reset(xy.x);
                mFilter2.reset(xy.y);
                mMutex.lock();
                mValue = xy;
                mMutex.unlock();
            }

        /// Tune filter.
            virtual void tune(
                unsigned int nsamplemax   ///< maximum number of samples
            ) {
                mFilter1.tune(nsamplemax);
                mFilter2.tune(nsamplemax);
            }

        protected:
            AvgFilter mFilter1;      ///< filter for first axis
            AvgFilter mFilter2;      ///< filter for second axis

        private:
    // There is no default constructor or assignment operator.
            AvgFilter2D();
            AvgFilter2D& operator=(const AvgFilter2D& rhs);
    };
}
#endif

