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
	_outputFile.close();
}

std::string OutputJNI::getJNIType(std::string inputType) {
	return _dictionnary->convertJNI(inputType);
}

string OutputJNI::getVMSignature(string inputType) {
	return _dictionnary->convertVM(inputType);
}
/*
void OutputJNI::printPrototype(string typeRetour)
{
	string returnType = getJNIType(typeRetour);
	if(returnType  == "")  //TODO revoir ça !
		returnType = "jobject";   

	_outputFile << "JNIEXPORT " << returnType << " JNICALL ";
}
*/

/*
void OutputJNI::printName(string name)
{
	_outputFile << name << "(";
}
*/

/*
void OutputJNI::printParameters(Param::vector& parameters)
{
	int i;
	_outputFile << "JNIEnv *env, jobject o ";
	for(i=0;i<parameters.size();i++)
	{
		_outputFile << ", ";
		printParameter(parameters[i]);
	}	
	_outputFile << ")\n";
}
*/

/*
void OutputJNI::printParameter(Param parameter)
{
	_outputFile << getJNIType(parameter.getType()) << " " << parameter.getName();
}
*/

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
			"#include <kep/kep_sts.h>\n\n\n"
			);

	f << include;
}


/*
void OutputJNI::addFunctionPrototype(Function::vector fcts) {
	for(int k = 0;k<fcts.size();k++)
	{   
		string typeRetour = fcts[k].getReturnType();
		string name = fcts[k].getName();
		Param::vector parameters = fcts[k].getParamList();
		printPrototype(typeRetour);
		printName(name);
		printParameters(parameters);
		_outputFile << "{\n";
		addContent();
		_outputFile << "\n}\n\n";
	}
}
*/
void OutputJNI::addNativeFunctionTable(ofstream &f, string filename, vector<nsJNI::Function*> fcts) {
	f << "static JNINativeMethod method_table[] = {\n";
	for(int k = 0; k < fcts.size(); k++) {
		f << "\t{ \"" << fcts[k]->getName() << "\", \"";
		vector<nsJNI::Param *> prms = fcts[k]->getArgs();

		if(prms.size() == 0)
			f << "()";
		else {
			f << "(";
			for(int i = 0; i < prms.size(); ++i) {
				if(!(prms[i]->getType()=="size_t *"))
					f << _dictionnary->convertVM(prms[i]->getType()); 
			}
			f << ")";
		}
		string typeRetour = fcts[k]->getReturnType();
		string typeRetour2 = _dictionnary->convertVM(typeRetour);
		if(typeRetour2 == "")
			typeRetour2 = "L" + filename + "$" + typeRetour + ";"; 
		f << typeRetour2;

		f << "\", (void *)" << "JNI_" << fcts[k]->getName() << " }";
		if(fcts.size() > 1 && k < fcts.size() - 1)
			f << ",\n";
	}
	f << "};\n\n";

	f << "static int method_table_size = sizeof(method_table) / sizeof(method_table[0]);\n\n";

}
/*
void OutputJNI::convert(Module& module)
{
	string fileName = module.getModuleName() +  ".c";
	_outputFile.open(fileName.c_str());
	fileName = module.getModuleName();
	fileName = nsUtils::toJavaName(fileName, false, false, true);

	//add include in the .c file
	addInclude();

	addFunctionPrototype(module.getFunctions());
	addNativeFunctionTable(module.getFunctions(), fileName);

	generateJNIOnload(fileName);

	_outputFile.close();
}
*/

void OutputJNI::convert(ofstream &f,Function *fct)
{
	cout << "2.4" << endl;
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
