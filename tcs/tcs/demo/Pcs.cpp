/// \file Pcs.cpp
/// \brief implements the PCS framework class

// D L Terrett
// Copyright STFC. All rights reserved.

#include <tcl.h>
#include <exception>
#include "tpk.h"
#include "Pcs.h"
#include "Util.h"
#include "tpkobj.h"

namespace dpk {


/// Constructor
    Pcs::Pcs(
        Tcl_Interp* interp                  ///< Tcl interpreter
    ) : mWindshake(0.0), mInterp(interp), mTrackMount(false), 
        mLimitReason("") {

// Initialise the Tcl stubs mechanism.
    if ( Tcl_InitStubs( interp, "8.0", 0 ) == NULL ) throw std::exception();

   // Initialise hash tables
        mTargets = new TpkObj<tpk::Target>("target");
        mOrigins = new TpkObj<tpk::PointingOrigin>("pointingOrigin");
        mTelescopes = new TpkObj<tpk::BaseVt>("telescope");
        mMounts = new TpkObj<tpk::MountVt>("mount");
        mAxes = new TpkObj<dpk::Axis>("axis");
        mGuiders = new TpkObj<guider>("guider");
        mPointing = new TpkObj<tpk::PointingControl>("pointingControl");
        mModels = new TpkObj<tpk::PointingModel>("pointingModel");
        mWraps = new TpkObj<tpk::WrapControl>("wrapControl");
        
    // Link windshake to Tcl variable.
        Tcl_LinkVar(mInterp, "windshake", reinterpret_cast<char*>(&mWindshake),
                TCL_LINK_DOUBLE);
    }

/// Destructor
    Pcs::~Pcs() {
        delete mTargets;
        delete mOrigins;
        delete mTelescopes;
        delete mMounts;
        delete mAxes;
        delete mGuiders;
        delete mPointing;
        delete mModels;
    }

/// Slow process
    void Pcs::slow(
        double temp,             ///< Ambient temperature (deg K)
        double press,            ///< Pressure (mBar)
        double humid             ///< Relative humidity
    ) {

    // Update site.
        mSite->refresh( mTai, temp, press, humid);
    }

/// Medium process
    void Pcs::medium() {

    // Update all the virtual telescopes.
        Tcl_HashSearch search;
        Tcl_HashEntry* ptr = Tcl_FirstHashEntry(&mTelescopes->table, &search);
        while ( ptr ) {
            TpkObj<tpk::BaseVt>::Tpk_Obj* obj =
                    static_cast<TpkObj<tpk::BaseVt>::Tpk_Obj*>
                    (Tcl_GetHashValue(ptr));
            obj->obj->update();
            ptr = Tcl_NextHashEntry(&search);
        }

    // Update all the mount pointing models.
        ptr = Tcl_FirstHashEntry(&mMounts->table, &search);
        while ( ptr ) {
            TpkObj<tpk::MountVt>::Tpk_Obj* obj =
                    static_cast<TpkObj<tpk::MountVt>::Tpk_Obj*>
                    (Tcl_GetHashValue(ptr));
            obj->obj->updatePM();
            ptr = Tcl_NextHashEntry(&search);
        }
    }

/// Fast process
    void Pcs::fast() {

    // Read the clock.
        double tai = mClock->read();

    // Only do the fast loop processing.If the time has advanced by more than 
    // 10 ms. This avoids running the pointing calculations twice at the same
    // time stamp if there is any jitter in the timing of the execution of
    // the Tcl fast command.
        if ( tai - mTimeKeeper->tai() > 0.01 / 86400.0 ) {

        // Store the new time.
            mTai = tai;

        // Update the time keeper.
            mTimeKeeper->update();

        // Call the application specific update routine.
           update();
        }
    }

/// Update Tcl variables with the kernel state
    void Pcs::stats() {

    // Update time as a double.
        setUiVar("tai", mTai);

    // Update time formatted as a string.
        setUiVar("tai_string", Util::formatMJD(mTai));

    // Update siderial time string.
        setUiVar("st_string", Util::formatTOD(mSite->st(mTai)));

    // Call application specific udate interface update routine.
        uiExport();
    }

/// Register axis.
/**
    Axes can be enabled and disabled and tuned.
*/
    void Pcs::registerAxis(
        Axis* axis,                ///< axis
        const std::string& name    ///< name
    ) {
        mAxes->NewObj(mInterp, axis, Tcl_NewStringObj(name.c_str(),-1));
    }
    
/// Register axis with wrap.
/**
    Axes can also have an associated wrap controller.
*/
    void Pcs::registerAxis(
        Axis* axis,                ///< axis
        tpk::WrapControl* wrap,    ///< wrap controller
        const std::string& name    ///< name
    ) {
        mAxes->NewObj(mInterp, axis, Tcl_NewStringObj(name.c_str(),-1));
        mWraps->NewObj(mInterp, wrap, Tcl_NewStringObj(name.c_str(),-1));
    }

/// Register guider
/**
    The guider virtual telescope associated with the guider is registered in
    the table of virtual telescopes and the guider_info structure registered
    in the table of guiders.
*/
    void Pcs::registerGuider(
        guider* guider_info,       ///< guider info structure
        const std::string& name    ///< name
    ) {

    // Register the guider virtual telescope in the table of telescopes.
        mTelescopes->NewObj(mInterp, guider_info->gvt, 
                Tcl_NewStringObj(name.c_str(),-1));

    // Register the guider structure.
        mGuiders->NewObj(mInterp, guider_info, Tcl_NewStringObj(name.c_str(),-1));
    }

/// Register a mount virtual telescope.
/**
    The virtual telescope is registered in the tables of mounts and virtual
    telescopes.
*/
    void Pcs::registerMount(
        tpk::MountVt* mount,          ///< mount
        const std::string& name       ///< name
    ) {

    // Register the virtual telescope.
        mTelescopes->NewObj(mInterp, mount, Tcl_NewStringObj(name.c_str(),-1));

    // Register the mount.
        mMounts->NewObj(mInterp, mount, Tcl_NewStringObj(name.c_str(),-1));
    }

/// Register optics virtual telescope
/**
    Registers the optics virtual telescope in the table of virtual telescopes.
*/
    void Pcs::registerOptics(
        tpk::OpticsVt* optics,        ///< optics virtual telescope
        const std::string& name       ///< name
    ) {

    // Register the virtual telescope.
        mTelescopes->NewObj(mInterp, optics, Tcl_NewStringObj(name.c_str(),-1));
    }

/// Registers a pointing controller
    void Pcs::registerPointingControl(
        tpk::PointingControl* pc,        ///< pointing controller
        const std::string& name          ///< name
    ) {

    // Register the pointing controller.
        mPointing->NewObj(mInterp, pc, Tcl_NewStringObj(name.c_str(),-1));
    }
    
/// Set a Tcl variable in the tpk:: namespace to a double value.
    void Pcs::setUiVar( 
        const std::string& name,   ///< variable name
        double value               ///< new value
    ) {
        Tcl_SetVar2Ex( mInterp, ("tpk::" + name).c_str(), 0, 
                Tcl_NewDoubleObj(value), TCL_NAMESPACE_ONLY );
    }

/// Set a Tcl variable in the tpk:: namespace to a boolean value.
    void Pcs::setUiVar( 
        const std::string& name,   ///< variable name
        bool value                 ///< new value
    ) {
        Tcl_SetVar2Ex( mInterp, ("tpk::" + name).c_str(), 0, 
                Tcl_NewBooleanObj(value), TCL_NAMESPACE_ONLY );
    }

/// Set a Tcl variable in the tpk:: namespace to a string value.
    void Pcs::setUiVar( 
        const std::string& name,   ///< variable name
        std::string value          ///< new value
     ) {
         Tcl_SetVar2Ex( mInterp, ("tpk::" + name).c_str(), 0, 
             Tcl_NewStringObj(value.c_str(),-1), TCL_NAMESPACE_ONLY );
    }

/// Set a Tcl array element in the tpk:: namespace to a double.
    void Pcs::setUiVar( 
        const std::string& name,   ///< array name
        const std::string& elem,   ///< element name
        double value               ///< new value
    ) {
        Tcl_SetVar2Ex( mInterp, ("tpk::" + name).c_str(), elem.c_str(),
            Tcl_NewDoubleObj(value), TCL_NAMESPACE_ONLY );
    }

/// Set a Tcl array element in the tpk:: namespace to a boolean.
    void Pcs::setUiVar( 
        const std::string& name,   ///< array name
        const std::string& elem,   ///< element name
        bool value                 ///< new value
    ) {
        Tcl_SetVar2Ex( mInterp, ("tpk::" + name).c_str(), elem.c_str(), 
            Tcl_NewBooleanObj(value), TCL_NAMESPACE_ONLY );
    }

/// Set a Tcl array element in the tpk:: namespace to a string.
    void Pcs::setUiVar( 
        const std::string& name,   ///< array name
        const std::string& elem,   ///< element name
        std::string value          ///< new value
    ) {
        Tcl_SetVar2Ex( mInterp, ("tpk::" + name).c_str(), elem.c_str(),
            Tcl_NewStringObj(value.c_str(),-1), TCL_NAMESPACE_ONLY );
    }

/// Set a Tcl array element to a vector of x/y coordinates
    void Pcs::setUiVar(
        const std::string& name,            ///< array name
        const std::string& elem,            ///< element name
        std::vector<tpk::xycoord>& values   ///< vector of values
    ) {
        Tcl_Obj* sampleObj = Tcl_NewListObj( 0, NULL);
        for ( size_t i = 0; i < values.size(); i++ ){
            Tcl_ListObjAppendElement( mInterp, sampleObj, 
                Tcl_NewDoubleObj(values[i].x) );
            Tcl_ListObjAppendElement( mInterp, sampleObj, 
                Tcl_NewDoubleObj(values[i].y) );
        }
        Tcl_SetVar2Ex( mInterp, ("tpk::" + name).c_str(), elem.c_str(), 
                sampleObj, TCL_NAMESPACE_ONLY );
    }
}
