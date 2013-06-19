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
        	std::string outputCpp();
        	string getStructName();
        	string getTargetType();
        
		protected:
			string _structName;
			string _targetType;	
    };
}

#endif

