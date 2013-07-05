#ifndef __JNI_FREE_H
#define __JNI_FREE_H

#include "JNI/Types/Function.h"
#include "C/Param.h"
#include "Utils/Utils.h"
#include <fstream>

namespace nsJNI
{
   class Function;
   class TypesDictionnary;
	class Free : public Function
	{
		public : 
			Free(string structName, TypesDictionnary * dictionnary);
			virtual ~Free();
			void create();
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
