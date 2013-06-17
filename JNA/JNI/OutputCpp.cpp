#include "JNI/OutputCpp.h"

using namespace std;
using namespace nsJNI;
OutputCpp::OutputCpp()
{
	addCppType("int","jint");
    addCppType("float","jfloat");
    addCppType("double","jdouble");
    addCppType("char","jbyte");
    addCppType("void","void");
    addCppType("short","jshort");
    addCppType("bool","jboolean");
	addCppType("long","jlong");	
}

void OutputCpp::addCppType(std::string inputType, std::string cppType)
{
	toCppType.insert(std::pair<std::string,std::string>(inputType,cppType) );	
}


std::string OutputCpp::getCppType(std::string inputType)
{
	return toCppType[inputType];

}


void OutputCpp::printPrototype(string typeRetour)
{
	cout << getCppType(typeRetour) << " ";
}

void OutputCpp::printName(string name)
{
	cout << name << "(" ;
}

void OutputCpp::printParameters(Param::vector& parameters)
{
	int i;
	for(i=0;i<parameters.size();i++)
	{
		printParameter(parameters[i]);
		if(i+1<parameters.size())
			cout << ",";
	}	
	cout << ");" << endl;
}

void OutputCpp::printParameter(Param parameter)
{
	cout << getCppType(parameter.getType()) << " " << parameter.getName();
}

void OutputCpp::convert(Module& module)
{
	Function::vector fcts = module.getFunctions();
	for(int k = 0;k<fcts.size();k++)
	{
		string typeRetour = fcts[k].getReturnType();
		string name = fcts[k].getName();
		Param::vector parameters = fcts[k].getParamList();
		printPrototype(typeRetour);
		printName(name); 
		printParameters(parameters);
			
	}
}
