//
// Created by piotr@janczura.pl on 2020.01.20
//

#include "DateTime.h"

namespace pjpl {

std::string DateTime::transformFromYmD(const std::string &date) noexcept
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

DateTime::DateTime(const std::string &timeStamp)
    : ptime(DateTime::createPtime(timeStamp))
{
}

DateTime::Type DateTime::check(const pjpl::String &timeStr)  {
    // @work zdefiniować magiczne wartości
    if (timeStr.length() > 19 || (timeStr.length() != 10 && timeStr.length() != 19)) {
        return Type::BAD;
    }
    std::size_t cursor = 0;
    SimpleTM stm;
    if (timeStr.length() >= 10) {
        for ( ; cursor < 4; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return Type::BAD;
            }
        }
        if (timeStr[cursor++] != '-') {
            return Type::BAD;
        }
        for ( ; cursor < 7; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return Type::BAD;
            }
        }
        if (timeStr[cursor++] != '-') {
            return Type::BAD;
        }
        for ( ; cursor < 10; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return Type::BAD;
            }
        }
        if (timeStr.length() == 10) {
            stm = DateTime::simpleTm(timeStr);
            if (
                    ( stm.year > 0 && stm.year < 9999 )&&
                    ( stm.mon > 0 && stm.mon < 13 )&&
                    ( stm.mday > 0 && stm.mday < 32 )
                    ) {
                return Type::DATE;
            } else {
                return Type::BAD;
            }
        }
    }
    if (timeStr.length() == 19 ) {
        if (timeStr[cursor++] != ' ') {
            return Type::BAD;
        }
        for ( ; cursor < 13; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return Type::BAD;
            }
        }
        if (timeStr[cursor++] != ':') {
            return Type::BAD;
        }
        for ( ; cursor < 16; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return Type::BAD;
            }
        }
        if (timeStr[cursor++] != ':') {
            return Type::BAD;
        }
        for ( ; cursor < 19; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return Type::BAD;
            }
        }
    } else if (timeStr.length() == 8 ) { // tylko godzina
        cursor = 0;
        for ( ; cursor < 3; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return Type::BAD;
            }
        }
        if (timeStr[cursor++] != ':') {
            return Type::BAD;
        }
        for ( ; cursor < 6; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return Type::BAD;
            }
        }
        if (timeStr[cursor++] != ':') {
            return Type::BAD;
        }
        for ( ; cursor < 9; ++cursor) {
            if (!std::isdigit(timeStr[cursor])) {
                return Type::BAD;
            }
        }
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
        return Type::DATE_HOUR;
    } else {
        return Type::BAD;
    }

}

boost::posix_time::ptime DateTime::createPtime(const std::string &time) noexcept {
    switch (check(time)) {
        case Type::DATE: {
            return boost::posix_time::time_from_string(time + " 00:00:00");
        }
        case Type::HOUR: {
            boost::posix_time::ptime ptime;
            return boost::posix_time::time_from_string(DateTime::getStringDate(ptime) + time);
        }
        case Type::DATE_HOUR: {
            return boost::posix_time::time_from_string(time);
        }
        case Type::BAD : {
            return boost::posix_time::time_from_string("1970-01-01 00:00:00");
        }
        default:
            return boost::posix_time::ptime();
    }
}

boost::posix_time::ptime DateTime::get() const noexcept {
    return ptime;
}

pjpl::String DateTime::getStringDateTime() const noexcept {
    pjpl::String s;

    s += ( ptime.date().year() < 10
            ? "0" + std::to_string(ptime.date().year())
            : std::to_string(ptime.date().year()) ) + "-";
    s += ( ptime.date().month() < 10
            ? "0" + std::to_string(ptime.date().month())
            : std::to_string(ptime.date().month()) ) + "-";
    s += ( ptime.date().day()   < 10
            ? "0" + std::to_string(ptime.date().day())
            : std::to_string(ptime.date().day()) ) + " ";

    s += ( ptime.time_of_day().hours() < 10
            ? "0" + std::to_string(ptime.time_of_day().hours())
            : std::to_string(ptime.time_of_day().hours())) + ":";
    s += ( ptime.time_of_day().minutes() < 10
            ? "0" + std::to_string(ptime.time_of_day().minutes())
            : std::to_string(ptime.time_of_day().minutes()) ) + ":";
    s += ( ptime.time_of_day().seconds() < 10
            ? "0" + std::to_string(ptime.time_of_day().seconds())
            : std::to_string(ptime.time_of_day().seconds()) );

    return s;
}

