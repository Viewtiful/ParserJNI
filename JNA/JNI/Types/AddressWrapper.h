/** @file
 *
 * Header for Types
 */

#ifndef __JNI_ADDRESSWRAPPER_H
#define __JNI_ADDRESSWRAPPER_H
#include "JNI/Types/Type.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
namespace nsJNI {
    class AddressWrapper : public Type
    {
      public:
        virtual ~AddressWrapper();
		AddressWrapper(string realCType, string VMSignature);
		AddressWrapper(string VMSignature);
		std::string outputJava();
        std::string outputJNI();
        bool isNativeType();
        void prepareCall(ofstream& f,string& varName);
        string getJNIParameterName(string& varName);
        void getReturnValue(ofstream& f);
        
      	protected:
      	string _realCType;
    };
}

#endif

