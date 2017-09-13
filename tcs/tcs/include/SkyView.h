/// \file SkyView.h
/// \brief Definition of the SkyView class

// D L Terrett
// Copyright STFC. All rights reserved.

#ifndef dpkSKYVIEW_H
#define dpkSKYVIEW_H

#include <vector>
#include <tpk.h>
#include "Pcs.h"

namespace dpk {

/// Artificial focal plane image generator
/**
    A SkyView object generates the positions in the focal plane
    of the list of sample star positions.
*/
    class SkyView {
        public:
            SkyView(
                const tpk::MountVt& mount,
                const tpk::Transform& transform,
                Pcs& pcs,
                const std::string& name,
                const std::vector<tpk::vector>& skysample
            );
            virtual ~SkyView() {};
            virtual void genxy (
                double roll,
                double pitch,
                double rma,
                double windshake,
                double tip = 0.0,
                double tilt = 0.0
            );
            virtual bool measure(
                double guiderx,
                double guidery,
                double box,
                double& xmeas,
                double& ymeas
            );
            virtual void uiExport(
                const std::string& name,
                const std::string& elem
            );
        protected:
            double gauss();
            Pcs& mPcs;                      ///< Pointing kernel
            tpk::MountVt mSkyVt;            ///< Mount virtual telescope
            const tpk::Transform& mTransform;   
                                            ///< Focal plane transformation
            const std::vector<tpk::vector>& mSkySample;
                                            ///< Sky positions
            std::vector<tpk::xycoord> mFocalPlane;
                                            ///< Focal plane coordinates
            double mShakeX;                 ///< Windshake in x
            double mShakeY;                 ///< Windshake in y
    };
}
#endif

