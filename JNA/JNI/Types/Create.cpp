#include "JNI/Types/Create.h"

using namespace nsJNI;
using namespace nsUtils;

Create::Create(string structName, TypesDictionnary *dictionnary) : Function(dictionnary)
{

	_structName = structName;
	create();
}

Create::~Create()
{


}
			

void Create::create()
{
	_name = "gen_jni_" +_structName + "_" + "create";
	_returnType = "long";
}

void Create::printPrototypeJNI(ofstream &f)
{
	string returnType;
	returnType = _dictionnary->convertJNI(_returnType);
	f << "\t" << "JNIEXPORT " << returnType << " JNICALL " << "JNI_" << _name;
}

void Create::printContentJNI(ofstream &f)
{
	f << "{\n\n";
   string body = 
         "\t\t%CLASSNAME% *C_ctx = (%CLASSNAME% *)malloc(sizeof(%CLASSNAME%));\n"
         "\t\treturn C_ctx;\n"
         "\t}\n\n";

	stringReplace(body,"CLASSNAME",_structName);

	f << body;
}

void Create::prepareCall(ofstream &f)
{




}

string Create::call()
{
	return _name + "(" + _args[0]->getName()+ ");"; 
}