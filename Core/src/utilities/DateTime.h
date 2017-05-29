#pragma once

#include <string>
using std::string;

#include <time.h>

class DateTime {
private:
    time_t secondsFrom;
    struct tm *currentDate;

public:

    typedef enum {
        Sunday = 0,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday
    } DayOfWeek;

    typedef enum {
        Year,
        Month,
        Day,
        Hour,
        Minutes,
        Seconds
    } DateTimeComponent;

    DateTime();
    DateTime(const DateTime &dateTime);
    ~DateTime();

    int getYear() const;
    int getMonth() const;
    int getDay() const;

    int getHour() const;
    int getMinutes() const;
    int getSeconds() const;

    DayOfWeek getDayOfWeek() const;
    string getDayOfWeekName() const;

    void increase(int quantity, DateTimeComponent component);

    void operator=(const DateTime &dateTime);
    bool operator==(const DateTime &dateTime) const;
    bool operator>=(const DateTime &dateTime) const;
    bool operator<=(const DateTime &dateTime) const;

    time_t toSeconds() const;

    string toString() const;
    string toString(const char *format) const;
};
