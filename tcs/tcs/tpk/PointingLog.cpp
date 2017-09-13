/// \file PointingLog.cpp
/// \brief Implementation of the pointing log class.

// D L Terrett
// Copyright CCLRC. All rights reserved.

#include "PointingLog.h"

#include <fstream>
#include <ios>
#include <string>
#include "slalib.h"

#include "ICRefSys.h"
#include "MountVt.h"
#include "Site.h"
#include "TcsLib.h"
#include "TcsMutex.h"

using std::string;
using std::ofstream;
using std::endl;

namespace tpk {
/**
    Opens a file for pointing logging and writes the header.

    The telescope name argument is just a text string that is written
    to the log file.

    \exception std::runtime_error
    \exception std::ios::failure
*/
    PointingLog::PointingLog(
        const MountVt& mount,            ///< mount virtual telescope
        const std::string& filename,     ///< name of file for logging
        const std::string& telescope     ///< telescope name
    ) throw(std::runtime_error, std::ios::failure) :
            PointingObs(mount),
            mLogStream( filename.c_str(), std::ios::app )
    {

    // Check the the logging file has been opened sucessfully.
        if ( ! mLogStream ) {
            throw std::runtime_error("Unable to open pointing log file");
        }
        mLogStream.exceptions(std::ios::badbit);

    // Set number formating.
        mLogStream.precision(14);
        mLogStream.setf(std::ios::showpoint);

    // Get the time as a calender date and time.
        int y, m, d, j; double f;
        slaDjcl( mTaiStart - mDelat, &y, &m, &d, &f, &j);
        int hmsf[4]; char sign;
        slaDd2tf( 0, f, &sign, hmsf);

    // Write log file header.
        mLogStream << "VERSION 1.1" << endl;
        mLogStream << "TELNAME " << telescope << endl;
        char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
                "Aug", "Sep", "Oct", "Nov", "Dec"};
        mLogStream << "DATE " << y << " " << months[m-1] << " " << d << endl;
        mLogStream << "UTC " << hmsf[0] << " " << hmsf[1] << " " <<
                hmsf[2] << endl;
        mLogStream << "MTYPE " << mMtype << endl;
        if (mMtype == tcspk::GIMBAL ) {
            mLogStream << "GIM1Z " << mGim1z/TcsLib::d2r << endl;
            mLogStream << "GIM2Y " << mGim2y/TcsLib::d2r << endl;
            mLogStream << "GIM3X " << mGim3x/TcsLib::d2r << endl;
        }
        mLogStream << "TLONGM " << mElongm/TcsLib::d2r << endl;
        mLogStream << "TLATM " << mLatm/TcsLib::d2r << endl;
        mLogStream << "HEIGHT " << mHm << endl;
        mLogStream << "XPM " << mXpm/TcsLib::as2r << endl;
        mLogStream << "YPM " << mYpm/TcsLib::as2r << endl;
        mLogStream << "TTMTAI " << mTtmtai*86400.0 << endl;
        mLogStream << "DJMLS " << 999999.0 << endl;
        mLogStream << "DELAT " << mDelat*86400.0 << endl;
        mLogStream << "DELUT " << mDelut*86400.0 << endl;
    }

/**
    Writes the log file end record.

    \exception std::ios::failure
*/
    PointingLog::~PointingLog() {
        try {
                mLogStream << "END" << endl;
        }
        catch (...) {};
    }

/// Log pointing observation
/**
    Logs a pointing observation to the current pointing log file.

    If the field identifier is the empty string an identifier is
    constructed by formatting the RA and Dec of the calibration
    star.

    The position of the pointing calibration star is assumed to be the
    position of the target that the mount virtual telescope is tracking.

    \exception std::ios::failure
*/
    void PointingLog::log(
        std::string id    ///< Field identifier
    ) throw(std::ios::failure)
    {
    // If data isn't available call mark() to capture it.
        if ( ! mMarked ) mark();

    // If the field id is empty construct one from the RA & Dec
        if ( id.empty() ) {
            int hmsf[4], dmsf[4];
            char sign, str[28];
            slaDr2tf( 4, mRa, &sign, hmsf);
            slaDr2af( 3, mDec, &sign, dmsf);
            sprintf(str, "%02d %02d %02d.%04d %c%02d %02d %02d.%03d", hmsf[0],
                    hmsf[1], hmsf[2], hmsf[3], sign, dmsf[0], dmsf[1], dmsf[2],
                    dmsf[3] );
            id = str;
        }

    // Write observation to log file.
        mLogStream << "OBS " << id << endl;
        mLogStream << floor(mTai) << endl;
        mLogStream << (mTai - floor(mTai)) * 86400.0 << endl;
        mLogStream << mRa << endl << mDec << endl;
        mLogStream << mWavel << endl;
        mLogStream << mRoll << endl << mPitch << endl;
        mLogStream << mCasspa << endl;
        mLogStream << mXr << endl << mYr << endl;
        mLogStream << mFl << endl;
        mLogStream << mTemp << endl << mPress << endl << mHumid << endl << mTlr 
                << endl;
        mLogStream << mRcorr << endl;

    // Add auxilairy readings.
        logAuxiliary( mAux );

    // Flush observation to file so it can't be lost.
        mLogStream.flush();

    // Clear the marked flag.
        mMarked = false;
    }

/// Log pointing observation
/**
    Logs a pointing observation to the current pointing log file.

    If the field identifier is the empty string an identifier is
    constructed by formatting the RA and Dec of the calibration
    star.

    \exception std::ios::failure
*/
    void PointingLog::log(
        double ra,      ///< ICRS right ascension of the pointing star (radians)
        double dec,     ///< ICRS declination of the pointing star (radians)
        std::string id  ///< field identifier
    ) throw(std::ios::failure)
    {

    // Overwrite the stored RA & dec,
        mRa = ra;
        mDec = dec;

    // Log the observation.
        log(id);
    }

/// Log comment
/**
    Adds a comment to the current pointing log file.

    \exception std::ios::failure
*/
    void PointingLog::comment(
        const std::string& str       ///< comment string
        ) throw(std::ios::failure)
    {

    // Write observation to log file.
        mLogStream << "! " << str << endl;
        mLogStream.flush();
    }
}
