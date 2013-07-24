/** @file
 *
 * @defgroup JNI_OutputJava Writting Java code.
 * Write a Java class corresponding to the C headers.
 */


#ifndef __JNI_OUTPUTJAVA_H
#define __JNI_OUTPUTJAVA_H
#include "Modules/Module.h"
#include <map>
#include <fstream>
#include "C/Enum.h"
#include "JNI/TypesDictionnary.h"
#include "JNI/Types/Function.h"
using namespace nsModules;
using namespace std;
using namespace nsC;

/** @addtogroup JNI_OutputJava
 * @{ */

namespace nsJNI
{
	/*!
	  \class OutputJava
	  \brief Generate, manage the Java Side.
	  */

	class OutputJava
	{

		public:
			/*!
			  \brief Constructor with two parameters.
			  create, and initialize OutputJava with the following arguments.
			  \param dictionnary : Dictionnary of all types.
			  */
			OutputJava(TypesDictionnary* dictionnary);

			~OutputJava();

			/*!
			  \brief Give the correct Java Translation for an specific C type.
			  \param inputType : C type which will be translated.
			  \return The corresponding Java type of the C type.
			  */
			string getJavaType(const string& inputType);

			/*!
			  \brief Convert a C function into a Java function, and write the result in a file.
			  \param f : The target file where the function will be written.
			 *      \param fct : function which is going to be translated.
			 */
			void convert(ofstream &f, nsJNI::Function *fct);

			/*!
			  \brief The library loaded by Java containing the JNI code.
			  \param f : The target file where the library load will be written.
			  */
			void printLoadLibrary(ofstream &f, const string& library);

			/*!
			  \brief Print Java Header for the main class.
			  \param f : The target file where the Java header of the main class will be written.
			 *      \param type : Header type (class)
			 *      \param className : class name of the Java class.
			 */
			void printJavaHeader(ofstream &f, const string& type, const string& className);

			/*!
			  \brief Print the class definition in the target file.
			  \param f : The target file where the class definition will be written.
			  \param className : The class name for which we write a class definition.
			  */
			void addClassDefinition(ofstream &f, const string& className);

			/*!
			  \brief Add an addressWrapper definition in the Java file.
			  \param f : The target file where the AddressWrapper class will be written.
			  */
			void addAddressWrapper(ofstream &f);

			/*!
			  \brief Add a BoolWrapper definition in the Java file.
			  \param f :  The target file where the BoolWrapper class will be written.
			  */
			void addBoolWrapper(ofstream &f);

		protected:
			TypesDictionnary *_dictionnary; /*!< Dictionnary of all Types*/


	};
}

#endif

