/*
 * File:   ParamsForFilter.h
 * Author: Piotr Janczura <piotr@janczura.pl>
 *
 * Created on 13 września 2017, 16:46
 */

#ifndef PARAMSFORFILTER_H
#define PARAMSFORFILTER_H

#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include <iomanip>

#include "lib/def.hpp"
#include "lib/DateTime.hpp"

namespace pjpl::model {

class EventToServeRecord;
class EventMacroRecord;

// TODO przełączyć na dziedziczenie po pjpl::ex::general
class ParamsForFilterEx : public std::exception {};

// Jeżeli w przedziale czasu przed zgłoszeniem zdarzenia (zm.Events) jakiś port (wejściowy)
// miał stan ON choć przez moment, to do filtra przekazana jest wartość TRUE. Nawet gdy  w chwili pracy filtra miała wartość FALSE.
// Filtr jest uruchamiany "jakiś czas" po wystąpieniu zdarzenia, więc historia w BitPortHistory nie pamięta 5s przed zdarzeniem ale 5 s przed filtrowaniem.
const int DURATION_ON_FOR_FILTER = 5; // sek;
/**
 * Porty bitowe (coils) które ustawione są na wartość ON.
 * Zmienna znajduje się na tej liście jeżeli w ciągu DURATION_ON_FOR_FILTER była ON - nawet gdy obecnie jest OFF.
 *
 * first.first identyfikator zmiennej pod jakim przechowywana jest wartość z portu.
 * second.first numer sekundy, w której zmienną ustawiono na ON
 * second.second aktualny stan portu.
 * jeżeli second.second == false wartość przestanie być aktualna w chwili second.first + DURATION_ON_FOR_FILTER
 * gdy zmiana z 0 na 1 to aktualizowany jest second.first na teraz
 */
typedef std::map<pjpl::autom::VariableId, std::pair<pjpl::DateTime, bool> > BitPortHistory;

/**
 * Dostarcza parametry do filtra uruchamiającego makra.
 *
 * Klasa budująca filtr dla dopasowania komend do zgłoszonych zdarzeń EventsToServe.
 * Tabela EventsToServe przechowuje wybrane pola z różnych tabel gromadzących stan systemu ale nie zawiera wszystkich
 * danych potrzebnych do przetwarzania.
 * Te, brakujące elementy należy zebrać i dodać do tabeli zmiennych przekazywanych filtrowi.
 *
 * Brakujące elementy :
 *  - MonitorFunction
 *  - Weekday
 *  - VariableId    - id zmiennej generującej zdarzenie : EventsToServe.VariableId
 *  - VariableVal   - wartość zmiennej generującej zdarzenie : EventsToServe.VariableVal
 *  - @xxxx         - oczekiwana przez filtr wartość dla zmiennej o id = xxxx pobierana z BitPortHistory
 */
class ParamsForFilter {
public:
    typedef std::shared_ptr<ParamsForFilter> ptr;

    ParamsForFilter();
    virtual ~ParamsForFilter() = default;
//
//    /**
//     * Przebuduje listę parametrów związanych ze zdarzeniem i wymaganym przez macro.
//     * Makro pracuje na danych związanych ze zdarzeniem ale może potrzebować dane o stanie systemu.
//     * Metoda na podstawie makra zgromadzi dodatkowe dane
//     * @param event zdarzenie do obsłużenia, niesie ze sobą część danych do wykonania makra
//     * @param macro makro obsługujące zdarzenie,
//     */
//    void reload(
//            std::shared_ptr<pjpl::model::EventToServeRecord> event
//            , std::shared_ptr<pjpl::model::EventMacroRecord> macro);
//
//    /**
//     * Zwraca listę parametrów i ich wartości.
//     * Zwraca wartości z tabeli EventsToServe przeznaczone do testowania zdarzenia ale dodatkowo zwraca wybrane wartości
//     * z innych bloków systemu, które nie są związane są ze zdarzeniem ale wymagane są przez filtr.
//     *
//     * @return key nazwa parametru , val wartość parametru
//     */
//    ParamsMap* getParams();
//    /**
//     * Dopuszczalne wartości parametrów dla parametru o nazwie params.key.
//     * Lista tych wartości brana jest z definicji makra z operatorów =[ i ![ np
//     *      =["1","2","3"] - warunek jest spełniony gdy params.key przyjął jedną z wartości ,
//     *      !["3","5"]     - warunek jest spełniony gdy params.key nie przyjął żadnej z wartości
//     * @return
//     */
//    pjpl::InParamsMap* getInParams();
//    /**
//     * Zwraca parametr
//     * @param name
//     * @return wartość parametry
//     */
//    std::string getParam(const std::string &name);
//    /**
//     * Śledzenie zmian zmiennych.
//     *
//     * Zgodnie z założeniem zmienna ma być uznawana za ON jeżeli choć raz i choć na krótko w czasie DURATION_ON_FOR_FILTER
//     * była ustawiona na ON.
//     * Uwaga! : należy wywoływać w każdej obsłudze zdarzeń, nie zależnie czy jakieś zmienne uległy zmianie.
//     *
//     * @param changedValueMap
//     */
//    void variableTracking(pjpl::autom::ChangedValuesMap *changedValueMap);
//    /**
//     * Zwraca true jeżeli zgodnie z założeniami "DURATION_ON_FOR_FILTER" zmienna była ON
//     * @param variableId
//     * @return
//     */
//    bool considoredAsOn(pjpl::autom::VariableId variableId);
//    /**
//     * @param variableMap
//     */
//    void variableInit(pjpl::autom::Variables *variables);
//
//    void setParam(const std::string &key, const std::string &val );

private: // methods

//    void refresh();
//
//    // Stan parametrów zewnętrznych odświeżam rzadziej niż wykonywana jest obsługa zdarzeń.
//    // Odświeżenie nie częściej niż raz na sekundę.
//    std::string loadWeekday(const std::string &dateTime);
//    void loadDiskDiskBlocks();

private: // attributes
//
//    pjpl::model::BitPortHistory bitPortHistory;
//
//    int diskPercent;
//    std::string s_diskPercent;
//    int diskDiskBlocks;
//    std::string s_diskDiskBlocks;
//    pjpl::ParamsMap *params;
//    pjpl::InParamsMap *inParams;
//
//    pjpl::DateTime lastRefresh;
};

}

#endif /* PARAMSFORFILTER_H */

