/** @file
 *
 * Body for JNIParser
 */

#include <cstdlib>
#include <iostream>
#include "Utils/Output.h"
#include "Modules/Module.h"
#include "JNI/TypesDictionnary.h"
#include "JNA/SupportClass.h"
#include "JNA/Module.h"
#include "JNI/JNIParser.h"
#define JNIPARSER nsJNI::JNIParser

using nsJNA::SupportClass;
using namespace nsC;
#define JNIPARSER nsJNI::JNIParser

JNIPARSER::~JNIParser() {
}

int JNIPARSER::run(nsModules::Module::vector modules) 
{
	
    TypesDictionnary *dico = new TypesDictionnary();
    OutputCpp *cpp = new OutputCpp(dico);
    OutputJava *java = new OutputJava(dico);
    
    // Recupération des proto de fonctions 
    int k;
    for(int i = 0; i<modules.size(); i++)
	{
		string filename = modules[i].getModuleName() + ".java";
		filename[0] = toupper(filename[0]);
    	ofstream f(filename.c_str());   //faudra revoir ça !
    
    	cout << "C++" << endl;
    	cpp->convert(modules[i]);
    	cout << "Java" << endl;
    	java->convert(f,modules[i]);
    	nsC::Struct::vector structs = modules[i].getStructs();
    	cout << "Number structs" << structs.size() << endl;
    	dico->addStruct(structs);
    	nsC::Typedef::vector typedefs = modules[i].getTypedefs();
    	cout << "Number typedefs" << typedefs.size() << endl;
    }
    std::cout << "Nombre de Modules = " << modules.size() << std::endl; 
	return EXIT_SUCCESS;
}

#undef JNIPARSER
