/** @file
 *
 * Body for JNIParser
 */
#define NATIVETYPE nsJNI::NATIVETYPE
#include "JNI/Types/NativeType.h"
using namespace nsJNI;
using namespace std;

NativeType::NativeType(const string& javaType, const string& jniType, const string& VMSignature,bool isNativeType) : Type(javaType, jniType, VMSignature)
{
	_isNativeType = isNativeType;
	cout << "isNativeType Value : " << _isNativeType << endl;
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

bool NativeType::isNativeType()
{
	return _isNativeType;
}

void NativeType::prepareCall(ofstream& f,string& varName)
{

}

string NativeType::getJNIParameterName(string& varName)
{
	return "NativeType";
}

void NativeType::getReturnValue(ofstream& f)
{


}
        
