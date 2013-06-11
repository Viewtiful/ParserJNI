/** @file
 *
 * Header for the Struct class
 */

#ifndef __C_STRUCT_H
#define __C_STRUCT_H

#include <string>
#include <vector>
#include "Param.h"

namespace nsC
{
    /** A C typedef struct. */
    class Struct: public nsUtils::Displayable
    {
      public:
        typedef std::vector<Struct> vector;

        Struct();
        virtual ~Struct();

        /** Name of the struct.
         *
         * This is the qualified name (with "struct " before it)
         */
        void setName(const std::string& name);
        const std::string& getName(void) const;
        /** Typedef name of the struct. */
        void setTypedef(const std::string& name);
        const std::string& getTypedef(void) const;
        /** If this typedef is a pointer, this is indicated here */
        void addTypedefIndirection(void);
        int getTypedefIndirection(void) const;

        /** Add a field to the struct. */
        void addField(const std::string& type,
                      const std::string& name);

        /** Return the fields list */
        Param::vector& getFields(void);

        const Param::vector& getFields(void) const;

      protected:
        std::string mName;
        std::string mTypedef;
        Param::vector mFields;
        int mIndirections;

        void display(std::ostream& stream) const;
    };
}

#endif

