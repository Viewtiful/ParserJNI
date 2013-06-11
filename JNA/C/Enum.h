/** @file
 *
 * Header for Enum class
 */

#ifndef __C_ENUM_H
#define __C_ENUM_H

#include <string>
#include <vector>
#include <utility>
#include "Utils/Displayable.h"

namespace nsC
{
    /** Represent a C enumeration.
     *
     * One instance of this class is created everytime a
     * @code
     * typedef enum
     * @endcode
     * is found.
     */
    class Enum: public nsUtils::Displayable
    {
      public:
        typedef std::pair<std::string,int> EnumValue;
        typedef std::vector<EnumValue> EnumValues;
        typedef std::vector<Enum> vector;

        Enum();
        virtual ~Enum();

        /** Set the name of the enum.
         *
         * This is the qualified name (with "enum " in front of it). It can
         * be omitted when the enum is directly used with typedef.
         */
        void setName(const std::string& name);
        const std::string& getName(void) const;
        /** Set the typedef name of the enum.
         *
         * This is the "useful" name of the enum, at the end of the typedef.
         */
        void setTypedef(const std::string& name);
        const std::string& getTypedef(void) const;

        /** Add a constant in this enum.
         *
         * This constant's value will be the last value plus one.
         */
        void addValue(const std::string& name);

        /** Add a constant with a specific value. */
        void addValue(const std::string& name, int value);

        /** Add a constant using another constant as the source value.
         *
         * If @a value is not already present in the enum, this will fail.
         */
        bool addValue(const std::string& name, 
                      const std::string& value);

        const EnumValues& getValues(void) const;

      protected:
        int mNextValue;
        EnumValues mValues;
        std::string mName;
        std::string mTypedef;

        void display(std::ostream& stream) const;
    };
}

#endif

