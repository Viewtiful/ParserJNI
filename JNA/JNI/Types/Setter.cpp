#include "JNI/Types/Setter.h"

using namespace nsJNI;
using namespace nsUtils;

Setter::Setter(nsC::Param& param, string structName, TypesDictionnary *dictionnary) : Function(dictionnary)
{
	_structName = structName;
	create(param);
}

Setter::~Setter()
{
}		

void Setter::create(nsC::Param& param)
{
	//JNI function name
	_name = "gen_jni_" +_structName + "_" + "set" + "_" +param.getName();
	//Add an argument for the pointer to the structure.
	_args.push_back(new nsJNI::Param("long", "mInternal"));

	//If the parameter is const void * or void *, this is an array. Otherwise
	//this is the normal type.
	if( param.getCType() == "const void *" || param.getCType() == "void *") {  
		_args.push_back(new nsJNI::Param(param.getCType() + "Array", param.getName()));
	}
	else {
		_args.push_back(new nsJNI::Param(param.getCType(), param.getName()));
	}
	_returnType = "void";
}

void Setter::printPrototypeJNI(ofstream &f)
{
	string returnType;
	returnType = _dictionnary->convertJNI(_returnType);
	f << "\t" << "JNIEXPORT " << returnType << " JNICALL " << "JNI_" << _name;
}

void Setter::printContentJNI(ofstream &f)
{
	Type * type = _dictionnary->getType(_args[1]->getType());
   string returnType = _dictionnary->convertJNI(_args[1]->getType());

	//Write the Java elements in the C variables of the structure. 
	string body = "{\n\n"
      "\t\t%CLASSNAME% *C_ctx;\n"
		"\t\tif(mInternal != 0)\n"
		"\t\t\tC_ctx = (%CLASSNAME% *)((contextWrapper *)mInternal)->ctxRef;\n"
		"\t\telse\n"
		"\t\t\tC_ctx = NULL;\n"
		"%WRITEFIELD%"
      "\t}\n\n";
	string writeField;

	//If its an jobject there is an enum or a struct. We do the work to pass it
	//to the C variable.
	if(returnType == "jobject")
	{
		writeField = "\t\tjclass enm_%ATTRIBUTENAME%;\n"
			"\t\tenm_%ATTRIBUTENAME% = (*env)->GetObjectClass(env, %ATTRIBUTENAME%);\n"
			"\t\tjmethodID get_%ATTRIBUTENAME% = (*env)->GetMethodID(env, enm_%ATTRIBUTENAME%, \"getValue\", \"()I\");\n"
			"\t\tjint %ATTRIBUTENAME%_value = (*env)->CallIntMethod(env, %ATTRIBUTENAME%, get_%ATTRIBUTENAME%);\n"
			"\t\t%Type% C_%ATTRIBUTENAME% = (%Type%)%ATTRIBUTENAME%_value;\n"
			"\t\tC_ctx->%ATTRIBUTENAME% = C_%ATTRIBUTENAME%;\n";
		stringReplace(writeField, "Type", _args[1]->getType());
	}
	//It's a pointer.
	else if( returnType == "jlong" && !(type->isNativeType())) {
		writeField = "\t\tC_ctx->%ATTRIBUTENAME% = (%CTYPE%)((contextWrapper *)%ATTRIBUTENAME%)->ctxRef;\n"
			"\t\t((contextWrapper *)%ATTRIBUTENAME%)->env = env;\n";
		stringReplace(writeField, "FIELDNAME", _args[1]->getName());
		stringReplace(writeField, "CTYPE", _args[1]->getType());
	}
	//It's an array.
	else if( returnType == "jbyteArray") {
		writeField = "\t\tjbyte * C_%FIELDNAME%;\n"
			"\t\tsize_t C_%FIELDNAME%_length = (*env)->GetArrayLength(env, %FIELDNAME%);\n"
			"\t\tC_%FIELDNAME% = (jbyte *)malloc(C_%FIELDNAME%_length);\n"
			"\t\tC_%FIELDNAME% = (*env)->GetByteArrayElements(env, %FIELDNAME%, NULL);\n"
			"\t\tC_ctx->%ATTRIBUTENAME% = C_%FIELDNAME%;\n";
		stringReplace(writeField, "FIELDNAME", _args[1]->getName());
		stringReplace(writeField, "CTYPE", _args[1]->getType());
	}
	//It's a normal type.
	else
	{
		writeField = "\t\tC_ctx->%ATTRIBUTENAME% = %FIELDNAME%;\n";
		stringReplace(writeField, "FIELDNAME", _args[1]->getName());
	}

	stringReplace(writeField, "ATTRIBUTENAME", _args[1]->getName());
	stringReplace(body, "CLASSNAME", _structName);
	stringReplace(body, "WRITEFIELD", writeField);

	f << body;
}

string Setter::call()
{
	//JNI argument.
	return _name + "(" + _args[0]->getName()+ ");"; 
}
