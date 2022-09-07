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

def opcodes(code, expected_result=nil)
    l = Lexer.new "file.marg", code.chars;
    p = Parser.new l.make_tokens, "bytecode";
    expect(p.analyse_syntax).to eq expected_result;
end

def opdebug(code, expected_result=nil)
    l = Lexer.new "file.marg", code.chars;
    p = Parser.new l.make_tokens, "bytecode";
    expect(pp p.analyse_syntax).to eq expected_result;
end

def operror(code, error_message)
    begin
        l = Lexer.new "file.marg", code.chars;
        p = Parser.new l.make_tokens, "bytecode";
        expect(p.analyse_syntax).to eq nil;
    rescue Exception => e
        expect(e.message).to eq error_message;
    end
end

def evalcodes(code, expected_result=nil)
    l = Lexer.new "file.marg", code.chars;
    p = Parser.new l.make_tokens, "bytecode";
    e = Evaluator.new p.analyse_syntax;
    expect(e.evaluate).to eq expected_result;
end

def evaldebug(code, expected_result=nil)
    l = Lexer.new "file.marg", code.chars;
    p = Parser.new l.make_tokens, "bytecode";
    e = Evaluator.new p.analyse_syntax;
    expect(pp e.evaluate).to eq expected_result;
end

def evalerror(code, error_message)
    begin
        l = Lexer.new "file.marg", code.chars;
        p = Parser.new l.make_tokens, "bytecode";
        e = Evaluator.new p.analyse_syntax;
        expect(e.evaluate).to eq nil;
    rescue Exception => e
        expect(e.message).to eq error_message;
    end
end
