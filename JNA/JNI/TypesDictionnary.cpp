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

void TYPESDICTIONNARY::convertJNI(Module::vector modules)
{

}

string TYPESDICTIONNARY::convertJava(string Ctype)
{
	return _conversionMap[Ctype]->outputJava();
}

string TYPESDICTIONNARY::convertJNI(string Ctype)
{
	return _conversionMap[Ctype]->OutputJNI();
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
	for (nsC::Struct::vector::const_iterator iterator(structs.begin());
         iterator != structs.end();
         ++iterator)
   {
      const nsC::Struct CStruct(*iterator);
      bool haveName(!CStruct.getName().empty());
      bool haveTypedef(!CStruct.getTypedef().empty());
      bool haveFields(CStruct.getFields().size() != 0);
      bool isTypedefPointer(CStruct.getTypedefIndirection() == 1);

      if (haveName && !haveTypedef) {
         std::cout << CStruct.getName() << std::endl;
         /*_conversionMap[CStruct.getName()] = */
         Struct ee = new Struct(CStruct.getName(), CStruct.getName(), "idk", CStruct, this);
      }
      if(haveTypedef)
          std::cout << CStruct.getTypedef() << std::endl;
      if(haveFields)
         std::cout << "create structure" << std::endl;
      if(isTypedefPointer)
         std::cout << "crée un typedef " << CStruct.getTypedef() << std::endl;
      

   }
}

#undef TYPESDICTIONNARY

