/*
 * File:   conf.h
 * Author: Piotr Janczura <piotr@janczura.pl>
 *
 * Created on 27 września 2017, 10:53
 */

#ifndef CONF_H
#define CONF_H

#include <string>

namespace pjpl::conf {


const char* const LOG_FILE      = "/var/log/pjpl/pjpl-automation.log";
const char* const STATUS_FILE   = "/usr/share/zoneminder/fifo/pjpl-automation.status";

// Czas w którym zgłoszone zdarzenie, może być uznane jako zgłoszone ponownie a w związku z tym uznane za szum.
const int FILTER_NOISE_EVENT_DURATIN  = 60; // sek

const int DATABUS_APPROVED_DELAY = 50; //[ms] Dopuszczalny czas przez jaki podłączone urządzenie może być niedostępne.

const int TCPIP_PORT_DATA = 21000;
const int TCPIP_PORT_SERVICE = 21001;


}

#endif /* CONF_H */
