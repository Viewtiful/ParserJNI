/** @file
 *
 * Body for JNIParser
 */

#include <cstdlib>
#include <iostream>
#include "Utils/Output.h"
#include "Utils/Utils.h"
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
    OutputJNI *jni = new OutputJNI(dico);
    OutputJava *java = new OutputJava(dico);
    
    // Recupération des proto de fonctions 
   for(int i = 0; i<modules.size(); ++i)
	{
   		string filename = modules[i].getModuleName() + ".java";
   		filename = nsUtils::toJavaName(filename, false, false, true);
   		ofstream f(filename.c_str());   //faudra revoir ça (Un peu mieux)!
    
   		dico->addStruct(modules[i].getStructs());
   		cout << "C++" << endl;
   		
   		jni->convert(modules[i]);
   		cout << "Java" << endl;
   		java->convert(f,modules[i]);
   		
    }
    std::cout << "Nombre de Modules = " << modules.size() << std::endl; 
	return EXIT_SUCCESS;
}

#undef JNIPARSER
