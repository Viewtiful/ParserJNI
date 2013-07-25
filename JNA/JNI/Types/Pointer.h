/** @file
 *
 * Header for Types
 * \brief Handle pointer for the JNI code.
 */

/*!
  \file Pointer.h
  \author Baptiste HAUDEGAND & Antoine MOISE
  \version 1.0
  !*/
#ifndef __JNI_POINTER_H
#define __JNI_POINTER_H
#include <string>
#include "JNI/Types/Type.h"
#include "JNI/TypesDictionnary.h"

/** @addtogroup Types
 * @{ */

/*!
  \namespace nsJNI 
  JNI parser namespace
  !*/
namespace nsJNI {

	class TypesDictionnary;
	/*!
	  \class Pointer
	  \brief represents a Pointer
	  */
	class Pointer : public Type 
	{
		public:
			/*!
			  \brief destructor
			  */
			virtual ~Pointer();
			/*!
			  \brief constructor with three parameters
			  Create, and initialize a Pointer with the following arguments
			  \param vmSignature : signature for the java Virtual Machine
			  \param CBaseType : pointer's type
			  \param dictionnary : dictionnary of all type
			  */
			Pointer(const string& vmSignature, const string& CBaseType, TypesDictionnary *dictionnary, bool isNativeType);
			std::string outputJava();
			std::string outputJNI();
			bool isNativeType();
			bool isAddressWrapper();
			bool isBooleanWrapper();
			bool isArray();
			void prepareCall(ofstream& f, const string& varName);
			string getJNIParameterName(const string& varName);
			void getReturnValue(ofstream& f);
			string getVMSignature();
		protected:
			std::string _CBaseType; /*!< The pointer's C Type*/
			TypesDictionnary* _dictionnary/*!< Dictionnary of types*/;
			bool _isNativeType; /*!< is a NativeType?*/
	};
}

#endif

