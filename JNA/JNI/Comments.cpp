#include "Comments.h"
using namespace nsJNI;
Comments::Comments()
{
    /*_lexic["@param"] = "@param";
    _lexic["@return"] = "@return";
    _lexic["@ref"] = "@see";
    _lexic["@a"] = "<i>";*/
    
    _lexic["@param"] = &Comments::transformParam;
    _lexic["@ref"] = &Comments::transformRef;
    //_lexic["@a"] = &Comments::transformA;
    
}

Comments::~Comments()
{

}

void Comments::call(string& token, int index, string& comments)
{
   if(_lexic.count(token)!=0)
   {
      codeGenerator c = _lexic[token];
      (this->*c)(index,comments);
   }
   
}

string  Comments::transformToJavadoc(nsC::Function fct,ofstream &f)
{
    string comments = fct.getComment();
    int index = 1;
    int increm = 1;
    for(int i  = 0; i<comments.size();i = index + increm)
    {
        index = comments.find('@',i);
        if(index!=comments.npos)
        {
            string token = getToken(index,comments);
           
            cout << "Token = " << token << endl;
            cout << "Token size = " << token.size() << endl;
            increm = token.size() + 1;
            cout << "increm = " << increm << endl;
            call(token,index,comments);
        }
        else
            break;
          
    }
    return comments;
}

string Comments::getToken(int index,string &comments)
{
    int endofToken;
    bool endToken = false;
    for(endofToken = index;endofToken<comments.size() && !endToken;endofToken++)
    {
        if(comments[endofToken] == '[')
        {
            comments.insert(endofToken,1,' ');
            endToken = true;
        }
        else if(comments[endofToken] == ' ')
            endToken = true;
         
    }
    return comments.substr(index,endofToken-index-1);
    
}

void Comments::transformParam(int index,string &comments)
{
    string paramToken = "@param";
    int tokenSize = paramToken.size();
    comments.erase(index,tokenSize);
    comments.insert(index,"@param");
}

void Comments::transformRef(int index,string &comments)
{
    string paramToken = "@See";
    int tokenSize = paramToken.size();
    comments.erase(index,tokenSize);
    comments.insert(index,"@See");
}

void Comments::transformA(int index, string &comments)
{
    string paramToken = "@a";
    int tokenSize = paramToken.size();
    int i;
    comments.erase(index,tokenSize);
    for(i = index + 4;i< comments.size();i++)
    {
        if(isalpha(comments[i])!=0)
            break;
    }
    comments.insert(index,"<i>");
    comments.insert(i,"</i>");
}

