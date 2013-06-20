#define ARRAY nsJNI::ARRAY
#include "JNI/Types/Array.h"
using namespace nsJNI;

Array::Array(string CBaseType,string VMSignature,TypesDictionnary *dictionnary) : Type(VMSignature)
{
	this->_CBaseType = getCBaseTypeFromPointer(CBaseType);	
}

Array::~Array()
{

}

std::string Array::outputJava()
{
	return _dictionnary->convertJava(_CBaseType)+"[]";
}

std::string Array::outputJNI()
{
	string jniType = _dictionnary->convertJNI(_CBaseType);
	return jniType + "Array";
}

std::string Array::getCBaseTypeFromPointer(string pointerType)
{
	string CBaseType;
	int i,k;
	
	for(i = pointerType.size()-1 && pointerType[i]=='*';i>-1;i--);
	for(k = 0; k<i; k++)
		CBaseType[k] = pointerType[k];
				
	CBaseType[k]='\0';
	return CBaseType;
}
