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
   if(_jniType != "jstring") {
	   string structure (
			   "\t\t%TYPE% %NAME% = (%TYPE%) %NAMEBASE%;\n\n"
			   );
	   string type = getJNIType();    //get C type !!!!!! probleme
	   string name = "C_" + varName;

      stringReplace(structure, "TYPE", type);
      stringReplace(structure, "NAME", name);
      stringReplace(structure, "NAMEBASE", varName);

	   f << structure; 
   }
   else {
      string structure (
            "\t\t%TYPE% %NAME%;\n"
            "\t\t%NAME% = (%TYPE%)(*env)->Get%TYPEMAJ%UTFChars(env, %CNAME%, NULL);\n"
            "\t\tif(%NAME% == NULL) {\n"
            "\t\t\t fprintf(stderr, \" Out of memory\");\n"
            "\t\t\t exit(1);\n"
            "\t\t}\n\n"
            );
      string type = getJNIType();
	   string name = "C_" + varName;
      string typeMaj = type.substr(1, type.size());
      typeMaj = toJavaName(typeMaj, false, false, true);

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
   if(_jniType != "void") {
      
      if(_jniType == "jstring") {
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
}
        
