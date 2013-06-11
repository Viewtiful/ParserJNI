/** @file
 *
 * Body for Callback class
 */

#include "Utils/Output.h"
#include "C/Callback.h"

using std::string;
using std::ostream;
using nsC::Param;

#define CALLBACK nsC::Callback

CALLBACK::Callback()
{
}

CALLBACK::~Callback()
{
}

void CALLBACK::setName(const string& name)
{
    DEBUG(3) << "Setting callback name:\"" << name << "\"\n";
    mName = name;
}

const string& CALLBACK::getName(void) const
{
    return mName;
}

void CALLBACK::setReturnType(const string& returnType)
{
    DEBUG(3) << "Setting callback return type:\"" << returnType << "\"\n";
    mReturnType = returnType;
}

const string& CALLBACK::getReturnType(void) const
{
    return mReturnType;
}

Param::vector& CALLBACK::getParamList(void)
{
    return mParams;
}

const Param::vector& CALLBACK::getParamList(void) const
{
    return mParams;
}

void CALLBACK::display(ostream& stream) const
{
    stream << "[CB:";
    if (mName.empty())
        stream << "<unnamed>";
    else
        stream << mName;
    stream << ':';
    if (mReturnType.empty())
        stream << "<unknown>";
    else
        stream << mReturnType;
    if (!mParams.empty()) {
        for (size_t i(0); i < mParams.size(); ++i)
            stream << ',' << mParams[i];
    }
    stream << ']';
}

#undef CALLBACK

