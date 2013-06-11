/** @file
 *
 * Body for utility functions
 */

#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sstream>
#include <unistd.h>
#include "Utils/Output.h"
#include "Utils/Parameters.h"
#include "Utils/Utils.h"

using std::ostringstream;
using std::string;

void nsUtils::stringReplace(string& buffer,
                            string src,
                            const string& dst)
{
    string::size_type index;
    src = string("%") + src + "%";
    if (dst.find(src) != string::npos)
        return;

    while ((index = buffer.find(src)) != string::npos) {
        buffer.replace(index, src.length(), dst);
    }
}

void nsUtils::stringReplace(string& buffer,
                            const string& src,
                            int dst)
{
    ostringstream ss;
    ss << dst;
    stringReplace(buffer, src, ss.str());
}

string nsUtils::packageToDirectory(string package)
{
    string::size_type index;
    while ((index = package.find(".")) != string::npos)
        package.replace(index, 1, "/");
    return package;
}

string nsUtils::directoryToPackage(string directory)
{
    string::size_type index;
    while ((index = directory.find("/")) != string::npos)
        directory.replace(index, 1, ".");
    return directory;
}

string nsUtils::createJavaFileName(const string& srcDir,
                                   const string& package,
                                   const string& className)
{
    return srcDir + '/' + packageToDirectory(package) + '/' + 
           className + ".java";
}

void nsUtils::makeDir(const string& path)
{
#ifdef __MINGW32__
    mkdir(path.c_str());
#else
    mkdir(path.c_str(), S_IRWXU | S_IRGRP | S_IROTH);
#endif
}

void nsUtils::createPackageTree(const string& srcDir,
                                const string& package)
{
    string currentDir(srcDir);
    string::size_type index(0);
    string::size_type nextDot;
    while ((nextDot = package.find(".", index)) != string::npos) {
        currentDir = currentDir + "/" + package.substr(index, 
                                                       nextDot - index);
        index = nextDot + 1;
        DEBUG(3) << "Creating dir:\"" << currentDir << "\"\n";
        makeDir(currentDir);
    }
    currentDir = currentDir + "/" + package.substr(index);
    DEBUG(3) << "Creating last dir:\"" << currentDir << "\"\n";
    makeDir(currentDir);
}

std::string nsUtils::toJavaName(string source,
                                bool stripUnderscore,
                                bool stripLastT,
                                bool capitalFirst)
{
    if (source.empty())
        return "";

    if (capitalFirst)
        source[0] = (char) toupper((int) source[0]);

    if (stripLastT) {
        size_t i;
        if ((i = source.find("_t")) == source.length() - 2)
            source.erase(i, 2);
    }
    if (stripUnderscore) {
        size_t i;
        while ((i = source.find("_")) != string::npos)
        {
            source.erase(i, 1);
            if (i < source.length())
                source[i] = (char) toupper((int) source[i]);
        }
    }
    return source;
}

void nsUtils::splitQualifiedName(const string& input,
                                 string& package, string& className)
{
    string::size_type pos(input.rfind("."));
    if (pos == string::npos) {
        package = "";
        className = input;
    }
    package = input.substr(0, pos);
    className = input.substr(pos + 1);
    DEBUG(2) << "Splitting qualified name \"" << input <<
                "\" into package \"" << package <<
                "\" and class \"" << className << "\"\n";
}

void nsUtils::prepareJavaString(string& buffer,
                                const string package,
                                const string imports,
                                const string baseJavaName,
                                const string baseCName)
{
    buffer = string("%IMPORTS%") + 
             "@SuppressWarnings(\"all\")\n" +
             buffer;

    if (!package.empty())
        buffer = string("package %FULLPACKAGE%;\n") + buffer;

    stringReplace(buffer, "FULLPACKAGE", package);
    stringReplace(buffer, "IMPORTS", imports);
    stringReplace(buffer, "BASEJAVANAME", baseJavaName);
    stringReplace(buffer, "BASECNAME", baseCName);
    string supportPackage;
    string supportName;
    splitQualifiedName(Parameters::getInstance().getBaseModule(), 
                       supportPackage,
                       supportName);
    stringReplace(buffer, "SUPPORTCLASSNAME", supportName);
}

bool nsUtils::runCmd(const string& cmd,
        const strings& input,
        strings& output)
{
    int childStdIn[2]; // child read 0, parent write 1
    int childStdOut[2]; // parent read 0, child write 1
    if (pipe(childStdIn) != 0) {
        std::cerr << "Failed to create pipe 1\n";
        return false;
    }
    if (pipe(childStdOut) != 0) {
        std::cerr << "Failed to create pipe 2\n";
        return false;
    }
    pid_t child(fork());
    if (child == -1) {
        std::cerr << "Failed to fork\n";
        close(childStdIn[0]);
        close(childStdIn[1]);
        close(childStdOut[0]);
        close(childStdOut[1]);
        return false;
    }
    if (child == 0) {
        // child
        close(childStdIn[1]);
        close(childStdOut[0]);
        dup2(childStdIn[0], 0);
        dup2(childStdOut[1], 1);
        execl(cmd.c_str(), cmd.c_str(), NULL);
        exit(1);
    }
    // parent
    close(childStdIn[0]);
    close(childStdOut[1]);
    char lineEnd('\n');
    for (size_t i = 0; i < input.size(); ++i) {
        write(childStdIn[1], input[i].c_str(), input[i].length());
        write(childStdIn[1], &lineEnd, 1);
    }
    close(childStdIn[1]);
    ssize_t readCount;
    const int bufferSize(512);
    char buffer[bufferSize + 1];
    while ((readCount = read(childStdOut[0], buffer, bufferSize)) > 0) {
        buffer[readCount] = '\0';
        if (buffer[readCount - 1] == '\n') {
            buffer[readCount - 1] = '\0';
        }
        output.push_back(string(buffer));
    }
    close(childStdOut[0]);
    wait(NULL);
    return true;
}

nsUtils::strings nsUtils::splitLines(const string& input)
{
    strings result;
    string::size_type EOLPos;
    string::size_type searchPos = 0;
    while ((EOLPos = input.find('\n', searchPos)) != string::npos) {
        result.push_back(input.substr(searchPos, EOLPos - searchPos));
        searchPos = EOLPos + 1;
    }
    if (searchPos < (input.length() - 1)) {
        result.push_back(input.substr(searchPos));
    }
    return result;
}
