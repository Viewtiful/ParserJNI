/** @file
 *
 * Header for JNIParser
 */

#ifndef __JNI_PARAM_H

#include <iostream>
#include <string>
using namespace std;
namespace nsJNI {
    class Param
    {
      public:
        Param(string type,string name);
		virtual ~Param();
        void convert();
      protected:
      	string _type;
      	string _name;
    };
}

#endif

