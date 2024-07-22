#include "MargHash.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "MargValue.h"

#define MARG_HASH_MAX_LOAD 0.75

/**
 * @brief Finds a specific entry using a key
 * @param entries -> The entries array
 * @param alloced -> Current alloced size used for hashing calculations
 * @param key -> Current key used for searching
 * @return MargHashEntry* -> Found entry, or tombstone in case of removal
 */
static MargHashEntry *
marg_hash_find_entry(MargHashEntry *entries, size_t alloced, MargValue key) {
  uint64_t index = MEMORY_GROW_FACTOR == 2
                     ? AS_STRING(key)->hash & (alloced - 1)
                     : AS_STRING(key)->hash % alloced;

  // Linear probing
  MargHashEntry *tombstone = NULL;
  while(true) {
    MargHashEntry *entry = &entries[index];
    if(IS_NOT_INTERNED(entry->key)) {
      if(IS_UNDEFINED(entry->value)) {
        return tombstone != NULL ? tombstone : entry;
      } else if(tombstone == NULL) {
        tombstone = entry;
      }
    } else if(AS_STRING(entry->key)->hash == AS_STRING(key)->hash) {
      return entry;
    }

    index = MEMORY_GROW_FACTOR == 2 ? (index + 1) & (alloced - 1)
                                    : (index + 1) % alloced;
  }
}

/**
 * @brief Resizes the Hash and rehashes interned elements
 * @param self -> Current Hash
 * @param alloced -> New, increased capacity number
 */
static void marg_hash_adjust_capacity(MargHash *self, size_t alloced) {
  MargHashEntry *entries =
    (MargHashEntry *)collected_malloc(sizeof(MargHashEntry) * alloced);

  for(size_t i = 0; i < alloced; i++) {
    entries[i].key   = MARG_NOT_INTERNED;
    entries[i].value = MARG_UNDEFINED;
  }

  self->size = 0;
  for(size_t i = 0; i < self->alloced; i++) {
    MargHashEntry *entry = &self->entries[i];
    if(IS_NOT_INTERNED(entry->key)) {
      continue;
    }

    MargHashEntry *new_entry =
      marg_hash_find_entry(entries, alloced, entry->key);
    new_entry->key   = entry->key;
    new_entry->value = entry->value;
    self->size++;
  }

  self->entries = entries;
  self->alloced = alloced;
}

MargHash *marg_hash_new(VM *vm) {
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargHash), string_new("$HashClone")
  );
  MargHash *self = (MargHash *)obj;

  MargValue proto_object =
    table_get(&vm->global_variables, MARG_STRING("$Hash"));
  obj->parent = AS_OBJECT(proto_object);

  table_set(&obj->instance_variables, MARG_STRING("@self"), QNAN_BOX(obj));
  table_set(
    &obj->instance_variables, MARG_STRING("@super"), QNAN_BOX(obj->parent)
  );

  self->alloced = 0;
  self->size    = 0;
  self->entries = NULL;

  return self;
}

void marg_hash_add(MargHash *self, MargValue key, MargValue value) {
  if(self->size + 1 > self->alloced * MARG_HASH_MAX_LOAD) {
    marg_hash_adjust_capacity(self, MEMORY_GROW_CAPACITY(self->alloced));
  }

  MargHashEntry *entry =
    marg_hash_find_entry(self->entries, self->alloced, key);
  if(IS_NOT_INTERNED(entry->key) && IS_UNDEFINED(entry->value)) {
    self->size++;
  }

  entry->key   = key;
  entry->value = value;
}

MargValue marg_hash_get(MargHash *self, MargValue key) {
  if(self->size == 0) {
    return MARG_UNDEFINED;
  }

  MargHashEntry *entry =
    marg_hash_find_entry(self->entries, self->alloced, key);
  if(IS_NOT_INTERNED(entry->key)) {
    return MARG_UNDEFINED;
  }

  return entry->value;
}

void marg_hash_delete(MargHash *self, MargValue key) {
  if(self->size == 0) {
    return;
  }

  MargHashEntry *entry =
    marg_hash_find_entry(self->entries, self->alloced, key);
  if(IS_NOT_INTERNED(entry->key)) {
    return;
  }

  /* Places a `tombstone` entry in the deleted position */
  entry->key   = MARG_NOT_INTERNED;
  entry->value = MARG_UNDEFINED;
}

char *marg_hash_to_string(MargHash *object) {
  char *res = string_new("");
  string_add(res, "{");
  size_t hash_size = marg_hash_size(object);
  if(hash_size > 0) {
    for(size_t i = 0; i < object->alloced; i++) {
      MargHashEntry *entry = &object->entries[i];
      if(!IS_NOT_INTERNED(entry->key)) {
        string_addf(
          res,
          "%s: %s, ",
          marg_value_format(entry->key),
          marg_value_format(entry->value)
        );
      }
    }
    string_ignore_last(res, 2);
  }

  string_add(res, "}");

  return res;
}
