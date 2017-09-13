/// \file Planet.cpp
/// \brief Implementation of the Planet class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "Planet.h"

#include <stdexcept>
#include <string>
#include <stdio.h>

#include "Site.h"
#include "SolSysTargets.h"

namespace {
    int Plosc ( char*, double, double*, double*, double*, double*, double*, 
            double*, double* );
}

namespace tpk {
    std::string Planet::mEphemPath;
    Planet::Planet(
        const Site& site,       ///< telscope site
        const names& planet     ///< planet name
    ) : SolarSystemTarget(site) {

    // Append file name to path to get the full file name.
    std::string filename;
        switch (planet) {
            case Mercury:
                filename = mEphemPath + "/series96.mer";
                break;
            case Venus:
                filename = mEphemPath + "/series96.ven";
                break;
            case Mars:
                filename = mEphemPath + "/series96.mar";
                break;
            case Jupiter:
                filename = mEphemPath + "/series96.jup";
                break;
            case Saturn:
                filename = mEphemPath + "/series96.sat";
                break;
            case Uranus:
                filename = mEphemPath + "/series96.ura";
                break;
            case Neptune:
                filename = mEphemPath + "/series96.nep";
                break;
            case Pluto:
                filename = mEphemPath + "/series96.plu";
                break;
        }

    // Get orbital elements from ephemeris.
        double t = site.tai();
        mForm = 1;
        mEpochOfEl = site.tt(t);
        if (Plosc( const_cast<char*>(filename.c_str()), mEpochOfEl, &mOrbInc,
                &mANode, &mPerih, &mAorQ, &mE, &mAorL, &mDailyMot)) {
            throw std::runtime_error("error reading planetary ephemeris");
        }
        update(t);
    }

/// Set path for locating ephemeris files.
    void Planet::ephemPath(
        const std::string& ephemPath     ///< Path to ephemeris files
    ) {
        mEphemPath = ephemPath;
    };
}

/*----------------------------------------------------------------------*/

#include <string.h>
#include <math.h>
#include "slalib.h"

namespace {
    int Plosc ( char *file, double date, double *orbinc, double *anode, 
            double *perih, double *a, double *e, double *el, double *dm )
    /*
    **  - - - - - -
    **   P l o s c
    **  - - - - - -
    **
    **  Compute planetary osculating elements using the planetary ephemerides
    **  of Chapront & Francou (Bureau des Longitudes, Paris).  The coefficients
    **  from which the ephemerides are computed come from a file, one per
    **  planet, supplied by Chapront & Francou.
    **
    **  Given:
    **     file    char[]    name of ephemeris file for the selected planet
    **     date    double    TDB as a Modified Julian Date (JD-2400000.5)
    **
    **  Returned (arguments):
    **     orbinc  double*   inclination (radians)
    **     anode   double*   longitude of the ascending node (radians)
    **     perih   double*   longitude of perihelion (radians)
    **     a       double*   mean distance (AU)
    **     e       double*   eccentricity
    **     el      double*   mean longitude (radians)
    **     dm      double*   daily motion (radians)
    **
    **  Returned (function value):
    **             int     status:
    **                        0 = OK
    **                       -1 = file open or read error
    **                       -2 = wrong sort of file
    **                       -3 = date out of range of ephemeris file
    **                       -4 = transformation to elements failed
    **
    **  Notes:
    **
    **     1  The files supplied by Chapront & Francou contain coefficients
    **        they obtained by frequency analysis of the JPL DE403 planetary
    **        ephemeris.  There is one file per planet.  The naming convention
    **        is (unavoidably) platform-dependent.  A typical scheme is that
    **        file "series.xxx", where xxx is "mer", "ven", "emb", "mar",
    **        "jup", "sat", "ura", "nep", "plu", contains the coefficients
    **        for Mercury, Venus, EMB, Mars, Jupiter, Saturn, Uranus, Neptune
    **        or Pluto.  It is the caller's responsibility to supply the full
    **        name of the file for the planet concerned.
    **
    **     2  The osculating elements are with respect to the dynamical
    **        mean equinox and equator J2000 as implemented by the DE403
    **        ephemeris.
    **
    **     3  The timescale is Barycentric Dynamical Time (TDB).
    **
    **  References:
    **     J.Chapront, 1995, Astron.Astrophys.Suppl.Ser., 109, 181.
    **     J.Chapront, G.Francou, Bureau des Longitudes - 96.12
    **
    **  Called:  slaPv2el
    **
    **  Last revision:   8 December 2001
    **  Copyright P.T.Wallace.  All rights reserved.
    */

#define LINE 81
#define MAXOR 3
#define MAXFQ 250

