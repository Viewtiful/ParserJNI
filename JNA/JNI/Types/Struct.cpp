#define STRUCT nsJNI::STRUCT
#include "JNI/Types/Struct.h"
#include "Utils/Utils.h"
#include "JNI/Types/Getter.h"
#include "JNI/Types/Setter.h"
#include <string>
#include <fstream>
using namespace nsJNI;
using namespace nsUtils;
using namespace std;
Struct::Struct(ofstream &f, ofstream &f2, const string& VMSignature, const nsC::Struct& cStruct, TypesDictionnary* dictionnary) : Type(VMSignature)
{
	this->_cStruct = cStruct;
	this->_dictionnary = dictionnary;
	this->_jniType = "jobject";
	toupper(_cStruct.getTypedef()[0]);
	this->_javaType = cStruct.getTypedef();
   addStructToJava(f);
   addStructFunctionToJNI(f2);
}


std::string Struct::outputJava() // Warning unused overridden function
{
	return "Java";
}

std::string Struct::outputJNI() // Warning unused overridden function
{
	return "JNI";
}

void Struct::addStructFunctionToJNI(ofstream &f) {
	/*string jniFunction(
            "%CREATE%"
            "%FREE%"
            "\n\n"
            );
	
   stringReplace(jniFunction, "CREATE", generateCreateFunction(false));
   stringReplace(jniFunction, "FREE", generateFreeFunction(false));

   nsC::Param::vector fields = _cStruct.getFields();
	string getterSetter;
	f << jniFunction;*/
	for(size_t i = 0;i<_getters.size();i++)
		_getters[i]->convertJNI(f);
	for(size_t i = 0;i<_setters.size();i++)
		_setters[i]->convertJNI(f);
}

void Struct::addStructToJava(ofstream &f)
{
   string structure(
		"\tpublic class %CLASSNAME% {\n"
		"%FIELDS%\n"
      "\t\tprivate long mInternal;\n\n"
      "%CONSTRUCTOR%"
      "%FINALIZE%"
      "%WRITE%"
      "%READ%"
		"\t}\n\n"
      "%CREATE%"
      "%FREE%"
	);

   nsC::Param::vector fields = _cStruct.getFields();
	string fieldsTemp;
	string getterSetter;
	for(size_t i =0; i<fields.size(); i++) {
      string field("\t\t%VALUE1% %VALUE2%;\n");
		
		stringReplace(field, "VALUE1", _dictionnary->convertJava(fields[i].getCType()));
		stringReplace(field, "VALUE2", fields[i].getName());
 		Getter *g = new Getter(fields[i],_javaType, _dictionnary);
        _getters.push_back(g);
        Setter *s = new Setter(fields[i], _javaType,  _dictionnary);
        _setters.push_back(s);
        fieldsTemp += field;
   }

   stringReplace(structure, "CLASSNAME", _cStruct.getTypedef());
	stringReplace(structure, "FIELDS", fieldsTemp);
	stringReplace(structure, "CONSTRUCTOR", generateConstructor());
   stringReplace(structure, "CREATE", generateCreateFunction(true));
   stringReplace(structure, "FINALIZE", generateFinalize());
   stringReplace(structure, "WRITE", generateWrite());
   stringReplace(structure, "READ", generateRead());
   stringReplace(structure, "FREE", generateFreeFunction(true));
   f << structure;
   for(size_t i = 0;i<_getters.size();i++)
   {
   		_getters[i]->convertJava(f);
   		f << endl;
   }
   for(size_t i = 0;i<_setters.size();i++)
   {
   		_setters[i]->convertJava(f);
   		f << endl;
   }
}

string Struct::generateConstructor()
{
	string constructor(
            "\t\tpublic %CLASSNAME%() {\n"
	         "\t\t\tmInternal = gen_jni_%CLASSNAME%_create();\n"
            "\t\t}\n\n"
            );
	
	stringReplace(constructor, "CLASSNAME", _cStruct.getTypedef());

	return constructor;
}

