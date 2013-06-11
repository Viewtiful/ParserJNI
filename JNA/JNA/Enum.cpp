/** @file
 *
 * Body for the Enum class
 */

#include "Utils/Output.h"
#include "Utils/Utils.h"
#include "JNA/Enum.h"

using std::string;
using std::ostream;
using nsModules::Module;
using nsUtils::toJavaName;
using nsUtils::stringReplace;

#define ENUM nsJNA::Enum

ENUM::~Enum()
{
}

bool ENUM::create(const Module& module,
                  Type::map& javaTypes)
{
    DEBUG(2) << "Creating Java enums from \"" << module.getModuleName()
             << "\"\n";
    const nsC::Enum::vector& enums(module.getEnums());
    for (nsC::Enum::vector::const_iterator iterator(enums.begin());
         iterator != enums.end();
         ++iterator)
    {
        const nsC::Enum& CEnum(*iterator);

        new Enum(module, CEnum, javaTypes);
    }
    return true;
}

bool ENUM::convertToJava(void)
{
    return true;
}

bool ENUM::needWriting(void) const
{
    return true;
}

bool ENUM::writeJava(ostream& file) const
{
    string structure(
            "public class %BASEJAVANAME% implements NativeMapped\n"
            "{\n"
            "    private static Map<Integer, %BASEJAVANAME%> sValues = "
                "new HashMap<Integer, %BASEJAVANAME%>();\n"
            "    public static boolean containValue(final int value)\n"
            "    {\n"
            "        return sValues.containsKey(value);\n"
            "    }\n"
            "    public static %BASEJAVANAME% fromValue(final int value)\n"
            "    {\n"
            "        return sValues.get(value);\n"
            "    }\n"
            "    private int mValue;\n"
            "    public %BASEJAVANAME%()\n"
            "    {\n"
            "    }\n"
            "    private %BASEJAVANAME%(final int value)\n"
            "    {\n"
            "        mValue = value;\n"
            "        sValues.put(mValue, this);\n"
            "    }\n"
            "    public boolean equals(final Object obj)\n"
            "    {\n"
            "        if (!(obj instanceof %BASEJAVANAME%))\n"
            "        {\n"
            "            return false;\n"
            "        }\n"
            "        final %BASEJAVANAME% op2 = (%BASEJAVANAME%) obj;\n"
            "        return op2.mValue == mValue;\n"
            "    }\n"
            "    public Object fromNative(final Object nativeValue,\n"
            "            final FromNativeContext context)\n"
            "    {\n"
            "        final Integer nativeInteger = (Integer) nativeValue;\n"
            "        if (!%BASEJAVANAME%.class\n"
            "                .isAssignableFrom(context.getTargetType()))\n"
            "        {\n"
            "            throw new RuntimeException(\"Invalid enum\");\n"
            "        }\n"
            "        if (!%BASEJAVANAME%.sValues.containsKey(nativeInteger))\n"
            "        {\n"
            "            throw new RuntimeException("
                "\"Invalid enum value\");\n"
            "        }\n"
            "        return %BASEJAVANAME%.sValues.get(nativeInteger);\n"
            "    }\n"
            "    public int getValue()\n"
            "    {\n"
            "        return mValue;\n"
            "    }\n"
            "    public int hashCode()\n"
            "    {\n"
            "        return mValue;\n"
            "    }\n"
            "    public Class nativeType()\n"
            "    {\n"
            "        return Integer.class;\n"
            "    }\n"
            "    public Object toNative()\n"
            "    {\n"
            "        return new Integer(mValue);\n"
            "    }\n"
            "    public String toString()\n"
            "    {\n"
            "        return this.getClass().getName() + "
                "\"(\" + mValue + \")\";\n"
            "    }\n"
            "%FIELDS%"
            "}\n"
            );
    const nsC::Enum::EnumValues& values(mEnum.getValues());
    string fields;
    for (nsC::Enum::EnumValues::const_iterator iter(values.begin());
         iter != values.end();
         ++iter)
    {
        string field("    static public final %BASEJAVANAME% %FIELD% = "
                     "new %BASEJAVANAME%(%VALUE%);\n");
        stringReplace(field, "FIELD", iter->first);
        stringReplace(field, "VALUE", iter->second);
        fields += field;
    }
    stringReplace(structure, "FIELDS", fields);
    prepareString(structure);
    file << structure;
    return true;
}

ENUM::Enum(const Module& module,
           const nsC::Enum& CEnum,
           Type::map& javaTypes)
    : super(module),
      mEnum(CEnum)
{
    string shortName;
    if (!CEnum.getTypedef().empty()) {
        mBaseCName = CEnum.getTypedef();
        shortName = mBaseCName;
    }
    else
    {
        mBaseCName = CEnum.getName();
        shortName = mBaseCName;
        shortName.replace(0, 7, "");
    }
    mBaseJavaName = toJavaName(shortName, false, false, true);
    mBasePackage = "types.enums";
    mPackageList.addImport("java.util.HashMap");
    mPackageList.addImport("java.util.Map");
    mPackageList.addImport("com.sun.jna.FromNativeContext");
    mPackageList.addImport("com.sun.jna.NativeMapped");
    addToMap(javaTypes);
}

#undef ENUM

