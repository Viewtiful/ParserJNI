#define STRUCT nsJNI::STRUCT
#include "JNI/Types/Struct.h"
#include "Utils/Utils.h"
#include "JNI/Types/Getter.h"
#include "JNI/Types/Setter.h"
#include "JNI/Types/Create.h"
#include "JNI/Types/Free.h"
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
	_createFunction->convertJNI(f);
	_freeFunction->convertJNI(f);
	_structSize->convertJNI(f);

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
			"\t\tlong struct_size;\n"
			"\t\tprivate AddressWrapper mInternal;\n\n"
			"%CONSTRUCTOR%"
			"%FINALIZE%"
			"%MINTERNAL%"
			"%WRITE%"
			"%READ%"
			"\t}\n\n"
			);

	_createFunction = new Create(_javaType, _dictionnary);

	_freeFunction = new Free(_javaType, _dictionnary);

	nsC::Param::vector fields = _cStruct.getFields();
	string fieldsTemp;

	_structSize = new Getter("struct_size",_javaType, _dictionnary, true);
	_structSize->convertJava(f);

	for(size_t i =0; i<fields.size(); i++) {
		string field("\t\tpublic %VALUE1% %VALUE2%;\n");
		if(fields[i].getCType() == "const void *" || fields[i].getCType() == "void *") {
			stringReplace(field, "VALUE1", _dictionnary->convertJava(fields[i].getCType() + "Array"));
		}
		else {
			stringReplace(field, "VALUE1", _dictionnary->convertJava(fields[i].getCType()));
		}
		stringReplace(field, "VALUE2", fields[i].getName());

		Getter *g = new Getter(fields[i],_javaType, _dictionnary, false);
		_getters.push_back(g);
		Setter *s = new Setter(fields[i], _javaType,  _dictionnary);
		_setters.push_back(s);
		fieldsTemp += field;
	}

	stringReplace(structure, "CLASSNAME", _cStruct.getTypedef());
	stringReplace(structure, "FIELDS", fieldsTemp);
	stringReplace(structure, "CONSTRUCTOR", generateConstructor());
	stringReplace(structure, "FINALIZE", generateFinalize());
	stringReplace(structure, "WRITE", generateWrite());
	stringReplace(structure, "READ", generateRead());

	string mInternal (
			"\t\tAddressWrapper getMInternal() {\n"
			"\t\t\treturn mInternal;\n"
			"\t\t}\n\n"
			);
	stringReplace(structure, "MINTERNAL", mInternal);
	f << structure;

	//Write Function create/free/getters/setters for the struct.
	_createFunction->convertJava(f);

	_freeFunction->convertJava(f);

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
			"\t\t\tmInternal = new AddressWrapper();\n"
			"\t\t\tmInternal.setAddress(gen_jni_%CLASSNAME%_create());\n"
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
			"\t\t\tgen_jni_%CLASSNAME%_free(mInternal.getAddress());\n"
			"\t\t\tmInternal = null;\n"
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
		string field("\t\t\tgen_jni_%CLASSNAME%_set_%VALUE%(mInternal.getAddress(), %VALUE%);\n");

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
	fieldsTemp += "\t\t\tstruct_size = gen_jni_%CLASSNAME%_get_struct_size();\n";

	stringReplace(fieldsTemp, "CLASSNAME", _cStruct.getTypedef());
	stringReplace(read, "FIELDS", fieldsTemp);

	return read;
}

Struct::~Struct() {
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
	return "C_" + varName;
}

void Struct::getReturnValue(ofstream& f)
{
}

vector<Function*> Struct::getGetterSetters()
{
	_getterSetters.push_back(_createFunction);
	_getterSetters.push_back(_freeFunction);
	_getterSetters.push_back(_structSize);

	int size = _getterSetters.size();
	copy(_getters.begin(),_getters.end(),back_inserter(_getterSetters));
	assert(_getterSetters.size()==size+_getters.size());

	size = _getterSetters.size();
	copy(_setters.begin(),_setters.end(),back_inserter(_getterSetters));
	assert(_getterSetters.size()==size+_setters.size());

	return _getterSetters;
}        
