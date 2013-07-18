#include "JNI/Types/AddressWrapper.h"
#include <sstream>

using namespace nsJNI;
using namespace nsUtils;
using namespace std;

//Ensure that every items in the JNI functions are unique.
static int nbOfOcc;
static int nbOfRtn;

AddressWrapper::AddressWrapper(string realCType,string VMSignature) : Type("AddressWrapper", "jobject", VMSignature)
{
	_realCType = realCType;
	nbOfOcc = 1;
	nbOfRtn = 1;
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

bool AddressWrapper::isBooleanWrapper()
{
	return false;
}

bool AddressWrapper::isArray()
{
	return false;
}

void AddressWrapper::prepareCall(ofstream& f,string& varName)
{
	//We create the C object equivalent of the Java one and allocate memory for it.
	string structure (
			"\t\t%TYPE% %NAME%;\n"
			"\t\tcontextWrapper *ctxWrp%VALUE% = (contextWrapper *)malloc(sizeof(contextWrapper));\n"
			"\t\tctxWrp%VALUE%->env = env;\n\n"
			);
	std::ostringstream oss;
	oss << nbOfOcc;
	_varName = varName;

	string name = "C_" + varName;
	//If it's a pointer, we suppress it from the type.
	if(_realCType.find("*", 0) != string::npos) {   //A optimiser
		stringReplace(structure, "TYPE", _realCType.substr(0, _realCType.size() -2));
	}
	else
		stringReplace(structure, "TYPE", _realCType);

	stringReplace(structure, "NAME", name);
	stringReplace(structure, "VALUE", oss.str());
	f << structure;
	//We don't forget to increment the value, in order to have each object unique.
	nbOfOcc = nbOfOcc + 1;
}

string AddressWrapper::getJNIParameterName(string& varName)
{
	return varName;

}
void AddressWrapper::getReturnValue(ofstream& f)
{
	//We return the address of the C object to Java.
	string structure (
			"\t\tctxWrp%VALUE%->ctxRef = %NAME%;\n"
			"\t\tjclass adrWrp_%CNAME%;\n"
			"\t\tjmethodID setAddr_%CNAME%;\n"
			"\t\tjlong arg_%CNAME%;\n\n"
			"\t\tadrWrp_%CNAME% = (*env)->GetObjectClass(env, %CNAME%);\n"
			"\t\tsetAddr_%CNAME% = (*env)->GetMethodID(env, adrWrp_%CNAME%, \"setAddress\", \"(J)V\");\n"
			"\t\targ_%CNAME% = (jlong) ctxWrp%VALUE%;\n"
			"\t\t(*env)->CallVoidMethod(env, %CNAME%, setAddr_%CNAME%, arg_%CNAME%);\n\n"
			);

	std::ostringstream oss;
	oss << nbOfRtn;
	string name = "C_" + _varName;
	if(_realCType.find("*", 0) != string::npos) {
		stringReplace(structure, "TYPE", _realCType.substr(0, _realCType.size() -2));
	}
	else
		stringReplace(structure, "TYPE", _realCType);

	stringReplace(structure, "CNAME", _varName);
	stringReplace(structure, "VALUE", oss.str());
	stringReplace(structure, "NAME", name);

	f << structure;
	//We don't forget to increment the value, in order to have each the object corresponding to prepareCall()
	//and each of them to be unique.
	nbOfRtn = nbOfRtn + 1;
}

