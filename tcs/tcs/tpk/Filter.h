/// \file Filter.h
/// \brief Definition of the Filter class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef FILTER_H
#define FILTER_H

#include "TcsMutex.h"

namespace tpk {

/// Null 1D filter
/**
    A filter filters a stream input values in some fashion to generate an
    output value. The base filter class does no filtering and always returns
    the last value input.

    It can be used as the base class of real filters and can be used where
    a filter is required but no actual filtering is desired.

    All classes derived from Filter must implement the clone method so that
    copies of filters can be made without knowing their type.

    All the methods of this class are thread safe.
*/
    class Filter {
        public:
            Filter(
                double value = 0.0         ///< initial value
            ) : mValue(value) {}
            Filter(
                const Filter& src
            ) {
                src.mMutex.lock();
                mValue = src.mValue;
                src.mMutex.unlock();
            }

        /// Clone object
            virtual Filter* clone() const {
                return new Filter(*this);
            }
            virtual ~Filter() {}

        /// << operator
        /**
            Inserts a new value into the filter.

            \returns  current value
        */
            virtual double operator<<(
                double input               ///< input value
            ) {
                mMutex.lock();
                mValue = input;
                mMutex.unlock();
                return input;
            }

        /// value
        /**
            Returns the current output of the filter.

            \returns current value
        */
            virtual double value() const {
                mMutex.lock();
                double v = mValue;
                mMutex.unlock();
                return v;
            }

        /// Reset to initial state.
            virtual void reset(
                double value = 0.0   ///< initial value
            ) {
                mMutex.lock();
                mValue = value;
                mMutex.unlock();
            }

        protected:
            double mValue;              ///< current value
            mutable TcsMutex mMutex;    ///< mutex
    };
}
#endif

