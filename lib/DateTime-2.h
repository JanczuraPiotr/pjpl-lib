//
// Created by piotr@janczura.pl on 2019.11.25
//

#ifndef DATETIME_2_H
#define DATETIME_2_H

#include <boost/date_time/posix_time/posix_time.hpp>

class DateTime {
public:

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
    static std::string transformFromYmD(const std::string &date);

    /*!
     * Utworzy obiekt dla sekundy z momentu powstania obiektu
     */
    DateTime();
    /*!
     * Utworzy obiekt dla daty w formacie : "Y-m-d H:M:S"  np: 2011-11-11 11-11-11
     */
    explicit DateTime(const std::string &timeStamp);
    explicit DateTime(const std::wstring &timeStamp);
    DateTime(boost::posix_time::ptime ptime);
    DateTime(DateTime &&other);
    DateTime(const DateTime &dateTime);
    DateTime &operator=(DateTime &&other);

    virtual ~DateTime() = default;

    /*!
     * Utworzy obiekt dla daty w formacie : "Y-m-d H:M:S"  np: 2011-11-11 11-11-11
     */
    void set(const std::string &timeStamp);
    static DateTimeType check(const std::string &time);
    static SimpleTM simpleTm(const std::string &timeStamp);
    boost::posix_time::ptime get() const;
    unsigned getTotalSeconds();
    std::string getStringDateTime() const ;
    std::string getStringDateTimeMiliseconds() const ;
    std::string getStringDate() const;
    std::string getStringTime() const ;
    // Sekundy od początku epoki
    boost::posix_time::time_duration fromEpoch();
    void roundToSecond();

private:
    boost::posix_time::ptime ptime;

public: // lock
    DateTime &operator=(const DateTime &) = delete;

};


#endif
