/** @file
 * Header for Getter
 */
/*!
  \file Getter.h
  \author Baptiste HAUDEGAND & Antoine MOISE
  \version 1.0
  !*/
#ifndef __JNI_GETTER_H
#define __JNI_GETTER_H

#include "JNI/Types/Function.h"
#include "C/Param.h"
#include "Utils/Utils.h"
#include <fstream>

/** @addtogroup Types
 * @{ */

namespace nsJNI
{
	class Getter : public Function
	{
		public : 
			/*!
			  \brief constructor with three parameters
			  Create, and initialize a Getter with the following arguments
			  \param param : parametter that the getter can return
			  \param structName : Struct's name which contains this method
			  \param dictionnary : dictionnary of all type
			  */
			Getter(nsC::Param& param,string structName, TypesDictionnary * dictionnary, bool specialCase);
			Getter(string name, string structName, TypesDictionnary *dictionnary, bool specialCase);
			virtual ~Getter();
			void create(nsC::Param& param);
			void printPrototypeJNI(ofstream &f);
			string call();
			string printParameters();
			void printContentJNI(ofstream &f);
         string printContentJNIArray();
         string printContentJNIObject();
		private:
			string _structName;/*!< The structure's name*/
			string _fieldName; /*!< field name*/
			nsJNI::Param *_handledVariable; /*!< Variable Name*/
			bool _specialCase;  /*!< if it's getter for struct size*/

	};







}
#endif
