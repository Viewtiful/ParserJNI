/** @file
 *
 * Header for the Type class
 */

#ifndef __JAVA_TYPE_H
#define __JAVA_TYPE_H

#include <string>
#include <vector>
#include <map>
#include "JNA/PackageList.h"
#include "Modules/Module.h"
#include "Utils/Displayable.h"

namespace nsJNA
{
    /** Base class for conversion into JavaType */
    class Type: public nsUtils::Displayable
    {
      public:
        typedef std::vector<Type> vector;
        /** A map to find a JavaType from a CType.
         * The CType must contain the * if it is an indirection. 
         */
        typedef std::map<std::string, Type*> map;

        virtual ~Type();

        /** Convert the CType to Java equivalent.
         *
         * This function should prepare everything needed to latter output
         * the Java code.
         *
         * @retval true The conversion was successful
         * @retval false The conversion failed. For example, a structure
         * lacking one of it's field type in the dictionnary...
         */
        virtual bool convertToJava(void) =0;
        /** Determine if a type need to be written in a Java file. */
        virtual bool needWriting(void) const =0;
        /** Write the Java source code in @a file.
         *
         * @retval true Everything's ok
         * @retval false An error occured while writing
         *
         * @note
         * This function should not fail because the type is somewhat
         * invalid; that's what convertToJava() is here for.
         */
        virtual bool writeJava(std::ostream& file) const =0;

        virtual const std::string& getModule(void) const;
        virtual const std::string& getBaseCName(void) const;
        virtual const std::string& getBaseJavaName(void) const;
        virtual std::string getFullPackageName(void) const;

        /** Return the import string to use with "import".
         *
         * If the type isn't in a package, the returned string is empty.
         */
        std::string getImport(void) const;
        std::string getImport(size_t id) const;

        /** Determine if a given type is special.
         *
         * Special types should return "legit" information in other
         * functions, and are handled by hand where it's needed.
         *
         * Main place : multiple version of the same function for pointers.
         */
        virtual bool isSpecial(void) const;
        virtual size_t getVariantCount(void) const;
        virtual std::string getVariantName(size_t id) const;
        virtual std::string getVariantPackage(size_t id) const;

        bool isStructPtr(void) const;

      protected:
        /** Module */
        std::string mModule;
        /** Base C type name */
        std::string mBaseCName;
        /** Java unqualified class name */
        std::string mBaseJavaName;
        /** Is a struct pointer? */
        bool mStructPtr;
        /** Java subpackage (relative from application-wide package) */
        std::string mBasePackage;
        PackageList mPackageList;

        Type(const std::string& moduleName);
        Type(const nsModules::Module& module);

        void display(std::ostream& stream) const;
        void addToMap(map& javaTypes);

        /** Will prepare a string for writting.
         *
         * This function will do the following:
         * - add a "package" line if needed
         * - add imports from mPackageList
         * - add the suppresswarning line at the beginning of @a buffer
         * - replace all occurence of %FULLPACKAGE%
         * - replace all occurence of %IMPORTS%
         * - replace all occurence of %BASEJAVANAME%, %BASECNAME%
         * - replace all occurence of %SUPPORTCLASSNAME%
         */
        void prepareString(std::string& buffer) const;
    };

}
#endif

