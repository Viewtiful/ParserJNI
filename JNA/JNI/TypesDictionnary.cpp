/** @file
 *
 * Body for TypesDictionnary class
 */

#include <fstream>
#include "JNI/TypesDictionnary.h"
#define TYPESDICTIONNARY nsJNI::TypesDictionnary
using namespace nsJNI;
using namespace nsC;
using namespace nsModules;
TYPESDICTIONNARY::TypesDictionnary()
{
	addBaseType();   
}

TYPESDICTIONNARY::~TypesDictionnary()
{
    
}


void TYPESDICTIONNARY::addBaseType()
{
	_conversionMap["short"] = new NativeType("short","jshort","S"); 
	_conversionMap["int"] = new NativeType("int","jint","I");
	_conversionMap["long"] = new NativeType("long","jlong","J");
	_conversionMap["float"] = new NativeType("float","jfloat","F");
	_conversionMap["double"] = new NativeType("double","jdouble","D");
	_conversionMap["bool"] = new NativeType("boolean","jboolean","Z");
	_conversionMap["char"] = new NativeType("byte","jbyte","B");
	_conversionMap["void"] = new NativeType("void","void","V");
	_conversionMap["size_t"] = new NativeType("long","jlong","J");
}

void TYPESDICTIONNARY::convertJava(Module::vector modules)
{
	
}

void TYPESDICTIONNARY::convertCpp(Module::vector modules)
{

}

string TYPESDICTIONNARY::convertJava(string Ctype)
{
	return _conversionMap[Ctype]->outputJava();
}

string TYPESDICTIONNARY::convertCpp(string Ctype)
{
	return _conversionMap[Ctype]->outputCpp();
}

string TYPESDICTIONNARY::convertVM(string Ctype)
{
	return _conversionMap[Ctype]->getVMSignature();
}

int TYPESDICTIONNARY::nbIndirections(string CType)
{
	int strSize = CType.size();
	int nbIndirection = 0;
	for(int i = strSize-1;i>-1;i--)
		nbIndirection++;
	return nbIndirection;

}

void TYPESDICTIONNARY::addTypedefs(nsC::Typedef::vector typedefs)
{

}
void TYPESDICTIONNARY::addStruct(nsC::Struct::vector structs)
{
	
}

#undef TYPESDICTIONNARY

