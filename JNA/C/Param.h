/** @file
 *
 * Header for the Param class
 */

#ifndef __C_PARAM_H
#define __C_PARAM_H

#include <string>
#include <vector>
#include "Utils/Displayable.h"

namespace nsC
{
    /** Hold a single parameter for function parameters list/struct fields.
     */
    class Param: public nsUtils::Displayable {
      public:
        typedef std::vector<Param> vector;

        /** Create the param object.
         *
         * If type contain indirections ('*'), they will be removed from the
         * type string, and increase the count returned by
         * getIndirections().
         */
        Param(const std::string& type,
              const std::string& name);
        virtual ~Param();

        /** Return the base type of this parameter. */
        const std::string& getType(void) const;
        /** Return the name of this parameter. */
        const std::string& getName(void) const;
        /** Return the number of indirections of this parameter. */
        int getIndirections(void) const;
        /** Return the C type, with indirections */
        std::string getCType(void) const;

        bool operator != (const Param& B) const;

      protected:
        std::string mType;
        std::string mName;
        int mIndirections;

        void display(std::ostream& stream) const;
    };

    bool operator == (const Param::vector& A, const Param::vector& B);
}

#endif

