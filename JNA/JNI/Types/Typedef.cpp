#include "JNI/Types/Typedef.h"

using namespace std;
using namespace nsJNI;

Typedef::Typedef(string javaType, string cppType, string VMSignature, string structName) : Type(javaType,cppType,VMSignature)
{	
   _structName = structName;
   _targetType = javaType;  
}

Typedef::~Typedef()
{

}

std::string Typedef::outputJava()
{
	return _targetType;
}


std::string Typedef::outputJNI()
{
	
}

string Typedef::getTargetType()
{
	return _targetType;
}

string Typedef::getStructName()
{
	return _structName;
}



