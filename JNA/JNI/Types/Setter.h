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
	class Setter : public Function
	{
		public : 
			Setter(nsC::Param& param,string structName, TypesDictionnary * dictionnary);
			virtual ~Setter();
			void create(nsC::Param& param);
			void printPrototypeJNI(ofstream &f);
			string call();
			string printParameters();
			void printContentJNI(ofstream &f);
			void prepareCall(ofstream &f);
		private:
			string _structName;
			nsJNI::Param *_handledVariable; 
	
	};







}
#endif
