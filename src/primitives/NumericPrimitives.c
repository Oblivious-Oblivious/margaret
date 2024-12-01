#include "NumericPrimitives.h"

MargValue __PRIM_ADD(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  if(IS_INTEGER(self) && IS_INTEGER(args[0])) {
    return MARG_INTEGER(AS_INTEGER(self)->value + AS_INTEGER(args[0])->value);
  } else if(IS_INTEGER(self) && IS_FLOAT(args[0])) {
    return MARG_FLOAT(AS_INTEGER(self)->value + AS_FLOAT(args[0])->value);
  } else if(IS_FLOAT(self) && IS_INTEGER(args[0])) {
    return MARG_FLOAT(AS_FLOAT(self)->value + AS_INTEGER(args[0])->value);
  } else if(IS_FLOAT(self) && IS_FLOAT(args[0])) {
    return MARG_FLOAT(AS_FLOAT(self)->value + AS_FLOAT(args[0])->value);
  } else {
    return raise("TypeError: cannot add non-numeric values.");
  }
}

MargValue __PRIM_SUB(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  if(IS_INTEGER(self) && IS_INTEGER(args[0])) {
    return MARG_INTEGER(AS_INTEGER(self)->value - AS_INTEGER(args[0])->value);
  } else if(IS_INTEGER(self) && IS_FLOAT(args[0])) {
    return MARG_FLOAT(AS_INTEGER(self)->value - AS_FLOAT(args[0])->value);
  } else if(IS_FLOAT(self) && IS_INTEGER(args[0])) {
    return MARG_FLOAT(AS_FLOAT(self)->value - AS_INTEGER(args[0])->value);
  } else if(IS_FLOAT(self) && IS_FLOAT(args[0])) {
    return MARG_FLOAT(AS_FLOAT(self)->value - AS_FLOAT(args[0])->value);
  } else {
    return raise("TypeError: cannot subtract non-number values.");
  }
}

MargValue __PRIM_MUL(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  if(IS_INTEGER(self) && IS_INTEGER(args[0])) {
    return MARG_INTEGER(AS_INTEGER(self)->value * AS_INTEGER(args[0])->value);
  } else if(IS_INTEGER(self) && IS_FLOAT(args[0])) {
    return MARG_FLOAT(AS_INTEGER(self)->value * AS_FLOAT(args[0])->value);
  } else if(IS_FLOAT(self) && IS_INTEGER(args[0])) {
    return MARG_FLOAT(AS_FLOAT(self)->value * AS_INTEGER(args[0])->value);
  } else if(IS_FLOAT(self) && IS_FLOAT(args[0])) {
    return MARG_FLOAT(AS_FLOAT(self)->value * AS_FLOAT(args[0])->value);
  } else {
    return raise("TypeError: cannot multiply non-number values.");
  }
}

MargValue __PRIM_DIV(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  if(IS_INTEGER(args[0]) && AS_INTEGER(args[0])->value == 0) {
    return raise("Runtime Error: Division by zero");
  } else if(IS_FLOAT(args[0]) && AS_FLOAT(args[0])->value == 0.0) {
    return raise("Runtime Error: Division by zero");
  } else if(IS_INTEGER(self) && IS_INTEGER(args[0])) {
    return MARG_INTEGER(AS_INTEGER(self)->value / AS_INTEGER(args[0])->value);
  } else if(IS_INTEGER(self) && IS_FLOAT(args[0])) {
    return MARG_FLOAT(AS_INTEGER(self)->value / AS_FLOAT(args[0])->value);
  } else if(IS_FLOAT(self) && IS_INTEGER(args[0])) {
    return MARG_FLOAT(AS_FLOAT(self)->value / AS_INTEGER(args[0])->value);
  } else if(IS_FLOAT(self) && IS_FLOAT(args[0])) {
    return MARG_FLOAT(AS_FLOAT(self)->value / AS_FLOAT(args[0])->value);
  } else {
    return raise("TypeError: cannot divide non-number values.");
  }
}
