#include "JNI/Types/Way.h"

using namespace std;

Way getWay(string way)
{
    toupper(way);
     if(way=="IN")
        return IN;
    else if(way=="OUT")
         return OUT;
    else
         return UNKNOWN;
}

void toupper(string &s)
{
    for(int i =0;i<s.size();i++)
        s[i] = toupper(s[i]);
}
