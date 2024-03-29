#include "JNI/Types/BoolWrapper.h"
#include "Utils/Utils.h"

using namespace nsUtils;
using namespace nsJNI;
using namespace std;

BoolWrapper::BoolWrapper(string realCType,string filename) : Type("BoolWrapper", "jobject")
{
	_realCType = realCType;
        _VMSignature = "L" + filename + "$BoolWrapper;";
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

bool BoolWrapper::isBooleanWrapper()
{
	return true;
}

bool BoolWrapper::isArray()
{
	return false;
}

void BoolWrapper::prepareCall(ofstream& f, const string& varName)
{
	string structure (
			"\t\t%TYPE% %NAME%;\n\n"
			);
	_varName = varName;
	string name = "C_" + varName;
	string type = _realCType.substr(0, _realCType.size()-2);
	stringReplace(structure, "TYPE", type);
	stringReplace(structure, "NAME", name);

	f << structure;
}

string BoolWrapper::getJNIParameterName(const string& varName)
{
	return "&C_" + varName;
}

void BoolWrapper::getReturnValue(ofstream& f)
{
	//Return the value of the C boolean to Java.
	string structure (
			"\t\tjclass boolWrp;\n"
			"\t\tjmethodID setVal;\n"
			"\t\tjboolean arg;\n"
			"\t\tboolWrp = (*env)->GetObjectClass(env, %CNAME%);\n"
			"\t\tsetVal = (*env)->GetMethodID(env, boolWrp, \"setValue\", \"(Z)V\");\n" 
			"\t\targ = (jboolean) %NAME%;\n"
			"\t\t(*env)->CallVoidMethod(env, %CNAME%, setVal, arg);\n\n"
			);

	stringReplace(structure, "CNAME", _varName);
	stringReplace(structure, "NAME", "C_" + _varName);
	f << structure;
}

