/** @file
 *
 * Body for TypesDictionnary class
 */

#include <fstream>
#include "JNI/TypesDictionnary.h"
#define TYPESDICTIONNARY nsJNI::TypesDictionnary

TYPESDICTIONNARY::TypesDictionnary()
{
    addBaseType();
    
}

TYPESDICTIONNARY::~TypesDictionnary()
{
    
}


void TYPESDICTIONNARY::addBaseType()
{
	conversionMap["short"] = new NativeType("short","jshort"); 
	conversionMap["int"] = new NativeType("int","jint");
	conversionMap["long"] = new NativeType("long","jlong");
	conversionMap["float"] = new NativeType("float","jfloat");
	conversionMap["double"] = new NativeType("double","jdouble");
	conversionMap["bool"] = new NativeType("boolean","jboolean");
	conversionMap["char"] = new NativeType("byte","jbyte");



}

void TYPESDICTIONNARY::convertJava(Module::vector modules)
{
	
}

void TYPESDICTIONNARY::convertCpp(Module::vector modules)
{


}

string TYPESDICTIONNARY::getJavaType(string Ctype)
{
	return conversionMap[Ctype]->getJavaType();
}

string TYPESDICTIONNARY::getCppType(string Ctype)
{
	return conversionMap[Ctype]->getCppType();
}
#undef TYPESDICTIONNARY

