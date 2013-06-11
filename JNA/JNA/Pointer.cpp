/** @file
 *
 * Body for the Pointer class
 */

#include "JNA/Pointer.h"

using std::string;
using std::ostream;

#define POINTER nsJNA::Pointer

POINTER::~Pointer()
{
}

bool POINTER::isSpecial(void) const
{
    return true;
}

size_t POINTER::getVariantCount(void) const
{
    return 2;
}

string POINTER::getVariantName(size_t id) const
{
    switch (id)
    {
      case 1: return "ByteBuffer";
      default: return "Pointer";
    }
}

string POINTER::getVariantPackage(size_t id) const
{
    switch (id)
    {
      case 1: return "java.nio";
      default: return "com.sun.jna";
    }
}

POINTER::Pointer(const string& nativeName, Type::map& javaTypes)
    : super(nativeName, "Pointer", "com.sun.jna", javaTypes)
{
}

#undef POINTER

