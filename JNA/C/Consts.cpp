/** @file
 *
 * Body for Consts class
 */

#include "Utils/Output.h"
#include "C/Consts.h"

using std::string;
using std::ostream;

#define CONSTS nsC::Consts

CONSTS::Consts()
{
}

CONSTS::~Consts()
{
}

void CONSTS::addValue(const string& type,
                      const string& name,
                      const string& value)
{
    DEBUG(3) << "Adding CONST value: [" << name << 
                                    ":" << type << 
                                    "=" << value << "]\n";
    mValues.push_back(TypeValuePair(type, NameValuePair(name, value)));
}

size_t CONSTS::getCount(void) const
{
    return mValues.size();
}

const CONSTS::TypeValuePair& CONSTS::getValue(size_t id) const
{
    return mValues[id];
}

void CONSTS::display(ostream& stream) const
{
    ValueVector::const_iterator iter(mValues.begin());
    while (iter != mValues.end()) {
        stream << iter->second.first << ':' << iter->first << '=' 
               << iter->second.second << ';';
        ++iter;
    }
}

#undef CONSTS

