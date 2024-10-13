#ifndef __MARG_STRING_H_
#define __MARG_STRING_H_

#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "MargObject.h"

/**
 * @brief Defines a string representation for Margaret
 * @param _ -> Inherited object properties
 * @param value -> Actual character array (stored as an EmeraldsString)
 */
typedef struct MargString {
  MargObject _;
  char *value;
} MargString;

/**
 * @brief Creates a new MargString as an object
 * @param vm -> Current VM
 * @param value -> Initial characters
 * @return MargString* -> Newly created string
 */
MargString *marg_string_new(VM *vm, const char *value);

#define marg_string_addn(self, other, len) string_addn(self->value, other, len)
#define marg_string_add(self, other)       string_add(self->value, other)
#define marg_string_addi(self, other)      string_addi(self->value, other)
p_inline void marg_string_addf(MargString *self, const char *f, ...) {
  signed int result = 0;
  char buf[4096];
  va_list args;

  va_start(args, f)
    ;
    result = vsnprintf(buf, sizeof(buf), f, args);
  va_end(args);

  if(result >= 0) {
    string_add(self->value, buf);
  }
}
#define marg_string_size(self)             string_size(self->value)
#define marg_string_size_signed(self)      string_size_signed(self->value)
#define marg_string_shorten(self, len)     string_shorten(self->value, len)
#define marg_string_skip_first(self, len)  string_skip_first(self->value, len)
#define marg_string_ignore_last(self, len) string_ignore_last(self->value, len)
#define marg_string_delete(self)           string_delete(self->value)
#define marg_string_remove(self, len)      string_remove(self->value, len)
#define marg_string_equals(self, other)    string_equals(self->value, other->value)

char *marg_string_to_string(MargString *object);

#endif
