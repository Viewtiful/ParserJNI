/** @file
 *
 * Header for ModuleList class
 */

#ifndef __MODULES_MODULELIST_H
#define __MODULES_MODULELIST_H

#include <string>
#include <vector>

namespace nsModules
{
    /** Create the list of modules.
     *
     * This class will crawl through a base directory to find every headers
     * and generate a list of modules from them.
     */
    class ModuleList
    {
      public:
        /** A module "source".
         *
         * This hold the information needed to initialize a module.
         */
        class ModuleSource
        {
          public:
            /** Define the source of a module.
             *
             * For example, if headers are located in the base directory
             * "/usr/include/headers", and a header is found in
             * "/usr/include/headers/mod1/file.h", @a filePath will include
             * this whole path, while @a modulePath will only be 
             * "mod1/file.h".
             *
             * @param[in] basePath
             * The root path
             *
             * @param[in] subPath
             * The relative path
             *
             * @param[in] fileName
             * The module file name
             */
            ModuleSource(const std::string& basePath,
                         const std::string& subPath,
                         const std::string& fileName);
            virtual ~ModuleSource();

            const std::string& getFilePath(void) const;
            const std::string& getModuleName(void) const;
            const std::string& getSubPath(void) const;

          protected:
            std::string mFilePath;
            std::string mModuleName;
            std::string mSubPath;
        };

        /** Build a module list from a base directory. */
        ModuleList(const std::string& basePath);
        virtual ~ModuleList();

        /** Return the number of modules */
        size_t getModuleCount(void);
        /** Return the source for a specific module */
        const ModuleSource& getModuleSource(size_t i);

      protected:
        typedef std::vector<ModuleSource> ModuleSourceVector;

        ModuleSourceVector mModuleSources;
        std::string mBasePath;

        void recurse(const std::string subPath);
    };
}

#endif

