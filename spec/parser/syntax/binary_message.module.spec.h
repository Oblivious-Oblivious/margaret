#ifndef __BINARY_MESSAGE_MODULE_SPEC_H_
#define __BINARY_MESSAGE_MODULE_SPEC_H_

#include "../../generic/_helpers.h"
#include "binary_selector_chain.module.spec.h"
#include "unary_message.module.spec.h"

module(binary_message, {
  binary_selector_chain();
  unary_message();
})

#endif
