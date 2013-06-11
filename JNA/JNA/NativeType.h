/** @file
 *
 * Header for the NativeType class
 */

#ifndef __JAVA_NATIVETYPE_H
#define __JAVA_NATIVETYPE_H

#include "C/Typedef.h"
#include "JNA/Type.h"

namespace nsJNA
{
    /** Mapping for C native types already present in JNA */
    class NativeType: public Type
    {
      typedef Type super;

      public:
        virtual ~NativeType();

        static void createNativeTypes(Type::map& javaTypes);
        static bool createTypedef(const nsC::Typedef::vector& typedefs,
                                  Type::map& javaTypes);

        bool convertToJava(void);
        bool needWriting(void) const;
        bool writeJava(std::ostream& file) const;

        std::string getFullPackageName(void) const;

      protected:
        NativeType(const std::string& baseCName,
                   const std::string& baseJavaName,
                   const std::string& fullPackage,
                   Type::map& javaTypes);
    };
}

#endif

