/** @file
 *
 * Body for JNIParser
 */
#define POINTER nsJNI::POINTER
#include "JNI/Types/Pointer.h"
using namespace nsJNI;
using namespace std;

Pointer::Pointer(const string& VMSignature,const string& CBaseType,TypesDictionnary *dictionnary,bool isNativeType) : Type("long","jlong",VMSignature)
{
	cout << "toto" << endl;
	this->_CBaseType = CBaseType;
	this->_dictionnary = dictionnary;
	_isNativeType = isNativeType;
	
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

bool Pointer::isNativeType()
{
	if(!_isNativeType)
		return _isNativeType;
	cout << "Pointer" << "CbaseType = " << _CBaseType << endl;
	return _dictionnary->isNativeType(_CBaseType);
}

