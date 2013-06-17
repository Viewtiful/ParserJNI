/** @file
 *
 * Body for JNIParser
 */
#define TYPES nsJNI::TYPES
#include "JNI/Types/NativeType.h"
using namespace nsJNI;
using namespace std;

NativeType::NativeType(string javaType,string cppType,string vmSignature) : Type(javaType,cppType,vmSignature)
{
	
}


NativeType::~NativeType()
{

}

void NativeType::outputJava()
{
	cout << "JavaType = "<< javaType << endl;
}

void NativeType::outputCpp()
{
	cout << "JavaType = "<< cppType << endl;
}


