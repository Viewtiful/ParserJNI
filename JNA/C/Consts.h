/** @file
 *
 * Header for Consts class
 */

#ifndef __C_CONSTS_H
#define __C_CONSTS_H

#include <vector>
#include <string>
#include <utility>
#include "Utils/Displayable.h"

namespace nsC
{
    /** A const definition that need to be available in Java.
     *
     * For now, those consts values are specified by hand, since it's not
     * practical to parse every #define and guess the corresponding Java
     * type, if any.
     *
     * To specify a const value for a given module in C code, add:
     * @code
     * //JNA CONST <type> <var_name> <value>
     * @endcode
     * Currently only int is valid for <type>.
     */
    class Consts: public nsUtils::Displayable
    {
      public:
        typedef std::pair<std::string, std::string> NameValuePair;
        typedef std::pair<std::string, NameValuePair> TypeValuePair;

        Consts();
        virtual ~Consts();

        /** Add a const to this list. */
        void addValue(const std::string& type,
                      const std::string& name,
                      const std::string& value);

        size_t getCount(void) const;
        const TypeValuePair& getValue(size_t id) const;


      protected:
        typedef std::vector<TypeValuePair> ValueVector;

        ValueVector mValues;

        void display(std::ostream& stream) const;
    };
}

#endif

