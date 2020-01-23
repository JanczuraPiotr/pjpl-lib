//
// Created by piotr@janczura.pl on 2020.01.20
//

#ifndef PJPL_LIB_DATETIME_H
#define PJPL_LIB_DATETIME_H

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "../lib/def.h"

namespace pjpl {


class DateTime {
public:
    // Typ zmiennej do zrzucania czasu na ilość sekund lub milisekund od początku epoki.
    typedef uint64_t Duration;
    typedef struct SimpleTM{
        int year = 0;
        int mon = 0;
        int mday = 0;
        int hour = 0;
        int min = 0;
        int sec = 0;
    } SimpleTM;
    typedef enum class DateTimeEnum {
        BAD = 0,
        DATE = 1,
        DATE_HOUR = 2,
        HOUR = 3
    } Type;

    DateTime();
    explicit DateTime(const std::string &timeStamp);
    virtual ~DateTime() = default;

//    Duration getSeconds() const noexcept ;
//    //Duration getMilliseconds();
//
    virtual void set(const std::string &value);
    static Type check(const std::string &time);

//    explicit DateTime(const std::wstring &timeStamp);
//    DateTime(boost::posix_time::ptime ptime);
//    DateTime(DateTime &&other);
//    DateTime(const DateTime &dateTime);
//    DateTime &operator=(DateTime &&other);
//    DateTime(const boost::posix_time::time_duration &timeDuration);
//    /**
//     * Utworzy obiekt dla daty dateTime przesunięty o time_duration
//     * @param timeDuration
//     */
//    DateTime(const DateTime &dateTime, const boost::posix_time::time_duration &timeDuration);
//    /**
//     * Utworzy obiekt dla daty w formacie : "Y-m-d H:M:S"
//     * @param timeStamp
//     */
//    DateTime(const std::string &timeStamp);
//    DateTime(boost::posix_time::ptime &timeStamp);
//    DateTime(const DateTime &dateTime);
//    DateTime(std::time_t time);
//    virtual ~DateTime();
//
//    /**
//     * Gdy dt jest większa zwraca wartości dodatnie
//     * @param dt
//     * @return
//     */
//    int diffInSec(const DateTime &dt);
//    boost::posix_time::ptime get() const;
//    std::time_t time_t();
//    std::string getString() { return getStringDateTime(); };
//    std::string getStringDateTime();
    std::string getStringDate() const ;
//    std::string getStringTime();
//    std::string getStringMs();
//    int getWeekdayNr();
////        boost::posix_time::ptime next01MinInterval();
////        boost::posix_time::ptime next05MinInterval();
////        boost::posix_time::ptime next10MinInterval();
////        boost::posix_time::ptime next15MinInterval();
////        boost::posix_time::ptime next30MinInterval();
////        boost::posix_time::ptime next01HourInterval();
////        boost::posix_time::ptime nextDayInterval();
//    void nextSec();
//    void now();
//    virtual void set(std::time_t time);
    static SimpleTM simpleTm(const std::string &timeStamp);
//
//    DateTime &operator = (const std::string &time);
//    DateTime operator + (const boost::posix_time::time_duration &step);
//    DateTime operator - (const boost::posix_time::time_duration &step) ;
//    DateTime &operator -= (const boost::posix_time::time_duration &step);
//    DateTime &operator += (const boost::posix_time::time_duration &step) ;
//    friend DateTime operator + (const DateTime &lv, const boost::posix_time::time_duration &step);
//    friend bool operator == (const DateTime &lv, const DateTime &rv);
//    friend bool operator < (const DateTime &lv, const DateTime &rv);
//    friend bool operator != (const DateTime &lv, const DateTime &rv);
//    friend bool operator <= (const DateTime &lv, const DateTime &rv);
//    friend bool operator > (const DateTime &lv, const DateTime &rv);
//    friend bool operator >= (const DateTime &lv, const DateTime &rv);

private:
    boost::posix_time::ptime ptime;

};

}


#endif
