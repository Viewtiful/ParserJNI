#include "Comments.h"
using namespace nsJNI;

Comments::Comments()
{

    //Adding all parsing function
    _lexic["@param"] = &Comments::transformParam;
    _lexic["@ref"] = &Comments::transformRef;
    _lexic["@a"] = &Comments::transformA;
    _lexic["@note"] = &Comments::transformNote;
    _lexic["@retval"] = &Comments::transformReturnVal;

}

Comments::~Comments()
{
    _lexic.clear();
}

void Comments::call(string& token, int index, string& comments)
{
    //test if this token is handled
    if (_lexic.count(token) != 0)
    {
        codeGenerator c = _lexic[token];
        (this->*c)(index, comments);
    }


}

string Comments::transformToJavadoc(nsC::Function fct, ofstream &f)
{
    string comments = fct.getComment();
    int tokenBegin = 1;
    int tokenEnd = 1;
    int nextI;
    for (int i = 0; i < comments.size(); i = nextI)
    {
        tokenBegin = comments.find('@', i);
        //If there is an Tag
        if (tokenBegin != comments.npos)
        {
            string token = getToken(tokenBegin, comments);
            if(token!="@see" && token!="@a" && token!="@retval")
                inRetval = false;
            cout << "Token = " << token << endl;
            cout << "Token size = " << token.size() << endl;
            tokenEnd = token.size() + tokenBegin;
            cout << "increm = " << tokenEnd << endl;
            call(token, tokenBegin, comments);
            nextI = tokenEnd + 1;
        }
        else // No more tag in comments
            break;

    }
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
    //Return the token value
    return comments.substr(tokenIndex, endofToken - tokenIndex - 1);

}

void Comments::transformParam(int index, string &comments)
{
    string handledToken = "@param";
    int handledTokenSize = handledToken.size();
    int endofToken = index + handledTokenSize;

    //If we find a tag like this : @param[in] or @param[out]
    if (comments[endofToken + 1] == '[')
    {
        //Skip until a ']' is found
        int inOut = skipLine(endofToken + 1, comments, ']');
        assert(inOut != -1);

        //skip until a space found, to get the parameter name
        int value = skipLine(inOut + 1, comments, ' ');
        assert(value != -1);
        
        //Get the paramName by using substr
        string paramName = comments.substr(inOut, value - inOut);
        int indexSize = paramName.find("_size", 0);

        //If the param Name contain _size, we have to delete this comments
        if (indexSize != paramName.npos)
        {
            int nextTag = comments.find('@', inOut);
            //Jump to the next Tag or delete the remaining comments
            if (nextTag != comments.npos)
                comments.erase(index, nextTag - index - 1);
            else
            {
                comments.erase(index, comments.size() - index - 2);
                comments.insert(comments.size(), "*/");
            }
        }


    }
   
}

void Comments::transformRef(int index, string &comments)
{
    string handledToken = "@see";
    int handledTokenSize = handledToken.size();

    string javadocToken = "@see";

    comments.erase(index, handledTokenSize);
    comments.insert(index, javadocToken);
}

void Comments::transformA(int index, string &comments)
{
    string handledToken = "@a";
    int handledTokenSize = handledToken.size();

    string javadocTokenopen = "<i>";
    int javadocEnd = index + javadocTokenopen.size() + 1;

    string javadocTokenclose = "</i>";

    int i;
    bool letters = false;

    comments.erase(index, handledTokenSize);
    comments.insert(index, javadocTokenopen);

    // Search a space, in order to put the </i>
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
}

void Comments::transformReturnVal(int index, string &comments)
{
    string handledToken = "@retval";
    string header = "<br /><u>Possible return Value</u> : <br /><ul>\n\t*";
    int endOfLine;
    int offset;
    comments.erase(index, handledToken.size());
    if (!inRetval)
    {
        comments.insert(index, header);
        inRetval = true;
        offset = header.size();
    }
    else
        offset = 0;
    
    comments.insert(index+offset, "<li>");
    endOfLine = skipLine(index + 4, comments, '\n');
        
    assert(endOfLine != -1);
    comments.insert(endOfLine-1, "</li>");


}

int Comments::skipLine(int index, string &comments, char c)
{
    for (int i = index; i < comments.size(); i++)
        if (comments[i] == c && i < comments.size() + 1)
            return i + 1;

    return -1;
}