    {
        int nf[MAXOR];
        double fq[MAXOR][MAXFQ];
        double sec[3][4];
        double ct[3][MAXOR][MAXFQ];
        double st[3][MAXOR][MAXFQ];
        FILE *fp;
        char buf[LINE], cname[13];
        int i, mx, imax, iblock, nb, m, k, iv, ip, max, nw, jform, j;
        double v[3], w[3], ws[3], tjd, tzero, dt, pim, tmax, ca, cb, tdeb,
                    x, fx, wx, f, cf, sf, wt, fw, stw, ctw, wy, pv[6], epoch;



    /* Open the specified ephemeris file. */
        if ( ( fp = fopen ( file, "r" ) ) == NULL ) return -1;

    /* TDB Julian Date. */
        tjd = date + 2400000.5;

    /* Read file parameters. */
        if ( fgets ( buf, LINE, fp ) == NULL ) return -1;
        sscanf ( buf, "%12c %lf %lf %d %d %d",
                    cname, &tzero, &dt, &mx, &imax, &iblock );
        cname[12] = (char) '\0';

    /* Check right sort of file, and look up planet inverse mass. */
        if ( strncmp ( cname, "SERIES96.", 9 ) ) {
            fclose ( fp );
            return -2;
        }
        if ( ! strcmp ( cname+9, "mer" ) ) {
            pim = 6023600.0;
        } else if ( ! strcmp ( cname+9, "ven" ) ) {
            pim = 408523.5;
        } else if ( ! strcmp ( cname+9, "emb" ) ) {
            pim = 328900.5;
        } else if ( ! strcmp ( cname+9, "mar" ) ) {
            pim = 3098710.0;
        } else if ( ! strcmp ( cname+9, "jup" ) ) {
            pim = 1047.355;
        } else if ( ! strcmp ( cname+9, "sat" ) ) {
            pim = 3498.5;
        } else if ( ! strcmp ( cname+9, "ura" ) ) {
            pim = 22869.0;
        } else if ( ! strcmp ( cname+9, "nep" ) ) {
            pim = 19314.0;
        } else if ( ! strcmp ( cname+9, "plu" ) ) {
            pim = 3000000.0;
        } else {
            fclose ( fp );
            return -2;
        }

    /* Validate the date. */
        tmax = tzero + dt * ( (double) iblock );
        if ( tjd < ( tzero - 0.5 ) || tjd > ( tmax + 0.5 ) ) {
            fclose ( fp );
            return -3;
        }
        nb = (int) ( ( tjd - tzero ) / dt ) + 1;
        if ( tjd <= tzero ) {
            nb = 1;
        } else if ( tjd >= tmax ) {
            nb = iblock;
        }

    /* Read frequencies. */
        for ( m = 0; m <= mx; m++ ) {
            if ( fgets ( buf, LINE, fp ) == NULL ) return -1;
            sscanf ( buf, "%d", &nf[m] );
            for ( i = 0; i < nf[m]; i++ ) {
                if ( fgets ( buf, LINE, fp ) == NULL ) return -1;
                sscanf ( buf, "%lf", &fq[m][i] );
            }
        }

    /* Skip separator. */
        if ( fgets ( buf, LINE, fp ) == NULL ) return -1;

    /* Read series. */
        for ( k = 0; k < nb; k++ ) {
            for ( iv = 0; iv < 3; iv++ ) {

            /* Skip block and variable numbers. */
                if ( fgets ( buf, LINE, fp ) == NULL ) return -1;

            /* Read secular terms. */
                for ( i = 0; i <= imax; i += 2 ) {
                    if ( fgets ( buf, LINE, fp ) == NULL ) return -1;
                    sscanf ( buf, "%lf %lf", &sec[iv][i], &sec[iv][i+1] );
                }

            /* Read Poisson terms. */
                for ( m = 0; m <= mx; m++ ) {
                    ip = m % 2;
                    for ( i = 0; i < nf[m]; i++ ) {
                        if ( fgets ( buf, LINE, fp ) == NULL ) return -1;
                        sscanf ( buf, "%lf %lf", &ca, &cb );
                        ct[iv][m][i] = ip ? cb : ca;
                        st[iv][m][i] = ip ? ca : cb;
                    }
                }
            }
        }

    /* Finished with the file. */
        fclose ( fp );

    /* Change variable. */
        tdeb = tzero + dt * (double) ( nb - 1 );
        x = 2.0 * ( tjd - tdeb ) / dt - 1.0;
        fx = x * dt / 2.0;

    /* Compute positions (secular terms). */
        for ( iv = 0; iv < 3; iv++ ) {
            v[iv] = 0.0;
            wx = 1.0;
            max = 2 * imax - 1;
            for ( i = 0; i <= max; i++ ) {
                v[iv] += sec[iv][i] * wx;
                wx *= x;
            }
        }

    /* Compute positions (Poisson terms). */
        wx = 1.0;
        for ( m = 0; m <= mx; m++ ) {
            nw = nf[m];
            for ( iv = 0; iv < 3; iv++ ) {
                ws[iv] = 0.0;
            }
            for ( i = 0; i < nw; i++ ) {
                f = fq[m][i] * fx;
                cf = cos ( f );
                sf = sin ( f );
                for ( iv = 0; iv < 3; iv++ ) {
                    ws[iv] += ct[iv][m][i] * cf + st[iv][m][i] * sf;
                }
            }
            for ( iv = 0; iv < 3; iv++ ) {
                v[iv] += ws[iv] * wx;
            }
            wx *= x;
        }

    /* Compute velocities (secular terms). */
        wt = 2.0 / dt;
        for ( iv = 0; iv < 3; iv++ ) {
            w[iv] = 0.0;
            wx = 1.0;
            max = 2 * imax - 1;
            for ( i = 1; i <= max; i++ ) {
                w[iv] += ( (double) i ) * sec[iv][i] * wx;
                wx *= x;
            }
            w[iv] *= wt;
        }

    /* Compute velocities (Poisson terms). */
        wx = 1.0;
        wy = 0.0;
        for ( m = 0; m <= mx; m++ ) {
            nw = nf[m];
            for ( i = 0; i < nw; i++ ) {
                fw = fq[m][i];
                f = fw * fx;
                cf = cos ( f );
                sf = sin ( f );
                for ( iv = 0; iv < 3; iv++ ) {
                    stw = st[iv][m][i];
                    ctw = ct[iv][m][i];
                    w[iv] += fw * ( stw * cf - ctw * sf ) * wx +
                            ( (double) m ) * wt * ( ctw * cf + stw * sf ) * wy;
                }
            }
            wy = wx;
            wx *= x;
        }

    /* Scale to AU and AU/sec. */
        for ( iv = 0; iv < 3; iv++ ) {
            pv[iv] = v[iv] / 1e10;
            pv[iv+3] = w[iv] / 86400e10;
        }

    /* Transform into osculating elements. */
        slaPv2el ( pv, date, 1.0/pim, 1, &jform, &epoch, orbinc, anode, perih, 
                a, e, el, dm, &j );
        if ( j || jform != 1 ) return -4;

    /* Finished. */
        return 0;

    }
}

