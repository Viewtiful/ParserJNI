/** @file
 *
 * Header for Types
 */

/*!
	\file Struct.h
	\author Baptiste HAUDEGAND & Antoine MOISE
	\version 1.0
!*/
#ifndef __JNI_STRUCT_H
#define __JNI_STRUCT_H
#include <string>
#include "C/Struct.h"
#include "JNI/Types/Type.h"
#include "JNI/TypesDictionnary.h"
#include "JNI/Types/Getter.h"
#include "JNI/Types/Setter.h"
#include <vector>
/*!
	\namespace nsJNI 
	JNI parser namespace
!*/
namespace nsJNI {

	 class TypesDictionnary;
	 /*!
		\class Struct
		\brief represents a Struct
	*/
    class Struct : public Type 
    {
      public:
      /*!
      	\brief destructor
      */
        virtual ~Struct();
		Struct(ofstream &f, ofstream& f2, const string& vmSignature,const nsC::Struct& cStruct,TypesDictionnary *dictionnary);
		std::string outputJava();
     	void addStructToJava(ofstream &f);
     	void addStructFunctionToJNI(ofstream &f);
        std::string outputJNI();
        bool isNativeType();
        bool isAddressWrapper();
        bool isBooleanWrapper();
        bool isArray();
        void prepareCall(ofstream& f,string& varName);
        string getJNIParameterName(string& varName);
        string generateGetter(bool java, const string& fieldType,const string& fieldName);
        string generateSetter(bool java, const string& fieldType,const string& fieldName);
        string generateConstructor();
        string generateFinalize();
        string generateFreeFunction(bool java);
        string generateWrite();
        string generateRead();
        string generateCreateFunction(bool java);
        void getReturnValue(ofstream& f);
      protected:
        nsC::Struct _cStruct;
        TypesDictionnary* _dictionnary;
      	vector<Getter*> _getters;
      	vector<Setter*> _setters;
    };
}

#endif

