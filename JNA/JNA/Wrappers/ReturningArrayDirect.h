/** @file
 *
 * Header for the ReturningArrayDirect class
 */

#ifndef __JAVA_WRAPPERS_RETURNINGARRAYDIRECT_H
#define __JAVA_WRAPPERS_RETURNINGARRAYDIRECT_H

#include <vector>
#include "C/Function.h"
#include "JNA/Module.h"
#include "JNA/Wrappers/Wrapper.h"

namespace nsJNA
{
    namespace nsWrappers
    {
        /** Handle pair of functions returning an array and it's size.
         *
         * When a functions like this is found:
         * - (const void*)(*)(...,size_t *size)
         *
         * a wrapper will be created that return a byte array.
         */
        class ReturningArrayDirect: public Wrapper
        {
            typedef Wrapper super;

          public:
            virtual ~ReturningArrayDirect();

            static bool handle(const nsC::Function::vector& functions,
                               std::vector<bool>& functionsDone,
                               nsJNA::Module& javaModule,
                               const nsJNA::TypesDictionnary&
                                   dictionnary);

            std::string getWrapperCode(void) const;

          protected:
            ReturningArrayDirect(const nsC::Function& returningArray,
                           nsJNA::Module& javaModule,
                           const nsJNA::TypesDictionnary& dictionnary);
        };
    }
}

#endif
