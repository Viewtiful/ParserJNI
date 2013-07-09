#ifndef __JNI_CREATE_H
#define __JNI_CREATE_H

#include "JNI/Types/Function.h"
#include "C/Param.h"
#include "Utils/Utils.h"
#include <fstream>

namespace nsJNI
{
   class Function;
   class TypesDictionnary;
	class Create : public Function
	{
		public : 
		/*!
			\brief constructor with two parameters
			Create, and initialize a Create Function with the following arguments
			\param structName : Struct's name which contains this method
			\param dictionnary : dictionnary of all type
	        */
	
			Create(string structName, TypesDictionnary * dictionnary);
		
			virtual ~Create();
			void create();
			void printPrototypeJNI(ofstream &f);
			string call();
			string printParameters();
			void printContentJNI(ofstream &f);
			void prepareCall(ofstream &f);
		private:
			string _structName; /*!< The structure's name*/
			nsJNI::Param *_handledVariable; /*!< Variable Name*/ 
	
	};







}
#endif
