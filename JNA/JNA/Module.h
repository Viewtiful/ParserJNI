/** @file
 *
 * Header for the Module class
 */

#ifndef __JAVA_MODULE_H
#define __JAVA_MODULE_H

#include <string>
#include <iostream>
#include <vector>
#include "JNA/TypesDictionnary.h"
#include "JNA/PackageList.h"
#include "Modules/Module.h"

namespace nsJNA
{
    namespace nsWrappers
    {
        class Wrapper;
    }

    class Module
    {
      public:
        Module(const nsModules::Module& module, const std::string& commHandler);
        virtual ~Module();

        bool prepare(const nsJNA::TypesDictionnary& typesDict);

        bool needWriting(void) const;
        bool convert(std::ostream& file) const;

        const std::string& getName(void) const;

        std::string getFullPackageName(void) const;
        std::string getBaseJavaName(void) const;

        static bool processModules(const nsModules::Module::vector& 
                                        modules,
                                   const nsJNA::TypesDictionnary& 
                                        typesDict);

        void addWrapperPtr(nsWrappers::Wrapper* wrapper);

        PackageList& getPackageList(void);

      protected:
        class Method
        {
          public:
            typedef std::vector<Method> vector;

            Method(const nsJNA::TypesDictionnary& typesDict,
                   const nsC::Function& function,
                   PackageList& packageList);
            virtual ~Method();

            bool convert(void);

            std::string getString(void) const;

          protected:
            const nsJNA::TypesDictionnary* mDictionnary;
            const nsC::Function* mFunction;
            PackageList* mPackageList;
            std::string mReturnJavaType;
            std::vector<std::string> mParamString;
            bool mIgnore;
        };

        std::vector<nsWrappers::Wrapper*> mWrappers;
        const nsModules::Module& mModule;
        std::string mName;
        std::string mCommHandler;
        Method::vector mMethods;
        PackageList mPackageList;
        std::string mConstsString;

        bool updateComments(void);
        bool prepareFunctions(const nsJNA::TypesDictionnary& typesDict);
        bool prepareConsts(const nsJNA::TypesDictionnary& typesDict);
    };
}

#endif

