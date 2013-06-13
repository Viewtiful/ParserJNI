#include "OutputJava.h"

using namespace std;
using namespace nsJNI;

OutputJava::OutputJava()
{
	addJavaType("int","int");
    addJavaType("float","float");
    addJavaType("double","double");
    addJavaType("char","byte");
    addJavaType("void","void");
    addJavaType("short","short");
    addJavaType("bool","boolean");
	addJavaType("long","long");
}


string OutputJava::getJavaType(string inputType)
{
	return toJavaType[inputType];
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
	f << "\t" << "public native " << getJavaType(typeRetour) << " ";
}

void OutputJava::printName(ofstream &f,string name)
{
	f << name << "(" ;
}

void OutputJava::printParameters(ofstream &f,Param::vector& parameters)
{
	int i;
	for(i=0;i<parameters.size();i++)
	{
		printParameter(f,parameters[i]);
		if(i+1<parameters.size())
			f << ",";
	}	
	f << ");" << endl;
}

void OutputJava::printJavaHeader(ofstream &f,string type,string CHeaderFile)
{
	f << "public "<< type << " " << CHeaderFile << "{" << endl << endl;
}

void OutputJava::printJavaHeader(ofstream &f,string CHeaderFile)
{
	f << "public "<< CHeaderFile << "{" << endl << endl;
}

void OutputJava::printLoadLibrary(ofstream &f,string library)
{
	f << "\t" << "static {" << endl ;
	f << "\t" << "\t" << "System.out.loadLibrary(lib" << library << ");";
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

void OutputJava::printEnumElement(ofstream &f,Enum::EnumValue value)
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
	}
	f << ";" << endl;
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
}

void OutputJava::convert(ofstream &f,Module& module)
{
	Function::vector fcts = module.getFunctions();
	printJavaHeader(f,"class",module.getModuleName());
	printLoadLibrary(f,"library");
	convertFunctions(f,fcts);
	convertEnums(f,module.getEnums());
		
	f << "}" << endl;
}
