/** @file
 *
 * Body for the Default class
 */

#include "Utils/Output.h"
#include "Utils/Utils.h"
#include "JNA/Type.h"
#include "JNA/Wrappers/Default.h"

using std::string;
using std::vector;
using nsC::Function;
using nsJNA::TypesDictionnary;
using nsUtils::stringReplace;

#define DEFAULT nsJNA::nsWrappers::Default

DEFAULT::~Default()
{
}

bool DEFAULT::handle(const Function::vector& functions,
                            vector<bool>& functionsDone,
                            Module& javaModule,
                            const TypesDictionnary& dictionnary)
{
    for (size_t i(0), len(functions.size());
         i < len;
         ++i)
    {
        if (functionsDone[i])
            continue;
        const Function& function(functions[i]);
        DEBUG(2) << "Adding a wrapper [default] for \""
                 << function.getName() << "\"\n";
        functionsDone[i] = true;
        new Default(function, javaModule, dictionnary);
    }
    return true;
}

string DEFAULT::getWrapperCode(void) const
{
    string function(
                "%COMMENT%\n"
                "    public final static "
                    "%RETURNTYPE% %WRAPPEDFUNCNAME%(%PARAMS%)\n"
                "    {\n"
                "%WRAPPERS%"
                "%RETURNWRAPPER%"
                "    }\n");
    stringReplace(function, "RETURNWRAPPER", 
                  mReturnWrapper.getReturnBlock(
                      "%MODULENAME%.%FUNCNAME%(%CALLPARAMS%)"));
    prepareString(function);
    return function;
}

DEFAULT::Default(const Function& function,
                 Module& javaModule,
                 const TypesDictionnary& dictionnary,
                 int iteration)
    : super(function, javaModule),
      mReturnWrapper(function.getReturnType(), javaModule.getPackageList(),
                     dictionnary)
{
    PackageList& packageList(javaModule.getPackageList());
    packageList.addImport("com.sun.jna.Pointer");
    if (WrappedParam::wrapParams(dictionnary, function.getParamList(),
                                 mWrappedParams, packageList, iteration))
    {
        new Default(function, javaModule, dictionnary, iteration + 1);
    }
    const Type* javaType = dictionnary.getType(function.getReturnType(), 
                                               true);
    mNativeJavaType = javaType->getBaseJavaName();
    packageList.addType(javaType);
    mReturnType = mReturnWrapper.getReturnType();
}

#undef DEFAULT

