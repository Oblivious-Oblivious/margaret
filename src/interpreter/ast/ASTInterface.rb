require_relative "Abstract";

class ASTInterface; extend Abstract;
    abstract_methods :empty,
                     :list,
                     :translation_unit,
                     :assignment_message,
                     :binary_operand,
                     :keyword,
                     :keyword_argument,
                     :base_ten_literal,
                     :tuple_literal,
                     :hash_literal,
                     :association,
                     :json_association,
                     :symbol_literal,
                     :terminal_POSITIVE_BASE_TEN_NUMBER,
                     :terminal_ALTERNATE_BASE_NUMBER,
                     :terminal_STRING,
                     :terminal_UNQUOTED_STRING,
                     :terminal_IDENTIFIER,
                     :terminal_MESSAGE_SYMBOL,
                     :terminal_IDENTIFIER_SYMBOL,
                     :terminal_SIGN,
                     :terminal_EQUALS,
                     :terminal_COLON;
end
