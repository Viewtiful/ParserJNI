/** @file
 *
 * Header for the Output class
 */

#ifndef __UTILS_OUTPUT_H
#define __UTILS_OUTPUT_H

#include <iostream>

/** Output something on stdout, except if the quiet flag was passed as an
 * argument. */
#define OUT nsUtils::Output::getInstance().out()
/** Output something on stderr. */
#define ERR nsUtils::Output::getInstance().err()
/** Output a debug string. This is removed in release build. */
#define DEBUG(x) nsUtils::Output::getInstance().debug(x)

namespace nsUtils
{
    /** Manage output of text according to command line parameters. */
    class Output
    {
      public:
        virtual ~Output();

        /** Return the only instance of Output */
        static Output& getInstance(void);

        /** Set the quiet flag */
        void setQuiet(bool quiet);
#ifndef NDEBUG
        /** Set the debug level */
        void setDebugLevel(int level);
#endif

        void startProgress(int max, const std::string& message);
        void progress(const std::string& message);
        void endProgress(bool failed = false);

        /** Return the stream to use for standard output */
        std::ostream& out(void);
        /** Return the stream to use for error output */
        std::ostream& err(void);
        /** Return the stream to use for debug output.
         *
         * In release build, this will return a /dev/null stream. */
        std::ostream& debug(int level);

      protected:
        std::ostream* mOut;
        std::ostream* mErr;
        std::ostream* mDebug;

        std::ostream* mNull;

        int mProgressMax;
        int mProgressCurrent;
        std::string mLastProgressMessage;
        std::string mHeaderProgressMessage;
        bool mDotProgress;

        int mDebugLevel;

        size_t mTermWidth;
        
        void getTermWidth(void);

      private:
        Output();

        static Output sInstance;
    };
}

#endif

