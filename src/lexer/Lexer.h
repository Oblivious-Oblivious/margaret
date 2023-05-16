#ifndef __LEXER_H_
#define __LEXER_H_

#include <stdint.h> /* size_t */
#include <string.h> /* strlen */

#include "../base/string.h"
#include "../tokens/TokenTable.h"

static const char REGEX_WHITESPACE[5] = {' ','\t','\f','\r','\0'};
static const char REGEX_NEWLINE[2] = {'\n','\0'};
static const char REGEX_NUMBER[11] = {'0','1','2','3','4','5','6','7','8','9','\0'};
static const char REGEX_LETTER[53] = {
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    '\0'
};
static const char REGEX_BINARY[3] = {'0','1','\0'};
static const char REGEX_HEXADECIMAL[23] = {'0','1','2','3','4','5','6','7','8','9','A','a','B','b','C','c','D','d','E','e','F','f','\0'};
static const char REGEX_OCTAL[9] = {'0','1','2','3','4','5','6','7','\0'};
static const char REGEX_ID_SYMBOL[3] = {'!','?','\0'};
static const char REGEX_MESSAGE_SYMBOL[19] = {'!','?','+','-','*','/','\\','~','<','>','=','%','|','&','^',';','.','`','\0'};
static const char REGEX_SYNTAX_SYMBOL[13] = {'_','(',')','[',']','{','}',',',':','@','$','#','\0'};
static const char REGEX_SINGLE_QUOTE[2] = {'\'','\0'};
static const char REGEX_DOUBLE_QUOTE[2] = {'"','\0'};

// TODO ::label:: syntax with double colons

/**
 * @brief Pattern matches a character in a matcher
 * @param c -> The character to match
 * @param matcher -> The set of characters that we look to match for
 * @return int -> A boolean
 */
static int regex_matches(char c, const char *matcher) {
    size_t matcher_size = strlen(matcher);

    for(size_t i = 0; i < matcher_size; i++)
        if(matcher[i] == c && matcher[i] != '\0')
            return 1;
    return 0;
}

/**
 * @brief Defines a lexer object
 * @param filename -> Current filename to lex tokens from
 * @param text -> string* version of scanned raw text
 * @param pos -> Current position in text array
 * @param lineno -> Counter for line numbers
 */
typedef struct Lexer {
    char *filename;
    string *text;
    size_t pos;
    size_t lineno;
} Lexer;

/**
 * @brief Creates a new lexer object and initializes the loaded text
 * @param filename -> The filename of the file that we just loaded
 * @param text -> The text we read
 * @return Lexer*
 */
Lexer *lexer_new(char *filename, string *text);

/**
 * @brief Reports an error to stderrr
 * @param self -> The lexer object
 * @param message -> The error message to report
 * @param token -> The token where the error occurred at
 * @return void* -> NULL
 */
void *lexer_error(Lexer *self, char *message, string *token);

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
