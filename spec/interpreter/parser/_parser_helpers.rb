def parse(code, expected_result=nil)
    l = Lexer.new "file.marg", code.chars;
    p = Parser.new l.make_tokens, "s-expressions";
    expect(p.analyse_syntax).to eq expected_result;
end

def debug(code, expected_result=nil)
    l = Lexer.new "file.marg", code.chars;
    p = Parser.new l.make_tokens, "s-expressions";
    expect(pp p.analyse_syntax).to eq expected_result;
end

def error(code, error_message)
    begin
        l = Lexer.new "file.marg", code.chars;
        p = Parser.new l.make_tokens, "s-expressions";
        expect(p.analyse_syntax).to eq nil;
    rescue Exception => e
        expect(e.message).to eq error_message;
    end
end
