/** @file
 *
 * Body for JNIParser
 */
#define TYPE nsJNI::TYPE
#include "JNI/Types/Type.h"

using namespace nsJNI;
using namespace std;
Type::Type(string javaType,string cppType,string VMSignature)
{
	_javaType = javaType;
	_cppType = cppType;
	_VMSignature = VMSignature;
}

Type::~Type()
{

}

string Type::getJavaType()
{
	return _javaType;
}

string Type::getCppType()
{
	return _cppType;
}

string Type::getVMSignature()
{
	return _VMSignature;
}
