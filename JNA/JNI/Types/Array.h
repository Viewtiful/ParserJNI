/** @file
 *
 * Header for Types
 */

#ifndef __JNI_ARRAY_H
#define __JNI_ARRAY_H
#include <string>
#include "C/Struct.h"
#include "JNI/Types/Type.h"
#include "JNI/TypesDictionnary.h"
namespace nsJNI {

	class TypesDictionnary;
    class Array : public Type 
    {
      public:
        virtual ~Array();
		Array(string CBaseType, string vmSignature, TypesDictionnary *dictionnary) ;
		std::string outputJava();
        std::string outputJNI() ;
        std::string getCBaseTypeFromPointer(string pointerType);

      protected:
        TypesDictionnary* _dictionnary;
        std::string _CBaseType;
    };
}

#endif

