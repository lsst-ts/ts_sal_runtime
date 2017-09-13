/// \file KernelWcs.cpp
/// \brief Implementation of the kernel world coordinate system class.

// D Terrett
// Copyright CLRC. All rights reserved.

#include "KernelWcs.h"

#include "slalib.h"

#include "Coordinates.h"
#include "BaseVt.h"
#include "MountVt.h"
#include "RefSys.h"
#include "Transform.h"

namespace tpk {

    extern double tlr;
    extern double wavelr;

/**
    The KernelWcs constructor takes a snapshot of the running system to
    construct the world coordinate transformation.
*/
    KernelWcs::KernelWcs(
        const MountVt& mount,      ///< Mount virtual telescope
        const Trajectory roll,     ///< Actual roll of mount
        const Trajectory pitch,    ///< Actual pitch of mount
        const Trajectory rma,      ///< Actual rotator mechanical angle
        const Trajectory aoa,      ///< Actual optics tip
        const Trajectory aob,      ///< Actual optics tilt
        const RefSys& refsys,      ///< World coordinate reference system
        const double& wavel,       ///< Effective wavelength
        const Transform& trans,    ///< Focal plane to instrument 
                                   //   transformation
        const xycoord& centre,     ///< Center of sample grid (inst coords)
        const double& gridsize     ///< Sample grid size (inst coords)
    ) {

    // Copy context into local variables.
        mount.mMutex.lock();
        double tai = mount.mTai;
        const vector tel = mount.mTelVec;
        const TcsLib::rotloc rotl = mount.mRotloc;
        const double ga = mount.mGa;
        const double gb = mount.mGb;
        const double ia = mount.mIa;
        const double ib = mount.mIb;
        const double np = mount.mNp;
        const double cst = mount.mCst;
        const double sst = mount.mSst;
        double ae2mt[3][3];
        TcsLib::copyMatrix(mount.mAe2mt, ae2mt);
        mount.mMutex.unlock();

    // Copy site site information from the Site object.
        mount.mSite.mMutex.lock();
        const double lat = mount.mSite.mLat;
        const double refa = mount.mSite.mRefa;
        const double refb = mount.mSite.mRefb;
        const double hm = mount.mSite.mHm;
        const double temp = mount.mSite.mTemp;
        const double press = mount.mSite.mPress;
        const double humid = mount.mSite.mHumid;
        const double ttj = mount.mSite.mTtj;
        double amprms[21];
        TcsLib::copyAmprms(mount.mSite.mAmprms, amprms);
        const double diurab = mount.mSite.mDiurab;
        mount.mSite.mMutex.unlock();

    // Get a kernel reference system.
        KernelRefSys::Ptr krefsys(refsys.kernelRefSys());

    // Generate a grid of points in the focal plane.
        double xy[5][2];
        xy[0][0] = centre.x;
        xy[0][1] = centre.y;
        xy[1][0] = centre.x - gridsize;
        xy[1][1] = centre.y + gridsize;
        xy[2][0] = centre.x - gridsize;
        xy[2][1] = centre.y - gridsize;
        xy[3][0] = centre.x + gridsize;
        xy[3][1] = centre.y - gridsize;
        xy[4][0] = centre.x + gridsize;
        xy[4][1] = centre.y + gridsize;

    // Adjust refraction constants for color.
        double refac, refbc;
        slaAtmdsp( temp, press, humid, wavelr, refa, refb, wavel,
                &refac, &refbc);

    // Transform the 5 focal plane points to celestial coordinates.
        double xieta[5][2];
        for ( int i = 0; i < 5; i++ ) {

        // Focal plane coordinates.
            focalplane fp = trans.forward(instrcoord(xy[i][0], xy[i][1]));

        // Get boresight vector for this point.
            vector bs = TcsLib::bs( tel, rotl, rma.sample(tai),
                    roll.sample(tai), pitch.sample(tai),
                    ga + aoa.sample(tai), gb + aob.sample(tai), fp);

        // Aim vector.
            vector aim = TcsLib::enc2aim( roll.sample(tai), pitch.sample(tai),
                    bs, ia, ib, np);

        // Celestial coordinates
            spherical p = krefsys->ptrani( aim, ttj, amprms, ae2mt, hm, lat, 
                    diurab, refac, refbc, temp, press, humid, tlr, wavel, 
                    sst, cst);

        // Store the field centre.
            if ( i == 0 ) {
                mWcsTrans.ab0[0] = p.a;
                mWcsTrans.ab0[1] = p.b;
            }

        // To standard coordinates.
            int istat;
            slaDs2tp( p.a, p.b, mWcsTrans.ab0[0], mWcsTrans.ab0[1],
                    &xieta[i][0], &xieta[i][1], &istat);
            if ( istat ) {
                throw std::runtime_error(
                        "internal error (bad status from slaDs2tp)");
            }
        }

    // Fit 6-coefficient linear model to the x/y and xi/eta samples.
        int istat;
        slaFitxy( 6, 5, xieta, xy, mWcsTrans.coeffs, &istat);
        if ( istat ) {
            throw std::runtime_error(
                    "internal error (bad status from slaFitxy)");
        }

    // Compute and store the inverse transformation.
        invtr();
        
    // Store the reference system.
        mRefSys = refsys.clone();
    }
}

