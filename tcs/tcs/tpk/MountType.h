/// \file MountType.h
/// \brief Definition of the mount type class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkMOUNTTYPE_H
#define tpkMOUNTTYPE_H

#include "TcsLib.h"

namespace tpk {
    class MountVt;

/// Virtual base class for mount types
/**
    The MountType class is a base class for the specific mount type
    classes. It stores the TCSpk mount type code and, if necessary,
    the gimbal angles.

    \note The classes derived from MountType do not define any additional
    data or methods so it is safe to make a copy through a pointer to the
    base class. This makes a virtual constructor method unneccesary.
*/
    class MountType {
        friend class MountVt;
        friend class PointingObs;
        public:
            virtual ~MountType() {}
        protected:
            const TcsLib::mtype mMtype;       ///< mount type
            double mGim1z;                    ///< first gimbal angle
            double mGim2y;                    ///< second gimbal angle
            double mGim3x;                    ///< third gimbal angle
            MountType(
                TcsLib::mtype mtype
            ) : mMtype(mtype) {}
            MountType(
                TcsLib::mtype mtype,
                double gim1z,
                double gim2y,
                double gim3x
            ) :
                mMtype(mtype),
                mGim1z(gim1z),
                mGim2y(gim2y),
                mGim3x(gim3x)
            {}
    };

/// Alt,Az mount type
/**
    An AltAzMountType object specifies that the mount is an altitude over
    azimuth mount.
*/
    class AltAzMountType : public MountType {
        public:
            AltAzMountType() : MountType(tcspk::ALTAZ) {}
    };

/// Equatorial mount type
/**
    An EquatorialType object specifies that the mount is an equatorial mount.
*/
    class EquatorialMountType : public MountType {
        public:
            EquatorialMountType() : MountType(tcspk::EQUAT) {}
    };

/// Gimbal mount type
/**
    A GimbalMountType specifies that mount is a gimbal with the supplied
    gimbal angles.
*/
    class GimbalMountType : public MountType {
        public:
            GimbalMountType(
                double gim1z,     ///< first gimbal angle (degrees)
                double gim2y,     ///< second gimbal angle (degrees)
                double gim3x      ///< third gimbal angle (degrees)
        ) : MountType(tcspk::GIMBAL, gim1z * TcsLib::d2r, gim2y * TcsLib::d2r,
                gim3x * TcsLib::d2r) {}
    };
}
#endif

