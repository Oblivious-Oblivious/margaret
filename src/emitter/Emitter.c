#include "Emitter.h"

#include <string.h> /* strtoll, strtold */

#include "../inspector/Inspector.h"

#include "../base/chunk.h"
#include "../opcode/Opcodes.h"
#include "../opcode/MargValue.h"
#include "../opcode/MargInteger.h"
#include "../opcode/MargFloat.h"
#include "../opcode/MargString.h"
#include "../opcode/MargTensor.h"
#include "../opcode/MargProc.h"
#include "../vm/byte_conversions.h"

#define switch_opcode_case(opstr) if(string_equals(opcode, (opstr)))
#define opcode_case(opstr) else if(string_equals(opcode, (opstr)))

#define switch_unary_case(unarystr) if(string_equals(unary_name, string_new((unarystr))))
#define unary_case(unarystr) else if(string_equals(unary_name, string_new((unarystr))))
#define default_unary_case else

#define switch_binary_case(binarystr) if(string_equals(binary_name, string_new((binarystr))))
#define binary_case(binarystr) else if(string_equals(binary_name, string_new((binarystr))))
#define default_binary_case else

#define switch_keyword_case(keywordstr) if(string_equals(keyword_name, string_new((keywordstr))))
#define keyword_case(keywordstr) else if(string_equals(keyword_name, string_new((keywordstr))))
#define default_keyword_case else

#define emit_byte(byte) chunk_add(vm->current->bytecode, (byte), 123)

#define emit_bytes2(byte1, byte2) do { \
    emit_byte((byte1)); \
    emit_byte((byte2)); \
} while(0)

#define emit_bytes3(byte1, byte2, byte3) do { \
    emit_byte((byte1)); \
    emit_byte((byte2)); \
    emit_byte((byte3)); \
} while(0)

#define emit_bytes4(byte1, byte2, byte3, byte4) do { \
    emit_byte((byte1)); \
    emit_byte((byte2)); \
    emit_byte((byte3)); \
    emit_byte((byte4)); \
} while(0)

#define emit_possible_long_op(opcode) do { \
    if(chunk_temporaries_size(vm->current->bytecode) < 256) \
        chunk_add(vm->current->bytecode, (opcode), 123); \
    else \
        chunk_add(vm->current->bytecode, (opcode##_LONG), 123); \
} while(0)

#define emit_temporary(temporary) do { \
    uint32_t temporary_index; \
    make_temporary(vm, (temporary), &temporary_index); \
    add_temporary(vm, temporary_index); \
} while(0)

#define make_temporary(vm, temporary, index) \
    chunk_temporaries_add((vm)->current->bytecode, (temporary), (index));

#define add_temporary(vm, temporary_index) \
    __add_temporary_function(vm, temporary_index, 256+1);
#define add_premade_temporary(vm, temporary_index) \
    __add_temporary_function(vm, temporary_index, 256);

static void __add_temporary_function(VM *vm, uint32_t temporary_index, uint16_t upper_bound) {
    if(chunk_temporaries_size(vm->current->bytecode) < upper_bound) {
        emit_byte((uint8_t)temporary_index);
    }
    else {
        uint8_t *temporary_index_in_bytes = dword_to_bytes(temporary_index);
        emit_bytes4(
            temporary_index_in_bytes[0],
            temporary_index_in_bytes[1],
            temporary_index_in_bytes[2],
            temporary_index_in_bytes[3]
        );
    }
}

