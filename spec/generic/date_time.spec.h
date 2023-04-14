#ifndef __DATE_TIME_SPEC_H_
#define __DATE_TIME_SPEC_H_

#include "../_helpers.h"

module(date_time_spec, {
    it("parses dates", {
        parse("(x = Date today)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_STORE, marg_string_new("x")));
        parse("(x = Date day_and_time_now)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("day_and_time_now"), OP_STORE, marg_string_new("x")));
        parse("(x = Date from_string: \"01/02/1999\")", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_PUSH_STRING, marg_string_new("01/02/1999"), OP_KEYWORD, marg_string_new("from_string:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = Date day: 6 month: \"july\" year: 2022)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_PUSH_INTEGER, marg_string_new("6"), OP_PUSH_STRING, marg_string_new("july"), OP_PUSH_INTEGER, marg_string_new("2022"), OP_KEYWORD, marg_string_new("day:month:year:"), marg_string_new("3"), OP_STORE, marg_string_new("x")));
        parse("(x = Date from_days: 36000)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_PUSH_INTEGER, marg_string_new("36000"), OP_KEYWORD, marg_string_new("from_days:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = Date day_of_week: \"Monday\")", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_PUSH_STRING, marg_string_new("Monday"), OP_KEYWORD, marg_string_new("day_of_week:"), marg_string_new("1"), OP_STORE, marg_string_new("x"))); // 1
        parse("(x = Date index_of_month: \"March\")", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_PUSH_STRING, marg_string_new("March"), OP_KEYWORD, marg_string_new("index_of_month:"), marg_string_new("1"), OP_STORE, marg_string_new("x"))); // 3
        parse("(x = Date days_in_month: 2 for_year: 1978)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("1978"), OP_KEYWORD, marg_string_new("days_in_month:for_year:"), marg_string_new("2"), OP_STORE, marg_string_new("x"))); // 28 or 29
        parse("(x = Date days_in_year: 1984)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_PUSH_INTEGER, marg_string_new("1984"), OP_KEYWORD, marg_string_new("days_in_year:"), marg_string_new("1"), OP_STORE, marg_string_new("x"))); // 365 or 66
        parse("(x = Date name_of_day: 1)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_PUSH_1, OP_KEYWORD, marg_string_new("name_of_day:"), marg_string_new("1"), OP_STORE, marg_string_new("x"))); // Monday
        parse("(x = Date is_leap_year?: 1996)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_PUSH_INTEGER, marg_string_new("1996"), OP_KEYWORD, marg_string_new("is_leap_year?:"), marg_string_new("1"), OP_STORE, marg_string_new("x"))); // true or false
            
        parse("(x = Date today weekday)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_UNARY, marg_string_new("weekday"), OP_STORE, marg_string_new("x"))); // What day is today
        parse("(x = Date today previous)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_UNARY, marg_string_new("previous"), OP_STORE, marg_string_new("x"))); // Prev day from today
        parse("(x = Date today day_of_month)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_UNARY, marg_string_new("day_of_month"), OP_STORE, marg_string_new("x"))); // 1-31
        parse("(x = Date today day)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_UNARY, marg_string_new("day"), OP_STORE, marg_string_new("x"))); // 1-366
        parse("(x = Date today first_day_of_month)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_UNARY, marg_string_new("first_day_of_month"), OP_STORE, marg_string_new("x")));
        parse("(x = Date today month_name)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_UNARY, marg_string_new("month_name"), OP_STORE, marg_string_new("x")));
        parse("(x = Date today month_index)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_UNARY, marg_string_new("month_index"), OP_STORE, marg_string_new("x")));
        parse("(x = Date today days_in_month)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_UNARY, marg_string_new("days_in_month"), OP_STORE, marg_string_new("x"))); // 1-31
        parse("(x = Date today year)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_UNARY, marg_string_new("year"), OP_STORE, marg_string_new("x"))); // 2022
        parse("(x = Date today days_in_year)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_UNARY, marg_string_new("days_in_year"), OP_STORE, marg_string_new("x")));
        parse("(x = Date today days_left_in_year)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_UNARY, marg_string_new("days_left_in_year"), OP_STORE, marg_string_new("x")));
        parse("(x = Date today to_seconds)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_UNARY, marg_string_new("to_seconds"), OP_STORE, marg_string_new("x")));
        parse("(x = Date today add_days: 10)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_PUSH_INTEGER, marg_string_new("10"), OP_KEYWORD, marg_string_new("add_days:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = Date today subtract_days: 10)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_PUSH_INTEGER, marg_string_new("10"), OP_KEYWORD, marg_string_new("subtract_days:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = Date today subtract_date: Date today)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_PUSH_VARIABLE, marg_string_new("Date"), OP_UNARY, marg_string_new("today"), OP_KEYWORD, marg_string_new("subtract_date:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
    });

    it("parses time", {
        parse("(x = Time now)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Time"), OP_UNARY, marg_string_new("now"), OP_STORE, marg_string_new("x")));
        parse("(x = Time date_and_time_now)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Time"), OP_UNARY, marg_string_new("date_and_time_now"), OP_STORE, marg_string_new("x")));
        parse("(x = Time from_string: \"3:47:26 pm\")", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Time"), OP_PUSH_STRING, marg_string_new("3:47:26 pm"), OP_KEYWORD, marg_string_new("from_string:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = Time from_string: \"22:47:26\")", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Time"), OP_PUSH_STRING, marg_string_new("22:47:26"), OP_KEYWORD, marg_string_new("from_string:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = Time from_seconds: (60 * 60 * 4))", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Time"), OP_PUSH_INTEGER, marg_string_new("60"), OP_PUSH_INTEGER, marg_string_new("60"), OP_BINARY, marg_string_new("*"), OP_PUSH_INTEGER, marg_string_new("4"), OP_BINARY, marg_string_new("*"), OP_KEYWORD, marg_string_new("from_seconds:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = Time millisecond_clock_value)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Time"), OP_UNARY, marg_string_new("millisecond_clock_value"), OP_STORE, marg_string_new("x"))); // Since midnight?
        parse("(x = Time total_seconds)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Time"), OP_UNARY, marg_string_new("total_seconds"), OP_STORE, marg_string_new("x"))); // Since beginning

        parse("(x = Time now seconds)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Time"), OP_UNARY, marg_string_new("now"), OP_UNARY, marg_string_new("seconds"), OP_STORE, marg_string_new("x"))); // Seconds past current minute
        parse("(x = Time now minutes)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Time"), OP_UNARY, marg_string_new("now"), OP_UNARY, marg_string_new("minutes"), OP_STORE, marg_string_new("x"))); // Minutes past current hour
        parse("(x = Time now hours)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Time"), OP_UNARY, marg_string_new("now"), OP_UNARY, marg_string_new("hours"), OP_STORE, marg_string_new("x"))); // Hours past midnight
        parse("(x = Time now add_time: Time now)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Time"), OP_UNARY, marg_string_new("now"), OP_PUSH_VARIABLE, marg_string_new("Time"), OP_UNARY, marg_string_new("now"), OP_KEYWORD, marg_string_new("add_time:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = Time now subtract_time: Time now)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Time"), OP_UNARY, marg_string_new("now"), OP_PUSH_VARIABLE, marg_string_new("Time"), OP_UNARY, marg_string_new("now"), OP_KEYWORD, marg_string_new("subtract_time:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = Time now as_seconds)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Time"), OP_UNARY, marg_string_new("now"), OP_UNARY, marg_string_new("as_seconds"), OP_STORE, marg_string_new("x")));
    });
})

#endif
