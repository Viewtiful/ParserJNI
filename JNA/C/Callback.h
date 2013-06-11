/** @file
 *
 * Header for Callback class
 */

#ifndef __C_CALLBACK_H
#define __C_CALLBACK_H

#include <string>
#include <vector>
#include "C/Param.h"
#include "Utils/Displayable.h"

namespace nsC
{
    /** A callback definition in C.
     *
     * An instance of this class will be created everytime a C-type callback
     * is encountered.
     */
    class Callback: public nsUtils::Displayable
    {
      public:
        typedef std::vector<Callback> vector;

        Callback();
        virtual ~Callback();

        /** Set the name of the callback.
         *
         * This is typename in:
         * @code
         * typedef void (*typename)(void);
         * @endcode
         */
        void setName(const std::string& name);
        const std::string& getName(void) const;

        /** Set the return type of the callback. */
        void setReturnType(const std::string& returnType);
        const std::string& getReturnType(void) const;

        /** Return the parameters list for this callback. */
        Param::vector& getParamList(void);

        const Param::vector& getParamList(void) const;

      protected:
        std::string mReturnType;
        std::string mName;
        Param::vector mParams;

        void display(std::ostream& stream) const;
    };
}

#endif

