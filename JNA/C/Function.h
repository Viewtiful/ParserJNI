/** @file
 *
 * Header for the Function class
 */

#ifndef __C_FUNCTION_H
#define __C_FUNCTION_H

#include <string>
#include <utility>
#include <vector>
#include "C/Param.h"
#include "Utils/Displayable.h"

namespace nsC
{
    /** A C function definition.
     *
     * One instance of this is created for every function found in a module.
     */
    class Function: public nsUtils::Displayable
    {
      public:
        typedef std::vector<Function> vector;

        Function();
        virtual ~Function();

        /** Set the return type of the function. */
        void setReturnType(const std::string& returnType);
        std::string getReturnType(void) const;
        /** Set the name of the function. */
        void setName(const std::string& name);
        const std::string& getName(void) const;
        /** Return this function parameters list. */
        Param::vector& getParamList(void);
        const Param::vector& getParamList(void) const;
        bool isVariadic(void) const;

        void setComment(const std::string& comment);
        const std::string& getComment() const;

      protected:
        bool mReturnTypeSet;
        std::string mReturnType;
        bool mNameSet;
        std::string mName;
        Param::vector mParams;
        std::string mComment;

        void display(std::ostream& stream) const;
    };
}

#endif

