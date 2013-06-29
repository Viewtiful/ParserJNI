/** @file
 *
 * Header for Types
 */

#ifndef __JNI_SPECIALTYPE_H
#define __JNI_SPECIALTYPE_H
#include "JNI/Types/Type.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
namespace nsJNI {
    class BoolWrapper : public Type
    {
      public:
        virtual ~BoolWrapper();
		BoolWrapper(string realCType, string VMSignature);
		BoolWrapper(string VMSignature);
		std::string outputJava();
        std::string outputJNI();
        bool isNativeType();
        bool isAddressWrapper();
        bool isBooleanWrapper();
        bool isArray();
        void prepareCall(ofstream& f,string& varName);
        string getJNIParameterName(string& varName);
        void getReturnValue(ofstream& f);
        
      	protected:
      	string _realCType;
         string _varName;
    };
}

#endif

