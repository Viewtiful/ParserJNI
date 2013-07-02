#include "JNI/Types/Param.h"

using namespace nsJNI;
Param::Param(const string& type, const string& name)
{
	cout << "2.4.3.4.7.1" << endl;
	this->_type=type;
	this->_name = name;
	cout << "2.4.3.4.7.2" << endl;
	
}

Param::~Param()
{


}

std::string& Param::getName()
{
	return _name;
}

std::string& Param::getType()
{
	return _type;
}
