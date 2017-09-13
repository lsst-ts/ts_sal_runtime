/// \file AvgFilter.cpp
/// \brief Implementation of the AvgFilter class.

// Copyright CCLRC. All rights reserved.

#include "AvgFilter.h"

namespace tpk {
    AvgFilter::AvgFilter(
        const unsigned int nsamplemax  ///< maximum number of samples to average
        ) : Filter(),
                mNsampleMax(nsamplemax),
                mNsample(0),
                mNext(0) {
        if ( mNsampleMax > 0 ) {
            mBuffer = new double[mNsampleMax];
        } else {
            mBuffer = 0;
        }
    }
    AvgFilter::AvgFilter(
        const AvgFilter& src
    ) : Filter(src)
    {

        src.mMutex.lock();
        mNsampleMax= src.mNsampleMax;
        mNsample = src.mNsample;
        mNext = src.mNext;
        for (unsigned int i = 0; i < mNsample; i++) {
            mBuffer[i] = src.mBuffer[i];
        }
        mValue = src.mValue;
        src.mMutex.unlock();
        if ( mNsampleMax > 0 ) {
            mBuffer = new double[mNsampleMax];
        } else {
            mBuffer = 0;
        }
    }

/// Destructor
    AvgFilter::~AvgFilter() {
        delete[] mBuffer;
    }

/// Insert value into filter
/**
    \returns New filter value
*/
    double AvgFilter::operator<<(
        double input               ///< input value
    ) {
        mMutex.lock();
        if ( mNsampleMax > 0 ) {
            if ( mNsample == mNsampleMax ) {

            // Buffer is full so subtract an n'th of the value about to be
            // replaced add an n'th of the input value.
                mValue = mValue - mBuffer[mNext] / double(mNsampleMax) +
                        input / double(mNsampleMax);

            // Replace the value in the buffer.
                mBuffer[mNext++] = input;
            } else {

            // Buffer is not full yet. Add input to average.
                mNsample++;
                mValue = mValue * double(mNsample - 1) / double(mNsample) +
                        input / double(mNsample);

            // Store new input in buffer
                mBuffer[mNext++] = input;
            }

        // Wrap pointer if necessary
            mNext = (mNext == mNsampleMax) ? 0 : mNext;
        }
        double v = mValue;
        mMutex.unlock();
        return v;
    }

/// Tune filter
/**
    Change the number of samples to be averaged by resizing the filter buffer.

    If the size of the buffer is decreased the oldest samples are discarded
    and the filter value recalculated.
*/
    void AvgFilter::tune(
        unsigned int nsamplemax   ///< maximum number of samples
    ) {
        mMutex.lock();
        if ( nsamplemax != mNsampleMax) {

        // Create the new buffer
            double* newbuf;
            if ( nsamplemax > 0 ) {
                newbuf = new double[nsamplemax];

            // If the new buffer is bigger than the current number of
            // samples copy the old samples to the new buffer starting with the
            // oldest sample.
                if ( nsamplemax > mNsample ) {
                    unsigned int n = mNext;
                    for (unsigned int i = 0; i < mNsample; i++ ) {
                        newbuf[i] = mBuffer[n++];
                        n = (n == mNsample) ? 0 : n;
                    }
                    mNext = mNsample;
                } else {

                // Copy as many old samples as will fit and recalculate the
                // filter value.
                    mValue = 0.0;
                    unsigned int n = mNext + mNsample - nsamplemax;
                    n = n < mNsample ? n : n - mNsample;
                    for (unsigned int i = 0; i < nsamplemax; i++ ) {
                        newbuf[i] = mBuffer[n++];
                        mValue += newbuf[i];
                        n = (n == mNsampleMax) ? 0 : n;
                    }
                    mValue = mValue / nsamplemax;
                    mNsample = nsamplemax;
                    mNext = 0;
                }
            } else {
                newbuf = 0;
                mNsample = 0;
            }

        // Replace the old buffer with the new.
            delete[] mBuffer;
            mBuffer = newbuf;
            mNsampleMax = nsamplemax;
        }
        mMutex.unlock();
    }
}

