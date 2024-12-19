#ifndef __MARGARET_PRIMITIVES_H_
#define __MARGARET_PRIMITIVES_H_

#include "../opcode/instruction.h"

/* TODO - Create a raise built-in object */
#define raise(msg) (__PRIM_RAISE(vm, MARG_STRING(msg)))
MargValue __PRIM_RAISE(VM *vm, MargValue error);
/* MargValue primitive_DNU(VM *vm, MargValue args_value); */
/* MargValue primitive_CLONE(VM *vm, MargValue args_value); */
MargValue __PRIM_INSPECT(VM *vm, MargValue args_value);
MargValue __PRIM_BIND(VM *vm, MargValue args_value);
MargValue __PRIM_MARGARET_MESSAGES(VM *vm, MargValue args_value);

/* TODO - Refactor as a $Margaret message */
/**
 * @brief String representation for object literals in the Java style
 * @param object -> The `object` object as a MargValue
 * @return char*
 */
/* char *marg_object_to_string_with_hash(MargValue object) {
  char *res = string_new("");
  string_addf(
    &res,
    "%s@0x%zx",
    AS_OBJECT(object)->name,
    komihash_hash(AS_OBJECT(object), sizeof(MargObject))
  );
  return res;
} */

#endif
