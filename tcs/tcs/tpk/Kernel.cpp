/// \file Kernel.cpp
/// \brief Pointing kernel constants

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "RefSys.h"
#include "ICRefSys.h"
#include "TcsLib.h"

namespace tpk {

/// Kernel constants
/**
    Public constants that may need to be tailored for different kernel
    implementatons.
*/

/// Zenith "no-go" limit (radians).
    double rnogo = 0.25 * TcsLib::d2r;

/// Interval between the trajectory samples (days).
    double sampleint = 1.0 / 86400.0;

/// Canonical tropospheric lapse rate
    double tlr = 0.0065;

/// Reference wavelength for refraction calculations (microns).
/**
    Set to 1e6 to disable the standard optics/IR refraction calculations.
*/
    double wavelr = 0.5;

/// The default tracking frame
    const RefSys* defaultFrame = new ICRefSys();

/// The estimated delay in getting demands to the mechanism controllers (days).
/**
    The time stamps of all demands will be at least this amount in the
    future.
*/
    double transdelay = 0.0 / 86400.0;

// Address of custom refraction routine.
/**
    Use NULL to just use the standard optical/IR refraction model.
*/
    tcspk::PRF refsub = 0;
}