string Struct::generateFinalize()
{
	string constructor(
            "\t\t@Override\n"
            "\t\tpublic void finalize() {\n"
	         "\t\t\tgen_jni_%CLASSNAME%_free(mInternal);\n"
            "\t\t}\n\n"
            );
	
	stringReplace(constructor, "CLASSNAME", _cStruct.getTypedef());

	return constructor;
}

string Struct::generateWrite()
{
	string write(
            "\t\tpublic void write() {\n"
	         "%FIELDS%"
            "\t\t}\n\n"
            );


   nsC::Param::vector fields = _cStruct.getFields();
	string fieldsTemp;
	for(size_t i =0; i<fields.size(); i++) {
      string field("\t\t\tgen_jni_%CLASSNAME%_set_%VALUE%(mInternal, %VALUE%);\n");
		
		stringReplace(field, "VALUE", fields[i].getName());
	   stringReplace(field, "CLASSNAME", _cStruct.getTypedef());
		fieldsTemp += field;
   }
	
	stringReplace(write, "FIELDS", fieldsTemp);

	return write;
}

string Struct::generateRead()
{
	string read(
            "\t\tpublic void read() {\n"
	         "%FIELDS%"
            "\t\t}\n\n"
            );


   nsC::Param::vector fields = _cStruct.getFields();
	string fieldsTemp;
	for(size_t i =0; i<_getters.size(); i++) {
		fieldsTemp += "\t\t\t " + fields[i].getName() + " = " + _getters[i]->call() + "\n";
   }
	
	stringReplace(read, "FIELDS", fieldsTemp);

	return read;
}

string Struct::generateFreeFunction(bool java)
{
	string freeFunction;

   if(java) {
      freeFunction = "\tpublic native void gen_jni_%CLASSNAME%_free(long mInternal);\n";
	   stringReplace(freeFunction, "CLASSNAME", _cStruct.getTypedef());
   }
   else {
      freeFunction = 
         "\tJNIEXPORT void JNICALL gen_jni_%CLASSNAME%_free(JNIEnv *env, jclass cls, jlong stru) {\n"
         "\t\t%CLASSNAME% *C_ctx = (%CLASSNAME% *)stru;\n"
         "\t\tfree(C_ctx);\n"
         "\t}\n\n";
	   stringReplace(freeFunction, "CLASSNAME", _cStruct.getTypedef());
   }

	return freeFunction;
}

string Struct::generateCreateFunction(bool java)
{
   string createFunction;
   
   if(java) {
      createFunction = "\tpublic native long gen_jni_%CLASSNAME%_create();\n";
	   stringReplace(createFunction, "CLASSNAME", _cStruct.getTypedef());
   }
   else {
      createFunction = 
         "\tJNIEXPORT jlong JNICALL gen_jni_%CLASSNAME%_create(JNIEnv *env, jclass cls) {\n"
         "\t\t%CLASSNAME% *C_ctx = (%CLASSNAME% *)malloc(sizeof(%CLASSNAME%));\n"
         "\t\treturn C_ctx;\n"
         "\t}\n\n";
	   stringReplace(createFunction, "CLASSNAME", _cStruct.getTypedef());
   }

	return createFunction;
}

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

string Struct::generateGetter(bool java, const string& fieldType,const string& fieldName)
{
	string getterStructure;

   if(java) {
      getterStructure = "\tpublic native %RETURNTYPE% gen_jni_%CLASSNAME%_get_%ATTRIBUTENAME%"
      "(long mInternal);\n";

	   stringReplace(getterStructure, "RETURNTYPE", _dictionnary->convertJava(fieldType));
	   stringReplace(getterStructure, "CLASSNAME", _cStruct.getTypedef());
	   stringReplace(getterStructure, "ATTRIBUTENAME", fieldName);
   }
   else {
      getterStructure = "\tJNIEXPORT %RETURNTYPE% JNICALL gen_jni_%CLASSNAME%_get_%ATTRIBUTENAME%"
      "(JNIEnv *env, jclass cls, jlong stru) {\n"
      "\t\t%CLASSNAME% *C_ctx = (%CLASSNAME% *)stru;\n"
      "\t\treturn C_ctx->%ATTRIBUTENAME%;\n"
      "\t}\n\n";

      string typeRetour = _dictionnary->convertJNI(fieldType);

      if(typeRetour == "jobject") {
         typeRetour = "jint";
      }

	   stringReplace(getterStructure, "RETURNTYPE", typeRetour);
	   stringReplace(getterStructure, "CLASSNAME", _cStruct.getTypedef());
	   stringReplace(getterStructure, "ATTRIBUTENAME", fieldName);
   }

	return getterStructure;
}        

