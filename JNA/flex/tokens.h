/** @file
 *
 * Tokens identifier returned by flex parser
 *
 * @author Gabriel Paul "Cley Faye" Risterucci
 * @date 2010-04-08
 */

#ifndef  __FLEX_TOKENS_H
#define  __FLEX_TOKENS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    FLEX_EOF = 0,
    TOK_JNA_COMMAND,
    TOK_KEYWORD,
    TOK_STRING,
    TOK_NUMBER,
    TOK_SYMBOL,
    TOK_IDENTIFIER,
    TOK_COMMENT,

    TOK_OTHER

} TokensList;

#ifdef __cplusplus
}
#endif

#endif

