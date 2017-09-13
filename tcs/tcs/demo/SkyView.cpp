/// \file SkyView.cpp
/// \brief Implemention of the SkyView class.

#include <stdlib.h>
#include <vector>
#include <tpk.h>
#include "Util.h"
#include "SkyView.h"

namespace dpk {

    SkyView::SkyView(
        const tpk::MountVt& mount,       ///< mount virtual telescope
        const tpk::Transform& transform, ///< focal plane to camera transformation
        Pcs& pcs,                        ///< pcs to register in
        const std::string& name,         ///< virtual telescope name
        const std::vector<tpk::vector>& skysamp ///< sky positions of stars
    ) : mPcs(pcs), mSkyVt(mount), mTransform(transform), mSkySample(skysamp), 
            mShakeX(0.0), mShakeY(0.0) {
    
    // Register the virtual telescope.
        mPcs.registerMount(&mSkyVt, name);
    }

/// Generate the positions in the focal plane of the sample stars.
    void SkyView::genxy(
        double roll,              ///< roll position of mount (radians)
        double pitch,             ///< pitch position of mount (radians)
        double rma,               ///< rotator mechanical angle (radians)
        double windshake,         ///< windshake estimate (mm)
        double tip,               ///< optics tip (radians)
        double tilt               ///< optics tilt (radians)
    ) {

    // Update the sky virtual telescope
        mSkyVt.track(1, tip, tilt);

    // Create a world coordinate object from the sky virtual telescope to map
    // star coordinates to positions in the focal plane.
        tpk::KernelWcs wcs( mSkyVt, roll, pitch, rma, tip, tilt,
                tpk::ICRefSys(), 0.5, mTransform, tpk::xycoord( 0.0, 0.0 ),
                30.0 * tpk::TcsLib::as2r );

    // Clear the array of focal plane positions.
        mFocalPlane.clear();
        
    // Update windshake
        mShakeX = ( mShakeX * 99.0 + windshake * gauss() ) / 100.0;
        mShakeY = ( mShakeY * 99.0 + windshake * gauss() ) / 100.0;

    // Convert each of the sample points to x/y in the focal plane.
        for ( size_t i = 0; i < mSkySample.size(); i++ ) {

        // Sample position with windshake added.
            tpk::spherical s = mSkySample[i] +
                    tpk::xycoord(mShakeX, mShakeY); 

        // Conversion to focal plane coordinate may fail if the star is too
        // far from the telescope position.
            try {
                double xp, yp;
                wcs.sph2inst( s.a, s.b, xp, yp );
                mFocalPlane.push_back(tpk::xycoord(xp,yp));
            } catch (...) {}
        }
    }

/// Measure star position.
/**
    This method seaches the list of star positions for a star that lies
    inside the guider box and returns its position if one is found.
    
    \returns Star was found
*/
    bool SkyView::measure(
        double guiderx,             ///< x position of guider
        double guidery,             ///< y position of guider
        double box,                 ///< guider box size
        double& xmeas,              ///< measured x position
        double& ymeas               ///< measured y position
    ) {
        for ( size_t i = 0; i < mFocalPlane.size(); i++ ) {
            xmeas = mFocalPlane[i].x;
            ymeas = mFocalPlane[i].y;
            if ( std::abs( xmeas - guiderx ) < box &&
                    std::abs( ymeas - guidery ) < box ) {
                return true;
            }
        }
        return false;
    }

/// Export focal plane positions to Tcl    
    void SkyView::uiExport(
        const std::string& name,    ///< array name
        const std::string& elem     ///< element name
    ) {
        mPcs.setUiVar(name, elem, mFocalPlane);
    }
     
    double SkyView::gauss() {
        double a = (static_cast<double>(rand()) + 1.0e-20) / 
                static_cast<double>(RAND_MAX);
        double b = (static_cast<double>(rand()) + 1.0e-20) / 
                static_cast<double>(RAND_MAX);
        return sqrt( -2.0 * log(a) ) * cos( tpk::TcsLib::pi2 * b );
    }
}
