/* margaret */
#include "version.spec.h"

/* emitter */
#include "emitter/Emmiter.spec.h"

/* generic */
#include "generic/arithmetic.spec.h"
#include "generic/assignments.spec.h"
#include "generic/bitstrings.spec.h"
#include "generic/bitwise.spec.h"
#include "generic/booleans.spec.h"
#include "generic/characters.spec.h"
#include "generic/complex.spec.h"
#include "generic/conditionals.spec.h"
#include "generic/constants.spec.h"
#include "generic/conversions.spec.h"
#include "generic/date_time.spec.h"
#include "generic/errors.spec.h"
#include "generic/groups.spec.h"
#include "generic/headless_methods.spec.h"
#include "generic/identifiers.spec.h"
#include "generic/intervals.spec.h"
#include "generic/iterations.spec.h"
#include "generic/margaret_messages.spec.h"
#include "generic/messages.spec.h"
#include "generic/meta_evaluation.spec.h"
#include "generic/method_definition.spec.h"
#include "generic/numeric.spec.h"
#include "generic/postcard.spec.h"
#include "generic/rational.spec.h"
#include "generic/strings.spec.h"
#include "generic/tables.spec.h"
#include "generic/tensors.spec.h"
#include "generic/tuples.spec.h"
#include "generic/unicode.spec.h"
#include "generic/variables.spec.h"

/* lexer */
#include "lexer/alternate_to_dec.spec.h"
#include "lexer/Lexer.spec.h"
#include "lexer/token_types.spec.h"

/* loader */
#include "loader/Loader.spec.h"

/* opcode */
#include "opcode/instruction.spec.h"
#include "opcode/MargBitstring.spec.h"
#include "opcode/MargFloat.spec.h"
#include "opcode/MargInteger.spec.h"
#include "opcode/MargLabel.spec.h"
#include "opcode/MargMethod.spec.h"
#include "opcode/MargObject.spec.h"
#include "opcode/MargPrimitive.spec.h"
#include "opcode/MargSingletons.spec.h"
#include "opcode/MargString.spec.h"
#include "opcode/MargTable.spec.h"
#include "opcode/MargTensor.spec.h"
#include "opcode/MargTuple.spec.h"
#include "opcode/MargValue.spec.h"

/* optimizer */
#include "optimizer/Optimizer.spec.h"

/* parser */
#include "parser/Parser.spec.h"

/* scanner */
#include "scanner/Scanner.spec.h"

/* tokens */
#include "tokens/Token.spec.h"
#include "tokens/Type.spec.h"

/* vm */
#include "vm/vm.spec.h"

int main(void) {
  cspec_run_suite("all", {
    VersionSpec();

    EmmiterSpec();

    arithmetic_spec();
    assignments_spec();
    bitstrings_spec();
    bitwise_spec();
    booleans_spec();
    characters_spec();
    complex_spec();
    conditionals_spec();
    constants_spec();
    conversions_spec();
    date_time_spec();
    errors_spec();
    groups_spec();
    tables_spec();
    headless_methods_spec();
    identifiers_spec();
    intervals_spec();
    iterations_spec();
    margaret_messages_spec();
    messages_spec();
    meta_evaluation_spec();
    method_definition_spec();
    numeric_spec();
    postcard_spec();
    rational_spec();
    strings_spec();
    tensors_spec();
    tuples_spec();
    unicode_spec();
    variables_spec();

    alternate_to_dec_spec();
    LexerSpec();
    token_types_spec();

    LoaderSpec();

    instruction_spec();
    MargBitstringSpec();
    MargFloatSpec();
    MargIntegerSpec();
    MargLabelSpec();
    MargMethodSpec();
    MargObjectSpec();
    MargPrimitiveSpec();
    MargSingletonsSpec();
    MargStringSpec();
    MargTableSpec();
    MargTensorSpec();
    MargTupleSpec();
    MargValueSpec();

    OptimizerSpec();

    ParserSpec();

    ScannerSpec();

    TokenSpec();
    TypeSpec();

    VmSpec();
  });
}
