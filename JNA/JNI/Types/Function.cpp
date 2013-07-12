#include "JNI/Types/Function.h"

using namespace nsUtils;
using namespace nsJNI;
Function::Function(TypesDictionnary *dictionnary)
{
	_dictionnary = dictionnary;
}

Function::~Function()
{
   for(vector<Param*>::const_iterator it = _args.begin(); it != _args.end(); it++)
       delete *it;
   _args.clear();
}

void Function::create(const nsC::Function& fct)
{
	setReturnType(fct.getReturnType());
	_name = fct.getName();
	addArgs(fct.getParamList());
}

void Function::printPrototypeJava(ofstream& file)
{
	string returnType;
	returnType = _dictionnary->convertJava(_returnType);
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
		if(_args[i]->getType()=="size_t *")
			skip = true;
		
		// if skip is true, we do not print the size_t* parameter
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
	printPrototypeJava(file);
	file << "(";
	printParametersJava(file);	
	file << ");" << endl; 	
	
}

void Function::convertJNI(ofstream& file)
{
	printPrototypeJNI(file);
	file << "(";
	printParametersJNI(file);	
	file << ") "; 	
	printContentJNI(file);
}


void Function::printParametersJNI(ofstream &f)
{
	int i;
	int n = _args.size();
	bool skip;
	
	f << "JNIEnv *env, jclass cls";
	if(n > 0)
		f << ", ";

	for(i = 0; i < n; i++) {
		skip = false;
		if(_args[i]->getType() == "size_t *") 
			skip = true;
		// if skip is true, we do not print the size_t* parameter
		if(!skip) {
			f << _dictionnary->convertJNI(_args[i]->getType()) << " " << _args[i]->getName();
			if(i + 1 < n && _args[i+1]->getType() != "size_t *")
				f << ',';
		}
	}
}

string Function::getName() {
	return _name;
}

void Function::printPrototypeJNI(ofstream &f)
{
	string returnType;
	returnType = _dictionnary->convertJNI(_returnType);
	f << "\t" << "JNIEXPORT " << returnType << " JNICALL " << "JNI_" << _name;
}

void Function::printContentJNI(ofstream &f)
{
	f << "{\n\n";
	if(!(_returnType=="void"))
		f << "\t\t" << _dictionnary->convertJNI(_returnType) << " " << "JNI_result;\n\n";
	//Preparing all arguments before calling the native method
	for(size_t i = 0; i < _args.size(); ++i) {
		Type * param = _dictionnary->getType(_args[i]->getType());

		param->prepareCall(f, _args[i]->getName());
	}
	//calling the native method with correct parameters
   	callNativeMethod(f);

	for(size_t i = 0; i < _args.size(); ++i) {
		Type * param = _dictionnary->getType(_args[i]->getType());

	      if(param->isAddressWrapper() || param->isBooleanWrapper())
		   param->getReturnValue(f);
	      if(param->isArray()) {
	         Array *a = (Array *)param;
	         a->getReturnValueAndFree(f);
	      }
	}

   	Type *returnValue = _dictionnary->getType(_returnType);
   	returnValue->getReturnValue(f);

	f << "\t}\n\n";
}

