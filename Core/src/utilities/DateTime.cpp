#include "DateTime.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "utilities/Translator.h"

struct tm *convertDate(time_t *secs) {
    struct tm *temp = localtime(secs);

    struct tm *result = (struct tm *) malloc(sizeof (struct tm));
    memcpy(result, temp, sizeof (struct tm));
    return result;
}

DateTime::DateTime() {
    // Number of seconds since the epoch (January 1st, 1970 00:00 GMT)
    time(&secondsFrom);
    // Convert the time_t (int) value to a more interesting structure (struct tm)
    currentDate = convertDate(&secondsFrom);
}

DateTime::DateTime(const DateTime &dateTime) {
    secondsFrom = dateTime.secondsFrom;
    currentDate = convertDate(&secondsFrom);
}

DateTime::~DateTime() {
    if (currentDate) free(currentDate);
    currentDate = nullptr;
}

int DateTime::getYear() const {
    return (currentDate->tm_year + 1900);
}

int DateTime::getMonth() const {
    return (currentDate->tm_mon + 1);
}

int DateTime::getDay() const {
    return (currentDate->tm_mday);
}

int DateTime::getHour() const {
    return (currentDate->tm_hour);
}

int DateTime::getMinutes() const {
    return (currentDate->tm_min);
}

int DateTime::getSeconds() const {
    return (currentDate->tm_sec);
}

DateTime::DayOfWeek DateTime::getDayOfWeek() const {
    return (DateTime::DayOfWeek)(currentDate->tm_wday);
}

string DateTime::getDayOfWeekName() const {
    switch (getDayOfWeek()) {
        case DateTime::Sunday:
            return _("Sunday");
        case DateTime::Monday:
            return _("Monday");
        case DateTime::Thursday:
            return _("Thursday");
        case DateTime::Wednesday:
            return _("Wednesday");
        case DateTime::Tuesday:
            return _("Tuesday");
        case DateTime::Friday:
            return _("Friday");
        case DateTime::Saturday:
            return _("Saturday");
        default:
            return _("Unknown");
    }
}

void DateTime::increase(int quantity, DateTimeComponent component) {
    time_t seconds = 0;
    switch (component) {
        case DateTime::Year:
            quantity *= 365;
        case DateTime::Month:
            quantity *= 30;
        case DateTime::Day:
            quantity *= 24;
        case DateTime::Hour:
            quantity *= 60;
        case DateTime::Minutes:
            quantity *= 60;
        case DateTime::Seconds:
            seconds = quantity;
            break;
    }
    secondsFrom += seconds;
    currentDate = convertDate(&secondsFrom);
}

void DateTime::operator=(const DateTime &dateTime) {
    secondsFrom = dateTime.secondsFrom;
    currentDate = convertDate(&secondsFrom);
}

bool DateTime::operator==(const DateTime &dateTime) const {
    return secondsFrom == dateTime.secondsFrom;
}

bool DateTime::operator>=(const DateTime &dateTime) const {
    return secondsFrom >= dateTime.secondsFrom;
}

bool DateTime::operator<=(const DateTime &dateTime) const {
    return secondsFrom <= dateTime.secondsFrom;
}

time_t DateTime::toSeconds() const {
    return secondsFrom;
}

char *DateTime::toString() const {
    return ctime(&secondsFrom);
}

char *DateTime::toString(const char *format) const {
    char *string = (char *) malloc(sizeof (char) * 100);
    memset(string, '\0', 100);
    strftime(string, 100, format, currentDate);

    return string;
}

