require "rspec/autorun";

# All source files
Dir["#{Dir.pwd}/src/oblisp/**/*.rb"].each { |f| require f };

# lexer
require "#{Dir.pwd}/spec/oblisp/lexer/file_loader.spec.rb";
require "#{Dir.pwd}/spec/oblisp/lexer/lexer.spec.rb";

# tokens
require "#{Dir.pwd}/spec/oblisp/lexer/token.spec.rb";
require "#{Dir.pwd}/spec/oblisp/lexer/type.spec.rb";

# parser
require "#{Dir.pwd}/spec/oblisp/parser/parser.spec.rb"

# oblisp
require "#{Dir.pwd}/spec/oblisp/version.spec.rb";
