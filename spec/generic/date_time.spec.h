#ifndef __DATE_TIME_SPEC_H_
#define __DATE_TIME_SPEC_H_

#include "../_helpers.h"

module(date_time_spec, {
  it("parses dates", {
    parse(
      "(x = Date today)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Date day_and_time_now)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("day_and_time_now"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Date from_string: \"01/02/1999\")",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_STRING,
        string_new("01/02/1999"),
        FM_KEYWORD,
        string_new("from_string:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Date day: 6 month: \"july\" year: 2022)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_INTEGER,
        string_new("6"),
        FM_STRING,
        string_new("july"),
        FM_INTEGER,
        string_new("2022"),
        FM_KEYWORD,
        string_new("day:month:year:"),
        string_new("3"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Date from_days: 36000)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_INTEGER,
        string_new("36000"),
        FM_KEYWORD,
        string_new("from_days:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Date day_of_week: \"Monday\")",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_STRING,
        string_new("Monday"),
        FM_KEYWORD,
        string_new("day_of_week:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // 1
    parse(
      "(x = Date index_of_month: \"March\")",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_STRING,
        string_new("March"),
        FM_KEYWORD,
        string_new("index_of_month:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // 3
    parse(
      "(x = Date days_in_month: 2 for_year: 1978)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("1978"),
        FM_KEYWORD,
        string_new("days_in_month:for_year:"),
        string_new("2"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // 28 or 29
    parse(
      "(x = Date days_in_year: 1984)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_INTEGER,
        string_new("1984"),
        FM_KEYWORD,
        string_new("days_in_year:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // 365 or 66
    parse(
      "(x = Date name_of_day: 1)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_INTEGER,
        string_new("1"),
        FM_KEYWORD,
        string_new("name_of_day:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // Monday
    parse(
      "(x = Date is_leap_year?: 1996)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_INTEGER,
        string_new("1996"),
        FM_KEYWORD,
        string_new("is_leap_year?:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // true or false

    parse(
      "(x = Date today weekday)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_UNARY,
        string_new("weekday"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // What day is today
    parse(
      "(x = Date today previous)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_UNARY,
        string_new("previous"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // Prev day from today
    parse(
      "(x = Date today day_of_month)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_UNARY,
        string_new("day_of_month"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // 1-31
    parse(
      "(x = Date today day)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_UNARY,
        string_new("day"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // 1-366
    parse(
      "(x = Date today first_day_of_month)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_UNARY,
        string_new("first_day_of_month"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Date today month_name)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_UNARY,
        string_new("month_name"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Date today month_index)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_UNARY,
        string_new("month_index"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Date today days_in_month)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_UNARY,
        string_new("days_in_month"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // 1-31
    parse(
      "(x = Date today year)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_UNARY,
        string_new("year"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // 2022
    parse(
      "(x = Date today days_in_year)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_UNARY,
        string_new("days_in_year"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Date today days_left_in_year)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_UNARY,
        string_new("days_left_in_year"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Date today to_seconds)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_UNARY,
        string_new("to_seconds"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Date today add_days: 10)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_INTEGER,
        string_new("10"),
        FM_KEYWORD,
        string_new("add_days:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Date today subtract_days: 10)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_INTEGER,
        string_new("10"),
        FM_KEYWORD,
        string_new("subtract_days:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Date today subtract_date: Date today)",
      vector_new(
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_LOCAL,
        string_new("Date"),
        FM_UNARY,
        string_new("today"),
        FM_KEYWORD,
        string_new("subtract_date:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
  });

  it("parses time", {
    parse(
      "(x = Time now)",
      vector_new(
        FM_LOCAL,
        string_new("Time"),
        FM_UNARY,
        string_new("now"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Time date_and_time_now)",
      vector_new(
        FM_LOCAL,
        string_new("Time"),
        FM_UNARY,
        string_new("date_and_time_now"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Time from_string: \"3:47:26 pm\")",
      vector_new(
        FM_LOCAL,
        string_new("Time"),
        FM_STRING,
        string_new("3:47:26 pm"),
        FM_KEYWORD,
        string_new("from_string:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Time from_string: \"22:47:26\")",
      vector_new(
        FM_LOCAL,
        string_new("Time"),
        FM_STRING,
        string_new("22:47:26"),
        FM_KEYWORD,
        string_new("from_string:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Time from_seconds: (60 * 60 * 4))",
      vector_new(
        FM_LOCAL,
        string_new("Time"),
        FM_INTEGER,
        string_new("60"),
        FM_INTEGER,
        string_new("60"),
        FM_BINARY,
        string_new("*"),
        FM_INTEGER,
        string_new("4"),
        FM_BINARY,
        string_new("*"),
        FM_KEYWORD,
        string_new("from_seconds:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Time millisecond_clock_value)",
      vector_new(
        FM_LOCAL,
        string_new("Time"),
        FM_UNARY,
        string_new("millisecond_clock_value"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // Since midnight?
    parse(
      "(x = Time total_seconds)",
      vector_new(
        FM_LOCAL,
        string_new("Time"),
        FM_UNARY,
        string_new("total_seconds"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // Since beginning

    parse(
      "(x = Time now seconds)",
      vector_new(
        FM_LOCAL,
        string_new("Time"),
        FM_UNARY,
        string_new("now"),
        FM_UNARY,
        string_new("seconds"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // Seconds past current minute
    parse(
      "(x = Time now minutes)",
      vector_new(
        FM_LOCAL,
        string_new("Time"),
        FM_UNARY,
        string_new("now"),
        FM_UNARY,
        string_new("minutes"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // Minutes past current hour
    parse(
      "(x = Time now hours)",
      vector_new(
        FM_LOCAL,
        string_new("Time"),
        FM_UNARY,
        string_new("now"),
        FM_UNARY,
        string_new("hours"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    ); // Hours past midnight
    parse(
      "(x = Time now add_time: Time now)",
      vector_new(
        FM_LOCAL,
        string_new("Time"),
        FM_UNARY,
        string_new("now"),
        FM_LOCAL,
        string_new("Time"),
        FM_UNARY,
        string_new("now"),
        FM_KEYWORD,
        string_new("add_time:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Time now subtract_time: Time now)",
      vector_new(
        FM_LOCAL,
        string_new("Time"),
        FM_UNARY,
        string_new("now"),
        FM_LOCAL,
        string_new("Time"),
        FM_UNARY,
        string_new("now"),
        FM_KEYWORD,
        string_new("subtract_time:"),
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
    parse(
      "(x = Time now as_seconds)",
      vector_new(
        FM_LOCAL,
        string_new("Time"),
        FM_UNARY,
        string_new("now"),
        FM_UNARY,
        string_new("as_seconds"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
  });
})

#endif
