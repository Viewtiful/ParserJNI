/** @file
 *
 * Header for the ReturnWrapper class
 */

#ifndef __JAVA_WRAPPER_RETURNWRAPPER_H
#define __JAVA_WRAPPER_RETURNWRAPPER_H

#include "JNA/PackageList.h"
#include "JNA/TypesDictionnary.h"

namespace nsJNA
{
    namespace nsWrappers
    {
        /** Wrappers for the return value of functions */
        class ReturnWrapper
        {
          public:
            ReturnWrapper(const std::string& CType,
                          nsJNA::PackageList& packageList,
                          const nsJNA::TypesDictionnary& dictionnary);
            virtual ~ReturnWrapper();

            /** Will return the return block using the given functionCall.
             */
            std::string getReturnBlock(const std::string& functionCall) const;

            std::string getReturnType(void) const;

          protected:
            std::string mReturnType;
            std::string mReturnBlock;
        };
    }
}

#endif

