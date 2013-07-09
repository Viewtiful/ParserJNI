#include "JNI/Types/Param.h"

using namespace nsJNI;
Param::Param(const string& type, const string& name)
{
	_type = type;
	_name = name;
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
