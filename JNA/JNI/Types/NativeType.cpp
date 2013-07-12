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
   _CType = javaType;
}

NativeType::NativeType(const string& javaType, const string& jniType,const string& CType,
		const string& VMSignature,bool isNativeType) : Type(javaType,
			jniType, VMSignature)
{
	_isNativeType = isNativeType;
   _jniType = jniType;
	_CType = CType;
}
NativeType::~NativeType()
{
}

std::string NativeType::outputJava()
{
	return getJavaType();
}

string NativeType::getCType()
{
	return _CType;
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

bool NativeType::isBooleanWrapper()
{
	return false;
}

bool NativeType::isArray()
{
	return false;
}

void NativeType::prepareCall(ofstream& f,string& varName)
{
	string type = getCType();
	string name = "C_" + varName;
      
   //If it's not a string, we do the normal thing. Casting from JNI types to C.
   if(_jniType != "jstring") {
	   string structure (
			   "\t\t%TYPE% %NAME% = (%TYPE%) %NAMEBASE%;\n\n"
			   );

      stringReplace(structure, "TYPE", type);
      stringReplace(structure, "NAME", name);
      stringReplace(structure, "NAMEBASE", varName);

	   f << structure; 
   }
   //If it's a string, we get the string from Java.
   else {
      string structure (
            "\t\t%TYPE% %NAME%;\n"
            "\t\t%NAME% = (%TYPE%)(*env)->Get%TYPEMAJ%UTFChars(env, %CNAME%, NULL);\n"
            "\t\tif(%NAME% == NULL) {\n"
            "\t\t\t fprintf(stderr, \" Out of memory\");\n"
            "\t\t\t exit(1);\n"
            "\t\t}\n\n"
            );

      string typeMaj = toJavaName(type, false, false, true);

      stringReplace(structure, "TYPEMAJ", typeMaj);
      stringReplace(structure, "NAME", name);
      stringReplace(structure, "CNAME", varName);
      stringReplace(structure, "TYPE", "char *");

      f << structure;
   }
}

string NativeType::getJNIParameterName(string& varName)
{
	return "NativeType";
}

void NativeType::getReturnValue(ofstream& f)
{
   //Return type == void to nothing.
	if(_jniType == "void") 
		return ;
		
   //Return type == string, create an object for Java and return it.
	else if(_jniType == "jstring") 
	{
      string structure (
               "\t\tJNI_result = (*env)->New%TYPEMAJ%UTF(env, tempJNI_result);\n"
		         );
      string type = getJNIType();
      string typeMaj = type.substr(1, type.size());
	 	typeMaj = toJavaName(typeMaj, false, false, true);

      stringReplace(structure, "TYPEMAJ", typeMaj);

      f << structure;
	}

	f << "\t\t return JNI_result;\n";
	   
}        
