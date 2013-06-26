/** @file
 *
 * Header for JNIParser
 */

#ifndef __JNI_PARAM_H
#define __JNI_PARAM_H
#include <iostream>
#include <string>
using namespace std;
namespace nsJNI {
    class Param
    {
      public:
        Param(const string& type,const string& name);
		virtual ~Param();
        void convert();
        std::string& getType();
        std::string& getName();
        bool isNativeType();
      protected:
      	string _type;
      	string _name;
    };
}

#endif

