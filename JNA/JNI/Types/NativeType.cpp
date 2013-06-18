/** @file
 *
 * Body for JNIParser
 */
#define NATIVETYPE nsJNI::NATIVETYPE
#include "JNI/Types/NativeType.h"
using namespace nsJNI;
using namespace std;

NativeType::NativeType(string javaType,string cppType,string vmSignature) : Type(javaType,cppType,vmSignature)
{
	
}


NativeType::~NativeType()
{

}

std::string NativeType::outputJava()
{
	return javaType;
}

std::string NativeType::outputCpp()
{
	return cppType ;
}


