#include "MargValue.h"

#define MARG_HASH_MAX_LOAD    0.75
#define MARG_HASH_GROW_FACTOR 2

static size_t custom_fnv_1a_64_hash(char *key, size_t size) {
  size_t i;
  size_t hash = 14695981039346656037u;

  for(i = 0; i < size; i++) {
    hash ^= (uint8_t)key[i];
    hash *= 1099511628211;
  }

  return hash;
}

/**
 * @brief Finds a specific entry using a key
 * @param entries -> The entries array
 * @param alloced -> Current alloced size used for hashing calculations
 * @param key -> Current key used for searching
 * @return MargHashEntry* -> Found entry, or tombstone in case of removal
 */
static MargHashEntry *
marg_hash_find_entry(MargHashEntry *entries, size_t alloced, MargValue key) {
  size_t hash = custom_fnv_1a_64_hash(
    AS_STRING(key)->value, marg_string_size(AS_STRING(key))
  );
  size_t index = hash & (alloced - 1);

  MargHashEntry *tombstone = NULL;
  while(true) {
    MargHashEntry *entry = &entries[index];
    size_t entry_hash    = custom_fnv_1a_64_hash(
      AS_STRING(entry->key)->value, marg_string_size(AS_STRING(entry->key))
    );
    if(IS_NOT_INTERNED(entry->key)) {
      if(IS_UNDEFINED(entry->value)) {
        return tombstone != NULL ? tombstone : entry;
      } else if(tombstone == NULL) {
        tombstone = entry;
      }
    } else if(entry_hash == hash) {
      return entry;
    }

    index = MARG_HASH_GROW_FACTOR == 2 ? (index + 1) & (alloced - 1)
                                       : (index + 1) % alloced;
  }
}

/**
 * @brief Resizes the Hash and rehashes interned elements
 * @param self -> Current Hash
 * @param alloced -> New, increased capacity number
 */
static void marg_hash_adjust_capacity(MargHash *self, size_t alloced) {
  size_t i;
  MargHashEntry *entries =
    (MargHashEntry *)malloc(sizeof(MargHashEntry) * alloced);

  for(i = 0; i < alloced; i++) {
    entries[i].key   = MARG_NOT_INTERNED;
    entries[i].value = MARG_UNDEFINED;
  }

  self->size = 0;
  for(i = 0; i < self->alloced; i++) {
    MargHashEntry *entry     = &self->entries[i];
    MargHashEntry *new_entry = NULL;

    if(IS_NOT_INTERNED(entry->key)) {
      continue;
    }

    new_entry        = marg_hash_find_entry(entries, alloced, entry->key);
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

  MargValue proto_object = table_get(&vm->global_variables, "$Hash");
  obj->parent            = AS_OBJECT(proto_object);

  table_add(&obj->instance_variables, "@self", QNAN_BOX(obj));
  table_add(&obj->instance_variables, "@super", QNAN_BOX(obj->parent));

  self->alloced = 0;
  self->size    = 0;
  self->entries = NULL;

  return self;
}

void marg_hash_add(MargHash *self, MargValue key, MargValue value) {
  MargHashEntry *entry = NULL;

  if(self->size + 1 > self->alloced * MARG_HASH_MAX_LOAD) {
    marg_hash_adjust_capacity(self, self->alloced * MARG_HASH_GROW_FACTOR);
  }

  entry = marg_hash_find_entry(self->entries, self->alloced, key);
  if(IS_NOT_INTERNED(entry->key) && IS_UNDEFINED(entry->value)) {
    self->size++;
  }

  entry->key   = key;
  entry->value = value;
}

MargValue marg_hash_get(MargHash *self, MargValue key) {
  MargHashEntry *entry = NULL;

  if(self->size == 0) {
    return MARG_UNDEFINED;
  }

  entry = marg_hash_find_entry(self->entries, self->alloced, key);
  if(IS_NOT_INTERNED(entry->key)) {
    return MARG_UNDEFINED;
  }

  return entry->value;
}

void marg_hash_delete(MargHash *self, MargValue key) {
  MargHashEntry *entry = NULL;

  if(self->size == 0) {
    return;
  }

  entry = marg_hash_find_entry(self->entries, self->alloced, key);
  if(IS_NOT_INTERNED(entry->key)) {
    return;
  }

  entry->key   = MARG_NOT_INTERNED;
  entry->value = MARG_UNDEFINED;
}

#undef MARG_HASH_MAX_LOAD
#undef MARG_HASH_GROW_FACTOR
