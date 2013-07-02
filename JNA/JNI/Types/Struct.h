/** @file
 *
 * Header for Types
 */

/*!
	\file Struct.h
	\author Baptiste HAUDEGAND & Antoine MOISE
	\version 1.0
!*/
#ifndef __JNI_STRUCT_H
#define __JNI_STRUCT_H
#include <string>
#include "C/Struct.h"
#include "JNI/Types/Type.h"
#include "JNI/TypesDictionnary.h"
/*!
	\namespace nsJNI 
	JNI parser namespace
!*/
namespace nsJNI {

	 class TypesDictionnary;
	 /*!
		\class Struct
		\brief represents a Struct
	*/
    class Struct : public Type 
    {
      public:
      /*!
      	\brief destructor
      */
        virtual ~Struct();
		Struct(ofstream &f, const string& vmSignature,const nsC::Struct& cStruct,TypesDictionnary *dictionnary);
		std::string outputJava();
     	void addStructToJava(ofstream &f);
        std::string outputJNI();
        bool isNativeType();
        bool isAddressWrapper();
        bool isBooleanWrapper();
        bool isArray();
        void prepareCall(ofstream& f,string& varName);
        string getJNIParameterName(string& varName);
        void getReturnValue(ofstream& f);
      protected:
        nsC::Struct _cStruct;
        TypesDictionnary* _dictionnary;
    };
}

#endif

