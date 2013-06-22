#include "OutputJava.h"

using namespace std;
using namespace nsJNI;

OutputJava::OutputJava(TypesDictionnary *dictionnary)
{
	this->_dictionnary = dictionnary;
}


string OutputJava::getJavaType(string inputType)
{
	return _dictionnary->convertJava(inputType);
}

OutputJava::~OutputJava()
{

}

void OutputJava::printJavaHeader(ofstream &f,string type,string CHeaderFile)
{
	f << "public "<< type << " " << CHeaderFile << "{\n\n";
}

void OutputJava::printJavaHeader(ofstream &f,string CHeaderFile)
{
	f << "\npublic static enum "<< CHeaderFile << "{\n";
}

void OutputJava::printLoadLibrary(ofstream &f,string library)
{
	f << "\t" << "static {\n";
	f << "\t" << "\t" << "System.loadLibrary(\""<< library << "\");\n";
	f << "\t" << "}\n\n";
}

void OutputJava::convertFunctions(ofstream &f,nsC::Function::vector fcts)
{
	cout << "2.4.1" << endl;
	for(int k = 0;k<fcts.size();k++)
	{
		cout << "2.4.2" << endl;
		nsJNI::Function *fct = new Function(_dictionnary);
		fct->create(fcts[k]);
		cout << "2.4.3" << endl;
		fct->convert(f);
	}
}

void OutputJava::addClassDefinition(ofstream &f, string className) {
	printJavaHeader(f, "class", className);
	printLoadLibrary(f, "library");
}

void OutputJava::convert(ofstream &f,Module& module)
{
	nsC::Function::vector fcts = module.getFunctions();
	cout << "2.4" << endl;
	convertFunctions(f,fcts);
	//convertEnums(f,module.getEnums());
}
