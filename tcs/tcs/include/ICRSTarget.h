/// \file ICRSTarget.h
/// \brief Definition of the international coordinate reference system
///        target class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkICRSTARGET_H
#define tpkICRSTARGET_H

#include <stdexcept>
#include <string>

#include "TrackingTarget.h"

namespace tpk {
    class Site;
    class RefSys;

/// ICRS target
/**
    An ICRSTarget object represents a fixed position in the ICRF

    All the methods of this class are thread safe.
*/
    class ICRSTarget : public TrackingTarget {
        public:
            ICRSTarget(
                const Site& site,
                const vector& pos
            );
            ICRSTarget(
                const Site& site,
                const double& t0,
                const vector& pos,
                const deltav& rate
            );
            ICRSTarget(
                const Site& site,
                const double& ra,
                const double& dec
            );
            ICRSTarget(
                const Site& site,
                const double& t0,
                const double& ra,
                const double& dec,
                const double& radot,
                const double& decdot
            );
            ICRSTarget(
                const Site& site,
                const std::string& starget
            );
            ICRSTarget(
                const Site& site,
                const double& ra,
                const double& dec,
                const double& epoch,
                const double& pmRA,
                const double& pmDec,
                const double& parallax,
                const double& rv
            );

            virtual ICRSTarget* clone() const {
                return new ICRSTarget(*this);
            }
            using TrackingTarget::position;
            vector position(
                const double& t,
                const RefSys& frame
            ) const;
            virtual void adjust(
                const double& t,
                const vector& tar
            );
        protected:
            vector mPositionICRS;       ///< Position in ICRS
            double mT0ICRS;             ///< Reference time
            deltav mVelocityICRS;       ///< Velocity in ICRS
        private:
            void init(
                const double& ra,
                const double& dec,
                const double& pmr,
                const double& pmd,
                const double& px,
                const double& rv,
                const double& epoch
            );
    };
}
#endif

