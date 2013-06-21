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

/*void OutputJava::printEnumElement(ofstream &f,Enum::EnumValue value)
{
	f << value.first << "(" << value.second << ")";
}

void OutputJava::printEnum(ofstream &f,Enum e)
{
	Enum::EnumValues enumValues = e.getValues();
	for(int k =0;k<enumValues.size();k++)
	{
		f << "\t" ;
		printEnumElement(f,enumValues[k]);
		if(k+1<enumValues.size())
			f << "," << endl;
		else if(k == enumValues.size()-1)
			f << ";" << endl;
	}

	f << "\n\n\tint enumValue;\n\n";
	string enumName = e.getName();
    if(enumName == "")
            enumName = e.getTypedef();

	f << "\t" << enumName << " (int val) {\n";
	f << "\t\tenumValue=val;\n";
	f << "\t}\n\n";

	f << "\tint getValue() {\n";
	f << "\t\treturn enumValue;\n";
	f << "\t}\n\n";

	f << "\tvoid setValue(int val) {\n";
	f << "\t\tenumValue=val;\n";
	f << "\t}" << endl;
}

void OutputJava::convertEnums(ofstream &f, Enum::vector enums)
{
	for(int i = 0;i<enums.size();i++)
	{
		string enumName = enums[i].getName();
		if(enumName=="")
			enumName = enums[i].getTypedef();
		printJavaHeader(f,enumName);
		printEnum(f,enums[i]);
		f << "}" << endl;			
	}
}*/

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
