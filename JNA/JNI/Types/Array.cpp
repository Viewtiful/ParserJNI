#define ARRAY nsJNI::ARRAY
#include "JNI/Types/Array.h"
#include <string>
#include "Utils/Utils.h"
using namespace nsJNI;
using namespace nsUtils;

Array::Array(const string& CBaseType, const string& VMSignature, TypesDictionnary *dictionnary) : Type(VMSignature)
{
	_CBaseType = CBaseType;	
	_dictionnary = dictionnary;
}

Array::~Array()
{

}

std::string Array::outputJava()
{
	//Conversion of the Array's BaseType
	string javaType = _dictionnary->convertJava(_CBaseType);
	return javaType+"[]";
}
	

std::string Array::outputJNI()
{
	//Conversion of the Array's BaseType
	string jniType = _dictionnary->convertJNI(_CBaseType); // Voir si  référence possible
	return jniType + "Array"; // Corresponding for an Array in JNI
}

bool Array::isNativeType()
{
	//An array is Native is its Base type is Native
	return _dictionnary->isNativeType(_CBaseType);
}

bool Array::isAddressWrapper()
{
	return false;
}

bool Array::isBooleanWrapper()
{
	return false;
}

bool Array::isArray()
{
	return true;
}

void Array::prepareCall(ofstream& f, string& varName) 
{
	string structure (
			"\t\t%TYPE% * %NAME%;\n"
			"\t\tint %NAMELENGTH% = (*env)->GetArrayLength(env, %CNAME%);\n"
			"\t\t%NAME% = (%TYPE% *)malloc(%NAMELENGTH%);\n"
			"\t\t%NAME% = (*env)->Get%TYPEMAJ%ArrayElements(env, %CNAME%, NULL);\n\n"
			);
   _varName = varName;
	string type = _dictionnary->convertJNI(_CBaseType);
	string name = "C_" + varName;
	string nameLength = name + "_size";
	string typeMaj = type.substr(1, type.size());
	typeMaj = toJavaName(typeMaj, false, false, true);

	stringReplace(structure, "TYPE", type);
	stringReplace(structure, "NAME", name);
	stringReplace(structure, "NAMELENGTH", nameLength);
	stringReplace(structure, "TYPEMAJ", typeMaj);
	stringReplace(structure, "CNAME", varName);

	f << structure;
}

std::string Array::getJNIParameterName(string& varName) 
{
	return "Array";
}

void Array::getReturnValue(ofstream& f) 
{
   string structure (
         "\t\tJNI_result = (*env)->New%TYPEMAJ%Array(env, C_size);\n" 
         "\t\t(*env)->Set%TYPEMAJ%ArrayRegion(env, JNI_result, 0, C_size, (%CTYPE% *)tempJNI_result);\n"
         "\t\treturn JNI_result;\n"
         );

	string type = _dictionnary->convertJNI(_CBaseType);
   	string typeMaj = type.substr(1, type.size());
 	typeMaj = toJavaName(typeMaj, false, false, true);

   stringReplace(structure, "TYPEMAJ", typeMaj);
   stringReplace(structure, "CTYPE", type);

   f << structure;
}

void Array::getReturnValueAndFree(ofstream& f, string& varName) 
{
   string structure (
         "\t\t(*env)->Set%TYPEMAJ%ArrayRegion(env, %CNAME%, 0, %CNAMELENGTH%, %NAME%);\n"
         "\t\tfree(%NAME%);\n\n"
         );

	string type = _dictionnary->convertJNI(_CBaseType);
   	string typeMaj = type.substr(1, type.size());
 	typeMaj = toJavaName(typeMaj, false, false, true);

   stringReplace(structure, "TYPEMAJ", typeMaj);
   stringReplace(structure, "CNAME", varName);
   stringReplace(structure, "NAME", "C_" + varName);
   stringReplace(structure, "CNAMELENGTH", "C_" + varName + "_size");

   f << structure;
}
        
        
