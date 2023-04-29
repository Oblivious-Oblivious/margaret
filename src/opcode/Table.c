#include "Table.h"

#include <string.h> /* memcmp */

#include "../base/memory.h"
#include "MargNil.h"

#define TABLE_MAX_LOAD 0.75

static TableEntry *table_find_entry(TableEntry *entries, size_t capacity, MargString *key) {
    uint64_t index = MEMORY_GROW_FACTOR == 2
        ? key->hash & (capacity - 1)
        : key->hash % capacity;

    // Linear probing
    TableEntry *tombstone = NULL;
    while(true) {
        TableEntry *entry = &entries[index];
        if(entry->key == NULL) {
            if(IS_NIL(entry->value))
                return tombstone != NULL ? tombstone : entry;
            else if(tombstone == NULL)
                tombstone = entry;
        }
        else if(entry->key->hash == key->hash) {
            return entry;
        }

        index = MEMORY_GROW_FACTOR == 2
            ? (index + 1) & (capacity - 1)
            : (index + 1) % capacity;
    }
}

static void table_adjust_capacity(Table *self, size_t capacity) {
    TableEntry *entries = (TableEntry*)collected_malloc(sizeof(TableEntry) * capacity);

    for(size_t i = 0; i < capacity; i++) {
        entries[i].key = NULL;
        entries[i].value = MARG_NIL;
    }

    self->count = 0;
    for(size_t i = 0; i < self->capacity; i++) {
        TableEntry *entry = &self->entries[i];
        if(entry->key == NULL)
            continue;

        TableEntry *new_entry = table_find_entry(entries, capacity, entry->key);
        new_entry->key = entry->key;
        new_entry->value = entry->value;
        self->count++;
    }

    self->entries = entries;
    self->capacity = capacity;
}

void table_init(Table *self) {
    self->count = 0;
    self->capacity = 0;
    self->entries = NULL;
}

bool table_set(Table *self, MargString *key, MargValue value) {
    if(self->count + 1 > self->capacity * TABLE_MAX_LOAD) {
        size_t capacity = MEMORY_GROW_CAPACITY(self->capacity);
        table_adjust_capacity(self, capacity);
    }

    TableEntry *entry = table_find_entry(self->entries, self->capacity, key);
    bool is_key_new = entry->key == NULL;
    if(is_key_new && IS_NIL(entry->value))
        self->count++;

    entry->key = key;
    entry->value = value;

    return is_key_new;
}

bool table_get(Table *self, MargString *key, MargValue *value) {
    if(self->count == 0) {
        *value = MARG_NIL;
        return false;
    }

    TableEntry *entry = table_find_entry(self->entries, self->capacity, key);
    if(entry->key == NULL) {
        *value = MARG_NIL;
        return false;
    }

    *value = entry->value;
    return true;
}

bool table_delete(Table *self, MargString *key) {
    if(self->count == 0)
        return false;

    TableEntry *entry = table_find_entry(self->entries, self->capacity, key);
    if(entry->key == NULL)
        return false;

    /* Places a `tombstone` entry in the deleted position */
    entry->key = NULL;
    entry->value = MARG_TRUE;

    return true;
}

void table_add_all(Table *src, Table *dest) {
    for(size_t i = 0; i < src->capacity; i++) {
        TableEntry *entry = &src->entries[i];
        if(entry->key != NULL)
            table_set(dest, entry->key, entry->value);
    }
}

MargString *table_find_string(Table *self, char *chars, size_t size, uint64_t hash) {
    if(self->count == 0)
        return NULL;

    uint64_t index = MEMORY_GROW_FACTOR == 2
        ? hash & (self->capacity - 1)
        : hash % self->capacity;

    while(true) {
        TableEntry *entry = &self->entries[index];
        if(entry->key == NULL) {
            // Stops on a tombstone entry
            if(IS_NIL(entry->value))
                return NULL;
        }
        else if(entry->key->size == size
             && entry->key->hash == hash
             && memcmp(entry->key->chars, chars, size) == 0
        ) {
            return entry->key;
        }

        index = MEMORY_GROW_FACTOR == 2
            ? (index + 1) & (self->capacity - 1)
            : (index + 1) % self->capacity;
    }
}
