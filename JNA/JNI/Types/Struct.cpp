#define STRUCT nsJNI::STRUCT
#include "JNI/Types/Struct.h"
#include "Utils/Utils.h"
#include <string>
#include <fstream>
using namespace nsJNI;
using namespace nsUtils;

Struct::Struct(ofstream &f, ofstream &f2, const string& VMSignature, const nsC::Struct& cStruct, TypesDictionnary* dictionnary) : Type(VMSignature)
{
	this->_cStruct = cStruct;
	this->_dictionnary = dictionnary;
	this->_jniType = "jobject";
	toupper(_cStruct.getTypedef()[0]);
	this->_javaType = cStruct.getTypedef();
   addStructToJava(f);
   //addStructFunctionToJNI(f2);
}


std::string Struct::outputJava() // Warning unused overridden function
{
	return "Java";
}

std::string Struct::outputJNI() // Warning unused overridden function
{
	return "JNI";
}
void Struct::addStructToJava(ofstream &f)
{
   string structure(
		"\tpublic class %CLASSNAME% {\n"
		"\t\t%FIELDS%\n"
      "\t\tprivate long mInternal;\n\n"
      "\t\t%CONSTRUCTOR%\n\n"
		"\t}\n\n"
      "%GS%\n\n"
	);

   nsC::Param::vector fields = _cStruct.getFields();
	string fieldsTemp;
	string getterSetter;
	for(size_t i =0; i<fields.size(); i++) {
      string field("%VALUE1% %VALUE2%;");
		
		stringReplace(field, "VALUE1", _dictionnary->convertJava(fields[i].getCType()));
		stringReplace(field, "VALUE2", fields[i].getName());

		getterSetter = getterSetter 
            + generateGetter(fields[i].getCType(),fields[i].getName())
            + generateSetter(fields[i].getCType(),fields[i].getName());
 
		fieldsTemp += field;
   }

   stringReplace(structure, "CLASSNAME", _cStruct.getTypedef());
	stringReplace(structure, "FIELDS", fieldsTemp);
	//stringReplace(structure, "CONSTRUCTOR", getterSetter);
	stringReplace(structure, "GS", getterSetter);	
   f << structure;
}

/*string Struct::generateConstructor(const string& fieldName)
{
	string getterStructure(
            "\tpublic native %RETURNTYPE% gen_jni_%CLASSNAME%_get_%ATTRIBUTENAME%"
	         "(long mInternal);\n"
            );
	
	stringReplace(getterStructure, "RETURNTYPE", _dictionnary->convertJava(fieldType));
	stringReplace(getterStructure, "CLASSNAME", _cStruct.getTypedef());
	stringReplace(getterStructure, "ATTRIBUTENAME", fieldName);

	return getterStructure;
}*/

Struct::~Struct(){

}        

bool Struct::isNativeType()
{
	cout << "isNativeType Struct" << endl;
	return false;
}

bool Struct::isAddressWrapper()
{
	return false;
}

bool Struct::isBooleanWrapper()
{
	return false;
}

void Struct::prepareCall(ofstream &f,string& varName)
{

}

bool Struct::isArray()
{
	return false;
}

string Struct::getJNIParameterName(string& varName)
{
	return "Struct";
}

void Struct::getReturnValue(ofstream& f)
{


}

string Struct::generateGetter(const string& fieldType,const string& fieldName)
{
	string getterStructure(
            "\tpublic native %RETURNTYPE% gen_jni_%CLASSNAME%_get_%ATTRIBUTENAME%"
	         "(long mInternal);\n"
            );
	
	stringReplace(getterStructure, "RETURNTYPE", _dictionnary->convertJava(fieldType));
	stringReplace(getterStructure, "CLASSNAME", _cStruct.getTypedef());
	stringReplace(getterStructure, "ATTRIBUTENAME", fieldName);

	return getterStructure;
}        

string Struct::generateSetter(const string& fieldType,const string& fieldName)
{
	string setterStructure(
            "\tpublic native void gen_jni_%CLASSNAME%_set_%ATTRIBUTENAME%"
	         "(long mInternal, %JAVATYPE% %FIELDNAME%);\n"
            );
	
	stringReplace(setterStructure, "CLASSNAME", _cStruct.getTypedef());
	stringReplace(setterStructure, "ATTRIBUTENAME", fieldName);
	stringReplace(setterStructure, "JAVATYPE", _dictionnary->convertJava(fieldType));
	stringReplace(setterStructure, "FIELDNAME", fieldName);

	return setterStructure;
}        
