#ifndef __MARG_STRING_H_
#define __MARG_STRING_H_

#include <stdlib.h> /* size_t */

/**
 * @struct marg_string
 * @brief A mutable string of characters used to dynamically build a string.
 * @param str -> The str char* we construct our string into
 * @param alloced -> The total sized allocated for the string
 * @param size -> The total size of the string
 */
typedef struct marg_string {
    char *str;
    size_t alloced;
    size_t size;
} marg_string;

/**
 * @brief Create an str builder
 * @param initial_string -> The initial string to set
 * @return The str builder
 */
marg_string *marg_string_new(char *initial_string);

/**
 * @brief Adds a formatted string into the builder
 * @param self -> The str builder ot add to
 * @param f -> The format string to use
 * @param ... -> The rest of the arguments
 */
void marg_string_addf(marg_string *self, const char *f, ...);

/**
 * @brief Add a string to the builder
 * @param self -> The string builder to use
 * @param str -> The string to add
 */
void marg_string_add_str(marg_string *self, const char *str);

/**
 * @brief Add a character to the builder
 * @param self -> The string builder to use
 * @param c -> The character to add 
 */
void marg_string_add_char(marg_string *self, char c);

/**
 * @brief Adds a marg_string into self
 * @param self -> The str builder to use
 * @param other -> The str builder to add
 */
void marg_string_add(marg_string *self, marg_string *other);

/**
 * @brief A pointer to the internal buffer with the builder's stirng data
 * @param self -> The string builder to use
 * @return A pointer to the internal string data
 */
char *marg_string_get(marg_string *self);

/**
 * @brief Accessor to the string characters by index
 * @param self -> The string builder to use
 * @param index -> The index of the character we want to receive
 * @return The character we searched for
 */
char marg_string_get_char_at_index(marg_string *self, size_t index);

/**
 * @brief Return a memory duplicate string
 * @param self -> The string to duplicate
 * @return The dup string
 */
marg_string *marg_string_dup(marg_string *self);

/**
 * @brief Clear the builder
 * @param self -> The string builder to use
 **/
void marg_string_delete(marg_string *self);

/**
 * @brief Remove data from the end of the builder
 * @param self -> The string builder to use
 * @param len -> The new length of the string, anything after this length is removed
 */
void marg_string_shorten(marg_string *self, size_t len);

/**
 * @brief Remove data from the beginning of the builder
 * @param self -> The string builder to use
 * @param len -> The length to remove
 */
void marg_string_skip(marg_string *self, size_t len);

/**
 * @brief Removes all instances of `_` underscores
 * @param self -> The string builder to use
 * @return The edited string builder
 */
marg_string *marg_string_remove_underscores(marg_string *self);

/**
 * @brief Return a substring of our current string without modifying the original
 * @param self -> The string builder we are using
 * @param str_position_from -> The point where we start our substring
 * @param str_position_to -> The point where we end our substring
 * @return A substring of a copy of the original string
 */
marg_string *string_substring(marg_string *self, size_t str_position_from, size_t str_position_to);

/**
 * @brief The size of the string contained in the builder
 * @param self -> The string builder to use
 * @return The current size of the string
 */
size_t marg_string_size(marg_string *self);

/**
 * @brief Checks if the char pointers of the two strings passed are the same
 * @param self -> The first string
 * @param other -> The second string
 * @return A boolean signaling if the strings are equal
 */
unsigned char marg_string_equals(marg_string *self, marg_string *other);

/**
 * @brief Frees the memory of the string
 * @param self -> The string to free
 */
void marg_string_free(marg_string *self);

#endif
