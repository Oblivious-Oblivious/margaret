require_relative "_parser_helpers";

describe Parser do
    context "on blocks" do
        it "parses blocks" do
            parse("(x = ((x = 1) (y = 2)))", "(= x ((= x 1) (= y 2)))"); # x = 2
            parse("(x = (
                    (:v1 :v2)
                    (
                        (v1 += 1)
                        (v1 += 2)
                        (v1 * v2)
                    )
                )
            )", %Q{(= x ((new Symbol "v1" new Symbol "v2") ((+= v1 1) (+= v1 2) (* v1 v2))))});
        end
    end
end
