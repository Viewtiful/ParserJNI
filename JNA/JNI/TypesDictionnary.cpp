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
	conversionMap["short"] = new NativeType("short","jshort","S"); 
	conversionMap["int"] = new NativeType("int","jint","I");
	conversionMap["long"] = new NativeType("long","jlong","J");
	conversionMap["float"] = new NativeType("float","jfloat","F");
	conversionMap["double"] = new NativeType("double","jdouble","D");
	conversionMap["bool"] = new NativeType("boolean","jboolean","Z");
	conversionMap["char"] = new NativeType("byte","jbyte","B");
	conversionMap["void"] = new NativeType("void","void","V");

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

