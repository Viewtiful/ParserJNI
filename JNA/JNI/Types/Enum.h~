

#ifndef __JNI_ENUM_H
#define __JNI_ENUM_H
#include "JNI/Types/Type.h"
#include "C/Enum.h"
#include "JNI/TypesDictionnary.h"
#include "Modules/Module.h"

namespace nsJNI{

   class TypesDictionnary;
	class Enum : public Type
	{
	   public : 
         virtual ~Enum();
       
	      static bool create(const nsC::Enum::vector& en, TypesDictionnary *dictionnary);
         std::string outputJava();
         std::string outputJNI();

      protected : 
         nsC::Enum _cEnum;

         Enum(string javaType,string jniType,string vmSignature,nsC::Enum cEnum);
	};
}
#endif
