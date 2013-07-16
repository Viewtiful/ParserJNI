#include "Comments.h"
using namespace nsJNI;
Comments::Comments()
{
    _lexic["param"] = "param";
    _lexic["retval"] = "return";
}

Comments::~Comments()
{

}


void Comments::transformToJavadoc(nsC::Function fct,ofstream &f)
{
    string comments = fct.getComment();
    bool functionBrief = false;
    string fctBrief;
    for(int i = 0;comments[i]!='\0';i++)
    {
    }
}
void Comments::transformToJavadoc(nsC::Struct s,ofstream &f)
{

}
void Comments::transformToJavadoc(nsC::Enum e,ofstream &f)
{

}

string Comments::format(const string& fctComments)
{
    string comments;
    int k = 0;
    for(int i =0;fctComments.size();i++)
        if(!(fctComments[i]=='/' || fctComments[i]=='*'))
        {
            comments[k] = fctComments[i];
            k++;
        }    
    cout << "Comments : " << fctComments << endl;
    return comments;
}