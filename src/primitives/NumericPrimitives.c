#include "NumericPrimitives.h"

MargValue __PRIM_NUMERIC_ADD(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  if(IS_INTEGER(args[0]) && IS_INTEGER(args[1])) {
    return MARG_INTEGER(
      AS_INTEGER(args[0])->value + AS_INTEGER(args[1])->value
    );
  } else if(IS_INTEGER(args[0]) && IS_FLOAT(args[1])) {
    return MARG_FLOAT(AS_INTEGER(args[0])->value + AS_FLOAT(args[1])->value);
  } else if(IS_FLOAT(args[0]) && IS_INTEGER(args[1])) {
    return MARG_FLOAT(AS_FLOAT(args[0])->value + AS_INTEGER(args[1])->value);
  } else if(IS_FLOAT(args[0]) && IS_FLOAT(args[1])) {
    return MARG_FLOAT(AS_FLOAT(args[0])->value + AS_FLOAT(args[1])->value);
  } else {
    return raise("TypeError: cannot add non-numeric values.");
  }
}

MargValue __PRIM_NUMERIC_SUB(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  if(IS_INTEGER(args[0]) && IS_INTEGER(args[1])) {
    return MARG_INTEGER(
      AS_INTEGER(args[0])->value - AS_INTEGER(args[1])->value
    );
  } else if(IS_INTEGER(args[0]) && IS_FLOAT(args[1])) {
    return MARG_FLOAT(AS_INTEGER(args[0])->value - AS_FLOAT(args[1])->value);
  } else if(IS_FLOAT(args[0]) && IS_INTEGER(args[1])) {
    return MARG_FLOAT(AS_FLOAT(args[0])->value - AS_INTEGER(args[1])->value);
  } else if(IS_FLOAT(args[0]) && IS_FLOAT(args[1])) {
    return MARG_FLOAT(AS_FLOAT(args[0])->value - AS_FLOAT(args[1])->value);
  } else {
    return raise("TypeError: cannot subtract non-numeric values.");
  }
}

MargValue __PRIM_NUMERIC_MUL(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  if(IS_INTEGER(args[0]) && IS_INTEGER(args[1])) {
    return MARG_INTEGER(
      AS_INTEGER(args[0])->value * AS_INTEGER(args[1])->value
    );
  } else if(IS_INTEGER(args[0]) && IS_FLOAT(args[1])) {
    return MARG_FLOAT(AS_INTEGER(args[0])->value * AS_FLOAT(args[1])->value);
  } else if(IS_FLOAT(args[0]) && IS_INTEGER(args[1])) {
    return MARG_FLOAT(AS_FLOAT(args[0])->value * AS_INTEGER(args[1])->value);
  } else if(IS_FLOAT(args[0]) && IS_FLOAT(args[1])) {
    return MARG_FLOAT(AS_FLOAT(args[0])->value * AS_FLOAT(args[1])->value);
  } else {
    return raise("TypeError: cannot multiply non-numeric values.");
  }
}

MargValue __PRIM_NUMERIC_DIV(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  if(IS_INTEGER(args[1]) && AS_INTEGER(args[1])->value == 0) {
    return raise("Runtime Error: Division by zero");
  } else if(IS_FLOAT(args[1]) && AS_FLOAT(args[1])->value == 0.0) {
    return raise("Runtime Error: Division by zero");
  } else if(IS_INTEGER(args[0]) && IS_INTEGER(args[1])) {
    return MARG_INTEGER(
      AS_INTEGER(args[0])->value / AS_INTEGER(args[1])->value
    );
  } else if(IS_INTEGER(args[0]) && IS_FLOAT(args[1])) {
    return MARG_FLOAT(AS_INTEGER(args[0])->value / AS_FLOAT(args[1])->value);
  } else if(IS_FLOAT(args[0]) && IS_INTEGER(args[1])) {
    return MARG_FLOAT(AS_FLOAT(args[0])->value / AS_INTEGER(args[1])->value);
  } else if(IS_FLOAT(args[0]) && IS_FLOAT(args[1])) {
    return MARG_FLOAT(AS_FLOAT(args[0])->value / AS_FLOAT(args[1])->value);
  } else {
    return raise("TypeError: cannot divide non-numeric values.");
  }
}

MargValue __PRIM_NUMERIC_GREATER(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  if(IS_INTEGER(args[0]) && IS_INTEGER(args[1])) {
    if(AS_INTEGER(args[0])->value > AS_INTEGER(args[1])->value) {
      return MARG_TRUE;
    } else {
      return MARG_FALSE;
    }
  } else if(IS_FLOAT(args[0]) && IS_FLOAT(args[1])) {
    if(AS_FLOAT(args[0])->value > AS_FLOAT(args[1])->value) {
      return MARG_TRUE;
    } else {
      return MARG_FALSE;
    }
  } else if(IS_INTEGER(args[0]) && IS_FLOAT(args[1])) {
    if(AS_INTEGER(args[0])->value > AS_FLOAT(args[1])->value) {
      return MARG_TRUE;
    } else {
      return MARG_FALSE;
    }
  } else if(IS_FLOAT(args[0]) && IS_INTEGER(args[1])) {
    if(AS_FLOAT(args[0])->value > AS_INTEGER(args[1])->value) {
      return MARG_TRUE;
    } else {
      return MARG_FALSE;
    }
  } else {
    return raise("TypeError: cannot compare non-numeric values.");
  }
}

MargValue __PRIM_NUMERIC_LESS(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  if(IS_INTEGER(args[0]) && IS_INTEGER(args[1])) {
    if(AS_INTEGER(args[0])->value < AS_INTEGER(args[1])->value) {
      return MARG_TRUE;
    } else {
      return MARG_FALSE;
    }
  } else if(IS_FLOAT(args[0]) && IS_FLOAT(args[1])) {
    if(AS_FLOAT(args[0])->value < AS_FLOAT(args[1])->value) {
      return MARG_TRUE;
    } else {
      return MARG_FALSE;
    }
  } else if(IS_INTEGER(args[0]) && IS_FLOAT(args[1])) {
    if(AS_INTEGER(args[0])->value < AS_FLOAT(args[1])->value) {
      return MARG_TRUE;
    } else {
      return MARG_FALSE;
    }
  } else if(IS_FLOAT(args[0]) && IS_INTEGER(args[1])) {
    if(AS_FLOAT(args[0])->value < AS_INTEGER(args[1])->value) {
      return MARG_TRUE;
    } else {
      return MARG_FALSE;
    }
  } else {
    return raise("TypeError: cannot compare non-numeric values.");
  }
}
