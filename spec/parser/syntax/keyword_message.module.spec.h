#ifndef __KEYWORD_MESSAGE_MODULE_SPEC_H_
#define __KEYWORD_MESSAGE_MODULE_SPEC_H_

#include "../../generic/_helpers.h"
#include "binary_message.module.spec.h"
#include "keyword_selector_chain.module.spec.h"

module(keyword_message, {
  keyword_selector_chain();
  binary_message();
})

#endif
