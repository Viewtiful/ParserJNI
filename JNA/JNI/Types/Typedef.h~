/** @file
 *
 * Header for the TypesDictionnary class
 */

#ifndef __JNI_TYPEDEF_H
#define __JNI_TYPEDEF_H

#include <string>
#include <iostream>
#include <map>
#include "JNI/Types/Type.h"
using namespace std;
namespace nsJNI
{
    class Typedef : public Type
    {
		public:
	        Typedef(string javaType, string cppType, string VMSignature, string structName);
	        virtual ~Typedef();
	        std::string outputJava();
        	std::string outputJNI();
        	string getStructName();
        	string getTargetType();
        	bool isNativeType();
        	
        	void prepareCall(ofstream& f,string& varName);
        	string getJNIParameterName(string& varName);
        	virtual void getReturnValue(ofstream& f) =0;
        
		protected:
			string _structName;
			string _targetType;	
    };
}

#endif

