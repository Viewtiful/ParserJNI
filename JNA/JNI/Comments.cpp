#include "Comments.h"
using namespace nsJNI;
Comments::Comments()
{
 
    inRetval = false;
    _lexic["@param"] = &Comments::transformParam;
    _lexic["@ref"] = &Comments::transformRef;
    _lexic["@a"] = &Comments::transformA;
    _lexic["@note"] = &Comments::transformNote;
    _lexic["@retval"] = &Comments::transformReturnVal;
    
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
    inRetval = false;
    return comments;
}

string Comments::getToken(int index,string &comments)
{
    int endofToken;
    bool endToken = false;
    for(endofToken = index+1;endofToken<comments.size() && !endToken;endofToken++)
    {
        if(comments[endofToken] == '[')
        {
            comments.insert(endofToken,1,' ');
            endToken = true;
        }
        else if(comments[endofToken] == ' ' || !isAlpha(comments[endofToken]))
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
    inRetval = false;
}

void Comments::transformRef(int index,string &comments)
{
    string paramToken = "@See";
    int tokenSize = paramToken.size();
    comments.erase(index,tokenSize);
    comments.insert(index,"@see");
    inRetval = false;
}

void Comments::transformA(int index, string &comments)
{
    string paramToken = "@a";
    int tokenSize = paramToken.size();
    int i;
    int k;
    locale loc;
    bool letters = false;
    comments.erase(index,tokenSize);
    comments.insert(index,"<i>");
    for(i = index+4;i<comments.size();i++)
    {
        if(!letters && (isAlpha(comments[i]) || comments[i]=='*'))
            letters = true;
        else if(!letters && comments[i]==' ')
            comments.erase(i,1);
        else if(letters && !isAlpha(comments[i]))
            break;
    }
    cout << "isalpha(=) = " << isAlpha('=') << endl;
    comments.insert(i,"</i>");
}

bool Comments::isAlpha(char c)
{
    return ((c>='a' && c<='z') || (c>='A' && c<='Z')); 
}

void Comments::transformNote(int index, string &comments)
{
    string paramToken = "<br /><b><i>Note :</i></b>";
    string handledToken = "@note";
    int tokenSize = paramToken.size();
    comments.erase(index,handledToken.size());
    comments.insert(index,paramToken);
    inRetval = false;
}

void Comments::transformReturnVal(int index, string &comments)
{
    string handledToken = "@retval";
    string header = "<br /><u>Possible return Value</u> : <br /><ul>\n\t*";
    int endOfLine;        
    if(!inRetval)
    {
        comments.erase(index,handledToken.size());
        comments.insert(index,header);
        inRetval = true;
        comments.insert(index+header.size(), "<li>");
        for(endOfLine = index+header.size(); endOfLine < comments.size() ;endOfLine++)
            if(comments[endOfLine]=='\n')
                break;
        comments.insert(endOfLine,"</li>");
    }
    else
    {
        comments.erase(index,handledToken.size());
        comments.insert(index, "<li>");
        for(endOfLine = index+3; endOfLine < comments.size() ;endOfLine++)
            if(comments[endOfLine]=='\n')
                break;
        comments.insert(endOfLine,"</li>");
    }
    
}