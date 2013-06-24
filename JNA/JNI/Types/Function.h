/** @file
 *
 * Header for JNIParser
 */

#ifndef __JNI_FUNCTION_H

#include "JNI/TypesDictionnary.h"
#include "C/Function.h"
#include "JNI/Types/Param.h"
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
        void convert(ofstream &f);
        void setReturnType(const string& returnType);
        void addArgs(const nsC::Param::vector& args);
		void printParameters(ofstream &f);
		void printPrototype(ofstream &f);
		void printParameter(ofstream &f);
		void create(const nsC::Function& fct);
		std::string& getReturnType();
		vector<Param*> getArgs();
       protected:
       	string _returnType;
       	string _name;
       	vector<Param*> _args; 
       	TypesDictionnary *_dictionnary;
    };
}

#endif

