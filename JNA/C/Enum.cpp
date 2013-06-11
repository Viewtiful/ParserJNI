/** @file
 *
 * Body for Enum class
 */

#include "Utils/Output.h"
#include "C/Enum.h"

using std::string;
using std::ostream;

#define ENUM nsC::Enum

ENUM::Enum()
    : mNextValue(0)
{
}

ENUM::~Enum()
{
}

void ENUM::setName(const string& name)
{
    DEBUG(3) << "Setting enum name:\"" << name << "\"\n";
    mName = name;
}

const string& ENUM::getName(void) const
{
    return mName;
}

void ENUM::setTypedef(const string& name)
{
    DEBUG(3) << "Setting enum typedef:\"" << name << "\"\n";
    mTypedef = name;
}

const string& ENUM::getTypedef(void) const
{
    return mTypedef;
}

void ENUM::addValue(const string& name)
{
    addValue(name, mNextValue);
}

void ENUM::addValue(const string& name, int value)
{
    DEBUG(3) << "Adding enum value: [" << name << "=" << value << "]\n";
    mValues.push_back(EnumValue(name, value));
    mNextValue = value + 1;
}

bool ENUM::addValue(const string& name,
                    const string& value)
{
    DEBUG(3) << "Searching enum reference value for \"" << value << "\"\n";
    // FIXME current limitation of this : only work when the referenced
    // value is previously declared and it will not be visible in the
    // converted java file (it will only show the numerical value)
    EnumValues::const_iterator iter = mValues.begin();
    while (iter != mValues.end() && iter->first != value)
        ++iter;
    if (iter == mValues.end()) {
        ERR << "Enum reference value not found ("
            << value << ") !\n";
        return false;
    }
    else
    {
        DEBUG(3) << "Found;";
        addValue(name, iter->second);
        return true;
    }
}

const ENUM::EnumValues& ENUM::getValues(void) const
{
    return mValues;
}

void ENUM::display(ostream& stream) const
{
    EnumValues::const_iterator iter(mValues.begin());
    stream << "[";
    if (!mName.empty())
        stream << mName << "=";
    else
        stream << "<unnamed>=";

    while (iter != mValues.end()) {
        stream << "{" << iter->first << "=" << iter->second << "}";
        ++iter;
    }
    if (!mTypedef.empty())
        stream << ">" << mTypedef;
    else
        stream << ">{nothing}";

    stream << "]";
}

#undef ENUM

