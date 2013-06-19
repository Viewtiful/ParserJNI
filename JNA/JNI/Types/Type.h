/** @file
 *
 * Header for Types
 */

#ifndef __JNI_TYPE_H
#define __JNI_TYPE_H
#include <string>
#include <iostream>
using namespace std;
namespace nsJNI {
    class Type 
    {
      public:
        virtual ~Type();
		Type(string javaType,string cppType,string VMSignature);
		virtual std::string outputJava() =0;
        virtual std::string outputCpp() =0;
        
        string getJavaType();
        string getCppType();
        string getVMSignature();
        
      protected:
      	string _javaType;
      	string _cppType;
      	string _VMSignature;
      
    };
}

#endif

