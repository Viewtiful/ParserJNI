/** @file
 *
 * Header for Types
 */

/*!
  \file Struct.h
  \author Baptiste HAUDEGAND & Antoine MOISE
  \version 1.0
  !*/
#ifndef __JNI_STRUCT_H
#define __JNI_STRUCT_H
#include <string>
#include "C/Struct.h"
#include "JNI/Types/Type.h"
#include "JNI/TypesDictionnary.h"
#include "JNI/Types/Function.h"
#include <vector>

/** @addtogroup Types
 * @{ */

/*!
  \namespace nsJNI 
  JNI parser namespace
  !*/
namespace nsJNI {

	class TypesDictionnary;
	class Getter;
	class Setter;
	class Create;
	class Free;
	class Function;
	/*!
	  \class Struct
	  \brief represents a Struct
	  */
	class Struct : public Type 
	{
		public:
			/*!
			  \brief destructor
			  */
			virtual ~Struct();
			Struct(ofstream &f, ofstream& f2, const string& vmSignature,const nsC::Struct& cStruct,TypesDictionnary *dictionnary);
			std::string outputJava();
			/*!
			  \brief Write the structure to a Java file.
			  */
			void addStructToJava(ofstream &f);
			/*!
			  \brief Write the structure to the JNI file.
			  */
			void addStructFunctionToJNI(ofstream &f);
			std::string outputJNI();
			bool isNativeType();
			bool isAddressWrapper();
			bool isBooleanWrapper();
			bool isArray();
			void prepareCall(ofstream& f,string& varName);
			string getJNIParameterName(string& varName);
			/*!
			  \brief Generate constructor of the structure
			  \return the constructor function to write
			  */
			string generateConstructor();
			/*!
			  \brief Generate finalize function of the structure to free it.
			  \return the finalize function to write
			  */
			string generateFinalize();
			/*!
			  \brief Generate write function of the structure.
			  Write all params from Java to the C structure.
			  \return the write function to write
			  */
			string generateWrite();
			/*!
			  \brief Generate read function of the structure.
			  Read all params from the C structure to Java.
			  \return the read function to write
			  */
			string generateRead();
			void getReturnValue(ofstream& f);
			/*!
			  \brief Get all the functions used by the structure.
			  All the functions means, create/free/getters/setters.
			  \return all the functions used by the structure.
			  */
			vector<Function*> getGetterSetters();
		protected:
			nsC::Struct _cStruct;
			TypesDictionnary* _dictionnary; /*!< dictionnary of all type*/
			vector<Getter*> _getters; /*!< all the getter functions*/
			vector<Setter*> _setters; /*!< all the setter functions*/
			vector<Function*> _getterSetters; /*!< all functions used in the structure*/
			Create *_createFunction; /*!< create function of the structure*/
			Getter *_structSize; /*!< getter function of the structure size*/
			Free *_freeFunction; /*!< free function of the structure*/
	};
}
#endif
