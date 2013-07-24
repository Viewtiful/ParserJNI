/** @file
 *
 * Header for the TypesDictionnary class
 */

/*!
	\file Typedef.h
	\author Baptiste HAUDEGAND & Antoine MOISE
	\version 1.0
!*/
#ifndef __JNI_TYPEDEF_H
#define __JNI_TYPEDEF_H

#include <string>
#include <iostream>
#include <map>
#include "JNI/Types/Type.h"

/** @addtogroup Types
 * @{ */

using namespace std;
/*!
	\namespace nsJNI 
	JNI parser namespace
!*/
namespace nsJNI
{
	/*!
		\class Typedef
		\brief represents a Typedef
	*/
    class Typedef : public Type
    {
		public:
		/*!
        	\brief constructor with four parameters
        	Create, and initialize a Typedef with the following arguments : 
        	The first three arguments are used to call the super constructor
        	\param javaType : the corresponding java Type
        	\param jniType : the corresponding JNI Type
        	\param VMSIgnature : signature for the java Virtual Machine
        	The last one is specific of that class:
        	\param structName : Struct's name behind the typedef
        */
	        Typedef(string javaType, string cppType, string VMSignature, string structName);
	        
	        /*!
      			\brief destructor
      		*/
	        virtual ~Typedef();
	        std::string outputJava();
        	std::string outputJNI();
        	string getStructName();
        	string getTargetType();
        	bool isNativeType();
        	bool isAddressWrapper();
         bool isBooleanWrapper();
         bool isArray();
        	void prepareCall(ofstream& f, const string& varName);
        	string getJNIParameterName(const string& varName);
        	virtual void getReturnValue(ofstream& f) =0;
        
		protected:
			string _structName; /*!< name of struct to be redefined with this typedef*/
			string _targetType;	 /*!< name of typedef*/
    };
}

#endif

