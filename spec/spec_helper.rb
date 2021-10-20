require "rspec/autorun";

# All source files
Dir[Dir.pwd + "/src/oblisp/**/*.rb"].each { |f| require f };

# All spec files
Dir[Dir.pwd + "/spec/oblisp/**/*.rb"].each { |f| require f };
