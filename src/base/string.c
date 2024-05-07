#include "string.h"

#include "memory.h"

#include <stdarg.h> /* va_start, va_end, va_arg */
#include <stdio.h>  /* printf, snprintf, vsnprintf */
#include <string.h> /* strlen, strcmp, memmove */

#define STRING_GROW_FACTOR 1.618

/**
 * @brief Ensure there is enough space for data being added plus a NULL
 *terminator
 * @param self -> The string builder to use
 * @param add_len -> The length that needs to be added *not* including a NULL
 *terminator
 **/
static void string_ensure_space(string *self, size_t add_len) {
  char *new_str = NULL;
  if(self == NULL || add_len == 0) {
    return;
  }

  /* Attempt to reallocate new memory in the items list */
  new_str = (char *)collected_realloc(self->str, sizeof(char *) * add_len);

  if(new_str) {
    /* Reset the items in the new memory space */
    self->str     = new_str;
    self->alloced = add_len;
  }
}

string *string_new(const char *initial_string) {
  string *self = (string *)collected_malloc(sizeof(string));

  self->str     = (char *)collected_malloc(sizeof(char) * 1024);
  self->alloced = 1024;
  self->size    = 0;
  string_add_str(self, (char *)initial_string);

  return self;
}

void string_addf(string *self, const char *f, ...) {
  signed int result = 0;
  char buf[65536];
  va_list args;

  va_start(args, f)
    ;
    result = vsnprintf(buf, sizeof(buf), f, args);
  va_end(args);

  if(result < 0) {
    return;
  }

  string_add_str(self, buf);
}

void string_add_str(string *self, const char *str) {
  size_t len;

  if(self == NULL || str == NULL || *str == '\0') {
    return;
  }

  len = strlen(str);

  if(self->alloced < self->size + len) {
    string_ensure_space(self, self->alloced * STRING_GROW_FACTOR);
  }

  /* Copy the value into memory */
  memmove(self->str + self->size, str, len);

  /* Reset size and NULL terminate */
  self->size += len;
  self->str[self->size] = '\0';
}

void string_add_char(string *self, char c) {
  if(self == NULL) {
    return;
  }

  if(self->alloced < self->size + 1) {
    string_ensure_space(self, self->alloced * STRING_GROW_FACTOR);
  }

  self->str[self->size] = c;
  self->size++;
  self->str[self->size] = '\0';
}

void string_add(string *self, string *other) {
  if(self == NULL || other == NULL) {
    return;
  }
  string_add_str(self, other->str);
}

char *string_get(string *self) {
  if(self == NULL) {
    return NULL;
  }
  return self->str;
}

char string_get_char_at_index(string *self, size_t index) {
  if(self == NULL) {
    return '\0';
  }
  return self->str[index];
}

string *string_dup(string *self) {
  string *dup = NULL;

  if(self == NULL) {
    return NULL;
  }

  dup = string_new("");
  string_add_str(dup, string_get(self));

  return dup;
}

void string_delete(string *self) {
  if(self == NULL) {
    return;
  }

  /* Call shorten with 0, clearing out the string */
  string_shorten(self, 0);
}

void string_shorten(string *self, size_t len) {
  if(self == NULL || len >= self->size) {
    return;
  }

  /* Reset the length and NULL terminate, ingoring
      all values right to the NULL from memory */
  self->size            = len;
  self->str[self->size] = '\0';
}

void string_skip(string *self, size_t len) {
  if(self == NULL || len == 0) {
    return;
  }

  if(len >= self->size) {
    /* If we choose to drop more bytes than the
        string has simply clear the string */
    string_delete(self);
    return;
  }

  self->size -= len;

  /* +1 to move the NULL. */
  memmove(self->str, self->str + len, self->size + 1);
}

string *string_remove_underscores(string *self) {
  string *sb_dup = string_new("");

  char *sb_str = string_get(self);
  for(size_t i = 0; i < string_size(self); i++) {
    if(sb_str[i] != '_') {
      string_add_char(sb_dup, sb_str[i]);
    }
  }

  return sb_dup;
}

string *string_substring(
  string *self, size_t str_position_from, size_t str_position_to
) {
  string *strdup = string_dup(self);
  string_skip(strdup, str_position_from);
  string_shorten(strdup, str_position_to - str_position_from + 1);
  return strdup;
}

size_t string_size(string *self) {
  if(self == NULL) {
    return 0;
  }
  return self->size;
}

bool string_equals(string *self, string *other) {
  return strcmp(string_get(self), string_get(other)) == 0;
}
