/** @file
 *
 * Header for Parser class
 */

#ifndef __CONVERT_PARSER_H
#define __CONVERT_PARSER_H

#include <vector>
#include <iostream>
#include "Utils/Parameters.h"
#include "C/Function.h"
#include "C/Enum.h"
#include "C/Struct.h"
#include "C/Callback.h"
#include "C/Typedef.h"
#include "C/Consts.h"
#include "flex/tokens.h"

namespace nsConvert
{
    /** Parse a C header file to find functions, typedefs... */
    class Parser
    {
      public:
        /** Create a parser object for a given file. */
        Parser(const std::string& input,
               nsC::Function::vector& functions,
               nsC::Enum::vector& enums,
               nsC::Struct::vector& structs,
               nsC::Callback::vector& callbacks,
               nsC::Typedef::vector& typedefs,
               nsC::Consts& consts);
        virtual ~Parser();

        /** Effectively parse the file.
         *
         * @retval true The file was parsed succesfuly
         * @retval false An error occured while parsing the file
         */
        bool parse(void);

      protected:
        std::string mInputFileName;
        FILE* mInputFile;

        int mBraceDepth;
        TokensList mLastToken;
        std::string mJnaTypedef;

        nsC::Function::vector& mFunctionVector;
        nsC::Enum::vector& mEnumVector;
        nsC::Struct::vector& mStructVector;
        nsC::Callback::vector& mCallbackVector;
        nsC::Typedef::vector& mTypedefs;
        nsC::Consts& mConsts;

        /** Parse a top level token.
         *
         * @retval true Triggered an error
         * @retval false Continue parsing
         */
        bool parseTopLevel(void);

        /** Read a JNA command.
         *
         * @retval true An error occured
         * @retval false No error occured
         */
        bool readJNACommand(void);

        /** Process a toplevel keyword.
         *
         * @retval true An error occured
         * @retval false No error occured
         */
        bool processTopLevelKeyword(void);

        /** Process a toplevel symbol.
         *
         * Currently only support '}' matching an 'extern "C" {'.
         *
         * @retval true An error occured
         * @retval false No error occured
         */
        bool processTopLevelSymbol(void);

        /** Process a toplevel identifier.
         *
         * Currently, only functions are supported.
         *
         * @retval true An error occured
         * @retval false No error occured
         */
        bool processTopLevelIdentifier(void);

        /** Read a "extern" declaration.
         *
         * In header files, this is usualle 'extern "C" {'.
         *
         * @retval true An error occured
         * @retval false No error occured
         */
        bool readExtern(void);

        /** Process a function.
         *
         * The current token must be the first token of the function return
         * type.
         *
         * The next token when the function finish is the first token after
         * the semicolon.
         *
         * @retval true An error occured
         * @retval false No error occured
         */
        bool processFunction(void);

        /** Read a typedef.
         *
         * The next token must be the first token after the "typedef".
         *
         * The next token after the function return is the first token after
         * the final semicolon of whatever the typedef was.
         *
         * @retval true An error occured
         * @retval false No error occured
         */
        bool readTypedef(void);

        /** Read a typedef struct.
         *
         * The next token must be the first token coming after
         * "typedef struct", or eventually "typedef const struct".
         *
         * The next token when the function exit is the first token after
         * the semicolon.
         *
         * @retval true An error occured
         * @retval false No error occured
         */
        bool readTypedefStruct(bool constant = false);

        /** Read a typedef enum.
         *
         * The next token must be the first token coming after
         * "typedef enum".
         *
         * The next token when the function exit is the first token after
         * the semicolon.
         *
         * @retval true An error occured
         * @retval false No error occured
         */
        bool readTypedefEnum(void);

        /** Process a typedef callback.
         *
         * The current token must be the first token of the callback return
         * value.
         * If a 'const' keyword was read right before, the @a constant
         * parameter must be set to @c true to indicate that.
         *
         * The next token when the function return will be the first token
         * after the semicolon.
         *
         * @retval true An error occured
         * @retval false No error occured
         */
        bool processTypedefCallback(bool constant = false);

        /** Read a function parameters list.
         *
         * The next token must be the first token of the parameters list.
         *
         * When the function exit, the next token will be the first token
         * after the closing bracket.
         *
         * @param[out] paramList
         * The vector to fill with the parameters. It will be cleared when
         * entering the function.
         *
         * @retval true An error occured
         * @retval false No error occured.
         */
        bool readParamList(nsC::Param::vector& paramList);

        /** Concatenate a vector of identifier into a type and name string.
         *
         * @param[in] vector
         * A vector of identifier. This can also contain stars ('*')
         *
         * @param[out] type
         * The type string. All identifiers from @a vector except the last
         * one are concatenated into this
         *
         * @param[out] name
         * The name string. This is the last identifier in @a vector
         */
        void createTypeAndName(const std::vector<std::string>& vector, 
                               std::string& type, 
                               std::string& name);

        /** Check if the next token is the given token.
         *
         * This will consume the next token.
         *
         * expect() functions will output an error message when the expected
         * token is not the next token read.
         *
         * @retval true The next token is the given token
         * @retval false The next token isn't the given token
         */
        bool expect(TokensList type, const std::string& text);

        /** Check if the next token is the given token.
         *
         * This will consume the next token.
         *
         * expect() functions will output an error message when the expected
         * token is not the next token read.
         *
         * @retval true The next token is the given token
         * @retval false The next token isn't the given token
         */
        bool expect(TokensList type);

        /** Check if the last token read is the given token.
         *
         * This will NOT consume the next token.
         *
         * @retval true The last token is the given token
         * @retval false The last token isn't the given token
         */
        bool compare(TokensList type, const std::string& text);

        /** Check if the last token read is the given token.
         *
         * This will NOT consume the next token.
         *
         * @retval true The last token is the given token
         * @retval false The last token isn't the given token
         */
        bool compare(TokensList type);

        /** Check if the last token read is the given token.
         *
         * This will NOT consume the next token.
         *
         * @retval true The last token is the given token
         * @retval false The last token isn't the given token
         */
        bool compare(const std::string& text);

        /** Read all token that form a function parameter.
         *
         * This function will start reading tokens until a non-identifier is
         * encountered (with the exception of stars '*', which are also
         * read without breaking the function).
         *
         * The next token must be the first token for the function
         * parameter. If the first token that make the function parameter
         * was already extracted by getToken(), set @a reuseLastToken to
         * @c true to make it reuse it instead of ignoring it.
         *
         * When the function exit, it the current token (in mLastToken) will
         * be the first token coming after the parameter's tokens.
         *
         * @param[out] vector
         * The list of tokens read
         *
         * @param[in] reuseLastToken
         * Set to true to reuse the last token read instead of dropping it
         */
        void readFunctionParam(std::vector<std::string>& vector, 
                               bool reuseLastToken = false);

        /** Read the next token from the file.
         *
         * This function will read the next token, put it in mLastToken, and
         * return it.
         */
        TokensList getToken(void);

        /** Convert a token from @c TokensList into a user readable string
         */
        static const char* tokenToString(TokensList type);

        /** Display an error message with the last token read.
         *
         * This function output an error message and the last token, and
         * return the output stream to display custom informations.
         */
        std::ostream& fail(void);

        std::string mComment;
    };
}

#endif

