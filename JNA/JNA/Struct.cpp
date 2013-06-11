/** @file
 *
 * Body for the Struct class
 */

#include <cctype>
#include "Utils/Utils.h"
#include "Utils/Output.h"
#include "C/Struct.h"
#include "JNA/Struct.h"

using std::string;
using std::ostream;
using nsC::Param;
using nsModules::Module;
using nsJNA::TypesDictionnary;
using nsUtils::stringReplace;
using nsUtils::toJavaName;

#define STRUCT nsJNA::Struct

bool STRUCT::create(const Module& module,
                    const TypesDictionnary& dictionnary,
                    Type::map& javaTypes)
{
    DEBUG(2) << "Creating Java structs from \"" << module.getModuleName() 
             << "\"\n";
    const nsC::Struct::vector& structs(module.getStructs());
    for (nsC::Struct::vector::const_iterator iterator(structs.begin());
         iterator != structs.end();
         ++iterator)
    {
        const nsC::Struct& CStruct(*iterator);

        bool haveName(!CStruct.getName().empty());
        bool haveTypedef(!CStruct.getTypedef().empty());
        bool haveFields(CStruct.getFields().size() != 0);
        bool isTypedefPointer(CStruct.getTypedefIndirection() == 1);
        bool isDeepPointer(CStruct.getTypedefIndirection() > 1);
        bool isConstRedefinition(haveTypedef && 
                CStruct.getTypedef().find("const_") == 0);

        // =========DEBUG
        DEBUG(3) << "Found structure ";
        if (!haveName)
            DEBUG(3) << "<anonymous>";
        else
            DEBUG(3) << "\"" << CStruct.getName() << "\"";
		std::cout << "Has typedef ? : " << haveTypedef << std::endl;
        if (haveTypedef) {
            DEBUG(3) << " whose typedef to \"" << CStruct.getTypedef();
            int indirections(CStruct.getTypedefIndirection());
            if (indirections)
                while (indirections--)
                    DEBUG(3) << "*";
            DEBUG(3) << "\"";
        }
        if (haveFields) {
            DEBUG(3) << " containing FIELDS";
            for (Param::vector::const_iterator 
                    iter(CStruct.getFields().begin());
                 iter != CStruct.getFields().end();
                 ++iter)
                DEBUG(3) << ", " << *iter;
        }
        if (isConstRedefinition)
            DEBUG(3) << " which is a duplicated const_ definition";
        DEBUG(3) << "\n";
        // =========DEBUG
        
        // skip
        if (isConstRedefinition)
            continue;

        // Various kind of struct declarations
        bool error(false);
        if (haveFields) error |= createStruct(module, CStruct, dictionnary,
                                              javaTypes);
        if (isTypedefPointer) error |= createTypedef(module, 
                                                     CStruct,
                                                     dictionnary,
                                                     javaTypes);
        if (isDeepPointer) {
            ERR << "Deep pointer typedef are not supported\n";
            error = true;
        }
        if (error)
            return true;
    }
    return true;
}

STRUCT::~Struct()
{
}

bool STRUCT::convertToJava(void)
{
    switch (mStructType)
    {
      case stStructure:
        return convertStruct();

      case stTypedefPtr:
        // Nothing to do to "prepare" the conversion
        return true;

      case stTypedefPtrByRef:
        return true;

      default:
        ERR << "Unknown struct type found???\n";
        return false;
    }
}

bool STRUCT::needWriting(void) const
{
    return true;
}

bool STRUCT::writeJava(ostream& file) const
{
    switch (mStructType)
    {
      case stStructure:
        writeStruct(file);
        break;

      case stTypedefPtr:
        writeTypedefPtr(file);
        break;

      case stTypedefPtrByRef:
        writeTypedefPtrByRef(file);
        break;
    }
    return !file.fail();
}

STRUCT::Struct(const Module& module, 
               const nsC::Struct& CStruct,
               StructType type,
               const TypesDictionnary& dictionnary,
               Type::map& javaTypes)
    : super(module),
      mStructType(type),
      mDictionnary(dictionnary),
      mStruct(&CStruct)
{
    switch (mStructType)
    {
      case stStructure:
        if (CStruct.getTypedef().empty())
            mBaseCName = CStruct.getName();
        else
            mBaseCName = CStruct.getTypedef();
        mBaseJavaName = toJavaName(CStruct.getTypedef(), false, false, 
                                   true);
        mBasePackage = "types.structs";
        mPackageList.addImport("com.sun.jna.Structure");
        break;

      case stTypedefPtr:
        mBaseCName = CStruct.getTypedef();
        mBaseJavaName = toJavaName(CStruct.getTypedef(), false, false,
                                   true);
        mBasePackage = "types.structs.typedef";
        mPackageList.addImport("com.sun.jna.FromNativeContext");
        mPackageList.addImport("com.sun.jna.NativeMapped");
        mPackageList.addImport("com.sun.jna.Pointer");
        break;

      case stTypedefPtrByRef:
        mStructPtr = true;
        mBaseCName = CStruct.getTypedef() + " *";
        mTypedefPtrName = toJavaName(CStruct.getTypedef(), false, false,
                                     true);
        mBaseJavaName = mTypedefPtrName + "ByReference";
        mBasePackage = "types.structs.typedef";
        mPackageList.addImport("com.sun.jna.ptr.ByReference");
        mPackageList.addImport("com.sun.jna.Pointer");
        break;
    }
    addToMap(javaTypes);
}

