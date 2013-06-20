#include "OutputJava.h"

using namespace std;
using namespace nsJNI;

OutputJava::OutputJava(TypesDictionnary *dictionnary)
{
	this->dictionnary = dictionnary;
}


string OutputJava::getJavaType(string inputType)
{
	return dictionnary->convertJava(inputType);
}


void OutputJava::addJavaType(string inputType, string javaType)
{
	toJavaType.insert(pair<string,string>(inputType,javaType) );	
}

OutputJava::~OutputJava()
{

}

void OutputJava::printPrototype(ofstream& f,string typeRetour)
{
	string returnType = getJavaType(typeRetour);
	if(returnType  == "")
		returnType = typeRetour;
	f << "\t" << "public native " << returnType << " ";
}

void OutputJava::printName(ofstream &f,string name)
{
	f << name << "(" ;
}

void OutputJava::printParameters(ofstream &f,Param::vector& parameters)
{
	int i;
	int n = parameters.size();
	for(i=0;i<n;i++)
	{
		if(parameters[i].getIndirections()>0 && i+1<n)
		{
			Param size = parameters[i+1];
			if(parameters[i].getName() + "_size" == size.getName())
			{
				cout << "Array" << endl;
			}
		}	
		printParameter(f,parameters[i]);
		if(i+1<parameters.size())
			f << ",";
	}	
	f << ");" << endl;
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

void OutputJava::printParameter(ofstream &f,Param parameter)
{
	f << getJavaType(parameter.getType()) << " " << parameter.getName();
}

void OutputJava::convertFunctions(ofstream &f,Function::vector fcts)
{
	for(int k = 0;k<fcts.size();k++)
	{
		string typeRetour = fcts[k].getReturnType();
		string name = fcts[k].getName();
		Param::vector parameters = fcts[k].getParamList();
		printPrototype(f,typeRetour);
		printName(f,name); 
		printParameters(f,parameters);
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
	Function::vector fcts = module.getFunctions();
	printJavaHeader(f,"class",module.getModuleName());
	printLoadLibrary(f,"library");
	convertFunctions(f,fcts);
	//convertEnums(f,module.getEnums());

	f << "}" << endl;
}
