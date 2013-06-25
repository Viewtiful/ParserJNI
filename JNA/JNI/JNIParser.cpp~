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

   string filename = "ArcanaJNI";
   string extension = ".java";
   string fullName = filename + extension;
   filename = nsUtils::toJavaName(filename, false, false, true);
   ofstream f(fullName.c_str());   //faudra revoir ça (Un peu mieux)!

   java->addClassDefinition(f, filename);
	
    // Recupération des types
   for(int i = 0; i<modules.size(); ++i)
   {
   		dico->addStruct(modules[i].getStructs());
		   if(modules[i].getEnums().size() > 0)
			   dico->addEnums(f, modules[i].getEnums());
   }

   for(int i = 0; i<modules.size(); ++i)
	{
      	cout << "Java" << endl;
   		cout << "1" << endl;
   		java->convert(f,modules[i]);
   		cout << "2" <<endl;
   }
	f << "}" << endl;
    std::cout << "Nombre de Modules = " << modules.size() << std::endl; 
	return EXIT_SUCCESS;
}

#undef JNIPARSER
