/*
 * File:   DateTime.h
 * Author: Piotr Janczura <piotr@janczura.pl>
 *
 * Created on 6 października 2017, 14:12
 */
#ifndef DATETIME_H
#define DATETIME_H

#include <sys/time.h>

#include <ctime>
#include <iosfwd>
#include <iomanip>
#include <sstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <sys/time.h>
#include <locale>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/greg_duration.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/greg_duration.hpp>

namespace old {
    typedef struct SimpleTM{
        int year = 0;
        int mon = 0;
        int mday = 0;
        int hour = 0;
        int min = 0;
        int sec = 0;
    } SimpleTM;

    typedef enum DateTimeEnum {
        BAD = 0,
        DATE = 1,
        DATE_HOUR = 2,
        HOUR = 3
    } DateTimeType;

    class DateTime {
    public:
        /**
         * Zainicjowanie lokalizmu
         */
        static void init_locale() {
//            tz{ new boost::local_time::posix_time_zone{"CET+1"}};
        }
        /**
         * Utworzy obiekt dla sekundy z momentu powstania obiektu
         */
        DateTime();
        /**
         * Utworzy obiekt dla momentu powstania przesunięty o td
         * @param timeDuration
         */
        DateTime(const boost::posix_time::time_duration &timeDuration);
        /**
         * Utworzy obiekt dla daty dateTime przesunięty o time_duration
         * @param timeDuration
         */
        DateTime(const DateTime &dateTime, const boost::posix_time::time_duration &timeDuration);
        /**
         * Utworzy obiekt dla daty w formacie : "Y-m-d H:M:S"
         * @param timeStamp
         */
        DateTime(const std::string &timeStamp);
        DateTime(boost::posix_time::ptime &timeStamp);
        DateTime(const DateTime &dateTime);
        DateTime(std::time_t time);
        virtual ~DateTime();

        static DateTimeType check(const std::string &time);
        /**
         * Gdy dt jest większa zwraca wartości dodatnie
         * @param dt
         * @return
         */
        int diffInSec(const DateTime &dt);
        boost::posix_time::ptime get() const;
        std::time_t time_t();
        std::string getString() { return getStringDateTime(); };
        std::string getStringDateTime();
        std::string getStringDate();
        std::string getStringTime();
        std::string getStringMs();
        int getWeekdayNr();
//        boost::posix_time::ptime next01MinInterval();
//        boost::posix_time::ptime next05MinInterval();
//        boost::posix_time::ptime next10MinInterval();
//        boost::posix_time::ptime next15MinInterval();
//        boost::posix_time::ptime next30MinInterval();
//        boost::posix_time::ptime next01HourInterval();
//        boost::posix_time::ptime nextDayInterval();
        void nextSec();
        void now();
        virtual void set(const std::string &value);
        virtual void set(std::time_t time);
        static SimpleTM simpleTm(const std::string &timeStamp);

        DateTime &operator = (const std::string &time);
        DateTime operator + (const boost::posix_time::time_duration &step);
        DateTime operator - (const boost::posix_time::time_duration &step) ;
        DateTime &operator -= (const boost::posix_time::time_duration &step);
        DateTime &operator += (const boost::posix_time::time_duration &step) ;
        friend DateTime operator + (const DateTime &lv, const boost::posix_time::time_duration &step);
        friend bool operator == (const DateTime &lv, const DateTime &rv);
        friend bool operator < (const DateTime &lv, const DateTime &rv);
        friend bool operator != (const DateTime &lv, const DateTime &rv);
        friend bool operator <= (const DateTime &lv, const DateTime &rv);
        friend bool operator > (const DateTime &lv, const DateTime &rv);
        friend bool operator >= (const DateTime &lv, const DateTime &rv);

    private:
        boost::posix_time::ptime ptime;
    };
}


#endif /* DATETIME_H */

