/** @file
 *
 * Body for the PackageList class
 */

#include <algorithm>
#include "Utils/Output.h"
#include "Utils/Parameters.h"
#include "Utils/Utils.h"
#include "JNA/Type.h"
#include "JNA/PackageList.h"

using std::string;
using std::vector;
using std::ostream;
using nsUtils::Parameters;
using nsUtils::stringReplace;

#define PACKAGELIST nsJNA::PackageList

PACKAGELIST::PackageList()
{
}

PACKAGELIST::~PackageList()
{
}

void PACKAGELIST::addType(const Type* type, bool includeVariant)
{
    if (!type) {
        ERR << "NULL passed where it shouldn't!\n";
        return;
    }
    size_t variantMax(includeVariant ? type->getVariantCount() : 1);
    for (size_t i(0); i < variantMax; ++i)
    {
        string importPackage(type->getImport(i));
        if (importPackage.empty()) {
            DEBUG(3) << "Type \"" << type->getBaseJavaName() << 
                "\" doesn't need an import\n";
            continue;
        }
        if (find(mPackageList.begin(), mPackageList.end(), importPackage) !=
            mPackageList.end()) {
            DEBUG(3) << "Package \"" << importPackage << 
                "\" already in the list\n";
            continue;
        }
        mPackageList.push_back(importPackage);
        DEBUG(3) << "Adding package \"" << importPackage 
                 << "\" to the list\n";
    }
}

void PACKAGELIST::addImport(const string& import)
{
    if (find(mPackageList.begin(), mPackageList.end(), import) !=
            mPackageList.end()) {
        DEBUG(3) << "Package \"" << import << "\" already in the list\n";
        return;
    }
    mPackageList.push_back(import);
}

void PACKAGELIST::addSupportClass(void)
{
    Parameters& param(Parameters::getInstance());
    string baseModule(param.getBaseModule());
    addImport(baseModule);
}

const vector<string>& PACKAGELIST::getList(void) const
{
    return mPackageList;
}

string PACKAGELIST::getImportString(void) const
{
    string result;
    for (vector<string>::const_iterator iterator(
                mPackageList.begin());
         iterator != mPackageList.end();
         ++iterator)
    {
        string import("import %PACKAGE%;\n");
        stringReplace(import, "PACKAGE", *iterator);
        result += import;
    }
    return result;
}

void PACKAGELIST::display(ostream& stream) const
{
    stream << "Package import list:[";
    for (vector<string>::const_iterator iter(mPackageList.begin());
         iter != mPackageList.end();
         ++iter)
    {
        if (iter != mPackageList.begin())
            stream << ',';
        stream << *iter;
    }
    stream << ']';
}

#undef PACKAGELIST

