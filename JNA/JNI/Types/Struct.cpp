#define STRUCT nsJNI::STRUCT
#include "JNI/Types/Struct.h"
#include "Utils/Utils.h"
#include <string>
#include <fstream>
using namespace nsJNI;
using namespace nsUtils;

Struct::Struct(ofstream &f, const string& VMSignature, const nsC::Struct& cStruct, TypesDictionnary* dictionnary) : Type(VMSignature)
{
	this->_cStruct = cStruct;
	this->_dictionnary = dictionnary;
	this->_jniType = "jobject";
	toupper(_cStruct.getTypedef()[0]);
	this->_javaType = cStruct.getTypedef();
   addStructToJava(f);
}


std::string Struct::outputJava()
{

}

void Struct::addStructToJava(ofstream &f)
{
   string structure(
		"\tpublic class %CLASSNAME% {\n"
		"%FIELDS%"
		"\t}\n\n"
	);

   nsC::Param::vector fields = _cStruct.getFields();
	string fieldsTemp;

	for(int i =0; i<fields.size(); i++) {
      string field("\t\t%VALUE1% %VALUE2%;");
		
		stringReplace(field, "VALUE1", _dictionnary->convertJava(fields[i].getCType()));
		stringReplace(field, "VALUE2", fields[i].getName());
		fieldsTemp += field;
   }

   stringReplace(structure, "CLASSNAME", _cStruct.getTypedef());

	stringReplace(structure, "FIELDS", fieldsTemp);

   f << structure;
}

std::string Struct::outputJNI()
{
}

Struct::~Struct(){

}        

bool Struct::isNativeType()
{
	cout << "isNativeType Struct" << endl;
	return false;
}

void Struct::prepareCall(ofstream &f,string& varName)
{

}

string Struct::getJNIParameterName(string& varName)
{
	return "Struct";
}

void Struct::getReturnValue(ofstream& f)
{


}
        
