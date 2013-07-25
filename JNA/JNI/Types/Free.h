/** @file
 * Header for Free
 * \brief Handle free function for structure type.
 */
/*!
  \file Free.h
  \author Baptiste HAUDEGAND & Antoine MOISE
  \version 1.0
  !*/
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
			  create, and initialize a Free function with the following arguments
			  \param structName : Struct's name which contains this method
			  \param dictionnary : dictionnary of all type
			  */

			Free(string structName, TypesDictionnary * dictionnary);
			virtual ~Free();
			void printPrototypeJNI(ofstream &f);
         /*!
            \brief Return the name and the param of the function free.
         */
			string call();
			void printContentJNI(ofstream &f);
		private:
			string _structName; /*!< The structure's name*/
			nsJNI::Param *_handledVariable; /*!< Variable Name*/ 
	};
}
#endif
