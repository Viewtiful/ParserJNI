#include "JNI/Types/Typedef.h"

using namespace std;
using namespace nsJNI;

Typedef::Typedef(string javaType, string cppType, string VMSignature, string structName) : Type(javaType,cppType,VMSignature)
{	
	this->structName = structName;
}

Typedef::~Typedef()
{

}

std::string Typedef::outputJava()
{



}


std::string Typedef::outputCpp()
{




}

