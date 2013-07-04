/** @file
 *
 * Header for JNIParser
 */

/*!
	\file Function.h
	\author Baptiste HAUDEGAND & Antoine MOISE
	\version 1.0
!*/

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
/*!
	\namespace nsJNI 
	JNI parser namespace
!*/
namespace nsJNI {
	/*!
		\class Function
		\brief represents a Function
	*/
    class Function
    {
      public:
      /*!
        	\brief constructor 
        	Create, and initialize a Function with the argument
        	\param dictionnary : Dictionnary of type
        */
        Function(TypesDictionnary *dictionnary);
        /*!
      	\brief destructor
      */
		virtual ~Function();
		
		/*!
			\brief convert a function to Java
			\param f: Output Java file
		*/
        void convertJava(ofstream &f);
        
        /*!
        	\brief print all converted Java Parameters
        	\param f: Output Java file
        */
        void printParametersJava(ofstream &f);
        
        /*!
        	\brief print the Java Function prototype
        	\param f: Output Java file
        */
		void printPrototypeJava(ofstream &f);
		
		/*!
        	\brief print a converted Java Parameter
        	\param f: Output Java file
        */
		void printParameterJava(ofstream &f);
		
		/*!
			\brief convert a function to JNI
			\param f: Output Java file
		*/
        void convertJNI(ofstream& file);
        
        /*!
			\brief Print the body of the JNI Function
			\param f: Output JNI file
		*/
        virtual void printContentJNI(ofstream &f);
        
        /*!
        	\brief print the JNI Function prototype
        	\param f: Output JNI file
        */
		virtual void printPrototypeJNI(ofstream &f);
		
		/*!
        	\brief print all converted JNI Parameters
        	\param f: Output JNI file
        */
		void printParametersJNI(ofstream &f);
		
        void setReturnType(const string& returnType);
        
        /*!
        	\brief Add Arguments from the C Function object
        	\param args : the C function argsuments
        */
        void addArgs(const nsC::Param::vector& args);
		
		/*!
			\brief create a new Function
			\param fct : the C function
		*/
		void create(const nsC::Function& fct);
		/*!
			\brief generate the Native Function Call
			\param f: Output JNI File
		*/
      	void callNativeMethod(ofstream &f);
		std::string& getReturnType();
		vector<Param*> getArgs();
		string getName();
       protected:
       	string _returnType; /*!< return Type*/
       	string _name; /*!< Name*/
       	vector<Param*> _args; /*!< Arguments*/
       	TypesDictionnary *_dictionnary; /*!< Dictionnary of type*/
    };
}

#endif

