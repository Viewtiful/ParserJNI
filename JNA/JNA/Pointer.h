/** @file
 *
 * Header for the Pointer class
 */

#ifndef __JAVA_POINTER_H
#define __JAVA_POINTER_H

#include "JNA/NativeType.h"

namespace nsJNA
{
    class Pointer: public NativeType
    {
        typedef NativeType super;

      public:
        virtual ~Pointer();

        bool isSpecial(void) const;
        size_t getVariantCount(void) const;
        std::string getVariantName(size_t id) const;
        std::string getVariantPackage(size_t id) const;

      protected:
        Pointer(const std::string& nativeName, Type::map& javaTypes);

        friend class NativeType;
    };
}

#endif

