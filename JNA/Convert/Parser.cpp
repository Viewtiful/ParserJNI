/** @file
 *
 * Body for the Parser class
 */

#include <errno.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "flex/include_flex.h"
#include "Utils/Output.h"
#include "Convert/Parser.h"

#define PARSER nsConvert::Parser

using std::string;
using std::ostream;
using std::vector;
using nsC::Function;
using nsC::Enum;
using nsC::Struct;
using nsC::Callback;
using nsC::Typedef;
using nsC::Consts;
using nsC::Param;

PARSER::Parser(const string& input,
               Function::vector& functions,
               Enum::vector& enums,
               Struct::vector& structs,
               Callback::vector& callbacks,
               Typedef::vector& typedefs,
               Consts& consts)
    : mInputFileName(input),
      mBraceDepth(0),
      mFunctionVector(functions),
      mEnumVector(enums),
      mStructVector(structs),
      mCallbackVector(callbacks),
      mTypedefs(typedefs),
      mConsts(consts)
{
    DEBUG(2) << "Creating parser for \"" << input << "\"\n";
    if (!(mInputFile = fopen(input.c_str(), "r"))) {
        ERR << "Can't open input file \"" << input << "\" because:\n"
               "[" << strerror(errno) << "]\n";
    }
}

PARSER::~Parser()
{
    if (mInputFile)
        fclose(mInputFile);
}

bool PARSER::parse(void)
{
    if (!mInputFile)
        return false;

    DEBUG(2) << "Parsing \"" << mInputFileName << "\"...\n";

    if (fseek(mInputFile, 0, SEEK_SET))
        ERR << "Can't set file position for \"" << mInputFileName << 
               "\" because:\n[" << strerror(errno) << "]\n";

    yyin = mInputFile;
	//The lexer doesn't initialize yylineno, so it needs to be set to 1 when starting readin a file
    yylineno = 1;
    bool error = false;
	//go through all the tokens of the input file we are currently reading
    while (!error && getToken() != FLEX_EOF)
        error |= parseTopLevel();

	//We finished the lexing, releasing the memory
    yylex_destroy();

    if (mBraceDepth != 0) {
        ERR << "Unmatched {}!\n";
        error = true;
    }

    DEBUG(2) << "Functions:\n";
    for (size_t i = 0; i < mFunctionVector.size(); ++i)
        DEBUG(2) << mFunctionVector[i] << '\n';
    DEBUG(2) << "Enums:\n";
    for (size_t i = 0; i < mEnumVector.size(); ++i)
        DEBUG(2) << mEnumVector[i] << '\n';
    DEBUG(2) << "Structs:\n";
    for (size_t i = 0; i < mStructVector.size(); ++i)
        DEBUG(2) << mStructVector[i] << '\n';
    DEBUG(2) << "Callbacks:\n";
    for (size_t i = 0; i < mCallbackVector.size(); ++i)
        DEBUG(2) << mCallbackVector[i] << '\n';
    DEBUG(2) << "Consts:\n";
    DEBUG(2) << mConsts << '\n';

    return !error;
}

bool PARSER::parseTopLevel(void)
{
    switch (mLastToken) {
      case FLEX_EOF:
        return false;
        
      case TOK_JNA_COMMAND:
        return readJNACommand();

      case TOK_KEYWORD:
        return processTopLevelKeyword();

      case TOK_STRING:
        fail() << "got a string at top-level\n";
        return true;

      case TOK_SYMBOL:
        return processTopLevelSymbol();

      case TOK_IDENTIFIER:
        return processTopLevelIdentifier();

      case TOK_OTHER:
      default:
        fail() << "unknown token\n";
        return true;
    }
}

bool PARSER::readJNACommand(void)
{
    if (!expect(TOK_IDENTIFIER)) return true;
    if (compare("CONST")) {
        string type;
        string name;
        string value;
        if (!expect(TOK_IDENTIFIER)) return true;
        type = yytext;
        if (compare("int")) {
            if (!expect(TOK_IDENTIFIER)) return true;
            name = yytext;
            if (!expect(TOK_NUMBER)) return true;
            value = yytext;
        }
        else
        {
            fail() << "JNA CONST command with unsupported type\n";
            return true;
        }
        mConsts.addValue(type, name, value);
    }
    else if (compare("TYPEDEF")) {
        if (!expect(TOK_STRING)) return true;
        mJnaTypedef = yytext;
    }
    else {
        fail() << "JNA command invalid\n";
        return true;
    }
    return false;
}

