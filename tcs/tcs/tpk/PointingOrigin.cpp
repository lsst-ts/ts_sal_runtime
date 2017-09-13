/// \file PointingOrigin.cpp
/// \brief Implementation of the pointing origin class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "PointingOrigin.h"

#include "Transform.h"

namespace tpk {
/**
    Creates a pointing origin with no offsets, the identity transformation
    and zero base.
*/
    PointingOrigin::PointingOrigin() :
        mBaseXp(0.0),
        mBaseYp(0.0),
        mNumOffsets(0),
        mTransf(0) {}

/// Constructor for a pointing origin with the identity transformation.
/**
    \exception std::domain_error
*/
    PointingOrigin::PointingOrigin(
        const double& xp,       ///< first coordinate
        const double& yp,       ///< second coordinate
        const int& numOffsets   ///< number of offsets
    ) throw(std::domain_error):
        mBaseXp(xp),
        mBaseYp(yp),
        mNumOffsets(numOffsets)
    {
        mTransf = new Transform;

        if ( numOffsets > 0 ) {
            mXoffsets = new double[numOffsets];
            mYoffsets = new double[numOffsets];
            for ( int i = 0; i < mNumOffsets; i++ ) {
                mXoffsets[i] = 0.0;
                mYoffsets[i] = 0.0;
            }
        } else if ( numOffsets < 0 ) {
            throw std::domain_error("Number of offsets less than zero");
        }
    }

/// Constructor for a pointing origin with a transformation
/**
    \exception std::domain_error
*/

    PointingOrigin::PointingOrigin(
        const double& xp,          ///< first coordinate
        const double& yp,          ///< second coordinate
        const Transform& transf,   ///< transformation
        const int &numOffsets      ///< number of offsets
    ) throw(std::domain_error):
        mBaseXp(xp),
        mBaseYp(yp),
        mNumOffsets(numOffsets)
    {
        mTransf = transf.clone();

        if ( numOffsets > 0 ) {
            mXoffsets = new double[numOffsets];
            mYoffsets = new double[numOffsets];
            for ( int i = 0; i < numOffsets; i++ ) {
                mXoffsets[i] = 0.0;
                mYoffsets[i] = 0.0;
            }
        } else if ( numOffsets < 0 ) {
            throw std::domain_error("Number of offsets less than zero");
        }
    }

/// Copy constructor.
    PointingOrigin::PointingOrigin(
        const PointingOrigin& po      ///< pointing origin
    ) throw () :
        mBaseXp(po.mBaseXp),
        mBaseYp(po.mBaseYp),
        mNumOffsets(po.mNumOffsets)
    {
        mTransf = po.mTransf->clone();
        if ( mNumOffsets ) {
            mXoffsets = new double[mNumOffsets];
            mYoffsets = new double[mNumOffsets];
            for ( int i = 0; i < mNumOffsets; i++ ) {
                mXoffsets[i] = po.mXoffsets[i];
                mYoffsets[i] = po.mYoffsets[i];
            }
        } else {
            mYoffsets = 0;
            mXoffsets = 0;
        }
    }

/// Assignment operator
    PointingOrigin& PointingOrigin::operator=(
        const PointingOrigin& rhs     ///< pointing origin
    ) throw ()
    {
        if ( &rhs != this ) {
            if ( mNumOffsets ) {
                delete[] mXoffsets;
                delete[] mYoffsets;
            }
            mBaseXp = rhs.mBaseXp;
            mBaseYp = rhs.mBaseYp;
            mNumOffsets = rhs.mNumOffsets;
            mTransf = rhs.mTransf->clone();
            if ( mNumOffsets ) {
                mXoffsets = new double[mNumOffsets];
                mYoffsets = new double[mNumOffsets];
                for ( int i = 0; i < mNumOffsets; i++ ) {
                    mXoffsets[i] = rhs.mXoffsets[i];
                    mYoffsets[i] = rhs.mYoffsets[i];
                }
            } else {
                mYoffsets = 0;
                mXoffsets = 0;
            }
        }
        return *this;
    }

/// Destructor
    PointingOrigin::~PointingOrigin()
    {
        delete mTransf;
        if ( mNumOffsets ) {
            delete[] mXoffsets;
            delete[] mYoffsets;
        }
    }

/// Set the base position
    void PointingOrigin::setBase(
        const double& xp,  ///< first coordinate
        const double& yp   ///< second coordinate
    ) {
        mBaseXp = xp;
        mBaseYp = yp;
    }

/// Get the base position
/**
    \returns the base position.
*/
    focalplane PointingOrigin::base(
    ) const {
        return focalplane(mBaseXp,mBaseYp);
    }

/// Set offset
/**
    Either sets the offset specified by the index or sets all offsets to the
    same values if the index is less than zero.

    \exception std::out_of_range
*/
    void PointingOrigin::setOffset(
        const int& n,      ///< offset index
        const double& xp,  ///< first coordinate
        const double& yp   ///< second coordinate
    ) throw (std::out_of_range) {
        if ( n >= mNumOffsets ) {
            throw std::out_of_range( "Offset index out of range" );
        } else if ( n < 0 ) {
            for ( int i = 0; i < mNumOffsets; i++ ) {
                mXoffsets[i] = xp;
                mYoffsets[i] = yp;
            }
        } else {
            mXoffsets[n] = xp;
            mYoffsets[n] = yp;
        }
    }

/// Get offset
/**
    \returns offset

    \exception std::out_of_range
*/
    focalplane PointingOrigin::offset(
        const int& n      ///< offset index
    ) const throw (std::out_of_range) {
        if ( n >= mNumOffsets || n < 0) {
            throw std::out_of_range( "Offset index out of range" );
        } else {
            return focalplane(mXoffsets[n],mYoffsets[n]);
        }
    }

/// Absorb offset.
/**
    Absorbs either the specified offset all offsets into the base position
    so the the offsets are zero and the net position is unchanged.

    \exception std::out_of_range
*/
    void PointingOrigin::absorbOffset(
        const int& n       ///< offset index
    ) throw (std::out_of_range) {
        if ( n >= mNumOffsets ) {
            throw std::out_of_range( "Offset index out of range" );
        } else if ( n < 0 ) {
            for ( int i = 0; i < mNumOffsets; i++ ) {
                mBaseXp += mXoffsets[i];
                mBaseYp += mYoffsets[i];
                mXoffsets[i] = 0.0;
                mYoffsets[i] = 0.0;
            }
        } else {
            mBaseXp += mXoffsets[n];
            mBaseYp += mYoffsets[n];
            mXoffsets[n] = 0.0;
            mYoffsets[n] = 0.0;
        }
    }

/// Get X,Y
/**
    Returns the net pointing origin position in focal plane coordinates.

    \returns net position
*/
    focalplane PointingOrigin::xy(
        const double& t    ///< TAI (MJD)
    ) const {
        double x = mBaseXp;
        double y = mBaseYp;
        for ( int i = 0; i < mNumOffsets; i++ ) {
            x+= mXoffsets[i];
            y+= mYoffsets[i];
        }
        if ( mTransf ) {
            return mTransf->forward(instrcoord(x, y));
        } else {
            return focalplane(x,y);
        }
    }
}

