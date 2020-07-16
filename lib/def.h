//
// Created by piotr@janczura.pl on 2020.01.20
//

#ifndef PJPL_LIB_DEF_H
#define PJPL_LIB_DEF_H

#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace pjpl   {

typedef uint64_t Duration;
typedef std::string String;  // albo typedef std::string String;
typedef unsigned AutoId;

// key : param name
// val : current param value
typedef std::map<std::string, std::string> ParamsMap;

// key : param name
// val : list of valid values
typedef std::map<std::string, std::vector<std::string> > InParamsMap;

typedef int StatusCode; // if < 0 then error if > 0 then ok if = 0 unknown/not set

typedef enum RecognitionEnum {
    BAD_STRING = -1,    // string not a plate and not a face
    UNKNOWN = 0,        // string is a plate but not assigned to black or white list
    WHITE = 1,
    BLACK = 2
} RecognitionType;

}

namespace pjpl::autom {


// Identyfikatory zmiennych na podstawie bazy danych
typedef int VariableId;
typedef std::vector<VariableId> VariableGroup;
typedef pjpl::autom::VariableGroup ObservedVariable;

typedef uint16_t VariableValue;
typedef struct {
    VariableId     id;
    VariableValue  val;
} Variable;

typedef enum VariableEnum {
    VARIABLE     = 0,
    VARIABLE_IN  = 1,
    VARIABLE_OUT = 2
} VariableType;

// Zmienne "wyłuskane" z rejestru urządzenia.
typedef std::map<VariableId, VariableValue> Variables;
// Zmienne do wysłania
// first : identyfikator zmiennej
// second.first : wartość
// second.second : Znacznik czasu z momentu przekazania zmiennej do wysłania.
typedef std::map<VariableId , std::pair<VariableValue , pjpl::Duration > > VariableToSend;

// Mapa Zmiennych które zmieniły swoją wartość podczas ostatniego odczytu
// key : identyfikator zmiennej
// val :
//      first : nowa wartość
//      second : poprzednia wartość
typedef std::map<VariableId, std::pair<VariableValue, VariableValue> > ChangedValuesMap;

typedef int MonitorId;
typedef std::map<pjpl::autom::VariableId, pjpl::autom::VariableType> VariableTypeMap;


}



#endif