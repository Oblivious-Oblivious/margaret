#ifndef __STRING_H_
#define __STRING_H_

#include <stdlib.h> /* size_t */
#include <stdbool.h> /* bool */

/**
 * @brief A mutable string of characters used to dynamically build a string.
 * @param str -> The str char* we construct our string into
 * @param alloced -> The total sized allocated for the string
 * @param size -> The total size of the string
 */
typedef struct string {
    char *str;
    size_t alloced;
    size_t size;
} string;

/**
 * @brief Create an str builder
 * @param initial_string -> The initial string to set
 * @return The str builder
 */
string *string_new(const char *initial_string);

/**
 * @brief Adds a formatted string into the builder
 * @param self -> The str builder ot add to
 * @param f -> The format string to use
 * @param ... -> The rest of the arguments
 */
void string_addf(string *self, const char *f, ...);

/**
 * @brief Add a string to the builder
 * @param self -> The string builder to use
 * @param str -> The string to add
 */
void string_add_str(string *self, const char *str);

/**
 * @brief Add a character to the builder
 * @param self -> The string builder to use
 * @param c -> The character to add 
 */
void string_add_char(string *self, char c);

/**
 * @brief Adds a string into self
 * @param self -> The str builder to use
 * @param other -> The str builder to add
 */
void string_add(string *self, string *other);

/**
 * @brief A pointer to the internal buffer with the builder's stirng data
 * @param self -> The string builder to use
 * @return A pointer to the internal string data
 */
char *string_get(string *self);

/**
 * @brief Accessor to the string characters by index
 * @param self -> The string builder to use
 * @param index -> The index of the character we want to receive
 * @return The character we searched for
 */
char string_get_char_at_index(string *self, size_t index);

/**
 * @brief Return a memory duplicate string
 * @param self -> The string to duplicate
 * @return The dup string
 */
string *string_dup(string *self);

/**
 * @brief Clear the builder
 * @param self -> The string builder to use
 **/
void string_delete(string *self);

/**
 * @brief Remove data from the end of the builder
 * @param self -> The string builder to use
 * @param len -> The new length of the string, anything after this length is removed
 */
void string_shorten(string *self, size_t len);

/**
 * @brief Remove data from the beginning of the builder
 * @param self -> The string builder to use
 * @param len -> The length to remove
 */
void string_skip(string *self, size_t len);

/**
 * @brief Removes all instances of `_` underscores
 * @param self -> The string builder to use
 * @return The edited string builder
 */
string *string_remove_underscores(string *self);

/**
 * @brief Return a substring of our current string without modifying the original
 * @param self -> The string builder we are using
 * @param str_position_from -> The point where we start our substring
 * @param str_position_to -> The point where we end our substring
 * @return A substring of a copy of the original string
 */
string *string_substring(string *self, size_t str_position_from, size_t str_position_to);

/**
 * @brief The size of the string contained in the builder
 * @param self -> The string builder to use
 * @return The current size of the string
 */
size_t string_size(string *self);

/**
 * @brief Checks if the char pointers of the two strings passed are the same
 * @param self -> The first string
 * @param other -> The second string
 * @return A boolean signaling if the strings are equal
 */
bool string_equals(string *self, string *other);

#endif
