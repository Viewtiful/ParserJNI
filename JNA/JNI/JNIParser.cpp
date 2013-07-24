#include "JNI/JNIParser.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#define JNIPARSER nsJNI::JNIParser
using namespace nsC;
using namespace std;
JNIPARSER::~JNIParser() {
	delete _jni;
	delete _java;
	delete _dico;
	delete _cm;
}

int JNIPARSER::run(nsModules::Module::vector modules) 
{
	vector<nsC::Enum> enums;
	vector<nsC::Struct> structs;

	string filename = "ArcanaJNI";
	// Even if the filename ArcanaJNI is correct as a java type, we ensure that.
	filename = nsUtils::toJavaName(filename, false, false, true);
	_dico = new TypesDictionnary(filename);	
	_jni = new OutputJNI(_dico);
	_java = new OutputJava(_dico);
	_cm = new Comments();

	// Get the java path from the command line parameters.
	string javaPath = nsUtils::Parameters::getInstance().getJavaSrcDir();
	// Creating the real path with the name of the file for Java.
	string realJavaPath = nsUtils::createJavaFileName(javaPath, "", filename);
	ofstream fileJava(realJavaPath.c_str());
	//Same thing for the JNI file.
	string realJNIPath = nsUtils::createJNIFileName(javaPath, filename);
	ofstream fileJNI(realJNIPath.c_str());

	//We add in the header of each file what is specific (include, class def..)
	_java->addClassDefinition(fileJava, filename);
	_jni->addInclude(fileJNI);
	_jni->addContextWrapper(fileJNI);

	// Getting all the types from all the modules.
	for(size_t i = 0; i<modules.size(); ++i)
	{
		if(containsCallback(modules[i])) {
			cout << "Module contains callback function, we ignore it." << endl;
			continue;
		}

		vector<nsC::Enum> moduleEnums = modules[i].getEnums();
		vector<nsC::Struct> moduleStructs = modules[i].getStructs();

		//We get all enums and structs from the modules.
		copy(moduleEnums.begin(), moduleEnums.end(), back_inserter(enums));
		copy(moduleStructs.begin(), moduleStructs.end(), back_inserter(structs));
		_dico->addTypedefs(modules[i].getTypedefs());

		moduleEnums.clear();
		moduleStructs.clear();	
	}
	//We had all enums/structures to the dictionnary.
	_dico->addEnums(fileJava, enums);
	_dico->addStruct(fileJava, fileJNI, structs);

	//We get all the functions from the header files for the future table
	//of native functions.
	vector<nsJNI::Function*> saveFcts;

	//We also get all functions created for the structure, like create,get,set..
	//We get them for the future table of native functions.
	vector<nsJNI::Function*> getSet;
	getSet = _dico->getFcts();

	//We copy in saved functions, all the functions from the structures.
	copy(getSet.begin(),getSet.end(),back_inserter(saveFcts));

	// Converting everything to JNI and Java.
	for(size_t i = 0; i<modules.size(); i++)
	{
		if(containsCallback(modules[i])) {
			cout << "Module contains callback function, we ignore it." << endl;
			continue;
		}

		//For each module, we get all the functions and we convert them to
		//Java and JNI.
		nsC::Function::vector fcts = modules[i].getFunctions();
		cout << "Avant le for" << endl;
		for(size_t k = 0;k<fcts.size();k++)
		{
			nsC::Function current = fcts[k];
			if(!current.isVariadic())
			{
				fileJava << _cm->transformToJavadoc(current) << endl;
				nsJNI::Function *fct = new Function(_dico);
				cout << "Comments function : "<< current.getName() << current.getComment() << endl;
				saveFcts.push_back(fct);
				fct->create(current);
				_java->convert(fileJava,fct);
				_jni->convert(fileJNI,fct);
			}
			else
				cout << "Variadic Function : " << current.getName() << endl;

		}
		cout << "Après le for" << endl;
		fcts.clear();
	}

	//We then, generate the table of native functions. This is used for linking
	//the Java part and the JNI part.
	_jni->addNativeFunctionTable(fileJNI, filename, saveFcts);

	//This part generate the function JNI_LOAD. This is the first function that
	//is checked by the VM.
	_jni->generateJNIOnload(fileJNI, filename);

	// Just for tests !
	fileJava << "}" << endl;
	std::cout << "Nombre de Modules = " << modules.size() << std::endl; 

	fileJNI.close();
	fileJava.close();

	for(vector<nsJNI::Function*>::const_iterator it = saveFcts.begin(); it != saveFcts.end(); it++)
		delete *it;

	saveFcts.clear();
	getSet.clear();
	enums.clear();
	structs.clear();

	return EXIT_SUCCESS;
}

bool JNIPARSER::containsCallback(nsModules::Module module) {
	return (module.getCallbacks().size() > 0)? true: false;
}

#undef JNIPARSER
