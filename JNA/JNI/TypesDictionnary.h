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
		void convertCpp(Module::vector modules);
		
		string convertJava(string Ctype);
		string convertCpp(string Ctype);
		string convertVM(string Ctype);
		
		string getJavaType(string Ctype);
		string getCppType(string Ctype);
		string getVMType(string Ctype);
		
		void addTypedef(Typedef t);
		int nbIndirections(string CType);
		void addTypedefs(nsC::Typedef::vector typedefs);
		void addStruct(nsC::Struct::vector structs);


      protected:

        /** Add base types (int, size_t, char, those stuff) */
        std::map<std::string, Type*> _conversionMap;
		
    };
}

#endif

