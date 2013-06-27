#define ARRAY nsJNI::ARRAY
#include "JNI/Types/Array.h"
using namespace nsJNI;

Array::Array(const string& CBaseType, const string& VMSignature, TypesDictionnary *dictionnary) : Type(VMSignature)
{
	_CBaseType = CBaseType;	
	cout <<"Constructeur" <<  _CBaseType << endl;
	_dictionnary = dictionnary;
}

Array::~Array()
{

}

std::string Array::outputJava()
{
	cout << "Convert java Array" << endl;
	cout << "Signature" << getVMSignature() << endl;
	cout << "Base type = "<< _CBaseType;
	
	string test = _dictionnary->convertJava(_CBaseType)+"[]";
	cout << "Type = " << _dictionnary->convertJava(_CBaseType)<< endl;
	return _dictionnary->convertJava(_CBaseType)+"[]";
}

std::string Array::outputJNI()
{
	string jniType = _dictionnary->convertJNI(_CBaseType);
	return jniType + "Array";
}

bool Array::isNativeType()
{
	return _dictionnary->isNativeType(_CBaseType);
}

void Array::prepareCall(ofstream& f,string& varName)
{
	cout << "Prepare call" << endl;
}

std::string Array::getJNIParameterName(string& varName)
{
	return "Array";
}

void Array::getReturnValue(ofstream& f)
{

}
        
        
