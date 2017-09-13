/// \file FK5Target.h
/// \brief Definition of the FK5 target class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkFK5TARGET_H
#define tpkFK5TARGET_H

#include <stdexcept>
#include <string>

#include "TrackingTarget.h"

namespace tpk {
    class RefSys;
    class Site;

/// FK5 target
/**
    An FK5Target object represents a fixed position in the FK5

    All the methods of this class are thread safe.
*/
    class FK5Target : public TrackingTarget {
        public:
            FK5Target(
                const Site& site,
                const vector& pos,
                const double& equinox = 2000.0
            );
            FK5Target(
                const Site& site,
                const double& t0,
                const vector& pos,
                const deltav& rate,
                const double& equinox = 2000.0
            );
            FK5Target(
                const Site& site,
                const double& ra,
                const double& dec,
                const double& equinox = 2000.0
            );
            FK5Target(
                const Site& site,
                const double& t0,
                const double& ra,
                const double& dec,
                const double& radot,
                const double& decdot,
                const double& equinox = 2000.0
            );
            FK5Target(
                const Site& site,
                const std::string& starget
            );
            FK5Target(
                const Site& site,
                const double& ra,
                const double& dec,
                const double& equinox,
                const double& epoch,
                const double& pmRA,
                const double& pmDec,
                const double& parallax,
                const double& rv = 0.0
            );

            FK5Target* clone() const {
                return new FK5Target(*this);
            }

            using TrackingTarget::position;
            vector position(
                const double& t,
                const RefSys& frame
            ) const;
            void adjust(
                const double& t,
                const vector& tar
            );
        protected:
            vector mPositionFK5;     ///< position in FK5
            double mT0FK5;           ///< reference time
            deltav mVelocityFK5;     ///< velocity in FK5
            double mEquinox;         ///< equinox of position
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

