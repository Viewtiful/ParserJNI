#ifndef COMMENTS_H_INCLUDED
#define COMMENTS_H_INCLUDED
#include <fstream>
#include <map>
#include <string>
#include "JNI/Types/Function.h"
#include "JNI/Types/Param.h"
#include <cassert>
#include <vector>
#include <locale>
#include <cstdlib>
using namespace std;
namespace nsJNI {
    /*!
            \class Comments
            \brief Transform Doxygen comments to Javadoc comments 
     */
    class Comments;
    typedef void (Comments::*codeGenerator)(int, string &);

    class Comments {
    public:
        Comments();
        virtual ~Comments();
        /*!
         * \brief Transform  doxygen Comments to Javadoc
         */ 
        string transformToJavadoc(string &comments,nsJNI::Function *fct);
        /*!
         * \brief parse and compute the \@ token
         * \param index : the beginning search index
         * \param comments : whole comments
         * \return the token
         * 
        !*/
        string getToken(int index, string &comments);

        /*!
         * \brief handle transformation of an Doxygen \@param to Javadoc \@param
         * \param index : beginning index of the \@param in the comments
         * \param comments : the whole comments
         */
        void transformParam(int index, string &comments);

        /*!
         * \brief call the function which handle this token's translation
         * \param token : token which had to be translated
         * \param index : position of the token in the comments
         * \param comments : the whole comments
         */
        void call(string& token, int index, string& comments);

        /*!
         * \brief handle transformation of an Doxygen \@ref to Javadoc \@see
         * \param index : beginning index of the \@ref in the comments
         * \param comments : the whole comments
         */
        void transformRef(int index, string &comments);

        /*!
         * \brief handle transformation of an Doxygen \@a, an \@a is transformed to an \<i\> \</i\>
         * 
         * \param index : beginning index of the \@a in the comments
         * \param comments : the whole comments
         */
        void transformA(int index, string &comments);

        /*!
         * \brief check if a character is an letter
         * \return true if it is a letter, false else
         */
        bool isAlpha(char c);

        /*!
         * \brief handle transformation of an Doxygen \@note, an \@note is transformed to an \<b\>\<i\>
         * 
         * \param index : beginning index of the \@a in the comments
         * \param comments : the whole comments
         */
        void transformNote(int index, string &comments);

        /*!
         * \brief handle transformation of an Doxygen \@retval, an \@retval is transformed to an \<b\>Possible return Value
         * 
         * \param index : beginning index of the \@a in the comments
         * \param comments : the whole comments
         */
        void transformReturnVal(int index, string &comments);

        /*!
         * \brief skip characters until one specfic character occured
         * \param index : beginning comments index 
         * \param comments : the whole comments
         * \param c : stop character
         * \return index where the stop Character is found
         * */
        int skipLine(int index, string &comments, char c);
        
        /*!
         * \brief search the next blockTag such as \@Note
         * \param index : beginning comments index
         * \param comments : the whole comments
         */
        int searchNextBlockTag(int index,string &commments);
        
        /*!
         * \brief get the parameter name from whole comments if an \@param is found
         * \param index : beginning comments index
         * \param comments : the whole comments
         * \return the parameter name
         *          */
        string getParameterName(int index,string &comments);
        
        /*!
         * \brief define if this parameter is an size_t *
         * \param paramName : the paramater name
         * \return true if it is a size_t*, false else
         */
        bool paramisSize(string paramName);
        
        /*!
         * \brief set the Way for an Param
         * \param way : the way in string format
         * \param paramName : parameter name
         */
        void setWay(string way,string paramName);

    private:
        map<string, codeGenerator> _lexic; /*!< contains handle function*/
        bool inRetval; /*!< translating an retval*/
        bool _deleteUnusedParam; /*!< flag is true if an \@param was deleted*/
        vector<nsJNI::Param*> _fctParameters;/*!< the fonction's parameters*/
    };


}

#endif
