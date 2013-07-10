#include "JNI/JNIParser.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#define JNIPARSER nsJNI::JNIParser
using namespace nsC;
using namespace std;

JNIPARSER::~JNIParser() {
	delete jni;
	delete java;
	delete dico;
}

int JNIPARSER::run(nsModules::Module::vector modules) 
{
	vector<nsC::Enum> enums;
	vector<nsC::Struct> structs;

	string filename = "ArcanaJNI";
	// Even if the filename ArcanaJNI is correct as a java type, we ensure that.
	filename = nsUtils::toJavaName(filename, false, false, true);
	dico = new TypesDictionnary(filename);	
	jni = new OutputJNI(dico);
	java = new OutputJava(dico);

	// Get the java path from the command line parameters.
	string javaPath = nsUtils::Parameters::getInstance().getJavaSrcDir();
	// Creating the real path with the name of the file for Java.
	string realJavaPath = nsUtils::createJavaFileName(javaPath, "", filename);
	ofstream fileJava(realJavaPath.c_str());
	//Same thing for the JNI file.
	string realJNIPath = nsUtils::createJNIFileName(javaPath, filename);
	ofstream fileJNI(realJNIPath.c_str());

	//We add in the header of each file what is specific (include, class def..)
	java->addClassDefinition(fileJava, filename);
	jni->addInclude(fileJNI);
	jni->addContextWrapper(fileJNI);
		
	// Getting all the types from all the modules.
	for(size_t i = 0; i<modules.size(); ++i)
	{
		vector<nsC::Enum> moduleEnums = modules[i].getEnums();
		vector<nsC::Struct> moduleStructs = modules[i].getStructs();
	
		//We get all enums and structs from the modules.
		copy(moduleEnums.begin(), moduleEnums.end(), back_inserter(enums));
		copy(moduleStructs.begin(), moduleStructs.end(), back_inserter(structs));
		
		moduleEnums.clear();
		moduleStructs.clear();	
	}
	//We had all enums/structures to the dictionnary.
	dico->addEnums(fileJava, enums);
	dico->addStruct(fileJava, fileJNI, structs);
	//We get all the functions from the header files for the future table
	//of native functions.
	vector<nsJNI::Function*> saveFcts;

	//We also get all functions created for the structure, like create,get,set..
	//We get them for the future table of native functions.
	vector<nsJNI::Function*> getSet;
	getSet = dico->getFcts();

	//We copy in saved functions, all the functions from the structures.
	copy(getSet.begin(),getSet.end(),back_inserter(saveFcts));
	
	// Converting everything to JNI and Java.
	for(size_t i = 0; i<modules.size(); i++)
	{
		//For each module, we get all the functions and we convert them to
		//Java and JNI.
		nsC::Function::vector fcts = modules[i].getFunctions();

		for(size_t k = 0;k<fcts.size();k++)
		{
			cout << "Commentaires = " << fcts[k].getComment() << endl;
			nsJNI::Function *fct = new Function(dico);
			saveFcts.push_back(fct);
			fct->create(fcts[k]);
			java->convert(fileJava,fct);
			jni->convert(fileJNI,fct);

		}
		fcts.clear();
	}
	
	//We then, generate the table of native functions. This is used for linking
	//the Java part and the JNI part.
	jni->addNativeFunctionTable(fileJNI, filename, saveFcts);

	//This part generate the function JNI_LOAD. This is the first function that
	//is checked by the VM.
	jni->generateJNIOnload(fileJNI, filename);

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

#undef JNIPARSER
