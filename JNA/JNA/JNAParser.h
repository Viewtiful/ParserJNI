/** @file
 *
 * Header for JNAParser
 */

#ifndef __JNA_JNAPARSER_H

#include "Utils/Parser.h"

namespace nsJNA {
    class JNAParser: public nsUtils::Parser {
      public:
        virtual ~JNAParser();

        int run(nsModules::Module::vector modules);
    };
}

#endif

