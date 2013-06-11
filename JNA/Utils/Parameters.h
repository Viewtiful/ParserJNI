/** @file
 *
 * Header for Parameters class
 */

#ifndef __UTILS_PARAMETERS_H
#define __UTILS_PARAMETERS_H

#include <string>

namespace nsUtils
{
    /** Handle the command line parameters and default value for every
     * variables */
    class Parameters
    {
      public:
        typedef enum {
            targetError,
            targetJNA,
            targetJNI
        } TargetType;

        static Parameters& getInstance(void);

        /** Parse the command line.
         *
         * This will put all the command line parameters in the appropriate
         * variables.
         *
         * @retval true All mandatory parameters are present
         * @retval false Some mandatory parameters are missing
         */
        bool parseCommandLine(int argc, char* argv[]);
#ifndef NDEBUG
        int getDebugLevel(void) const;
#endif

        bool isHelpWanted(void) const;
        bool isHelpNeeded(void) const;
        bool isQuiet(void) const;
        bool isRecurse(void) const;
        bool isDryRun(void) const;
        bool isForceSupportClass(void) const;

        const std::string& getHeaderDir(void) const;
        const std::string& getJavaSrcDir(void) const;
        const std::string& getJavaBasePackage(void) const;
        const std::string& getBaseModule(void) const;
        const std::string& getCommHandler(void) const;

        TargetType getTargetType(void) const;

      protected:
        bool mHelpWanted;
        bool mHelpNeeded;
        bool mQuiet;
        bool mRecurse;
        bool mDryRun;
        bool mForceSupportClass;

        std::string* mHeaderDir;
        std::string* mJavaSrcDir;
        std::string* mJavaBasePackage;
        std::string* mBaseModule;
        std::string* mCommHandler;
        std::string* mTargetTypeString;

        int mDebugLevel;

        /** Set all unset values to a default values (except for mandatory
         * ones). */
        void setDefaultValues(void);

        /** Set or reset a string pointer */
        void setString(std::string*& string);

        /** Determine if all mandatory parameters are present */
        bool isMandatorySet(void) const;

      private:
        Parameters();
        virtual ~Parameters();

        static Parameters sInstance;
    };

}

#endif

