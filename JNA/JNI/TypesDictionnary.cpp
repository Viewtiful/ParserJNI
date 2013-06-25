/** @file
 *
 * Body for TypesDictionnary class
 */

#include <fstream>
#include "JNI/TypesDictionnary.h"
#include <cstdlib>
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

	addToMap("short", new NativeType("short","jshort","S",true));
	addToMap("int", new NativeType("int","jint","I",true));
	addToMap("long", new NativeType("long","jlong","J",true));
	addToMap("float", new NativeType("float","jfloat","F",true));
	addToMap("double", new NativeType("double","jdouble","D",true));
	addToMap("bool", new NativeType("boolean","jboolean","Z",true));
	addToMap("char", new NativeType("byte","jbyte","B",true));
	addToMap("void", new NativeType("void","void","V",true));
	addToMap("size_t", new NativeType("long","jlong","J",true));
	//addToMap("char*", new NativeType("String","jstring","Ljava/lang/String;"));
	addToMap("const char *", new NativeType("String","jstring","Ljava/lang/String;",true));
	addToMap("const void *", new Array("char","[B",this));
	addToMap("void *", new NativeType("byte","jbyte","B",true));
	addToMap("char *", new NativeType("byte","jbyte","B",true));
	addToMap("AddressWrapper",new NativeType("AddressWrapper","jobject","O",false));	
	addToMap("bool *",new NativeType("BoolWrapper","jobject","O",false));	
	
	//Native types
	//_conversionMap["short"] = new NativeType("short","jshort","S"); 
	//_conversionMap["int"] = new NativeType("int","jint","I");
	//_conversionMap["long"] = new NativeType("long","jlong","J");
	//_conversionMap["float"] = new NativeType("float","jfloat","F");
	//_conversionMap["double"] = new NativeType("double","jdouble","D");
	//_conversionMap["bool"] = new NativeType("boolean","jboolean","Z");
	//_conversionMap["char"] = new NativeType("byte","jbyte","B");
	//_conversionMap["void"] = new NativeType("void","void","V");
	//_conversionMap["size_t"] = new NativeType("long","jlong","J");
    //_conversionMap["char *"] = new NativeType("String","jstring","Ljava/lang/String;");
	
	
	addToMap("shortArray", new Array("short","[S",this));
	addToMap("intArray", new Array("int","[I",this));
	addToMap("longArray", new Array("long","[J",this));
	addToMap("floatArray", new Array("float","[F",this));
	addToMap("doubleArray", new Array("double","[D",this));
	addToMap("boolArray", new Array("boolean","[Z",this));
	addToMap("charArray", new Array("char","[B",this));
	addToMap("size_tArray", new Array("long","[J",this));
	addToMap("const void *Array", new Array("const void *","[B",this));
	addToMap("void *Array", new Array("void *","[B",this));
	
	//Array Types
	//_conversionMap["shortArray"] = new Array("short","[S",this);
	//_conversionMap["intArray"] = new Array("int","[I",this);
	//_conversionMap["longArray"] = new Array("long","[J",this);
	//_conversionMap["floatArray"] = new Array("float","[F",this);
	//_conversionMap["doubleArray"] = new Array("double","[D",this);
	//_conversionMap["boolArray"] = new Array("boolean","[Z",this);
	//_conversionMap["charArray"] = new Array("byte","[B",this);
	//_conversionMap["size_tArray"] = new Array("long","[J",this);
	
	//Pointer type
	//_conversionMap["short *"] = new Pointer("ptr","short",this);
	//_conversionMap["int *"] = new Pointer("ptr","int",this);
	//_conversionMap["long *"] = new Pointer("ptr","long",this);
	//_conversionMap["float *"] = new Pointer("ptr","float",this);
	//_conversionMap["double *"] = new Pointer("ptr","double",this);
	//_conversionMap["bool *"] = new Pointer("ptr","bool",this);
	//_conversionMap["char *"] = new Pointer("ptr","char",this);
	//_conversionMap["void *"] = new Pointer("ptr","void",this);
	//_conversionMap["size_t *"] = new Pointer("ptr","size_t",this);
	
	
	/*addToMap("short *", new Pointer("ptr","short",this));
	addToMap("int *", new Pointer("ptr","int",this));
	addToMap("long *", new Pointer("ptr","long",this));
	addToMap("float *", new Pointer("ptr","float",this));
	addToMap("double *", new Pointer("ptr","double",this));
	addToMap("bool *", new Pointer("ptr","bool",this));
	addToMap("char *", new Pointer("ptr","char",this));
	addToMap("size_t *", new Pointer("ptr","size_t",this));*/
	
}

