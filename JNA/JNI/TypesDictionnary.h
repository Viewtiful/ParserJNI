/** @file
 *
 * Header for the TypesDictionnary class
 */

#ifndef __JNI_TYPESDICTIONNARY_H
#define __JNI_TYPESDICTIONNARY_H

#include <string>
#include <iostream>
#include <map>
namespace nsJNI
{
    /** A dictionnary of all available types, and their converted names.
     *
     * This class hold a list of all available types (standard and user
     * defined).
     *
     * The good way to use it:
     * - create and populate it with a call to addModules()
     * - call convertToJava() to allow every type to check if they can be
     *   converted to Java
     * - call outputJava() to write out the resulting Java classes
     */
    class TypesDictionnary
    {
      public:
        TypesDictionnary();
        virtual ~TypesDictionnary();

		std::string getJavaType(std::string inputType);
		std::string getCppType(std::string inputType);
		void addCppType(std::string inputType, std::string cppType);
		void addJavaType(std::string inputType, std::string cppType);
      protected:

        /** Add base types (int, size_t, char, those stuff) */
        std::map<std::string,std::string> toJavaType;
		std::map<std::string,std::string> toCppType;

    };
}

#endif

