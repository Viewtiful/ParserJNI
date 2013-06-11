/** @file
 *
 * Body for class Module
 */

#include "Convert/Parser.h"
#include "Utils/Output.h"
#include "Modules/Module.h"

using std::string;
using nsConvert::Parser;
using nsC::Enum;
using nsC::Struct;
using nsC::Callback;
using nsC::Function;
using nsC::Typedef;
using nsC::Consts;

#define MODULE nsModules::Module

MODULE::Module(const ModuleList::ModuleSource& moduleSource)
{
    mName = moduleSource.getModuleName();
    mName.erase(mName.length() - 2);
    mFilePath = moduleSource.getFilePath();
    mSubPath = moduleSource.getSubPath();
    DEBUG(1) << "Using file \"" << mFilePath
             << "\" for module \"" << mName << "\"\n";
}

MODULE::~Module()
{
}

bool MODULE::parse(void)
{
    DEBUG(1) << "Parsing module \"" << mName << "\"\n";
    Parser parser(mFilePath,
                  mFunctions,
                  mEnums,
                  mStructs,
                  mCallbacks,
                  mTypedefs,
                  mConsts);
    bool retVal = parser.parse();
    if (!retVal) {
        ERR << "Parser failed on file \"" << mFilePath << "\"\n";
        return false;
    }
    return true;
}

const Struct::vector& MODULE::getStructs(void) const
{ return mStructs; }

const Enum::vector& MODULE::getEnums(void) const
{ return mEnums; }

const Callback::vector& MODULE::getCallbacks(void) const
{ return mCallbacks; }

const Function::vector& MODULE::getFunctions(void) const
{ return mFunctions; }

const Typedef::vector& MODULE::getTypedefs(void) const
{ return mTypedefs; }

const Consts& MODULE::getConsts(void) const
{ return mConsts; }

const string& MODULE::getModuleName(void) const
{ return mName; }

const string& MODULE::getSubPath(void) const
{ return mSubPath; }

#undef MODULE

