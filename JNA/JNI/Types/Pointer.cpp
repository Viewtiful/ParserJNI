/** @file
 *
 * Body for JNIParser
 */
#define POINTER nsJNI::POINTER
#include "JNI/Types/Pointer.h"
#include "Utils/Utils.h"
using namespace nsJNI;
using namespace nsUtils;
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
	cout << "Pointer" << "CbaseType = " << _CBaseType << endl;
	return _dictionnary->isNativeType(_CBaseType);
}

bool Pointer::isAddressWrapper()
{
	return false;
}

void Pointer::prepareCall(ofstream& f,string& varName)
{
   if(!_isNativeType && _CBaseType != "size_t") {
      string structure (
            "\t\t%TYPE% %NAME% = (%TYPE%)((contextWrapper *)%CName%)->ctxRef;\n"
            "\t\t((contextWrapper *)%CName%)->env = env;\n\n"
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

string Pointer::getJNIParameterName(string& varName)
{
	return "Pointer";
}

void Pointer::getReturnValue(ofstream& f)
{



}
        
