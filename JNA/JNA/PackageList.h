/** @file
 *
 * Header for the PackageList class
 */

#ifndef __JAVA_PACKAGELIST_H
#define __JAVA_PACKAGELIST_H

#include <string>
#include <vector>
#include "Utils/Displayable.h"

namespace nsJNA
{
    class Type;

    /** Manage a list of package to import */
    class PackageList: public nsUtils::Displayable
    {
      public:
        PackageList();
        virtual ~PackageList();

        /** Add a type.
         *
         * If this type is already present, it will be skipped.
         */
        void addType(const Type* type, bool includeVariant = false);
        /** Manually add an import line */
        void addImport(const std::string& import);

        void addSupportClass(void);

        /** Return the list of packages to import */
        const std::vector<std::string>& getList(void) const;

        /** Build the import string to put in a Java file */
        std::string getImportString(void) const;

      protected:
        std::vector<std::string> mPackageList;

        void display(std::ostream& stream) const;
    };
}

#endif

