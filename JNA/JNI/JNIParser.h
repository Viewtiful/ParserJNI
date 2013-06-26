/** @file
 *
 * Header for JNIParser
 */

#ifndef __JNI_JNIPARSER_H
#define __JNI_JNIPARSER_H
#include "Modules/Module.h"
#include "Utils/Parser.h"
#include "JNI/OutputJNI.h"
#include "JNI/OutputJava.h"
#include <fstream>
namespace nsJNI {
	
	class JNIParser: public nsUtils::Parser {
		public:
			virtual ~JNIParser();
			int run(nsModules::Module::vector modules);
	};
}

#endif

