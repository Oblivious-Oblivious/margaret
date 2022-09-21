#include "marg_string.h"

#include <stdio.h>  /* printf, snprintf, vsnprintf */
#include <stdlib.h> /* malloc, realloc, free */
#include <string.h> /* strlen, strcmp, memmove */
#include <stdarg.h> /* va_start, va_end, va_arg */

#define MARG_STRING_GROW_FACTOR 1.618

/**
 * @brief Ensure there is enough space for data being added plus a NULL terminator
 * @param self -> The string builder to use
 * @param add_len -> The length that needs to be added *not* including a NULL terminator
 **/
static void marg_string_ensure_space(marg_string *self, size_t add_len) {
    char *new_str = NULL;
    if(self == NULL || add_len == 0) return;

    /* Attempt to reallocate new memory in the items list */
    new_str = (char*)realloc(self->str, sizeof(char*) * add_len);

    if(new_str) {
        /* Reset the items in the new memory space */
        self->str = new_str;
        self->alloced = add_len;
    }
}

marg_string *marg_string_new(char *initial_string) {
    marg_string *self = (marg_string*)malloc(sizeof(marg_string));

    self->str = (char*)malloc(sizeof(char) * 32);
    self->alloced = 32;
    self->size = 0;
    marg_string_add_str(self, initial_string);

    return self;
}

void marg_string_addf(marg_string *self, const char *f, ...) {
    /* TODO -> Bounds checks for format string */
    signed int result = 0;
    char buf[16384];
    va_list args;

    va_start(args, f);
        result = vsnprintf(buf, sizeof(buf), f, args);
    va_end(args);

    if(result < 0)
        return;

    marg_string_add_str(self, buf);
}

void marg_string_add_str(marg_string *self, const char *str) {
    size_t len;

    if(self == NULL || str == NULL || *str == '\0')
        return;

    len = strlen(str);

    if(self->alloced < self->size + len)
        marg_string_ensure_space(self, self->alloced * MARG_STRING_GROW_FACTOR);

    /* Copy the value into memory */
    memmove(self->str+self->size, str, len);

    /* Reset size and NULL terminate */
    self->size += len;
    self->str[self->size] = '\0';
}

void marg_string_add_char(marg_string *self, char c) {
    if(self == NULL) return;

    if(self->alloced < self->size + 1)
        marg_string_ensure_space(self, self->alloced * MARG_STRING_GROW_FACTOR);

    self->str[self->size] = c;
    self->size++;
    self->str[self->size] = '\0';
}

void marg_string_add(marg_string *self, marg_string *other) {
    if(self == NULL || other == NULL) return;
    marg_string_add_str(self, other->str);
}

char *marg_string_get(marg_string *self) {
    if(self == NULL) return NULL;
    return self->str;
}

char marg_string_get_char_at_index(marg_string *self, size_t index) {
    if(self == NULL) return '\0';
    return self->str[index];
}

marg_string *marg_string_dup(marg_string *self) {
    marg_string *dup = NULL;

    if(self == NULL) return NULL;

    dup = marg_string_new("");
    marg_string_add_str(dup, marg_string_get(self));

    return dup;
}

void marg_string_delete(marg_string *self) {
    if(self == NULL) return;

    /* Call shorten with 0, clearing out the string */
    marg_string_shorten(self, 0);
}

void marg_string_shorten(marg_string *self, size_t len) {
    if(self == NULL || len >= self->size) return;

    /* Reset the length and NULL terminate, ingoring
        all values right to the NULL from memory */
    self->size = len;
    self->str[self->size] = '\0';
}

void marg_string_skip(marg_string *self, size_t len) {
    if(self == NULL || len == 0) return;

    if(len >= self->size) {
        /* If we choose to drop more bytes than the
            string has simply clear the string */
        marg_string_delete(self);
        return;
    }

    self->size -= len;

    /* +1 to move the NULL. */
    memmove(self->str, self->str + len, self->size + 1);
}

marg_string *marg_string_remove_underscores(marg_string *self) {
    marg_string *sb_dup = marg_string_new("");

    char *sb_str = marg_string_get(self);
    for(size_t i = 0; i < marg_string_size(self); i++)
        if(sb_str[i] != '_')
            marg_string_add_char(sb_dup, sb_str[i]);

    return sb_dup;
}

marg_string *string_substring(marg_string *self, size_t str_position_from, size_t str_position_to) {
    marg_string *strdup = marg_string_dup(self);
    marg_string_skip(strdup, str_position_from);
    marg_string_shorten(strdup, str_position_to - str_position_from + 1);
    return strdup;
}

size_t marg_string_size(marg_string *self) {
    if(self == NULL) return 0;
    return self->size;
}

unsigned char marg_string_equals(marg_string *self, marg_string *other) {
    return strcmp(marg_string_get(self), marg_string_get(other)) == 0;
}

void marg_string_free(marg_string *self) {
    if(self != NULL && self->str != NULL)
        free(self->str);
    if(self != NULL)
        free(self);
}
