/** @file
 *
 * Body for the Wrapper class
 */

#include <vector>
#include <algorithm>
#include "Utils/Output.h"
#include "C/Function.h"
#include "Utils/Utils.h"
#include "JNA/Wrappers/ReturningArray.h"
#include "JNA/Wrappers/ReturningArrayDirect.h"
#include "JNA/Wrappers/Default.h"
#include "JNA/Wrappers/Wrapper.h"

using std::vector;
using std::string;
using nsC::Function;
using nsC::Param;
using nsJNA::nsWrappers::ReturningArray;
using nsUtils::stringReplace;
using nsUtils::toJavaName;
using nsUtils::strings;
using nsUtils::splitLines;
using nsUtils::runCmd;
using nsJNA::TypesDictionnary;

#define WRAPPER nsJNA::nsWrappers::Wrapper
#define WRAPPEDPARAM nsJNA::nsWrappers::Wrapper::WrappedParam

WRAPPEDPARAM::WrappedParam(const string& fromType, const string& fromName,
                           vector& wrappedParams,
                           const Type* paramType,
                           PackageList& packageList)
    : mFromType(fromType),
      mFromName(toJavaName(fromName, true, true, false))
{
    wrappedParams.push_back(this);

    if (mFromType == "NativeLong") {
        mToName = mFromName + "2long";
        mToType = "long";
        packageList.addImport("com.sun.jna.NativeLong");
        mConvertCommand = 
            "            final %FROMTYPE% %TONAME% = "
                "new NativeLong(%FROMNAME%);\n";
    }
    else if (mFromType.length() > 11 && mFromType.substr(mFromType.length() - 11) == "ByReference" &&
            paramType != NULL && paramType->isStructPtr()) {
        mToName = mFromName + "Ref";
        mToType = mFromType.substr(0, mFromType.length() - 11);
        packageList.addType(paramType, false);
        string packageName = paramType->getImport();
        packageName.erase(packageName.length() - 11);
        packageList.addImport(packageName);
        mConvertCommand = "        final %FROMTYPE% %TONAME% = new %FROMTYPE%();\n";
        mAfterCommand = "        %FROMNAME%.setFromNative(Pointer.nativeValue(%TONAME%.getValue().getPointer()));\n";
    }
    else if (mFromType == "$Buffer") {
        mFromType = "ByteBuffer";
        mToName = mFromName + "2ByteBuffer";
        mToType = "byte[]";
        packageList.addImport("java.nio.ByteBuffer");
        mConvertCommand = 
            "            final %FROMTYPE% %TONAME% = "
                "%FROMTYPE%.wrap(%FROMNAME%);\n";
    }
    else if (mFromType == "$BufferWithOffset")
    {
        mFromType = "ByteBuffer";
        mToName = mFromName + "2ByteBuffer";
        mToType = "byte[]";
        packageList.addImport("java.nio.ByteBuffer");
        mConvertCommand = 
            "            final %FROMTYPE% %TONAME% = "
                "%FROMTYPE%.wrap(%FROMNAME%, "
                "%FROMNAME%Offset, %FROMNAME%Length).slice();\n";
    }
    else if (mFromType == "$Size") {
        mFromType = "NativeLong";
        mToName = mFromName + "2NativeLong";
        mToType = "";
        packageList.addImport("com.sun.jna.NativeLong");
        mConvertCommand = 
            "            final %FROMTYPE% %TONAME% = "
                "new NativeLong(%FROMNAME%.length);\n";
    }
    else if (mFromType == "$BufferOffset") {
        mFromType = "";
        mFromName = mFromName + "Offset";
        mToName = "";
        mToType = "int";
        mConvertCommand = "";
    }
    else if (mFromType == "$BufferLength") {
        mFromType = "NativeLong";
        mFromName = mFromName + "Length";
        mToName = mFromName + "2NativeLong";
        mToType = "int";
        packageList.addImport("com.sun.jna.NativeLong");
        mConvertCommand =
            "            final %FROMTYPE% %TONAME% = "
                "new NativeLong(%FROMNAME%);\n";
    }
    else if (mFromType == "$StructureSize") {
        mFromType = "NativeLong";
        mToName = mFromName + "Size2NativeLong";
        mToType = "";
        packageList.addImport("com.sun.jna.NativeLong");
        mConvertCommand =
            "            final %FROMTYPE% %TONAME% = "
            "new NativeLong(%FROMNAME%.size());\n";
    }
    else
    {
        mToName = mFromName;
        mToType = mFromType;
    }
    stringReplace(mConvertCommand, "FROMTYPE", mFromType);
    stringReplace(mConvertCommand, "FROMNAME", mFromName);
    stringReplace(mConvertCommand, "TONAME", mToName);
    stringReplace(mConvertCommand, "TOTYPE", mToType);
    stringReplace(mAfterCommand, "FROMTYPE", mFromType);
    stringReplace(mAfterCommand, "FROMNAME", mFromName);
    stringReplace(mAfterCommand, "TONAME", mToName);
    stringReplace(mAfterCommand, "TOTYPE", mToType);
}

