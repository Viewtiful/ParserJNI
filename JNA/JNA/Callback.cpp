/** @file
 *
 * Body for the Callback class
 */

#include "Utils/Output.h"
#include "Utils/Utils.h"
#include "JNA/Callback.h"

using std::string;
using std::ostream;
using nsC::Param;
using nsJNA::TypesDictionnary;
using nsModules::Module;
using nsUtils::toJavaName;
using nsUtils::stringReplace;

#define CALLBACK nsJNA::Callback

CALLBACK::~Callback()
{
}

bool CALLBACK::create(const Module& module,
                      const TypesDictionnary& dictionnary,
                      Type::map& javaTypes)
{
    DEBUG(2) << "Creating Java callbacks from \"" << module.getModuleName()
             << "\"\n";
    const nsC::Callback::vector& callbacks(module.getCallbacks());
    for (nsC::Callback::vector::const_iterator iterator(callbacks.begin());
         iterator != callbacks.end();
         ++iterator)
    {
        const nsC::Callback& CCallback(*iterator);

        new Callback(module, CCallback, dictionnary, javaTypes);
    }
    return true;
}

bool CALLBACK::convertToJava(void)
{
    Type* type(mDictionnary.getType(mCallback.getReturnType(), true));
    if (!type) {
        ERR << "Callback \"" << mCallback.getName() <<
               "\" return type \"" << mCallback.getReturnType() <<
               "\" unavailable!\n";
        return false;
    }
    mPackageList.addType(type);
    mReturnJavaType = type->getBaseJavaName();
    const Param::vector& params(mCallback.getParamList());
    mParamString = "";
    for (Param::vector::const_iterator iterator(params.begin());
         iterator != params.end();
         ++iterator)
    {
        const Param& param(*iterator);
        if (!(type = mDictionnary.getType(param.getCType()))) {
            ERR << "Callback \"" << mCallback.getName() <<
                   "\" parameter \"" << param.getName() << 
                   "\" need unavailable type \"" << param.getCType()
                << "\"!\n";
            return false;
        }
        mPackageList.addType(type);
        if (!mParamString.empty())
            mParamString += ", ";
        mParamString += type->getBaseJavaName() + ' ' + param.getName();
    }
    DEBUG(3) << "Converted \"" << mCallback.getName() <<
                "\" successfuly\n";
    return true;
}

bool CALLBACK::needWriting(void) const
{
    return true;
}

bool CALLBACK::writeJava(ostream& file) const
{
    string structure(
        "/** Callback for %BASECNAME% */\n"
        "public interface %BASEJAVANAME% extends Callback\n"
        "{\n"
        "    public %RETURNTYPE% %BASEJAVANAME%(%PARAMS%);\n"
        "}\n"
        );
    stringReplace(structure, "RETURNTYPE", mReturnJavaType);
    stringReplace(structure, "PARAMS", mParamString);
    prepareString(structure);
    file << structure;

    return true;
}

CALLBACK::Callback(const Module& module,
                   const nsC::Callback& callback,
                   const TypesDictionnary& dictionnary,
                   Type::map& javaTypes)
    : super(module),
      mCallback(callback),
      mDictionnary(dictionnary)
{
    mBaseCName = callback.getName();
    mBaseJavaName = toJavaName(mBaseCName, false, false, true);
    mBasePackage = "types.callbacks";
    mPackageList.addImport("com.sun.jna.Callback");
    addToMap(javaTypes);
}

#undef CALLBACK

