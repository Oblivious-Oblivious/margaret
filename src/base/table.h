#ifndef __TABLE_H_
#define __TABLE_H_

#include <stdlib.h> /* size_t */

#include "../base/boolean.h"
#include "../opcode/MargString.h"
#include "../opcode/MargValue.h"

// TODO Implement data-oriented approach by separating keys with values
//      for better memory compaction, and less cache misses
// TableKeys -> table -> {key1: index1, key2: index2, ...}
// TableValues -> vector -> [index1, index2, ...]
typedef struct table_entry {
    MargString *key;
    MargValue value;
} table_entry;

typedef struct table {
    size_t count;
    size_t capacity;
    table_entry *entries;
} table;

/**
 * @brief Initializes the values of a table
 * @param self -> table that is passed from the stack
 */
void table_init(table *self);

/**
 * @brief Inserts given key/value pair into the table
        Overrites value if the key exists
 * @param self -> Current table
 * @param key
 * @param value 
 * @return true -> Insertion succeeded
 * @return false -> Insertion failed
 */
bool table_set(table *self, MargString *key, MargValue value);

/**
 * @brief Retrieves the value of the corresponding key,
    and saves it into the passed pointer parameter
 * @param self -> Current table
 * @param key -> Key of value we are searching for
 * @param value -> Result pointer
 * @return true -> Retrieval succeeded
 * @return false -> Retrieval failed
 */
bool table_get(table *self, MargString *key, MargValue *value);

/**
 * @brief Deletes the value of the corresponding key
 * @param self -> Current table
 * @param key -> Key of value we are deleting
 * @return true -> Deletion succeeded
 * @return false -> Deletion failed
 */
bool table_delete(table *self, MargString *key);

/**
 * @brief Adds all entries from src to dest
 * @param src -> Initial table
 * @param dest -> New table
 */
void table_add_all(table *src, table *dest);

/**
 * @brief Finds a string key efficiently.
        Checks for equal sizes, table values and
        only then, mem compares each character
 * @param self -> Current Table
 * @param chars
 * @param size
 * @param hash
 * @return MargString*
 */
MargString *table_find_string(table *self, char *chars, size_t size, uint64_t hash);

#endif
