#include "JNI/Types/Function.h"

using namespace nsJNI;
Function::Function(TypesDictionnary *dictionnary)
{
	_dictionnary = dictionnary;
}

Function::~Function()
{


}

void Function::create(const nsC::Function& fct)
{
	setReturnType(fct.getReturnType());
	_name = fct.getName();
	addArgs(fct.getParamList());
}

void Function::printPrototype(ofstream& file)
{
	string returnType = _dictionnary->convertJava(_returnType);
	if(returnType  == "")
		returnType = "void";
	file << "\t" << "public native " << returnType << " " <<  _name ;
}



void Function::printParameters(ofstream& file)
{
	int i;
	int n = _args.size();
	for(i=0;i<n;i++)
	{	
		cout << _args[i]->getType() << endl;
		cout << "Type = " << _dictionnary->convertJava(_args[i]->getType()) << endl;
		file << _dictionnary->convertJava(_args[i]->getType()) << " " << _args[i]->getName();
		if(i+1<n)
			file << ",";
	}	
}

void Function::convert(ofstream& file)
{
	cout << "Convert début" << endl;
	printPrototype(file);
	file << "(";
	printParameters(file);	
	file << ");" << endl; 	
	cout << "Convert Fin" << endl;
}

int Function::nbIndirections(const string& CType)
{
	int strSize = CType.size();
	int nbIndirection = 0;
	for(int i = strSize-1;i>-1;i--)
		nbIndirection++;
	return nbIndirection;

}

void Function::setReturnType(const string& returnType)
{
	if(returnType=="")
		this->_returnType = "void";
	else
		this->_returnType = returnType;
}

void Function::addArgs(const nsC::Param::vector& parameters)
{
	cout << "2.4.3.4.1" << endl;
	
	int n = parameters.size();
	for(int i = 0; i<n; i++)
	{
		cout << "2.4.3.4.2" << endl;
		cout << "i = " << i << "n =" << n << endl;
		if(parameters[i].getIndirections()>0 && i+1<n)
		{
				nsC::Param size = parameters[i+1];
				if(parameters[i].getName() + "_size" == size.getName())
				{
					_args.push_back(new nsJNI::Param(parameters[i].getType()+"Array",parameters[i].getName()));
					cout << parameters[i].getType()+"Array" << endl;
				}
				else
					_args.push_back(new nsJNI::Param(parameters[i].getType(),parameters[i].getName()));
					
	 	}
		else
			_args.push_back(new nsJNI::Param(parameters[i].getType(),parameters[i].getName()));
	}
}

vector<nsJNI::Param*> Function::getArgs()
{
	return _args;
}

std::string& Function::getReturnType()
{
	return _returnType;
}
