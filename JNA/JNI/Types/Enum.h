/*!
  \file Enum.h
  \brief Handle an enum for the JNI/Java code.
  \author Baptiste HAUDEGAND & Antoine MOISE
  \version 1.0
  !*/

#ifndef __JNI_ENUM_H
#define __JNI_ENUM_H
#include "JNI/Types/Type.h"
#include "C/Enum.h"
#include "JNI/TypesDictionnary.h"
#include "Modules/Module.h"

/** @addtogroup Types
 * @{ */

/*!
  \namespace nsJNI 
  JNI parser namespace
  !*/
namespace nsJNI{

	class TypesDictionnary;
	/*!
	  \class Enum
	  \brief Represents an Enum
	  */
	class Enum : public Type
	{
		public : 
			virtual ~Enum();

			/*!
			  \brief create an enum for the JNI parser.
			  create, and add to the dictionnary an Enum with the following arguments :
			  \param f : The file where the enum will be written.
			  \param en : Contains all enums from the C header (module), we are running through.
			  \param dictionnary : Dictionnary which contains all types.
			  */
			static bool create(ofstream &f, const nsC::Enum::vector& en, TypesDictionnary *dictionnary);
			std::string outputJava();
			std::string outputJNI();
			/*!
			  \brief Write the enum to the Java file 
			  \param f : The file where the enum will be written.
			  */
			void addEnumToJava(ofstream &f);
			bool isNativeType();
			bool isAddressWrapper();
			bool isBooleanWrapper();
			bool isArray();
			void prepareCall(ofstream& f, const string& varName);
			string getJNIParameterName(const string& varName);
			void getReturnValue(ofstream& f);

		protected : 
			nsC::Enum _cEnum; /*!< Object which represents the C enum.*/
			string _filename; /*!< Filename where the enum is written.*/
			string _enumName; /*!< Name of the current enum*/

			Enum(ofstream &f, const string& javaType,const string& jniType,const string& vmSignature,const nsC::Enum& cEnum, string filename);
	};
}
#endif
