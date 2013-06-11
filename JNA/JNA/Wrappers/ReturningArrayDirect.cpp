/** @file
 *
 * Body for the ReturningArrayDirect class
 */

#include "Utils/Output.h"
#include "JNA/Type.h"
#include "JNA/Wrappers/ReturningArrayDirect.h"

using std::string;
using std::vector;
using nsC::Function;
using nsC::Param;
using nsJNA::Module;
using nsC::operator ==;
using nsJNA::Type;
using nsJNA::TypesDictionnary;

#define RETURNINGARRAYDIRECT nsJNA::nsWrappers::ReturningArrayDirect

RETURNINGARRAYDIRECT::~ReturningArrayDirect()
{
}

bool RETURNINGARRAYDIRECT::handle(const Function::vector& functions,
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

        // Found a potential match
        DEBUG(3) << "Checking parameters of \"" << functions[i].getName()
                 << "\"\n";
        const Param::vector& params = functions[i].getParamList();
        if (params.size() < 1) {
            DEBUG(3) << "Not enough parameters\n";
            continue;
        }
        const Param& param = params[params.size() - 1];
        if (param.getName() == "size" &&
            param.getCType() == "size_t *") {
                    
            DEBUG(2) << "Adding a wrapper [returning direct array] for \""
                     << functions[i].getName() << "\"\n";
            functionsDone[i] = true;
            new ReturningArrayDirect(functions[i], javaModule, dictionnary);
        }
    }
    return true;
}

string RETURNINGARRAYDIRECT::getWrapperCode(void) const
{
    string function(
            "%COMMENT%\n"
            "    public final static "
                "%RETURNTYPE% %WRAPPEDFUNCNAME%(%PARAMS%)\n"
            "    {\n"
            "%WRAPPERS%\n"
            "        final NativeLongByReference resultSize = "
                "new NativeLongByReference();\n"
            "        final Pointer resultPtr = "
                "%MODULENAME%.%FUNCNAME%(%CALLPARAMS%, resultSize);\n"
            "        if (resultPtr.equals(Pointer.NULL))\n"
            "            return null;\n"
            "        final byte resultBytes[] = new byte["
                "resultSize.getValue().intValue()];\n"
            "        resultPtr.read(0, resultBytes, 0, "
                "resultBytes.length);\n"
            "        return resultBytes;\n"
            "    }\n"
            );
    prepareString(function);
    return function;
}

RETURNINGARRAYDIRECT::ReturningArrayDirect(const Function& returningArray,
                               Module& javaModule,
                               const TypesDictionnary& dictionnary)
    : super(returningArray, javaModule)
{
    PackageList& packageList(javaModule.getPackageList());
    packageList.addImport("com.sun.jna.Pointer");
    packageList.addImport("com.sun.jna.ptr.NativeLongByReference");
    const Param::vector& params(returningArray.getParamList());
    Param::vector::const_iterator begin(params.begin());
    Param::vector::const_iterator end(params.end() - 1);
    WrappedParam::wrapParams(dictionnary, begin, end,
                             mWrappedParams, packageList);
    mReturnType = "byte[]";
}

#undef RETURNINGARRAYDIRECT

