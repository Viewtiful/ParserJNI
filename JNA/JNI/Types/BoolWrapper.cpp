#include "JNI/Types/BoolWrapper.h"
#include "Utils/Utils.h"

using namespace nsUtils;
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

bool BoolWrapper::isAddressWrapper()
{
	return false;
}

void BoolWrapper::prepareCall(ofstream& f,string& varName)
{
      bool C_is_valid;
   string structure (
         "\t\t%TYPE% %NAME%;\n\n"
         );
   
   string name = "C_" + varName;
   string type = _realCType.substr(0, _realCType.size()-2);
   stringReplace(structure, "TYPE", type);
   stringReplace(structure, "NAME", name);

   f << structure;
}

string BoolWrapper::getJNIParameterName(string& varName)
{
	return varName;

}

void BoolWrapper::getReturnValue(ofstream& f)
{


}
        
