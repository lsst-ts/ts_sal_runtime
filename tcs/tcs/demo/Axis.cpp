/// \file Axis.cpp
/// \brief Implementation of the Axis class

// D L Terrett
// Copyright STFC. All rights reserved.

#include "Axis.h"
#include "math.h"
#include "tpk.h"

namespace {
    void servo ( int, double, double, double, double, double, double,
                    double, double, int, double, double, double, double,
                    double, double, double, double, dpk::Axis::servoh*,
                    double*, int* );
}

namespace dpk {

// Constructor
    Axis::Axis(
        double tick,         ///< tick length
        double vcale,        ///< velocity feed-forward calibration
        double gs,           ///< gain: SQRT
        double gp,           ///< gain: proportional
        double gi,           ///< gain: Integrator
        double pi,           ///< integrator window
        double gd,           ///< derivative gain
        double pnear,        ///< position near enough
        double dpmin,        ///< minimum demand
        double dpmax,        ///< maximum demand
        double dvmax,        ///< maximum velocity
        double damax,        ///< maximum acceleration
        double djmax,        ///< maximum jerk
        double pinit         ///< initial position
    ):
        Tick(tick/86400.0), Vcale(vcale), Gs(gs), Gp(gp), Gi(gi), Pi(pi),
        Gd(gd), Pnear(pnear), DpMin(dpmin), DpMax(dpmax), DvMax(dvmax * tick),
        DaMax(damax * tick * tick),  DjMax(djmax * tick * tick * tick),
        enabled(false), Pos(pinit) {

    // Initialise servo.
        double vd; int lim;
        servo( 1, Vcale, Gs, Gp, Gi, Pi, Gd, 0.0, Pnear, 5, DpMin, DpMax, DvMax,
                    DaMax, DjMax, pinit, pinit, 0.0, History, &vd, &lim);
        };

    /// Update axis with new demand position.
    bool Axis::update(
        double t,                        ///< current time
        const tpk::Trajectory& demand    ///< demand trajectory
    ) {
        double vd, va, pd;
        int inpos;
        if (enabled) {

    // Obtain next velocity demand.
            va = demand.sample(t,1) * Tick;
            pd = demand.sample(t,0);
        } else {

    // Ask for zero velocity and the current position.
            va = 0.0;
            pd = Pos.sample(t,0);
        }
        double pt = Pos.sample(t,0);
        double vt = Pos.sample(t,1) * Tick;
        servo( 0, Vcale, Gs, Gp, Gi, Pi, Gd, va, Pnear, 5, DpMin, DpMax, 
                DvMax, DaMax, DjMax, pd, pt, vt , History, &vd, &inpos);

    // Calculate new achieved trajectory.
        Pos = tpk::Trajectory(t, Tick, Pos.sample(t), Pos.sample(t) + vd );

    // Return "in position" status.
        return inpos != 0;
    }
}

