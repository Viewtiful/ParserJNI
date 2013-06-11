/** @file
 *
 * Header for the Parser base class
 */

#ifndef __UTILS_PARSER_H
#define __UTILS_PARSER_H

#include "Modules/Module.h"
#include "Utils/Parameters.h"

namespace nsUtils
{
    class Parser {
      public:

        static Parser& getParser(Parameters::TargetType targetType);

        virtual ~Parser();

        virtual int run(nsModules::Module::vector modules) =0;
    };
}

#endif