bool STRUCT::convertStruct(void)
{
    if (mBaseCName.empty())
        return false;

    string fieldBase("    /** %NAME% field */\n"
                     "    public %TYPE% %NAME%;\n");

    const Param::vector& params(mStruct->getFields());
    for (Param::vector::const_iterator iter(params.begin());
         iter != params.end();
         ++iter)
    {
        const Param& param(*iter);
        Type* type(mDictionnary.getType(param.getCType()));
        if (type == NULL) {
            ERR << "Type \"" << param.getCType() <<
                   "\" not found for field \"" <<
                   param.getName() << "\"\n";
            return false;
        }
        mPackageList.addType(type);
        string typeStr(fieldBase);
        stringReplace(typeStr, "NAME", param.getName());
        stringReplace(typeStr, "TYPE", type->getBaseJavaName());
        mStructFields += typeStr;
    }
    return true;
}

void STRUCT::writeStruct(ostream& file) const
{
    string output(
        "/** Structure %BASECNAME% */\n"
        "public class %BASEJAVANAME% extends Structure "
            "implements Structure.ByValue\n"
        "{\n"
        "%FIELDS%"
        "}\n"
        );
    stringReplace(output, "FIELDS", mStructFields);
    prepareString(output);
    file << output;
}

void STRUCT::writeTypedefPtr(ostream& file) const
{
    string output(
        "public class %BASEJAVANAME% implements NativeMapped {\n"
        "    private Pointer mPointer;\n"
        "    public %BASEJAVANAME%() {\n"
        "        mPointer = null;\n"
        "    }\n"
        "    %BASEJAVANAME%(final Pointer realPointer) {\n"
        "        mPointer = realPointer;\n"
        "    }\n"
        "    @Override\n"
        "    public Object fromNative(final Object _nativeValue,\n"
        "            final FromNativeContext _context) {\n"
        "        if (!(_nativeValue instanceof Pointer)) {\n"
        "            return null;\n"
        "        }\n"
        "        return new %BASEJAVANAME%((Pointer) _nativeValue);\n"
        "    }\n"
        "    public Pointer getPointer() {\n"
        "        return mPointer;\n"
        "    }\n"
        "    @Override\n"
        "    public Class nativeType() {\n"
        "        return Pointer.class;\n"
        "    }\n"
        "    @Override\n"
        "    public Object toNative() {\n"
        "        return mPointer;\n"
        "    }\n"
        "    public void setFromNative(long jnaPointer) {\n"
        "        mPointer = Pointer.createConstant(jnaPointer); \n"
        "    }\n"
        "}\n"
        "\n"
        );
    prepareString(output);
    file << output;
}

void STRUCT::writeTypedefPtrByRef(ostream& file) const
{
    string output(
       "public class %BASEJAVANAME% extends ByReference {\n"
       "    public %BASEJAVANAME%() {\n"
       "        this(null);\n"
       "    }\n"
       "    public %BASEJAVANAME%(final %TYPEDEFBASENAME% value) {\n"
       "        super(Pointer.SIZE);\n"
       "        setValue(value);\n"
       "    }\n"
       "    public %TYPEDEFBASENAME% getValue() {\n"
       "        return new %TYPEDEFBASENAME%(getPointer().getPointer(0));\n"
       "    }\n"
       "    public void setValue(final %TYPEDEFBASENAME% value) {\n"
       "        if (value != null)\n"
       "            getPointer().setPointer(0, value.getPointer());\n"
       "        else\n"
       "            getPointer().setPointer(0, Pointer.NULL);\n"
       "    }\n"
       "}\n"
       );
    stringReplace(output, "TYPEDEFBASENAME", mTypedefPtrName);
    prepareString(output);
    file << output;
}

bool STRUCT::createTypedef(const Module& module,
                           const nsC::Struct& CStruct,
                           const TypesDictionnary& dictionnary,
                           Type::map& javaTypes)
{
    new Struct(module, CStruct, stTypedefPtr, dictionnary, javaTypes);
    new Struct(module, CStruct, stTypedefPtrByRef, dictionnary, javaTypes);
    return false;
}

bool STRUCT::createStruct(const Module& module,
                          const nsC::Struct& CStruct,
                          const TypesDictionnary& dictionnary,
                          Type::map& javaTypes)
{
    new Struct(module, CStruct, stStructure, dictionnary, javaTypes);
    return false;
}

#undef STRUCT

