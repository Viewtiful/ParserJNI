#ifndef __JNI_SETTER_H
#define __JNI_SETTER_H

#include "C/Param.h"
#include "Utils/Utils.h"
#include "JNI/Types/Param.h"
#include <fstream>
#include <string>

namespace nsJNI
{
	class Setter : public Function
	{
		public : 
			Setter(nsC::Param& param,string structName,TypesDictionnary * dictionnary);
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
