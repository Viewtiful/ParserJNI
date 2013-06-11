/** @file
 *
 * Body for JNAParser
 */

#include <cstdlib>
#include <iostream>
#include "Utils/Output.h"
#include "Modules/Module.h"
#include "JNA/TypesDictionnary.h"
#include "JNA/SupportClass.h"
#include "JNA/Module.h"
#include "JNA/JNAParser.h"

#define JNAPARSER nsJNA::JNAParser

using nsJNA::TypesDictionnary;
using nsJNA::SupportClass;

JNAPARSER::~JNAParser() {
}

int JNAPARSER::run(nsModules::Module::vector modules) {
	std::cout << "Just before constructor call ?" << std::endl;
    TypesDictionnary dictionnary;
	std::cout << "Just after constructor call ?" << std::endl;
    // STEP 3
    if (!dictionnary.addModules(modules)) {
        ERR << "Error while adding modules to the dictionnary\n";
        return EXIT_FAILURE;
    }

    // STEP 4
    if (!dictionnary.convertToJava()) {
        ERR << "Error while converting into Java types\n";
        return EXIT_FAILURE;
    }

    // STEP 5
    if (!dictionnary.outputJava()) {
        ERR << "Error while writing Java files\n";
        return EXIT_FAILURE;
    }

    // STEP 6
    if (!SupportClass::create()) {
        ERR << "Error while checking the support class\n";
        return EXIT_FAILURE;
    }

    // STEP 7
    if (!nsJNA::Module::processModules(modules, dictionnary)) {
        ERR << "Error while processing modules\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#undef JNAPARSER