WRAPPEDPARAM::~WrappedParam()
{
}

bool WRAPPEDPARAM::wrapParams(const nsJNA::TypesDictionnary& dict,
                              const Param::vector& params,
                              vector& wrappedParams,
                              PackageList& packageList,
                              int iteration)
{
    return wrapParams(dict, params.begin(), params.end(), wrappedParams, 
            packageList, iteration);
}

bool WRAPPEDPARAM::wrapParams(const nsJNA::TypesDictionnary& dict,
                              const Param::vector::const_iterator& begin,
                              const Param::vector::const_iterator& end,
                              vector& wrappedParams,
                              PackageList& packageList,
                              int iteration)
{
    bool result(false);
    for (Param::vector::const_iterator iter(begin), 
                                       iterNext(iter);
         iter != end;
         ++iter)
    {
        bool done(false);
        iterNext = iter + 1;
        const Param& current(*iter);
        const Type* currentType(dict.getType(current));
        if (currentType->getBaseJavaName() == "Pointer" &&
            iterNext != end) {
            // Buffer followed by it's size
            const Param& next(*iterNext);
            const Type* nextType(dict.getType(next));
            if (nextType->getBaseJavaName() == "NativeLong" &&
                next.getName() == current.getName() + "_size") {
                switch (iteration)
                {
                  default:
                  case 0:
                    addByteBufferWrapper(current, wrappedParams,
                                         packageList);
                   result = true;
                    break;
                  case 1:
                    addByteBufferWrapperWithOffset(current, wrappedParams,
                                                   packageList);
                    break;
                }
                done = true;
                ++iter;
            }
        }
        else if (currentType->getBaseJavaName() == "Structure" &&
                 iterNext != end) {
            const Param& next(*iterNext);
            const Type* nextType(dict.getType(next));
            if (nextType->getBaseJavaName() == "NativeLong" &&
                next.getName() == current.getName() + "_size") {
                addStructureWrapper(current, currentType, wrappedParams, 
                        packageList);
                done = true;
                ++iter;
            }
        }
        // Structure pointer followed by it's size
        if (!done)
            addDirectWrapper(current, currentType, wrappedParams, 
                    packageList);
    }
    return result;
}

string WRAPPEDPARAM::getName(void) const
{ return mFromName; }

string WRAPPEDPARAM::getWrappedName(void) const
{ return mToName; }

string WRAPPEDPARAM::getWrappingLine(void) const
{
    return mConvertCommand;
}

string WRAPPEDPARAM::getAfterWrappingLine(void) const
{
    return mAfterCommand;
}

string WRAPPEDPARAM::getJavaType(void) const
{ return mToType; }

void WRAPPEDPARAM::addDirectWrapper(const Param& param,
                                    const Type* paramType,
                                    vector& wrappedParams,
                                    PackageList& packageList)
{
    new WrappedParam(paramType->getBaseJavaName(), param.getName(), 
                     wrappedParams, paramType, packageList);
}

void WRAPPEDPARAM::addByteBufferWrapper(const Param& buffer,
                                        vector& wrappedParams,
                                        PackageList& packageList)
{
    new WrappedParam("$Buffer", buffer.getName(), wrappedParams, NULL,
                     packageList);
    new WrappedParam("$Size", buffer.getName(), wrappedParams, NULL,
                     packageList);
}

void WRAPPEDPARAM::addStructureWrapper(
        const Param& structure,
        const Type* currentType,
        vector& wrappedParams,
        PackageList& packageList)
{
    addDirectWrapper(structure, currentType, wrappedParams,
                    packageList);
    new WrappedParam(
            "$StructureSize",
            structure.getName(),
            wrappedParams,
            NULL,
            packageList);
}                                 

void WRAPPEDPARAM::addByteBufferWrapperWithOffset(const Param& buffer,
                                                  vector& wrappedParams,
                                                  PackageList& packageList)
{
    new WrappedParam("$BufferWithOffset", buffer.getName(), wrappedParams, NULL,
                     packageList);
    new WrappedParam("$BufferOffset", buffer.getName(), wrappedParams, NULL,
                     packageList);
    new WrappedParam("$BufferLength", buffer.getName(), wrappedParams, NULL,
                     packageList);
}

WRAPPER::~Wrapper()
{
    for (WrappedParam::vector::iterator iter(mWrappedParams.begin());
         iter != mWrappedParams.end();
         ++iter)
        delete *iter;
}

