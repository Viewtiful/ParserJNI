/** @file
 *
 * Header for the Default class
 */

#ifndef __JAVA_WRAPPERS_DEFAULT_H
#define __JAVA_WRAPPERS_DEFAULT_H

#include <vector>
#include "C/Function.h"
#include "JNA/Module.h"
#include "JNA/Wrappers/ReturnWrapper.h"
#include "JNA/Wrappers/Wrapper.h"

namespace nsJNA
{
    namespace nsWrappers
    {
        /** Last wrapper. Will handle functions not handled by another
         * wrapper. */
        class Default: public Wrapper
        {
            typedef Wrapper super;

          public:
            virtual ~Default();

            static bool handle(const nsC::Function::vector& functions,
                               std::vector<bool>& functionsDone,
                               nsJNA::Module& javaModule,
                               const nsJNA::TypesDictionnary&
                                   dictionnary);

            std::string getWrapperCode(void) const;

          protected:

            std::string mNativeJavaType;
            ReturnWrapper mReturnWrapper;

            Default(const nsC::Function& returningArray,
                    nsJNA::Module& javaModule,
                    const nsJNA::TypesDictionnary& dictionnary,
                    int iteration = 0);
        };
    }
}

#endif
