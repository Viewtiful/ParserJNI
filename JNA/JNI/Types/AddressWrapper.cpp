#include "JNI/Types/AddressWrapper.h"

using namespace nsJNI;
using namespace std;

AddressWrapper::AddressWrapper(string realCType,string VMSignature) : Type("AddressWrapper", "jobject", VMSignature)
{
	_realCType = realCType;
}



AddressWrapper::~AddressWrapper()
{

}


std::string AddressWrapper::outputJava()
{
	return getJavaType();
}
 
std::string AddressWrapper::outputJNI()
{
	return getJNIType();
}
        
bool AddressWrapper::isNativeType()
{
	return false;
}

void AddressWrapper::prepareCall(ofstream& f,string& varName)
{

}

string AddressWrapper::getJNIParameterName(string& varName)
{
	return varName;

}
void AddressWrapper::getReturnValue(ofstream& f)
{


}
        
