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

namespace nsJNI
{
	/*!
		\class OutputJNI
		\brief generate, manage the JNI Side 
	*/
	class OutputJNI{

		public:
			/*!
			\brief constructor with two parameters
			Create, and initialize a Create Function with the following arguments
			\param structName : Struct's name which contains this method
			\param dictionnary : dictionnary of all type
	        	*/
			OutputJNI(TypesDictionnary *dictionnary);
			~OutputJNI();
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/
			
			void addVMSignature(string inputType, string vmSignature);
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/

			string getJNIType(string inputType);
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/

			string getVMSignature(string inputType);
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/

			void convert(ofstream &f,Function *fct);
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/

			void addInclude(ofstream &f);
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/


	         	void addContextWrapper(ofstream &f);
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/

			void generateJNIOnload(ofstream &f, string filename);
			//void addFunctionPrototype(Function::vector fcts);
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/

			void addNativeFunctionTable(ofstream &f, string filename, vector<nsJNI::Function*> fcts);
			
		protected:	
			TypesDictionnary *_dictionnary; /*!< The structure's name*/
	};
}

#endif
