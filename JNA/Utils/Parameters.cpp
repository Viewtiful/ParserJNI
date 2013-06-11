/** @file
 *
 * Body for the Parameters class
 */

#define __USE_POSIX2
#include <unistd.h>
#include <assert.h>
#include <cstdlib>
#include <iostream>
#include "Output.h"
#include "Parameters.h"

#define PARAMETERS nsUtils::Parameters

using std::cout;
using std::string;

PARAMETERS PARAMETERS::sInstance;

PARAMETERS& PARAMETERS::getInstance(void)
{ return PARAMETERS::sInstance; }

bool PARAMETERS::parseCommandLine(int argc, char* argv[])
{
    assert(argc >= 0);
    assert(argv);

    int opt;
#ifdef NDEBUG
    const char* optString = "hqH:rj:p:m:M:Dc:L:";
#else
    const char* optString = "hqH:rj:p:m:M:Dd:c:L:";
#endif
    while ((opt = getopt(argc, argv, optString)) != -1)
        switch (opt)
        {
          case 'h':
            mHelpWanted = true;
            break;

          case 'q':
            mQuiet = true;
            break;

          case 'H':
            setString(mHeaderDir);
            break;

          case 'r':
            mRecurse = true;
            break;

          case 'j':
            setString(mJavaSrcDir);
            break;

          case 'p':
            setString(mJavaBasePackage);
            break;

          case 'm':
            setString(mBaseModule);
            mForceSupportClass = false;
            break;

          case 'M':
            setString(mBaseModule);
            mForceSupportClass = true;
            break;

          case 'c':
            setString(mCommHandler);
            break;

          case 'D':
            mDryRun = true;
            break;

          case 'L':
            setString(mTargetTypeString);
            break;

#ifndef NDEBUG
          case 'd':
            mDebugLevel = atoi(optarg);
            break;
#endif

          default:
            mHelpNeeded = true;
        }
    setDefaultValues();

    if (isMandatorySet())
        return true;
    
    mHelpNeeded = true;
    return false;
}

#ifndef NDEBUG
int PARAMETERS::getDebugLevel(void) const
{ return mDebugLevel; }
#endif

bool PARAMETERS::isHelpWanted(void) const
{ return mHelpWanted; }

bool PARAMETERS::isHelpNeeded(void) const
{ return mHelpWanted || mHelpNeeded; }

bool PARAMETERS::isQuiet(void) const
{ return mQuiet; }

bool PARAMETERS::isRecurse(void) const
{ return mRecurse; }

bool PARAMETERS::isDryRun(void) const
{ return mDryRun; }

bool PARAMETERS::isForceSupportClass(void) const
{ return mForceSupportClass; }

const string& PARAMETERS::getHeaderDir(void) const
{
    assert(mHeaderDir);
    return *mHeaderDir;
}

const string& PARAMETERS::getJavaSrcDir(void) const
{
    assert(mJavaSrcDir);
    return *mJavaSrcDir;
}

const string& PARAMETERS::getJavaBasePackage(void) const
{
    assert(mJavaBasePackage);
    return *mJavaBasePackage;
}

const string& PARAMETERS::getBaseModule(void) const
{
    assert(mBaseModule);
    return *mBaseModule;
}

const string& PARAMETERS::getCommHandler(void) const
{
    assert(mCommHandler);
    return *mCommHandler;
}

PARAMETERS::TargetType PARAMETERS::getTargetType(void) const {
    if ((*mTargetTypeString) == "JNA") {
        return targetJNA;
    } else if ((*mTargetTypeString) == "JNI") {
        return targetJNI;
    } else {
        return targetError;
    }
}

void PARAMETERS::setDefaultValues(void)
{
    if (!mJavaBasePackage)
        mJavaBasePackage = new string("");
}

void PARAMETERS::setString(string*& str)
{

    if (str)
        delete str;
    //optarg contient le parametre de l'argument
    str = new string(optarg);
}

bool PARAMETERS::isMandatorySet(void) const
{
    return mHeaderDir != NULL &&
           mJavaSrcDir != NULL &&
           mJavaBasePackage != NULL &&
           mBaseModule != NULL &&
           getTargetType() != targetError;
}

PARAMETERS::Parameters(void)
    : mHelpWanted(false),
      mHelpNeeded(false),
      mQuiet(false),
      mRecurse(false),
      mDryRun(false),
      mForceSupportClass(false),
      mHeaderDir(NULL),
      mJavaSrcDir(NULL),
      mJavaBasePackage(NULL),
      mBaseModule(NULL),
      mCommHandler(new string("")),
      mTargetTypeString(new string("JNA")),
      mDebugLevel(1)
{}

PARAMETERS::~Parameters()
{
    delete mHeaderDir;
    delete mJavaSrcDir;
    delete mJavaBasePackage;
    delete mBaseModule;
    delete mCommHandler;
    delete mTargetTypeString;
}

#undef PARAMETERS

