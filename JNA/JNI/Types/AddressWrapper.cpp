#include "JNI/Types/AddressWrapper.h"
#include <sstream>

using namespace nsJNI;
using namespace nsUtils;
using namespace std;

AddressWrapper::AddressWrapper(const string& realCType, const string& filename) : Type("AddressWrapper", "jobject")
{
	_realCType = realCType;
        _VMSignature = "L" + filename + "$AddressWrapper;";
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

void AddressWrapper::prepareCall(ofstream& f, const string& varName)
{
	_varName = varName;

	//We create the C object equivalent of the Java one and allocate memory for it.
	string structure (
			"\t\t%TYPE% %NAME%;\n"
			"\t\tcontextWrapper *ctxWrp_%CNAME% = (contextWrapper *)malloc(sizeof(contextWrapper));\n"
			"\t\tctxWrp_%CNAME%->env = env;\n\n"
			);

	string name = "C_" + varName;
	//If it's a pointer, we delete the star from the type.
	if(_realCType.find("*", 0) != string::npos) { 
		stringReplace(structure, "TYPE", _realCType.substr(0, _realCType.size() -2));
	}
	else
		stringReplace(structure, "TYPE", _realCType);

	stringReplace(structure, "NAME", name);
	stringReplace(structure, "CNAME", _varName);
	f << structure;
}

string AddressWrapper::getJNIParameterName(const string& varName)
{
	return "&C_" + varName;
}

void AddressWrapper::getReturnValue(ofstream& f)
{
	//We return the address of the C object to Java.
	string structure (
			"\t\tctxWrp_%CNAME%->ctxRef = %NAME%;\n"
			"\t\tjclass adrWrp_%CNAME%;\n"
			"\t\tjmethodID setAddr_%CNAME%;\n"
			"\t\tjlong arg_%CNAME%;\n\n"
			"\t\tadrWrp_%CNAME% = (*env)->GetObjectClass(env, %CNAME%);\n"
			"\t\tsetAddr_%CNAME% = (*env)->GetMethodID(env, adrWrp_%CNAME%, \"setAddress\", \"(J)V\");\n"
			"\t\targ_%CNAME% = (jlong) ctxWrp_%CNAME%;\n"
			"\t\t(*env)->CallVoidMethod(env, %CNAME%, setAddr_%CNAME%, arg_%CNAME%);\n\n"
			);

	string name = "C_" + _varName;
	if(_realCType.find("*", 0) != string::npos) {
		stringReplace(structure, "TYPE", _realCType.substr(0, _realCType.size() -2));
	}
	else
		stringReplace(structure, "TYPE", _realCType);

	stringReplace(structure, "CNAME", _varName);
	stringReplace(structure, "NAME", name);

	f << structure;
}

