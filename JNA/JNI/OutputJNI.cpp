#include "JNI/OutputJNI.h"
#include "Utils/Utils.h"

using namespace std;
using nsUtils::stringReplace;
using namespace nsJNI;
OutputJNI::OutputJNI(TypesDictionnary *dictionnary)
{
	_dictionnary = dictionnary;
}

OutputJNI::~OutputJNI() {
}

std::string OutputJNI::getJNIType(std::string inputType) {
	return _dictionnary->convertJNI(inputType);
}

string OutputJNI::getVMSignature(string inputType) {
	return _dictionnary->convertVM(inputType);
}

void OutputJNI::addInclude(ofstream &f) {
	string include(
			"#include <jni.h>\n"
			"#include <stdio.h>\n"
			"#include <ktb/err.h>\n"
			"#include <ktb.h>\n"
			"#include <ktb/prng.h>\n"
			"#include <ktb/prng_custom.h>\n"
			"#include <ktb/cipher.h>\n"
			"#include <ktb/keys.h>\n"
			"#include <ktb/hash.h>\n"
			"#include <ktb/sign.h>\n"
			"#include <ktb/kdf.h>\n"
			"#include <ktb/curves.h>\n"
			"#include <kep/kep.h>\n"
			"#include <kep/kep_dh.h>\n"
			"#include <kep/kep_dhpass.h>\n"
			"#include <kep/kep_sts.h>\n\n\n"
			);

	f << include;
}

void OutputJNI::addContextWrapper(ofstream &f) {
	string contextWrapper (
			"\ttypedef struct\n"
			"\t{\n"
			"\t\tvoid *ctxRef;\n"
			"\t\tJNIEnv *env;\n"
			"\t} contextWrapper;\n\n"
			);

	f << contextWrapper;
}

void OutputJNI::addNativeFunctionTable(ofstream &f, string filename, vector<nsJNI::Function*> fcts) {

	string structure (
			"static JNINativeMethod method_table[] = {\n"
			"%METHODLIST%"
			"};\n\n"
			"%TABLESIZE%"
			);

	string methodList;

	//writing link between the Java function and the JNI one for each function.
	for(size_t k = 0; k < fcts.size(); k++) 
	{
		string method = "\t{\"%METHODNAME%\", \"(%VMSIGNATURE%)%VMRETURNTYPE%\", (void *)JNI_%METHODNAME%}";
		string VMSignature = "";

		//Writing VM signature param corresponding to the Java function.
		vector<nsJNI::Param *> prms = fcts[k]->getArgs();
		for(size_t i = 0; i < prms.size(); ++i) {
			if(!(prms[i]->getType()=="size_t *"))
				VMSignature += _dictionnary->convertVM(prms[i]->getType()); 
		}

		//VM signature of the return type.
		string typeRetour = fcts[k]->getReturnType();
		string typeRetour2 = _dictionnary->convertVM(typeRetour);
		if(typeRetour2 == "")
			typeRetour2 = "L" + filename + "$" + typeRetour + ";"; 

		prms.clear();

		stringReplace(method, "METHODNAME", fcts[k]->getName());   
		stringReplace(method, "VMSIGNATURE", VMSignature);  
		stringReplace(method, "VMRETURNTYPE", typeRetour2);  

		if(fcts.size() > 1 && k < fcts.size() - 1)
			method += ",\n"; 
		else 
			method += "\n";  

		methodList += method;
	}

	string tableSize = "static int method_table_size = sizeof(method_table) / sizeof(method_table[0]);\n\n";
	stringReplace(structure, "METHODLIST", methodList);  
	stringReplace(structure, "TABLESIZE", tableSize);  

	f << structure;

}

void OutputJNI::convert(ofstream &f,Function *fct)
{
	fct->convertJNI(f);
}

void OutputJNI::generateJNIOnload(ofstream &f, string filename) {
	string content(
			"jint JNI_OnLoad (JavaVM *vm, void *reserved) {\n"
			"\tJNIEnv *env;\n"
			"\tif ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_6) != JNI_OK) {\n"
			"\t\t\treturn JNI_ERR;\n"
			"\t} else {\n"
			"\t\tjclass class = (*env)->FindClass(env, \"%Print%\");\n"
			"\t\tif (class) {\n"
			"\t\t\tjint ret = (*env)->RegisterNatives(env, class, method_table, method_table_size);\n"
			"\t\t\t(*env)->DeleteLocalRef(env, class);\n"
			"\t\t\treturn ret == 0 ? JNI_VERSION_1_6 : JNI_ERR;\n"		
			"\t\t} else {\n"
			"\t\t\treturn JNI_ERR;\n"
			"\t\t}\n"
			"\t}\n"
			"}\n"
			);
	filename[0] = toupper(filename[0]);
	stringReplace(content, "Print", filename);
	f << content << endl;
}
