/** @file
 *
 * Body for class ModuleList
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <cstring>
#include "Utils/Output.h"
#include "Modules/ModuleList.h"

using std::string;

#define MODULELIST nsModules::ModuleList
#define MODULESOURCE MODULELIST::ModuleSource

MODULESOURCE::ModuleSource(const string& basePath,
                           const string& subPath,
                           const string& fileName)
    : mFilePath(basePath + subPath + fileName),
      mModuleName(fileName),
      mSubPath(subPath)

{
    DEBUG(3) << "Adding module source:\"" << mFilePath << 
                "\" >> \"" << mSubPath << "." << mModuleName << "\"\n";
}

MODULESOURCE::~ModuleSource()
{
}

const string& MODULESOURCE::getFilePath(void) const
{
    return mFilePath;
}

const string& MODULESOURCE::getModuleName(void) const
{
    return mModuleName;
}

const string& MODULESOURCE::getSubPath(void) const
{
    return mSubPath;
}

MODULELIST::ModuleList(const string& basePath)
    : mBasePath(basePath)
{
	if (mBasePath.length() > 0 && mBasePath[mBasePath.length() - 1] != '/')
        mBasePath += '/';
    DEBUG(1) << "Building file list...\n";
    DEBUG(3) << "Using header path:\"" << mBasePath << "\"\n";
    recurse("");
}

MODULELIST::~ModuleList()
{
}

size_t MODULELIST::getModuleCount(void)
{
    return mModuleSources.size();
}

const MODULESOURCE& MODULELIST::getModuleSource(size_t i)
{
    return mModuleSources[i];
}

void MODULELIST::recurse(const std::string subPath)
{
    DEBUG(2) << "Entering directory \"" << subPath << "\"\n";
    string fullPath(mBasePath + subPath);
    DEBUG(3) << "Using path:\"" << fullPath << "\"\n";
    DIR* dir = opendir(fullPath.c_str());
    if (dir == NULL) {
        ERR << "Failure to explore directory \"" << fullPath << "\"\n";
        return;
    }
    errno = 0;
    struct dirent* entry;
    while ((entry = readdir(dir)))
    {
        DEBUG(3) << "Got entry for:\"" << entry->d_name << "\"\n";
        string fileName(entry->d_name);
        if (fileName.empty())
            continue;

        if (fileName[0] == '.')
            continue;

        struct stat statBuff;
        if (stat((fullPath + "/" + fileName).c_str(), &statBuff))
            break;

		//If it is a directory, enter it and keep looking !
        if (S_ISDIR(statBuff.st_mode)) {
            recurse(fileName + "/");
            continue;
        }

        if (fileName.rfind(".h") == fileName.length() - 2) {
            DEBUG(2) << "Adding file \"" << fileName << "\"\n";
            mModuleSources.push_back(ModuleSource(mBasePath,
                                                  subPath,
                                                  fileName));
        }
        else
        {
            DEBUG(3) << "Ignoring file \"" << fileName << "\"\n";
        }
    }
    if (errno) {
        ERR << "Failure to crawl into directory \"" << fullPath << "\";\n"
               "Error:(" << errno << ") " << strerror(errno) << '\n';
    }
    closedir(dir);
}

#undef MODULESOURCE
#undef MODULELIST

