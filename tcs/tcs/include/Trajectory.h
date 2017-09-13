/// \file Trajectory.h
/// \brief Definition of the Trajectory class

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkTRAJECTORY_H
#define tpkTRAJECTORY_H

#include <stdexcept>

namespace tpk {

/// Position as a function of time
/**
    The position is defined by a reference time and number of polynomial
    coefficients. Polynomials of order up to 2 (i.e. position, velocity
    and acceleration) are supported such that:

        p(t) = p0 + p1 * (t - t0) + p2 * (t - t0)^2

    When creating a trajectory from a set of position samples the time
    interval must not be zero.
*/
    class Trajectory {
        public:
            Trajectory() :
                mTs(0.0),
                mT0(0.0),
                mOrder(0) {
                mCoeffs[0] = 0.0;
            };

    /// Constructor with explicit polynomial coefficients.
            Trajectory(
                double t,               ///< TAI time stamp (MJD)
                double t0,              ///< reference time for polynomial (MJD)
                const double* coeffs,   ///< polynomial coefficients
                unsigned int order      ///< polynomial order
            ) : mTs(t),
                mT0(t0),
                mOrder(order) {
                if ( mOrder > maxorder ) {
                    throw std::out_of_range( "Polynomial order to large" );
                }
                for (unsigned int i = 0; i <= mOrder; i++ ) {
                    mCoeffs[i] = coeffs[i];
                };
            }

    /// Constructor from just a position
            Trajectory (
                double p                   ///< position sample
            ) : mTs(0.0),
                mT0(0.0),
                mOrder(0) {
                mCoeffs[0] = p;
            }

    /// Constructor from one position sample.
            Trajectory (
                double t,                  ///< timestamp (MJD)
                double p                   ///< position sample
            ) : mTs(t),
                mT0(t),
                mOrder(0) {
                mCoeffs[0] = p;
            }

    /// Constructor from two position samples.
    /**
        The timestamp is the first of the two samples.
    */
            Trajectory (
                double t,                  ///< timestamp (MJD)
                double dt,                 ///< interval between samples
                double p1,                 ///< position sample 1
                double p2                  ///< position sample 2
            ) : mTs(t),
                mT0(t),
                mOrder(1) {
                mCoeffs[0] = p1;
                mCoeffs[1] = (p2 - p1) / dt;
            }

    /// Constructor from a list of equally spaced position samples.
            Trajectory (
                double t,                  ///< timestamp (MJD)
                double t0,                 ///< time of first sample (MJD)
                double dt,                 ///< interval between samples
                unsigned int n,            ///< number of samples
                double* p                  ///< position samples
            ) : mTs(t),
                mT0(t0),
                mOrder(n - 1) {
                if ( n == 1 ) {
                    mCoeffs[2] = 0.0;
                    mCoeffs[1] = 0.0;
                    mCoeffs[0] = p[0];
                } else if ( n == 2 ) {
                    mCoeffs[2] = 0.0;
                    mCoeffs[1] = (p[1] - p[0]) / dt;
                    mCoeffs[0] = p[0];
                } else if ( n == 3 ) {
                    mCoeffs[2]  = (p[2] - 2.0 * p[1] + p[0]) / (dt * dt) / 2.0;
                    mCoeffs[1] = (4.0 * p[1] - p[2] - 3.0 * p[0]) / dt / 2.0;
                    mCoeffs[0] = p[0];
                } else {
                    mCoeffs[2] = 0.0;
                    mCoeffs[1] = 0.0;
                    mCoeffs[0] = 0.0;
                }
            }

    /// Constructor from a Trajectory, a zero point and a scale factor
    /**
        This constructor enables a trajectory to be mapped from one coordinate
        system to another.

        The zero point is the value in the new coordinate system of the point
        0.0 in the source coordinate system.
    */
        Trajectory(
            const Trajectory& src,        ///< Source trajectory
            double zeropoint,             ///< zero point
            double scale                  ///< scale factor
        ) : mTs(src.mTs),
            mT0(src.mT0),
            mOrder(src.mOrder) {
            mCoeffs[0] = ( src.mCoeffs[0] - zeropoint ) * scale;
            for ( unsigned int i = 1; i < mOrder + 1; i++ ) {
                mCoeffs[i] = src.mCoeffs[i] * scale;
            }
        }

    /// Value of coefficent at time t.
    /**
        \returns coefficient value
    */
            double sample(
                double t,            ///< TAI (MJD)
                unsigned int n = 0   ///< order of coefficient
            ) const {
                double d = 0.0;
                for ( unsigned int i = mOrder + 1; i > n; i-- ) {
                    d = d * (t - mT0) + mCoeffs[i - 1];
                }
                return d;
            }

    /// Assignment to double.
    /**
        \returns the position at the timestamp.
    */
            operator double() const {
                return sample(mTs,0);
            }

    /// Timestamp.
    /**
        \returns timestamp (TAI, MJD)
    */
            double timestamp() const {
                return mTs;
            }

        protected:
            static const unsigned int maxorder = 2; ///< maximum order
            double mTs;                             ///< timestamp
            double mT0;                             ///< reference time
            unsigned int mOrder;                    ///< polynomial order
            double mCoeffs[maxorder+1];             ///< polynomial coefficients
    };
}
#endif