bool PARSER::processTopLevelKeyword(void)
{
    // TODO complete this
    if (compare("extern")) {
        return readExtern();
    }
    else if (compare("typedef")) {
        return readTypedef();
    }
    else if (compare("const")) {
        return processFunction();
    }
    fail() << "unhandled keyword\n";
    return true;
}

bool PARSER::processTopLevelSymbol(void)
{
    // TODO complete this
    if (compare("}")) {
        if (mBraceDepth-- > 0)
            return false;
        else {
            fail() << "Unmatched '}'\n";
            return true;
        }
    }
    fail() << "unhandled symbol\n";
    return true;
}

bool PARSER::processTopLevelIdentifier(void)
{
    // TODO complete that, currently only accept functions
    return processFunction();
}

bool PARSER::readExtern(void)
{
    // Currently only handle 'extern "C" {'
    if (!expect(TOK_STRING, "C")) {
		return true;
	}
    if (!expect(TOK_SYMBOL, "{")) return true;
    ++mBraceDepth;
    return false;
}

bool PARSER::processFunction(void)
{
    Function readFunction;
    vector<string> funcDef;
    readFunctionParam(funcDef, true);
    if (funcDef.size() < 2) {
        fail() << "incomplete function definition\n";
        return true;
    }
    string funcType;
    string funcName;
    createTypeAndName(funcDef, funcType, funcName);
    readFunction.setReturnType(funcType);
    readFunction.setName(funcName);
    if (!compare(TOK_SYMBOL, "(")) {
        fail() << "function expected '('\n";
        return true;
    }
    if (readParamList(readFunction.getParamList()))
        return true;

    if (!expect(TOK_SYMBOL, ";")) return true;
    readFunction.setComment(mComment);
    mFunctionVector.push_back(readFunction);

    return false;
}

bool PARSER::readTypedef(void)
{
    getToken();
    if (compare(TOK_KEYWORD)) {
        if (compare("enum"))
            return readTypedefEnum();

        if (compare("struct"))
            return readTypedefStruct();

        if (compare("const")) {
            getToken();
            if (compare(TOK_KEYWORD, "struct"))
                return readTypedefStruct(true);
            else
                return processTypedefCallback(true);
        }
    }
    else if (compare(TOK_IDENTIFIER)) {
        return processTypedefCallback();
    }
    while (getToken() != FLEX_EOF && !compare(TOK_SYMBOL, ";"));
    DEBUG(2) << "Skipping unhandled typedef\n";
    return false;
    /*
    fail() << "unhandled typedef variant\n";
    return true;
    */
}

bool PARSER::readTypedefStruct(bool constant)
{
    Struct currentStruct;

    getToken();
    if (compare(TOK_IDENTIFIER)) {
        string name(constant ? "const struct " : "struct ");
        name += yytext;
        currentStruct.setName(name);
        getToken();
    }
    if (compare(TOK_SYMBOL, "{")) {
        vector<string> IDs;
        bool keepGoing(true);
        do
        {
            readFunctionParam(IDs);

            if (IDs.empty()) {
                keepGoing = false;
            }
            else
            {
                if (!compare(TOK_SYMBOL, ";")) {
                    fail() << "typedef struct expected ';'\n";
                    return true;
                }

                string paramType;
                for (size_t i(0); i < IDs.size() - 1; ++i) {
                    if (i != 0)
                        paramType += ' ';
                    paramType += IDs[i];
                }
                string paramName = IDs[IDs.size() - 1];
                currentStruct.addField(paramType, paramName);
            }
        } while (keepGoing);
        if (!compare(TOK_SYMBOL, "}")) {
            fail() << "typedef struct expected '}'\n";
            return true;
        }
        getToken();
    }

    while (compare(TOK_SYMBOL, "*")) {
        currentStruct.addTypedefIndirection();
        getToken();
    }
    if (compare(TOK_IDENTIFIER)) {
        currentStruct.setTypedef(yytext);
        getToken();
    }
    if (!compare(TOK_SYMBOL, ";")) {
        fail() << "typedef struct expected ';'\n";
        return true;
    }
    mStructVector.push_back(currentStruct);
    return false;
}

