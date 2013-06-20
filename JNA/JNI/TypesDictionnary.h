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
#include "JNI/Types/Pointer.h"
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
		void convertJava(Module::vector modules);
		void convertJNI(Module::vector modules);
		
		string convertJava(string Ctype);
		string convertJNI(string Ctype);
		string convertVM(string Ctype);
		int nbIndirections(string CType);
		void addTypedefs(nsC::Typedef::vector typedefs);
		void addStruct(nsC::Struct::vector structs);


      protected:

        /** Add base types (int, size_t, char, those stuff) */
        std::map<std::string, Type*> _conversionMap;
		
    };
}

#endif

