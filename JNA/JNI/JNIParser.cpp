/** @file
 *
 * Body for JNIParser
 */

#include <iostream>
#include <cstdlib>
#include "JNI/JNIParser.h"
#include "JNA/TypesDictionnary.h"

#define JNIPARSER nsJNI::JNIParser

using nsJNA::TypesDictionnary;

JNIPARSER::~JNIParser() {
}

int JNIPARSER::run(nsModules::Module::vector modules) {
    std::cout << "JNI Parser run()\n";

	TypesDictionnary dictionnary;
	std::cout << "Just after constructor call ?" << std::endl;
	//STEP 3
	if (!dictionnary.addModules(modules)) {
		//ERR << "Error while adding modules to the dictionnary\n";
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}

#undef JNIPARSER

