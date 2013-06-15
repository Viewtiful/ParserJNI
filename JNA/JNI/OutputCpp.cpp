#include "JNI/OutputCpp.h"

using namespace std;
using namespace nsJNI;
OutputCpp::OutputCpp()
{
	addCppType("int","jint");
	addCppType("float","jfloat");
	addCppType("double","jdouble");
	addCppType("char","jbyte");
	addCppType("void","void");
	addCppType("short","jshort");
	addCppType("bool","jboolean");
	addCppType("long","jlong");	
}

OutputCpp::~OutputCpp() {
	outputFile.close();
}

void OutputCpp::addCppType(std::string inputType, std::string cppType)
{
	toCppType.insert(std::pair<std::string,std::string>(inputType,cppType) );	
}


std::string OutputCpp::getCppType(std::string inputType)
{
	return toCppType[inputType];

}


void OutputCpp::printPrototype(string typeRetour)
{
	outputFile << "JNIEXPORT " << getCppType(typeRetour) << " JNICALL ";
}

void OutputCpp::printName(string name)
{
	outputFile << name << "(";
}

void OutputCpp::printParameters(Param::vector& parameters)
{
	int i;
	for(i=0;i<parameters.size();i++)
	{
		printParameter(parameters[i]);
		if(i+1<parameters.size()) {
			outputFile << ",";
		}
	}	
	outputFile << ")\n";
}

void OutputCpp::printParameter(Param parameter)
{
	cout << getCppType(parameter.getType()) << " " << parameter.getName();
	outputFile << getCppType(parameter.getType()) << " " << parameter.getName();
}

void OutputCpp::addInclude() {
	cout << "here !!!" << endl;
	string include(
		"#include \"jni.h\"\n"
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

void OutputCpp::addContent() {
	outputFile << "\t printf(\"Hello\");";
}

void OutputCpp::convert(Module& module)
{
	string fileName = module.getModuleName() +  ".c";
	outputFile.open(fileName.c_str());

	//add include in the .c file
	addInclude();

	Function::vector fcts = module.getFunctions();
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
		outputFile << "\n}" << endl;
	}
}
