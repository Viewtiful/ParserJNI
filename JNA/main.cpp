/** @file
 *
 * Application start routine for JNAConvert
 */

#include <cctype>
#include <cstdlib>
#include <iostream>
#include "Utils/Output.h"
#include "Utils/Parameters.h"
#include "Utils/Parser.h"
#include "Modules/Module.h"
#include "Modules/ModuleList.h"
using std::cout;
using std::string;
using nsUtils::Output;
using nsUtils::Parameters;
using nsUtils::Parser;
using nsModules::Module;
using nsModules::ModuleList;

namespace
{

/** This function display the help. */
void help(char* argv[])
{
    const char* programName = 
        (argv != NULL && argv[0] != NULL) ? argv[0] 
                                          : "JNAConvert";
    cout << "Usage for JNAConvert:\n"
            "    " << programName << " [Options] Arguments\n"
            "Options:\n"
            " -h : Display this help and exit\n"
            " -q : Make the output quiet (display only error)\n"
            " -D : Perform a dry run. The application will not write any\n"
            "      file or create any directory, but will write what it\n"
            "      would do instead.\n"
#ifndef NDEBUG
            " -d<level> : Hide debug message above <level>\n"
            "         0 - hide all debug messages\n"
            "         1 - show usefuls informational messages (default)\n"
            "         2 - show intermediary results\n"
            "         3 - show internal steps\n"
            " -L<output mode> : Specify the output target. Currently\n"
            "                   support JNA and JNI\n"
            "\n"
#endif
            " (*) -H <header dir> : C header directory\n"
            "     -r : Recurse subdirectories of <header dir>\n"
            " (*) -j <Java src dir> : Java source directory\n"
            "     -p <package> : Java base package name\n"
            "\n"
            "Arguments for JNA:\n"
            " (*) -m <supp. class> : The class which will contain\n"
            "                        support code. Generated module will\n"
            "                        reference it. If it doesn't exist,\n"
            "                        an empty class with needed functions\n"
            "                        will be created.\n"
            "                        (you must specify the full package\n"
            "                        path!)\n"
            "     -M <supp. class> : This is the same flag as -m, but it\n"
            "                        will overwrite the content of the\n"
            "                        class if it already exist.\n"
            "\n"
            "Arguments with a (*) are mandatory.\n"
            "If an argument is present multiple time, only the last "
                "occurence will be taken into account.\n"
            "Default values are:\n"
            "- JNA output\n"
            "- no recursion\n"
            "- <package> : default package\n";
}

/** Display a header */
void header(void)
{
    OUT << "JNAConvert - C header to Java class convertion, ALPHA\n"
        << "by: Gabriel Paul \"Cley Faye\" Risterucci\n";
}

int run()
{
    Parameters& parameters(Parameters::getInstance());
    Output& output(Output::getInstance());

    OUT << "Locating C headers...\n";
    ModuleList moduleList(parameters.getHeaderDir());
    Module::vector modules;
    output.startProgress((int) moduleList.getModuleCount(), 
                         "STEP 1/x Adding modules");
    for (size_t i(0); i < moduleList.getModuleCount(); ++i) {
        output.progress("Adding modules");
        modules.push_back(Module(moduleList.getModuleSource(i)));
    }
    output.endProgress();

    output.startProgress((int) modules.size(), 
                         "STEP 2/x Parsing C headers");
    for (Module::vector::iterator iter(modules.begin());
         iter != modules.end();
         ++iter)
    {
        output.progress(string("Parsing \"") + 
                        iter->getModuleName() + 
                        "\"");
        if (!iter->parse()) {
            output.endProgress(true);
            ERR << "Parsing failed\n";
            return EXIT_FAILURE;
        }
    }
    output.endProgress();

    Parser& parser = Parser::getParser(parameters.getTargetType());
    parser.run(modules);

    return EXIT_SUCCESS;
}

} // namespace

int main(int argc, char* argv[])
{
    Parameters& parameters(Parameters::getInstance());

    parameters.parseCommandLine(argc, argv);
    Output::getInstance().setQuiet(parameters.isQuiet());
#ifndef NDEBUG
    Output::getInstance().setDebugLevel(
            parameters.getDebugLevel());
#endif

    header();
    if (parameters.isHelpNeeded()) {
        help(argv);
        if (parameters.isHelpWanted())
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
   }

   return run();
}

