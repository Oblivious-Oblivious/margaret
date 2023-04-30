#include "table.h"

#include <string.h> /* memcmp */

#include "memory.h"
#include "../opcode/MargString.h"

#define TABLE_MAX_LOAD 0.75

static table_entry *table_find_entry(table_entry *entries, size_t capacity, MargValue key) {
    uint64_t index = MEMORY_GROW_FACTOR == 2
        ? AS_STRING(key)->hash & (capacity - 1)
        : AS_STRING(key)->hash % capacity;

    // Linear probing
    table_entry *tombstone = NULL;
    while(true) {
        table_entry *entry = &entries[index];
        if(IS_NOT_INTERNED(entry->key)) {
            if(IS_UNDEFINED(entry->value))
                return tombstone != NULL ? tombstone : entry;
            else if(tombstone == NULL)
                tombstone = entry;
        }
        else if(AS_STRING(entry->key)->hash == AS_STRING(key)->hash) {
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
        entries[i].key = MARG_NOT_INTERNED;
        entries[i].value = MARG_UNDEFINED;
    }

    self->count = 0;
    for(size_t i = 0; i < self->capacity; i++) {
        table_entry *entry = &self->entries[i];
        if(IS_NOT_INTERNED(entry->key))
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

bool table_set(table *self, MargValue key, MargValue value) {
    if(self->count + 1 > self->capacity * TABLE_MAX_LOAD) {
        size_t capacity = MEMORY_GROW_CAPACITY(self->capacity);
        table_adjust_capacity(self, capacity);
    }

    table_entry *entry = table_find_entry(self->entries, self->capacity, key);
    bool is_key_new = IS_NOT_INTERNED(entry->key);
    if(is_key_new && IS_UNDEFINED(entry->value))
        self->count++;

    entry->key = key;
    entry->value = value;

    return is_key_new;
}

MargValue table_get(table *self, MargValue key) {
    if(self->count == 0)
        return MARG_UNDEFINED;

    table_entry *entry = table_find_entry(self->entries, self->capacity, key);
    if(IS_NOT_INTERNED(entry->key))
        return MARG_UNDEFINED;

    return entry->value;
}

bool table_delete(table *self, MargValue key) {
    if(self->count == 0)
        return false;

    table_entry *entry = table_find_entry(self->entries, self->capacity, key);
    if(IS_NOT_INTERNED(entry->key))
        return false;

    /* Places a `tombstone` entry in the deleted position */
    entry->key = MARG_NOT_INTERNED;
    entry->value = MARG_UNDEFINED;

    return true;
}

void table_add_all(table *src, table *dest) {
    for(size_t i = 0; i < src->capacity; i++) {
        table_entry *entry = &src->entries[i];
        if(!IS_NOT_INTERNED(entry->key))
            table_set(dest, entry->key, entry->value);
    }
}

MargValue table_find_string(table *self, char *chars, size_t size, uint64_t hash) {
    if(self->count == 0)
        return MARG_NOT_INTERNED;

    uint64_t index = MEMORY_GROW_FACTOR == 2
        ? hash & (self->capacity - 1)
        : hash % self->capacity;

    while(true) {
        table_entry *entry = &self->entries[index];
        if(IS_NOT_INTERNED(entry->key)) {
            // Stops on a tombstone entry
            if(IS_UNDEFINED(entry->value))
                return MARG_NOT_INTERNED;
        }
        else if(AS_STRING(entry->key)->size == size
             && AS_STRING(entry->key)->hash == hash
             && memcmp(AS_STRING(entry->key)->chars, chars, size) == 0
        ) {
            return entry->key;
        }

        index = MEMORY_GROW_FACTOR == 2
            ? (index + 1) & (self->capacity - 1)
            : (index + 1) % self->capacity;
    }
}
