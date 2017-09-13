/// \file Coordinates.cpp
/// \brief Implementation of the coordinate classes.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "Coordinates.h"
#include "TcsLib.h"

#include <cmath>

namespace tpk {

/// Constructor from a vector.
/**
    The vector is converted to the equivalent in spherical coordinates.
*/
    spherical::spherical( const vector& rhs) {
        double r = sqrt( rhs.x * rhs.x + rhs.y * rhs.y );
        a = r != 0.0 ? atan2( rhs.y, rhs.x ) : 0.0;
        a = a < 0.0 ? a + TcsLib::pi2 : a;
        b = rhs.z != 0.0 ? atan2( rhs.z, r ) : 0.0;
    }

/// Constructor from a pair of spherical coordinates.
/**
    The spherical coordinates are converted to the equivalent vector.
*/
    vector::vector(
        double a,      ///< first coordinate
        double b       ///< second coordinate
    ) {
        double cosb = cos( b );
        x = cos( a ) * cosb;
        y = sin( a ) * cosb;
        z = sin( b );
    }

/// Constructor from spherical coordinates.
/**
    The spherical coordinates are converted to the equivalent vector.
*/
    vector::vector( const spherical& rhs) {
        double cosb = cos( rhs.b );
        x = cos( rhs.a ) * cosb;
        y = sin( rhs.a ) * cosb;
        z = sin( rhs.b );
    }

/// Constructor from 3 doubles.
    vector::vector(
        const double xval,
        const double yval,
        const double zval
    ) {
        double f = sqrt(xval * xval + yval * yval + zval * zval);
        x = xval/f;
        y = yval/f;
        z = zval/f;
    };

/// Addition of a displacement.
    vector vector::operator+(
        const deltav& rhs
    ) const {
        double f = 1.0 - (x * rhs.dx + y * rhs.dy + z * rhs.dz);
        vector v;
        v.x = (x + rhs.dx) * f;
        v.y = (y + rhs.dy) * f;
        v.z = (z + rhs.dz) * f;
        return v;
    }

/// Addition of a xi, eta tangent plane offset.
    vector vector::operator+(
        const xycoord& rhs
    ) const {
        double x0 = x;
        double f = sqrt( 1.0 + rhs.xi * rhs.xi + rhs.eta * rhs.eta );
        double r = sqrt( x * x + y * y);
        if ( r == 0.0 ) {
            r = 1e-20;
            x0 = r;
        }
        double x1 = (x - ( rhs.xi * y + rhs.eta * x0 * z ) / r) / f;
        double y1 = (y + ( rhs.xi * x0 - rhs.eta * y * z ) / r) / f;
        double z1 = (z + rhs.eta * r) / f;
        return vector(x1, y1, z1);
    }

/// Bearing (postion angle) of one vector relative to another.
    double vector::bearing(
        const vector& v
    ) const {
        double s = v.y * x - v.x * y;
        double c = v.z * ( x * x + y * y ) - z * ( v.x * x + v.y * y );
        return ( s != 0.0 || c != 0.0 ) ? atan2 ( s, c ) : 0.0;
    }
}

