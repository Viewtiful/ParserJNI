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
		string getJavaType(string inputType);
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/
		void convert(ofstream &f,nsJNI::Function *fct);

		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/
		void printJavaHeader(ofstream &f,string CHeaderFile);
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/

		void printLoadLibrary(ofstream &f,string library);

		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/

		void printJavaHeader(ofstream &f,string type,string CHeaderFile);
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/

        	void addClassDefinition(ofstream &f, string className);
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/

         	void addAddressWrapper(ofstream &f);
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/

         	void addBoolWrapper(ofstream &f);
		protected:
		TypesDictionnary *_dictionnary; /*!< The structure's name*/
		
		
	};
}

#endif
