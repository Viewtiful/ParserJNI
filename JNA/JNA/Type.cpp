/** @file
 *
 * Body for the Type class
 */

#include "Utils/Output.h"
#include "Utils/Utils.h"
#include "Utils/Parameters.h"
#include "JNA/Type.h"

using std::string;
using std::ostream;
using nsModules::Module;
using nsUtils::Parameters;
using nsUtils::stringReplace;
using nsUtils::prepareJavaString;

#define TYPE nsJNA::Type

TYPE::~Type()
{
}

const string& TYPE::getModule(void) const
{
    return mModule;
}

const string& TYPE::getBaseCName(void) const
{
    return mBaseCName;
}

const string& TYPE::getBaseJavaName(void) const
{
    return mBaseJavaName;
}

string TYPE::getFullPackageName(void) const
{
    const string& basePackage(
            Parameters::getInstance().getJavaBasePackage());
    if (basePackage.empty())
        return mBasePackage;
    else
        return basePackage + '.' + mBasePackage;
}

string TYPE::getImport(void) const
{
    if (mBasePackage.empty())
        return "";
    else
        return getFullPackageName() + '.' + getBaseJavaName();
}

string TYPE::getImport(size_t id) const
{
    if (id >= getVariantCount())
        return "";
    else {
        string variantPackage(getVariantPackage(id));
        if (variantPackage.empty())
            return "";
        else
            return getVariantPackage(id) + '.' + getVariantName(id);
    }
}

bool TYPE::isSpecial(void) const
{
    return false;
}

size_t TYPE::getVariantCount(void) const
{
    return 1;
}

string TYPE::getVariantName(size_t id) const
{
    (void) id;
    return mBaseJavaName;
}

string TYPE::getVariantPackage(size_t id) const
{
    (void) id;
    return getFullPackageName();
}

bool TYPE::isStructPtr(void) const {
    return mStructPtr;
}

TYPE::Type(const string& moduleName)
    : mModule(moduleName),
      mStructPtr(false)
{
}

TYPE::Type(const Module& module)
    : mModule(module.getModuleName()),
      mStructPtr(false)
{
}

void TYPE::display(ostream& stream) const
{
    stream << "[C:" << mModule << "::" << mBaseCName
           << ">JAVA:" << mBasePackage << "." << mBaseJavaName << "]";
}

void TYPE::addToMap(map& javaTypes)
{
    if (javaTypes.find(mBaseCName) == javaTypes.end()) {
        DEBUG(2) << "Adding \"" << mBaseCName << 
                    "\" into the javaTypes map\n";
        javaTypes[mBaseCName] = this;
    }
    else
    {
        ERR << "Type \"" << mBaseCName << "\" is already in the map!\n";
    }
}

void TYPE::prepareString(string& buffer) const
{
    prepareJavaString(buffer,
                      getFullPackageName(),
                      mPackageList.getImportString(),
                      getBaseJavaName(),
                      getBaseCName());
}

#undef TYPE

