// cspec
#include "../libs/cSpec/export/cSpec.h"

// margaret
#include "version.spec.h"

// emitter
#include "emitter/Emitter.spec.h"

// evaluator
#include "evaluator/Evaluator.spec.h"

// generic
#include "generic/arithmetic.spec.h"
#include "generic/assignments.spec.h"
#include "generic/bitstrings.spec.h"
#include "generic/bitwise.spec.h"
#include "generic/booleans.spec.h"
#include "generic/characters.spec.h"
#include "generic/code_as_data.spec.h"
#include "generic/complex.spec.h"
#include "generic/conditionals.spec.h"
#include "generic/constants.spec.h"
#include "generic/conversions.spec.h"
#include "generic/date_time.spec.h"
#include "generic/errors.spec.h"
#include "generic/groups.spec.h"
#include "generic/hashes.spec.h"
#include "generic/identifiers.spec.h"
#include "generic/intervals.spec.h"
#include "generic/iterations.spec.h"
#include "generic/margaret_messages.spec.h"
#include "generic/messages.spec.h"
#include "generic/meta_evaluation.spec.h"
#include "generic/method_definition.spec.h"
#include "generic/numeric.spec.h"
#include "generic/postcard.spec.h"
#include "generic/procs.spec.h"
#include "generic/rational.spec.h"
#include "generic/strings.spec.h"
#include "generic/symbols.spec.h"
#include "generic/tensors.spec.h"
#include "generic/tuples.spec.h"
#include "generic/variables.spec.h"

// inspector
#include "inspector/Inspector.spec.h"

// lexer
#include "lexer/alternate_to_dec.spec.h"
#include "lexer/Lexer.spec.h"

// opcode
#include "opcode/MargFloat.spec.h"
#include "opcode/MargHash.spec.h"
#include "opcode/MargInteger.spec.h"
#include "opcode/MargMethod.spec.h"
#include "opcode/MargObject.spec.h"
#include "opcode/MargProc.spec.h"
#include "opcode/MargString.spec.h"
#include "opcode/MargTensor.spec.h"
#include "opcode/MargValue.spec.h"

// optimizer
#include "optimizer/Optimizer.spec.h"

// parser
#include "parser/Parser.spec.h"

// scanner
#include "scanner/Scanner.spec.h"

// tokens
#include "tokens/Token.spec.h"
#include "tokens/TokenTable.spec.h"
#include "tokens/Type.spec.h"

// vm
#include "vm/byte_conversions.spec.h"
#include "vm/vm.spec.h"

spec_suite({
  VersionSpec();

  EmitterSpec();

  EvaluatorSpec();

  arithmetic_spec();
  assignments_spec();
  bitstrings_spec();
  bitwise_spec();
  booleans_spec();
  characters_spec();
  code_as_data_spec();
  complex_spec();
  conditionals_spec();
  constants_spec();
  conversions_spec();
  date_time_spec();
  errors_spec();
  groups_spec();
  hashes_spec();
  identifiers_spec();
  intervals_spec();
  iterations_spec();
  margaret_messages_spec();
  messages_spec();
  meta_evaluation_spec();
  method_definition_spec();
  numeric_spec();
  postcard_spec();
  procs_spec();
  rational_spec();
  strings_spec();
  symbols_spec();
  tensors_spec();
  tuples_spec();
  variables_spec();

  InspectorSpec();

  alternate_to_dec_spec();
  LexerSpec();

  MargFloatSpec();
  MargHashSpec();
  MargIntegerSpec();
  MargMethodSpec();
  MargObjectSpec();
  MargProcSpec();
  MargStringSpec();
  MargTensorSpec();
  MargValueSpec();

  OptimizerSpec();

  ParserSpec();

  ScannerSpec();

  TokenSpec();
  TokenTableSpec();
  TypeSpec();

  byte_conversions_spec();
  VmSpec();
});

int main(void) { run_spec_suite("failing"); }
