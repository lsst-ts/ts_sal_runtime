/// \file AvgFilter.h
/// \brief Definition of the AvgFilter class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkAVGFILTER_H
#define tpkAVGFILTER_H

#include "Filter.h"

namespace tpk {

/// 1D averaging filter
/**
    The output of an AvgFilter is a running average of the input values.

    If the number of samples is set to zero the output is always equal to
    the initial value.

    All methods of this class are thread safe.
*/
    class AvgFilter : public Filter {
        protected:
            unsigned int mNsampleMax;
            unsigned int mNsample;
            double* mBuffer;
            unsigned int mNext;
        public:
            AvgFilter(
                const unsigned int nsamplemax
            );
            AvgFilter(const AvgFilter& src);
            ~AvgFilter();

    /// Clone object
            virtual AvgFilter* clone() const {
                return new AvgFilter(*this);
            }

            virtual double operator<<(
                double input
            );

    /// Reset to initial state.
            virtual void reset( double value = 0.0 ) {
                mMutex.lock();
                mValue = value;
                mNsample = 0;
                mNext = 0;
                mMutex.unlock();
            }
            virtual void tune(
                unsigned int nsamplemax
            );

        private:
    // There is no default constructor or assignment operator.
            AvgFilter();
            AvgFilter& operator=(const AvgFilter& rhs);
    };
}
#endif