namespace {

#define DTINY 1e-10
#define DHUGE 1e10
#define PEMAXI 200.0  /* Maximum position error that will be integrated */

/* sign(A,B) - magnitude of A with sign of B (double) */
#define sign(A,B) ((B)<0.0?-(A):(A))

/* Context */
#define PEOLD  history->peold      /* Position error last time */
#define ACCUMN history->accumn     /* Near integrator */
#define ACCUMF history->accumf     /* Far integrator */
#define V0     history->v0         /* Latest velocity demand */
#define VM1    history->vm1        /* Previous velocity demand */
#define VM2    history->vm2        /* Velocity demand before that */
#define NINPOS history->ninpos     /* Successive "in position" passes */

/// Servo routine: called in order to determine what velocity to demand.
/**
    \note    This routine is not conscious of either the units of position
             or the time per iteration.  It is up to the caller to choose
             units appropriate to the circumstances.  The units are
             defined by the following relationships.

            - vcale: This parameter controls the extent to which the anti-
                     wind-up margin is increased with increasing velocity.
                     It is a fraction which is guaranteed to exceed the
                     velocity feedforward calibration error.  A maximum
                     5% error (for example) corresponds to vcale=0.05.  The
                     anti-wind-up margin, pi, is increased by vcale*va.

            - gs:    If "slewing", a contribution gs*sqrt(pe) is added
                     to the velocity demand (with due regard to signs).  The
                     slewing state is invoked when the proportional law would
                     demand a higher velocity than the sqrt law.

            - gp:    In the non-slew case, a contribution gp*pe is added to
                     the velocity demand.

            - gi:    In the non-slew case, on each iteration the position error
                     pe is added to the integrator accum (internal to this
                     routine).  A contribution gi*accum is then added to the
                     velocity demand.  This behaviour is modified in three ways:
                     (i) the integrator is zeroed when the flag ir is set to 0,
                     (ii) the amount added to the integrator is limited to a
                     numerically safe value PEMAXI, and (iii) if the position
                     error exceeds in magnitude the anti-wind-up window pi, it
                     is zeroed.

            - gd:    In the non-slew case, a contribution equal to gd times the
                     change in position-error since last time through is added
                     to the velocity demand.

            - dvmax: The maximum allowed velocity is in position units per
                     "tick" (i.e. iteration timestep).

            - damax: The maximum allowed acceleration is in position units per
                     tick squared.

            - djmax: The maximum allowed jerk is in position units per tick
                     cubed.

        \note The measures taken to prevent running hard into a position limit
              are (i) the position demand is limited to the specified range,
              and (ii) the maximum allowed velocity demand is progressively
              reduced as the position limits are approached, at a rate
              determined by the specified acceleration limit.

              However, it should be noted that despite these measures it is
              still possible to overrun slightly into the forbidden region,
              and it is up to the application to deal with this condition.
              The recommended strategy is to choose conservative position
              limits, leaving a buffer zone between the most extreme position
              demand that is accepted and the true limit.


        \note The routine requires the achieved position and velocity, in
              essence the encoder reading and the tachometer reading.  Both
              of these should really be for the same instant of time as for
              the other information (the demand position, the demand velocity
              and so on), and in the case of the encoder readings this may
              involve extrapolation.

              The achieved velocity may come from a tachometer, or it could
              come from differencing successive position-encoder readings.

        \note The parameter pnear is the maximum position error that can be
              regarded as "near enough".  The parameter npnear is the number
              of successive iterations on which the test must be passed.  The
              returned argument inpos is set to true if this "near enough for
              long enough" test is passed, otherwise false.

              Note that the criteria may vary depending on what the mechanism
              is being used for at the time.  It may also vary depending on
              geometrical conditions;  in a two-axis "gimbal" mount, for
              example, pnear for the "roll" axis could be relaxed near the pole
              of the mount, where a large roll error corresponds to a small
                error in pointing direction.
*/
    void servo (
        int ir,           ///< new move
        double vcale,     ///< max velocity feedforward calibration error
        double gs,        ///< gain factor for sqrt mode
        double gp,        ///< gain factor for proportional part
        double gi,        ///< gain factor for integral part
        double pi,        ///< anti-wind-up: maximum pe for integration
        double gd,        ///< gain factor for derivative part
        double va,        ///< velocity advise
        double pnear,     ///< "near enough" position-error test
        int npnear,       ///< successive "near enough" passes needed
        double dpmin,     ///< minimum allowed position demand
        double dpmax,     ///< maximum allowed position demand
        double dvmax,     ///< maximum allowed velocity (must be +ve)
        double damax,     ///< maximum allowed acceleration ( " )
        double djmax,     ///< maximum allowed jerk ( " )
        double pd,        ///< desired position
        double pt,        ///< achieved position (i.e. encoder reading)
        double vt,        ///< achieved velocity (i.e. tacho reading)
        dpk::Axis::servoh *history,  ///< context variables
        double *vd,       ///< velocity demand
        int *inpos        ///< TRUE = "near enough for long enough"
    ) {
        double vdp, p, s0, pe, ape, daccum, accum, vi, da0, dam1, dj0,
                    v, dl, vl;

    /* If new move, reset context. */
        if ( ir ) {
            PEOLD = 0.0;
            ACCUMN = 0.0;
            ACCUMF = 0.0;
            VM2 = VM1 = V0 = vt;
            NINPOS = 0;
        }

    /*
    ** -------------------------
    ** LIMIT THE POSITION DEMAND
    ** -------------------------
    */

        if ( pd < dpmin ) {
            pd = dpmin;
        } else if ( pd > dpmax ) {
            pd = dpmax;
        }

    /*
    ** ---------------------------------------
    ** DETERMINE A PRELIMINARY VELOCITY DEMAND
    ** ---------------------------------------
    */

    /* Velocity feedforward. */
        vdp = va;

    /* Determine point at which P and SQRT laws give the same result. */
        if ( fabs ( gp ) < DTINY ) {
            s0 = DHUGE;
        } else {
            p = gs / gp;
            s0 = p * p;
        }

    /* Current position error and absolute value. */
        pe = pd - pt;
        ape = fabs ( pe );

    /* The "near enough for long enough" test. */
        NINPOS = ( ape > pnear ) ? 0 : NINPOS + 1;
        if ( NINPOS < npnear ) {
            *inpos = 0;
        } else {
            NINPOS = npnear;
            *inpos = 1;
        }

    /* Slew case? */
        if ( ape > s0 ) {

        /* Yes: use SQRT law. */

        /* Add the SQRT component to the velocity demand. */
            vdp += sign ( gs * sqrt ( ape ), pe );

        /* Reset both integrators. */
            ACCUMN = ACCUMF = 0.0;

        } else {

        /* No:  use PID law. */

        /* Manage the integrators. */
            daccum = ( ape < PEMAXI ) ? pe : sign ( PEMAXI, pe );
            if ( ape <  ( pi + vdp * vcale ) ) {
                accum = ACCUMN += daccum;
                ACCUMF = 0.0;
            } else {
                accum = ACCUMF += daccum;
                ACCUMN = 0.0;
            }

        /* Add the P component to the velocity demand. */
            vdp += gp * pe;

        /* Add the I component to the velocity demand. */
            vi = gi * accum;
            if ( fabs ( vi ) > dvmax ) vi = sign ( dvmax, vi );
            if ( fabs ( gi ) > DTINY ) accum = vi / gi;
            vdp += vi;

        /* Add the D component to the velocity demand. */
            vdp += gd * ( pe - PEOLD );
        }

    /* Remember current position error. */
        PEOLD = pe;

    /* Push new (provisional) velocity demand onto history stack. */
        VM2 = VM1;
        VM1 = V0;
        V0 = vdp;
    /*
    ** ----------------------------------
    ** LIMIT VELOCITY, ACCELERATION, JERK
    ** ----------------------------------
    */

    /* Apply velocity limit. */
        if ( fabs ( V0 ) > dvmax ) V0 = sign ( dvmax, V0 );

    /* Apply acceleration limit. */
        da0 = V0 - VM1;
        if ( fabs ( da0 ) > damax ) da0 = sign ( damax, da0 );
        V0 = VM1 + da0;

    /* Apply jerk limit. */
        da0 = V0 - VM1;
        dam1 = VM1 - VM2;
        dj0 = da0 - dam1;
        if ( fabs ( dj0 ) > djmax ) dj0 = sign ( djmax, dj0 );
        da0 = dj0 + dam1;
        v = da0 + VM1;
        V0 = v;

    /*
    ** ------------------------------------------------
    ** OVERRIDE THE VELOCITY DEMAND IF CLOSE TO A LIMIT
    ** ------------------------------------------------
    */

    /* Which direction are we trying to head in? */
        if ( v >= 0.0 ) {

        /* We are aiming for the +ve limit;  calculate distance left. */
            dl = dpmax - pt;
            dl = dl > 0.0 ? dl : 0.0;

        /* Current velocity if we will just decelerate without overshooting. */
            vl = sqrt ( 2.0 * damax * dl );

        /* If close, limit velocity feedforward. */
            if ( v > vl ) v = vl;

        } else {

        /* Same for -ve case. */
            dl = pt - dpmin;
            dl = dl > 0.0 ? dl : 0.0;
            vl = - sqrt ( 2.0 * damax * dl );
            if ( v < vl ) v = vl;
        }
    /* Return the final velocity demand. */
        *vd = v;
    }
}

