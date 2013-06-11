/** @file
 *
 * Body for the Typedef class
 */

#include "Utils/Output.h"
#include "C/Typedef.h"

using std::string;

#define TYPEDEF nsC::Typedef

TYPEDEF::Typedef(const string& CType, const string& javaType)
    : mCType(CType), mJavaType(javaType)
{
}

TYPEDEF::~Typedef()
{
}

const string& TYPEDEF::getCType(void) const
{ return mCType; }

const string& TYPEDEF::getTargetType(void) const
{ return mJavaType; }

#undef TYPEDEF

