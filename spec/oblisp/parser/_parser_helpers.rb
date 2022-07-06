def parse(code, expected_result="Compilation #{'successful'.green()}")
    l = Lexer.new "file.obl", code.chars;
    l.make_tokens;
    p = Parser.new l;
    expect(p.analyse_syntax).to eq expected_result;
end

def error(code, error_message)
    begin
        l = Lexer.new "file.obl", code.chars;
        l.make_tokens;
        p = Parser.new l;
        expect(p.analyse_syntax).to eq nil;
    rescue Exception => e
        expect(e.message).to eq error_message;
    end
end