string Struct::generateSetter(bool java, const string& fieldType,const string& fieldName)
{
	string setterStructure;

   if(java) {
      setterStructure = "\tpublic native void gen_jni_%CLASSNAME%_set_%ATTRIBUTENAME%"
      "(long mInternal, %JAVATYPE% %FIELDNAME%);\n";

	   stringReplace(setterStructure, "CLASSNAME", _cStruct.getTypedef());
	   stringReplace(setterStructure, "ATTRIBUTENAME", fieldName);
	   stringReplace(setterStructure, "JAVATYPE", _dictionnary->convertJava(fieldType));
	   stringReplace(setterStructure, "FIELDNAME", fieldName);
   }
   else {
      setterStructure = "\tJNIEXPORT void JNICALL gen_jni_%CLASSNAME%_set_%ATTRIBUTENAME%"
      "(JNIEnv *env, jclass cls, jlong stru, %JNITYPE% %FIELDNAME%) {\n"
      "\t\t%CLASSNAME% *C_ctx = (%CLASSNAME% *)stru;\n"
      "%WRITEFIELD%"
      "\t}\n\n";

      string field = _dictionnary->convertJNI(fieldType);
      string writeField;
      if(field == "jobject") {
		   writeField = "\t\tjclass enm_%ATTRIBUTENAME%;\n"
		                "\t\tenm_%ATTRIBUTENAME% = (*env)->GetObjectClass(env, %ATTRIBUTENAME%);\n"
		                "\t\tjmethodID get_%ATTRIBUTENAME% = (*env)->GetMethodID(env, enm_%ATTRIBUTENAME%, \"getValue\", \"()I\");\n"
		                "\t\tjint %ATTRIBUTENAME%_value = (*env)->CallIntMethod(env, %ATTRIBUTENAME%, get_%ATTRIBUTENAME%);\n"
		                "\t\t%Type% C_%ATTRIBUTENAME% = (%Type%)%ATTRIBUTENAME%_value;\n"
                      "\t\tC_ctx->%ATTRIBUTENAME% = C_%ATTRIBUTENAME%;\n";

         stringReplace(writeField, "CLASSNAME", _cStruct.getTypedef());
	     stringReplace(writeField, "ATTRIBUTENAME", fieldName);
	     stringReplace(writeField, "Type", fieldType);
      }
      else {
         writeField = "\t\tC_ctx->%ATTRIBUTENAME% = %FIELDNAME%;\n";

	      stringReplace(writeField, "FIELDNAME", fieldName);
	      stringReplace(writeField, "ATTRIBUTENAME", fieldName);
      }

	   stringReplace(setterStructure, "CLASSNAME", _cStruct.getTypedef());
	   stringReplace(setterStructure, "ATTRIBUTENAME", fieldName);
	   stringReplace(setterStructure, "JNITYPE", field);
	   stringReplace(setterStructure, "FIELDNAME", fieldName);
	   stringReplace(setterStructure, "WRITEFIELD", writeField);
   }

	return setterStructure;
}

vector<Function*> Struct::getGetterSetters()
{
	int size = _getterSetters.size();
	copy(_getters.begin(),_getters.end(),back_inserter(_getterSetters));
	assert(_getterSetters.size()==size+_getters.size());
	
	size = _getterSetters.size();
	copy(_setters.begin(),_setters.end(),back_inserter(_getterSetters));
	assert(_getterSetters.size()==size+_setters.size());
	cout << "Size Getter = " << _getters.size() << endl;
	cout << "Size Setter = " << _setters.size() << endl;
	cout << "Size GetterSetter = " << _getterSetters.size() << endl; 
	
	return _getterSetters;
}        
