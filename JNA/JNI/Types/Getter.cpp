#include "JNI/Types/Getter.h"

using namespace nsJNI;
using namespace nsUtils;
Getter::Getter(nsC::Param& param, string structName, TypesDictionnary *dictionnary) : Function(dictionnary)
{

	_structName = structName;
   _fieldName = param.getName();
	create(param);
}

Getter::~Getter()
{


}
			

void Getter::create(nsC::Param& param)
{
	_name = "gen_jni_" +_structName + "_" + "get" + "_" +param.getName();
	_args.push_back(new nsJNI::Param("long","mInternal"));
	_returnType = param.getCType();
}

void Getter::printPrototypeJNI(ofstream &f)
{
	string returnType;
	returnType = _dictionnary->convertJNI(_returnType);
	if(returnType == "jobject")
		returnType = "jint";
	f << "\t" << "JNIEXPORT " << returnType << " JNICALL " << "JNI_" << _name;
}

void Getter::printContentJNI(ofstream &f)
{
	f << "{\n\n";
	string structure("\t\t%CLASSNAME% *C_ctx = (%CLASSNAME% *)mInternal;\n"
      "\t\treturn C_ctx->%ATTRIBUTENAME%;\n");
	stringReplace(structure,"CLASSNAME",_structName);
	stringReplace(structure,"ATTRIBUTENAME",_fieldName);
	f << structure;
	f << "\t}\n\n";
}

void Getter::prepareCall(ofstream &f)
{




}

string Getter::call()
{
	return _name + "(" + _args[0]->getName()+ ");"; 
}
