describe Parser do
    context "on rational numbers" do
        it "parses rational literals" do
            parse("1r", ["push_1", "unary", "r"]);
            parse("2/3r", ["push_2", "push_integer", "3", "unary", "r", "binary", "/"]);
            parse("-1r", ["push_minus_1", "unary", "r"]);
            parse("-2/3r", ["push_integer", "-2", "push_integer", "3", "unary", "r", "binary", "/"]);
            # TODO Separate `-` message on its own token (avoids `-/` or `/-`)
            parse("2/(-3r)", ["push_2", "push_integer", "-3", "unary", "r", "binary", "/"]);
            parse("-2/(-3r)", ["push_integer", "-2", "push_integer", "-3", "unary", "r", "binary", "/"]);
            parse("+1 / (+3r)", ["push_1", "push_integer", "3", "unary", "r", "binary", "/"]);
            parse("1.2r", ["push_float", "1.2", "unary", "r"]);
            parse("1_1/2_2r", ["push_integer", "11", "push_integer", "22", "unary", "r", "binary", "/"]);
            parse("2/4r", ["push_2", "push_integer", "4", "unary", "r", "binary", "/"]);
        end

        it "parses rational literal messages" do
            # TODO rational messages
        end
    end
end
