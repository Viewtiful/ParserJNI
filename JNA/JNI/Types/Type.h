/** @file
 * @defgroup Types All the types used by the JNIParser
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
			virtual ~Type();
			/*!
			  \brief Constructor with three parameters.
			  create, and initialize a type with the following arguments
			  \param javaType : The corresponding Java type.
			  \param jniType : The corresponding JNI type.
			  \param VMSIgnature : The corresponding signature for the Java VM.
			  */
			Type(string javaType, string jniType, string VMSignature);

			/*!
			  \brief constructor with one parameter.
			  create, and initialize a type with the following argument : 
			  \param VMSIgnature : The corresponding signature for the Java VM.
			  */
			Type(string VMSignature);

			/*!
			  \brief Convert a C type to a Java type.
			  \return The corresponding Java type.
			  */
			virtual std::string outputJava() = 0;

			/*!
			  \brief Convert a type to JNI type.
			  \return The corresponding JNI type.
			  */
			virtual std::string outputJNI() = 0;

			/*!
			  \brief Verify is this type is derived from a native type such as 'int, float ...'
			  \return True if it's a NativeType, false otherwise;
			  */
			virtual bool isNativeType() = 0;


			/*!
			  \brief Verify is this type is an AddressWrapper.
			  \return True if it's an AddressWrapper, false otherwise;
			  */
			virtual bool isAddressWrapper() = 0;

			/*!
			  \brief Verify is this type is a BoolWrapper.
			  \return True if it's a BoolWrapper, false otherwise;
			  */
			virtual bool isBooleanWrapper() = 0;

			/*!
			  \brief Verify is this type is an Array
			  \return True if it's an Array, false otherwise;
			  */
			virtual bool isArray() = 0;

			/*!
			  \brief Prepare JNI call with variables initialization before calling the native function.
			  */
			virtual void prepareCall(ofstream& f,const string& varName) =0;

			/*!
			  \brief create the parameter name for the native function call.
			  \return the parameter name for native call.
			  */
			virtual string getJNIParameterName(const string& varName) =0;

			/*!
			  \brief create JNI instructions to return the value from the native function call to Java.
			  \params f : The target file where the JNI instructions are written.
			  */
			virtual void getReturnValue(ofstream& f) =0;

			string getJavaType();
			string getJNIType();
			string getVMSignature();

		protected:
			/** Corresponding java type.*/
			string _javaType; 
			/** Corresponding JNI type.*/
			string _jniType; 
			/** Corresponding signature for the Java Virtual Machine.*/
			string _VMSignature;

	};
}

#endif

