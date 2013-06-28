#include "JNI/Types/BoolWrapper.h"

using namespace nsJNI;
using namespace std;

BoolWrapper::BoolWrapper(string realCType,string VMSignature) : Type("BoolWrapper", "jobject", VMSignature)
{
	_realCType = realCType;
}



BoolWrapper::~BoolWrapper()
{

}


std::string BoolWrapper::outputJava()
{
	return getJavaType();
}
 
std::string BoolWrapper::outputJNI()
{
	return getJNIType();
}
        
bool BoolWrapper::isNativeType()
{
	return false;
}

void BoolWrapper::prepareCall(ofstream& f,string& varName)
{

}

string BoolWrapper::getJNIParameterName(string& varName)
{
	return varName;

}

void BoolWrapper::getReturnValue(ofstream& f)
{


}
        
