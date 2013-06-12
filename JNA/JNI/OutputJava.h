#include "Modules/Module.h"
#include <map>
#include <fstream>
using namespace nsModules;
using namespace std;
using namespace nsC;
namespace nsJNI
{

	class OutputJava
	{
	
		public:
			OutputJava();
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

			
		protected:
		map<string, string> toJavaType;
		
		
	};








}
