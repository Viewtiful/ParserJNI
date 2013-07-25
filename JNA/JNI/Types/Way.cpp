#include "JNI/Types/Way.h"

using namespace std;
Way getWay(string way)
{
    toupper(way);
    cout << "WaySIze :" << way.size() << endl;
    if(way=="IN")
    {
        cout << "IN" << endl;
        return IN;
    }
    else if(way=="OUT")
    {
        cout << "OUT" << endl;
        return OUT;
    }
    else
    {
        cout << "UNKNOWN" << endl;
        return UNKNOWN;
    }
}

void toupper(string &s)
{
    for(int i =0;i<s.size();i++)
        s[i] = toupper(s[i]);
}