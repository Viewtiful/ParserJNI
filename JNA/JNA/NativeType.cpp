/** @file
 *
 * Body for the NativeType class
 */

#include "Utils/Output.h"
#include "Utils/Utils.h"
#include "JNA/Pointer.h"
#include "JNA/NativeType.h"

using std::string;
using std::ostream;
using nsC::Typedef;
using nsUtils::splitQualifiedName;

#define NATIVETYPE nsJNA::NativeType

NATIVETYPE::~NativeType()
{
}

void NATIVETYPE::createNativeTypes(Type::map& javaTypes)
{
    // void
    new NativeType("void", "void", "", javaTypes);

    // pointers are special
    new Pointer("void *", javaTypes);
    new Pointer("char *", javaTypes);

    // base type
    new NativeType("int", "int", "", javaTypes);
    new NativeType("bool", "boolean", "", javaTypes);
    // TODO check if bool is specifically an int in standard
    new NativeType("bool *", "IntByReference", "com.sun.jna.ptr", 
                   javaTypes);

    // various NativeLong
    new NativeType("size_t", "NativeLong", "com.sun.jna", javaTypes);
    new NativeType("size_t *", "NativeLongByReference", "com.sun.jna.ptr", 
                   javaTypes);
    new NativeType("off_t", "NativeLong", "com.sun.jna", javaTypes);
    new NativeType("off_t *", "NativeLongByReference", "com.sun.jna.ptr",
                   javaTypes);

    // strings
    new NativeType("const char *", "String", "", javaTypes);

    // Weird stuff ?
    // Functions using FILE * in KTB also use variadic, so they will be
    // stripped down, hopefully.
    new NativeType("FILE *", "Pointer", "com.sun.jna", javaTypes);
}

bool NATIVETYPE::createTypedef(const Typedef::vector& typedefs,
                               Type::map& javaTypes)
{
    for (Typedef::vector::const_iterator iter(typedefs.begin());
         iter != typedefs.end();
         ++iter)
    {
        string targetType(iter->getTargetType());
		std::cout << "targetType : " << targetType << std::endl;
        string package;
        string className;
        splitQualifiedName(targetType, package, className);
		std::cout << "targetType : " << targetType << ", package : " << package << "and className : " << className << std::endl;
        new NativeType(iter->getCType(), className, package, javaTypes);
    }
    return true;
}

bool NATIVETYPE::convertToJava(void)
{
    return true;
}

bool NATIVETYPE::needWriting(void) const
{
    return false;
}

bool NATIVETYPE::writeJava(ostream& file) const
{
    (void) file;
    return false;
}

string NATIVETYPE::getFullPackageName(void) const
{
    return mBasePackage;
}

NATIVETYPE::NativeType(const string& baseCName,
                       const string& baseJavaName,
                       const string& fullPackage,
                       Type::map& javaTypes)
    : super("<native>")
{
    mBaseCName = baseCName;
    mBaseJavaName = baseJavaName;
    mBasePackage = fullPackage;
    addToMap(javaTypes);
}

#undef NATIVETYPE

