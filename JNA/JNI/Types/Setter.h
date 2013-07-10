#ifndef __JNI_SETTER_H
#define __JNI_SETTER_H

#include "JNI/Types/Function.h"
#include "C/Param.h"
#include "Utils/Utils.h"
#include <fstream>

namespace nsJNI
{
   class Function;
   class TypesDictionnary;
	/*!
		\class Setter
		\brief represents a Setter
	*/
	class Setter : public Function
	{
		public : 
		/*!
			\brief constructor with three parameters
			Create, and initialize a Setter with the following arguments
			\param param : parametter that the getter can modify
			\param structName : Struct's name which contains this method
			\param dictionnary : dictionnary of all type
	        */
			Setter(nsC::Param& param,string structName, TypesDictionnary * dictionnary);
			virtual ~Setter();
			void create(nsC::Param& param);
			void printPrototypeJNI(ofstream &f);
			string call();
			string printParameters();
			void printContentJNI(ofstream &f);
			void prepareCall(ofstream &f);
		private:
			string _structName;/*!< The structure's name*/
			nsJNI::Param *_handledVariable; /*!< Variable Name*/
	
	};







}
#endif
