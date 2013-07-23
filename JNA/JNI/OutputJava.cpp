#include "OutputJava.h"

using namespace std;
using namespace nsJNI;

OutputJava::OutputJava(TypesDictionnary *dictionnary)
{
	this->_dictionnary = dictionnary;
}

string OutputJava::getJavaType(const string& inputType)
{
	return _dictionnary->convertJava(inputType);
}

OutputJava::~OutputJava()
{
}

void OutputJava::printJavaHeader(ofstream &f, const string& type, const string& CHeaderFile)
{
	f << "public "<< type << " " << CHeaderFile << "{\n\n";
}

void OutputJava::printLoadLibrary(ofstream &f, const string& library)
{
	f << "\t" << "static {\n";
	f << "\t" << "\t" << "System.loadLibrary(\""<< library << "\");\n";
	f << "\t" << "}\n\n";
}

void OutputJava::addAddressWrapper(ofstream &f) {

	string structure (
			"\tpublic static class AddressWrapper {\n"
			"\t\tprivate long address;\n\n"
			"\t\tpublic long getAddress() {\n"
			"\t\t\treturn address;\n"
			"\t\t}\n\n"
			"\t\tpublic void setAddress(long addr) {\n"
			"\t\t\taddress = addr;\n"
			"\t\t}\n"
			"\t}\n\n"
			);

	f << structure;
}

void OutputJava::addBoolWrapper(ofstream &f) {

	string structure (
			"\tpublic static class BoolWrapper {\n"
			"\t\tprivate boolean booleanVal;\n\n"
			"\t\tpublic boolean getValue() {\n"
			"\t\t\treturn booleanVal;\n"
			"\t\t}\n\n"
			"\t\tpublic void setValue(boolean val) {\n"
			"\t\t\tbooleanVal = val;\n"
			"\t\t}\n"
			"\t}\n\n"
			);

	f << structure;
}

void OutputJava::addClassDefinition(ofstream &f, const string& className) {
	printJavaHeader(f, "class", className);
	printLoadLibrary(f, "arcanaJNI");
	addAddressWrapper(f);
	addBoolWrapper(f);
}

void OutputJava::convert(ofstream &f,nsJNI::Function *fct)
{
	cout << "Converting Function : "<< fct->getName() << endl;
	fct->convertJava(f);
}
