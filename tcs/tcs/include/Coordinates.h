/// \file Coordinates.h
/// \brief Definitions of coordinate classes.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkCOORDINATES_H
#define tpkCOORDINATES_H

#include <cmath>

namespace tpk {
    struct vector;

/// Cartesian coordinate pair
    struct xycoord {
        union {
            double x;         ///< first coordinate
            double xi;        ///< first coordinate
            double a;         ///< first coordinate
        };
        union {
            double y;         ///< second coordinate
            double eta;       ///< second coordinate
            double b;         ///< second coordinate
        };

    /// Constructor from two values.
        xycoord(
            double xval,
            double yval
        ) : x(xval), y(yval) {}

    /// Default constructor
        xycoord() : x(0.0), y(0.0) {};

/// Difference between two points.
        xycoord operator-(
            const xycoord& op
        ) const {
            return xycoord(x - op.x, y - op.y);
        }

/// Addition.
        xycoord operator+(
            const xycoord& op
        ) const {
            return xycoord(x + op.x, y + op.y);
        }

/// Multiplication by a double.
        xycoord operator*(
            const double& op
        ) const {
            return xycoord(x * op, y * op);
        }

/// Length.
        double len() const {
            return sqrt( x * x + y * y );
        }

/// Length squared.
        double len2() const {
            return x * x + y * y;
        }
    };

/// Focal plane coordinates
/**
    focalplane objects are used to represent positions in the focal plane.
    The units are focal lengths and the origin is the centre of rotation
    of the instrument or image rotator. The coordinate system can either
    be fixed to the telescope (usually designated xi, eta) or fixed to
    the rotator (usually designated x, y).
*/
    typedef xycoord focalplane;

/// Instrument coordinates
/**
    instrcoord objects are used to represent positions on a instrument
    detector or in the coordinate system of a guider or wave-front
    sensor.
*/
    typedef xycoord instrcoord;

/// Spherical coordinate
/**
    A spherical structure stores the two components of a position in
    spherical coordinates. No operators or methods are defined but the
    constructor from a vector implements conversion from direction
    cosines to spherical coordinates.

    The vector class has a constructor from a spherical structure that
    implement conversion from spherical to direction cosines.
*/
    struct spherical {
        double a;
        double b;

    /// Constructor from a pair of coodinates.
        spherical(
            double aval,         ///< First coordinate.
            double bval          ///< Second coordinate.
        ) : a(aval), b(bval) {}

    /// Default constructor.
        spherical() : a(0.0), b(0.0) {}

        spherical( const vector& rhs);
    };

/// Vector displacement
/**
    A deltav structure represents the displacement beween two vector directions.
    it can be multiplied or divided by a double and a pair of deltav's can be
    added and subtracted.
*/
    struct deltav {
        public:
            double dx;
            double dy;
            double dz;

    /// Default constructor
        deltav() : dx(0.0), dy(0.0), dz(0.0) {}

    /// Constructor from x, y & z.
        deltav(
            const double x,
            const double y,
            const double z
        ) : dx(x), dy(y), dz(z) {}

    /// Length.
        double len() const {
            return sqrt( dx * dx + dy * dy + dz * dz );
        }

    /// Multiplication by a double.
        deltav operator*(
            const double& rhs
        ) const {
            return deltav(dx * rhs, dy * rhs, dz * rhs);
        }

    /// Division by a double.
        deltav operator/(
            const double& rhs
        ) const {
            return deltav(dx / rhs, dy / rhs, dz / rhs);
        }

    /// Addition
        deltav operator+(
            const deltav& rhs
        ) const {
            return deltav(dx + rhs.dx, dy + rhs.dy, dz + rhs.dz);
        }

    /// Subtraction
        deltav operator-(
            const deltav& rhs
        ) const {
            return deltav(dx - rhs.dx, dy - rhs.dy, dz - rhs.dz);
        }
    };

/// Direction vector
/**
    A vector stores the three direction cosines that define a direction.

    One vector can be subtracted from another to give a displacement (deltav)
    object and a displacement can be added to or subtracted from a vector.

    The construtor that takes a spherical implements the conversion from
    spherical coordinates to a vector. Note that if the spherical coordinates
    are in a left handed coordinate system (such as Az,El or HA,Dec) the
    resulting vector will also be in a left handed system.
*/
    struct vector {
        double x;
        double y;
        double z;

    /// Constructor from x, y & z.
        vector(
            const double xval,
            const double yval,
            const double zval
        );

    /// Constructor from a pair of spherical coordinates
        vector(
            const double a,
            const double b
        );

    /// Default constructor.
        vector() : x(1.0), y(0.0), z(0.0) {};

    /// Spherical to vector.
        vector( const spherical& rhs);

    /// Difference.
        deltav operator-(
            const vector& rhs
        ) const {
            return deltav(x - rhs.x, y - rhs.y, z - rhs.z);
        }

    // Displacement
        vector operator+(
            const deltav& rhs
        ) const;

    // Inverse Displacement
        vector operator-(
            const deltav& rhs
        ) const {
            return *this + (rhs * -1.0);
        }

    // Offsets in the tangent plane
        vector operator+(
            const xycoord& rhs
        ) const;

    /// Inverse offset in the tangent plane
        vector operator-(
            const xycoord& rhs
        ) const {
            return *this + (rhs * -1.0);
        }

    // Bearing of one vector relative to another
        double bearing(
            const vector& v
            ) const;
    };
}
#endif

