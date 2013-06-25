/** @file
 *
 * Body for JNIParser
 */
#define TYPE nsJNI::TYPE
#include "JNI/Types/Type.h"

using namespace nsJNI;
using namespace std;
Type::Type(string javaType, string jniType, string VMSignature)
{
	_javaType = javaType;
	_jniType = jniType;
	_VMSignature = VMSignature;
}

Type::Type(string VMSignature)
{
	this->_VMSignature = VMSignature;
}

Type::~Type()
{

}

string Type::getJavaType()
{
	return _javaType;
}

string Type::getJNIType()
{
	return _jniType;
}

string Type::getVMSignature()
{
	return _VMSignature;
}



