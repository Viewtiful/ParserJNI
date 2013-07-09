/** @file
 *
 * Header for Types
 */

/*!
	\file Array.h
	\author Baptiste HAUDEGAND & Antoine MOISE
	\version 1.0
!*/
#ifndef __JNI_ARRAY_H
#define __JNI_ARRAY_H
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
		\class Array
		\brief represents a Array
	*/
    class Array : public Type 
    {
      public:
      /*!
      	\brief destructor
      */
        virtual ~Array();
	/*!
        	\brief constructor with three parameters
        	Create, and initialize an Array with the following arguments
        	\param CBaseType : Base C array type such as int for int[]
        	\param VMSIgnature : signature for the java Virtual Machine
		\param dictionnary : dictionnary of all type
        */
	Array(const string& CBaseType, const string& vmSignature, TypesDictionnary *dictionnary) ;
	std::string outputJava();
        std::string outputJNI() ;
        bool isNativeType();
	bool isAddressWrapper();
        bool isBooleanWrapper();
        bool isArray();
        void prepareCall(ofstream& f,std::string& varName);
        std::string getJNIParameterName(std::string& varName);
        void getReturnValue(ofstream& f);
        void getReturnValueAndFree(ofstream& f);
        
      protected:
        TypesDictionnary* _dictionnary; /*!< dictionnary of all type*/
        std::string _CBaseType; /*!< C Base Type*/
        string _varName; /*!< Variable name*/
    };
}

#endif

