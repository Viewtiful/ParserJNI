/** @file
 *
 * @defgroup JNI_parser JNI Parser of C headers.
 * Parsing C headers in order to create the corresponding java class 
 * and JNI code.
 */

#ifndef __JNI_JNIPARSER_H
#define __JNI_JNIPARSER_H
#include "Modules/Module.h"
#include "Utils/Parser.h"
#include "JNI/TypesDictionnary.h"
#include "JNI/OutputJNI.h"
#include "JNI/OutputJava.h"
#include "JNI/Comments.h"

/** @addtogroup JNI_parser
 * @{ */

namespace nsJNI {

	/*!
	  \class JNIParser
	  \brief The class which manage the conversion from C to JNI/Java.
	  */
	class JNIParser: public nsUtils::Parser {
		public:
			virtual ~JNIParser();

			/*!
			  \brief Running the JNI parser.
			  This is where we start the conversion from C headers to 
			  Java/JNI. We first transform C types to Java / JNI / VM 
			  signatures and then we write them to a java / c file.
			  \param modules : All the C headers
			  */
			int run(nsModules::Module::vector modules);
			/*!
			  \brief Return true if the current module contains callback.
			  \param modules : All the C headers
			  */
			bool containsCallback(nsModules::Module module);

		protected :
			//! manager of the JNI Side
			OutputJNI *_jni; 
			//! manager of the Java Side
			OutputJava *_java; 
			//! Dictionnary of all types
			TypesDictionnary *_dico;
			//! Generate javadoc comments for function
			Comments *_cm;  


	};
}

#endif

