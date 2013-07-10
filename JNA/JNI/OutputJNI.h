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
			\brief constructor with one parameter
			Create, and initialize a OutputJNI class with the following argument
			\param dictionnary : dictionnary of all type
	        	*/
			OutputJNI(TypesDictionnary *dictionnary);
			~OutputJNI();

		/*!
			\brief add a VMSignature to an inputType
			\param inputType: type which need a VmSignature
			\param vmSignature : VMSignature which will be added
		*/
			
			void addVMSignature(string inputType, string vmSignature);

		/*!
			\brief give the JNI type from an inputType
			\param inputType: considered type
			\return jniType 
		*/

			string getJNIType(string inputType);
		/*!
			\brief give the VMSignature type from an inputType
			\param inputType: considered type
			\return : VMSignature 
		*/

			string getVMSignature(string inputType);
		/*!
			\brief Convert a fonction and write the result in a File
			\param f: The file where the result will be print
			\param fct : the function which have to be converted
		*/

			void convert(ofstream &f,Function *fct);
		/*!
			\brief add all header include to the target file
			\param f: the target file
		*/

			void addInclude(ofstream &f);
		
		/*!
			\brief add a ContextWrapper to the target file
			\param f: the target file
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
