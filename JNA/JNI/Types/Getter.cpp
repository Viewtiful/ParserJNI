#include "JNI/Types/Getter.h"

using namespace nsJNI;
using namespace nsUtils;
Getter::Getter(nsC::Param& param, string structName, TypesDictionnary *dictionnary) : Function(dictionnary)
{

	_structName = structName;
   	_fieldName = param.getName();
	create(param);
}

Getter::~Getter()
{


}
			
void Getter::create(nsC::Param& param)
{
   //JNI function name.
	_name = "gen_jni_" +_structName + "_" + "get" + "_" +param.getName();
   //Add an argument for the pointer to the structure.
	_args.push_back(new nsJNI::Param("long","mInternal"));

   //If the parameter is const void * or void *, this is an array. Otherwise
   //this is the normal type.
   if(param.getCType()  == "const void *" || param.getCType()  == "void *")
      _returnType = param.getCType() + "Array";
   else
	   _returnType = param.getCType();
}

void Getter::printPrototypeJNI(ofstream &f)
{
	string returnType;
	returnType = _dictionnary->convertJNI(_returnType);

	f << "\t" << "JNIEXPORT " << returnType << " JNICALL " << "JNI_" << _name;
}

void Getter::printContentJNI(ofstream &f)
{
	f << "{\n\n";
	string structure;

   //Write specific code in order to transform the return Value from C to Java.
   if(_dictionnary->convertJNI(_returnType) == "jbyteArray") {
      structure =
            "\t\t%CLASSNAME% *C_ctx = (%CLASSNAME% *)mInternal;\n\n"
            "\t\tjbyteArray result = (*env)->NewByteArray(env, C_ctx->%ATTRIBUTENAME%_size);\n"
            "\t\t(*env)->SetByteArrayRegion(env, result, 0, C_ctx->%ATTRIBUTENAME%_size, C_ctx->%ATTRIBUTENAME%);\n"
            "\t\treturn result;\n"
            ;
   }
   else if( _dictionnary->convertJNI(_returnType) == "jobject") {
      structure =
               "\t\t%CLASSNAME% *C_ctx = (%CLASSNAME% *)mInternal;\n\n"
               "\t\tjobject JNI_result;\n"
               "\t\tjclass retObjCls;\n"
               "\t\tretObjCls = (*env)->FindClass(env, \"ArcanaJNI$%CTYPE%\");\n"
               "\t\tjmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, \"values\", \"()[LArcanaJNI$%CTYPE%;\");\n"
               "\t\tjobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);\n\n"
               "\t\tint arrayLength = (*env)->GetArrayLength(env, valuesArray);\n\n"
               "\t\tint i, val;\n"
               "\t\tjmethodID getVal;\n"
               "\t\tgetVal = (*env)->GetMethodID(env, retObjCls, \"getValue\", \"()I\");\n\n"
               "\t\tfor(i = 0; i < arrayLength; ++i) {\n"
               "\t\t\tJNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);\n"
               "\t\t\tval = (*env)->CallIntMethod(env, JNI_result, getVal);\n"
               "\t\t\tif(val == C_ctx->%ATTRIBUTENAME%) {\n"
               "\t\t\t\tbreak;\n"
               "\t\t\t}\n"
               "\t\t}\n\n"
               "\t\treturn JNI_result;\n"
               ;  
   }
   else {
      structure =
            "\t\t%CLASSNAME% *C_ctx = (%CLASSNAME% *)mInternal;\n"
            "\t\treturn C_ctx->%ATTRIBUTENAME%;\n"
            ;
   }

	stringReplace(structure,"CLASSNAME",_structName);
	stringReplace(structure,"ATTRIBUTENAME",_fieldName);
	stringReplace(structure,"CTYPE",_returnType);

	f << structure;
	f << "\t}\n\n";
}

void Getter::prepareCall(ofstream &f)
{
}

string Getter::call()
{
   //JNI function argument.
	return _name + "(" + _args[0]->getName()+ ");"; 
}
