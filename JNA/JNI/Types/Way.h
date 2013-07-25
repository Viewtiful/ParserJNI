#ifndef __JNI_WAY_H
#define __JNI_WAY_H
#include <string>
#include <cctype>
#include <iostream>
using namespace std;
typedef enum
{
    IN,
    OUT,
    UNKNOWN
}Way;

Way getWay(string way);

void toupper(string &s);







#endif