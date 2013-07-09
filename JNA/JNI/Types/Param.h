/** @file
 *
 * Header for JNIParser
 */
 
/*!
	\file Param.h
	\author Baptiste HAUDEGAND & Antoine MOISE
	\version 1.0
!*/
#ifndef __JNI_PARAM_H
#define __JNI_PARAM_H
#include <iostream>
#include <string>
using namespace std;
/*!
	\namespace nsJNI 
	JNI parser namespace
!*/
namespace nsJNI {

	/*!
		\class Param
		\brief represents a Function Parameter
	*/
    class Param
    {
      public:
      /*!
        	\brief constructor with two parameter
        	Create, and initialize a Param with the following arguments
        	\param type : type of the new Parameter
        	\param name : name of the new Parameter
        */
        Param(const string& type,const string& name);
        /*!
      	\brief destructor
      */
		virtual ~Param();
		std::string& getType();
        std::string& getName();
      protected:
      	string _type; /*!< Type of the parameter*/
      	string _name; /*!< Name of the parameter*/
    };
}

#endif

