#ifndef __LEXER_H_
#define __LEXER_H_

#include <stdint.h> /* int64_t, uint64_t */
#include <string.h> /* strlen */

#include "../base/marg_string.h"
#include "../tokens/TokenTable.h"

static const char REGEX_WHITESPACE[4] = {' ','\t','\f','\r'};
static const char REGEX_NEWLINE[1] = {'\n'};
static const char REGEX_NUMBER[10] = {'0','1','2','3','4','5','6','7','8','9'};
static const char REGEX_LETTER[52] = {
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};
static const char REGEX_BINARY[2] = {'0','1'};
static const char REGEX_HEXADECIMAL[22] = {'0','1','2','3','4','5','6','7','8','9','A','a','B','b','C','c','D','d','E','e','F','f'};
static const char REGEX_OCTAL[8] = {'0','1','2','3','4','5','6','7'};
static const char REGEX_ID_SYMBOL[2] = {'!','?'};
static const char REGEX_MESSAGE_SYMBOL[19] = {'!','?','+','-','*','/','\\','~','<','>','=','%','|','&','^',';','.','`','$'};
/* TODO Check if `_` underscore is supposed to be a syntax symbol */
static const char REGEX_SYNTAX_SYMBOL[11] = {'_','(',')','[',']','{','}',',',':','@','#'};
static const char REGEX_SINGLE_QUOTE[1] = {'\''};
static const char REGEX_DOUBLE_QUOTE[1] = {'"'};

/**
 * @brief Pattern matches a character in a matcher
 * @param c -> The character to match
 * @param matcher -> The set of characters that we look to match for
 * @return int -> A boolean
 */
static int regex_matches(char c, const char *matcher) {
    size_t matcher_size = strlen(matcher);

    for(size_t i = 0; i < matcher_size; i++)
        if(matcher[i] == c)
            return 1;
    return 0;
}

typedef struct Lexer {
    char *filename;
    marg_string *text;
    /* TODO Abstract into generic size */
    int64_t pos;
    uint64_t lineno;
} Lexer;

/**
 * @brief Creates a new lexer object and initializes the loaded text
 * @param filename -> The filename of the file that we just loaded
 * @param text -> The text we read
 * @return Lexer*
 */
Lexer *lexer_new(char *filename, marg_string *text);

/**
 * @brief Reports an error to stderrr
 * @param self -> The lexer object
 * @param message -> The error message to report
 * @param token -> The token where the error occurred at
 * @return void* -> NULL
 */
void *lexer_error(Lexer *self, char *message, marg_string *token);

/**
 * @brief Get the next character from the input stream
 * @param self -> The lexer object
 * @return char -> The found character
 */
char lexer_next_character(Lexer *self);

/**
 * @brief Peeks a character in distance `i` from pos
 * @param self -> The lexer object
 * @param i -> The index of the character (distance)
 * @return char -> The found character
 */
char lexer_peek_character(Lexer *self, size_t i);

/**
 * @brief Tokenizes the input and stores into a TokenTable
 * @param self -> The lexer object
 * @return TokenTable* -> A TokenTable of Token objects;
 */
TokenTable *lexer_make_tokens(Lexer *self);

#endif
