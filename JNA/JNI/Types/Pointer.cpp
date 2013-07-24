#define POINTER nsJNI::POINTER
#include "JNI/Types/Pointer.h"
#include "Utils/Utils.h"
using namespace nsJNI;
using namespace nsUtils;
using namespace std;

Pointer::Pointer(const string& VMSignature,const string& CBaseType,TypesDictionnary *dictionnary,bool isNativeType) : Type("long","jlong",VMSignature)
{
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

bool Pointer::isBooleanWrapper()
{
	return false;
}

bool Pointer::isArray()
{
	return false;
}

bool Pointer::isNativeType()
{
	if(!_isNativeType)
		return _isNativeType;
	return _dictionnary->isNativeType(_CBaseType);
}

bool Pointer::isAddressWrapper()
{
	return false;
}

void Pointer::prepareCall(ofstream& f, const string& varName)
{
	//We have a pointer from not a native type, we get the address and cast it
	//to the corresponding type.
	if(!_isNativeType && _CBaseType != "size_t") {
		string structure (
				"\t\t%TYPE% %NAME%;\n"
				"\t\tif(%CName% != 0) {\n"
				"\t\t\t%NAME% = (%TYPE%)((contextWrapper *)%CName%)->ctxRef;\n"
				"\t\t\t((contextWrapper *)%CName%)->env = env;\n"
				"\t\t}\n"
				"\t\telse\n"
				"\t\t\t%NAME% = NULL;\n\n"
				);

		string name = "C_" + varName;

		stringReplace(structure, "TYPE", _CBaseType);
		stringReplace(structure, "NAME", name);
		stringReplace(structure, "CName", varName);

		f << structure;
	}
	else if(_CBaseType == "size_t") {
		string structure (
				"\t\t%TYPE% %NAME%;\n\n"
				);

		string name = "C_" + varName;
		stringReplace(structure, "TYPE", _CBaseType);
		stringReplace(structure, "NAME", name);

		f << structure;
	}
}

string Pointer::getJNIParameterName(const string& varName)
{
	return "C_" + varName;
}

void Pointer::getReturnValue(ofstream& f)
{
}

