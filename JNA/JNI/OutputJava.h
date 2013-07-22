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
namespace nsJNI
{
	/*!
		\class OutputJava
		\brief generate, manage the Java Side 
	*/

	class OutputJava
	{
	
		public:
		/*!
			\brief constructor with two parameters
			Create, and initialize a Create Function with the following arguments
			\param structName : Struct's name which contains this method
			\param dictionnary : dictionnary of all type
	        */
		OutputJava(TypesDictionnary* dictionnary);
		~OutputJava();
                
                /*!
			\brief give the correct java Translation for an specific c Type
			\param inpuutType: C type which will be translated
                 *      \return the corresponding Java Type
		*/
		string getJavaType(string inputType);
                
		/*!
			\brief Convert a C function into an Java Function, and write the result in a file
			\param f: Output Java File
                 *      \param fct : function which is going to be translated
		*/
		void convert(ofstream &f,nsJNI::Function *fct);

		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/

		void printLoadLibrary(ofstream &f,string library);

		/*!
			\brief print Java Header for class or enum
			\param f: Output Java File
                 *      \param type : Header type
                 *      \param CHeaderFile : filename of C header
		*/

                        
		void printJavaHeader(ofstream &f,string type,string CHeaderFile);
                
		/*!
			\brief print Java Header for enum
			\param f: Output Java File
                 *      \param CHeaderFile : filename of C header
		*/
		void printJavaHeader(ofstream &f,string CHeaderFile);
		/*!
			\brief print the class definition in a file
			\param f: Output Java File
                 *      \param className : Class' name which need definition
		*/

        	void addClassDefinition(ofstream &f, string className);
                
		/*!
			\brief Add an addressWrapper definition in the Java file
			\param f: Output Java File
		*/
         	void addAddressWrapper(ofstream &f);
                
		/*!
			\brief Add a BoolWrapper definition in the java file
			\param f: Output Java File
		*/
         	void addBoolWrapper(ofstream &f);
		protected:
		TypesDictionnary *_dictionnary; /*!< Dictionnary of all Types*/
		
		
	};
}

#endif

