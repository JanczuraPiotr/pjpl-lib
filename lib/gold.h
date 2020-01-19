//---------------------------------------------------------------------------
#ifndef GOLD_H
#define GOLD_H
//---------------------------------------------------------------------------
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <limits>
#include <set>
#include <cstdlib>
#include <ifaddrs.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <memory>
#include <arpa/inet.h>

#include "lib/napisy.h"
#include "lib/gold.h"


namespace pjpl {

    typedef int err_t;
    typedef std::stack<std::wstring> ws_stack;
    typedef std::vector<std::wstring> ws_vector;
    typedef std::map<std::string, std::string > ss_map;
    typedef std::vector<std::string> vs_t;


    std::string getIpAddress();
    std::vector<int> splitIpAddr(const std::string &ipAddr);
    std::vector<uint8_t> getNet(const std::string &ipAddr, const std::string &netMask);
    std::vector<uint8_t> getNet(const std::string &ipAddr);
    std::string exec(const std::string &cmd);

    float systemLoad();

    //------------------------------------------------------------------------------
    std::string GetErrStr(err_t err_);
    enum kom_t{
        ERR = 0,                // Dowolny nie określony błąd (może nie znany w miejscu wystąpienia)
                                // Można używać też tam gdzie wystarcza proste poinformowanie o niepowodzeniu poprawnie
        OK = 1,                 // Wszystko jest OK!
        ERR_FILE,               // Początek sekcji błędów dotyczących pracy z plikami - oznacza ogólny nie określony błąd podczas
                                // pracy z plikami
        ERR_FILE_DATA,          // Dane umieszczone w pliku mają zły format
        ERR_FILE_OPEN,          // Nie powiodła się próba otwarcia pliku (urządzenia-zasobu)
        ERR_FILE_READ,          // Błąd podczas odczytu danych. Prawdopodobnie osiągnięto koniec
                                // pliku w przed pobraniem oczekiwanej ilości danych
        ERR_FILE_WRITE,         // Błąd zapisu do pliku. Prawdopodobnie nie było możliwe zapisanie
                                // do pliku wymaganej ilości danych
        ERR_FILE_CLOSE,         // Coś nie tak z zamknięciem pliku (urządzenia)
        ERR_EOD,                // End Of Data - Koniec danych. Informuje że wywołanie funkcji dla
                                // operacji na danych odbyło się gdy brak jest danych. Może to nastąpić gdy
                                // obecne wywołanie jest kolejnym a poprzednie poprawnie przeszły po całym
                                // zbiorze i zakończyły pobieranie danych i nie ma powodu sądzić że dalej istnieją jakieś
                                // dane wbrew obowiązującym formatom.
        ERR_NOT_FIND,           // Cokolwiek nie szukano nie znaleziono tego
        ERR_NUM,                // Początek sekcji komunikatów dotyczących przetwarzania liczb. Jednocześnie jakiś nie
                                // nie określony niżej błąd związany z pracą z liczbami
        ERR_NUM_RANGE_IN,       // Zmienna którą przekazano do przetwarzania posiada za dużą dodatnią
                                // lub za małą ujemną wartość wymaganą do przeprowadzenia obliczeń
        ERR_NUM_RANGE_OUT,      // Podczas obliczeń wyprodukowano wartość która nie mieści się w oczekiwanym zakresie
        ERR_SRC_BAD,            // Dane wejściowe podczas przetwarzania okazały się niepoprawne
        ERR_SIGNED,             // Liczba otrzymana w wyniku przetwarzania posiada znak gdy miała być bez znaku lub na odwrót
                                // Patrz SIGNED, UNSIGNED, SIGNED_NOT_CHANGE.
        ERR_RANGE,              // Zmienna poza zakresem. W wyniku operacji zmienna przyjmie wartość za dużą dodatni lub za ma ujemną wartość
        ERR_REDEF,              // Pewna stała zmienia swoja wartość lub próbowano wykonać czynności zmieniając wartość
        ERR_BAD_VALUE,          // Wartość którą przekazano do dalszego przetwarzania jest nie właściwa.
                                // Nie określa się żadnych bliższych informacji.
        ERR_BAD_DEF,            // Wyrażenie definiujące wartość jest nie poprawne. Nie określono przyczyny niepoprawności
                                // Może to być z powodu złej składni, tej liczby nawiasów lub niezdefiniowania jednego
                                // ze składników wyrażenia
        ERR_MATHOP,             // Bd powstały podczas próby wykonania podstawowej operacji matematycznej
        ERR_CALC_LATER,         // Podczas pobierania wartości symbolicznej używanej do obliczenia wartości wyrażenia
                                // okazało się że choć jest zdefiniowana to nie mona było określić jej wartości i obliczenie
                                // wyrażenia należy odłożyć zwracając ten bd
        ERR_THREAD_STOP,        // Awaryjne zakończenie wątku. Wątek przerwano mimo trwania pracy (obliczeń)
        ERR_PAR_BAD,
        ERR_FUN,
        ERR_NOT_OPEN,
        ERR_NOT_VALUE,
        ERR_DIV_0
    };
    const int NUL                 = 0;
    const int SIGNED              = NUL + 7;
    const int UNSIGNED            = NUL + 8;
    const int SIGNED_NOT_CHANGE   = NUL + 9;
    const int WITH_LIM            = SIGNED_NOT_CHANGE + 1;

}


#endif

