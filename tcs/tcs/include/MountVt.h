/// \file MountVt.h
/// \brief Definition of the mount virtual telescope class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkMOUNTVT_H
#define tpkMOUNTVT_H

#include <memory>
#include <stdexcept>

#include "BaseVt.h"
#include "Coordinates.h"
#include "KernelRefSys.h"
#include "MountType.h"
#include "PointingModel.h"
#include "RefSys.h"
#include "Target.h"
#include "TcsMutex.h"
#include "TcsLib.h"
#include "Trajectory.h"


namespace tpk {
    class DawdleFilter;
    class MountType;
    class PointingOrigin;
    class RotatorLoc;
    class Site;
    class Target;
    class TimeKeeper;
    class Transform;

/// Mount virtual telescope
/**
    The MountVt class implements the mount virtual telescope.
    It generates mount azimuth, altitude and rotator mechanical
    angle trajectories.

    All the methods of this class are thread safe.
*/
    class MountVt : public BaseVt {
        friend class AutoGuider;
        friend class BaseVt;
        friend class KernelWcs;
        friend class OpticsVt;
        friend class PointCat;
        friend class PointingControl;
        friend class PointingObs;
        public:
        /// MountVt auto_ptr
            typedef std::auto_ptr<MountVt> Ptr;
        /// Const MountVt auto_ptr
            typedef std::auto_ptr<const MountVt> ConstPtr;
            MountVt(
                const TimeKeeper& ticker,
                const Site& site,
                const RotatorLoc& rotl,
                const MountType& mtype,
                DawdleFilter* dawdle = 0,
                const RefSys& trackframe = *defaultFrame
            );
            MountVt(
                const MountVt& src
            );
            MountVt(
                const TimeKeeper& ticker,
                const Site& site,
                const MountVt& src
            );
            int track(
                unsigned int samples,
                const Trajectory& rma,
                const Trajectory& aoa,
                const Trajectory& aob
            ) throw();
            int track(
                unsigned int samples,
                const Trajectory& aoa,
                const Trajectory& aob
            ) throw();
            int track(
                unsigned int samples,
                const Trajectory& rma
            ) throw();
            int track(
                unsigned int samples
            ) throw();
            Trajectory roll() const throw();
            Trajectory pitch() const throw();
            Trajectory rma() const throw();
            vector position(
                const Trajectory& roll,
                const Trajectory& pitch,
                const Trajectory& rma
            ) const throw();
            vector position(
                const Trajectory& roll,
                const Trajectory& pitch,
                const Trajectory& rma,
                const Trajectory& aoa,
                const Trajectory& aob
            ) const throw();
            double orientation(
                const Trajectory& roll,
                const Trajectory& pitch,
                const Trajectory& rma
                ) const throw();
            double orientation(
                const Trajectory& roll,
                const Trajectory& pitch,
                const Trajectory& rma,
                const Trajectory& aoa,
                const Trajectory& aob
                ) const throw();
            void newPointingModel(
                const PointingModel& model
            ) throw(std::runtime_error);
            void setPai(
                const double& pai,
                const RefSys& refsys,
                const bool slit = false
            ) throw();
            void setIaa(
                const double& iaa,
                const Transform& transf
            ) throw();
            void setRotRef(
                const Target* reference
            ) throw();
            void setGuide(
                const double& ga,
                const double& gb
            ) throw();
            void getGuide(
                double& ga,
                double& gb
            ) const throw();
            void dawdle(
                const bool& bypass,
                const double& tunepar
            ) throw ();
            bool dawdle(
                const bool& bypass
            ) throw ();
            void update() throw(std::runtime_error);
            void updatePM() throw(std::runtime_error);
            vector xy2sky(
                const xycoord& xy,
                const RefSys& refsys,
                const double& wavel
            ) const throw(std::runtime_error);
            void setBeyondPole(
                const bool& state
            );
        protected:
            double mAux[3];                        ///> auxiliary pointing data

            const TcsLib::rotloc mRotloc;   ///> rotator location
            MountType mMtype;               ///> mount type
            PointingModel::ConstPtr mPm;    ///> pointing model
            DawdleFilter* mDawdle;          ///> dawdle filter
            double mGa;                     ///> guiding corrections, 
                                            ///  roll (radians)
            double mGb;                     ///> guiding corrections, 
                                            ///  pitch (radians)
            Trajectory mAoa;                ///> ao collimation 
                                            ///  corrections, roll (radians)
            Trajectory mAob;                ///> ao collimation corrections
                                            ///  corrections, pitch (radians)
            double mAe2nm[3][3];            ///> az/el to nominal mount 
                                            ///  rotation matrix
            double mIa;                     ///> index error, roll (radians)
            double mIb;                     ///> index error, pitch (radians)
            double mNp;                     ///> axis non-perpendicularity
                                            ///  (radians)
            vector mTelVec;                 ///> telescope vector
            double mAe2mt[3][3];            ///> az,el to mount rotation matrix
            Target::Ptr mRotTarget;         ///> rotation reference target
            KernelRefSys::Ptr mKernelRF;    ///> kernel rotator reference frame
            RefSys::ConstPtr mRotFrame;     ///> rotator reference frame
            KernelRefSys::Ptr mKernelRTF;   ///> kernel rotator target reference
                                            ///  frame 
            RefSys::ConstPtr mRtarFrame;    ///> rotator target reference frame
            double mPai;                    ///> position angle of 
                                            ///  instrument (radians)
            double mCia;                    ///> cosine of instrument
                                            ///  alignment angle (radians)
            double mSia;                    ///> sine of instrument
                                            ///  alignment angle (radians)
            Trajectory mRoll;               ///> predicted roll trajectory
            Trajectory mPitch;              ///> predicted pitch trajectory
            Trajectory mRma;                ///> rotator angle trajectory
            bool mBp;                       ///> beyond pole flag
            bool mSlit;                     ///> slit optimised rotation
        private:
        // No default constructor or assignment operator
            MountVt();
            MountVt& operator=(const MountVt&);
    };
}
#endif

