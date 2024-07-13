#ifndef __LHS_MESSAGE_MODULE_SPEC_H_
#define __LHS_MESSAGE_MODULE_SPEC_H_

#include "../../generic/_helpers.h"
#include "lhs_selector.module.spec.h"
#include "literal.module.spec.h"

module(lhs_message, {
  lhs_selector();
  literal();
})

#endif
