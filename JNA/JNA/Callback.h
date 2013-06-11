/** @file
 *
 * Header for the Callback class
 */

#ifndef __JAVA_CALLBACK_H
#define __JAVA_CALLBACK_H

#include <string>
#include <vector>
#include "C/Callback.h"
#include "JNA/TypesDictionnary.h"
#include "JNA/PackageList.h"
#include "JNA/Type.h"

namespace nsJNA
{
    class Callback: public Type
    {
      typedef Type super;

      public:
        virtual ~Callback();

        static bool create(const nsModules::Module& module,
                           const nsJNA::TypesDictionnary& dictionnary,
                           Type::map& javaTypes);

        bool convertToJava(void);
        bool needWriting(void) const;
        bool writeJava(std::ostream& file) const;

      protected:
        const nsC::Callback& mCallback;
        const nsJNA::TypesDictionnary& mDictionnary;
        std::string mReturnJavaType;
        std::string mParamString;

        Callback(const nsModules::Module& module,
                 const nsC::Callback& callback,
                 const nsJNA::TypesDictionnary& dictionnary,
                 Type::map& javaTypes);
    };
}

#endif

