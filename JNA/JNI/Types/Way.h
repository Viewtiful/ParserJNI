/*!
 * \file Way.h
 * \brief Prevent unused copy for JNI code generation
 */
#ifndef __JNI_WAY_H
#define __JNI_WAY_H
#include <string>
#include <cctype>
#include <iostream>
using namespace std;

/*!
 * \enum Way
 * \brief give informations of the use of an Parameter
 */
typedef enum
{
    IN, /*!< If the parameter contains only input Data for function*/
    OUT, /*!< If the parameter will contain output Data for function */
    UNKNOWN /*!< We have no information*/
}Way;

/*!
 * \brief compute the right Enum value with a string
 * \param way : the enum walue in string format
 */
Way getWay(string way);
/*!
 * \brief transform an lowercase string to uppercase string
 * \param s a lowercase string
 */
void toupper(string &s);







#endif
