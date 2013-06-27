

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
       
	    static bool create(ofstream &f, const nsC::Enum::vector& en, TypesDictionnary *dictionnary,string filename);
        std::string outputJava();
        std::string outputJNI();
        void addEnumToJava(ofstream &f);
        bool isNativeType();
        void prepareCall(ofstream& f,string& varName);
        string getJNIParameterName(string& varName);
        void getReturnValue(ofstream& f);
        
      protected : 
         nsC::Enum _cEnum;

         Enum(ofstream &f, const string& javaType,const string& jniType,const string& vmSignature,const nsC::Enum& cEnum);
	};
}
#endif
