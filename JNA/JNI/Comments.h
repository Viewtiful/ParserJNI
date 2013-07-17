#ifndef COMMENTS_H_INCLUDED
#define COMMENTS_H_INCLUDED
#include <fstream>
#include <map>
#include <string>
#include "C/Function.h"
#include "C/Struct.h"
#include "C/Enum.h"
#include <cassert>
#include <vector>
using namespace std;
using namespace nsC;
namespace nsJNI
{
	/*!
		\class Comments
		\brief Transform Doxygen comments to Javadoc comments 
	*/
    class Comments;
        typedef void (Comments::*codeGenerator)(int,string &);
        class Comments
        {
		public :
			Comments();
			virtual ~Comments();
                        /*!
                         * \brief Transform  doxygen Comments to Javadoc
                         * 
                         * 
                         * !*/
			string transformToJavadoc(nsC::Function fct,ofstream &f);
                        /*!
                         * \brief parse and compute the @ token
                         * \param index : the beginning search index
                         * \param comments : whole comments
                         * \return the token
                        * 
                        !*/
			string getToken(int index,string &comments);
                        
                        /*!
                         * \brief handle transformation of an Doxygen @param to Javadoc @param
                         * \param index : beginning index of the @param in the comments
                         * \param comments : the whole comments
                         */
                        void transformParam(int index,string &comments);
                        
                        /*!
                         * \brief call the function which handle this token's translation
                         * \param token : token which had to be translated
                         * \param index : position of the token in the comments
                         * \param comments : the whole comments
                        */
                        void call(string& token, int index, string& comments);
                        
                        /*!
                         * \brief handle transformation of an Doxygen @ref to Javadoc @see
                         * \param index : beginning index of the @ref in the comments
                         * \param comments : the whole comments
                         */
                        void transformRef(int index,string &comments);
                        
                        /*!
                         * \brief handle transformation of an Doxygen @a, an @a is transformed to an <i> </i>
                         * 
                         * \param index : beginning index of the @a in the comments
                         * \param comments : the whole comments
                         */
                        void transformA(int index, string &comments);


	private :
            map<string,codeGenerator> _lexic; /*!< contains handle function*/
	};
        

}

#endif
