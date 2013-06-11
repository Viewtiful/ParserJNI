/** @file
 *
 * Body for the Module class
 */

#include <fstream>
#include "Utils/Output.h"
#include "Utils/Parameters.h"
#include "Utils/Utils.h"
#include "JNA/Wrappers/Wrapper.h"
#include "JNA/Module.h"

using std::string;
using std::ostream;
using std::ofstream;
using std::vector;
using nsC::Function;
using nsC::Consts;
using nsJNA::TypesDictionnary;
using nsC::Param;
using nsUtils::Output;
using nsUtils::Parameters;
using nsUtils::directoryToPackage;
using nsUtils::stringReplace;
using nsUtils::splitQualifiedName;
using nsUtils::toJavaName;
using nsUtils::createJavaFileName;
using nsUtils::createPackageTree;
using nsUtils::prepareJavaString;
using nsJNA::PackageList;
using nsJNA::nsWrappers::Wrapper;

#define MODULE nsJNA::Module
#define METHOD MODULE::Method

METHOD::Method(const TypesDictionnary& typesDict,
               const Function& function,
               PackageList& packageList)
    : mDictionnary(&typesDict),
      mFunction(&function),
      mPackageList(&packageList),
      mIgnore(false)
{
    DEBUG(2) << "Creating module function for \""
             << mFunction->getName() << "\"\n";
}

METHOD::~Method()
{
}

bool METHOD::convert(void)
{
    // FIXME merge callbacks and this somehow
    Type* type(mDictionnary->getType(mFunction->getReturnType(), true));
    if (!type) {
        ERR << "Function \"" << mFunction->getName() <<
               "\" return type \"" << mFunction->getReturnType() <<
               "\" unavailable!\n";
        return false;
    }
    if (mFunction->isVariadic()) {
        DEBUG(3) << "Skipping variadic function\n";
        mIgnore = true;
        return true;
    }
    mPackageList->addType(type);
    mReturnJavaType = type->getBaseJavaName();
    const Param::vector& funcParams(mFunction->getParamList());
    size_t maxVariant(1);
    for (Param::vector::const_iterator iter(funcParams.begin());
         iter != funcParams.end();
         ++iter)
    {
        const Param& param(*iter);

        if (!(type = mDictionnary->getType(param.getCType()))) {
            ERR << "Function \"" << mFunction->getName() <<
                   "\" parameter \"" << param.getName() << 
                   "\" need unavailable type \"" << param.getCType()
                << "\"!\n";
            return false;
        }
        mPackageList->addType(type, true);
        if (type->getVariantCount() > maxVariant)
            maxVariant = type->getVariantCount();
    }

    mParamString.resize(maxVariant);
    for (Param::vector::const_iterator iter(funcParams.begin());
         iter != funcParams.end();
         ++iter)
    {
        const Param& param(*iter);

        type = mDictionnary->getType(param.getCType());
        for (size_t i(0); i < maxVariant; ++i)
        {
            if (!mParamString[i].empty())
                mParamString[i] += ", ";
            mParamString[i] += type->getVariantName(i) + ' ' + 
                               param.getName();
        }
    }
    return true;
}

string METHOD::getString(void) const
{
    string resultStr(
        "%COMMENT%\n"
        "        public native static %RETURNTYPE% %FUNCNAME%(%PARAMLIST%);\n"
        );
    string result;
    stringReplace(resultStr, "COMMENT", mFunction->getComment());
    stringReplace(resultStr, "FUNCNAME", mFunction->getName());
    stringReplace(resultStr, "RETURNTYPE", mReturnJavaType);
    for (size_t i(0); i < mParamString.size(); ++i)
    {
        string func(resultStr);
        stringReplace(func, "PARAMLIST", mParamString[i]);
        result += func;
    }
    return result;
}

MODULE::Module(const nsModules::Module& module, const string& commHandler)
    : mModule(module),
      mCommHandler(commHandler)
{
    DEBUG(2) << "Converting module \"" << module.getModuleName() << "\"\n";
    mName = module.getModuleName();
    mPackageList.addImport("com.sun.jna.Native");
    mPackageList.addSupportClass();
}

MODULE::~Module()
{
    for (vector<Wrapper*>::iterator iter(mWrappers.begin());
         iter != mWrappers.end();
         ++iter)
        delete *iter;
}

bool MODULE::prepare(const TypesDictionnary& typesDict)
{
    DEBUG(1) << "Preparing module \"" << getName() << "\"\n";

    if (!prepareFunctions(typesDict))
        return false;
    if (!prepareConsts(typesDict))
        return false;
    if (!Wrapper::addWrappers(mModule, *this, typesDict))
        return false;
    if (!updateComments())
        return false;

    return true;
}

bool MODULE::needWriting(void) const
{
    // trim "empty" modules
    return mModule.getFunctions().size() != 0;
}

