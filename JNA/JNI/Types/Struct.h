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
		Struct(const string& vmSignature,const nsC::Struct& cStruct,TypesDictionnary *dictionnary);
		std::string outputJava();
        std::string outputJNI();
        bool isNativeType();
      protected:
        nsC::Struct _cStruct;
        TypesDictionnary* _dictionnary;
    };
}

#endif