bool PARSER::readTypedefEnum()
{
    Enum currentEnum;
    getToken();
    if (compare(TOK_IDENTIFIER)) {
        string name("enum ");
        name += yytext;
        currentEnum.setName(name);
        getToken();
    }
    if (!compare(TOK_SYMBOL, "{")) {
        fail() << "typedef enum expected '{'\n";
        return true;
    }
    bool keepGoing(true);
    do
    {
        getToken();
        if (compare(TOK_SYMBOL, "}")) {
            keepGoing = false;
            break;
        }
        if (!compare(TOK_IDENTIFIER)) {
            fail() << "typedef enum expected an identifier\n";
            return true;
        }
        string name(yytext);
        string refValue;
        bool useRefValue(false);
        int value = 0;
        bool useValue(false);
        if (!expect(TOK_SYMBOL)) return true;
        if (compare("=")) {
            getToken();
            if (compare(TOK_IDENTIFIER)) {
                refValue = yytext;
                useRefValue = true;
            }
            else if (compare(TOK_NUMBER)) {
                value = atoi(yytext);
                useValue = true;
            }
            else {
                fail() << "typedef enum expected a value\n";
                return true;
            }
            if (!expect(TOK_SYMBOL)) return true;
        }

        if (useRefValue) {
            if (!currentEnum.addValue(name, refValue)) {
                fail() << "typedef enum got a lost reference\n";
                return true;
            }
        }
        else if (useValue)
            currentEnum.addValue(name, value);
        else
            currentEnum.addValue(name);

        if (compare("}"))
            keepGoing = false;
        else if (!compare(",")) {
            fail() << "typedef enum expected ',' or '}'\n";
            return true;
        }
    } while (keepGoing);

    getToken();
    if (compare(TOK_IDENTIFIER)) {
        currentEnum.setTypedef(yytext);
        getToken();
    }
    if (!compare(TOK_SYMBOL, ";")) {
        fail() << "typedef enum expected ';'\n";
        return true;
    }
    mEnumVector.push_back(currentEnum);

    return false;
}

bool PARSER::processTypedefCallback(bool constant)
{
    vector<string> retValue;
    readFunctionParam(retValue, true);

    if (!compare(TOK_SYMBOL, "(")) {
        DEBUG(2) << "Not a callback! must be a regular typedef\n";
        if (!compare(TOK_SYMBOL, ";")) {
            fail() << "callback expected '('\n";
            return true;
        }
        else
        {
            string last(retValue[retValue.size() - 1]);
            if (mJnaTypedef.empty()) {
                // FIXME should be able to handle this using the C typedef
                // itself
                fail() << "Typedef \"" << last << "\" isn't "
                          "associated with a Java Type; expect break!\n";
                return true;
            }
            mTypedefs.push_back(Typedef(last, mJnaTypedef));
            return false;
        }
    }
    string returnType(constant ? "const " : "");

    vector<string>::const_iterator retValue_iter(retValue.begin());
    returnType += *retValue_iter;
    for (++retValue_iter; retValue_iter != retValue.end(); ++retValue_iter)
        returnType += ' ' + *retValue_iter;
    Callback currentCallback;
    currentCallback.setReturnType(returnType);

    if (!expect(TOK_SYMBOL, "*")) return true;
    if (!expect(TOK_IDENTIFIER)) return true;
    currentCallback.setName(yytext);
    if (!expect(TOK_SYMBOL, ")")) return true;
    if (!expect(TOK_SYMBOL, "(")) return true;

    if (readParamList(currentCallback.getParamList()))
        return true;

    if (!expect(TOK_SYMBOL, ";")) return true;
    mCallbackVector.push_back(currentCallback);
    return false;
}

