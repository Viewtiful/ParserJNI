/** @file
 *
 * Header for BoolWrapper.
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
	  \brief Handle bool* type.
	  */
	class BoolWrapper : public Type
	{
		public:
			virtual ~BoolWrapper();

			/*!
			  \brief Constructor with two parameters
			  create, and initialize a BoolWrapper with the following arguments
			  \param realCType : The Data's CType which is converted to BoolWrapper.
			  \param VMSIgnature : Signature for the Java Virtual Machine.
			  */		
			BoolWrapper(string realCType, string VMSignature);

			std::string outputJava();
			std::string outputJNI();
			bool isNativeType();
			bool isAddressWrapper();
			bool isBooleanWrapper();
			bool isArray();
			void prepareCall(ofstream& f, const string& varName);
			string getJNIParameterName(const string& varName);
			void getReturnValue(ofstream& f);

		protected:
			string _realCType; /*!< C Type of the element*/
			string _varName; /*!< Name of the boolean*/
	};
}

#endif

