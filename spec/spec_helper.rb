require "rspec/autorun";

# All source files
Dir["#{Dir.pwd}/src/oblisp/**/*.rb"].each { |f| require f };

# All spec files
Dir["#{Dir.pwd}/spec/oblisp/**/*.rb"].each { |f| require f };

# require "#{Dir.pwd}/spec/oblisp/lexer/file_loader.spec.rb";
# require "#{Dir.pwd}/spec/oblisp/lexer/lexer.spec.rb";
# require "#{Dir.pwd}/spec/oblisp/lexer/token.spec.rb";
# require "#{Dir.pwd}/spec/oblisp/lexer/type.spec.rb";

# require "#{Dir.pwd}/spec/oblisp/parser/parser.spec.rb"

# require "#{Dir.pwd}/spec/oblisp/version.spec.rb";