VM *emitter_emit(VM *vm, vector *formal_bytecode) {
    MargObject *marg_object = AS_OBJECT(table_get(&vm->global_variables, MARG_STRING("$Margaret")));
    MargMethod *main_method = AS_METHOD(table_get(&marg_object->messages, MARG_STRING("main:")));
    vm->current->bytecode = chunk_new();
    vm->current = main_method->proc;

    size_t bytecode_size = vector_size(formal_bytecode);
    for(size_t ip = 0; ip < bytecode_size; ip++) {
        string *opcode = vector_get(formal_bytecode, ip);

        switch_opcode_case(FM_POP) {
            emit_byte(OP_POP);
        }

        opcode_case(FM_LOCAL) {
            string *variable_name = vector_get(formal_bytecode, ++ip);
            MargValue temporary = MARG_STRING(variable_name->str);
            emit_possible_long_op(OP_GET_LOCAL);
            emit_temporary(temporary);
        }
        opcode_case(FM_INSTANCE) {
            string *variable_name = vector_get(formal_bytecode, ++ip);
            MargValue temporary = MARG_STRING(variable_name->str);
            emit_possible_long_op(OP_GET_INSTANCE);
            emit_temporary(temporary);
        }
        opcode_case(FM_GLOBAL) {
            string *variable_name = vector_get(formal_bytecode, ++ip);
            MargValue temporary = MARG_STRING(variable_name->str);
            emit_possible_long_op(OP_GET_GLOBAL);
            emit_temporary(temporary);
        }

        opcode_case(FM_STORE_LOCAL) {
            string *variable_name = vector_get(formal_bytecode, ++ip);
            emit_possible_long_op(OP_SET_LOCAL);
            emit_temporary(MARG_STRING(variable_name->str));
        }
        opcode_case(FM_STORE_INSTANCE) {
            string *variable_name = vector_get(formal_bytecode, ++ip);
            emit_possible_long_op(OP_SET_INSTANCE);
            emit_temporary(MARG_STRING(variable_name->str));
        }
        opcode_case(FM_STORE_GLOBAL) {
            string *variable_name = vector_get(formal_bytecode, ++ip);
            emit_possible_long_op(OP_SET_GLOBAL);
            emit_temporary(MARG_STRING(variable_name->str));
        }

        opcode_case(FM_NIL) {
            emit_byte(OP_PUT_NIL);
        }
        opcode_case(FM_TRUE) {
            emit_byte(OP_PUT_TRUE);
        }
        opcode_case(FM_FALSE) {
            emit_byte(OP_PUT_FALSE);
        }

        opcode_case(FM_SELF) {}
        opcode_case(FM_SUPER) {}

        // TODO Distinguish normal number from big numbers
        opcode_case(FM_INTEGER) {
            string *temporary_str = vector_get(formal_bytecode, ++ip);
            char *end; long long integer = strtoll(string_get(temporary_str), &end, 10);
            if(integer == -1)
                emit_byte(OP_PUT_MINUS_1);
            else if(integer == 0)
                emit_byte(OP_PUT_0);
            else if(integer == 1)
                emit_byte(OP_PUT_1);
            else if(integer == 2)
                emit_byte(OP_PUT_2);
            else {
                emit_possible_long_op(OP_PUT_OBJECT);
                emit_temporary(MARG_INTEGER(integer));
            }
        }
        opcode_case(FM_FLOAT) {
            char *end;
            string *temporary_str = vector_get(formal_bytecode, ++ip);
            MargValue temporary = MARG_FLOAT(strtold(string_get(temporary_str), &end));
            emit_possible_long_op(OP_PUT_OBJECT);
            emit_temporary(temporary);
        }

        opcode_case(FM_STRING) {
            string *temporary_str = vector_get(formal_bytecode, ++ip);
            char *chars = string_get(temporary_str);
            size_t size = string_size(temporary_str);

            MargValue interned = MARG_STRING_INTERNED(chars, size);
            emit_possible_long_op(OP_PUT_OBJECT);

            if(IS_NOT_INTERNED(interned)) {
                interned = MARG_STRING(chars);

                uint32_t temporary_index;
                make_temporary(vm, interned, &temporary_index);
                add_temporary(vm, temporary_index);

                table_set(&vm->interned_strings, interned, MARG_INTEGER(temporary_index));
            }
            else {
                uint32_t temporary_index;
                make_temporary(vm, interned, &temporary_index);
                add_temporary(vm, temporary_index);
            }
        }

        opcode_case(FM_TENSOR) {
            char *end;
            string *number_of_elements = vector_get(formal_bytecode, ++ip);
            MargValue temporary = MARG_INTEGER(strtoll(string_get(number_of_elements), &end, 10));
            emit_possible_long_op(OP_PUT_TENSOR);
            emit_temporary(temporary);
        }
        opcode_case(FM_TUPLE) {}
        opcode_case(FM_HASH) {
            char *end;
            string *number_of_elements = vector_get(formal_bytecode, ++ip);
            MargValue temporary = MARG_INTEGER(strtoll(string_get(number_of_elements), &end, 10));
            emit_possible_long_op(OP_PUT_HASH);
            emit_temporary(temporary);
        }
        opcode_case(FM_BITSTRING) {}

        opcode_case(FM_START_PROC) {
            MargValue new_proc = MARG_PROC(vm->current->bound_method);
            AS_PROC(new_proc)->bound_proc = vm->current;
            emit_possible_long_op(OP_PUT_OBJECT);
            emit_temporary(new_proc);

            vm->current = AS_PROC(new_proc);
        }
        opcode_case(FM_END_PROC) {
            emit_byte(OP_EXIT_ACTIVATION_RECORD);
            inspect_and_print_proc(vm);
            vm->current = vm->current->bound_proc;
        }

        opcode_case(FM_START_C_FUNCTION) {}
        opcode_case(FM_END_C_FUNCTION) {}

        opcode_case(FM_START_UNARY_METHOD) {
            MargValue new_method = MARG_METHOD(vm->current->bound_method->bound_object, string_get(vector_get(formal_bytecode, ++ip)));
            AS_METHOD(new_method)->proc->bound_proc = vm->current;
            emit_possible_long_op(OP_PUT_OBJECT);
            emit_temporary(new_method);

            vm->current = AS_METHOD(new_method)->proc;
        }
        opcode_case(FM_END_UNARY_METHOD) {
            emit_byte(OP_EXIT_ACTIVATION_RECORD);
            inspect_and_print_method(vm);
            vm->current = vm->current->bound_proc;
        }
        opcode_case(FM_START_BINARY_METHOD) {
            MargValue new_method = MARG_METHOD(vm->current->bound_method->bound_object, string_get(vector_get(formal_bytecode, ++ip)));
            AS_METHOD(new_method)->proc->bound_proc = vm->current;
            emit_possible_long_op(OP_PUT_OBJECT);
            emit_temporary(new_method);

            vm->current = AS_METHOD(new_method)->proc;
        }
        opcode_case(FM_END_BINARY_METHOD) {
            emit_byte(OP_EXIT_ACTIVATION_RECORD);
            inspect_and_print_method(vm);
            vm->current = vm->current->bound_proc;
        }
        opcode_case(FM_START_KEYWORD_METHOD) {
            MargValue new_method = MARG_METHOD(vm->current->bound_method->bound_object, string_get(vector_get(formal_bytecode, ++ip)));
            AS_METHOD(new_method)->proc->bound_proc = vm->current;
            emit_possible_long_op(OP_PUT_OBJECT);
            emit_temporary(new_method);

            vm->current = AS_METHOD(new_method)->proc;
        }
        opcode_case(FM_END_KEYWORD_METHOD) {
            emit_byte(OP_EXIT_ACTIVATION_RECORD);
            inspect_and_print_method(vm);
            vm->current = vm->current->bound_proc;
        }

        opcode_case(FM_ANY_OBJECT) {}
        opcode_case(FM_METHOD_PARAMETER) {
            char *parameter_name = string_get(vector_get(formal_bytecode, ++ip));
            marg_tensor_add(AS_TENSOR(vm->current->bound_method->parameter_names), MARG_STRING(parameter_name));
        }

        opcode_case(FM_UNARY) {
            string *unary_name = vector_get(formal_bytecode, ++ip);

            switch_unary_case("call")
                emit_byte(OP_CALL_PROC);
            unary_case("abs")
                emit_byte(OP_PRIM_INTEGER_ABS);
            default_unary_case {
                emit_byte(OP_PUT_0);
                emit_possible_long_op(OP_SEND);
                emit_temporary(MARG_STRING(string_get(unary_name)));
            }
        }
        opcode_case(FM_BINARY) {
            string *binary_name = vector_get(formal_bytecode, ++ip);

            switch_binary_case("+")
                emit_byte(OP_PRIM_INTEGER_ADD);
            binary_case("-")
                emit_byte(OP_PRIM_INTEGER_SUB);
            binary_case("*")
                emit_byte(OP_PRIM_INTEGER_MUL);
            binary_case("/")
                emit_byte(OP_PRIM_INTEGER_DIV);
            binary_case("==")
                emit_byte(OP_PRIM_INTEGER_EQUALS);
            binary_case("<")
                emit_byte(OP_PRIM_INTEGER_LT);
            binary_case(">")
                emit_byte(OP_PRIM_INTEGER_GT);
            binary_case("<=")
                emit_byte(OP_PRIM_INTEGER_LTE);
            binary_case(">=")
                emit_byte(OP_PRIM_INTEGER_GTE);
            binary_case("++")
                ;
            default_binary_case {
                emit_byte(OP_PUT_1);
                emit_possible_long_op(OP_SEND);
                emit_temporary(MARG_STRING(string_get(binary_name)));
            }
        }
        opcode_case(FM_KEYWORD) {
            string *keyword_name = vector_get(formal_bytecode, ++ip);
            string *number_of_parameters = vector_get(formal_bytecode, ++ip);

            switch_keyword_case("puts:")
                emit_byte(TEST_OP_PRINT);
            keyword_case("bind:")
                emit_byte(OP_BIND_METHOD);
            keyword_case("call:")
                emit_byte(OP_CALL_PROC_PARAMS);
            keyword_case("clone:")
                emit_byte(OP_CLONE_OBJECT);
            default_keyword_case {
                if(string_equals(number_of_parameters, string_new("1")))
                    emit_byte(OP_PUT_1);
                if(string_equals(number_of_parameters, string_new("2")))
                    emit_byte(OP_PUT_2);
                else {
                    char *end; long long integer = strtoll(string_get(number_of_parameters), &end, 10);
                    emit_bytes2(OP_PUT_OBJECT, integer);
                }

                emit_possible_long_op(OP_SEND);
                emit_temporary(MARG_STRING(string_get(keyword_name)));
            }
        }
    }

    emit_byte(OP_HALT);
    inspect_and_print_main(vm);

    return vm;
}
