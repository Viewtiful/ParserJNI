#include "JNI/Types/Struct.h"
using namespace nsJNI;

Struct::Struct(string javaType, string cppType, string vmSignature, nsC::Struct cStruct, TypesDictionnary* dictionnary) : Type(javaType,cppType,vmSignature)
{
	this->cStruct = cStruct;
	this->dictionnary = dictionnary;
}


std::string Struct::outputJava()
{
	nsC::Param::vector fields = cStruct.getFields();
	for(int i =0; i<fields.size(); i++)
		cout << dictionnary->convertJava(fields[i].getType()) << " " << fields[i].getName() << endl;
}

std::string Struct::outputCpp()
{
	return "titi";
}

Struct::~Struct(){

}        


