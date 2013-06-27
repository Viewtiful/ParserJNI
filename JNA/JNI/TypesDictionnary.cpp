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

TYPESDICTIONNARY::TypesDictionnary(string filename)
{
	_filename = filename;
	addBaseType(filename);
	   
}

TYPESDICTIONNARY::~TypesDictionnary()
{
    
}

void TYPESDICTIONNARY::addBaseType(string filename)
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
	addToMap("const char *", new NativeType("String","jstring","Ljava/lang/String;",true));
	addToMap("const void *", new NativeType("byte","jbyte","B",true));
	addToMap("void *", new NativeType("byte","jbyte","B",true));
	addToMap("char *", new NativeType("byte","jbyte","B",true));
	addToMap("AddressWrapper", new NativeType("AddressWrapper","jobject","L" + filename + "$AddressWrapper;",false));	
	addToMap("bool *",new NativeType("BoolWrapper","jobject","L" + filename + "$BoolWrapper;",false));	
	
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
}

void TYPESDICTIONNARY::convertJava(const Module::vector& modules)
{
	
}

void TYPESDICTIONNARY::convertJNI(const Module::vector& modules)
{

}

bool TYPESDICTIONNARY::isNativeType(const string &type)
{
	static int call = 0;
	cout << "Beta" << endl;
	cout << "Type = " << type << "Call : " << call << endl;
	assert(_conversionMap.count(type)==1);
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
	cout << "Converting to Java : "<< Ctype << endl;
	if(_conversionMap.count(Ctype)==1)
		object = _conversionMap[Ctype];
		
	assert(object!=NULL);
	return object->outputJava();
	
}

int TYPESDICTIONNARY::countAt(const string& Ctype)
{
	return _conversionMap.count(Ctype);
}

string TYPESDICTIONNARY::convertJNI(const string& Ctype)
{
	Type *object = NULL;
	cout << "Converting to JNI : "<< Ctype << endl;
	if(_conversionMap.count(Ctype)==1)
		object = _conversionMap[Ctype];
		
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

void TYPESDICTIONNARY::addStruct(ofstream &f, const nsC::Struct::vector& structs)
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
      		addToMap(CStruct.getTypedef(), new Struct(f, "L"+_filename+"$"+CStruct.getTypedef() + ";",CStruct,this));
      		//_conversionMap[CStruct.getTypedef()] = new Struct("jobject",CStruct,this);
	    }  	
   }
  
}

void TYPESDICTIONNARY::addEnums(ofstream &f, const nsC::Enum::vector &enums) {
	Enum::create(f, enums, this,_filename);
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

