/// \file Target.h
/// \brief Definition of the target class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkTARGET_H
#define tpkTARGET_H

#include <memory>

#include "Coordinates.h"
#include "RefSys.h"
#include "Site.h"
#include "TcsLib.h"
#include "TcsMutex.h"

namespace tpk {

    extern const RefSys* defaultFrame;
    extern tcspk::PRF refsub;

/// Virtual base class for targets
/**
    A Target represents a celestial position of an object and has a method
    that returns the position of the object at a specified time. The "fast"
    processing calls the position method to get the target position in the
    tracking reference frame and so its implementation must be resonably
    efficient.

    The base class defines a mutex for protecting the member data from
    simultaneous access from different threads and stores the site and
    tracking frame.

    \attention Derived classes must implement the position, adjust,
                    update and clone methods.

    All the methods of this class are thread safe.
*/
    class Target {
        public:
        /// Target auto_ptr
            typedef std::auto_ptr<Target> Ptr;
        /// Const Target auto_ptr
            typedef std::auto_ptr<const Target> ConstPtr;
            
            virtual ~Target() {}

        /// Get position in tracking frame
        /**
            Because this method is called by the "fast" processing it must not
            involve excessing amounts of computation.

            \returns position at time t
        */
            virtual vector position(
                const double& t                  ///< TAI (MJD)
            ) const = 0;
            virtual vector position(
                const double& t,                 ///< TAI (MJD)
                const RefSys& frame              ///< coordinate frame
            ) const;

        /// Update target.
        /**
            This method is called by the "medium" processing and is an
            opportunity to do any onerous calculations needed to enable
            the position method to compute the position in the tracking frame
            in an efficient manner.

            The default implementation, which does nothing, can be used when
            no such calculation is necessary.
        */
            virtual void update(
                const double& t                  ///< TAI (MJD)
            ) {}

        /// Adjust target position
            virtual void adjust(
                const double& t,           ///< TAI (MJD)
                const vector& tar          ///< new target coordinates
            ) = 0;

        /// Set tracking frame
        /**
            Defines the tracking frame for the target.
        */
            virtual void trackframe(
                const RefSys& refsys        ///< tracking frame
            ) {
                mTrackFrame.reset(refsys.clone());
            }

        /// Virtual copy constructor
            virtual Target* clone() const = 0;

        /// Get site
        /**
            \returns reference to the telescope site
        */
            virtual const Site& site() {
                return mSite;
            }

        protected:
        /*
            The Constructor, destructor and assignment operators are all
            declared protected so that Target objects cannot be created
            or destroyed directly.
        */

        /// Constructor
        /**
            The constructor stores the site and sets the target's tracking
            frame to the default tracking frame defined in the tpk::
            namespace.
        */
            Target(
                const Site& site        ///< telescope site
            ) : mSite(site),
                mTrackFrame(defaultFrame->clone()) {}

        /// Copy constructor
            Target(
                const Target& src
            ) : mSite(src.mSite),
                mTrackFrame(src.mTrackFrame->clone()) {}

            const Site& mSite;                ///< telescope site
            RefSys::ConstPtr mTrackFrame;     ///< tracking frame
            mutable TcsMutex mMutex;          ///< mutex

        private:
        // Default constructor
            Target();
        // Assignment operator
            Target& operator=(const Target&);
    };
}
#endif

