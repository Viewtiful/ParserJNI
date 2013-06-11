/** @file
 *
 * Body for the Struct class
 */

#include "Utils/Output.h"
#include "C/Struct.h"

using std::string;
using std::ostream;
using nsC::Param;

#define STRUCT nsC::Struct

STRUCT::Struct()
    : mIndirections(0)
{
}

STRUCT::~Struct()
{
}

void STRUCT::setName(const string& name)
{
    DEBUG(3) << "Setting struct name:\"" << name << "\"\n";
    mName = name;
}

const string& STRUCT::getName(void) const
{
    return mName;
}

void STRUCT::setTypedef(const string& name)
{
    DEBUG(3) << "Setting struct typedef name:\"" << name << "\"\n";
    mTypedef = name;
}

const string& STRUCT::getTypedef(void) const
{
    return mTypedef;
}

void STRUCT::addTypedefIndirection(void)
{
    DEBUG(3) << "Typedef struct is an indirection\n";
    ++mIndirections;
}

int STRUCT::getTypedefIndirection(void) const
{
    return mIndirections;
}

void STRUCT::addField(const string& type,
                      const string& name)
{
    mFields.push_back(Param(type, name));
}

Param::vector& STRUCT::getFields(void)
{
    return mFields;
}

const Param::vector& STRUCT::getFields(void) const
{
    return mFields;
}

void STRUCT::display(ostream& stream) const
{
    stream << "[";
    if (mName.empty())
        stream << "<unnamed>";
    else
        stream << mName;

    if (!mFields.empty()) {
        stream << "{";
        for (Param::vector::const_iterator iter(mFields.begin());
             iter != mFields.end();
             ++iter)
        {
            if (iter != mFields.begin())
                stream << ", ";
            stream << *iter;
        }
        stream << "}";
    }
    if (mTypedef.empty())
        stream << ">{nothing}";
    else
        stream << ">" << mTypedef;

    stream << "]";
}

#undef STRUCT

