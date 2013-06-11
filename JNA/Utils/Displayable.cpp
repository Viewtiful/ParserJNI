/** @file
 *
 * Body for the Displayable class
 */

#include "Displayable.h"

using std::ostream;
using nsUtils::Displayable;

ostream& operator << (ostream& stream,
                      const Displayable& disp)
{
    disp.display(stream);
    return stream;
}

