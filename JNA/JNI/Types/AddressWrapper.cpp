#include "JNI/Types/AddressWrapper.h"
#include "Utils/Utils.h"
#include <sstream>

using namespace nsJNI;
using namespace nsUtils;
using namespace std;

static int nbOfOcc;

AddressWrapper::AddressWrapper(string realCType,string VMSignature) : Type("AddressWrapper", "jobject", VMSignature)
{
	_realCType = realCType;
   nbOfOcc = 1;
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

bool AddressWrapper::isAddressWrapper()
{
	return true;
}

void AddressWrapper::prepareCall(ofstream& f,string& varName)
{
   string structure (
         "\t\t%TYPE% %NAME%;\n"
         "\t\tcontextWrapper *ctxWrp%VALUE% = (contextWrapper *)malloc(sizeof(contextWrapper));\n"
         "\t\tctxWrp%VALUE%->env = env;\n\n"
         );
   std::ostringstream oss;
   oss << nbOfOcc;
   string name = "C_" + varName;
   if(_realCType.find("*", 0) != string::npos) {
      stringReplace(structure, "TYPE", _realCType.substr(0, _realCType.size() -2));
   }
   else
      stringReplace(structure, "TYPE", _realCType);
   
   stringReplace(structure, "NAME", name);
   stringReplace(structure, "VALUE", oss.str());
   f << structure;
   nbOfOcc = nbOfOcc + 1;
}

string AddressWrapper::getJNIParameterName(string& varName)
{
	return varName;

}
void AddressWrapper::getReturnValue(ofstream& f)
{


}
        
