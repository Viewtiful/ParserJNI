/** @file
 *
 * Body for the ReturningArray class
 */

#include "Utils/Output.h"
#include "JNA/Type.h"
#include "JNA/Wrappers/ReturningArray.h"

using std::string;
using std::vector;
using nsC::Function;
using nsJNA::Module;
using nsC::operator ==;
using nsJNA::Type;
using nsJNA::TypesDictionnary;

#define RETURNINGARRAY nsJNA::nsWrappers::ReturningArray

RETURNINGARRAY::~ReturningArray()
{
}

bool RETURNINGARRAY::handle(const Function::vector& functions,
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
        Type* returnType = 
            dictionnary.getType(functions[i].getReturnType(), true);
        if (returnType->getBaseJavaName() != "Pointer")
            continue;

        string baseFunctionName(functions[i].getName());
        size_t func_size_id(i);
        for (size_t i2(0); i2 < len && func_size_id == i; ++i2)
        {
            if (i2 != i &&
                !functionsDone[i2] && 
                functions[i2].getName() == baseFunctionName + "_size" &&
                functions[i2].getReturnType() == "size_t") {
                func_size_id = i2;
            }
        }
        if (func_size_id != i) {
            // Found a potential match
            DEBUG(3) << "Checking parameters of \"" << baseFunctionName 
                     << "\"\n";
            if (functions[func_size_id].getParamList() != 
                functions[i].getParamList()) {
                DEBUG(3) << "Discarded for different parameters\n";
                continue;
            }
                    
            DEBUG(2) << "Adding a wrapper [returning array] for \""
                     << baseFunctionName << "\"\n";
            functionsDone[i] = true;
            functionsDone[func_size_id] = true;
            new ReturningArray(functions[i], javaModule, dictionnary);
        }
    }
    return true;
}

string RETURNINGARRAY::getWrapperCode(void) const
{
    string function(
            "%COMMENT%\n"
            "    public final static "
                "%RETURNTYPE% %WRAPPEDFUNCNAME%(%PARAMS%)\n"
            "    {\n"
            "%WRAPPERS%\n"
            "        final Pointer resultPtr = "
                "%MODULENAME%.%FUNCNAME%(%CALLPARAMS%);\n"
            "        if (resultPtr.equals(Pointer.NULL))\n"
            "            return null;\n"
            "        final byte resultBytes[] = new byte["
                "%MODULENAME%.%FUNCNAME%_size(%CALLPARAMS%).intValue()];\n"
            "        resultPtr.read(0, resultBytes, 0, "
                "resultBytes.length);\n"
            "        return resultBytes;\n"
            "    }\n"
            );
    prepareString(function);
    return function;
}

RETURNINGARRAY::ReturningArray(const Function& returningArray,
                               Module& javaModule,
                               const TypesDictionnary& dictionnary)
    : super(returningArray, javaModule)
{
    PackageList& packageList(javaModule.getPackageList());
    packageList.addImport("com.sun.jna.Pointer");
    WrappedParam::wrapParams(dictionnary, returningArray.getParamList(),
                             mWrappedParams, packageList);
    mReturnType = "byte[]";
}

#undef RETURNINGARRAY

