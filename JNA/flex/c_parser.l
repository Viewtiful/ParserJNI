digit [0-9]
letter [A-Za-z]
underline _
opencurlybrace [{]
closecurlybrace [}]
openbracket [(]
closebracket [)]
equal [=]
comma [,]
star [*]
quote ["]
slash [/]
variadic \.\.\.
    /* comment stuff from http://compilers.iecc.com/comparch/article/96-03-019 */
cmt [^/*]
separator [ \t\n]
%{
#include "flex/tokens.h"
%}
%%
    /* Reserve something for special instructions ? */
{slash}{slash}JNA return TOK_JNA_COMMAND;
    /* Strip comments */
{slash}({slash}[^J].*|{star}({slash}|{cmt}|{star}+{cmt})*{star}+{slash}) return TOK_COMMENT;
    /* Some preprocessor stuff */
#if\ 0\n([^(#endif)].*\n)*#endif\n ;
#.*\n ;
KTB_DLL ;
    /* keywords, except for void treated differently */
enum return TOK_KEYWORD;
const return TOK_KEYWORD;
struct return TOK_KEYWORD;
extern return TOK_KEYWORD;
static return TOK_KEYWORD;
typedef return TOK_KEYWORD;
volatile return TOK_KEYWORD;

    /* litteral constants */
{quote}(\\.|[^\"\\])*{quote} return TOK_STRING;
{digit}*([uUlL])? return TOK_NUMBER;

    /* Symbols */
{openbracket}|{closebracket} return TOK_SYMBOL;
{opencurlybrace}|{closecurlybrace} return TOK_SYMBOL;
{variadic}|{star}|{equal}|{comma}|; return TOK_SYMBOL;

    /* Identifiers */
({underline}|{letter})({letter}|{digit}|{underline})* return TOK_IDENTIFIER;

    /* Remaining crap */
{separator} ;
. return TOK_OTHER;
%%

