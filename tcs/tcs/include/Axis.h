/// \file Axis.h
/// \brief Definition of the Axis class

// D L Terrett
// Copyright STFC. All rights reserved.

#ifndef dpkAXIS_H
#define dpkAXIS_H

#include <tcl.h>
#include "tpk.h"

namespace dpk {

    /// Simulation of one axis of a mechanism.
    class Axis {
        friend int AxisCmd( ClientData clientdata, Tcl_Interp *interp,
                int objc, Tcl_Obj *CONST objv[]);

        public:
        /// Servo history structure
            typedef struct {
                double peold;       ///< Position error last time
                double accumn;      ///< Near integrator
                double accumf;      ///< Far integrator
                double v0;          ///< Latest velocity demand
                double vm1;         ///< Previous velocity demand
                double vm2;         ///< Velocity demand before that
                int ninpos;         ///< Successive "in position" passes
            } servoh;

            Axis(
                double tick,
                double vcal,
                double gs,
                double gp,
                double gi,
                double pi,
                double gd,
                double pnear,
                double dpmin,
                double dpmax,
                double dvmax,
                double damax,
                double djmax,
                double pinit
            );
            virtual bool update(
                double t,
                const tpk::Trajectory& demand
            );
            
        /// Get current position
        /**
            \returns Current position trajectory
        */
            tpk::Trajectory position(){
                return Pos;
            }
            
        /// Set enable flag
            virtual void enable(
                bool en         ///< enable flag
            ) {
                enabled = en;
            }
        protected:
            double Tick;            ///< Tick length
            double Vcale;           ///< Velocity feed forward calibration
            double Gs;              ///< Gain: SQRT
            double Gp;              ///< Gain: proportional
            double Gi;              ///< Gain: integrator
            double Pi;              ///< Anti-windup (integrator window)
            double Gd;              ///< Derivative gain
            double Pnear;           ///< Position near enough
            double DpMin;           ///< Minimum position demand
            double DpMax;           ///< Maximum position demand
            double DvMax;           ///< Maximum velocity
            double DaMax;           ///< Maximum acceleration
            double DjMax;           ///< Maximum jerk
            bool enabled;           ///< Enabled flag
            tpk::Trajectory Pos;    ///< Current mechanism position
            servoh History[6];      ///< Servo history
        private:
            Axis();
    };
}
#endif

