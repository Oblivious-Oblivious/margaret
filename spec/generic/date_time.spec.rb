describe Parser do
    context "on date and time" do
        it "parses dates" do
            parse("(x = Date today)", ["push_variable", "Date", "unary", "today", "store", "x"]);
            parse("(x = Date day_and_time_now)", ["push_variable", "Date", "unary", "day_and_time_now", "store", "x"]);
            parse(%Q{(x = Date from_string: "01/02/1999")}, ["push_variable", "Date", "push_string", %Q{"01/02/1999"}, "keyword", "from_string:", "1", "store", "x"]);
            parse(%Q{(x = Date day: 6 month: "july" year: 2022)}, ["push_variable", "Date", "push_integer", "6", "push_string", %Q{"july"}, "push_integer", "2022", "keyword", "day:month:year:", "3", "store", "x"]);
            parse("(x = Date from_days: 36000)", ["push_variable", "Date", "push_integer", "36000", "keyword", "from_days:", "1", "store", "x"]);
            parse(%Q{(x = Date day_of_week: "Monday")}, ["push_variable", "Date", "push_string", %Q{"Monday"}, "keyword", "day_of_week:", "1", "store", "x"]); # 1
            parse(%Q{(x = Date index_of_month: "March")}, ["push_variable", "Date", "push_string", %Q{"March"}, "keyword", "index_of_month:", "1", "store", "x"]); # 3
            parse("(x = Date days_in_month: 2 for_year: 1978)", ["push_variable", "Date", "push_2", "push_integer", "1978", "keyword", "days_in_month:for_year:", "2", "store", "x"]); # 28 or 29
            parse("(x = Date days_in_year: 1984)", ["push_variable", "Date", "push_integer", "1984", "keyword", "days_in_year:", "1", "store", "x"]); # 365 or 366
            parse("(x = Date name_of_day: 1)", ["push_variable", "Date", "push_1", "keyword", "name_of_day:", "1", "store", "x"]); # :Monday
            parse("(x = Date is_leap_year?: 1996)", ["push_variable", "Date", "push_integer", "1996", "keyword", "is_leap_year?:", "1", "store", "x"]); # true or false
            
            parse("(x = Date today weekday)", ["push_variable", "Date", "unary", "today", "unary", "weekday", "store", "x"]); # What day is today
            parse("(x = Date today previous)", ["push_variable", "Date", "unary", "today", "unary", "previous", "store", "x"]); # Prev day from today
            parse("(x = Date today day_of_month)", ["push_variable", "Date", "unary", "today", "unary", "day_of_month", "store", "x"]); # 1-31
            parse("(x = Date today day)", ["push_variable", "Date", "unary", "today", "unary", "day", "store", "x"]); # 1-366
            parse("(x = Date today first_day_of_month)", ["push_variable", "Date", "unary", "today", "unary", "first_day_of_month", "store", "x"]);
            parse("(x = Date today month_name)", ["push_variable", "Date", "unary", "today", "unary", "month_name", "store", "x"]);
            parse("(x = Date today month_index)", ["push_variable", "Date", "unary", "today", "unary", "month_index", "store", "x"]); # 
            parse("(x = Date today days_in_month)", ["push_variable", "Date", "unary", "today", "unary", "days_in_month", "store", "x"]); # 1-31
            parse("(x = Date today year)", ["push_variable", "Date", "unary", "today", "unary", "year", "store", "x"]); # 2022
            parse("(x = Date today days_in_year)", ["push_variable", "Date", "unary", "today", "unary", "days_in_year", "store", "x"]);
            parse("(x = Date today days_left_in_year)", ["push_variable", "Date", "unary", "today", "unary", "days_left_in_year", "store", "x"]);
            parse("(x = Date today to_seconds)", ["push_variable", "Date", "unary", "today", "unary", "to_seconds", "store", "x"]);
            parse("(x = Date today add_days: 10)", ["push_variable", "Date", "unary", "today", "push_integer", "10", "keyword", "add_days:", "1", "store", "x"]);
            parse("(x = Date today subtract_days: 10)", ["push_variable", "Date", "unary", "today", "push_integer", "10", "keyword", "subtract_days:", "1", "store", "x"]);
            parse("(x = Date today subtract_date: Date today)", ["push_variable", "Date", "unary", "today", "push_variable", "Date", "unary", "today", "keyword", "subtract_date:", "1", "store", "x"]);
        end

        it "parses time" do
            parse("(x = Time now)", ["push_variable", "Time", "unary", "now", "store", "x"]);
            parse("(x = Time date_and_time_now)", ["push_variable", "Time", "unary", "date_and_time_now", "store", "x"]);
            parse(%Q{(x = Time from_string: "3:47:26 pm")}, ["push_variable", "Time", "push_string", %Q{"3:47:26 pm"}, "keyword", "from_string:", "1", "store", "x"]);
            parse(%Q{(x = Time from_string: "22:47:26")}, ["push_variable", "Time", "push_string", %Q{"22:47:26"}, "keyword", "from_string:", "1", "store", "x"]);
            parse("(x = Time from_seconds: (60 * 60 * 4))", ["push_variable", "Time", "push_integer", "60", "push_integer", "60", "binary", "*", "push_integer", "4", "binary", "*", "keyword", "from_seconds:", "1", "store", "x"]);
            parse("(x = Time millisecond_clock_value)", ["push_variable", "Time", "unary", "millisecond_clock_value", "store", "x"]); # Since midnight ?
            parse("(x = Time total_seconds)", ["push_variable", "Time", "unary", "total_seconds", "store", "x"]); # Since beginning

            parse("(x = Time now seconds)", ["push_variable", "Time", "unary", "now", "unary", "seconds", "store", "x"]); # Seconds past current minute
            parse("(x = Time now minutes)", ["push_variable", "Time", "unary", "now", "unary", "minutes", "store", "x"]); # Minutes past current hour
            parse("(x = Time now hours)", ["push_variable", "Time", "unary", "now", "unary", "hours", "store", "x"]); # Hours past midnight
            parse("(x = Time now add_time: Time now)", ["push_variable", "Time", "unary", "now", "push_variable", "Time", "unary", "now", "keyword", "add_time:", "1", "store", "x"]);
            parse("(x = Time now subtract_time: Time now)", ["push_variable", "Time", "unary", "now", "push_variable", "Time", "unary", "now", "keyword", "subtract_time:", "1", "store", "x"]);
            parse("(x = Time now as_seconds)", ["push_variable", "Time", "unary", "now", "unary", "as_seconds", "store", "x"]);
        end
    end
end
