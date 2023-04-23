#include "MargHash.h"

#include <string.h> /* memcmp */

#include "../base/memory.h"

#define MARG_HASH_MAX_LOAD 0.75

static MargHashEntry *marg_hash_find_entry(MargHashEntry *entries, size_t capacity, MargString *key) {
    uint64_t index = MEMORY_GROW_FACTOR == 2
        ? key->hash & (capacity - 1)
        : key->hash % capacity;

    // Linear probing
    MargHashEntry *tombstone = NULL;
    while(true) {
        MargHashEntry *entry = &entries[index];
        if(entry->key == NULL) {
            if(IS_NIL(entry->value))
                return tombstone != NULL ? tombstone : entry;
            else if(tombstone == NULL)
                tombstone = entry;
        }
        else if(entry->key == key) {
            return entry;
        }

        index = MEMORY_GROW_FACTOR == 2
            ? (index + 1) & (capacity - 1)
            : (index + 1) % capacity;
    }
}

static void marg_hash_adjust_capacity(MargHash *self, size_t capacity) {
    MargHashEntry *entries = (MargHashEntry*)collected_malloc(sizeof(MargHashEntry) * capacity);

    for(size_t i = 0; i < capacity; i++) {
        entries[i].key = NULL;
        entries[i].value = MARG_NIL;
    }

    self->count = 0;
    for(size_t i = 0; i < self->capacity; i++) {
        MargHashEntry *entry = &self->entries[i];
        if(entry->key == NULL)
            continue;

        MargHashEntry *new_entry = marg_hash_find_entry(entries, capacity, entry->key);
        new_entry->key = entry->key;
        new_entry->value = entry->value;
        self->count++;
    }

    self->entries = entries;
    self->capacity = capacity;
}

void marg_hash_init(MargHash *self) {
    self->count = 0;
    self->capacity = 0;
    self->entries = NULL;
}

bool marg_hash_set(MargHash *self, MargString *key, MargValue value) {
    if(self->count + 1 > self->capacity * MARG_HASH_MAX_LOAD) {
        size_t capacity = MEMORY_GROW_CAPACITY(self->capacity);
        marg_hash_adjust_capacity(self, capacity);
    }

    MargHashEntry *entry = marg_hash_find_entry(self->entries, self->capacity, key);
    bool is_key_new = entry->key == NULL;
    if(is_key_new && IS_NIL(entry->value))
        self->count++;

    entry->key = key;
    entry->value = value;

    return is_key_new;
}

bool marg_hash_get(MargHash *self, MargString *key, MargValue *value) {
    if(self->count == 0)
        return false;

    MargHashEntry *entry = marg_hash_find_entry(self->entries, self->capacity, key);
    if(entry->key == NULL)
        return false;

    *value = entry->value;
    return true;
}

bool marg_hash_delete(MargHash *self, MargString *key) {
    if(self->count == 0)
        return false;

    MargHashEntry *entry = marg_hash_find_entry(self->entries, self->capacity, key);
    if(entry->key == NULL)
        return false;

    /* Places a `tombstone` entry in the deleted position */
    entry->key = NULL;
    entry->value = MARG_BOOL(true);

    return true;
}

void marg_hash_add_all(MargHash *src, MargHash *dest) {
    for(size_t i = 0; i < src->capacity; i++) {
        MargHashEntry *entry = &src->entries[i];
        if(entry->key != NULL)
            marg_hash_set(dest, entry->key, entry->value);
    }
}

MargString *marg_hash_find_string(MargHash *self, char *chars, size_t size, uint64_t hash) {
    if(self->count == 0)
        return NULL;

    uint64_t index = MEMORY_GROW_FACTOR == 2
        ? hash & (self->capacity - 1)
        : hash % self->capacity;

    while(true) {
        MargHashEntry *entry = &self->entries[index];
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
