/// \file TcsLib.h
/// \brief Definition of  the TcsLib class

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkTCSLIB_H
#define tpkTCSLIB_H

#include <stdexcept>

#include "Coordinates.h"

namespace tpk {

    namespace tcspk {
        #include "tcs.h"
    }

/// A class that wraps the TcsLib C functions.
/**
    The TcsLib class defines a static class method for each C function in
    the TcsLib library. They map arguments from C++ types to C types as
    necessary and convert error returns into exceptions.

    A number of inline functions for manipulating various kernel data
    structure are also defined.
*/
    class TcsLib {
        public:
            typedef tcspk::MTYPE mtype;
            typedef tcspk::FRAMETYPE frametype;
            typedef tcspk::ROTLOC rotloc;

        // Class constants
            static const double pi;
            static const double pi2;
            static const double d2r;
            static const double r2d;
            static const double r2as;
            static const double as2r;
            static const double d90;
            static const double strpd;
            static const double c;
            static const double au2km;
            static const double utst;

        /// \internal
        /// Copy 3 element vector.
            inline static void copyVector(
                const double src[3],    ///< source vector
                double dest[3]          ///< destination vector
            ) throw () {
                for ( int i = 0; i < 3; i++ ) dest[i] = src[i];
            }

        /// \internal
        /// Copy 3x3 matrix.
            inline static void copyMatrix(
                const double src[3][3],    ///< source matrix
                double dest[3][3]          ///< destination matrix
            ) throw () {
                for ( int i = 0; i < 3; i++ ) {
                    for ( int j = 0; j < 3; j++ ) dest[i][j] = src[i][j];
                }
            }

        /// \internal
        /// Copy amprms array.
            inline static void copyAmprms(
                const double src[21],    ///< source amprms array
                double dest[21]          ///< destination amprms array
            ) throw () {
                for ( int i = 0; i < 21; i++ ) dest[i] = src[i];
            }

        /// \internal
        /// Copy aoprms array
            inline static void copyAoprms(
                const double src[14],    ///< source aoprms array
                double dest[14]          ///< destination aoprms array
            ) throw () {
                for ( int i = 0; i < 14; i++ ) dest[i] = src[i];
            }

        // TcsPk functions.
            static vector bs(
                const vector& tel,
                const rotloc& rotl,
                const double& rma,
                const double& roll,
                const double& pitch,
                const double& ga,
                const double& gb,
                const focalplane& xy
            ) throw() ;
            static void casspa(
                const rotloc& rotl,
                const double& rma,
                const double& roll,
                const double& pitch,
                double& spa,
                double& cpa
            ) throw ();
            static vector enc2aim(
                const double& roll,
                const double& pitch,
                const vector& bs,
                const double& ia,
                const double& ib,
                const double& np
            ) throw();
            static void init2(
                const double& tlongm,
                const double& tlatm,
                const double& xpmr,
                const double& ypmr,
                const double& hm,
                const double& gim1z,
                const double& gim2y,
                const double& gim3x,
                double ae2nm[3][3],
                double& tlong,
                double& tlat,
                double& uau,
                double& vau,
                double& ukm,
                double& vkm,
                double& diurab
            ) throw (std::runtime_error);
            static void init2(
                const double& tlongm,
                const double& tlatm,
                const double& xpmr,
                const double& ypmr,
                const double& hm,
                const mtype& mtype,
                double ae2nm[3][3],
                double& tlong,
                double& tlat,
                double& uau,
                double& vau,
                double& ukm,
                double& vkm,
                double& diurab
            ) throw (std::runtime_error);
            static void init2(
                const double& tlongm,
                const double& tlatm,
                const double& xpmr,
                const double& ypmr,
                const double& hm,
                const mtype& mtype,
                const double& gim1z,
                const double& gim2y,
                const double& gim3x,
                double ae2nm[3][3],
                double& tlong,
                double& tlat,
                double& uau,
                double& vau,
                double& ukm,
                double& vkm,
                double& diurab
            ) throw (std::runtime_error);
            static void slow(
                const double& tai,
                const double& delut,
                const double& delat,
                const double& ttmtai,
                const double& temp,
                const double& press,
                const double& humid,
                const double& wavelr,
                const double& elong,
                double& t0,
                double& st0,
                double& tt0,
                double& ttj,
                double amprms[21],
                double& refa,
                double& refb
            ) throw();

            static focalplane xy2xe(
                const focalplane& xy,
                const rotloc& rotl,
                const double& rma,
                const double& roll,
                const double& pitch
            ) throw ();
            static focalplane xe2xy(
                const focalplane& xieta,
                const rotloc& rotl,
                const double& rma,
                const double& roll,
                const double& pitch
            ) throw ();

        // Pointing model functions
            static void pup(
                int maxtrm,
                const int model[],
                const double* coeffv,
                int nterml,
                int ntermx,
                int nterms,
                const char coeffn[][9],
                const char coform[][9],
                mtype mtype,
                const double ae2nm[3][3],
                double roll,
                double pitch,
                bool bp,
                const double aux[3],
                double lat,
                double& ia,
                double& ib,
                double& np,
                vector& tel,
                double ae2mt[3][3]
            ) throw(std::runtime_error);
            static void intpm(
                const std::string& filename,
                int maxtrm,
                int ntroom,
                int model[],
                int& nterml,
                int& ntermx,
                int& nterms,
                char coeffn[][9],
                char coform[][9],
                double coeffv[]
            ) throw(std::runtime_error);
            static void minit(
                int maxtrm,
                int ntroom,
                int model[],
                int& nterml,
                int& ntermx,
                int& nterms,
                char coeffn[][9]
            ) throw ();
            static void addtrm(
                int maxtrm,
                int ntroom,
                const std::string& name,
                double value,
                int& nterms,
                char coeffn[][9],
                char coform[][9],
                int model[],
                double coeffv[]
            ) throw (std::runtime_error);
            static void sterm(
                const std::string& name,
                double value,
                int maxtrm,
                int model[],
                char coeffn[][9],
                double coeffv[]
            ) throw (std::runtime_error);
            static void iterm(
                int iterm,
                int maxtrm,
                const int model[],
                const char coeffn[][9],
                const double coeffv[],
                std::string& name,
                double& value
            ) throw (std::runtime_error);
    };
}
#endif