void TYPESDICTIONNARY::convertJava(const Module::vector& modules)
{
	
}

void TYPESDICTIONNARY::convertJNI(const Module::vector& modules)
{

}

bool TYPESDICTIONNARY::isNativeType(const string &type)
{
	static int i = 0;
	cout << "Beta" << endl;
	cout << "Type = " << type << "Call " << i << endl;
	i++;
	if(i>10)
		exit(1);
	return _conversionMap[type]->isNativeType();
}

int TYPESDICTIONNARY::nbIndirections(const string& CType)
{
	cout << "début indirection" << endl;
	int strSize = CType.size();
	int nbIndirection = 0;
	for(int i = strSize-1 && CType[i]=='*';i>0;i--)
		nbIndirection++;
	cout << "fin indirection" << endl;
	return nbIndirection;
}

string TYPESDICTIONNARY::getRealType(const string& CType)
{
	int i;
	for(i = CType.size()-1;i>0 && CType[i]=='*';i--);

	return CType.substr(0,i);
}	
					
string TYPESDICTIONNARY::convertJava(const string& Ctype)
{
	Type *object = NULL;
	/*
	if(indirections>0 && _conversionMap.count(Ctype)==0)
	{
		string realType = getRealType(Ctype);
		//cout << "Add pointer" << endl;
		object = new Pointer("bla",realType,this);
		//cout << "realType =" << realType << "CType = " << Ctype << endl;
		addToMap(Ctype,object);
		return object->outputJava();		
	}
	*/
	cout << "Converting to Java : "<< Ctype << endl;
	if(_conversionMap.count(Ctype)==1)
		object = _conversionMap[Ctype];
		
	assert(object!=NULL);
	//cout << "signature = " << object->getVMSignature() << endl;
	return object->outputJava();
	
}

int TYPESDICTIONNARY::countAt(const string& Ctype)
{
	return _conversionMap.count(Ctype);
}

string TYPESDICTIONNARY::convertJNI(const string& Ctype)
{
	Type *object =  _conversionMap[Ctype];
	assert(object!=NULL);
	return object->outputJNI();
}

string TYPESDICTIONNARY::convertVM(const string& Ctype)
{
	Type *object =  _conversionMap[Ctype];
	assert(object!=NULL);
	return object->getVMSignature();
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
		if(haveTypedef && !haveFields && (isTypedefPointer || isDeepPointer))
      	{
      		addToMap(CStruct.getTypedef(), new Pointer("J",CStruct.getTypedef(),this,false));
      		cout << "Typedef = "<< CStruct.getTypedef() << endl;
      		//_conversionMap[CStruct.getTypedef()] = new Pointer("J",CStruct.getTypedef(),this);
      	}	
      	else if(haveTypedef && haveFields && !isTypedefPointer && !isDeepPointer)
      	{
      		addToMap(CStruct.getTypedef(), new Struct("jobject",CStruct,this));
      		//_conversionMap[CStruct.getTypedef()] = new Struct("jobject",CStruct,this);
	    }  	
   }
  
}

void TYPESDICTIONNARY::addEnums(ofstream &f, const nsC::Enum::vector &enums) {
	Enum::create(f, enums, this);
}

void TYPESDICTIONNARY::addToMap(const string& cType, Type *type) {
	int size = _conversionMap.size();
	int sizeCType = _conversionMap.count(cType);
	cout << "insert= "<< cType << endl;
	cout << cType << ": " << (_conversionMap.count(cType)) << endl ;
	assert(_conversionMap[cType]==NULL);
	_conversionMap[cType] = type;
	assert(_conversionMap[cType]==type);
	cout << "Size now = " << _conversionMap.size() << " " << "Size before =" << size << endl;
	assert(_conversionMap.size()==size+1);
	assert(_conversionMap.count(cType)==sizeCType+1);
}

#undef TYPESDICTIONNARY

