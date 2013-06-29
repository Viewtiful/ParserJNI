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
		Array(const string& CBaseType, const string& vmSignature, TypesDictionnary *dictionnary) ;
		std::string outputJava();
        std::string outputJNI() ;
        bool isNativeType();
		  bool isAddressWrapper();
        void prepareCall(ofstream& f,std::string& varName);
        std::string getJNIParameterName(std::string& varName);
        void getReturnValue(ofstream& f);
        
      protected:
        TypesDictionnary* _dictionnary;
        std::string _CBaseType;
    };
}

#endif

