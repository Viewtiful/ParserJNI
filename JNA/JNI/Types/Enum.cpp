/** @file
 *
 * Body for JNIParser
 */

#include "JNI/Types/Enum.h"
#include "Utils/Utils.h"
#include <string>
#include <fstream>
#define ENUM nsJNI::ENUM
using namespace nsJNI;
using namespace nsUtils;

static int nbOfOcc;

bool Enum::create(ofstream &f, const nsC::Enum::vector& en,
		TypesDictionnary *dictionnary)
{
	for (nsC::Enum::vector::const_iterator iterator(en.begin());
			iterator != en.end();
			++iterator)
	{
		const nsC::Enum& CEnum(*iterator);

		string enumName = CEnum.getName(); //Optimisation à faire (3 fois le même test
		if(enumName == "") {
			enumName = CEnum.getTypedef();
      }

      if(CEnum.getName() != "" && CEnum.getTypedef() != "") {
         enumName = CEnum.getTypedef();
      }
		dictionnary->addToMap(enumName, new Enum(f, enumName, enumName, "L" + dictionnary->getFilename() + "$" + enumName + ";", CEnum, dictionnary->getFilename()));
	}
	return true;
}

Enum::Enum(ofstream &f, const string& javaType, const string& jniType, const string& VMSignature, const nsC::Enum& cEnum, string filename) : Type(javaType, jniType, VMSignature)
{
	_cEnum = cEnum;
   _filename = filename;
	addEnumToJava(f);
}

void Enum::addEnumToJava(ofstream &f) {

   string structure(
			"\tpublic static enum %ENUMNAME% {\n"
			"%FIELDS%"
			"\t\tint enumValue;\n\n"
			"\t\t%ENUMNAME% (int val) {\n"
			"\t\t\tenumValue = val;\n"
			"\t\t}\n\n"
			"\t\tint getValue() {\n"
			"\t\t\treturn enumValue;\n"
			"\t\t}\n\n"
			"\t\tvoid setValue(int val) {\n"
			"\t\t\tenumValue = val;\n"
			"\t\t}\n"
			"\t}\n\n"
			);
	const nsC::Enum::EnumValues& values(_cEnum.getValues());
	string fields;
	
	for(int i = 0; i < values.size(); ++i)
	{	
		string field("\t\t%VALUE1% (%VALUE2%)");
		if(i+1 < values.size())
			field = field + ",\n";
		else if(i == values.size()-1)
			field = field + ";\n";
		
		stringReplace(field, "VALUE1", values[i].first);
		stringReplace(field, "VALUE2", values[i].second);
		fields += field;
	}

   _enumName = _cEnum.getName();
   if(_cEnum.getName().empty()) {
      _enumName = _cEnum.getTypedef();
   }

   if(!_cEnum.getName().empty() && !_cEnum.getTypedef().empty()) {
      _enumName = _cEnum.getTypedef();
   }
   stringReplace(structure, "ENUMNAME", _enumName);

	stringReplace(structure, "FIELDS", fields);

   f << structure;
}

Enum::~Enum()
{

}

std::string Enum::outputJava()
{	
	string enumName = _cEnum.getName();
	if(enumName == "") {
		enumName = _cEnum.getTypedef();
   }

   if(_cEnum.getName() != "" && _cEnum.getTypedef() != "") {
      enumName = _cEnum.getTypedef();
   }
	return enumName;
}

std::string Enum::outputJNI()
{
   return "jobject";
}

bool Enum::isNativeType()
{
	return false;
}

bool Enum::isAddressWrapper()
{
	return false;
}

bool Enum::isBooleanWrapper()
{
	return false;
}

bool Enum::isArray()
{
	return false;
}

void Enum::prepareCall(ofstream& f,string& varName)
{
   string structure (
         "\t\tjclass enm_%CNAME%;\n"
         "\t\tenm_%CNAME% = (*env)->GetObjectClass(env, %CNAME%);\n"
         "\t\tjmethodID get_%CNAME% = (*env)->GetMethodID(env, enm_%CNAME%, \"getValue\", \"()I\");\n"
         "\t\tjint %CNAME%_value = (*env)->CallIntMethod(env, %CNAME%, get_%CNAME%);\n"
         "\t\t%TYPE% %NAME% = (%TYPE%)%CNAME%_value;\n\n"
         );


   string name = "C_" + varName;

	stringReplace(structure, "TYPE", _enumName);
	stringReplace(structure, "NAME", name);
	stringReplace(structure, "CNAME", varName);

	f << structure;
}

string Enum::getJNIParameterName(string& varName)
{
	return "Enum";
}


void Enum::getReturnValue(ofstream& f)
{
   string structure (
         "\t\tjclass retObjCls = (*env)->FindClass(env, \"%FILENAME%$%ENUMNAME%\");\n"
         "\t\tjmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, \"values\", \"()[L%FILENAME%$%ENUMNAME%;\");\n"
         "\t\tjobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);\n\n"
         "\t\tint arrayLength = (*env)->GetArrayLength(env, valuesArray);\n\n"
         "\t\tint i, val;\n"
         "\t\tjmethodID getVal;\n"
         "\t\tgetVal = (*env)->GetMethodID(env, retObjCls, \"getValue\", \"()I\");\n\n"
         "\t\tfor(i = 0; i < arrayLength; ++i)\n"
         "\t\t{\n"
         "\t\t\tJNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);\n"
         "\t\t\tval = (*env)->CallIntMethod(env, JNI_result, getVal);\n"
         "\t\t\tif(val == tempJNI_result) {\n"
         "\t\t\t\tbreak;\n"
         "\t\t\t}\n"
         "\t\t}\n"
         "\t\treturn JNI_result;\n\n"
         );

   stringReplace(structure, "FILENAME", _filename);

   string enumName = _cEnum.getName();
   if(_cEnum.getName().empty()) {
      enumName = _cEnum.getTypedef();
   }

   if(!_cEnum.getName().empty() && !_cEnum.getTypedef().empty()) {
      enumName = _cEnum.getTypedef();
   }
   stringReplace(structure, "ENUMNAME", enumName);

   f << structure;
}
        
