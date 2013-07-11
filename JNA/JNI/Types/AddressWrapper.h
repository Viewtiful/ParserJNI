/** @file
 *
 * Header for Types
 */
/*!
	\file AddressWrapper.h
	\author Baptiste HAUDEGAND & Antoine MOISE
	\version 1.0
!*/
#ifndef __JNI_ADDRESSWRAPPER_H
#define __JNI_ADDRESSWRAPPER_H
#include "JNI/Types/Type.h"
#include "Utils/Utils.h"
#include <string>
#include <iostream>
#include <fstream>

/** @addtogroup Types
 * @{ */

using namespace std;
/*!
	\namespace nsJNI 
	JNI parser namespace
!*/
namespace nsJNI {
	/*!
		\class AddressWrapper
		\brief handle all struct
	*/
    class AddressWrapper : public Type
    {
      public:
      /*!
      	\brief destructor
      */
        virtual ~AddressWrapper();

	/*!
        	\brief constructor with two parameters
        	Create, and initialize an AddressWrapper with the following arguments
        	\param realCType : The Data's CType which is converted to AddressWrapper
        	\param VMSIgnature : signature for the java Virtual Machine
        */
	AddressWrapper(string realCType, string VMSignature);
	
	/*!
        	\brief constructor with one parameters
        	Create, and initialize an AddressWrapper with the following arguments
        	\param VMSIgnature : signature for the java Virtual Machine
        */
	AddressWrapper(string VMSignature);
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

