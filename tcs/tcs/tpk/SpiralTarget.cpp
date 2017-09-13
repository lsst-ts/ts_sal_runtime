/// \file SpiralTarget.cpp
/// \brief Implementation of the spiral target class.

#include "SpiralTarget.h"

#include <cmath>
#include "slalib.h"

#include "Site.h"
#include "TcsLib.h"
#include "RefSys.h"

namespace tpk {
    SpiralTarget::SpiralTarget(
        Target& target,         ///< centre position
        double pitch,           ///< pitch of spiral (arcsec)
        double speed,           ///< velocity of spiral (arcsec/sec)
        double t0               ///< start time
    ) : Target(target.site()),
            mCentre(target.clone()),
            mPitch(pitch*TcsLib::as2r),
            mSpeed(speed*TcsLib::as2r*86400.0),
            mT0(t0) { }

    void SpiralTarget::update(
        const double& t
    ) {

    // Update centre target
        mCentre->update( t );
    }

    vector SpiralTarget::position(
        const double& t
    ) const {
        return mCentre->position(t) + xyposition(t);
    }

    vector SpiralTarget::position(
        const double& t,
        const RefSys& frame
    ) const {

    // Position in tracking frame.
        vector pos = position(t);

    // Create a temporary tracking frame target in the hope that this sort
    // of target supports conversion to the requested frame.
        Target* target = mTrackFrame->target( mSite, pos);

    // Return the position in the requested frame.
        return target->position(t, frame);
    }

    void SpiralTarget::adjust(
        const double& t,
        const vector& tar
    ) {

    // Adjust centre position so that the current position matches the
    // requested one.
        mCentre->adjust(t, tar - xyposition(t));
    }

    void SpiralTarget::trackframe(
        const RefSys& frame
    ) {

    // Store new frame.
        mTrackFrame.reset(frame.clone());

    // Set tracking frame of centre target.
        mCentre->trackframe( frame );
    }

/// Copy constructor
    SpiralTarget::SpiralTarget(
        const SpiralTarget& src    ///< source target
    ) : Target(src),
            mCentre(src.mCentre->clone()),
            mPitch(src.mPitch),
            mSpeed(src.mSpeed),
            mT0(src.mT0) {}

/// Position in tangent plane at time t.
/**
    \returns position in tangent plane
*/
    focalplane SpiralTarget::xyposition(
        double t                   ///< TAI (MJD)
    ) const {
/*
    The spiral pattern looks like this:

                                        6  7  8  9
                                        5  0  1 10
                                        4  3  2 11
                                    16 15 14 13 12

    with each square separated by Pitch in arcsec or Pitch/Speed in time.
    To find the x,y position at time t we find the x,y of the squares that
    we are currently moving between and interpolate.
*/
    // Split the distance we can move in t - t0 into integer and fractional
    // parts.
        double cr;
        double f = modf(( t - mT0 ) / ( mPitch / mSpeed ), &cr);
        int c = int(cr);

    // x & y are the coordinates of the square we have currently got to.
    // Square zero is at x = 0, y = 0;
        int x = 0, y = 0;

    // xp & yp are the coordinates of the previous square.
        int xp = 0, yp = 0;

    // traverse is the number of steps to make in the current direction.
        int traverse = 1;

    // nleft is the number of steps left to make in the current direction.
        int nleft = 1;

    // cx and cy is the current step; it is always 1,0 0,1 -1,0 or 0,-1.
        int cx = 1, cy = 0;

    // Trace out the path.
        for ( int i = 0; i <= c; i++ ) {

        // Save current coordinates.
            xp = x;
            yp = y;

        // Advance to the next square.
            x += cx;
            y += cy;

        // If we are are the end of a traverse...
            if ( --nleft == 0 ) {

            // If the last move was in the Y direction, increase the length
            // of the traverse by one.
                if ( cy ) {
                    traverse++;
                }

            // Reset the number of steps left in the current traverse.
                nleft = traverse;

            // Change the direction we are moving in.
                if ( cx ) {
                    cy = -cx;
                    cx = 0;
                } else {
                    cx = cy;
                    cy = 0;
                }
            }
        }

    // Convert the integer coordinates to real focal plane coordinates and
    // extrapolate between the current and previous square centres.
        double xr = ( double(xp) + double( x - xp ) * f ) *mPitch;
        double yr = ( double(yp) + double( y - yp ) * f ) *mPitch;
        return focalplane(xr, yr);
    }
}

