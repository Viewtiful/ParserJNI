/** @file
 *
 * Body for JNIParser
 */
#define POINTER nsJNI::POINTER
#include "JNI/Types/Pointer.h"
using namespace nsJNI;
using namespace std;

Pointer::Pointer(const string& VMSignature,const string& CBaseType,TypesDictionnary *dictionnary) : Type("long","jlong",VMSignature)
{
	cout << "toto" << endl;
	this->_CBaseType = CBaseType;
	this->_dictionnary = dictionnary;
	
}


Pointer::~Pointer()
{

}

std::string Pointer::outputJava()
{
	return getJavaType();
}

std::string Pointer::outputJNI()
{
	return getJNIType();
}