bool WRAPPER::addWrappers(const nsModules::Module& module,
                          Module& javaModule,
                          const TypesDictionnary& dictionnary)
{
    const Function::vector& functions(module.getFunctions());
    vector<bool> functionsDone;
    functionsDone.resize(functions.size());

    for (size_t i(0),size(functions.size()); i < size; ++i)
        functionsDone[i] = functions[i].isVariadic();
 
    if (!ReturningArrayDirect::handle(functions, functionsDone, javaModule,
                                      dictionnary))
        return false;
     if (!ReturningArray::handle(functions, functionsDone, javaModule,
                                dictionnary))
        return false;
   if (!Default::handle(functions, functionsDone, javaModule, dictionnary))
        return false;

    return true;
}

bool WRAPPER::updateComment(const string& commHandler)
{
    if (commHandler.length() == 0)
        return true;

    strings input;
    strings output;
    string paramLine;
    for (size_t i = 0; i < mWrappedParams.size(); ++i) {
        if (!mWrappedParams[i]->getJavaType().empty()) {
            if (!paramLine.empty()) {
                paramLine += ",";
            }
            paramLine += mWrappedParams[i]->getName();
        }
    }
    input.push_back(paramLine);
    strings comments(splitLines(mComment));
    for (size_t i = 0; i < comments.size(); ++i) {
        string line = comments[i];
        if (line.length() >= 2 && line.substr(line.length() - 2, 2) == "*/") {
            line.erase(line.length() - 2, 2);
        }
        if (line.substr(0, 3) == "/**") {
            line.erase(0, 3);
        } else if (line.substr(0, 2) == " *") {
            line.erase(0, 2);
        } else if (line.substr(0, 1) == "*") {
            line.erase(0, 1);
        }
        input.push_back(line);
    }
    if (runCmd(commHandler, input,  output)) {
        mComment = "/**";
        for (size_t i = 0; i < output.size(); ++i) {
            mComment += string("\n") + " * " + output[i];
        }
        mComment += "\n */\n";
        return true;
    } else {
        return false;
    }
}

string WRAPPER::getWrappers(std::vector<Wrapper*> wrappers)
{
    if (wrappers.size() == 0)
        return "";

    string result(
            "%WRAPPER%"
            );
    string wrappersStr;
    for (std::vector<Wrapper*>::const_iterator iter(wrappers.begin());
         iter != wrappers.end();
         ++iter)
    {
        wrappersStr += (*iter)->getWrapperCode();
    }
    stringReplace(result, "WRAPPER", wrappersStr);
    return result;
}

WRAPPER::Wrapper(const nsC::Function& function, Module& javaModule)
    : mComment(function.getComment()),
      mFuncName(function.getName()),
      mJavaModule(javaModule)
{
    javaModule.addWrapperPtr(this);
}

string WRAPPER::getParamList(void) const
{
    string result;
    for (WrappedParam::vector::const_iterator iter(mWrappedParams.begin());
         iter != mWrappedParams.end();
         ++iter)
    {
        WrappedParam* param(*iter);
        if (!param->getJavaType().empty()) {
            if (!result.empty())
                result += ", ";
            result += "final " + param->getJavaType() + " " + 
                      param->getName();
        }
    }
    return result;
}

string WRAPPER::getCallerList(void) const
{
    string result;
    for (WrappedParam::vector::const_iterator iter(mWrappedParams.begin());
         iter != mWrappedParams.end();
         ++iter)
    {
        WrappedParam* param(*iter);
        string wrappedName(param->getWrappedName());
        if (!wrappedName.empty()) {
            if (!result.empty())
                result += ", ";
            result += param->getWrappedName();
        }
    }
    return result;
}

string WRAPPER::getParamWrappers(void) const
{
    string result;
    for (WrappedParam::vector::const_iterator iter(mWrappedParams.begin());
         iter != mWrappedParams.end();
         ++iter)
    {
        WrappedParam* param(*iter);
        result += param->getWrappingLine();
    }
    return result;
}

string WRAPPER::getParamAfterWrappers(void) const
{
    string result;
    for (WrappedParam::vector::const_iterator iter(mWrappedParams.begin());
         iter != mWrappedParams.end();
         ++iter)
    {
        WrappedParam* param(*iter);
        result += param->getAfterWrappingLine();
    }
    return result;
}

void WRAPPER::prepareString(string& str) const
{
    stringReplace(str, "COMMENT", mComment);
    stringReplace(str, "RETURNTYPE", mReturnType);
    stringReplace(str, "WRAPPEDFUNCNAME", 
                  toJavaName(mFuncName, true, true, false));
    stringReplace(str, "FUNCNAME", string("Natives.") + mFuncName);
    stringReplace(str, "MODULENAME", mJavaModule.getBaseJavaName());
    stringReplace(str, "PARAMS", getParamList());
    stringReplace(str, "WRAPPERS", getParamWrappers());
    stringReplace(str, "AFTERWRAPPERS", getParamAfterWrappers());
    stringReplace(str, "CALLPARAMS", getCallerList());
}

#undef WRAPPER

