#ifndef __MARG_TABLE_H_
#define __MARG_TABLE_H_

#include "MargObject.h"

/**
 * @brief Defines a table data structure
 * @param _ -> Inherited MargObject properties
 * @param value -> A pointer to the table table
 */
typedef struct MargTable {
  MargObject _;
  EmeraldsTable value;
} MargTable;

/**
 * @brief Creates a new emprt MargTable
 * @param vm -> A pointer to the current VM
 * @return MargTable*
 */
MargTable *marg_table_new(VM *vm);

#define _marg_table_get_table(self) (&(self)->value)

#define marg_table_add(self, key, value) \
  table_add(_marg_table_get_table(self), key, value)
#define marg_table_add_all(self, other) \
  table_add_all(_marg_table_get_table(self), _marg_table_get_table(other))
#define marg_table_get(self, key) table_get(_marg_table_get_table(self), key)
#define marg_table_remove(self, key) \
  table_remove(_marg_table_get_table(self), key)
#define marg_table_size(self) table_size(_marg_table_get_table(self))

#endif
