/// \file Pcs.h
/// \brief Definition of the Pcs class

// D L Terrett
// Copyright STFC. All rights reserved.

#ifndef dpkPCS_H
#define dpkPCS_H

#include <string>
#include <vector>
#include <tpk.h>
#include <tcl.h>
#include "tpkobj.h"
#include "Axis.h"

namespace dpk {

/// Virtual base class for demonstation pointing kernel applications
    class Pcs {
        friend int AxisCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        friend int EphempathCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        friend int GuideCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        friend int IpaCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        friend int LimitTimeCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        friend int OffsetCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        friend int OpticsCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        friend int OriginCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        friend int PointingCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        friend int PointingModelCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        friend int SkySampleCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        friend int StatsCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        friend int TargetCmd( ClientData clientdata, Tcl_Interp *interp,
                int objc, Tcl_Obj *CONST objv[]);
        friend int TelInfoCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        friend int WavelengthCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        friend int WrapCmd( ClientData clientdata,
                Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
        public:
            Pcs(Tcl_Interp* interp);
            virtual ~Pcs();
            void fast();
            void medium();
            void slow(double, double, double);
            void stats();
            virtual void uiExport() = 0;
            virtual void update() = 0;
            
            /// Get focal length
            /**
                \returns focal length (mm)
            */
            virtual double focalLength() const {
                return mFocalLength;
            }

        /// Guider information structure
        /**
            The guider structure stores flags to indicate whether or not
            the guider is active (i.e. guiding) and whether it should track
            the demand or achieved rotator position and a pointer to the
            guider virtual telescope.
        */
            typedef struct guider {
                guider(): guide(false), track_rot(false) {}
                bool guide;             ///< guide enabled flag
                bool track_rot;         ///< track rotator flag
                tpk::AutoGuider* gvt;   ///< auto-guider virtual telescope
            } guider;

        // Methods for registering kernel objects.
            void registerAxis(Axis*, const std::string&);
            void registerAxis(Axis*, tpk::WrapControl*, const std::string&);
            void registerGuider(guider*, const std::string&);
            void registerMount(tpk::MountVt*, const std::string&);
            void registerOptics(tpk::OpticsVt*, const std::string&);
            void registerPointingControl(tpk::PointingControl*, 
                    const std::string&);

        // Methods for setting Tcl variables.
            void setUiVar(const std::string& name, double value);
            void setUiVar(const std::string& name, bool value);
            void setUiVar(const std::string& name, std::string value);
            void setUiVar(const std::string& name, const std::string& elem,
                    double value);
            void setUiVar(const std::string& name, const std::string& elem,
                    bool value);
            void setUiVar(const std::string& name, const std::string& elem,
                    std::string value);
            void setUiVar(const std::string& name, const std::string& elem,
                    std::vector<tpk::xycoord>& value);

            virtual double limit() {
                return 0.0;
            }
        protected:
            double mTai;                          ///< current time (MJD)
            tpk::Clock* mClock;                   ///< clock
            tpk::TimeKeeper* mTimeKeeper;         ///< time keeper
            tpk::Site* mSite;                     ///< telescope site
            double mFocalLength;                  ///< telescope focal length
            std::vector<tpk::vector> mSkySamples; ///< sample sky positions
            double mWindshake;                    ///< windshake scale (arcsec)
            Tcl_Interp* mInterp;                  ///< Tcl interpreter
            bool mTrackMount;                     ///< optics track mount flag
            tpk::LimitCalc* mLimitCalc;           ///< tracking time calculator
            std::string mLimitReason;             ///< reason for tracking limit
        private:
        
        // Tables of custom Tcl objects.
            TpkObj<tpk::Target>* mTargets;
            TpkObj<tpk::PointingOrigin>* mOrigins;
            TpkObj<tpk::BaseVt>* mTelescopes;
            TpkObj<tpk::MountVt>* mMounts;
            TpkObj<Axis>* mAxes;
            TpkObj<guider>* mGuiders;
            TpkObj<tpk::PointingControl>* mPointing;
            TpkObj<tpk::PointingModel>* mModels;
            TpkObj<tpk::WrapControl>* mWraps;

            Pcs(const Pcs&);
            Pcs& operator=(const Pcs&);
        };
}
#endif

