/// \file PointingModel.cpp
/// \brief Implementation of the pointing model class

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "PointingModel.h"

#include <stdexcept>
#include <string>
#include <vector>

#include "TcsLib.h"

using std::string;
using std::vector;

namespace tpk {

/**
    Creates a pointing model with no terms.
*/
    PointingModel::PointingModel() throw()
    {
        TcsLib::minit(maxtrm, ntroom, mModel, mNterml, mNtermx, mNterms, 
                mCoeffn);
    }
/**
    Creates a pointing model with terms defined in a file.
*/
    PointingModel::PointingModel(
        const std::string& filename  ///< model file name
    ) throw (std::runtime_error) {
        TcsLib::intpm( filename, maxtrm, ntroom, mModel, mNterml, mNtermx, 
                mNterms, mCoeffn, mCoform, mCoeffv);
    }

/// Set term
/**
    Sets the value of an individual term in the pointing model.
*/
    void PointingModel::setTerm(
        const std::string& name,      /// name of term
        const double& value           /// new value
    ) throw (std::runtime_error) {
        TcsLib::sterm( name, value, maxtrm, mModel, mCoeffn, mCoeffv);
    }

/// Add term
/**
    Adds a new term to the pointing model.
*/
    void PointingModel::addTerm(
        const std::string& name,      /// name of term
        const double& value           /// value
    ) throw (std::runtime_error) {
        TcsLib::addtrm( maxtrm, ntroom, name, value, mNterms, mCoeffn, 
                mCoform, mModel, mCoeffv);
    }

/// GetTerm
/**
    Gets the value of a term in the pointing model.

    \returns value of term (radians)
*/
    double PointingModel::getTerm(
        const std::string& name      /// name of term
    ) const throw (std::runtime_error) {
        double value;
        for ( int i = 1; ; i++ ) {
            string term;
            TcsLib::iterm( i, maxtrm, mModel, mCoeffn, mCoeffv, term, value);
            if ( term == name ) break;
        }
        return value;
    }

/// List terms
/**
    Lists all the names of the terms in the pointing model

    \returns list of model terms
*/
    std::vector<std::string> PointingModel::listTerms() const {
        std::vector<string> list;
        for ( int i = 1; ; i++ ){
            string term;
            try {
                double value;
                TcsLib::iterm( i, maxtrm, mModel, mCoeffn, mCoeffv, term, value);
            } catch (std::runtime_error) {
                break;
            }
            list.insert(list.end(), term);
        }
        return list;
    }

/// summerize
/**
    Summerize pointing model.
*/
    void PointingModel::summerize(
        const TcsLib::mtype& mtype, ///< mount type
        const double ae2nm[3][3],   ///< Az,El to nominal mount rotation matrix
        const double& roll,         ///< mount roll (radians)
        const double& pitch,        ///< mount pitch (radians)
        const bool& bp,             ///< beyond pole flag
        const double aux[3],        ///< auxiliary readings
        const double& lat,          ///< telescope true latitude (radians)
        double& ia,                 ///< roll zero point (radians)
        double& ib,                 ///< pitch zero point (radians)
        double& np,                 ///< axis non-perpendicularity (radians)
        vector& tel,                ///< telescope vector
        double ae2mt[3][3]          ///< Az,El to mount rotation matrix
    ) const throw(std::runtime_error) {
        TcsLib::pup( maxtrm, mModel, mCoeffv, mNterml, mNtermx, mNterms,
                mCoeffn, mCoform, mtype, ae2nm, roll, pitch, bp,
                aux, lat, ia, ib, np, tel, ae2mt);
    }
}

