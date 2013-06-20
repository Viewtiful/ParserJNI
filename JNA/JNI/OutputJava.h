#include "Modules/Module.h"
#include <map>
#include <fstream>
#include "C/Enum.h"
#include "JNI/TypesDictionnary.h"
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
			void convert(ofstream &f,Module& module);	
			void printPrototype(ofstream &f,string typeRetour);
			void printName(ofstream &f,string name);
			void printParameters(ofstream &f,Param::vector& parameters);
			void printParameter(ofstream &f,Param parameter);
			void printJavaHeader(ofstream &f,string CHeaderFile);
			void printLoadLibrary(ofstream &f,string library);
			void convertFunctions(ofstream &f,Function::vector fcts);
		/*	void convertEnums(ofstream &f, Enum::vector enums);
			void printEnum(ofstream &f,Enum e);
			void printEnumElement(ofstream &f,Enum::EnumValue value);*/
			void printJavaHeader(ofstream &f,string type,string CHeaderFile);
		protected:
		map<string, string> toJavaType;
		TypesDictionnary *dictionnary;
		
		
	};








}
