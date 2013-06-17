/** @file
 *
 * Header for Types
 */

#ifndef __JNI_TYPE_H
#define __JNI_TYPE_H
#include <string>
using namespace std;
namespace nsJNI {
    class Type 
    {
      public:
        virtual ~Type();
		Type(string javaType,string cppType);
		string javaType;
        string cppType;
        virtual void outputJava() = 0;
        virtual void outputCpp() = 0;
        string getJavaType();
        string getCppType();
    };
}

#endif

