/// \file TopoApptTarget.h
/// \brief Definition of the topocentric apparent target class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkTOPOAPPTTARGET_H
#define tpkTOPOAPPTTARGET_H

#include <stdexcept>
#include <string>

#include "TrackingTarget.h"

namespace tpk {
    class Site;
    class RefSys;

/// Topocentric apparent target
/**
    A TopoApptTarget object represents a topocentric apparent place.
*/
    class TopoApptTarget : public TrackingTarget {
        public:
            TopoApptTarget(
                const Site& site,
                const vector& pos
            );
            TopoApptTarget(
                const Site& site,
                const double& t0,
                const vector& pos,
                const deltav& rate
            );
            TopoApptTarget(
                const Site& site,
                const double& ra,
                const double& dec
            );
            TopoApptTarget(
                const Site& site,
                const double& t0,
                const double& ra,
                const double& dec,
                const double& radot,
                const double& decdot
            );
            TopoApptTarget(
                const Site& site,
                const std::string& starget
            );

        /// Clone object
            virtual TopoApptTarget* clone() const {
                return new TopoApptTarget(*this);
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
            vector mPositionTopoAppt;       ///< Position in Topocentric Appt
            double mT0TopoAppt;             ///< Reference time
            deltav mVelocityTopoAppt;       ///< Velocity in Topocentric Appt
    };
}
#endif

