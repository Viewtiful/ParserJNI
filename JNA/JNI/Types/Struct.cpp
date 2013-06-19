#define STRUCT nsJNI::STRUCT
#include "JNI/Types/Struct.h"
using namespace nsJNI;

Struct::Struct(string javaType, string jniType, string VMSignature/*, nsC::Struct cStruct, TypesDictionnary* dictionnary*/) : Type(javaType,jniType,VMSignature)
{
	//this->cStruct = cStruct;
	//this->dictionnary = dictionnary;
}


std::string Struct::outputJava()
{
	/*cout << "public class " << cStruct.getTypedef() << " {" << endl;
	nsC::Param::vector fields = cStruct.getFields();
	
	for(int i =0; i<fields.size(); i++)
		cout << "\t" << dictionnary->convertJava(fields[i].getType()) << " " << fields[i].getName() << ";"<< endl;
	cout << "}" << endl;*/
	return getJavaType();
}

std::string Struct::outputJNI()
{
	return getJNIType();
}

Struct::~Struct(){

}        


