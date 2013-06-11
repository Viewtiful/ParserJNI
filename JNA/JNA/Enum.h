/** @file
 *
 * Header for the Enum class
 */

#ifndef __JAVA_ENUM_H
#define __JAVA_ENUM_H

#include "JNA/Type.h"

namespace nsJNA
{
    class Enum: public Type
    {
        typedef Type super;

      public:
        virtual ~Enum();

        static bool create(const nsModules::Module& module,
                           Type::map& javaTypes);

        bool convertToJava(void);
        bool needWriting(void) const;
        bool writeJava(std::ostream& file) const;

      protected:
        const nsC::Enum& mEnum;
        
        Enum(const nsModules::Module& module,
             const nsC::Enum& Enum,
             Type::map& javaTypes);
    };
}

#endif

