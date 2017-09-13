/// \file PointingLog.h
/// \brief Defintion of the pointing log class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#ifndef tpkPOINTINGLOG_H
#define tpkPOINTINGLOG_H

#include <fstream>
#include <stdexcept>
#include <string>

#include "PointingObs.h"

namespace tpk {
    class MountVt;

/// Pointing observation log file
/**
    A PointingLog object creates a file of pointing obeservations in the
    format recognised by the "ptconv" utility program that generates file
    suitable for analysis with TPOINT.

    Copying PointingLog objects is not permitted.
*/
    class PointingLog : public PointingObs {
        public:
            PointingLog(
                const MountVt& mountvt,
                const std::string& filename,
                const std::string& telescope
                ) throw(std::runtime_error, std::ios::failure);
            virtual ~PointingLog();
            void log(
                std::string id = ""
            ) throw(std::ios::failure);
            void log(
                double ra,
                double dec,
                std::string id = ""
            ) throw(std::ios::failure);
            void comment(
                const std::string& str
            ) throw(std::ios::failure);
        protected:

        /// Log auxiliary readings
        /*
            The log method calls logAuxiliary to add auxiliary readings to the
            log file. The default implementation of this does nothing and
            to log auxiliary readings a derived class must be written which
            re-implements logAuxiliary.

            Readings may be added by writing up to 3 additional records each 
            containing one double to the LogStream.
        */
            virtual void logAuxiliary(
                double aux[3]         ///< array of auxiliary readings
            ) {}
            std::ofstream mLogStream; ///< log file output stream
        private:
        // No default constructor, copy constructor or assignment operator
            PointingLog();
            PointingLog(const PointingLog&);
            PointingLog& operator=(const PointingLog&);
    };
}
#endif

