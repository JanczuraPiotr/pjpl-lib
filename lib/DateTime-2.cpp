//
// Created by piotr@janczura.pl on 2019.11.25
//
//

#include "DateTime-2.h"

std::string DateTime::transformFromYmD(const std::string &date)
{
    if (date[2] == '.' || date[2] == '-') {
        std::string newDate = date.substr(6, 4) + "-" + date.substr(3, 2) + "-" +date.substr(0,2);
        return newDate;
    }
    return "";
}

DateTime::DateTime()
        : ptime(boost::posix_time::microsec_clock::local_time())
{
}
DateTime::DateTime(boost::posix_time::ptime ptime)
    : ptime(ptime)
{

}
DateTime::DateTime(const std::string &timeStamp)
{
    set(timeStamp);
}

DateTime::DateTime(const std::wstring &timeStamp)
{
    std::string s(timeStamp.begin(), timeStamp.end());
    set(s);
}

DateTime::DateTime(const DateTime &dateTime) {
    ptime = dateTime.ptime;
}

void DateTime::set(const std::string &timeStamp)
{
    switch (check(timeStamp)) {
        case DateTimeEnum::DATE: {
            ptime = boost::posix_time::time_from_string(timeStamp + " 00:00:00");
        }
            break;
        case DateTimeEnum::HOUR: {
            ptime = boost::posix_time::time_from_string( getStringDate() + timeStamp);
        }
            break;
        case DateTimeEnum::DATE_HOUR: {
            ptime = boost::posix_time::time_from_string(timeStamp);
        }
            break;
        case DateTimeEnum::BAD : {
            ptime = boost::posix_time::time_from_string("1970-01-01 00:00:00");
        }
    }
}

DateTime::DateTimeType DateTime::check(const std::string &timeStr)
{
    if (timeStr.length() > 19 || (timeStr.length() != 10 && timeStr.length() != 19)) {
        return DateTimeEnum::BAD;
    }
    std::size_t cursor = 0;
    SimpleTM stm;
    if (timeStr.length() >= 10) {
        for ( ; cursor < 4; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return DateTimeEnum::BAD;
            }
        }
        if (timeStr[cursor++] != '-') {
            return DateTimeEnum::BAD;
        }
        for ( ; cursor < 7; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return DateTimeEnum::BAD;
            }
        }
        if (timeStr[cursor++] != '-') {
            return DateTimeEnum::BAD;
        }
        for ( ; cursor < 10; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return DateTimeEnum::BAD;
            }
        }
        if (timeStr.length() == 10) {
            stm = DateTime::simpleTm(timeStr);
            if (
                    ( stm.year > 0 && stm.year < 9999 )&&
                    ( stm.mon > 0 && stm.mon < 13 )&&
                    ( stm.mday > 0 && stm.mday < 32 )
                    ) {
                return DateTimeEnum::DATE;
            } else {
                return DateTimeEnum::BAD;
            }
        }
    }
    if (timeStr.length() == 19 ) {
        if (timeStr[cursor++] != ' ') {
            return DateTimeEnum::BAD;
        }
        for ( ; cursor < 13; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return DateTimeEnum::BAD;
            }
        }
        if (timeStr[cursor++] != ':') {
            return DateTimeEnum::BAD;
        }
        for ( ; cursor < 16; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return DateTimeEnum::BAD;
            }
        }
        if (timeStr[cursor++] != ':') {
            return DateTimeEnum::BAD;
        }
        for ( ; cursor < 19; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return DateTimeEnum::BAD;
            }
        }
        stm = DateTime::simpleTm(timeStr);
    } else if (timeStr.length() == 8 ) { // tylko godzina
        cursor = 0;
        for ( ; cursor < 3; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return DateTimeEnum::BAD;
            }
        }
        stm.hour = std::stoi(timeStr.substr(0, 2));
        if (timeStr[cursor++] != ':') {
            return DateTimeEnum::BAD;
        }
        stm.min = std::stoi(timeStr.substr(3, 2));
        for ( ; cursor < 6; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return DateTimeEnum::BAD;
            }
        }
        if (timeStr[cursor++] != ':') {
            return DateTimeEnum::BAD;
        }
        for ( ; cursor < 9; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return DateTimeEnum::BAD;
            }
        }
        stm.sec = std::stoi(timeStr.substr(7, 2));
    }
    stm = DateTime::simpleTm(timeStr);
    if (
            ( stm.year > 0 && stm.year < 9999 )&&
            ( stm.mon > 0 && stm.mon < 13 )&&
            ( stm.mday > 0 && stm.mday < 32 ) &&
            ( stm.hour >= 0 && stm.hour < 24 ) &&
            ( stm.min >= 0 && stm.min < 60 ) &&
            ( stm.sec >= 0 && stm.sec < 60 )
            ) {
        return DateTimeEnum::DATE_HOUR;
    } else {
        return DateTimeEnum::BAD;
    }

}

