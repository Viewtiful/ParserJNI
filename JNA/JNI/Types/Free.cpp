#include "JNI/Types/Free.h"

using namespace nsJNI;
using namespace nsUtils;

Free::Free(string structName, TypesDictionnary *dictionnary) : Function(dictionnary)
{

	_structName = structName;

	//JNI function name.
	_name = "gen_jni_" +_structName + "_" + "free";
	//Add an argument for the pointer to the structure.
	_args.push_back(new nsJNI::Param("long","mInternal"));
	_returnType = "void";
}

Free::~Free()
{
}

void Free::printPrototypeJNI(ofstream &f)
{
	string returnType;
	returnType = _dictionnary->convertJNI(_returnType);
	f << "\t" << "JNIEXPORT " << returnType << " JNICALL " << "JNI_" << _name;
}

void Free::printContentJNI(ofstream &f)
{
	//De-alloc the structure allocated with create().
	f << "{\n\n";
	string body = 
		"\t\t%CLASSNAME% *C_ctx = (%CLASSNAME% *)((contextWrapper *)mInternal)->ctxRef;\n"
		"\t\tfree(C_ctx);\n"
		"\t\tfree((contextWrapper *)mInternal);\n"
		"\t}\n\n";

	stringReplace(body,"CLASSNAME",_structName);

	f << body;
}

string Free::call()
{
	//JNI argument.
	return _name + "(" + _args[0]->getName()+ ");"; 
}
