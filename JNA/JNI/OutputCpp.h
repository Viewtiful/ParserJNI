#include "Modules/Module.h"
#include <map>
#include <vector>
#include <fstream>
using namespace nsModules;
using namespace std;
using namespace nsC;

namespace nsJNI
{

	class OutputCpp{
	
	public:
		OutputCpp();
		~OutputCpp();
		void addCppType(std::string inputType, std::string cppType);
		string getCppType(string inputType);
		void printPrototype(string typeRetour);
		void printName(string name);
		void printParameters(Param::vector& parameters);
		void printParameter(Param parameter);
		void convert(Module& module);
		
	protected:	
		map<string,string> toCppType;
		ofstream outputFile;		
	};

}

