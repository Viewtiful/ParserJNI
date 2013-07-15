/** @file
 * @defgroup Types All the types used by the JNIParser
 * Header for Types
 */

#ifndef __JNI_TYPE_H
#define __JNI_TYPE_H
#include <string>
#include <iostream>
#include <fstream>

/** @addtogroup Types
 * @{ */

/*!
	\file Type.h
	\author Baptiste HAUDEGAND & Antoine MOISE
	\version 1.0
!*/

using namespace std;
/*!
	\namespace nsJNI 
	JNI parser namespace
!*/

namespace nsJNI {
	/*!
		\class Type
		\brief represents an abstract Type
	*/
    class Type 
    {
      public:
      /*!
      	\brief destructor
      */
        virtual ~Type();
        /*!
        	\brief constructor with three parameters
        	Create, and initialize a type with the following arguments
        	\param javaType : the corresponding java Type
        	\param jniType : the corresponding JNI Type
        	\param VMSIgnature : signature for the java Virtual Machine
        */
		Type(string javaType, string jniType, string VMSignature);
		
		/*!
        	\brief constructor with one parameter
        	Create, and initialize a type with the following argument : 
        	\param VMSIgnature : signature for the java Virtual Machine
        */
		Type(string VMSignature);
		
		/*!
			\brief Convert a type to java Type
			\return the javaType
		*/
		virtual std::string outputJava() = 0;
		
		/*!
			\brief Convert a type to JNI Type
			\return the JNI Type
		*/
		virtual std::string outputJNI() = 0;
        
        	/*!
			\brief verify is this type is derived from a Native Type such as 'int, float...'
			\return true if it is a NativeType, false else;
		*/
        	virtual bool isNativeType() = 0;
        
        
        	/*!
			\brief verify is this type is an AddressWrapper
			\return true if it is an AddressWrapper, false else;
		*/
       		 virtual bool isAddressWrapper() = 0;
        
        
        
       		 /*!
			\brief verify is this type is an AddressWrapper
			\return true if it is a BooleanWrapper, false else;
		*/
        	virtual bool isBooleanWrapper() = 0;
        
        /*!
			\brief verify is this type is an Array
			\return true if it is an Array, false else;
		*/
        virtual bool isArray() = 0;
        
        /*!
			\brief Prepare JNI call, before calling the native Function, if this type is encontered
		*/
        virtual void prepareCall(ofstream& f,string& varName) =0;
        
        
        
        /*!
			\brief create the parameter name for the native function call
			\return the parameter name for native call
		*/
        virtual string getJNIParameterName(string& varName) =0;
        
        /*!
			\brief create JNI instruction to get return value from Native function call, and convert the result to Java
			\return the javaType
		*/
        virtual void getReturnValue(ofstream& f) =0;
        
        string getJavaType();
        string getJNIType();
        string getVMSignature();
        
      protected:
      	string _javaType; /*!< corresponding java type*/
      	string _jniType; /*!< corresponding JNI type*/
    	string _VMSignature; /*!< Signature for the Java Virtual Machine*/
      	
    };
}

#endif

