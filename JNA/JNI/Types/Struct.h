/** @file
 *
 * Header for Types
 */

#ifndef __JNI_STRUCT_H
#define __JNI_STRUCT_H
#include <string>
#include "C/Struct.h"
#include "JNI/Types/Type.h"
#include "JNI/TypesDictionnary.h"
namespace nsJNI {

	 class TypesDictionnary;
    class Struct : public Type 
    {
      public:
        virtual ~Struct();
		  Struct(string javaType,string jniType,string vmSignature,nsC::Struct cStruct,TypesDictionnary *dictionnary);
		  std::string outputJava();
        std::string outputJNI();
        
      protected:
        	nsC::Struct cStruct;
        	TypesDictionnary* dictionnary;
    };
}

#endif

