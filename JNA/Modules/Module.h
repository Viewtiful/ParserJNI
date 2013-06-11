/** @file
 *
 * Header for Module class
 */

#ifndef __MODULES_MODULE_H
#define __MODULES_MODULE_H

#include <string>
#include <vector>
#include "C/Enum.h"
#include "C/Struct.h"
#include "C/Callback.h"
#include "C/Function.h"
#include "C/Typedef.h"
#include "C/Consts.h"
#include "Modules/ModuleList.h"

namespace nsModules
{
    /** A module.
     *
     * One module is made for every header file.
     */
    class Module
    {
      public:
        typedef std::vector<Module> vector;

        /** Create this module using the specified source. */
        Module(const ModuleList::ModuleSource& moduleSource);
        virtual ~Module();

        /** Parse the C header */
        bool parse(void);

        const nsC::Struct::vector& getStructs(void) const;
        const nsC::Enum::vector& getEnums(void) const;
        const nsC::Callback::vector& getCallbacks(void) const;
        const nsC::Function::vector& getFunctions(void) const;
        const nsC::Typedef::vector& getTypedefs(void) const;
        const nsC::Consts& getConsts(void) const;

        const std::string& getModuleName(void) const;
        const std::string& getSubPath(void) const;

      protected:
        std::string mFilePath;
        std::string mName;
        std::string mSubPath;

        nsC::Function::vector mFunctions;
        nsC::Enum::vector mEnums;
        nsC::Struct::vector mStructs;
        nsC::Callback::vector mCallbacks;
        nsC::Typedef::vector mTypedefs;
        nsC::Consts mConsts;
    };
}

#endif

