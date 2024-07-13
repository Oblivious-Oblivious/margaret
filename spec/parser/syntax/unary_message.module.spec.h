#ifndef __UNARY_MESSAGE_MODULE_SPEC_H_
#define __UNARY_MESSAGE_MODULE_SPEC_H_

#include "../../generic/_helpers.h"
#include "lhs_message.module.spec.h"
#include "unary_selector_chain.module.spec.h"

module(unary_message, {
  unary_selector_chain();
  lhs_message();
})

#endif
