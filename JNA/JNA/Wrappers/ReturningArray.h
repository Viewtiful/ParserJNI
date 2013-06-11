/** @file
 *
 * Header for the ReturningArray class
 */

#ifndef __JAVA_WRAPPERS_RETURNINGARRAY_H
#define __JAVA_WRAPPERS_RETURNINGARRAY_H

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
         * When two functions like this are found:
         * - ktb_xxx() returning a void*
         * - ktb_xxx_size() returning a size_t
         *
         * a wrapper will be created that return a byte array.
         */
        class ReturningArray: public Wrapper
        {
            typedef Wrapper super;

          public:
            virtual ~ReturningArray();

            static bool handle(const nsC::Function::vector& functions,
                               std::vector<bool>& functionsDone,
                               nsJNA::Module& javaModule,
                               const nsJNA::TypesDictionnary&
                                   dictionnary);

            std::string getWrapperCode(void) const;

          protected:
            ReturningArray(const nsC::Function& returningArray,
                           nsJNA::Module& javaModule,
                           const nsJNA::TypesDictionnary& dictionnary);
        };
    }
}

#endif
