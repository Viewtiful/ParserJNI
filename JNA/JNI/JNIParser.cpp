/** @file
 *
 * Body for JNIParser
 */

#include <cstdlib>
#include <iostream>
#include "Utils/Output.h"
#include "Utils/Parameters.h"
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

	// Get the java path from the command line parameters.
	string javaPath = nsUtils::Parameters::getInstance().getJavaSrcDir();
	string filename = "ArcanaJNI";
	// Creating the real path with the name of the file.
	string realPath = nsUtils::createJavaFileName(javaPath, "", filename);
	// Even if the filename ArcanaJNI is correct as a java type, we ensure that.
	filename = nsUtils::toJavaName(filename, false, false, true);
	ofstream f(realPath.c_str());   //It seems well better now !

	java->addClassDefinition(f, filename);

	// Getting all the types from all the modules.
	for(int i = 0; i<modules.size(); ++i)
	{
		// If there is enums, adding them.
		if(modules[i].getEnums().size() > 0)
			dico->addEnums(f, modules[i].getEnums());
		// Same thing for structures, adding them after enums because structs
		// can use enum type.
		if(modules[i].getStructs().size() > 0)
			dico->addStruct(f, modules[i].getStructs());
	}

	// Converting everything to JNI and Java.
	for(int i = 0; i<modules.size(); ++i)
	{
		cout << "Java" << endl;
		cout << "1" << endl;
		java->convert(f,modules[i]);
		cout << "2" <<endl;
	}

	// Just for tests !
	f << "}" << endl;
	std::cout << "Nombre de Modules = " << modules.size() << std::endl; 
	return EXIT_SUCCESS;
}

#undef JNIPARSER
