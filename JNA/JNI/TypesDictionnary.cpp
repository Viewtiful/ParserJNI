/** @file
 *
 * Body for TypesDictionnary class
 */

#include <fstream>
#include "JNI/TypesDictionnary.h"
#define TYPESDICTIONNARY nsJNI::TypesDictionnary

TYPESDICTIONNARY::TypesDictionnary()
{
    
    
}

TYPESDICTIONNARY::~TypesDictionnary()
{
    
}


void TYPESDICTIONNARY::addMap(std::string inputType, Type* type)
{
	conversionMap.insert(std::pair<std::string,Type*>(inputType,type) );	
}

void TYPESDICTIONNARY::addBaseType()
{




}

#undef TYPESDICTIONNARY

