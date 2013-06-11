/** @file
 *
 * Body for the SupportClass class
 */

#include <cstring>
#include <string>
#include <fstream>
#include "Utils/Output.h"
#include "Utils/Parameters.h"
#include "Utils/Utils.h"
#include "JNA/SupportClass.h"

using std::string;
using std::fstream;
using std::ofstream;
using std::ios;
using std::ios_base;
using std::streampos;
using nsUtils::Parameters;
using nsUtils::packageToDirectory;
using nsUtils::splitQualifiedName;
using nsUtils::stringReplace;
using nsUtils::createPackageTree;

#define SUPPORTCLASS nsJNA::SupportClass

SUPPORTCLASS::~SupportClass()
{
}

bool SUPPORTCLASS::create(void)
{
    Parameters& param(Parameters::getInstance());
    DEBUG(1) << "Checking for the presence of the support class\n";

    string supportClass(param.getBaseModule());
    string supportClassPath(param.getJavaSrcDir() + '/' +
                            packageToDirectory(supportClass) + ".java");
    string className;
    string package;
    splitQualifiedName(supportClass, package, className);
    DEBUG(3) << "Creating directory for \"" << package << "\"\n";
    createPackageTree(param.getJavaSrcDir(), package);
    DEBUG(3) << "Looking for \"" << supportClassPath << "\"\n";

    if (param.isDryRun()) {
        OUT << "---DRYRUN--- would check for file \"" << supportClassPath
            << "\"\n";
        return true;
    }

    fstream file(supportClassPath.c_str());
    if (file.fail()) {
        // FIXME messy code is messy
        ofstream ofs(supportClassPath.c_str());
        if (ofs.fail()) {
            ERR << "Can't create \"" << supportClassPath << "\"\n";
            return false;
        }
        ofs.close();
        file.open(supportClassPath.c_str());
        if (file.fail()) {
            ERR << "Can't reopen \"" << supportClassPath << "\"\n";
            return false;
        }
    }
    streampos begin;
    streampos end;
    file.seekg(0, ios_base::beg);
    begin = file.tellg();
    file.seekg(0, ios_base::end);
    end = file.tellg();
    if ((end - begin) != 0) {
        DEBUG(2) << "Support class found\n";
        if (param.isForceSupportClass()) {
            DEBUG(1) << "Erasing existing support class\n";
            file.close();
            file.open(supportClassPath.c_str(), ios::trunc);
            if (file.fail()) {
                ERR << "Can't truncate \"" << supportClassPath << "\"\n";
                return false;
            }
        }
        else
            return true;
    }
    OUT << "STEP 6/x Creating support class\n";
    string packageHead("package %PACKAGE%;\n");
    string baseContent(
            "import com.sun.jna.NativeLibrary;\n"
            "/** Provide the glue to use the KTB library */\n"
            "public class %CLASSNAME%\n"
            "{\n"
    		"    private static final NativeLibrary sLibrary;\n"
    	    "    static { sLibrary = NativeLibrary.getInstance(getLibName());}\n"
    	    "    /** Return the shared library file path. */\n"
    	    "    private static String getLibName()\n"
    	    "    {\n"
    	    "        String libName;\n"
    	    "        final String envLibName = System.getenv(\"KTB_LIBRARY\");\n"
    	    "        if (envLibName != null)\n"
    	    "        {\n"
    	    "            libName = envLibName;\n"
    	    "            System.out.println(\"Using KTB library path:\" + libName);\n"
    	    "        }\n"
    	    "        else {\n"
    	    "    	    libName = \"ktb\";\n"
    	    "            System.out.println(\"KTB library path not specified \\n Looking for KTB in system\");\n"
    	    "        }\n"
    	    "       return libName;\n"
    	    "    }\n"
            "    /** return the KTB NativeLibrary instance */\n"
            "    public static NativeLibrary getLibrary()\n"
            "    {\n"
            "        return sLibrary;\n"
            "    }\n"
            "}\n"
            );
    if (!package.empty()) {
        stringReplace(packageHead, "PACKAGE", package);
        // FIXME error check
        file << packageHead;
    }
    stringReplace(baseContent, "CLASSNAME", className);
    // FIXME error check
    file << baseContent;
    file.close();
    return true;
}

#undef SUPPORTCLASS

