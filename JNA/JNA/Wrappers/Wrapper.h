/** @file
 *
 * Header for the Wrapper class
 */

#ifndef __JAVA_WRAPPERS_WRAPPER_H
#define __JAVA_WRAPPERS_WRAPPER_H

#include <string>
#include "C/Function.h"
#include "JNA/Type.h"
#include "JNA/PackageList.h"
#include "Modules/Module.h"
#include "JNA/Module.h"

namespace nsJNA
{
    namespace nsWrappers
    {
        class Wrapper
        {
          public:
            virtual ~Wrapper();

            static bool addWrappers(const nsModules::Module& module,
                                    nsJNA::Module& javaModule,
                                    const nsJNA::TypesDictionnary&
                                        dictionnary);

            bool updateComment(const std::string& commHandler);

            static std::string getWrappers(std::vector<Wrapper*> wrappers);

            virtual std::string getWrapperCode(void) const =0;

          protected:
            /** Wrap a parameters frmo a native type to a java type if
             * needed/possible. */
            class WrappedParam
            {
              public:
                typedef std::vector<WrappedParam*> vector;

                /** @param[in] fromType The java type
                 * @param[in] fromName The parameter name
                 */
                WrappedParam(const std::string& fromType,
                             const std::string& fromName,
                             vector& wrappedParams,
                             const nsJNA::Type* paramType,
                             nsJNA::PackageList& packageList);
                virtual ~WrappedParam();

                /** Wrap the parameters.
                 *
                 * @return true if there is another iteration possible,
                 * false otherwise.
                 */
                static bool wrapParams(const nsJNA::TypesDictionnary& 
                                           dict,
                                       const nsC::Param::vector& params,
                                       vector& wrappedParams,
                                       nsJNA::PackageList& packageList,
                                       int iteration = 0);

                static bool wrapParams(const nsJNA::TypesDictionnary&
                                           dict,
                                       const nsC::Param::vector
                                                ::const_iterator&
                                           begin,
                                       const nsC::Param::vector
                                                ::const_iterator&
                                           end,
                                       vector& wrappedParams,
                                       nsJNA::PackageList& packageList,
                                       int iteration = 0);

                std::string getName(void) const;
                /** The name of the parameter after it's translated into a
                 * local variable */
                std::string getWrappedName(void) const;
                /** The line to add to the function to translate from the
                 * parameter to the wrapper parameter */
                std::string getWrappingLine(void) const;
                std::string getAfterWrappingLine(void) const;
                /** The java type.
                 *
                 * This is mToType. If empty, the parameter is hidden.
                 */
                std::string getJavaType(void) const;

              protected:
                std::string mFromType;
                std::string mFromName;
                std::string mToName;
                std::string mToType;
                std::string mConvertCommand;
                std::string mAfterCommand;

                static void addDirectWrapper(const nsC::Param& param,
                                             const nsJNA::Type* paramType,
                                             vector& wrappedParams,
                                             nsJNA::PackageList& 
                                                packageList);
                static void addByteBufferWrapper(const nsC::Param& buffer,
                                                 vector& wrappedParams,
                                                 nsJNA::PackageList&
                                                    packageList);
                static void addByteBufferWrapperWithOffset(
                                                 const nsC::Param& buffer,
                                                 vector& wrappedParams,
                                                 nsJNA::PackageList&
                                                    packageList);

                static void addStructureWrapper(
                        const nsC::Param& structure,
                        const nsJNA::Type* currentType,
                        vector& wrappedParams,
                        nsJNA::PackageList& packageList);
            };

            WrappedParam::vector mWrappedParams;
            std::string mComment;
            std::string mFuncName;
            std::string mReturnType;
            nsJNA::Module& mJavaModule;

            Wrapper(const nsC::Function& function, 
                    nsJNA::Module& javaModule);

            std::string getParamList(void) const;
            std::string getCallerList(void) const;
            std::string getParamWrappers(void) const;
            std::string getParamAfterWrappers(void) const;

            /** Replace:
             * - %COMMENT%
             * - %RETURNTYPE%
             * - %FUNCNAME%
             * - %MODULENAME%
             * - %PARAMS%
             * - %WRAPPERS%
             * - %AFTERWRAPPERS%
             * - %CALLPARAMS%
             */
            void prepareString(std::string& str) const;
        };
    }
}

#endif

