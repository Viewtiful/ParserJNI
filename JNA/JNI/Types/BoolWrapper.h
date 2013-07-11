/** @file
 *
 * Header for Types
 */

/*!
	\file BoolWrapper.h
	\author Baptiste HAUDEGAND & Antoine MOISE
	\version 1.0
!*/
#ifndef __JNI_BOOLWRAPPER_H
#define __JNI_BOOLWRAPPER_H
#include "JNI/Types/Type.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

/** @addtogroup Types
 * @{ */

/*!
	\namespace nsJNI 
	JNI parser namespace
!*/
namespace nsJNI {

	/*!
		\class BoolWrapper
		\brief handle bool* type
	*/
    class BoolWrapper : public Type
    {
      public:
      /*!
      	\brief destructor
      */
        virtual ~BoolWrapper();

	/*!
        	\brief constructor with two parameters
        	Create, and initialize an BoolWrapper with the following arguments
        	\param realCType : The Data's CType which is converted to AddressWrapper
        	\param VMSIgnature : signature for the java Virtual Machine
        */		
	BoolWrapper(string realCType, string VMSignature);
	/*!
        	\brief constructor with one parameters
        	Create, and initialize an AddressWrapper with the following arguments
        	\param VMSIgnature : signature for the java Virtual Machine
        */
	BoolWrapper(string VMSignature);
	std::string outputJava();
        std::string outputJNI();
        bool isNativeType();
        bool isAddressWrapper();
        bool isBooleanWrapper();
        bool isArray();
        void prepareCall(ofstream& f,string& varName);
        string getJNIParameterName(string& varName);
        void getReturnValue(ofstream& f);
        
      	protected:
      	string _realCType; /*!< C Type of the data's*/
         string _varName; /*!< Variable name*/
    };
}

#endif

