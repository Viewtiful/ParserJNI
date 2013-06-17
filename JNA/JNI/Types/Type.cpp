/** @file
 *
 * Body for JNIParser
 */
#define TYPE nsJNI::TYPE
#include "JNI/Types/Type.h"

using namespace nsJNI;
Type::Type(string javaType,string cppType)
{
	this->javaType = javaType;
	this->cppType = cppType;
}

Type::~Type(){

}

string Type::getJavaType()
{
	return javaType;
}

string Type::getCppType()
{
	return cppType;
}


