#include "instruction.h"

MargBitstring *marg_bitstring_new(VM *vm) {
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargBitstring), G("$Bitstring"), string_new("")
  );
  MargBitstring *self = (MargBitstring *)obj;

  self->bits  = marg_tensor_new(vm);
  self->sizes = marg_tensor_new(vm);

  return self;
}

void marg_bitstring_add(MargBitstring *self, MargValue bit, MargValue size) {
  marg_tensor_add(self->bits, bit);
  marg_tensor_add(self->sizes, size);
}

size_t marg_bitstring_size(MargBitstring *self) {
  return marg_tensor_size(self->bits);
}
