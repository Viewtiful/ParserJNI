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
	//Native types
	_conversionMap["short"] = new NativeType("short","jshort","S"); 
	_conversionMap["int"] = new NativeType("int","jint","I");
	_conversionMap["long"] = new NativeType("long","jlong","J");
	_conversionMap["float"] = new NativeType("float","jfloat","F");
	_conversionMap["double"] = new NativeType("double","jdouble","D");
	_conversionMap["bool"] = new NativeType("boolean","jboolean","Z");
	_conversionMap["char"] = new NativeType("byte","jbyte","B");
	_conversionMap["void"] = new NativeType("void","void","V");
	_conversionMap["size_t"] = new NativeType("long","jlong","J");
	
	//Array Types
	_conversionMap["shortArray"] = new Array("short","[S",this);
	_conversionMap["intArray"] = new Array("int","[I",this);
	_conversionMap["longArray"] = new Array("long","[J",this);
	_conversionMap["floatArray"] = new Array("float","[F",this);
	_conversionMap["doubleArray"] = new Array("double","[D",this);
	_conversionMap["boolArray"] = new Array("boolean","[Z",this);
	_conversionMap["charArray"] = new Array("byte","[B",this);
	_conversionMap["size_tArray"] = new Array("long","[J",this);
	
}

void TYPESDICTIONNARY::convertJava(const Module::vector& modules)
{
	
}

void TYPESDICTIONNARY::convertJNI(const Module::vector& modules)
{

}

string TYPESDICTIONNARY::convertJava(const string& Ctype)
{
	return _conversionMap[Ctype]->outputJava();
}

string TYPESDICTIONNARY::convertJNI(const string& Ctype)
{
	return _conversionMap[Ctype]->outputJNI();
}

string TYPESDICTIONNARY::convertVM(const string& Ctype)
{
	return _conversionMap[Ctype]->getVMSignature();
}

void TYPESDICTIONNARY::addTypedefs(const nsC::Typedef::vector& typedefs)
{

}

void TYPESDICTIONNARY::addStruct(const nsC::Struct::vector& structs)
{
	for (nsC::Struct::vector::const_iterator iterator(structs.begin());
         iterator != structs.end();
         ++iterator)
   	{
     	const nsC::Struct CStruct(*iterator);
      	bool haveName(!CStruct.getName().empty());
      	bool haveTypedef(!CStruct.getTypedef().empty());
      	bool haveFields(CStruct.getFields().size() > 0);
      	bool isTypedefPointer(CStruct.getTypedefIndirection() == 1);
      	bool isDeepPointer(CStruct.getTypedefIndirection() > 1);
		cout << "1" << endl;
      	if(haveTypedef && !haveFields && (isTypedefPointer || isDeepPointer))
      		_conversionMap[CStruct.getTypedef()] = new Pointer("J",CStruct.getTypedef(),this);
      		
      	else if(haveTypedef && haveFields && !isTypedefPointer && !isDeepPointer)
      		_conversionMap[CStruct.getTypedef()] = new Struct("idk",CStruct,this);
	      	
   }
}

void TYPESDICTIONNARY::addEnums(const nsC::Enum::vector &enums) {
	Enum::create(enums, this);
}

void TYPESDICTIONNARY::addToMap(const string& cType, Type *type) {
	_conversionMap[cType] = type;
}

#undef TYPESDICTIONNARY