DateTime::SimpleTM DateTime::simpleTm(const std::string &timeStamp) {
    SimpleTM stm;
    // YYYY-MM-DD hh:mm:ss
    if (timeStamp.length() > 3){
        stm.year = std::stoi(timeStamp.substr(0, 4));
    }
    if (timeStamp.length() > 6){
        stm.mon = std::stoi(timeStamp.substr(5, 2));
    }
    if (timeStamp.length() > 9){
        stm.mday = std::stoi(timeStamp.substr(8,2));
    }
    if (timeStamp.length() > 11){
        stm.hour = std::stoi(timeStamp.substr(11, 2));
    }
    if (timeStamp.length() > 14){
        stm.min = std::stoi(timeStamp.substr(14, 2));
    }
    if (timeStamp.length() > 17){
        stm.sec = std::stoi(timeStamp.substr(17, 2));
    }
    return stm;
}

boost::posix_time::ptime DateTime::get() const {
    return ptime;
}

unsigned DateTime::getTotalSeconds() {
    return ptime.time_of_day().total_milliseconds();
}

std::string DateTime::getStringDateTimeMiliseconds() const
{
    std::string s = getStringDateTime() + " " + std::to_string(ptime.time_of_day().total_milliseconds());
    return s;
}

std::string DateTime::getStringDateTime() const {
    std::string s;

    s += ( ptime.date().year()  < 10 ? "0" + std::to_string(ptime.date().year())  : std::to_string(ptime.date().year()) ) + "-";
    s += ( ptime.date().month() < 10 ? "0" + std::to_string(ptime.date().month()) : std::to_string(ptime.date().month()) ) + "-";
    s += ( ptime.date().day()   < 10 ? "0" + std::to_string(ptime.date().day())   : std::to_string(ptime.date().day()) ) + " ";

    s += ( ptime.time_of_day().hours()   < 10 ? "0" + std::to_string(ptime.time_of_day().hours())   : std::to_string(ptime.time_of_day().hours())) + ":";
    s += ( ptime.time_of_day().minutes() < 10 ? "0" + std::to_string(ptime.time_of_day().minutes()) : std::to_string(ptime.time_of_day().minutes()) ) + ":";
    s += ( ptime.time_of_day().seconds() < 10 ? "0" + std::to_string(ptime.time_of_day().seconds()) : std::to_string(ptime.time_of_day().seconds()) );

    return s;
};

std::string DateTime::getStringDate() const {
    std::string s;
    s += ( ptime.date().year()  < 10 ? "0" + std::to_string(ptime.date().year())  : std::to_string(ptime.date().year()) ) + "-";
    s += ( ptime.date().month() < 10 ? "0" + std::to_string(ptime.date().month()) : std::to_string(ptime.date().month()) ) + "-";
    s += ( ptime.date().day()   < 10 ? "0" + std::to_string(ptime.date().day())   : std::to_string(ptime.date().day()) );
    return s;
};

std::string DateTime::getStringTime() const {
    std::string s;
    s += ( ptime.time_of_day().hours()   < 10 ? "0" + std::to_string(ptime.time_of_day().hours())   : std::to_string(ptime.time_of_day().hours())) + ":";
    s += ( ptime.time_of_day().minutes() < 10 ? "0" + std::to_string(ptime.time_of_day().minutes()) : std::to_string(ptime.time_of_day().minutes()) ) + ":";
    s += ( ptime.time_of_day().seconds() < 10 ? "0" + std::to_string(ptime.time_of_day().seconds()) : std::to_string(ptime.time_of_day().seconds()) );
    return s;
};

boost::posix_time::time_duration DateTime::fromEpoch() {
    boost::posix_time::ptime startEpoch(boost::gregorian::date(1970,1,1));
    return (ptime - startEpoch);
}

DateTime::DateTime(DateTime &&other) {
    this->ptime = other.ptime;
}

DateTime& DateTime::operator=(DateTime &&other) {
    this->ptime = other.ptime;
    return *this;
}

void DateTime::roundToSecond() {
    set(getStringDateTime());
}