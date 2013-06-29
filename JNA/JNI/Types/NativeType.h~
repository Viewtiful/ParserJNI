/** @file
 *
 * Header for Types
 */

#ifndef __JNI_NATIVETYPE_H
#define __JNI_NATIVETYPE_H
#include "JNI/Types/Type.h"
#include <iostream>
#include <string>
namespace nsJNI {
    class NativeType : public Type
    {
      public:
        virtual ~NativeType();
		NativeType(const string& javaType,const string& jniType,const string& VMSignature,bool isNativeType);
        std::string outputJava();
        std::string outputJNI();
        bool isNativeType();
        bool isAddressWrapper();
        bool isBooleanWrapper();
        void prepareCall(ofstream& f, string& varName);
        string getJNIParameterName(string& varName);
        void getReturnValue(ofstream& f);
        protected:
        bool _isNativeType;
        string _jniType;
       
    };
}

#endif

