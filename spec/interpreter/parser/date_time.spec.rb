require_relative "_parser_helpers";

describe Parser do
    context "on date and time" do
        it "parses dates" do
            parse("(x = Date today)", "(= x today Date)");
            parse("(x = Date day_and_time_now)", "(= x day_and_time_now Date)");
            parse(%Q{(x = Date from_string: "01/02/1999")}, %Q{(= x from_string: Date "01/02/1999")});
            parse(%Q{(x = Date day: 6 month: "july" year: 2022)}, %Q{(= x day:month:year: Date 6 "july" 2022)});
            parse("(x = Date from_days: 36000)", "(= x from_days: Date 36000)");
            parse(%Q{(x = Date day_of_week: "Monday")}, %Q{(= x day_of_week: Date "Monday")}); # 1
            parse(%Q{(x = Date index_of_month: "March")}, %Q{(= x index_of_month: Date "March")}); # 3
            parse("(x = Date days_in_month: 2 for_year: 1978)", "(= x days_in_month:for_year: Date 2 1978)"); # 28 or 29
            parse("(x = Date days_in_year: 1984)", "(= x days_in_year: Date 1984)"); # 365 or 366
            parse("(x = Date name_of_day: 1)", "(= x name_of_day: Date 1)"); # :Monday
            parse("(x = Date is_leap_year?: 1996)", "(= x is_leap_year?: Date 1996)"); # true or false
            
            parse("(x = Date today weekday)", "(= x weekday (today Date))"); # What day is today
            parse("(x = Date today previous)", "(= x previous (today Date))"); # Prev day from today
            parse("(x = Date today day_of_month)", "(= x day_of_month (today Date))"); # 1-31
            parse("(x = Date today day)", "(= x day (today Date))"); # 1-366
            parse("(x = Date today first_day_of_month)", "(= x first_day_of_month (today Date))");
            parse("(x = Date today month_name)", "(= x month_name (today Date))");
            parse("(x = Date today month_index)", "(= x month_index (today Date))"); # 
            parse("(x = Date today days_in_month)", "(= x days_in_month (today Date))"); # 1-31
            parse("(x = Date today year)", "(= x year (today Date))"); # 2022
            parse("(x = Date today days_in_year)", "(= x days_in_year (today Date))");
            parse("(x = Date today days_left_in_year)", "(= x days_left_in_year (today Date))");
            parse("(x = Date today to_seconds)", "(= x to_seconds (today Date))");
            parse("(x = Date today add_days: 10)", "(= x add_days: today Date 10)");
            parse("(x = Date today subtract_days: 10)", "(= x subtract_days: today Date 10)");
            parse("(x = Date today subtract_date: (Date today))", "(= x subtract_date: today Date (today Date))");
        end

        it "parses time" do
            parse("(x = Time now)", "(= x now Time)");
            parse("(x = Time date_and_time_now)", "(= x date_and_time_now Time)");
            parse(%Q{(x = Time from_string: "3:47:26 pm")}, %Q{(= x from_string: Time "3:47:26 pm")});
            parse(%Q{(x = Time from_string: "22:47:26")}, %Q{(= x from_string: Time "22:47:26")});
            parse("(x = Time from_seconds: (60 * 60 * 4))", "(= x from_seconds: Time (* (* 60 60) 4))");
            parse("(x = Time millisecond_clock_value)", "(= x millisecond_clock_value Time)"); # Since midnight ?
            parse("(x = Time total_seconds)", "(= x total_seconds Time)"); # Since beginning

            parse("(x = Time now seconds)", "(= x seconds (now Time))"); # Seconds past current minute
            parse("(x = Time now minutes)", "(= x minutes (now Time))"); # Minutes past current hour
            parse("(x = Time now hours)", "(= x hours (now Time))"); # Hours past midnight
            parse("(x = Time now add_time: (Time now))", "(= x add_time: now Time (now Time))");
            parse("(x = Time now subtract_time: (Time now))", "(= x subtract_time: now Time (now Time))");
            parse("(x = Time now as_seconds)", "(= x as_seconds (now Time))");
        end
    end
end
