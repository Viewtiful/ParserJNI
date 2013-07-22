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


bool Enum::create(ofstream &f, const nsC::Enum::vector& en,
		TypesDictionnary *dictionnary)
{
	for (nsC::Enum::vector::const_iterator iterator(en.begin());
			iterator != en.end();
			++iterator)
	{
		const nsC::Enum& CEnum(*iterator);

		//Here we get the name of the enum, either from it's name parameter or
		//it's typedef name.
		string enumName = CEnum.getName(); 

		//If the name is not defined, we get the typedef as the name.
		if(enumName.empty()) {
			enumName = CEnum.getTypedef();
		}

		//If both the name and the typedef are defined, we use the typedef as
		//the name.
		if(!CEnum.getName().empty() && !CEnum.getTypedef().empty()) {
			enumName = CEnum.getTypedef();
		}

		string VMSignature = "L" + dictionnary->getFilename() + "$" + enumName +
			";";
		//We then add the enum to the map of types and we create an enum.
		dictionnary->addToMap(enumName, new Enum(f, enumName, enumName,
					VMSignature, CEnum, dictionnary->getFilename()));
	}
	return true;
}

Enum::Enum(ofstream &f, const string& javaType, const string& jniType, const string& VMSignature, const nsC::Enum& cEnum, string filename) : Type(javaType, jniType, VMSignature)
{
	_cEnum = cEnum;
	_filename = filename;
	_enumName = javaType;
	//We add the new enum to the Java file generated.
	addEnumToJava(f);
}

void Enum::addEnumToJava(ofstream &f) {

	//This is what is generated in the Java file for an enum.
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

	//For each value in the C enum, we create the corresponding Java value.
	const nsC::Enum::EnumValues& values(_cEnum.getValues());
	string fields;

	for(size_t i = 0; i < values.size(); ++i)
	{	
		string field("\t\t%VALUE1% (%VALUE2%)");

		//Putting a ',' after each value added, for the last one, we had a ';'.
		if(i+1 < values.size())
			field = field + ",\n";
		else if(i == values.size()-1)
			field = field + ";\n";

		stringReplace(field, "VALUE1", values[i].first);
		stringReplace(field, "VALUE2", values[i].second);
		fields += field;
	}

	stringReplace(structure, "FIELDS", fields);
	stringReplace(structure, "ENUMNAME", _enumName);

	f << structure;
}

Enum::~Enum()
{
}

std::string Enum::outputJava()
{	
	return _enumName;
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
	//JNI code in order to get the value of the enum from Java.
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
	return "C_" + varName;
}


void Enum::getReturnValue(ofstream& f)
{
	//JNI code in order to pass back to Java, the value of the C enum.
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

	stringReplace(structure, "ENUMNAME", _enumName);

	f << structure;
}

