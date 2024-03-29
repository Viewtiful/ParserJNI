/** @file
 * Header for AddressWrapper
 * \brief Handle pointer for the JNI code.
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
	  \brief Handle every address of enums and structures in the Java side.
	  */
	class AddressWrapper : public Type
	{
		public:
			virtual ~AddressWrapper();

			/*!
			  \brief Constructor with two parameters.
			  create, and initialize an AddressWrapper with the following arguments
			  \param realCType : The Data's CType which is converted to AddressWrapper.
			  \param filename : filename.
			  */
			AddressWrapper(const string& realCType, const string& VMSignature);

			std::string outputJava();
			std::string outputJNI();
			bool isNativeType();
			bool isAddressWrapper();
			bool isBooleanWrapper();
			bool isArray();
			void prepareCall(ofstream& f,const string& varName);
			string getJNIParameterName(const string& varName);
			void getReturnValue(ofstream& f);

		protected:
			string _realCType; /*!< C Type of the data element*/
			string _varName; /*!< Name of the element*/
	};
}

#endif

