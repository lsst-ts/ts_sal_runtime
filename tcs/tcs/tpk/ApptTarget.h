/// \file ApptTarget.h
/// \brief Definition of the geocentric apparent target class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkAPPTTARGET_H
#define tpkAPPTTARGET_H

#include <stdexcept>
#include <string>

#include "TrackingTarget.h"

namespace tpk {
    class Site;
    class RefSys;

/// Geocentric apparent RA,Dec target
/**
    An ApptTarget object represents a geocentric apparent place.

    All the methods of this class are thread safe.
*/
    class ApptTarget : public TrackingTarget {
        public:
            ApptTarget(
                const Site& site,
                const vector& pos
            );
            ApptTarget(
                const Site& site,
                const double& t0,
                const vector& pos,
                const deltav& rate
            );
            ApptTarget(
                const Site& site,
                const double& ra,
                const double& dec
            );
            ApptTarget(
                const Site& site,
                const double& t0,
                const double& ra,
                const double& dec,
                const double& radot,
                const double& decdot
            );
            ApptTarget(
                const Site& site,
                const std::string& starget
            );
            virtual ApptTarget* clone() const {
                return new ApptTarget(*this);
            };
            using TrackingTarget::position;
            vector position(
                const double& t,
                const RefSys& refsys
            ) const;
            virtual void adjust(
                const double& t,
                const vector& tar
            );
        protected:
            vector mPositionAppt;    ///< geocentric apparent RA, Dec
            double mT0Appt;          ///< reference time
            deltav mVelocityAppt;    ///< tracking rate in geocentric apparent
    };
}
#endif

