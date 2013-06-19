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
	conversionMap["short"] = new NativeType("short","jshort","S"); 
	conversionMap["int"] = new NativeType("int","jint","I");
	conversionMap["long"] = new NativeType("long","jlong","J");
	conversionMap["float"] = new NativeType("float","jfloat","F");
	conversionMap["double"] = new NativeType("double","jdouble","D");
	conversionMap["bool"] = new NativeType("boolean","jboolean","Z");
	conversionMap["char"] = new NativeType("byte","jbyte","B");
	conversionMap["void"] = new NativeType("void","void","V");
	conversionMap["size_t"] = new NativeType("long","jlong","J");
}

void TYPESDICTIONNARY::convertJava(Module::vector modules)
{
	
}

void TYPESDICTIONNARY::convertCpp(Module::vector modules)
{

}

string TYPESDICTIONNARY::convertJava(string Ctype)
{
	return conversionMap[Ctype]->outputJava();
}

string TYPESDICTIONNARY::convertCpp(string Ctype)
{
	return conversionMap[Ctype]->outputCpp();
}

string TYPESDICTIONNARY::convertVM(string Ctype)
{
	return conversionMap[Ctype]->getVMSignature();
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
	for(int i = 0;i<typedefs.size();i++)
	{
	
		
	
	}

}
void TYPESDICTIONNARY::addStruct(nsC::Struct::vector structs)
{
	string javaType = "struct";
	string cppType = "struct";
	string vmSignature = "test";
	for(int i = 0;i<structs.size();i++)
	{
		nsJNI::Struct *test = new nsJNI::Struct(javaType, cppType, vmSignature, structs[i], this) ;
		conversionMap[structs[i].getTypedef()] = test; 
		test->outputJava();
	}
}
#undef TYPESDICTIONNARY

