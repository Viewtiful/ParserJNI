/** @file
 *
 * Header for the TypesDictionnary class
 */

#ifndef __JNI_TYPESDICTIONNARY_H
#define __JNI_TYPESDICTIONNARY_H

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "JNI/Types/Type.h"
#include "JNI/Types/NativeType.h"
#include "JNI/Types/Typedef.h"
#include "JNI/Types/Struct.h"
#include "JNI/Types/Enum.h"
#include "JNI/Types/Pointer.h"
#include "JNI/Types/Array.h"
#include "JNI/Types/Function.h"
#include "JNI/Types/BoolWrapper.h"
#include <cassert>
#include "Modules/Module.h"
using namespace nsModules;
namespace nsJNI
{
    
   class Array;
   class Function;
	/*!
		\class TypesDictionnary
		\brief contains All Type, and all we need to convert  
	*/
    class TypesDictionnary
    {
      public:
	/*!
		\brief constructor with one parameter
		Create, and initialize a TypeDictionnary with the following argument
		\param filename : The Output filename (Java and JNI output files have the same name)
	*/
        TypesDictionnary(string filename);
        virtual ~TypesDictionnary();

		/*!
			\brief add all Base Type conversion such as int and some specific conversion which not involved complex type
			\param filename: The Output filename (Java and JNI output files have the same name) : useful for struct's VMSignature
		*/

        void addBaseType(string filename);

		/*!
			\brief Convert module to Java
			\param modules: All header file representing by Module
		*/
		void convertJava(const Module::vector& modules);

		/*!
			\brief Convert module to JNI
			\param modules: All header file representing by Module
		*/
		void convertJNI(const Module::vector& modules);

		/*!
			\brief Add a new Type, to a specific place in the conversion Map
			\param cType : The CType which is handled by the new Type
			\param type : The new Type
		*/
		void addToMap(const string& cType, Type *type);

		/*!
			\brief Give the number of element in a specific place in the conversionMap 
			\param Ctype :  
		*/

		int countAt(const string& Ctype);

		/*!
			\brief give the Java translation from a CType
			\param CType: Type that we want to Translate
			\return : the translated Java Type
		*/

		string convertJava(const string& Ctype);

		/*!
			\brief give the JNI translation from a CType
			\param CType: Type that we want to Translate
			\return : the translated JNI Type
		*/

		string convertJNI(const string& Ctype);

		/*!
			\brief give the VM Signature from a CType
			\param CType: Type that we want to Translate
			\return : the VM signature
		*/

		string convertVM(const string& Ctype);
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/

		string getRealType(const string& CType);
		
		string getFilename();

		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/
		int nbIndirections(const string& CType);

		/*!
			\brief Add Typedefs to Dictionnary
			\param typedefs: all typedefs included in C Files
		*/

		void addTypedefs(const nsC::Typedef::vector typedefs);

		/*!
			\brief Add Structs to Dictionnary
			\param fJava : Output file Java
			\param fJNI : Ouput file JNI
			\param structs: all structs included in C Files
		*/
		void addStruct(ofstream &fJava, ofstream &fJNI, const nsC::Struct::vector& structs);

		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/

	   	void addEnums(ofstream &f, const nsC::Enum::vector& enums);

		/*!
			\brief inform that this type is a NativeType or not 
			\param type: C Type
			\param true if it is a NativeType, false else
		*/

		bool isNativeType(const string &type);

		/*!
			\brief return the Object Type which handle this C Type
			\param f: the C Type
			\return the Object type
		*/
		Type* getType(const string & Ctype);

		vector<Function*> getFcts();
      protected:

        /** Add base types (int, size_t, char, those stuff) */
        std::map<std::string, Type*> _conversionMap; /*!<Map which associate an type to a class (int -> NativeType)*/
		string _filename; /*!< filename*/
		std::vector<Function*> _fcts; /*!< All fonctions */
    };
}


#endif

