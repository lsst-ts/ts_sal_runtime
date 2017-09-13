/// \file Filter2D.h
/// \brief Definition of the Filter2D class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkFILTER2D_H
#define tpkFILTER2D_H

#include "Coordinates.h"
#include "TcsMutex.h"

namespace tpk {

/// Null 2D filter
/**
    A 2D filter filters a stream of pairs of input values in some fashion
    to generate a pair of output value. The base filter class does no
    filtering and always returns the last values input.

    It can be used as the base class of real filters and can be used where
    a filter is required but no actual filtering is desired.

    All classes derived from Filter must implement the clone method so that
    copies of filters can be made without knowing their type.

    All methods of this class are thread safe.
*/
    class Filter2D {
        public:
            Filter2D(
                xycoord xy = xycoord(0.0, 0.0)   ///< initial value
            ) : mValue(xy) {};
            Filter2D(
                const Filter2D& src
            ) {
                src.mMutex.lock();
                mValue = src.mValue;
                src.mMutex.unlock();
            }

        /// Clone object
            virtual Filter2D* clone() const {
                return new Filter2D(*this);
            }
            virtual ~Filter2D() {}

        /// << operator
        /**
            Inserts a new value into the filter.

            \returns output value
        */
            virtual xycoord operator<<(
                xycoord input               ///< input value
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
            virtual xycoord value() const {
                mMutex.lock();
                xycoord v = mValue;
                mMutex.unlock();
                return v;
            }

        /// Reset to initial state.
            virtual void reset(
                xycoord xy = xycoord(0.0,0.0)    ///< initial value
            ) {
                mMutex.lock();
                mValue = xy;
                mMutex.unlock();
            }

        protected:
            xycoord mValue;             ///< current value
            mutable TcsMutex mMutex;    ///< mutex
    };
}
#endif

