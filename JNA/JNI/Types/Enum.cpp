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
	cout << "Creating Java enums from \"" << endl;
	for (nsC::Enum::vector::const_iterator iterator(en.begin());
			iterator != en.end();
			++iterator)
	{
		const nsC::Enum& CEnum(*iterator);

		string enumName = CEnum.getName();
		if(enumName == "")
			enumName = CEnum.getTypedef();
		cout << "Enum Name = " << enumName << endl;
		dictionnary->addToMap(enumName, new Enum(f, enumName, enumName, "jobject", CEnum));
	}
	return true;
}

Enum::Enum(ofstream &f, const string& javaType, const string& jniType, const string& VMSignature, const nsC::Enum& cEnum) : Type(javaType, jniType, VMSignature)
{
	_cEnum = cEnum;
	addEnumToJava(f);
}

void Enum::addEnumToJava(ofstream &f) {

   string structure(
			"\tpublic static enum %ENUMNAME% {\n"
			"%FIELDS%"
			"\t\tint enumValue;\n\n"
			"\t\t%ENUMNAME%(int val) {\n"
			"\t\t\tenumValue = val;\n"
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

	if(!_cEnum.getName().empty()) {
		stringReplace(structure, "ENUMNAME", _cEnum.getName());
   }
	else {
		stringReplace(structure, "ENUMNAME", _cEnum.getTypedef());
   }

	stringReplace(structure, "FIELDS", fields);

   f << structure;
}

Enum::~Enum()
{

}

std::string Enum::outputJava()
{	
   string enumName;
	if(!_cEnum.getName().empty()) {
      enumName = _cEnum.getName();
   }
	else {
      enumName = _cEnum.getTypedef();
   }
   
	return enumName;
}

std::string Enum::outputJNI()
{
   return "jobject";
}
