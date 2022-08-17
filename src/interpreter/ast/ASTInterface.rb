require_relative "Abstract";

class ASTInterface; extend Abstract;
    abstract_methods :empty,
                     :first_unit,
                     :translation_unit,
                     :assignment_message,
                     :message,
                     :unary_message,
                     :binary_message,
                     :keyword_message,

                     :cascaded_message,

                     :literal,
                     :integer_literal,
                     :float_literal,
                     :binary_literal,
                     :hexadecimal_literal,
                     :octal_literal,
                     :big_integer_literal,
                     :big_float_literal,
                     :association,
                     :json_association,
                     :string_literal,
                     :symbol_literal,
                     :symbol_name,
                     :variable,
                     :list,
                     :tuple_literal,
                     :hash_literal,
                     :quoted_list_literal,
                     :block_literal;
end
