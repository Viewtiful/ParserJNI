/** @file
 *
 * Header for the TypesDictionnary class
 */

#ifndef __JNI_TYPESDICTIONNARY_H
#define __JNI_TYPESDICTIONNARY_H

#include <string>
#include <iostream>
#include <map>
#include "JNI/Types/Type.h"
#include "JNI/Types/NativeType.h"
#include "JNI/Types/Typedef.h"
#include "JNI/Types/Struct.h"
#include "JNI/Types/Enum.h"
#include "JNI/Types/Pointer.h"
#include "JNI/Types/Array.h"
#include <cassert>
#include "Modules/Module.h"
using namespace nsModules;
namespace nsJNI
{
    /** A dictionnary of all available types, and their converted names.
     *
     * This class hold a list of all available types (standard and user
     * defined).
     *
     * The good way to use it:
     * - create and populate it with a call to addModules()
     * - call convertToJava() to allow every type to check if they can be
     *   converted to Java
     * - call outputJava() to write out the resulting Java classes
     */
    class TypesDictionnary
    {
      public:
        TypesDictionnary();
        virtual ~TypesDictionnary();
        void addBaseType();
		void convertJava(const Module::vector& modules);
		void convertJNI(const Module::vector& modules);
		void addToMap(const string& cType, Type *type);
		int countAt(const string& Ctype);

		string convertJava(const string& Ctype);
		string convertJNI(const string& Ctype);
		string convertVM(const string& Ctype);
		string getRealType(const string& CType);
		int nbIndirections(const string& CType);
		void addTypedefs(const nsC::Typedef::vector& typedefs);
		void addStruct(const nsC::Struct::vector& structs);
	   	void addEnums(ofstream &f, const nsC::Enum::vector& enums);
		bool isNativeType(const string &type);

      protected:

        /** Add base types (int, size_t, char, those stuff) */
        std::map<std::string, Type*> _conversionMap;
		
    };
}

#endif

