/** @file
 *
 * Body for the Parser class
 */

#include "Utils/Parser.h"
#include "JNA/JNAParser.h"
#include "JNI/JNIParser.h"

#define PARSER nsUtils::Parser

using nsUtils::Parameters;
using nsJNA::JNAParser;
using nsJNI::JNIParser;

namespace {
JNAParser parserJNA;
JNIParser parserJNI;
}

PARSER& PARSER::getParser(Parameters::TargetType targetType)
{
    switch (targetType) {
    case Parameters::targetJNA:
        return parserJNA;
    case Parameters::targetJNI:
        return parserJNI;
    default:
        // should throw error...
        return parserJNA;
    }
}

PARSER::~Parser()
{
}

#undef PARSER

