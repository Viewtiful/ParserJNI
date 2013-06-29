/** @file
 *
 * Header for Types
 */

#ifndef __JNI_POINTER_H
#define __JNI_POINTER_H
#include <string>
#include "JNI/Types/Type.h"
#include "JNI/TypesDictionnary.h"
namespace nsJNI {

	class TypesDictionnary;
    class Pointer : public Type 
    {
      public:
        virtual ~Pointer();
		Pointer(const string& vmSignature,const string& CBaseType,TypesDictionnary *dictionnary,bool isNativeType);
		std::string outputJava();
        std::string outputJNI();
        bool isNativeType();
        bool isAddressWrapper();
        void prepareCall(ofstream& f,string& varName);
        string getJNIParameterName(string& varName);
        void getReturnValue(ofstream& f);
        string getVMSignature();
      protected:
        std::string _CBaseType;
        TypesDictionnary* _dictionnary;
        bool _isNativeType;
    };
}

#endif

