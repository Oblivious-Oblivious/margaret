#ifndef __SPEC_HELPER_H_
#define __SPEC_HELPER_H_

// margaret
#include "version.spec.h"

// base
#include "base/alternate_to_dec.spec.h"
#include "base/boolean.spec.h"
#include "base/file_loader.spec.h"
#include "base/memory.spec.h"
#include "base/string.spec.h"
#include "base/vector.spec.h"

// bytecode
#include "bytecode/FormalAST.spec.h"

// emitter
#include "emitter/Emitter.spec.h"

// evaluator
#include "evaluator/Evaluator.spec.h"

// generic
#include "generic/arithmetic.spec.h"
#include "generic/assignments.spec.h"
#include "generic/bitwise.spec.h"
#include "generic/bitstrings.spec.h"
#include "generic/booleans.spec.h"
#include "generic/c_functions.spec.h"
#include "generic/classes.spec.h"
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
#include "lexer/Lexer.spec.h"

// opcode
#include "opcode/MargFalse.spec.h"
#include "opcode/MargHash.spec.h"
#include "opcode/MargObject.spec.h"
#include "opcode/MargString.spec.h"
#include "opcode/MargTrue.spec.h"
#include "opcode/MargValue.spec.h"

// optimizer
#include "optimizer/Optimizer.spec.h"

// parser
#include "parser/Parser.spec.h"

// tokens
#include "tokens/Token.spec.h"
#include "tokens/TokenTable.spec.h"
#include "tokens/Type.spec.h"

// vm
#include "vm/vm.spec.h"

#include "cSpec.h"

spec_suite({
    VersionSpec();

    alternate_to_dec_spec();
    boolean_spec();
    file_loader_spec();
    memory_spec();
    string_spec();
    vector_spec();

    FormalASTSpec();

    EmitterSpec();

    EvaluatorSpec();

    arithmetic_spec();
    assignments_spec();
    bitwise_spec();
    bitstrings_spec();
    booleans_spec();
    c_functions_spec();
    classes_spec();
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
    procs_spec();
    rational_spec();
    strings_spec();
    symbols_spec();
    tensors_spec();
    tuples_spec();
    variables_spec();

    InspectorSpec();

    LexerSpec();

    MargFalseSpec();
    MargHashSpec();
    MargObjectSpec();
    MargStringSpec();
    MargTrueSpec();
    MargValueSpec();

    OptimizerSpec();

    ParserSpec();

    TokenSpec();
    TokenTableSpec();
    TypeSpec();

    VmSpec();
})

int main(void) {
    run_spec_suite("failing");
}

#endif
