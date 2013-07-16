#include "Comments.h"
using namespace nsJNI;
Comments::Comments()
{
    _lexic["@param"] = "@param";
    _lexic["@return"] = "@return";
    _lexic["@ref"] = "@see";
    _lexic["@a"] = "<i>";
    
}

Comments::~Comments()
{

}


void Comments::transformToJavadoc(nsC::Function fct,ofstream &f)
{
    string comments = fct.getComment();
    int index = 1;
    for(int i  = 0; i<comments.size();i++)
    {
        index = comments.find('@',i);
        if(!(index==comments.npos))
        {
            string token = getToken(index,comments);
            string javadocToken = _lexic[token];
            //assert(endofToken-index>0);
            if(javadocToken.size()!=0)
            {   comments.erase(index,token.size());
                comments.insert(index,javadocToken);
            }
            cout << "Token = " << token << endl;
            cout << "Token size = " << token.size() << endl;
        }
        else
            break;
          
    }
    cout << "Comments = " << endl;
    cout << comments << endl;
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
void Comments::transformToJavadoc(nsC::Struct s,ofstream &f)
{

}
void Comments::transformToJavadoc(nsC::Enum e,ofstream &f)
{

}
