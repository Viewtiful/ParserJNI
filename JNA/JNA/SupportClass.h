/** @file
 *
 * Header for the SupportClass class
 */

#ifndef __JAVA_SUPPORTCLASS_H
#define __JAVA_SUPPORTCLASS_H

namespace nsJNA
{
    class SupportClass
    {
      public:
        virtual ~SupportClass();

        static bool create(void);
    };
}

#endif

