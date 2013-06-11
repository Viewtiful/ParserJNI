/** @file
 *
 * Header for the TypesDictionnary class
 */

#ifndef __JNA_TYPESDICTIONNARY_H
#define __JNA_TYPESDICTIONNARY_H

#include <string>
#include "C/Param.h"
#include "Modules/Module.h"
#include "JNA/Type.h"

namespace nsJNA
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

        /** Add all types from modules to the dictionnary
         */
        bool addModules(nsModules::Module::vector& modules);

        bool convertToJava(void);
        bool outputJava(void);

        /** Return the JavaType associated with a given CType. 
         *
         * This function will strip the "const " if present.
         */
        nsJNA::Type* getType(const std::string& CType, 
                              bool returnValue = false) const;
        nsJNA::Type* getType(const nsC::Param& param,
                              bool returnValue = false) const;

      protected:
        nsJNA::Type::map mTypes;

        /** Add base types (int, size_t, char, those stuff) */
        void addBaseTypes();
        bool addModule(const nsModules::Module& module);
    };
}

#endif

