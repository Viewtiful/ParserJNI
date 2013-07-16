/** @file
 *
 * Body for TypesDictionnary class
 */
 
#include "JNI/TypesDictionnary.h"
#include <fstream>
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
    _fcts.clear();

    for ( std::map<std::string, Type*>::iterator it = _conversionMap.begin(); it != _conversionMap.end(); ++it ) 
        delete it->second;
    _conversionMap.clear();


}

void TYPESDICTIONNARY::addBaseType(string filename)
{

	addToMap("short", new NativeType("short","jshort","S",true));
	addToMap("int", new NativeType("int","jint","I",true));
	addToMap("long", new NativeType("long","jlong","J",true));
	addToMap("float", new NativeType("float","jfloat","F",true));
	addToMap("double", new NativeType("double","jdouble","D",true));
	addToMap("bool", new NativeType("boolean","jboolean","bool","Z",true));
	addToMap("char", new NativeType("byte","jbyte","B",true));
	addToMap("void", new NativeType("void","void","V",true));
	addToMap("size_t", new NativeType("long","jlong","size_t","J",true));
	addToMap("const char *", new NativeType("String","jstring","Ljava/lang/String;",true));
	addToMap("const void *", new NativeType("byte","jbyte","B",true));
	addToMap("void *", new NativeType("byte","jbyte","B",true));
	addToMap("char *", new NativeType("byte","jbyte","B",true));
	addToMap("bool *",new BoolWrapper("bool *", "L" + filename + "$BoolWrapper;"));	
	
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

bool TYPESDICTIONNARY::isNativeType(const string &type)
{
	assert(_conversionMap.count(type)==1);
	return _conversionMap[type]->isNativeType();
}

	

Type* TYPESDICTIONNARY::getType(const string& Ctype) {
	Type *object = NULL;
	if(_conversionMap.count(Ctype) == 1)
		object = _conversionMap[Ctype];

	assert(object != NULL);
	return object;
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


void TYPESDICTIONNARY::addStruct(ofstream &f, ofstream &f2, const nsC::Struct::vector& structs)
{
	std::vector<Struct*> createdStruct;
	for (nsC::Struct::vector::const_iterator iterator(structs.begin());
         iterator != structs.end();
         ++iterator)
   	{
     		const nsC::Struct CStruct(*iterator);
     	
      		bool haveTypedef(!CStruct.getTypedef().empty());
      		bool haveFields(CStruct.getFields().size() > 0);
      		bool isTypedefPointer(CStruct.getTypedefIndirection() == 1);
      		bool isDeepPointer(CStruct.getTypedefIndirection() > 1);
		assert(haveTypedef);

		if(haveTypedef && !haveFields && (isTypedefPointer || isDeepPointer))
      			addToMap(CStruct.getTypedef(), new Pointer("J",CStruct.getTypedef(),this,false));
      		else if(haveTypedef && haveFields && !isTypedefPointer && !isDeepPointer)
      		{
      			Struct *s = new Struct(f, f2, "L"+_filename+"$"+CStruct.getTypedef() + ";",CStruct,this);
			addToMap(CStruct.getTypedef(), s);
			createdStruct.push_back(s);
        	}  	
   	}
	//Generate getter, setters for structs
	for(size_t i = 0;i<createdStruct.size();i++)
	{
		Struct *current = createdStruct[i];
		current->addStructToJava(f);
		current->addStructFunctionToJNI(f2);
		vector<nsJNI::Function*> getSet = current->getGetterSetters();
      		copy(getSet.begin(),getSet.end(),back_inserter(_fcts));
      		getSet.clear();
      	}
	createdStruct.clear();	
  		
}

void TYPESDICTIONNARY::addEnums(ofstream &f, const nsC::Enum::vector &enums) {
	Enum::create(f, enums, this);
}

void TYPESDICTIONNARY::addToMap(const string& cType, Type *type) {
	size_t size = _conversionMap.size();
	size_t sizeCType = _conversionMap.count(cType);
	assert(_conversionMap[cType]==NULL);

	_conversionMap[cType] = type;

	assert(_conversionMap[cType]==type);
	assert(_conversionMap.size()==size+1);
	assert(_conversionMap.count(cType)==sizeCType+1);
}

string TYPESDICTIONNARY::getFilename()
{
	return _filename;
}

vector<nsJNI::Function*> TYPESDICTIONNARY::getFcts()
{ 
	return _fcts;
}

void TYPESDICTIONNARY::addTypedefs(const vector<nsC::Typedef> typedefs)
{
	for(int i = 0;i<typedefs.size();i++)
	{
		string cType = typedefs[i].getCType();
		_conversionMap[cType] = new Pointer("J",cType,this,false);
		
	}
}


#undef TYPESDICTIONNARY

