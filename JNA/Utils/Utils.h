/** @file
 *
 * Utility functions
 */

#ifndef __UTILS_UTILS_H
#define __UTILS_UTILS_H

#include <vector>
#include <string>

namespace nsUtils
{
    /** Replace all occurence of @a src by @a dst in @a buffer. */
    void stringReplace(std::string& buffer, 
                       std::string src, 
                       const std::string& dst);

    /** Replace all occurence of @a src by @a dst in @a buffer.
     * @a src will be surrounded by '%', so to replace @a %PACKAGE% by
     * @a org.dummy for example, you'll have to do something like this:
     * @code
     * stringReplace(buffer, "PACKAGE", "org.dummy");
     * @endcode
     */
    void stringReplace(std::string& buffer, 
                       const std::string& src, 
                       int dst);

    std::string packageToDirectory(std::string package);

    std::string directoryToPackage(std::string directory);

    std::string createJavaFileName(const std::string& srcDir,
                                   const std::string& package,
                                   const std::string& className);

    void makeDir(const std::string& path);

    /** Create all subdirs for a package to exist */
    void createPackageTree(const std::string& srcDir, 
                           const std::string& package);

    /** Make a CType look more Java like */
    std::string toJavaName(std::string source, 
                           bool stripUnderscore = false,
                           bool stripLastT = false,
                           bool capitalFirst = false);

    void splitQualifiedName(const std::string& input,
                            std::string& package,
                            std::string& className);

    /** @see Java.prepareString() */
    void prepareJavaString(std::string& buffer,
                           const std::string package,
                           const std::string imports,
                           const std::string baseJavaName,
                           const std::string baseCName);

    typedef std::vector<std::string> strings;

    bool runCmd(const std::string& cmd,
            const strings& input,
            strings& output);

    strings splitLines(const std::string& input);
}

#endif

