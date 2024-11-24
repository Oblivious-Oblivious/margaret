#ifndef __MARG_LABEL_H_
#define __MARG_LABEL_H_

#include "MargObject.h"

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
 * @brief Constructs a new label object
 * @param vm -> A pointer to the current VM
 * @param value -> The string representation of the label to store
 * @return MargLabel*
 */
MargLabel *marg_label_new(VM *vm, const char *value);

#endif
