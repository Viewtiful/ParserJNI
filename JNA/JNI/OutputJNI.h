#include "Modules/Module.h"
#include <map>
#include <vector>
#include <fstream>
#include "JNI/TypesDictionnary.h"

using namespace nsModules;
using namespace std;
using namespace nsC;

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
			void printPrototype(string typeRetour);
			void printName(string name);
			void printParameters(Param::vector& parameters);
			void printParameter(Param parameter);
			void convert(Module& module);
			void addInclude();
			void addContent();
			void generateJNIOnload(string filename);
			void addFunctionPrototype(Function::vector fcts);
			void addNativeFunctionTable(Function::vector fcts, string fileName);

		protected:	
			fstream _outputFile;		
			TypesDictionnary *_dictionnary;
	};
}
