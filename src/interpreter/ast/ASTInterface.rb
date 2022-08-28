require_relative "Abstract";

class ASTInterface; extend Abstract;
    abstract_methods :empty,
                     :first_unit,
                     :translation_unit,
                     :assignment,
                     :message,
                     :unary_message,
                     :unary_object,
                     :unary_selector,
                     :binary_message,
                     :binary_object,
                     :binary_selector,
                     :keyword_message,
                     :keyword_object,
                     :keyword_selector,
                     :literal,
                     :integer_literal,
                     :float_literal,
                     :binary_literal,
                     :hexadecimal_literal,
                     :octal_literal,
                     :big_integer_literal,
                     :big_float_literal,
                     :char_literal,
                     :string_literal,
                     :variable,
                     :list,
                     :tuple_literal,
                     :hash_literal,
                     :association,
                     :json_association,
                     :proc_literal,
                     :unary_method_definition,
                     :binary_method_definition,
                     :keyword_method_definition;
end