void Function::callNativeMethod(ofstream &f) {
   
   string structure (
            "\t\t%RETURNTYPE% %NAME% %CAST%%METHODNAME% (%PARAMS%);\n\n"
            );
	//Generate specific code to get the Return Value from native Function call
   if(_returnType != "void") {

      if(_dictionnary->convertJNI(_returnType) == "jbyteArray") {
         stringReplace(structure, "RETURNTYPE", "void*");
         stringReplace(structure, "CAST", "(void*)");
         stringReplace(structure, "NAME", "tempJNI_result =");
      }
      else if (_dictionnary->getType(_returnType)->isNativeType() &&
                  _dictionnary->convertJNI(_returnType) != "jstring") {
         stringReplace(structure, "RETURNTYPE", "");
         stringReplace(structure, "CAST", "");
         stringReplace(structure, "NAME", "JNI_result =");
      }
      else if (_dictionnary->convertJNI(_returnType) == "jstring") {
         stringReplace(structure, "RETURNTYPE", "char *");
         stringReplace(structure, "CAST", "(char *)");
         stringReplace(structure, "NAME", "tempJNI_result =");
      }
      else {
         stringReplace(structure, "RETURNTYPE", _returnType);
         stringReplace(structure, "CAST", "");
         stringReplace(structure, "NAME", "tempJNI_result =");
      }
   }
   else {
         stringReplace(structure, "RETURNTYPE", "");
         stringReplace(structure, "CAST", "");
         stringReplace(structure, "NAME", "");
   }

   stringReplace(structure, "METHODNAME", _name);

   string params;
	//generate code to have adequate param for Native function call
   for(size_t i = 0; i < _args.size(); ++i) {

      string param ("%PARAMNAME%");
      Type *typeRetour = _dictionnary->getType(_args[i]->getType());

      if(_args[i]->getType() == "bool *" || _args[i]->getType() == "size_t *" || typeRetour->isAddressWrapper()) {
         stringReplace(param, "PARAMNAME", "&C_" + _args[i]->getName());
      }      
      else if(typeRetour->getJNIParameterName(_args[i]->getName()) == "Array") {
         string param_size(", %PARAMNAME2%");
         param += param_size;
         stringReplace(param, "PARAMNAME", "C_" + _args[i]->getName());
         stringReplace(param, "PARAMNAME2", "C_" + _args[i]->getName() + "_size");
      }
      else {
         stringReplace(param, "PARAMNAME", "C_" + _args[i]->getName());
      }

      params += param;

      if(i+1 < _args.size())
         params += ", ";
   }
   stringReplace(structure, "PARAMS", params);

   f << structure;
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
	int n = parameters.size();	
	int beginArgs = 0;
	if(_returnType=="const void *" || _returnType=="void *")
		_returnType = _returnType+"Array";
	cout << "Creation Fct :" << _name << endl;
	// if the function is a init function, the first argument will be translated as an AddressWrapper
	if(parameters.size()>0 && _name.find("_init",0)!=string::npos)
	{
		cout << "This is a init Function" << endl;
		if(!_dictionnary->isNativeType(parameters[0].getType()))
		{
			cout << "The first argument type is not Native" << endl;
			//If this type does not exist
			if(_dictionnary->countAt(parameters[0].getCType())==0)
	 		{
	 			cout << "The object does not exists = " << parameters[0].getCType();
	 			
				Type *object = new AddressWrapper(parameters[0].getCType(),"L" + _dictionnary->getFilename() + "$AddressWrapper;");
 				_dictionnary->addToMap(parameters[0].getCType(),object);
	 		}
	 			
			_args.push_back(new nsJNI::Param(parameters[0].getCType(),parameters[0].getName()));
			beginArgs = 1;
		}
		else
			cout << "The first argument type is Native" << endl;
	
	}

   	bool skip = false;
	for( int i = beginArgs; i<n; i++)
	{
		size_t size = _args.size();
	      if(skip) {
		 skip = false;
		 continue;
	      }
		// If the parameters's type is a Pointer
		if(parameters[i].getIndirections()>0  && parameters[i].getCType()!= "const char *")
		{
			cout << "Pointer !" << endl;
			string type = parameters[i].getType();
			// detect if this pointer can be an Array
			if(i+1<n && parameters[i].getName() + "_size" == parameters[i+1].getName())
			{
				string array = "Array";
				cout << "Create an Array" << endl;
				if(type == "void" || type == "const void")
					array = " *" + array;
				
				_args.push_back(new nsJNI::Param(type+array,parameters[i].getName()));
				cout << parameters[i].getType()+array << endl;
       				skip = true;  //We just bypass the _size argument
			}
			else
			{
				if(_dictionnary->countAt(parameters[i].getCType())==0)
	 			{	
	 				cout << "The object does not exists = " << parameters[i].getCType();
					Type *object;
	 				if(!_dictionnary->isNativeType(type))
						object = new AddressWrapper(parameters[i].getCType(),"L" + _dictionnary->getFilename() + "$AddressWrapper;");
					else
						object = new Pointer("J",parameters[i].getType(),_dictionnary,false); 
					
					_dictionnary->addToMap(parameters[i].getCType(),object);
	 			}
				_args.push_back(new nsJNI::Param(parameters[i].getCType(),parameters[i].getName()));

			}
		}
	else
	   {
		   cout << "Normal Type" << endl;
		   cout << "Creating a new Param as following" << "[" << parameters[i].getCType()<<" , "  << parameters[i].getName() << "]" << endl; 
		   _args.push_back(new nsJNI::Param(parameters[i].getCType(),parameters[i].getName()));
	   }
      assert(_args.size()==size+1);
	}
	cout << "Fin Fonction" << endl;
}

vector<nsJNI::Param*> Function::getArgs()
{
	return _args;
}

std::string& Function::getReturnType()
{
	return _returnType;
}

