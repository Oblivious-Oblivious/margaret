#ifndef __MARG_OBJECT_H_
#define __MARG_OBJECT_H_

#include "../vm/vm.h"
#include "MargValueType.h"

/**
 * @brief A representation of user-defined object
 * @param is_marked -> If true, the object is read for garbage collection
 * @param next -> Turns the struct into a linked list of objects
 *
 * @param bound_vm -> A pointer to the current VM
 *
 * @param name -> Name of the object
 * @param parent -> Pointer to the parent object (Sets up delegation chain)
 * @param instance_variables -> Object scoped @variables
 * @param messages -> A table for messages pointing to a vector of methods
 */
typedef struct MargObject {
  bool is_marked;
  struct MargObject *next;

  VM *bound_vm;

  const char *name;
  size_t name_hash;
  struct MargObject *proto;
  MargValue instance_registers[MAX_REGISTERS];
  uint32_t instance_index;
  EmeraldsTable instance_variables;
  EmeraldsTable messages;
  EmeraldsTable primitives;
} MargObject;

/**
 * @brief An object representation of MARG_INTEGER
 * @param _ -> Inherted object properties
 */
typedef struct MargInteger {
  MargObject _;
  ptrdiff_t value;
} MargInteger;

/**
 * @brief An object representation of MARG_FLOAT
 * @param _ -> Inherted object properties
 * @param value -> Actual double value of Float object
 */
typedef struct MargFloat {
  MargObject _;
  double value;
} MargFloat;

/**
 * @brief An object representation of MARG_SYMBOL
 * @param _ -> Inherited object properties
 * ...
 */
typedef struct MargSymbol {
  MargObject _;
  char *value;
} MargSymbol;

/**
 * @brief An object representation of MARG_LABEL
 * @param _ -> Inherited object properties
 * @param value -> The string representation of the label
 * @param index -> The index of the bytecode array to jump to
 */
typedef struct MargLabel {
  MargObject _;
  size_t value;
  const char *name;
} MargLabel;

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
 * @brief Defines a tensor primitive
 * @param _ -> Inherited MargObject properties
 * @param value -> A MargValue pointer array
 */
typedef struct MargTensor {
  MargObject _;
  MargValue *value;
} MargTensor;

/**
 * @brief Defines a tuple representation for Margaret
 * @param _ -> Inherited object properties
 * @param value -> A pointer to the tuple values
 */
typedef struct MargTuple {
  MargObject _;
  MargValue *value;
} MargTuple;

/**
 * @brief Defines a table data structure
 * @param _ -> Inherited MargObject properties
 * @param value -> A pointer to the table table
 */
typedef struct MargTable {
  MargObject _;
  EmeraldsTable value;
} MargTable;

/**
 * @brief Defines a bitstring representation for Margaret
 * @param _ -> Inherited object properties
 */
typedef struct MargBitstring {
  MargObject _;
  MargTensor *bits;
  MargTensor *sizes;
} MargBitstring;

/**
 * @brief Defines a MargMethod object
 * @param _ -> Inherited object properties
 *
 * @param bound_object -> Points to bound object this method is defined under
 * @param bound_method -> Points to the enclosing method
 *
 * @param message_name -> Name of current message derived by the parsed method
 *
 * @param arguments -> A Tensor that saves formal argument names
 * @param constants -> A Tensor that saves intermediate values
 * @param local_variables -> A table for method-local variables
 * @param bytecode -> Bytecode array
 *
 * @param ip -> Instruction Pointer
 * @param sp -> Stack pointer
 */
typedef struct MargMethod {
  MargObject _;

  MargObject *bound_object;
  struct MargMethod *bound_method;

  const char *message_name;

  MargValue local_registers[MAX_REGISTERS];
  uint32_t local_index;
  MargValue *constants;
  EmeraldsTable local_variables;

  Instruction *bytecode;
  Instruction ip;
} MargMethod;

typedef MargValue (*MargPrimitiveFunction)(VM *, MargValue, MargValue);

/**
 * @brief Defines C-implemented primitives
 * @param _ -> Inherited object properties
 *
 * @param function -> C function pointer
 * @param primitive_name -> Name of primitive
 */
typedef struct MargPrimitive {
  MargObject _;

  MargPrimitiveFunction function;
  const char *primitive_name;
} MargPrimitive;

/**
 * @brief Creates a new object instance
 * @param vm -> Current VM
 * @param size -> Size of the pointer
 * @param proto -> Value of the prototype object
 * @param name -> Name of the object
 * @return MargObject*
 */
MargObject *
marg_object_init(VM *vm, size_t size, MargValue proto, const char *name);

/**
 * @brief Constructs a new integer object
 * @param vm -> A pointer to the current VM
 * @param value -> Actual C int value
 * @return MargInteger*
 */
MargInteger *marg_integer_init(VM *vm, ptrdiff_t value);

/**
 * @brief Constructs a new float object
 * @param vm -> A pointer to the current VM
 * @param value -> Actual C double value
 * @return MargFloat*
 */
MargFloat *marg_float_init(VM *vm, double value);

/**
 * @brief Constructs a new symbol object
 * @param vm -> A pointer to the current VM
 * @param value -> The identifier representation of the symbol
 * @return MargSymbol*
 */
MargSymbol *marg_symbol_init(VM *vm, char *value);

/**
 * @brief Constructs a new label object
 * @param vm -> A pointer to the current VM
 * @param value -> The string representation of the label to store
 * @return MargLabel*
 */
MargLabel *marg_label_init(VM *vm, const char *value);

/**
 * @brief Creates a new MargString as an object
 * @param vm -> Current VM
 * @param value -> Initial characters
 * @return MargString* -> Newly created string
 */
MargString *marg_string_init(VM *vm, const char *value);

/**
 * @brief Creates a new empty MargTensor without initial elements
 * @param vm -> A pointer to the current VM
 * @return MargTensor*
 */
MargTensor *marg_tensor_init(VM *vm);

/**
 * @brief Creates a new tuple
 * @param vm -> A pointer to the current VM
 * @param initial_size -> User chooses starting length
 * @return MargTuple*
 */
MargTuple *marg_tuple_init(VM *vm);

/**
 * @brief Creates a new emprt MargTable
 * @param vm -> A pointer to the current VM
 * @return MargTable*
 */
MargTable *marg_table_init(VM *vm);

/**
 * @brief Creates a new bitstring
 * @param vm -> A pointer to the current VM
 * @param initial_size -> User chooses starting length
 * @return MargBitstring*
 */
MargBitstring *marg_bitstring_init(VM *vm);

/**
 * @brief Creates a new MargMethod object
 * @param vm -> Current VM
 * @param bound_object
 * @param bound_method
 * @param message_name
 * @return MargMethod*
 */
MargMethod *marg_method_init(
  VM *vm,
  MargObject *bound_object,
  MargMethod *bound_method,
  const char *message_name
);

MargPrimitive *marg_primitive_init(
  VM *vm, const char *primitive_name, MargPrimitiveFunction function
);

#endif
