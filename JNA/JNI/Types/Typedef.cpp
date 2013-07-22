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
	return "JNI";	
}

string Typedef::getTargetType()
{
	return _targetType;
}

string Typedef::getStructName()
{
	return _structName;
}

bool Typedef::isNativeType()
{
	return false;
}

bool Typedef::isAddressWrapper()
{
	return false;
}

bool Typedef::isBooleanWrapper()
{
	return false;
}

bool Typedef::isArray()
{
	return false;
}

void Typedef::prepareCall(ofstream& f,string& varName)
{

}

//Useless code but needed for polymorphism
string Typedef::getJNIParameterName(string& varName)
{
	return "Typedef";
}

void Typedef::getReturnValue(ofstream& f)
{



}
        
