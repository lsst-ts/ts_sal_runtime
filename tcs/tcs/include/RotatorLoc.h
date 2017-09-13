/// \file RotatorLoc.h
/// \brief Definitions of the rotator location classes.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkROTATORLOC_H
#define tpkROTATORLOC_H

#include "TcsLib.h"

namespace tpk {
    class MountVt;

/// Virtual base class for rotator locations
/**
    The RotatorLoc class is a virtual base class for the specific
    rotator location classes. It stores the rotator location code.
*/
    class RotatorLoc {
        public:

    /// Assignment to TcsLib::rotloc.
            operator TcsLib::rotloc() const {
                return RotLoc;
            }
        protected:

    /// Constructor
            RotatorLoc(
                TcsLib::rotloc rotl        ///< rotator location code
            ) : RotLoc(rotl) {}
            const TcsLib::rotloc RotLoc;  ///< rotator location code
    };

/// Generic Optical Telescope Assembly rotator location
    class OTA : public RotatorLoc {
        public:
            OTA() : RotatorLoc(tcspk::OTA) {}
    };

/// Prime focus rotator location
    class Prime : public RotatorLoc {
        public:
            Prime() : RotatorLoc(tcspk::OTA) {}
    };

/// Cassegrain focus rotator location
    class Cassegrain : public RotatorLoc {
        public:
            Cassegrain() : RotatorLoc(tcspk::OTA) {}
    };

/// Gregorian focus rotator location
    class Gregorian : public RotatorLoc {
        public:
            Gregorian() : RotatorLoc(tcspk::OTA) {}
    };

/// Left Nasmyth rotator location
    class NasmythLeft : public RotatorLoc {
        public:
            NasmythLeft() : RotatorLoc(tcspk::NASMYTH_L) {}
    };

/// Right Nasmyth rotator location
    class NasmythRight : public RotatorLoc {
        public:
            NasmythRight() : RotatorLoc(tcspk::NASMYTH_R) {}
    };

/// left coude rotator location
    class CoudeLeft : public RotatorLoc {
        public:
            CoudeLeft() : RotatorLoc(tcspk::COUDE_L) {}
    };

/// Right coude rotator location
    class CoudeRight : public RotatorLoc {
        public:
            CoudeRight() : RotatorLoc(tcspk::COUDE_R) {}
    };
}
#endif

