/** @file
 *
 * \brief Handle an array for the JNI code.
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

/** @addtogroup Types
 * @{ */

/*!
  \namespace nsJNI 
  JNI parser namespace
  !*/


namespace nsJNI {

	class TypesDictionnary;
	/*!
	  \class Array
	  \brief Represents an array in Java and JNI.
	  */
	class Array : public Type 
	{
		public:
			virtual ~Array();
			/*!
			  \brief Constructor with three parameters
			  create, and initialize an Array with the following arguments,
			  \param CBaseType : Base C array type such as int for int[].
			  \param VMSIgnature : Signature for the Java Virtual Machine.
			  \param dictionnary : Dictionnary of all types.
			  */
			Array(const string& CBaseType, const string& vmSignature, TypesDictionnary *dictionnary) ;
			std::string outputJava();
			std::string outputJNI() ;
			bool isNativeType();
			bool isAddressWrapper();
			bool isBooleanWrapper();
			bool isArray();
         /*!
            \brief prepare the call of the native function by converting Java type to native type.
            \param f : The target file where is written the preparation of an array type.
            \param varName : Name of the array.
         */
			void prepareCall(ofstream& f, const string& varName);
			std::string getJNIParameterName(const string& varName);
			void getReturnValue(ofstream& f);
         /*!
            \brief Convert and return the native array to Java and free the native array.
            \param f : The target file where is written the code in order to return the array.
            \param varName : Name of the array.
         */
			void getReturnValueAndFree(ofstream& f, const string& varName, bool way);

		protected:
			/** Dictionnary of all types*/
			TypesDictionnary* _dictionnary; 
			/** C Base type*/
			std::string _CBaseType;
			/** Name of the array*/
			string _varName; 
	};
}

#endif

