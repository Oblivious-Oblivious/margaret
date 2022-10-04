#ifndef __EVALUATOR_SPEC_H_
#define __EVALUATOR_SPEC_H_

#include "../../src/ast/Bytecode.h"
#include "../../src/evaluator/Evaluator.h"
#include "../../src/lexer/Lexer.h"
#include "../../src/parser/Parser.h"

#include "../_helpers.h"

module(EvaluatorSpec, {
//     it("emits for a simple message", {
//         evalcodes("2 + 3", "5");
//     });

    it("emits for groups", {
        evalcodes("()", "nil");
        evalcodes("(1, 2, 3)", "3");
        evalcodes("(1, 2, (10, 20, 30), 3)", "3");
        evalcodes("(1, \"2\", c, 42.42)", "42.42");
    });

    it("emits for integers", {
        evalcodes("0", "0");
        evalcodes("-0", "0");
        evalcodes("+0", "0");
        evalcodes("1", "1");
        evalcodes("+1", "1");
        evalcodes("-1", "-1");
        evalcodes("2", "2");
        evalcodes("+2", "2");
        evalcodes("42", "42");
        evalcodes("-42", "-42");
        evalcodes("+42", "42");
        evalcodes("4_200", "4200");
        evalcodes("-4_200", "-4200");
        evalcodes("4____20__0", "4200");
        evalcodes("-4____20__0", "-4200");
        evalcodes("+4____20__0", "4200");
    });

    it("emits for floats", {
        evalcodes("42.0", "42.0");
        evalcodes("-42.0", "-42.0");
        evalcodes("986513.00056129", "986513.00056129");
        evalcodes("-986513.00056129", "-986513.00056129");
        evalcodes("0.1_2_3", "0.123");
        evalcodes("0.1__23", "0.123");
    });

    it("emits for binaries", {
        evalcodes("0b0110", "6");
        evalcodes("0B10", "2");
        evalcodes("-0b0110", "-6");
        evalcodes("-0B10", "-2");
    });

    it("emits for hexadecimals", {
        evalcodes("0xbeef", "48879");
        evalcodes("-0xbeEf", "-48879");
        evalcodes("0X0427", "1063");
        evalcodes("-0X0427", "-1063");
        evalcodes("0xbe____e___f", "48879");
    });

    it("emits for octals", {
        evalcodes("0o741", "481");
        evalcodes("-0o741", "-481");
        evalcodes("0O0210", "136");
        evalcodes("-0O0210", "-136");
    });

    it("emits for characters", {
        evalcodes("'a'", "'a'");
        evalcodes("'\n'", "'\n'");
    });

    it("emits for strings", {
        evalcodes("\"string\"", "\"string\"");
        evalcodes("\"foo\tbar\"", "\"foo\tbar\"");
        evalcodes("\"a string lit\"", "\"a string lit\"");
        evalcodes("\"str\"", "\"str\"");
    });

})

#endif
