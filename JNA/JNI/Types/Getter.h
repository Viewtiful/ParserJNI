#ifndef __JNI_GETTER_H
#define __JNI_GETTER_H

#include "JNI/Types/Function.h"
#include "C/Param.h"
#include "Utils/Utils.h"
#include <fstream>
namespace nsJNI
{
	class Getter : public Function
	{
		public : 
			Getter(nsC::Param& param,string structName, TypesDictionnary * dictionnary);
			virtual ~Getter();
			void create(nsC::Param& param);
			void printPrototypeJNI(ofstream &f);
			string call();
			string printParameters();
			void printContentJNI(ofstream &f);
			void prepareCall(ofstream &f);
		private:
			string _structName;
         string _fieldName;
			nsJNI::Param *_handledVariable; 
	
	};







}
#endif
