#include "MargHash.h"

#include "../base/memory.h"
#include "../opcode/MargString.h"

#define MARG_HASH_MAX_LOAD 0.75

/**
 * @brief Finds a specific entry using a key
 * @param entries -> The entries array
 * @param alloced -> Current alloced size used for hashing calculations
 * @param key -> Current key used for searching
 * @return MargHashEntry* -> Found entry, or tombstone in case of removal
 */
static MargHashEntry *marg_hash_find_entry(MargHashEntry *entries, size_t alloced, MargValue key) {
    uint64_t index = MEMORY_GROW_FACTOR == 2
        ? AS_STRING(key)->hash & (alloced - 1)
        : AS_STRING(key)->hash % alloced;

    // Linear probing
    MargHashEntry *tombstone = NULL;
    while(true) {
        MargHashEntry *entry = &entries[index];
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
            ? (index + 1) & (alloced - 1)
            : (index + 1) % alloced;
    }
}

/**
 * @brief Resizes the Hash and rehashes interned elements
 * @param self -> Current Hash
 * @param alloced -> New, increased capacity number
 */
static void marg_hash_adjust_capacity(MargHash *self, size_t alloced) {
    MargHashEntry *entries = (MargHashEntry*)collected_malloc(sizeof(MargHashEntry) * alloced);

    for(size_t i = 0; i < alloced; i++) {
        entries[i].key = MARG_NOT_INTERNED;
        entries[i].value = MARG_UNDEFINED;
    }

    self->size = 0;
    for(size_t i = 0; i < self->alloced; i++) {
        MargHashEntry *entry = &self->entries[i];
        if(IS_NOT_INTERNED(entry->key))
            continue;

        MargHashEntry *new_entry = marg_hash_find_entry(entries, alloced, entry->key);
        new_entry->key = entry->key;
        new_entry->value = entry->value;
        self->size++;
    }

    self->entries = entries;
    self->alloced = alloced;
}

MargHash *marg_hash_new(VM *vm) {
    MargObject *obj = (MargObject*)marg_object_new(vm, sizeof(MargHash), "$Hash");
    MargHash *self = (MargHash*)obj;

    self->alloced = 0;
    self->size = 0;
    self->entries = NULL;

    return self;
}

void marg_hash_add(MargHash *self, MargValue key, MargValue value) {
    if(self->size + 1 > self->alloced * MARG_HASH_MAX_LOAD)
        marg_hash_adjust_capacity(self, MEMORY_GROW_CAPACITY(self->alloced));

    MargHashEntry *entry = marg_hash_find_entry(self->entries, self->alloced, key);
    if(IS_NOT_INTERNED(entry->key) && IS_UNDEFINED(entry->value))
        self->size++;

    entry->key = key;
    entry->value = value;
}

MargValue marg_hash_get(MargHash *self, MargValue key) {
    if(self->size == 0)
        return MARG_UNDEFINED;

    MargHashEntry *entry = marg_hash_find_entry(self->entries, self->alloced, key);
    if(IS_NOT_INTERNED(entry->key))
        return MARG_UNDEFINED;

    return entry->value;
}

void marg_hash_delete(MargHash *self, MargValue key) {
    if(self->size == 0)
        return;

    MargHashEntry *entry = marg_hash_find_entry(self->entries, self->alloced, key);
    if(IS_NOT_INTERNED(entry->key))
        return;

    /* Places a `tombstone` entry in the deleted position */
    entry->key = MARG_NOT_INTERNED;
    entry->value = MARG_UNDEFINED;
}
