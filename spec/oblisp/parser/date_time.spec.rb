require_relative "_parser_helpers";

describe Parser do
    context "on date and time" do
        it "parses dates" do
            parse("(x = Date today)");
            parse("(x = Date day_and_time_now)");
            parse(%Q{(x = Date from_string: "01/02/1999")});
            parse("(x = Date day: 6 month: :july year: 2022)");
            parse("(x = Date from_days: 36000)");
            parse("(x = Date day_of_week: :Monday)"); # 1
            parse("(x = Date index_of_month: :March)"); # 3
            parse("(x = Date days_in_month: 2 for_year: 1978)"); # 28 or 29
            parse("(x = Date days_in_year: 1984)"); # 365 or 366
            parse("(x = Date name_of_day: 1)"); # :Monday
            parse("(x = Date is_leap_year?: 1996)"); # true or false
            
            parse("(x = Date today weekday)"); # What day is today
            parse("(x = Date today previous)"); # Prev day from today
            parse("(x = Date today day_of_month)"); # 1-31
            parse("(x = Date today day)"); # 1-366
            parse("(x = Date today first_day_of_month)");
            parse("(x = Date today month_name)");
            parse("(x = Date today month_index)"); # 
            parse("(x = Date today days_in_month)"); # 1-31
            parse("(x = Date today year)"); # 2022
            parse("(x = Date today days_in_year)");
            parse("(x = Date today days_left_in_year)");
            parse("(x = Date today to_seconds)");
            parse("(x = Date today add_days: 10)");
            parse("(x = Date today subtract_days: 10)");
            parse("(x = Date today subtract_date: (Date today))");
        end

        it "parses time" do
            parse("(x = Time now)");
            parse("(x = Time date_and_time_now)");
            parse("(x = Time from_string: '3:47:26 pm')");
            parse("(x = Time from_string: '22:47:26')");
            parse("(x = Time from_seconds: (60 * 60 * 4))");
            parse("(x = Time millisecond_clock_value)"); # Since midnight ?
            parse("(x = Time total_seconds)"); # Since beginning

            parse("(x = Time now seconds)"); # Seconds past current minute
            parse("(x = Time now minutes)"); # Minutes past current hour
            parse("(x = Time now hours)"); # Hours past midnight
            parse("(x = Time now add_time: (Time now))");
            parse("(x = Time now subtract_time: (Time now))");
            parse("(x = Time now as_seconds)");
        end
    end
end
