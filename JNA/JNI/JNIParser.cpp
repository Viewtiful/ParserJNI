#include "JNI/JNIParser.h"
#include <cstdlib>
#include <iostream>
#include "JNI/TypesDictionnary.h"
#include "JNI/OutputJNI.h"
#include "JNI/OutputJava.h"
#include <fstream>
#define JNIPARSER nsJNI::JNIParser
using namespace nsC;
using namespace std;
JNIPARSER::~JNIParser() {
}

int JNIPARSER::run(nsModules::Module::vector modules) 
{
	string filename = "ArcanaJNI";
	// Even if the filename ArcanaJNI is correct as a java type, we ensure that.
	
	filename = nsUtils::toJavaName(filename, false, false, true);
	TypesDictionnary *dico = new TypesDictionnary(filename);
	OutputJNI *jni = new OutputJNI(dico);
	OutputJava *java = new OutputJava(dico);

	// Get the java path from the command line parameters.
	string javaPath = nsUtils::Parameters::getInstance().getJavaSrcDir();
	// Creating the real path with the name of the file.
	string realPath = nsUtils::createJavaFileName(javaPath, "", filename);
	ofstream f(realPath.c_str());   //It seems well better now !
	ofstream f2("ArcanaJNI.c");
	java->addClassDefinition(f, filename);
	jni->addInclude(f2);
   	jni->addContextWrapper(f2);
	vector<Function*> gettersSetters;
		
	// Getting all the types from all the modules.
	for(size_t i = 0; i<modules.size(); ++i)
	{
		// If there is enums, adding them.
		if(modules[i].getEnums().size() > 0)
			dico->addEnums(f, modules[i].getEnums());
		// Same thing for structures, adding them after enums because structs
		// can use enum type.
		if(modules[i].getStructs().size() > 0)
			dico->addStruct(f, f2, modules[i].getStructs());
			
	}

	cout << "modules.size : " << modules.size() << endl;
//
	vector<nsJNI::Function*> saveFcts;
	vector<nsJNI::Function*> getSet;
	getSet = dico->getFcts();
	cout << "SaveFctsSize : " << saveFcts.size() << endl;
	cout << "JNIParser size : " << getSet.size() << endl;
	copy(getSet.begin(),getSet.end(),back_inserter(saveFcts));
	cout << "JNIParser size : " << getSet.size() << endl;
	
	cout << "SaveFctsSize : " << saveFcts.size() << endl;
	// Converting everything to JNI and Java.
	for(size_t i = 0; i<modules.size(); i++)
	{
		nsC::Callback::vector calls = modules[i].getCallbacks();
		nsC::Function::vector fcts = modules[i].getFunctions();
		cout << "Show Callbacks" << endl;
		for(size_t l = 0;l<calls.size();l++)
			cout << calls[l] << endl;
		for(size_t k = 0;k<fcts.size();k++)
		{
			nsJNI::Function *fct = new Function(dico);
			saveFcts.push_back(fct);
			fct->create(fcts[k]);
			java->convert(f,fct);
			jni->convert(f2,fct);

		}
		cout << "Java" << endl;
	cout << "1" << endl;
		cout << "Nom du module : " << modules[i].getModuleName() << endl;
		cout << "2" <<endl;
	}
	
	jni->addNativeFunctionTable(f2, filename, saveFcts);
	
	jni->generateJNIOnload(f2, filename);
	// Just for tests !
	f << "}" << endl;
	std::cout << "Nombre de Modules = " << modules.size() << std::endl; 

	delete jni;
	delete java;
	delete dico;
	return EXIT_SUCCESS;
}

#undef JNIPARSER
