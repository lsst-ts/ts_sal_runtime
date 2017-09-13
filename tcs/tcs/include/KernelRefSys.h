/// \file KernelRefSys.h
/// \brief Definition of the kernel coordinate reference system class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkKERNELREFSYS_H
#define tpkKERNELREFSYS_H

#include <memory>

#include "Coordinates.h"
#include "TcsLib.h"

namespace tpk {
        class RefSys;

/// Virtual base class reference systems
/**
    The KenelRefSys class is a pure virtual base class for the sky coordinate
    reference systems used internally by the pointing kernel.

    Kernel Reference systems provide an interface to the TCSpk functions that
    involve coordinate conversions to and from sky coordinates.

    \note See the TCSpk documentation for more information on the coordinate
            conversion methods.
*/
    class KernelRefSys {
        public:
        
        /// KernelRefSys auto_ptr
            typedef std::auto_ptr<KernelRefSys> Ptr;
        /// Const KernelRefSys auto_ptr
            typedef std::auto_ptr<const KernelRefSys> ConstPtr;

        /// Virtual destructor
            virtual ~KernelRefSys() {}

        /// Virtual copy constructor
            virtual KernelRefSys* clone() const = 0;

        /// aim vector to sky vector
        /**
            \returns sky vector
        */
            virtual vector aim2sky(
                const vector& aim,         ///< aim vector
                const double& sst,         ///< sine of siderial time
                const double& cst          ///< cosine of siderial time
            ) const throw() = 0;

        /// Inverse pointing transformation
        /**
            \returns sky vector
        */
            virtual vector ptrani(
                const vector& aim,         ///< aim vector
                const double& tdbj,        ///< TDB Julian epoch
                const double amprms[21],   ///< mean to apparent parameters
                const double ae2mt[3][3],  ///< mount orientation matrix
                const double& hm,          ///< height (metres)
                const double& tlat,        ///< true latitude (radians)
                const double& diurab,      ///< diurnal aberration (radians)
                const double& refa,        ///< refraction constant A
                const double& refb,        ///< refraction constant B
                const double& temp,        ///< temperature (deg K)
                const double& press,       ///< pressure (mBar)
                const double& humid,       ///< relative humidity
                const double& tlr,         ///< tropospheric lapse rate
                const double& wavel,       ///< wavelength (microns)
                const double& sst,         ///< sine of siderial time
                const double& cst          ///< cosine of siderial time
            ) const throw() = 0;

    /// Predict rotator demand
    /**
            \returns status (0 => success)
    */
            virtual int rotator(
                const vector& aim,          ///< aim vector
                const TcsLib::rotloc& rotl, ///< rotator location
                const double& rdp,          ///< predicted demand (radians)
                const bool& bp,             ///< beyond pole flag
                const double& ad,           ///< demand roll (radians)
                const double& bd,           ///< demand pitch (radians)
                const focalplane& xy,       ///< pointing origin
                const double& ia,           ///< roll index error (radians)
                const double& ib,           ///< pitch index error (radians)
                const double& np,           ///< axis non-perpendicularity 
                                            ///  (radians)
                const vector& tel,          ///< telescope vector
                const double& ga,           ///< roll guiding adjustment 
                                            ///  (radians)
                const double& gb,           ///< Pitch guiding adjustment 
                                            ///  (radians)
                const double& sia,          ///< sine of instrument alignment 
                                            ///  angle
                const double& cia,          ///< cosine of instrument alignment 
                                            ///  angle
                const double& sst,          ///< sine of siderial time
                const double& cst,          ///< cosine of siderial time
                const double& pai,          ///< instrument position angle
                const bool& slit,           ///< slit optimize
                double& rma                 ///< rotator demand (radians)
            ) const throw () = 0;

        /// Sky vector to aim vector
        /**
            \returns aim vector
        */
            virtual vector sky2aim(
                const vector& sky,         ///< sky vector
                const double& sst,         ///< sine of siderial time
                const double& cst          ///< cosine of siderial time
            ) const throw() = 0;

        /// Update target transformation
            virtual void tartran(
                const double& ttj,         ///< TT Julian epoch
                const double amprms[21],   ///< mean to apparent parameters
                const double ae2mt[3][3],  ///< mount orientation matrix
                const double& hm,          ///< height (metres)
                const double& lat,         ///< true latitude (radians)
                const double& diurab,      ///< diurnal aberration
                const double& refac,       ///< refraction constant A
                const double& refbc,       ///< refraction constant B
                const double& temp,        ///< temperature (deg K)
                const double& press,       ///< pressure (mBar)
                const double& humid,       ///< relative humidity
                const double& tlr,         ///< troposheric lapse rate
                const double& wavel,       ///< wavelength (microns)
                const double& sst,         ///< sine of siderial time
                const double& cst,         ///< cosine of siderial time
                const vector& tar          ///< target vector
            ) throw(std::runtime_error) = 0;

