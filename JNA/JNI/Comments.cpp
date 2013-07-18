#include "Comments.h"
using namespace nsJNI;

Comments::Comments() {

    inRetval = false;
    _lexic["@param"] = &Comments::transformParam;
    _lexic["@ref"] = &Comments::transformRef;
    _lexic["@a"] = &Comments::transformA;
    _lexic["@note"] = &Comments::transformNote;
    _lexic["@retval"] = &Comments::transformReturnVal;

}

Comments::~Comments() {

}

void Comments::call(string& token, int index, string& comments) {
    if (_lexic.count(token) != 0) {
        codeGenerator c = _lexic[token];
        (this->*c)(index, comments);
    }


}

string Comments::transformToJavadoc(nsC::Function fct, ofstream &f) {
    string comments = fct.getComment();
    int tokenBegin = 1;
    int tokenEnd = 1;
    int nextI;
    for (int i = 0; i < comments.size(); i = nextI) {
        tokenBegin = comments.find('@', i);
        if (tokenBegin != comments.npos) {
            string token = getToken(tokenBegin, comments);

            cout << "Token = " << token << endl;
            cout << "Token size = " << token.size() << endl;
            tokenEnd = token.size() + tokenBegin;
            cout << "increm = " << tokenEnd << endl;
            call(token, tokenBegin, comments);
            nextI = tokenEnd + 1;
        } else
            break;

    }
    inRetval = false;
    return comments;
}

string Comments::getToken(int tokenIndex, string &comments) 
{
    int endofToken;
    bool endToken = false;
    int i;
    for (i = tokenIndex + 1; i < comments.size() && !endToken; i++) 
    {
        if (comments[i] == '[') 
        {
            comments.insert(i, 1, ' ');
            endToken = true;
        } 
        else if (comments[i] == ' ' || !isAlpha(comments[i]))
            endToken = true;

    }
    endofToken = i;
    return comments.substr(tokenIndex, endofToken - tokenIndex - 1);

}

void Comments::transformParam(int index, string &comments) 
{
    string handledToken = "@param";
    int handledTokenSize = handledToken.size();
    int endofToken = index + handledTokenSize;
    
    if (comments[endofToken+1] == '[')
    {
        int inOut = bypass(endofToken+1,comments,']');
        assert(inOut!=-1);
    
        int value = bypass(inOut+1,comments,' ');
        int value2 = bypass(inOut+1,comments,'\n');
        cout << "Value = " << value << "value2 = " << value2 << endl;
        value = min(value,value2);
        assert(value!=-1);
        string paramName = comments.substr(inOut,value-inOut);
        cout << "ParamName : " << paramName << "endl" << endl;
        int indexSize = paramName.find("_size",0);
        
//        if(indexSize!=paramName.npos)
//        {
//            cout << "dans le if" << endl;
//            int nextTag = comments.find('@',inOut);
//            if(nextTag!=comments.npos)
//                comments.erase(index,nextTag-1);
//            else
//            {
//                comments.erase(index,comments.size()-2);
//                comments.insert(comments.size(),"*/");
//            }
//        }
        
       
    }

    inRetval = false;
}

void Comments::transformRef(int index, string &comments) {
    string handledToken = "@see";
    int handledTokenSize = handledToken.size();

    string javadocToken = "@see";

    comments.erase(index, handledTokenSize);
    comments.insert(index, javadocToken);
    inRetval = false;
}

void Comments::transformA(int index, string &comments) {
    string handledToken = "@a";
    int handledTokenSize = handledToken.size();
    
    string javadocTokenopen = "<i>";
    int javadocEnd = index + javadocTokenopen.size() + 1;
    
    string javadocTokenclose = "</i>";

    int i;
    bool letters = false;
    
    comments.erase(index, handledTokenSize);
    comments.insert(index, javadocTokenopen);

    for (i = javadocEnd; i < comments.size(); i++) 
    {
        if (!letters && (isAlpha(comments[i]) || comments[i] == '*'))
            letters = true;
        else if (!letters && comments[i] == ' ')
            comments.erase(i, 1);
        else if (letters && !isAlpha(comments[i]))
            break;
    }
    comments.insert(i, javadocTokenclose);
}

bool Comments::isAlpha(char c) 
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

void Comments::transformNote(int index, string &comments) 
{
    string javaDocToken = "<br /><b><i>Note :</i></b>";
    string handledToken = "@note";
    
    comments.erase(index, handledToken.size());
    comments.insert(index, javaDocToken);
    inRetval = false;
}

void Comments::transformReturnVal(int index, string &comments) {
    string handledToken = "@retval";
    string header = "<br /><u>Possible return Value</u> : <br /><ul>\n\t*";
    int endOfLine;
    
    int i;
    comments.erase(index, handledToken.size());
    if (!inRetval) 
    {
        comments.insert(index, header);
        inRetval = true;
        comments.insert(index + header.size(), "<li>");
        endOfLine = bypass(index+header.size(),comments,'\n');
    } 
    else 
    {
        comments.insert(index, "<li>");
        endOfLine = bypass(index+4,comments,'\n');
    }
    
    assert(endOfLine!=-1);
    comments.insert(endOfLine, "</li>");


}

int Comments::bypass(int index,string &comments,char c)
{
    int i;
    for(i = index;i<comments.size();i++)
        if(comments[i]==c && i<comments.size()+1)
            return i+1;
    
    return -1;
}


