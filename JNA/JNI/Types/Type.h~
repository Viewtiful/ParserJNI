/** @file
 *
 * Header for Types
 */

#ifndef __JNI_TYPE_H
#define __JNI_TYPE_H
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
namespace nsJNI {
    class Type 
    {
      public:
        virtual ~Type();
		Type(string javaType, string jniType, string VMSignature);
		Type(string VMSignature);
		virtual std::string outputJava() =0;
        virtual std::string outputJNI() =0;
        virtual bool isNativeType() =0;
        virtual void prepareCall(ofstream& f,string& varName) =0;
        virtual string getJNIParameterName(string& varName) =0;
        virtual void getReturnValue(ofstream& f) =0;
        string getJavaType();
        string getJNIType();
        string getVMSignature();
        
      protected:
      	string _javaType;
      	string _jniType;
    	string _VMSignature;
      	
    };
}

#endif

