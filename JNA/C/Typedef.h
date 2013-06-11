/** @file
 *
 * Header for the Typedef class
 */

#ifndef __C_TYPEDEF_H
#define __C_TYPEDEF_H

#include <vector>
#include <string>

namespace nsC
{
    class Typedef
    {
      public:
        typedef std::vector<Typedef> vector;

        Typedef(const std::string& CType, const std::string& javaType);
        virtual ~Typedef();

        const std::string& getCType(void) const;
        const std::string& getTargetType(void) const;

      protected:
        std::string mCType;
        std::string mJavaType;
    };
}

#endif

