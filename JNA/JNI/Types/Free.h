#ifndef __JNI_FREE_H
#define __JNI_FREE_H

#include "JNI/Types/Function.h"
#include "C/Param.h"
#include "Utils/Utils.h"
#include <fstream>

/** @addtogroup Types
 * @{ */

namespace nsJNI
{
	class Function;
	class TypesDictionnary;
	/*!
	  \class Free
	  \brief generate a Free Function for structure
	  */
	class Free : public Function
	{
		public : 
			/*!
			  \brief constructor with two parameters
			  Create, and initialize a Free Function with the following arguments
			  \param structName : Struct's name which contains this method
			  \param dictionnary : dictionnary of all type
			  */

			Free(string structName, TypesDictionnary * dictionnary);
			virtual ~Free();
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
