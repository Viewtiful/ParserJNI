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
	class OutputJNI{

		public:
			OutputJNI(TypesDictionnary *dictionnary);
			~OutputJNI();
			void addCppType(std::string inputType, std::string cppType);
			void addVMSignature(string inputType, string vmSignature);
			string getJNIType(string inputType);
			string getVMSignature(string inputType);
			void convert(ofstream &f,Function *fct);
			void addInclude();
			void addContent();
			void generateJNIOnload(string filename);
			//void addFunctionPrototype(Function::vector fcts);
			//void addNativeFunctionTable(Function::vector fcts, string fileName);
			
		protected:	
			fstream _outputFile;		
			TypesDictionnary *_dictionnary;
	};
}

#endif