            /// target vector to mount roll and pitch
            /**
                \returns status (0 => success)
            */
            virtual int track(
                const vector& tar,          ///< target coordinates
                const double& sst,          ///< sine of sidereal time
                const double& cst,          ///< cosine of sidereal time
                const TcsLib::rotloc& rotl, ///< rotator location
                const double& rma,          ///< predicted rotator mechanical 
                                            ///  angle (radians)
                const double& roll,         ///< predicted roll (radians)
                const double& pitch,        ///< predicted pitch (radians)
                const double& xr,           ///< pointing origin x (in focal 
                                            ///  lengths)
                const double& yr,           ///< pointing origin y (in focal 
                                            ///  lengths)
                const double& ia,           ///< roll zero point (radians)
                const double& ib,           ///< pitch zero point (radians)
                const double& np,           ///< mount axes nonperp (radians)
                const vector& tel,          ///< telescope vector
                const double& ga,           ///< guiding correction, 
                                            ///  collimation
                const double& gb,           ///< guiding correction, pitch
                const double& rnogo,        ///< radius of "no go" region 
                                            ///  (radians)
                vector& aim,                ///< aim vector
                double& ad1,                ///< roll coordinate, first 
                                            ///  solution (radians)
                double& bd1,                ///< pitch coordinate, first 
                                            ///  solution (radians)
                double& ad2,                ///< roll coordinate, 
                                            ///  second solution (radians)
                double& bd2                 ///< pitch coordinate, second 
                                            ///  solution (radians)
            ) const throw () = 0;

            /// mount roll and pitch to sky vector
            /**
                \returns sky vector
            */
            virtual vector vtsky(
                const double& roll,         ///< roll (radians)
                const double& pitch,        ///< pitch (radians)
                const TcsLib::rotloc& rotl, ///< rotator location
                const double& rma,          ///< rotator mechanical angle 
                                            ///  (radians)
                const focalplane& xy,       ///< x,y position
                const double& sst,          ///< sine of siderial time
                const double& cst,          ///< cosine of siderial time
                const double& ia,           ///< roll axis zero point (radians)
                const double& ib,           ///< pitch axis zero point (radians)
                const double& np,           ///< mount axes non-perpedicularity 
                                            ///  (radians)
                const vector& tel,          ///< telecope vector
                const double& ga,           ///< guiding adjustment, roll 
                                            ///  (radians)
                const double& gb            ///< guiding adjustment, pitch 
                                            ///  (radians)
            ) const throw () = 0;

            /// target vector to non-rotating focal plane
            /**
                    \returns status (0 => success)
            */
            virtual int vtxe(
                const vector& tar,     ///< target vector
                const double& sst,     ///< sine of siderial time
                const double& cst,     ///< cosine of siderial time
                const double& roll,    ///< roll (radians)
                const double& pitch,   ///< pitch (radians)
                const double& ia,      ///< roll axis zero point (radians)
                const double& ib,      ///< pitch axis zero point (radians)
                const double& np,      ///< mount axes non-perpedicularity 
                                       // ]/  (radians)
                const vector& tel,     ///< telecope vector
                const double& ga,      ///< guiding adjustment, roll (radians)
                const double& gb,      ///< guiding adjustment, pitch (radians)
                focalplane& xieta      ///< image position
            ) const throw () = 0;

            /// target vector to rotating focal plane
            /**
                    \returns status (0 => success)
            */
            virtual int vtxy(
                const vector& tar,          ///< target vector
                const double& sst,          ///< sine of siderial time
                const double& cst,          ///< cosine of siderial time
                const TcsLib::rotloc& rotl, ///< rotator location
                const double& rma,          ///< rotator mechanical angle 
                                            // ]/  (radians)
                const double& roll,         ///< roll (radians)
                const double& pitch,        ///< pitch (radians)
                const double& ia,           ///< roll axis zero point (radians)
                const double& ib,           ///< pitch axis zero point (radians)
                const double& np,           ///< mount axes non-perpedicularity 
                                            ///  (radians)
                const vector& tel,          ///< telecope vector
                const double& ga,           ///< guiding adjustment, roll 
                                            ///  (radians)
                const double& gb,           ///< guiding adjustment, pitch 
                                            ///  (radians)
                focalplane& xy              ///< image position
            ) const throw () = 0;
        protected:

    /// Default constructor
    /**
        The default constructor is protected so that only derived classes
        can call it.
    */
            KernelRefSys() {};
    };
}
#endif

