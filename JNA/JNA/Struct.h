/** @file
 *
 * Header for the Struct class
 */

#ifndef __JAVA_STRUCT_H
#define __JAVA_STRUCT_H

#include <string>
#include "Modules/Module.h"
#include "JNA/TypesDictionnary.h"
#include "JNA/PackageList.h"
#include "JNA/Type.h"

namespace nsJNA
{
    class Struct: public Type
    {
      typedef Type super;

      public:
        virtual ~Struct();

        /** Add to @a javaTypes all struct found in @a module (both typedef
         * and complete structure) */
        static bool create(const nsModules::Module& module,
                           const nsJNA::TypesDictionnary& dictionnary,
                           Type::map& javaTypes);

        bool convertToJava(void);
        bool needWriting(void) const;
        bool writeJava(std::ostream& file) const;

      protected:
        typedef enum {
            stStructure,
            stTypedefPtr,
            stTypedefPtrByRef
        } StructType;

        StructType mStructType;
        /** Used for stTypedefPtrByRef */
        std::string mTypedefPtrName;
        std::string mStructFields;
        const nsJNA::TypesDictionnary& mDictionnary;
        const nsC::Struct* mStruct;

        Struct(const nsModules::Module& module,
               const nsC::Struct& CStruct,
               StructType type,
               const nsJNA::TypesDictionnary& dictionnary,
               Type::map& javaTypes);

        bool convertStruct(void);

        void writeStruct(std::ostream& file) const;
        void writeTypedefPtr(std::ostream& file) const;
        void writeTypedefPtrByRef(std::ostream& file) const;

        /** Create a "typedef" using a NativeMapped object.
         *
         * This will simply create a NativeMapped object with the name of
         * the struct that will behave like a pointer.
         */
        static bool createTypedef(const nsModules::Module& module,
                                  const nsC::Struct& CStruct,
                                  const nsJNA::TypesDictionnary&
                                    dictionnary,
                                  map& javaTypes);

        /** Create a full Structure class.
         *
         * This will use the typedef if available; otherwise it will use the
         * base name from "struct basename".
         */
        static bool createStruct(const nsModules::Module& module,
                                 const nsC::Struct& CStruct,
                                 const nsJNA::TypesDictionnary& 
                                    dictionnary,
                                 Type::map& javaTypes);
    };
}

#endif

