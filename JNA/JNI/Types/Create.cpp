#include "JNI/Types/Create.h"

using namespace nsJNI;
using namespace nsUtils;

Create::Create(string structName, TypesDictionnary *dictionnary) : Function(dictionnary)
{

	_structName = structName;

	//JNI function name.
	_name = "gen_jni_" +_structName + "_" + "create";

	//Return type of the function in C.
	_returnType = "long";
}

Create::~Create()
{
}

void Create::printPrototypeJNI(ofstream &f)
{
	string returnType;
	//Convert the return type to JNI.
	returnType = _dictionnary->convertJNI(_returnType);
	f << "\t" << "JNIEXPORT " << returnType << " JNICALL " << "JNI_" << _name;
}

void Create::printContentJNI(ofstream &f)
{
	//Allocate memory for the structure.
	f << "{\n\n";
	string body = 
		"\t\tcontextWrapper *ctxWrp = (contextWrapper *)malloc(sizeof(contextWrapper));\n"
		"\t\t%CLASSNAME% *C_ctx = (%CLASSNAME% *)malloc(sizeof(%CLASSNAME%));\n"
		"\t\tctxWrp->ctxRef = C_ctx;\n"
		"\t\treturn ctxWrp;\n"
		"\t}\n\n";

	stringReplace(body,"CLASSNAME",_structName);

	f << body;
}

string Create::call()
{
	//Param of the JNI function.
	return _name + "(" + _args[0]->getName()+ ");"; 
}