bool PARSER::readParamList(Param::vector& paramList)
{
    bool first(true);
    vector<string> IDs;
    do
    {
        readFunctionParam(IDs);
        // Special first void case
        if (first) {
            if (IDs.size() == 1 && IDs[0] == "void")
                break;
            if (IDs.size() == 0)
                break;
            first = false;
        }
        // Special variadic functions
        if (compare(TOK_SYMBOL, "...")) {
            DEBUG(3) << "Adding variadic parameter\n";
            paramList.push_back(Param("variadic", "..."));
            getToken();
            break;
        }
        if (IDs.size() < 2) {
            fail() << "paramlist doesn't support unnamed parameters\n";
            return true;
        }
        // Add param
        string paramType;
        for (size_t i(0); i < IDs.size() - 1; ++i) {
            if (i != 0)
                paramType += ' ';
            paramType += IDs[i];
        }
        string paramName = IDs[IDs.size() - 1];
        DEBUG(3) << "Adding parameter:[" << paramName << ':' 
              << paramType << "]\n";
        paramList.push_back(Param(paramType, paramName));
        
        if (compare(TOK_SYMBOL, ")"))
            break;
        if (!compare(TOK_SYMBOL, ",")) {
            fail() << "paramlist expected ',' or ')'\n";
            return true;
        }
    } while (mLastToken != FLEX_EOF);

    if (!compare(TOK_SYMBOL, ")")) {
        fail() << "paramlist expected ')'\n";
        return true;
    }
    return false;
}

void PARSER::createTypeAndName(const vector<string>& vector, string& type, 
                               string& name)
{
    size_t i(0);
    for (; i < vector.size() - 1; ++i)
        if (i != 0)
            type += ' ' + vector[i];
        else
            type += vector[i];

    name = vector[i];
}

bool PARSER::expect(TokensList type, const string& text)
{
    getToken();
    if (compare(type) && compare(text))
        return true;
    else 
    {
        fail() << "expecting " << tokenToString(type) << "\"" << text 
            << "\"\n";
        return false;
    }
}

bool PARSER::expect(TokensList type)
{
    getToken();
    if (compare(type))
        return true;
    else
    {
        fail() << "expecting " << tokenToString(type) << '\n';
        return false;
    }
}

bool PARSER::compare(TokensList type, const string& text)
{
    return compare(type) && compare(text);
}

bool PARSER::compare(TokensList type)
{
    return mLastToken == type;
}

bool PARSER::compare(const string& text)
{
    return strcmp(yytext, text.c_str()) == 0;
}

void PARSER::readFunctionParam(vector<string>& vector, 
                               bool reuseLastToken)
{
    vector.clear();
    bool keepGoing(true);
    do
    {
        if (reuseLastToken)
            reuseLastToken = false;
        else
            getToken();

        switch (mLastToken)
        {
          case TOK_KEYWORD:
            vector.push_back(yytext);
            break;

          case TOK_IDENTIFIER:
            vector.push_back(yytext);
            break;

          case TOK_SYMBOL:
            if (compare("*"))
                vector.push_back(yytext);
            else
                keepGoing = false;
            break;

          default:
            keepGoing = false;
        }
    } while (keepGoing);
}

TokensList PARSER::getToken(void)
{
	//get the last token read by flex
    mLastToken = (TokensList) yylex();
	//it is a comment ? get it and get the next token
    if (mLastToken == TOK_COMMENT) {
        mComment = string(yytext);
        return getToken();
    }
	//it is a string ? get it
    if (mLastToken == TOK_STRING) {
        yytext += 1;
        yytext[strlen(yytext) - 1] = '\0';
    }
	//return the token we just read
    return mLastToken;
}

const char* PARSER::tokenToString(TokensList type)
{
    switch (type)
    {
      case FLEX_EOF: return "[End Of File]";
      case TOK_JNA_COMMAND: return "[JNA Command]";
      case TOK_KEYWORD: return "[Keyword]";
      case TOK_STRING: return "[String]";
      case TOK_NUMBER: return "[Number]";
      case TOK_SYMBOL: return "[Symbol]";
      case TOK_IDENTIFIER: return "[Identifier]";
      case TOK_COMMENT: return "[Comment]";
      default: return "<unknown token type>";
    }
}

ostream& PARSER::fail(void)
{
    return ERR << "Error while parsing " << tokenToString(mLastToken) 
               << "\"" << yytext << "\" at " << yylineno << ":";
}

#undef PARSER

