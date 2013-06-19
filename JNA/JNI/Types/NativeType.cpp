/** @file
 *
 * Body for JNIParser
 */
#define NATIVETYPE nsJNI::NATIVETYPE
#include "JNI/Types/NativeType.h"
using namespace nsJNI;
using namespace std;

NativeType::NativeType(string javaType, string cppType, string VMSignature) : Type(javaType, cppType, VMSignature)
{

}


NativeType::~NativeType()
{

}

std::string NativeType::outputJava()
{
	return getJavaType();
}

std::string NativeType::outputCpp()
{
	return getCppType();
}


