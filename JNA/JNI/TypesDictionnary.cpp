/** @file
 *
 * Body for TypesDictionnary class
 */

#include <fstream>
#include "Utils/Output.h"
#include "Utils/Utils.h"
#include "Utils/Parameters.h"
#include "JNA/Struct.h"
#include "JNA/Enum.h"
#include "JNA/NativeType.h"
#include "JNA/Callback.h"
#include "JNI/TypesDictionnary.h"

using std::string;
using std::ofstream;
using nsModules::Module;
using nsJNA::Type;
using nsUtils::Output;
using nsUtils::createJavaFileName;
using nsUtils::createPackageTree;
using nsUtils::Parameters;
using nsC::Param;
using nsJNA::Struct;
using nsJNA::Enum;
using nsJNA::NativeType;
using nsJNA::Callback;

#define TYPESDICTIONNARY nsJNI::TypesDictionnary

TYPESDICTIONNARY::TypesDictionnary()
{
    
    //Adding java types from C
    addJavaType("int","int");
    addJavaType("float","float");
    addJavaType("double","double");
    addJavaType("char","byte");
    addJavaType("void","void");
    addJavaType("short","short");
    addJavaType("bool","boolean");
	addJavaType("long","long");
	
	//Adding Cpp type
	addCppType("int","jint");
    addCppType("float","jfloat");
    addCppType("double","jdouble");
    addCppType("char","jbyte");
    addCppType("void","void");
    addCppType("short","jshort");
    addCppType("bool","jboolean");
	addCppType("long","jlong");
	
	
}

TYPESDICTIONNARY::~TypesDictionnary()
{
    
}


void TYPESDICTIONNARY::addJavaType(std::string inputType, std::string javaType)
{
	toJavaType.insert(std::pair<std::string,std::string>(inputType,javaType) );	
}

void TYPESDICTIONNARY::addCppType(std::string inputType, std::string cppType)
{
	toCppType.insert(std::pair<std::string,std::string>(inputType,cppType) );	
}

std::string TYPESDICTIONNARY::getJavaType(std::string inputType)
{
	return toJavaType[inputType];
}

std::string TYPESDICTIONNARY::getCppType(std::string inputType)
{
	return toCppType[inputType];

}



#undef TYPESDICTIONNARY

