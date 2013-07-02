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
#include <string>
#include <iostream>
#include <fstream>
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
		AddressWrapper(string realCType, string VMSignature);
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
      	string _realCType;
         string _varName;
    };
}

#endif

