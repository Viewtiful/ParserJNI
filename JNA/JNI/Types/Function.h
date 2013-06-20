/** @file
 *
 * Header for JNIParser
 */

#ifndef __JNI_FUNCTION_H

#include "JNI/TypesDictionnary.h"
#include "C/Function.h"
#include <iostream>
namespace nsJNI {
    class Function
    {
      public:
        Function(nsC::Function);
		virtual ~Function();
        void convert();
    };
}

#endif