pjpl::String DateTime::getStringDate() const noexcept {
    return DateTime::getStringDate(ptime);
}

pjpl::String DateTime::getStringDate(const boost::posix_time::ptime &ptime) noexcept {
    pjpl::String s;

    s += ( ptime.date().year()  < 10
           ? "0" + std::to_string(ptime.date().year())
           : std::to_string(ptime.date().year()) ) + "-";
    s += ( ptime.date().month() < 10
           ? "0" + std::to_string(ptime.date().month())
           : std::to_string(ptime.date().month()) ) + "-";
    s += ( ptime.date().day()   < 10
           ? "0" + std::to_string(ptime.date().day())
           : std::to_string(ptime.date().day()) );

    return s;
}

pjpl::String DateTime::getStringTime() const noexcept {
    pjpl::String s;

    s += ( ptime.time_of_day().hours()   < 10
            ? "0" + std::to_string(ptime.time_of_day().hours())
            : std::to_string(ptime.time_of_day().hours())) + ":";
    s += ( ptime.time_of_day().minutes() < 10
            ? "0" + std::to_string(ptime.time_of_day().minutes())
            : std::to_string(ptime.time_of_day().minutes()) ) + ":";
    s += ( ptime.time_of_day().seconds() < 10
            ? "0" + std::to_string(ptime.time_of_day().seconds())
            : std::to_string(ptime.time_of_day().seconds()) );

    return s;
}

std::time_t DateTime::time_t() const noexcept {
    return boost::posix_time::to_time_t(ptime);
}

