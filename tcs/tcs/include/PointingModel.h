/// \file PointingModel.h
/// \brief Defininition of the pointing model class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkPOINTINGMODEL_H
#define tpkPOINTINGMODEL_H

#include <stdexcept>
#include <string>
#include <vector>
#include <memory>

#include "TcsLib.h"

namespace tpk {

/// Telescope pointing model
/**
    A PointingModel summerizes the pointing model at a given roll and pitch
    as index errors in the two axes, the non-perpendicularity, a telescope
    vector and the orientation of the mount.

    \attention All classes derived from PointingModel must implement the clone
               method.
*/
    class PointingModel {
        public:
        
        /// PointingModel auto_ptr
            typedef std::auto_ptr<PointingModel> Ptr;
        /// Const PointingModel auto_ptr
            typedef std::auto_ptr<const PointingModel> ConstPtr;
            PointingModel() throw();
            PointingModel(
                const std::string &filename
            ) throw(std::runtime_error);
            virtual ~PointingModel() {}

    /// Virtual copy constructor
            virtual PointingModel* clone() const {
                return new PointingModel(*this);
            }

            virtual void summerize(
                const TcsLib::mtype& mtype,
                const double ae2nm[3][3],
                const double& roll,
                const double& pitch,
                const bool& bp,
                const double aux[3],
                const double& lat,
                double& ia,
                double& ib,
                double& np,
                vector& tel,
                double ae2mt[3][3]
            ) const throw(std::runtime_error);
            virtual void setTerm(
                const std::string& name,
                const double& value
            ) throw (std::runtime_error);
            virtual void addTerm(
                const std::string& name,
                const double& value
            ) throw (std::runtime_error);
            virtual double getTerm(
                const std::string& name
            ) const throw (std::runtime_error);
            virtual std::vector<std::string> listTerms() const;
        protected:
            static const int maxtrm = 30;   ///< maximum number of terms in 
                                            ///  pointing model
            static const int ntroom = 100;  ///< total number of terms known to 
                                            ///  TPOINT
            int mModel[maxtrm];             ///< term numbers for current model
            double mCoeffv[maxtrm];         ///< coefficient value
            int mNterml;                    ///< number of local terms
            int mNtermx;                    ///< number of terms implemented 
                                            ///  explicitly
            int mNterms;                    ///< number of terms available 
                                            ///  currently
            char mCoeffn[ntroom][9];        ///< coefficient names
            char mCoform[ntroom][9];        ///< format of generic term
    };
}
#endif

