/** @file
 *
 * Header for the Displayable class
 */

#ifndef __UTILS_DISPLAYABLE_H
#define __UTILS_DISPLAYABLE_H

#include <iostream>

namespace nsUtils { class Displayable; }

std::ostream& operator << (std::ostream& stream,
                           const nsUtils::Displayable& disp);

namespace nsUtils
{
    /** Define a class that can be displayed on a standard stream. */
    class Displayable
    {
      protected:
        virtual ~Displayable() { }
        
        /** Child classes must define this function to perform the needed
         * output operation. */
        virtual void display(std::ostream& stream) const =0;

        friend std::ostream& ::operator << (std::ostream& stream, 
                                            const Displayable& disp);
    };
}

#endif

