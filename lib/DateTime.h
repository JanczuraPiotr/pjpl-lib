//
// Created by piotr@janczura.pl on 2020.01.20
//

#ifndef PJPL_LIB_DATETIME_H
#define PJPL_LIB_DATETIME_H

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "../lib/def.h"

namespace pjpl {

// Klasa operuje na dacie w formacie ROK-MIESIĄC-DZIEŃ GODZINA:MINUTA:SEKUNDA - liczby z wiodącym zerem
// Możliwe również ROK-MIESIĄC-DZIEŃ lub GODZINA:MINUTA:SEKUNDA
// W przyszłości ROK-MIESIĄC-DZIEŃ GODZINA:MINUTA:SEKUNDA.MILISEKUNDA
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
    typedef enum class Enum {
        BAD = 0,
        DATE = 1,
        DATE_HOUR = 2,
        HOUR = 3,
        // @task MILLISECONDS_FROM_EPOCH,
        // @task MILLISECONDS_FROM_DAY,
        // @task MILLISECONDS,
    } Type;

    DateTime();
    explicit DateTime(const pjpl::String &timeStamp);
    virtual ~DateTime() = default;

    [[nodiscard]] static Type check(const pjpl::String &time) ;
    [[nodiscard]] static boost::posix_time::ptime createPtime(const pjpl::String &time) noexcept;
    [[nodiscard]] static pjpl::String getStringDate(const boost::posix_time::ptime &ptime) noexcept;
    //[[nodiscard]] static pjpl::String getStringTime(const boost::posix_time::ptime &ptime) noexcept;

    [[nodiscard]] pjpl::String getStringDateTime() const noexcept;
    [[nodiscard]] pjpl::String getStringDate() const noexcept;
    [[nodiscard]] pjpl::String getStringTime() const noexcept;

private: // methods
    static SimpleTM simpleTm(const std::string &timeStamp);

//    Duration getSeconds() const noexcept ;
//    //Duration getMilliseconds();
//


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

private: // attributes
    boost::posix_time::ptime ptime;

};

}


#endif
