/** @file
 *
 * Body for class Function
 */

#include "Utils/Output.h"
#include "C/Function.h"

using std::string;
using std::ostream;
using nsC::Param;

#define FUNCTION nsC::Function

FUNCTION::Function()
    : mReturnTypeSet(false),
      mNameSet(false)
{}

FUNCTION::~Function()
{}

void FUNCTION::setReturnType(const string& returnType)
{
    mReturnType = returnType;
    mReturnTypeSet = true;
}

string FUNCTION::getReturnType(void) const
{
    return mReturnType;
}

void FUNCTION::setName(const string& name)
{
    DEBUG(3) << "Setting function name:\"" << name << "\"\n";
    mName = name;
    mNameSet = true;
}

const string& FUNCTION::getName(void) const
{
    return mName;
}

Param::vector& FUNCTION::getParamList(void)
{
    return mParams;
}

const Param::vector& FUNCTION::getParamList(void) const
{
    return mParams;
}

bool FUNCTION::isVariadic(void) const
{
    for (Param::vector::const_iterator iter(mParams.begin());
         iter != mParams.end();
         ++iter) {
        string ctype(iter->getCType());
        if (ctype == "variadic" || ctype == "va_list")
            return true;
    }
    return false;
}

void FUNCTION::setComment(const string& comment) {
    mComment = comment;
}

const string& FUNCTION::getComment() const {
    return mComment;
}

void FUNCTION::display(ostream& stream) const
{
    stream << "Function(RET=";
    if (mReturnTypeSet)
        stream << mReturnType;
    else
        stream << "<undef>";
    stream << ",NAME=";
    if (mNameSet)
        stream << mName;
    else
        stream << "<undef>";
    if (mParams.empty())
        stream << ",void";
    else
        for (size_t i(0); i < mParams.size(); ++i)
            stream << ", " << mParams[i];

    stream << ");";
    if (mComment.length() > 0) {
        stream << ' ' << mComment;
    }
}

#undef FUNCTION

