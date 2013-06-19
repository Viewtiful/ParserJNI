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
		NativeType(string javaType,string jniType,string VMSignature);
        std::string outputJava();
        std::string OutputJNI();
       
    };
}

#endif

