#include "table.h"

#include <string.h> /* memcmp */

#include "memory.h"
#include "../opcode/MargNil.h"
#include "../opcode/MargTrue.h"

#define TABLE_MAX_LOAD 0.75

static table_entry *table_find_entry(table_entry *entries, size_t capacity, MargString *key) {
    uint64_t index = MEMORY_GROW_FACTOR == 2
        ? key->hash & (capacity - 1)
        : key->hash % capacity;

    // Linear probing
    table_entry *tombstone = NULL;
    while(true) {
        table_entry *entry = &entries[index];
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

static void table_adjust_capacity(table *self, size_t capacity) {
    table_entry *entries = (table_entry*)collected_malloc(sizeof(table_entry) * capacity);

    for(size_t i = 0; i < capacity; i++) {
        entries[i].key = NULL;
        entries[i].value = MARG_NIL;
    }

    self->count = 0;
    for(size_t i = 0; i < self->capacity; i++) {
        table_entry *entry = &self->entries[i];
        if(entry->key == NULL)
            continue;

        table_entry *new_entry = table_find_entry(entries, capacity, entry->key);
        new_entry->key = entry->key;
        new_entry->value = entry->value;
        self->count++;
    }

    self->entries = entries;
    self->capacity = capacity;
}

void table_init(table *self) {
    self->count = 0;
    self->capacity = 0;
    self->entries = NULL;
}

bool table_set(table *self, MargString *key, MargValue value) {
    if(self->count + 1 > self->capacity * TABLE_MAX_LOAD) {
        size_t capacity = MEMORY_GROW_CAPACITY(self->capacity);
        table_adjust_capacity(self, capacity);
    }

    table_entry *entry = table_find_entry(self->entries, self->capacity, key);
    bool is_key_new = entry->key == NULL;
    if(is_key_new && IS_NIL(entry->value))
        self->count++;

    entry->key = key;
    entry->value = value;

    return is_key_new;
}

bool table_get(table *self, MargString *key, MargValue *value) {
    if(self->count == 0) {
        *value = MARG_NIL;
        return false;
    }

    table_entry *entry = table_find_entry(self->entries, self->capacity, key);
    if(entry->key == NULL) {
        *value = MARG_NIL;
        return false;
    }

    *value = entry->value;
    return true;
}

bool table_delete(table *self, MargString *key) {
    if(self->count == 0)
        return false;

    table_entry *entry = table_find_entry(self->entries, self->capacity, key);
    if(entry->key == NULL)
        return false;

    /* Places a `tombstone` entry in the deleted position */
    entry->key = NULL;
    entry->value = MARG_TRUE;

    return true;
}

void table_add_all(table *src, table *dest) {
    for(size_t i = 0; i < src->capacity; i++) {
        table_entry *entry = &src->entries[i];
        if(entry->key != NULL)
            table_set(dest, entry->key, entry->value);
    }
}

MargString *table_find_string(table *self, char *chars, size_t size, uint64_t hash) {
    if(self->count == 0)
        return NULL;

    uint64_t index = MEMORY_GROW_FACTOR == 2
        ? hash & (self->capacity - 1)
        : hash % self->capacity;

    while(true) {
        table_entry *entry = &self->entries[index];
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
