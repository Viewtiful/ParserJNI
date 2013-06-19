#include "JNI/OutputJNI.h"
#include "Utils/Utils.h"

using namespace std;
using nsUtils::stringReplace;
using namespace nsJNI;
OutputJNI::OutputJNI(TypesDictionnary *dictionnary)
{
	this->dictionnary = dictionnary;
}

OutputJNI::~OutputJNI() {
	outputFile.close();
}

std::string OutputJNI::getJNIType(std::string inputType) {
	return dictionnary->convertJNI(inputType);
}

string OutputJNI::getVMSignature(string inputType) {
	return dictionnary->convertVM(inputType);
}

void OutputJNI::printPrototype(string typeRetour)
{
	string returnType = getJNIType(typeRetour);
	if(returnType  == "")  //TODO revoir ça !
		returnType = "jobject";   

	outputFile << "JNIEXPORT " << returnType << " JNICALL ";
}

void OutputJNI::printName(string name)
{
	outputFile << name << "(";
}

void OutputJNI::printParameters(Param::vector& parameters)
{
	int i;
	outputFile << "JNIEnv *env, jobject o ";
	for(i=0;i<parameters.size();i++)
	{
		outputFile << ", ";
		printParameter(parameters[i]);
	}	
	outputFile << ")\n";
}

void OutputJNI::printParameter(Param parameter)
{
	outputFile << getJNIType(parameter.getType()) << " " << parameter.getName();
}

void OutputJNI::addInclude() {
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
			"#include <kep/kep_sts.h>\n\n\n"
			);

	outputFile << include;
}

void OutputJNI::addContent() {   //TODO faudra revoir ça !
	outputFile << "\t printf(\"Hello\");";
}

void OutputJNI::addFunctionPrototype(Function::vector fcts) {
	for(int k = 0;k<fcts.size();k++)
	{   
		string typeRetour = fcts[k].getReturnType();
		string name = fcts[k].getName();
		Param::vector parameters = fcts[k].getParamList();
		printPrototype(typeRetour);
		printName(name);
		printParameters(parameters);
		outputFile << "{\n";
		addContent();
		outputFile << "\n}\n\n";
	}
}

void OutputJNI::addNativeFunctionTable(Function::vector fcts, string fileName) {
	outputFile << "static JNINativeMethod method_table[] = {\n";
	for(int k = 0; k < fcts.size(); k++) {
		outputFile << "\t{ \"" << fcts[k].getName() << "\", \"";
		Param::vector parameters = fcts[k].getParamList();
		if(parameters.size() == 0)
			outputFile << "()";
		else {
			outputFile << "(";
			for(int i = 0; i < parameters.size(); ++i) {
				outputFile << getVMSignature(parameters[i].getType());
			}
			outputFile << ")";
		}
		string typeRetour = fcts[k].getReturnType();
		string typeRetour2 = getVMSignature(typeRetour);
		if(typeRetour2 == "")
			typeRetour2 = "L" + fileName + "$" + typeRetour + ";"; 
		outputFile << typeRetour2;

		outputFile << "\", (void *)" << fcts[k].getName() << " }";
		if(fcts.size() > 1 && k < fcts.size() - 1)
			outputFile << ",\n";
	}
	outputFile << "};\n\n";

	outputFile << "static int method_table_size = sizeof(method_table) / sizeof(method_table[0]);\n\n";

}

void OutputJNI::convert(Module& module)
{
	string fileName = module.getModuleName() +  ".c";
	outputFile.open(fileName.c_str());
	fileName = module.getModuleName();
	fileName[0] = toupper(fileName[0]);

	//add include in the .c file
	addInclude();

	addFunctionPrototype(module.getFunctions());
	addNativeFunctionTable(module.getFunctions(), fileName);

	generateJNIOnload(fileName);

	outputFile.close();
}

void OutputJNI::generateJNIOnload(string filename) {
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
	outputFile << content << endl;
}
