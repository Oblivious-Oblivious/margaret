def opcodes(code, expected_result=nil)
    l = Lexer.new "file.obl", code.chars;
    p = Parser.new l.make_tokens, "bytecode";
    expect(p.analyse_syntax).to eq expected_result;
end

def opdebug(code, expected_result=nil)
    l = Lexer.new "file.obl", code.chars;
    p = Parser.new l.make_tokens, "bytecode";
    expect(pp p.analyse_syntax).to eq expected_result;
end

def operror(code, error_message)
    begin
        l = Lexer.new "file.obl", code.chars;
        p = Parser.new l.make_tokens, "bytecode";
        expect(p.analyse_syntax).to eq nil;
    rescue Exception => e
        expect(e.message).to eq error_message;
    end
end
