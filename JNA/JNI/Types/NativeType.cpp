/** @file
 *
 * Body for JNIParser
 */
#define NATIVETYPE nsJNI::NATIVETYPE
#include "JNI/Types/NativeType.h"
using namespace nsJNI;
using namespace std;

NativeType::NativeType(const string& javaType, const string& jniType, const string& VMSignature) : Type(javaType, jniType, VMSignature)
{

}


NativeType::~NativeType()
{

}

std::string NativeType::outputJava()
{
	cout << "Output Java : NativeType" << endl;
	cout << "javaType = " << getJavaType() << endl;
	return getJavaType();
}

std::string NativeType::outputJNI()
{
	return getJNIType();
}


