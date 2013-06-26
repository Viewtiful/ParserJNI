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

void Function::printPrototypeJava(ofstream& file)
{
	cout << "returnType = " << _returnType << endl;
	string returnType;
	cout << "Delta" << endl;
	returnType = _dictionnary->convertJava(_returnType);
	cout << "returnType = " << returnType << endl;
	if(returnType  == "")
		returnType = "void";
	file << "\t" << "public native " << returnType << " " <<  _name ;
}



void Function::printParametersJava(ofstream& file)
{
	int i;
	int n = _args.size();
	bool skip;
	for(i=0;i<n;i++)
	{	
		skip = false;
		cout << _args[i]->getType() << endl;
		if(_args[i]->getType()=="size_t *")
		{
			cout << "size_t * found skipping" << endl;
			skip = true;
		}
		cout << "Type = " << _dictionnary->convertJava(_args[i]->getType()) << endl;
		if(!skip)
		{
			file << _dictionnary->convertJava(_args[i]->getType()) << " " << _args[i]->getName();
			if(i+1<n && _args[i+1]->getType()!="size_t *")
				file << "," ;
		}
	}	
}

void Function::convertJava(ofstream& file)
{
	cout << "Convert début" << endl;
	printPrototypeJava(file);
	cout << "Converting Parameters" << endl;
	file << "(";
	printParametersJava(file);	
	file << ");" << endl; 	
	cout << "Convert Fin" << endl;
}

void Function::convertJNI(ofstream& file)
{
	cout << "Convert début" << endl;
	printPrototypeJNI(file);
	cout << "Converting Parameters" << endl;
	file << "(";
	printParametersJNI(file);	
	file << ") "; 	
	printContentJNI(file);
	cout << "Convert Fin" << endl;
}


void Function::printParametersJNI(ofstream &f)
{
	int i;
	int n = _args.size();
	bool skip;

	for(i = 0; i < n; ++i) {
		skip = false;
		cout << _args[i]->getType() << endl;
		if(_args[i]->getType() == "size_t *") {
			cout << "size_t * found skipping" << endl;
			skip = true;
		}
		cout << "Type = " << _dictionnary->convertJNI(_args[i]->getType()) << endl;
		if(!skip) {
			f << _dictionnary->convertJNI(_args[i]->getType()) << " " << _args[i]->getName();
			if(i + 1 < n && _args[i]->getType() != "size_t *")
				f << ',';
		}
	}
}

string Function::getName() {
	return _name;
}

void Function::printPrototypeJNI(ofstream &f)
{
	cout << "returnType = " << _returnType << endl;
	string returnType;
	returnType = _dictionnary->convertJNI(_returnType);
	cout << "returnType = " << returnType << endl;
	f << "\t" << "JNIEXPORT " << returnType << " JNICALL " << "JNI_" << _name;
}

void Function::printContentJNI(ofstream &f)
{
	f << "{\n";
	f << "\t\tprintf(\"Hello world !\");\n";
	f << "\t}\n\n";
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
	if(_name.find("_init",0)!=string::npos && parameters.size()>0)
	{
		cout << "This is a init Function" << endl;
		if(!_dictionnary->isNativeType(parameters[0].getType()))
		{
			cout << "The first argument type is not Native" << endl;
			_args.push_back(new nsJNI::Param("AddressWrapper",parameters[0].getName()));
			beginArgs = 1;
		}
		else
			cout << "The first argument type is Native" << endl;
	
	}
	for(int i = beginArgs; i<n; i++)
	{
		int size = _args.size();
		cout << "2.4.3.4.2" << endl;
		cout << "i = " << i << "n =" << n << endl;
		if(parameters[i].getIndirections()>0  && parameters[i].getCType()!= "const char *")
		{
			cout << "Pointer !" << endl;
			if(i+1<n)
			{
				nsC::Param arraySize = parameters[i+1];
				if(parameters[i].getName() + "_size" == arraySize.getName())
				{
					cout << "Create an Array" << endl;
					//Remplacer le if par le nombre d'indirection
					string type = parameters[i].getType();
					if(type == "void" || type == "const void")
						type = parameters[i].getCType();
					
					_args.push_back(new nsJNI::Param(type+"Array",parameters[i].getName()));
					cout << parameters[i].getType()+"Array" << endl;
					continue;
				}
			}
			if(!_dictionnary->isNativeType(parameters[i].getType()))
	 		{
	 			cout << "This is not a Native Type = " << parameters[i].getType() << endl;
	 			if(_dictionnary->countAt(parameters[i].getCType())==0)
	 			{
	 				cout << "The object does not exists = " << parameters[i].getCType();
	 			
	 				Type *object = new Pointer("bla",parameters[i].getType(),_dictionnary,false);
	 				_dictionnary->addToMap(parameters[i].getCType(),object);
	 			}
	 			cout << "Creating a new Param as following" << "[" << "Address Wrapper , " << parameters[i].getName() << "]" << endl; 
	 			_args.push_back(new nsJNI::Param("AddressWrapper",parameters[i].getName()));
			}
								
			else
			{
				cout << "Native Type pointer " << endl; 
				if(_dictionnary->countAt(parameters[i].getCType())==0)
	 			{	
	 				cout << "The object does not exists = " << parameters[i].getCType();
	 			
	 				Type *object = new Pointer("bla",parameters[i].getType(),_dictionnary,false);
	 				_dictionnary->addToMap(parameters[i].getCType(),object);
	 			}
	 			cout << "Creating a new Param as following" << "[" << "Address Wrapper , " << parameters[i].getName() << "]" << endl;
				_args.push_back(new nsJNI::Param(parameters[i].getCType(),parameters[i].getName()));
			}
			cout << "Apres le for" << endl;
			cout << "_args.size() : " << _args.size() << endl;
			assert(_args.size()==size+1);
	}
	else
	{
		cout << "Normal Type" << endl;
		cout << "Creating a new Param as following" << "[" << parameters[i].getCType()<<" , "  << parameters[i].getName() << "]" << endl; 
		_args.push_back(new nsJNI::Param(parameters[i].getCType(),parameters[i].getName()));
	}
	cout << "FIN fONCTION" << endl;
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
