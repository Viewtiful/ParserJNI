#ifndef COMMENTS_H_INCLUDED
#define COMMENTS_H_INCLUDED
#include <fstream>
#include <map>
#include <string>
#include "C/Function.h"
#include "C/Struct.h"
#include "C/Enum.h"
#include <cassert>
using namespace std;
using namespace nsC;
namespace nsJNI
{
	/*!
		\class Comments
		\brief Transform C++ comments to Java comments 
	*/

	class Comments
	{
		public :
			Comments();
			virtual ~Comments();
			void transformToJavadoc(nsC::Function fct,ofstream &f);
			void transformToJavadoc(nsC::Struct s,ofstream &f);
			void transformToJavadoc(nsC::Enum e,ofstream &f);
                        string format(const string& fctComments);
                        string getToken(int index,string &comments);	
	private :
			map<string,string> _lexic;
	};
}

#endif
