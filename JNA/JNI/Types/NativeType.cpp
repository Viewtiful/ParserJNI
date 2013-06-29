/** @file
 *
 * Body for JNIParser
 */
#define NATIVETYPE nsJNI::NATIVETYPE
#include "JNI/Types/NativeType.h"
#include "Utils/Utils.h"
using namespace nsJNI;
using namespace nsUtils;
using namespace std;

NativeType::NativeType(const string& javaType, const string& jniType,
		const string& VMSignature,bool isNativeType) : Type(javaType,
			jniType, VMSignature)
{
	_isNativeType = isNativeType;
   _jniType = jniType;
	cout << "isNativeType Value : " << _isNativeType << endl;
}


NativeType::~NativeType()
{

}

std::string NativeType::outputJava()
{
	cout << "Output Java : NativeType" << endl;
	cout << "javaType = " << getJavaType() << endl;
	return getJavaType();
}

std::string NativeType::outputJNI()
{
	return getJNIType();
}

bool NativeType::isNativeType()
{
	return _isNativeType;
}

bool NativeType::isAddressWrapper()
{
	return false;
}

void NativeType::prepareCall(ofstream& f,string& varName)
{
	string structure (
			"\t\t%TYPE% %NAME% = (%TYPE%) %NAMEBASE%;\n\n"
			);
	string type = getJNIType();
	string name = "C_" + varName;

	stringReplace(structure, "TYPE", type);
	stringReplace(structure, "NAME", name);
	stringReplace(structure, "NAMEBASE", varName);

	f << structure; 
}

string NativeType::getJNIParameterName(string& varName)
{
	return "NativeType";
}

void NativeType::getReturnValue(ofstream& f)
{
   if(_jniType != "void")
   f << "\t\t return JNI_result;\n";

}
        
