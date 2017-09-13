/// \file Planet.h
/// \brief Definition of the Planet class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkPLANET_H
#define tpkPLANET_H

#include <string.h>

#include "SolSysTargets.h"

namespace tpk {
        class Site;

/// Major Planet (Chapront & Francou ephemeris)
/**
    A Planet object is a SolSysTarget with orbital elements created from the
    planetary ephemerides of Chapront & Francou (Bureau des Longitudes, Paris).
    The coefficients from which the ephemerides are computed come from a file,
    one per planet, supplied by Chapront & Francou.

    The location of the ephemeris files must by set by calling the static method
    ephemPath before any Planet objects are created.

    All the methods of this class are thread safe.
*/
    class Planet : public SolarSystemTarget {
        public:
        /// Solar system objects supported by this class.
            typedef enum {
                Mercury, Venus, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto
            } names;
            Planet(
                const Site& site,
                const names& planet
            );
            static void ephemPath(
                const std::string& path
            );
        protected:
            static std::string mEphemPath;    ///< file path for ephemeris files
    };
}
#endif

