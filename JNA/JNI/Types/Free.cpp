#include "JNI/Types/Free.h"

using namespace nsJNI;
using namespace nsUtils;

Free::Free(string structName, TypesDictionnary *dictionnary) : Function(dictionnary)
{

	_structName = structName;
	create();
}

Free::~Free()
{


}
			

void Free::create()
{
   //JNI function name.
	_name = "gen_jni_" +_structName + "_" + "free";
   //add an argument for the pointer to the structure.
	_args.push_back(new nsJNI::Param("long","mInternal"));
	_returnType = "void";
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
            "\t\t%CLASSNAME% *C_ctx = (%CLASSNAME% *)mInternal;\n"
            "\t\tfree(C_ctx);\n"
            "\t}\n\n";

   stringReplace(body,"CLASSNAME",_structName);

	f << body;
}

void Free::prepareCall(ofstream &f)
{
}

string Free::call()
{
   //JNI argument.
	return _name + "(" + _args[0]->getName()+ ");"; 
}
