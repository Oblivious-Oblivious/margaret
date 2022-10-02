#ifndef __LEXER_SPEC_H_
#define __LEXER_SPEC_H_

#include "../../src/lexer/Lexer.h"
#include "../cSpec.h"

module(LexerSpec, {
    describe("Lexer", {
        it("contains the input text, lexer position and current character", {
            Lexer *l = lexer_new("file.marg", marg_string_new("(42 factorial)"));
            assert_that_charptr(l->filename equals to "file.marg");
            assert_that_charptr(marg_string_get(l->text) equals to "(42 factorial)");
            assert_that_int(l->pos equals to -1);
            assert_that_int(l->lineno equals to 1);
        });

        context("on #next_character", {
            it("properly advances characters in the array", {
                Lexer *l = lexer_new("file.marg", marg_string_new("(42 factorial)"));

                char current_char = lexer_next_character(l);
                assert_that(current_char is '(');
                assert_that_int(l->pos equals to 0);

                current_char = lexer_next_character(l);
                assert_that(current_char is '4');
                assert_that_int(l->pos equals to 1);

                current_char = lexer_next_character(l);
                current_char = lexer_next_character(l);
                current_char = lexer_next_character(l);
                assert_that(current_char is 'f');
                assert_that_int(l->pos equals to 4);
            });

            it("reads all characters until the list ends", {
                Lexer *l = lexer_new("file.marg", marg_string_new("12345"));
        
                char c1 = lexer_next_character(l);
                char c2 = lexer_next_character(l);
                char c3 = lexer_next_character(l);
                char c4 = lexer_next_character(l);
                char c5 = lexer_next_character(l);
                assert_that(c1 is '1');
                assert_that(c2 is '2');
                assert_that(c3 is '3');
                assert_that(c4 is '4');
                assert_that(c5 is '5');

                // String reaches EOF
                char c6 = lexer_next_character(l);
                assert_that_int(c6 equals to '\0');
            });
        });

        context("on #peek_character", {
            it("peeks the next character from the list", {
                Lexer *l = lexer_new("file.marg", marg_string_new("(42 factorial)"));

                char c1 = lexer_peek_character(l, 1);
                char c2 = lexer_peek_character(l, 2);
                char c3 = lexer_peek_character(l, 3);
                char c4 = lexer_peek_character(l, 4);
                char c5 = lexer_peek_character(l, 5);

                assert_that(c1 is '(');
                assert_that(c2 is '4');
                assert_that(c3 is '2');
                assert_that(c4 is ' ');
                assert_that(c5 is 'f');
            });
        });

        context("on string extensions", {
            it("matches regular expressions", {
                assert_that(regex_matches(' ', REGEX_WHITESPACE));
                assert_that(regex_matches('\r', REGEX_WHITESPACE));
                assert_that(regex_matches('\n', REGEX_NEWLINE));
                assert_that(regex_matches('9', REGEX_NUMBER));
                assert_that(regex_matches('k', REGEX_LETTER));
                assert_that(regex_matches('+', REGEX_MESSAGE_SYMBOL));
                assert_that(regex_matches('?', REGEX_ID_SYMBOL));
                assert_that(regex_matches('!', REGEX_ID_SYMBOL));
                assert_that(regex_matches('{', REGEX_SYNTAX_SYMBOL));
                assert_that(regex_matches('\'', REGEX_SINGLE_QUOTE));
                assert_that(regex_matches('"', REGEX_DOUBLE_QUOTE));
            });
        });

        it("prints error messages", {
            Lexer *l = lexer_new("file.marg", marg_string_new("(42 factorial)"));
            void *response = lexer_error(l, "random exception", marg_string_new(""));
            assert_that(response is NULL);
        });

        context("on #make_tokens", {
            it("correctly counts the number of lines", {
                Lexer *l = lexer_new("file.marg", marg_string_new("(42 factorial\nx = 2 + 3\ny = 5)"));
                lexer_make_tokens(l);

                assert_that_int(l->lineno equals to 3);
            });

            it("tokenizes symbols", {
                Lexer *l = lexer_new("file.marg", marg_string_new("(@ $ % ^ & *)"));
                TokenTable *tokens = lexer_make_tokens(l);
                assert_that_int(token_table_size(tokens) equals to 9);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 3)->value) equals to "%");
            });

            it("tokenizes integers", {
                TokenTable *tokens = lexer_make_tokens(lexer_new("file.marg", marg_string_new("(42 msg)")));
                assert_that_charptr(marg_string_get(token_table_get(tokens, 1)->value) equals to "42");
                assert_that_int(token_table_get(tokens, 1)->type equals to TOKEN_INTEGER);
                assert_that_int(token_table_get(tokens, 1)->line_number equals to 1);

                tokens = lexer_make_tokens(lexer_new("file.marg", marg_string_new("4_200")));
                assert_that_charptr(marg_string_get(token_table_get(tokens, 0)->value) equals to "4_200");
                tokens = lexer_make_tokens(lexer_new("file.marg", marg_string_new("4_2_0_0")));
                assert_that_charptr(marg_string_get(token_table_get(tokens, 0)->value) equals to "4_2_0_0");
            });

            it("tokenizes zero", {
                Lexer *l = lexer_new("file.marg", marg_string_new("(0 is_zero?)"));
                TokenTable *tokens = lexer_make_tokens(l);

                assert_that_charptr(marg_string_get(token_table_get(tokens, 1)->value) equals to "0");
                assert_that_int(token_table_get(tokens, 1)->type equals to TOKEN_INTEGER);
                assert_that_int(token_table_get(tokens, 1)->line_number equals to 1);
            });

            it("draws an error when trying to tokenize an integer starting with 0", {
                Lexer *l = lexer_new("file.marg", marg_string_new("042 msg"));
                TokenTable *table = lexer_make_tokens(l);
                assert_that(token_table_get(table, 0) is NULL);
            });

            it("tokenizes floats", {
                Lexer *l = lexer_new("file.marg", marg_string_new("0.0"));
                TokenTable *tokens = lexer_make_tokens(l);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 0)->value) equals to "0.0");
                assert_that_int(token_table_get(tokens, 0)->type equals to TOKEN_FLOAT);
                assert_that_int(token_table_get(tokens, 1)->line_number equals to 1);

                l = lexer_new("file.marg", marg_string_new("(42.7 msg)"));
                tokens = lexer_make_tokens(l);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 1)->value) equals to "42.7");
                assert_that_int(token_table_get(tokens, 1)->type equals to TOKEN_FLOAT);
                assert_that_int(token_table_get(tokens, 1)->line_number equals to 1);

                l = lexer_new("file.marg", marg_string_new("(0.7 msg)"));
                tokens = lexer_make_tokens(l);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 1)->value) equals to "0.7");
                assert_that_int(token_table_get(tokens, 1)->type equals to TOKEN_FLOAT);
                assert_that_int(token_table_get(tokens, 1)->line_number equals to 1);

                l = lexer_new("file.marg", marg_string_new("(0.7+0.5+0.23)"));
                tokens = lexer_make_tokens(l);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 1)->value) equals to "0.7");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 2)->value) equals to "+");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 3)->value) equals to "0.5");

                l = lexer_new("file.marg", marg_string_new("(.7 msg)"));
                tokens = lexer_make_tokens(l);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 0)->value) equals to "(");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 1)->value) equals to ".");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 2)->value) equals to "7");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 3)->value) equals to "msg");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 4)->value) equals to ")");

                l = lexer_new("file.marg", marg_string_new("(124.0 msg)"));
                tokens = lexer_make_tokens(l);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 1)->value) equals to "124.0");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 2)->value) equals to "msg");
            });

            it("tokenizes binary literals", {
                Lexer *l = lexer_new("file.marg", marg_string_new("(0b1010 + 0B0100)"));
                TokenTable *tokens = lexer_make_tokens(l);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 0)->value) equals to "(");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 1)->value) equals to "0b1010");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 2)->value) equals to "+");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 3)->value) equals to "0b0100");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 4)->value) equals to ")");

                assert_that_int(token_table_get(tokens, 1)->type equals to TOKEN_INTEGER);
                assert_that_int(token_table_get(tokens, 3)->type equals to TOKEN_INTEGER);
            });

            it("tokenizes hexadecimal literals", {
                Lexer *l = lexer_new("file.marg", marg_string_new("(0xfeed42 + 0Xbeef41)"));
                TokenTable *tokens = lexer_make_tokens(l);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 0)->value) equals to "(");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 1)->value) equals to "0xfeed42");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 2)->value) equals to "+");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 3)->value) equals to "0xbeef41");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 4)->value) equals to ")");

                assert_that_int(token_table_get(tokens, 1)->type equals to TOKEN_INTEGER);
                assert_that_int(token_table_get(tokens, 3)->type equals to TOKEN_INTEGER);
            });

            it("tokenizes octal literals", {
                Lexer *l = lexer_new("file.marg", marg_string_new("(0o752 + 0O52)"));
                TokenTable *tokens = lexer_make_tokens(l);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 0)->value) equals to "(");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 1)->value) equals to "0o752");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 2)->value) equals to "+");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 3)->value) equals to "0o52");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 4)->value) equals to ")");

                assert_that_int(token_table_get(tokens, 1)->type equals to TOKEN_INTEGER);
                assert_that_int(token_table_get(tokens, 3)->type equals to TOKEN_INTEGER);
            });

            it("tokenizes character literals", {
                Lexer *l = lexer_new("file.marg", marg_string_new("('a' puts)"));
                TokenTable *tokens = lexer_make_tokens(l);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 1)->value) equals to "'a'");
                assert_that_int(token_table_get(tokens, 1)->type equals to TOKEN_CHAR);
            });

            it("tokenizes string literals", {
                Lexer *l = lexer_new("file.marg", marg_string_new("(\"hello\" puts)"));
                TokenTable *tokens = lexer_make_tokens(l);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 1)->value) equals to "\"hello\"");

                l = lexer_new("file.marg", marg_string_new("(\"multi\nline\nstring\" puts)"));
                tokens = lexer_make_tokens(l);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 1)->value) equals to "\"multi\nline\nstring\"");
            });

            it("tokenizes identifiers", {
                Lexer *l = lexer_new("file.marg", marg_string_new("(42 factorial\nx = (2 times: 3)\n3 plus: 4)"));
                TokenTable *tokens = lexer_make_tokens(l);
                assert_that_int(token_table_size(tokens) equals to 17);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 2)->value) equals to "factorial");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 3)->value) equals to "x");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 7)->value) equals to "times");
                assert_that_charptr(marg_string_get(token_table_get(tokens, 12)->value) equals to "plus");
            });

            it("tokenizes identifiers starting with an underscore", {
                Lexer *l = lexer_new("file.marg", marg_string_new("((1 2 3) __msg)"));
                TokenTable *tokens = lexer_make_tokens(l);
                assert_that_charptr(marg_string_get(token_table_get(tokens, 6)->value) equals to "__msg");
            });
        });
    });
})

#endif
