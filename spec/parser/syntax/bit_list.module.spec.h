#ifndef __BIT_LIST_MODULE_SPEC_H_
#define __BIT_LIST_MODULE_SPEC_H_

#include "../../generic/_helpers.h"
#include "bit.module.spec.h"

module(bit_list, {
  parse(
    "%(3::4)",
    vector_new(
      FM_INTEGER,
      string_new("3"),
      FM_INTEGER,
      string_new("4"),
      FM_BITSTRING,
      string_new("2")
    )
  );

  bit();
})

#endif
