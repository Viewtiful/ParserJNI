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
	CHeaderFile[0] = toupper(CHeaderFile[0]);
	f << "public "<< type << " " << CHeaderFile << "{" << endl << endl;
}

void OutputJava::printJavaHeader(ofstream &f,string CHeaderFile)
{
	f << "\npublic static enum "<< CHeaderFile << "{" << endl << endl;
}

void OutputJava::printLoadLibrary(ofstream &f,string library)
{
	f << "\t" << "static {" << endl ;
	f << "\t" << "\t" << "System.loadLibrary(\""<< library << "\");";
	f << endl << "\t" << "}" << endl << endl;
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

void OutputJava::convert(ofstream &f,Module& module)
{
	cout << "2.1" << endl;
	nsC::Function::vector fcts = module.getFunctions();
	cout << "2.2" << endl;
	printJavaHeader(f,"class",module.getModuleName());
	cout << "2.3" << endl;
	printLoadLibrary(f,"library");
	cout << "2.4" << endl;
	convertFunctions(f,fcts);
	//convertEnums(f,module.getEnums());

	f << "}" << endl;
}
