#define STRUCT nsJNI::STRUCT
#include "JNI/Types/Struct.h"
using namespace nsJNI;

Struct::Struct(string VMSignature, nsC::Struct cStruct, TypesDictionnary* dictionnary) : Type(VMSignature)
{
	this->_cStruct = cStruct;
	this->_dictionnary = dictionnary;
	this->_jniType = "jobject";
	toupper(_cStruct.getTypedef()[0]);
	this->_javaType = cStruct.getTypedef();
}


std::string Struct::outputJava()
{
	cout << "public class " << _cStruct.getTypedef() << " {" << endl;
	nsC::Param::vector fields = _cStruct.getFields();
	
	for(int i =0; i<fields.size(); i++)
		cout << "\t" << _dictionnary->convertJava(fields[i].getType()) << " " << fields[i].getName() << ";"<< endl;
	cout << "}" << endl;
}

std::string Struct::outputJNI()
{
}

Struct::~Struct(){

}        


