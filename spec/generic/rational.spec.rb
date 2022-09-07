describe Parser do
    context "on rational numbers" do
        it "parses rational literals" do
            parse("1r", "r 1");
            parse("2/3r", "/ 2 r 3");
            parse("-1r", "r -1");
            parse("-2/3r", "/ -2 r 3");
            # TODO Separate `-` message on its own token (avoids `-/` or `/-`)
            parse("2/(-3r)", "/ 2 (r -3)");
            parse("-2/(-3r)", "/ -2 (r -3)");
            parse("+1 / (+3r)", "/ +1 (r +3)");
            parse("1.2r", "r 1.2");
            parse("1_1/2_2r", "/ 11 r 22");
            parse("2/4r", "/ 2 r 4");
        end

        it "parses rational literal messages" do
            # TODO rational messages
        end
    end
end
