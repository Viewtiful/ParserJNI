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

	class OutputJava
	{
	
		public:
			OutputJava(TypesDictionnary* dictionnary);
			~OutputJava();
			string getJavaType(string inputType);
			void addJavaType(string inputType, string javaType);
			void convert(ofstream &f,nsJNI::Function *fct);
			void printJavaHeader(ofstream &f,string CHeaderFile);
			void printLoadLibrary(ofstream &f,string library);
			void printJavaHeader(ofstream &f,string type,string CHeaderFile);
         void addClassDefinition(ofstream &f, string className);
         void addAddressWrapper(ofstream &f);
         void addBoolWrapper(ofstream &f);
		protected:
		map<string, string> toJavaType;
		TypesDictionnary *_dictionnary;
		
		
	};








}
