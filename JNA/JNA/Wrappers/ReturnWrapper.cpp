/** @file
 *
 * Body for the ReturnWrapper class
 */

#include "Utils/Output.h"
#include "Utils/Utils.h"
#include "JNA/Wrappers/ReturnWrapper.h"

using std::string;
using nsJNA::TypesDictionnary;
using nsJNA::PackageList;
using nsJNA::Type;
using nsUtils::stringReplace;

#define RETURNWRAPPER nsJNA::nsWrappers::ReturnWrapper

RETURNWRAPPER::ReturnWrapper(const string& CType,
                             PackageList& packageList,
                             const TypesDictionnary& dictionnary)
{
    const Type* returnType(dictionnary.getType(CType, true));
    if (returnType->getBaseJavaName() == "NativeLong") {
        mReturnType = "long";
        mReturnBlock = string() + 
            "        final %RETURNTYPE% %WRAPPEDFUNCNAME%Result = %FUNCTIONCALL%.longValue();\n" +
            "%AFTERWRAPPERS%" +
            "        return %WRAPPEDFUNCNAME%Result;";
    }
    else if (returnType->getBaseJavaName() == "void")
    {
        mReturnType = "void";
        mReturnBlock = string() + 
            "        %FUNCTIONCALL%;\n" +
            "%AFTERWRAPPERS%";
    }
    else
    {
        mReturnType = returnType->getBaseJavaName();
        packageList.addType(returnType, true);
        mReturnBlock = string() + 
            "        final %RETURNTYPE% %WRAPPEDFUNCNAME%Result = %FUNCTIONCALL%;\n" +
            "%AFTERWRAPPERS%" +
            "        return %WRAPPEDFUNCNAME%Result;\n";
    }
}

RETURNWRAPPER::~ReturnWrapper()
{
}

string RETURNWRAPPER::getReturnBlock(const string& functionCall) const
{
    string result(mReturnBlock);
    stringReplace(result, "FUNCTIONCALL", functionCall);
    return result;
}

string RETURNWRAPPER::getReturnType(void) const
{
    return mReturnType;
}

#undef RETURNWRAPPER
