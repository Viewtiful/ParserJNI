/** @file
 *
 * Header for JNIParser
 */

#ifndef __JNI_FUNCTION_H
#define __JNI_FUNCTION_H
#include "JNI/TypesDictionnary.h"
#include "C/Function.h"
#include "JNI/Types/Param.h"
#include "JNI/Types/Pointer.h"
#include "JNI/Types/AddressWrapper.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
namespace nsJNI {
    class Function
    {
      public:
        Function(TypesDictionnary *dictionnary);
		virtual ~Function();
        void convertJava(ofstream &f);
        void printParametersJava(ofstream &f);
		void printPrototypeJava(ofstream &f);
		void printParameterJava(ofstream &f);
		
        void convertJNI(ofstream& file);
        void printContentJNI(ofstream &f);
		void printPrototypeJNI(ofstream &f);
		void printParametersJNI(ofstream &f);
		
        void setReturnType(const string& returnType);
        void addArgs(const nsC::Param::vector& args);
		
		void create(const nsC::Function& fct);
      void callNativeMethod(ofstream &f);
		std::string& getReturnType();
		vector<Param*> getArgs();
		string getName();
       protected:
       	string _returnType;
       	string _name;
       	vector<Param*> _args; 
       	TypesDictionnary *_dictionnary;
    };
}

#endif