bool MODULE::convert(ostream& file) const
{
    string structure(
            "/** Mapping for %MODULEPATH% */\n"
            "public class %BASEJAVANAME%\n"
            "{\n"
            "%CONSTS%"
            "%WRAPPERS%"
    		"\n"
            "    private %BASEJAVANAME%()\n"
            "    {\n"
            "    }\n"
            "    private static class Natives {\n"
            "        static\n"
            "        {\n"
            "            Native.register(%SUPPORTCLASSNAME%.getLibrary());\n"
            "        }\n"
            "%FUNCTIONS%"
            "    };\n"
            "}\n"
            );
    string functions;
    for (Method::vector::const_iterator iter(mMethods.begin());
         iter != mMethods.end();
         ++iter)
        functions += iter->getString();

    stringReplace(structure, "MODULEPATH", mModule.getSubPath() +
                  mModule.getModuleName() + ".h");
    stringReplace(structure, "FUNCTIONS", functions);
    stringReplace(structure, "CONSTS", mConstsString);
    stringReplace(structure, "WRAPPERS", Wrapper::getWrappers(mWrappers));
    prepareJavaString(structure,
                      getFullPackageName(),
                      mPackageList.getImportString(),
                      getBaseJavaName(),
                      mModule.getModuleName());
    file << structure;
    return true;
}

bool MODULE::processModules(const nsModules::Module::vector& modules,
                            const TypesDictionnary& typesDict)
{
    Output& output(Output::getInstance());
    Parameters& param(Parameters::getInstance());
    string javaPath(param.getJavaSrcDir());
    bool dryRun(param.isDryRun());

    if (!dryRun)
        output.startProgress((int) modules.size(), 
                "STEP 6/x Processing modules");
    else
        OUT << " ========== DRYRUN ==========\n";

    for (nsModules::Module::vector::const_iterator iter(
                modules.begin());
         iter != modules.end();
         ++iter)
    {
        if (!dryRun)
            output.progress(string("Processing \"") + 
                            iter->getModuleName() + 
                            "\"");

        Module module(*iter, param.getCommHandler());
        if (!module.prepare(typesDict)) {
            ERR << "Error while preparing module \""
                << module.getName()
                << "\"\n";
            if (!dryRun)
                output.endProgress(true);
            return false;
        }

        if (!module.needWriting()) {
            DEBUG(2) << "Skipping empty module \"" << module.getName() << 
                        "\"\n";
            continue;
        }
        
        string filePath = 
            createJavaFileName(javaPath,
                               module.getFullPackageName(),
                               module.getBaseJavaName());
        if (dryRun) {
            OUT << "Writting Java Module \"" << module.getBaseJavaName()
                << "\" into \"" << filePath << "\"\n";
        }
        else
        {
            DEBUG(3) << "Output Java code for \"" << 
                        module.getBaseJavaName()
                     << "\" into \"" << filePath << "\"\n";

            createPackageTree(javaPath, module.getFullPackageName());
            ofstream outputFile(filePath.c_str());
            outputFile << 
                "/* code generated by JNAConvert -- DO NOT EDIT */\n";
            module.convert(outputFile);
            outputFile.close();
        }

    }
    if (!dryRun)
        output.endProgress();

    return true;
}

void MODULE::addWrapperPtr(Wrapper* wrapper)
{
    mWrappers.push_back(wrapper);
}

PackageList& MODULE::getPackageList(void)
{
    return mPackageList;
}

string MODULE::getFullPackageName(void) const
{
    string result;
    string basePackage = Parameters::getInstance().getJavaBasePackage();
    result = basePackage;
    string modulePackage = directoryToPackage(mModule.getSubPath());
    if (result.empty())
        result = modulePackage;
    else if (!modulePackage.empty())
        result = result + '.' + modulePackage;
    if (result[result.length() - 1] == '.')
        result.erase(result.length() - 1);
    return result;
}

string MODULE::getBaseJavaName(void) const
{
    return toJavaName(mName, false, false, true);
}

const string& MODULE::getName(void) const
{
    return mName;
}

bool MODULE::updateComments(void)
{
    if (mCommHandler.length() == 0)
    {
        return true ;
    }
    std::vector<nsWrappers::Wrapper*>::iterator iter;
    for (iter = mWrappers.begin(); iter != mWrappers.end(); ++iter)
    {
        if (!(*iter)->updateComment(mCommHandler))
            return false;
    }
    return true;
}

bool MODULE::prepareFunctions(const TypesDictionnary& typesDict)
{
    DEBUG(2) << "Checking function types\n";
    const Function::vector& functions(mModule.getFunctions());
    for (Function::vector::const_iterator iter(functions.begin());
         iter != functions.end();
         ++iter)
    {
        const Function& func(*iter);
        Method method(typesDict, func, mPackageList);
        if (!method.convert()) {
            ERR << "Error while inserting function \""
                << func.getName() << "\"\n";
            return false;
        }
        else
            mMethods.push_back(method);
    }
    return true;
}

bool MODULE::prepareConsts(const TypesDictionnary& typesDict)
{
    DEBUG(2) << "Adding constants\n";
    const Consts& consts(mModule.getConsts());
    size_t valCount(consts.getCount());
    for (size_t i(0); i < valCount; ++i) {
        const Consts::TypeValuePair& value(consts.getValue(i));
        Type* type(typesDict.getType(value.first));
        if (type == NULL)
            return false;
        mPackageList.addType(type);
        string constLine(
                "    public final static %TYPE% %NAME% = %VALUE%;\n");
        stringReplace(constLine, "TYPE", type->getBaseJavaName());
        stringReplace(constLine, "NAME", value.second.first);
        stringReplace(constLine, "VALUE", value.second.second);
        mConstsString += constLine;
    }
    return true;
}

#undef METHOD
#undef MODULE

