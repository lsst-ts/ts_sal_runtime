/// \file SolSysTargets.h
/// \brief Definitions of the solar system target classes.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkSOLSYSTARGETS_H
#define tpkSOLSYSTARGETS_H

#include "TopoApptTarget.h"
#include "Target.h"

namespace tpk {
    class Site;

/// Solar System Target
/**
    A solar system target is a target with its position described by a set
    of osculating elements.

    SolarSystemTarget objects are not created directly but are created
    through classes for each of the common sets of elements.

    All the methods of this class are thread safe.
*/
    class SolarSystemTarget : public Target {
        protected:
            SolarSystemTarget(
                const Site& site
            ) : Target(site),
                    mPosition(0),
                    mOffset(0.0, 0.0, 0.0) {};
            ~SolarSystemTarget() {
                delete mPosition;
            }
            SolarSystemTarget* clone() const {
                return new SolarSystemTarget(*this);
            }
            SolarSystemTarget(
                const SolarSystemTarget& src
            ) : Target(src.mSite) {
                mPosition = src.mPosition->clone();
                mForm = src.mForm;
                mEpochOfEl = src.mEpochOfEl;
                mOrbInc = src.mOrbInc;
                mANode = src.mANode;
                mPerih = src.mPerih;
                mAorQ = src.mAorQ;
                mE = src.mE;
                mAorL = src.mAorL;
                mDailyMot = src.mDailyMot;
                mOffset = src.mOffset;
            }
            vector position(
                const double& t,
                const RefSys& frame
            ) const {
                return mPosition->position(t, frame);
            }
            vector position(
                const double& t
            ) const {
                return mPosition->position(t);
            }
            void update( const double& t );
            virtual void adjust(
                const double& t,
                const vector& tar
            );
            TopoApptTarget* mPosition;  ///< position in topocentric apparent
            int mForm;                  ///< element set (see slaPlante)
            double mEpochOfEl;          ///< epoch of elements (TT, MJD)
            double mOrbInc;             ///< orbital inclination (radians)
            double mANode;              ///< longitude of ascending node 
                                       //   (radians)
            double mPerih;              ///< longitude or argument of perihelion
                                       //    (radians)
            double mAorQ;               ///< mean or perihelion distance (AU)
            double mE;                  ///< eccentricity
            double mAorL;               ///< mean anomoly or longitude (radians)
            double mDailyMot;           ///< daily motion
            deltav mOffset;
    };

/// Major Planet (Astronomical Almanac format)
/**
    A target whose position is defined by a set of osculating orbital elements
    as tabulated in the Astronomical Almanac for the major planets.
*/
    class AsAmajorPlanet : public SolarSystemTarget {
        public:

    /// Constructor
            AsAmajorPlanet(
                const Site& site,    ///< observing site
                double epochofel,    ///< epoch of elements (TT, MJD)
                double orbinc,       ///< orbital inclination (degrees)
                double longascnode,  ///< longitude of ascending node (degrees)
                double longofperih,  ///< longitude of perihelion (degrees)
                double meandist,     ///< mean distance (AU)
                double eccentricity, ///< eccentricity
                double meanlong,     ///< mean longitude (degrees)
                double dailymot      ///< daily motion (degrees)
            );
            virtual AsAmajorPlanet* clone() const {
                return new AsAmajorPlanet(*this);
            };
    };

/// Major Planet (JPL Horizons format)
/**
    A target whose position is defined by a set of osculating orbital elements
    as supplied by the JPL Horizons system for the major planets.
*/
    class JPLmajorPlanet : public AsAmajorPlanet {
        public:
            JPLmajorPlanet(
                const Site& site,
                double epochofel,
                double orbinc,
                double longascnode,
                double argofperih,
                double meandist,
                double eccentricity,
                double meananom,
                double dailymot
            );
            virtual JPLmajorPlanet* clone() const {
                return new JPLmajorPlanet(*this);
            };
    };

/// Minor planet
/**
    A target whose position is defined by a set of osculating orbital elements
    as tabulated in the Astronomical Almanac and supplied by the Minor Planets
    Center for minor planets.
*/
    class MinorPlanet : public SolarSystemTarget {
        public:
            MinorPlanet(
                const Site& site,
                double epochofel,
                double orbinc,
                double longascnode,
                double argofperih,
                double meandist,
                double eccentricity,
                double meananom
            );
            virtual MinorPlanet* clone() const {
                return new MinorPlanet(*this);
            };
    };

/// Minor solar system body
/**
    A target whose position is defined by a set of osculating orbital elements
    as tabulated in the Astronomical Almanac and supplied by the Minor Planets
    Center for comets and the JPL Horizons system for both minor planets and
    comets.
*/
    class MinorSolarSystemBody : public SolarSystemTarget {
        public:
            MinorSolarSystemBody(
                const Site& site,
                double epochofel,
                double orbinc,
                double longascnode,
                double argofperih,
                double perihdist,
                double eccentricity,
                double epochofperih
            );
            virtual MinorSolarSystemBody* clone() const {
                return new MinorSolarSystemBody(*this);
            };
    };
}
#endif

