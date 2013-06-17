/** @file
 *
 * Body for JNIParser
 */
#define TYPE nsJNI::TYPE
#include "JNI/Types/Type.h"

using namespace nsJNI;
Type::Type(string javaType,string cppType,string vmSignature)
{
	this->javaType = javaType;
	this->cppType = cppType;
	this->vmSignature = vmSignature;
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

string Type::getVMSignature()
{
	return vmSignature;
}
