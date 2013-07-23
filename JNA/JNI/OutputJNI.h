/** @file
 *
 * @defgroup JNI_OutputJNI Writting JNI code.
 * Write a JNI class creating a brigde between java and C functions.
 */

#ifndef __JNI_OUTPUTJNI_H
#define __JNI_OUTPUTJNI_H
#include "Modules/Module.h"
#include <map>
#include <vector>
#include <fstream>
#include "JNI/TypesDictionnary.h"
#include "JNI/Types/Function.h"
using namespace nsModules;
using namespace std;
using namespace nsJNI;

/** @addtogroup JNI_OutputJNI
 * @{ */

namespace nsJNI
{
	/*!
	  \class OutputJNI
	  \brief generate, manage the JNI Side 
	  */
	class OutputJNI{

		public:
			/*!
			  \brief Constructor with one parameter
			  Create, and initialize a OutputJNI class with the following argument
			  \param dictionnary : Dictionnary of all types.
			  */
			OutputJNI(TypesDictionnary *dictionnary);

			~OutputJNI();

			/*!
			  \brief Get the JNI type from a C type.
			  \param inputType : C type that we want to translate to JNI.
			  \return The JNI type corresponding to the C type. 
			*/
			string getJNIType(const string& inputType);

			/*!
			  \brief Get the VM Signature type from a C type.
			  \param inputType : C type that we want to translate to VM Signature.
			  \return The VM Signature corresponding to the C type. 
			  */
			string getVMSignature(const string& inputType);

			/*!
			  \brief Convert a fonction to JNI and write the result in a file.
			  \param f : The file where the result will be print.
			  \param fct : The function which will be converted to JNI.
			  */
			void convert(ofstream &f, Function *fct);

			/*!
			  \brief Add all headers include to the target file.
			  \param f : The target file where the headers include will be written.
			  */
			void addInclude(ofstream &f);

			/*!
			  \brief Add a ContextWrapper to the target file.
          * This contextWrapper enable us to keep the address of the object allocated in JNI.
			  \param f : The target file where the contextWrapper is written.
			  */
			void addContextWrapper(ofstream &f);

			/*!
			  \brief Generate the Native Function Call. The JNIOnload function is the first function
          * the Java VM will try to launch. Trying to get the java Class and register all the native functions and their corresponding one in Java.
          * 
			  \param f : The target file where the JNIOnload function is written.
			  */
			void generateJNIOnload(ofstream &f, string filename);

			//void addFunctionPrototype(Function::vector fcts);
			/*!
			  \brief generate the Native Function Call
			  \param f: Output JNI File
			  */
			void addNativeFunctionTable(ofstream &f, string filename, vector<nsJNI::Function*> fcts);

		protected:	
			TypesDictionnary *_dictionnary; /*!< The dictionnary of all types*/
	};
}

#endif
