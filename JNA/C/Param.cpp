/** @file
 *
 * Body for the Param class
 */

#include <utility>
#include "Param.h"

using std::operator !=;
using std::string;
using std::ostream;

#define PARAM nsC::Param

PARAM::Param(const string& type,
             const string& name)
    : mType(type),
      mName(name),
      mIndirections(0)
{
    size_t len;
    while ((len = mType.length()) && mType[len - 1] == '*') {
        ++mIndirections;
        mType.erase(len - 1);
    }
    while ((len = mType.length()) && mType[len - 1] == ' ') {
        mType.erase(len - 1);
    }
}

PARAM::~Param()
{
}

const string& PARAM::getType(void) const
{
    return mType;
}

const string& PARAM::getName(void) const
{
    return mName;
}

int PARAM::getIndirections(void) const
{
    return mIndirections;
}

string PARAM::getCType(void) const
{
    string result(getType());
    int ind(getIndirections());
    if (ind) {
        result += ' ';
        while (ind--)
            result += '*';
    }
    return result;
}

bool PARAM::operator != (const Param& B) const
{
    return !(mType == B.mType &&
             mName == B.mName &&
             mIndirections == B.mIndirections);
}

void PARAM::display(ostream& stream) const
{
    if (mType.empty())
        stream << "<no type>";
    else
        stream << mType;
    stream << " ";
    for (int i = 0; i < mIndirections; ++i)
        stream << '*';

    if (mName.empty())
        stream << "<no name>";
    else
        stream << mName;
}

bool nsC::operator == (const Param::vector& A, const Param::vector& B)
{
    if (A.size() != B.size())
        return false;

    for (size_t i(0), len(A.size()); i < len; ++i)
        if (A[i] != B[i])
            return false;

    return true;
}

#undef PARAM

