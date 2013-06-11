/** @file
 *
 * Body for the Output class
 */

#ifndef __MINGW32__
#include <sys/ioctl.h>
#endif
#include <iomanip>
#include <cstdio>
#include <fstream>
#include "Output.h"

using std::flush;
using std::setw;
using std::cout;
using std::cerr;
using std::string;

#define OUTPUT nsUtils::Output

OUTPUT OUTPUT::sInstance;

OUTPUT::~Output()
{
    delete mNull;
}

OUTPUT& OUTPUT::getInstance(void)
{
    return sInstance;
}

void OUTPUT::setQuiet(bool quiet)
{
    if (quiet)
        mOut = mNull;
    else
        mOut = &cout;
}

#ifndef NDEBUG
void OUTPUT::setDebugLevel(int level)
{
    mDebugLevel = level;
}
#endif

void OUTPUT::startProgress(int max, const std::string& message)
{
    mProgressMax = max + 1;
    mProgressCurrent = 0;
    mLastProgressMessage = message;
    mDotProgress = message.length() + 5 >= mTermWidth || mDebugLevel != 0;
    mHeaderProgressMessage = message;
    if (mDotProgress)
        OUT << message << "\n[" << flush;
    else
        OUT << "  0% " << message << flush;
}

void OUTPUT::progress(const string& message)
{
    ++mProgressCurrent;
    if (mDotProgress)
        OUT << ". " << message << '\n';
    else
    {
        int percent = mProgressCurrent * 100 / mProgressMax;
        OUT << "\r" << setw(3) << percent << "% " << message;
        for (size_t i(message.length()); 
             i < mLastProgressMessage.length();
             ++i)
            OUT << ' ';
        OUT << flush;
        mLastProgressMessage = message;
    }
}

void OUTPUT::endProgress(bool failed)
{
    if (mDotProgress) {
        OUT << "]\n" << mHeaderProgressMessage;
        if (failed)
            OUT << " FAILED";
        OUT << '\n';
    }
    else
    {
        OUT << '\r';
        if (failed)
            OUT << "FAIL ";
        else
            OUT << "100% ";
        OUT << mHeaderProgressMessage;
        for (size_t i(mHeaderProgressMessage.length()); 
             i < mLastProgressMessage.length();
             ++i)
            OUT << ' ';
        OUT << '\n';
    }
}

std::ostream& OUTPUT::out(void)
{
    return *mOut;
}

std::ostream& OUTPUT::err(void)
{
    return *mErr;
}

std::ostream& OUTPUT::debug(int level)
{
#ifdef NDEBUG
    (void) level;
    return *mNull;
#else
    if (level <= mDebugLevel)
        return *mDebug;
    else
        return *mNull;
#endif
}

OUTPUT::Output()
    : mOut(&cout),
      mErr(&cerr),
      mDebug(&cout)
{
#ifdef __WIN32__
    const char *nullDevice = "NUL:";
#else
    const char *nullDevice = "/dev/null";
#endif

    mNull = new std::ofstream(nullDevice);

    getTermWidth();
}

void OUTPUT::getTermWidth(void)
{
#ifdef TIOCGWINSZ
    struct winsize ws;
    if (ioctl(0, TIOCGWINSZ, &ws))
        mTermWidth = 0;
    else
        mTermWidth = ws.ws_col;
#else
    mTermWidth = 0;
#endif
}

#undef OUTPUT

