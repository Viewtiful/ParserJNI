/** @file
 *
 * Body for JNIParser
 */
#define POINTER nsJNI::POINTER
#include "JNI/Types/Pointer.h"
using namespace nsJNI;
using namespace std;

Pointer::Pointer(string VMSignature,string CBaseType,TypesDictionnary *dictionnary) : Type(VMSignature)
{
	this->_CBaseType = CBaseType;
	this->_dictionnary = dictionnary;
	this->_javaType = "long";
	this->_jniType = "jlong";
}


Pointer::~Pointer()
{

}

std::string Pointer::outputJava()
{
	return getJavaType();
}

std::string Pointer::outputJNI()
{
	return getJNIType();
}


