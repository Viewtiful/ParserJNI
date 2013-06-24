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
	cout << "returnType = " << _returnType << endl;
	string returnType;
	returnType = _dictionnary->convertJava(_returnType);
	cout << "returnType = " << returnType << endl;
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
	cout << "Converting Parameters" << endl;
	file << "(";
	printParameters(file);	
	file << ");" << endl; 	
	cout << "Convert Fin" << endl;
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
	int beginArgs = 0;
	string init;
	init = _name.substr(_name.size()- 5, _name.size()-1);
	
	if(init=="_init" && n>0)
	{
		_args.push_back(new nsJNI::Param("AddressWrapper",parameters[0].getName()));
		if(n>1)
			beginArgs = 1;
		else
			return;
	}
			
	for(int i = beginArgs; i<n; i++)
	{
		int size = _args.size();
		cout << "2.4.3.4.2" << endl;
		cout << "i = " << i << "n =" << n << endl;
		if(parameters[i].getIndirections()>0 && i+1<n)
		{
				nsC::Param size = parameters[i+1];
				if(parameters[i].getName() + "_size" == size.getName())
				{
					//Remplacer le if par le nombre d'indirection
					string type = parameters[i].getType();
					if(type == "void" || type == "const void")
						type = parameters[i].getCType();
						
					_args.push_back(new nsJNI::Param(type+"Array",parameters[i].getName()));
					cout << parameters[i].getType()+"Array" << endl;
				}
				else
					_args.push_back(new nsJNI::Param(parameters[i].getCType(),parameters[i].getName()));
					
	 	}
		else
			_args.push_back(new nsJNI::Param(parameters[i].getCType(),parameters[i].getName()));
		assert(_args.size()==size+1);
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