DateTime::SimpleTM DateTime::simpleTm(const pjpl::String &timeStamp) {
        SimpleTM stm{0,0,0,0,0,0};
        // @work zdefiniować magiczne wartości
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




//Duration DateTime::getSeconds() const noexcept {
//    return boost::posix_time::seconds;
//}
//
//

//    std::string DateTime::transformFromYmD(const std::string &date)
//    {
//        if (date[2] == '.' || date[2] == '-') {
//            std::string newDate = date.substr(6, 4) + "-" + date.substr(3, 2) + "-" +date.substr(0,2);
//            return newDate;
//        }
//        return "";
//    }
//
//    DateTime::DateTime()
//            : ptime(boost::posix_time::microsec_clock::local_time())
//    {
//    }
//    DateTime::DateTime(boost::posix_time::ptime ptime)
//            : ptime(ptime)
//    {
//
//    }
//
//    DateTime::DateTime(const std::wstring &timeStamp)
//    {
//        std::string s(timeStamp.begin(), timeStamp.end());
//        set(s);
//    }
//
//    DateTime::DateTime(const DateTime &dateTime) {
//        ptime = dateTime.ptime;
//    }
//
//    DateTime::SimpleTM DateTime::simpleTm(const std::string &timeStamp) {
//        SimpleTM stm;
//        // YYYY-MM-DD hh:mm:ss
//        if (timeStamp.length() > 3){
//            stm.year = std::stoi(timeStamp.substr(0, 4));
//        }
//        if (timeStamp.length() > 6){
//            stm.mon = std::stoi(timeStamp.substr(5, 2));
//        }
//        if (timeStamp.length() > 9){
//            stm.mday = std::stoi(timeStamp.substr(8,2));
//        }
//        if (timeStamp.length() > 11){
//            stm.hour = std::stoi(timeStamp.substr(11, 2));
//        }
//        if (timeStamp.length() > 14){
//            stm.min = std::stoi(timeStamp.substr(14, 2));
//        }
//        if (timeStamp.length() > 17){
//            stm.sec = std::stoi(timeStamp.substr(17, 2));
//        }
//        return stm;
//    }
//
//
//    unsigned DateTime::getTotalSeconds() {
//        return ptime.time_of_day().total_milliseconds();
//    }
//
//    std::string DateTime::getStringDateTimeMiliseconds() const
//    {
//        std::string s = getStringDateTime() + " " + std::to_string(ptime.time_of_day().total_milliseconds());
//        return s;
//    }
//

//
//    boost::posix_time::time_duration DateTime::fromEpoch() {
//        boost::posix_time::ptime startEpoch(boost::gregorian::date(1970,1,1));
//        return (ptime - startEpoch);
//    }
//
//    DateTime::DateTime(DateTime &&other) {
//        this->ptime = other.ptime;
//    }
//
//    DateTime& DateTime::operator=(DateTime &&other) {
//        this->ptime = other.ptime;
//        return *this;
//    }
//
//    void DateTime::roundToSecond() {
//        set(getStringDateTime());
//    }
//
//    DateTime::DateTime(const boost::posix_time::time_duration &timeDuration)
//            : ptime(boost::posix_time::microsec_clock::local_time() + timeDuration)
//    {
//    }
//
//    DateTime::DateTime(const DateTime &dateTime, const boost::posix_time::time_duration &timeDuration)
//            : ptime(dateTime.ptime + timeDuration)
//    {
//    }
//
//    DateTime::DateTime()
//            : ptime(boost::posix_time::microsec_clock::local_time())
//    {
//    }
//
//    DateTime::DateTime(boost::posix_time::ptime &timeStamp)
//            : ptime(timeStamp)
//    {
//    }
//
//    DateTime::DateTime(const std::string &timeStamp)
//    {
//        set(timeStamp);
//    }
//
//    DateTime::DateTime(const DateTime &dateTime) {
//        ptime = dateTime.ptime;
//    }
//
//    DateTime::DateTime(std::time_t time) {
//        set(time);
//    }
//
//    DateTime::~DateTime() {
//    }
//
//
//    int DateTime::diffInSec(const old::DateTime &dt) {
//        boost::posix_time::time_duration td;
//        td = dt.get() - ptime;
//        return td.total_seconds();
//    }
//    std::string DateTime::getStringMs() {
//        return boost::posix_time::to_simple_string(ptime).substr(12);
//    }
//
//    int DateTime::getWeekdayNr() {
//        return ptime.date().day_of_week();
//    }
//
//    void DateTime::nextSec() {
//        ptime += boost::posix_time::time_duration(0 , 0, 1);
//    }
//
//    void DateTime::now() {
//        ptime = boost::posix_time::microsec_clock::local_time();
//    }
//
//    void DateTime::set(std::time_t time) {
//        ptime = boost::posix_time::from_time_t(time);
//    }
//


//    DateTime &DateTime::operator = (const std::string &time) {
//        this->set(time);
//        return *this;
//    }
//
//    DateTime DateTime::operator + (const boost::posix_time::time_duration &step) {
//        DateTime dt;
//        dt.ptime = this->ptime + step;
//        return dt;
//    }
//
//    DateTime DateTime::operator - (const boost::posix_time::time_duration &step) {
//        DateTime dt;
//        dt.ptime = this->ptime - step;
//        return dt;
//    }
//
//    DateTime &DateTime::operator -= (const boost::posix_time::time_duration &step) {
//        this->ptime -= step;
//        return *this;
//    }
//
//    DateTime &DateTime::operator += (const boost::posix_time::time_duration &step) {
//        this->ptime += step;
//        return *this;
//    }
//
//    DateTime operator + (const DateTime &lv, const boost::posix_time::time_duration &step) {
//        DateTime t(lv);
//        t += step;
//        return t;
//    }
//
//    bool operator == (const DateTime &lv, const DateTime &rv) {
//        return lv.ptime == rv.ptime;
//    }
//
//    bool operator < (const DateTime &lv, const DateTime &rv) {
//        return lv.ptime < rv.ptime;
//    }
//
//    bool operator != (const DateTime &lv, const DateTime &rv) {
//        return !(lv.ptime == rv.ptime);
//    }
//
//    bool operator <= (const DateTime &lv, const DateTime &rv) {
//        return lv.ptime < rv.ptime || lv.ptime == rv.ptime;
//    }
//
//    bool operator > (const DateTime &lv, const DateTime &rv) {
//        return !(lv.ptime <= rv.ptime);
//    }
//
//    bool operator >= (const DateTime &lv, const DateTime &rv) {
//        return !(lv.ptime < rv.ptime);
//    }
}