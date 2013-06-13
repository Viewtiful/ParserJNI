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
    OutputCpp *cpp = new OutputCpp();
    OutputJava *java = new OutputJava();
    // Recupération des proto de fonctions 
    int k;
    for(int i = 0; i<modules.size(); i++)
    {
    	ofstream f("test.java");
    
    	cout << "C++" << endl;
    	cpp->convert(modules[i]);
    	cout << "Java" << endl;
    	java->convert(f,modules[i]);
    		
    }
    std::cout << "Nombre de Modules = " << modules.size() << std::endl; 
	return EXIT_SUCCESS;
}

#undef JNIPARSER

