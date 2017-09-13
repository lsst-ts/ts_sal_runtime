/// \file PointCat.h
/// \brief Declaration of the pointing catalogue class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkPOINTCAT_H
#define tpkPOINTCAT_H

#include <ios>
#include <stdexcept>
#include <string>
#include <vector>

namespace tpk {
    class Target;
    class Site;

/// Catalogue of pointing calibration stars
/**
    A PointCat is initialized by reading a file of star positions
    (in the format used by TPOINT).  Each star is given an index number
    that can be used to retrieve a star's catalog position and
    approximate current observed Az,El.

    Each star also has a flag (an int) associated with it and this
    can be used by the application fo any purpose, for example to
    keep track of which stars have been observed; the values
    assigned to the flag are not used within the class.
*/
    class PointCat {
        public:
            PointCat(
                const Site& site,
                const std::string& filename
            ) throw(std::runtime_error, std::ios::failure);
            ~PointCat();

        /// Get the size of the catalog
        /**
            Returns the number of stars in the catalog.

            \returns the number of entries.
        */
            size_t size() throw() {
                return mCatalog.size();
            }
            void entry(
                const size_t& index,
                Target*& target,
                double& az,
                double& el,
                int& flag
            ) throw(std::out_of_range);
            void flag(
                const size_t& index,
                const int& flag
            )throw(std::out_of_range) ;
            void flag(
                const int& flag
            )throw();
            int flag(
                const size_t& index
            ) throw(std::out_of_range);
        protected:
            const Site& mSite;             ///< telescope site
        /// Catalogue entry
            struct record {
                int flag;                  ///< user flag
                Target* target;            ///< target
                std::string star;          ///< catalogue record
            };
            std::vector<record> mCatalog; ///< catalogue
        private:
            PointCat();
            PointCat(const PointCat&);
            PointCat& operator=(const PointCat&);
    };
}
#endif

