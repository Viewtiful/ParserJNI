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
	_name = "gen_jni_" +_structName + "_" + "set" + "_" +param.getName();
	_args.push_back(new nsJNI::Param("long", "mInternal"));
	_args.push_back(new nsJNI::Param(param.getCType(), param.getName()));
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
	f << "{\n\n";
	string body = "\t\t%CLASSNAME% *C_ctx = (%CLASSNAME% *)mInternal;\n"
      "%WRITEFIELD%";
     string writeField;
	if(_dictionnary->convertJNI(_args[1]->getType())=="jobject")
	{
		writeField = "\t\tjclass enm_%ATTRIBUTENAME%;\n"
		"\t\tenm_%ATTRIBUTENAME% = (*env)->GetObjectClass(env, %ATTRIBUTENAME%);\n"
		"\t\tjmethodID get_%ATTRIBUTENAME% = (*env)->GetMethodID(env, enm_%ATTRIBUTENAME%, \"getValue\", \"()I\");\n"
		"\t\tjint %ATTRIBUTENAME%_value = (*env)->CallIntMethod(env, %ATTRIBUTENAME%, get_%ATTRIBUTENAME%);\n"
		"\t\t%Type% C_%ATTRIBUTENAME% = (%Type%)%ATTRIBUTENAME%_value;\n"
		"\t\tC_ctx->%ATTRIBUTENAME% = C_%ATTRIBUTENAME%;\n";
		stringReplace(writeField, "Type", _args[1]->getType());
	}
	else
	{
		writeField = "\t\tC_ctx->%ATTRIBUTENAME% = %FIELDNAME%;\n";
	   	stringReplace(writeField, "FIELDNAME", _args[1]->getName());
	}
	
	stringReplace(writeField, "ATTRIBUTENAME", _args[1]->getName());
	stringReplace(body, "CLASSNAME", _structName);
	stringReplace(body, "WRITEFIELD", writeField);

	f << body << "\t}\n\n";
}

void Setter::prepareCall(ofstream &f)
{




}

string Setter::call()
{
	return _name + "(" + _args[0]->getName()+ ");"; 
}
