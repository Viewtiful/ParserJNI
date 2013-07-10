/** @file
 *
 * Header for Types
 */

/*!
	\file NativeType.h
	\author Baptiste HAUDEGAND & Antoine MOISE
	\version 1.0
!*/
#ifndef __JNI_NATIVETYPE_H
#define __JNI_NATIVETYPE_H
#include "JNI/Types/Type.h"
#include <iostream>
#include <string>
/*!
	\namespace nsJNI 
	JNI parser namespace
!*/
namespace nsJNI {
	/*!
		\class NativeType
		\brief represents a NativeType
	*/
    class NativeType : public Type
    {
      public:
      	/*!
      	\brief destructor
      */
        virtual ~NativeType();
	/*!
        	\brief constructor with three parameters
        	Create, and initialize a type with the following arguments
        	\param javaType : the corresponding java Type
        	\param jniType : the corresponding JNI Type
        	\param VMSIgnature : signature for the java Virtual Machine
        	\param isNativeType : if this NativeType is a real NativeType
	*/
	NativeType(const string& javaType,const string& jniType,const string& VMSignature,bool isNativeType);
	/*!
        	\brief constructor with three parameters
        	Create, and initialize a type with the following arguments
        	\param javaType : the corresponding java Type
        	\param jniType : the corresponding JNI Type
		\param CType : C Type 
        	\param VMSIgnature : signature for the java Virtual Machine
        	\param isNativeType : if this NativeType is a real NativeType
	*/
	NativeType(const string& javaType, const string& jniType,const string& CType,const string& VMSignature,bool isNativeType);
        std::string outputJava();
        std::string outputJNI();
        bool isNativeType();
        bool isAddressWrapper();
        bool isBooleanWrapper();
        bool isArray();
        void prepareCall(ofstream& f, string& varName);
        string getJNIParameterName(string& varName);
        void getReturnValue(ofstream& f);
        string getCType();

        protected:
        bool _isNativeType; /*!< is a NativeType?*/
        string _jniType; /*!< The jniType*/
        string _CType; /*!< The C Type*/
       
    };
}

#endif

