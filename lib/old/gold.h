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

using namespace std;

//------------------------------------------------------------------------------
// sta³e matematyczne
//const double pi=3.1415926535897932385;
//const double e =2.7182818284590452354;

//------------------------------------------------------------------------------
// wymiary, rozmiary, domylne wartoci powstaj¹cych zmiennych
const size_t size_m=numeric_limits<size_t>::max();

namespace old
{
  #define size_m2                 size_m/2
  #define DEFAULT_MAX_BUF_SIZE    8192
  #define DEFAULT_BUF_SIZE        256
  #define DEFAULT_MIN_BUF_SIZE    32
  #define DEFAULT_MAX_STR_SIZE    512
  #define DEFAULT_STR_SIZE        128
        // domylny rozmiar buforów przeznaczonych na napisy
};

//------------------------------------------------------------------------------
// parametry prze³¹czaj¹ce (prze³¹czniki)
namespace old
{
#define NUL                     0
#define DEL_POS_START           NUL+1
#define NO_DEL_POS_START        NUL+2
        // Dotyczy usuwania danych z buforów. Metoda otrzymuj¹ca lub odnajduj¹ca samodzielnie wartoæ
        // w buforze mo¿e potrzebowaæ informacjê czy ma usun¹æ t¹ pozycje czy jest ona traktowana jako
        // granica usuwania.
#define DEL_LEFT                NUL+3
#define DEL_RIGHT               NUL+4
        // Dotyczy usuwania danych z buforów. Metody mog¹ usuwaæ dane z buforów w kierunku rosn¹cych
        // lub malej¹cych indeksów. Podanie jednej z tych wartoci naka¿e usun¹æ elementy w kierunku
        // malej¹cych indexów (DEL_LEFT) lub rosn¹cych (DEL_RIGHT).
#define DEL_POS_STOP            NUL+5
#define NO_DEL_POS_STOP         NUL+6
        // Dotyczy usuwania danych z buforów. Metoda otrzymuj¹ca a zw³¹szcza odnajduj¹ca samodzielnie
        // pozycje zmykaj¹cego elementu kasowany podzbiór mo¿e go potraktowaæ jako granicê kasowania
        // lub ostatni element usówanego podzbioru. Powy¿sze zmienne s³u¿a poinformowaniu metody o
        // postêpowaniu z ostatnim elementem
#define SIGNED                  NUL+7
#define UNSIGNED                NUL+8
#define SIGNED_NOT_CHANGE       NUL+9
        // Gdy bêd¹ wykonywane operacje na zmiennych szczególnie podczas ró¿nych konwersji mo¿e mieæ
        // znaczenie znak przetwarzanej zmiennej. Je¿li wartoæ mo¿e posiadaæ znak zezwalamy na to
        // parametrem SIGNED. Gdy wartoæ po przetworzeniunie mo¿e posiadaæ znaku przekazujemy do
        // metody UNSIGNED. J¿eli zmienna w wyniku operacji nie powinna zmieniæ znaku ustawiamy
        // w wywo³¹niu metody parametr SIGNED_NOT_CHANGE.
        // Patrz: ERR_SIGNED
#define WITH_LIM                SIGNED_NOT_CHANGE+1
#define NO_WITH_LIM             WITH_LIM+1
        // Tam gdzie przetwarzanie odbywa siê na jakim przedziale to jego granica wejdzie do
        // przetwarzanego przedzia³u gdy podany zostanie w wywo³aniu parametr WITH_LIM.
        // Je¿eli parametr znajduj¹cy siê na granicy nie jest przedmioem zainteresowañ, nie mo¿e ulec
        // zmianie podczas przetwarzania podaæ wartoæ NO_WITH_LIM

};

//------------------------------------------------------------------------------
// komunikaty o b³êdach
typedef int err_t;
string GetErrStr(err_t err_);
enum {
  OK,                   // Poprawnie
  ERR,                  // Dowolny nie okreœlony b³¹d (mo¿e nie znany w miejscu wyst¹pienia)
                        // Mo¿na u¿ywaæ te¿ tam gdzie wystarcza proste poinformpwamoie o niepowodzeniu
  ERR_FILE,             // Pocz¹tek sekcji b³êdów dotycz¹cych pracy z plikami
  ERR_FILE_DATA,        // Dane umieszczone w pliku maj¹ z³y format
  ERR_FILE_OPEN,        // Nie powiod³a siê próba otwarcia pliku (urz¹dzenia-zasobu)
  ERR_FILE_READ,        // B³¹d podzczas odczytu danych. Prawdopodobnie osi¹gniêto koniec
                        // pliku w przed pobraniem oczekiwanej iloœci danych
  ERR_FILE_WRITE,       // B³¹d zapisu do pliku. Prawdopodobnie nie by³o mo¿liwe zapisanie 
                        // do pliku wymaganej iloœci danych
  ERR_FILE_CLOSE,       // Coœ nie tak z zamkniêciem plku (urz¹dzenia)
  ERR_EOD,              // End Of Data - Koniec danych. Informuje ¿e wywo³anie funkcji dla 
                        // operacji na danych odby³o siê gdy brak jest danych. Mo¿e to nast¹piæ gdy 
                        // obecne wywo³anie jest kolejnym a poprzednie poprawnie przesz³y po ca³ym 
                        // zbiorze i zakoñczy³y pobieranie danych
  ERR_NOT_FIND,
  ERR_NUM,              // Pocz¹tek sekcji komunikatów dotycz¹cych przetwarzania liczb.
  ERR_NUM_RANGE_IN,     // Zmienna któr¹ przekazano do przetwarzania posiada za du¿¹ dodatni¹ 
                        // lub za ma³¹ ujemn¹ wartoœæ wymagan¹ do przeprowadzenia obliczeñ.
  ERR_NUM_RANGE_OUT,    // Podczas oliczeñ wyprodukowano wartoœæ która nie mieœci siê w oczekiwanym zakresie
  ERR_PAR_BAD,          // Parametr metody nie nadaje siê do przetwarzania     
  ERR_SRC_BAD,          // Dane wejœciowe podczas przetwarzania okaza³y siê niepoprawne
  ERR_FUN               // Zwracany gdy wywo³ywana funkcja uznana jest za niedokoñczon¹
};

namespace old
{
const int ERR=                  0;
const int ERR_SIGNED=           ERR-1;
        // Liczba otrzymana w wyniku przetwarzania posiada znak gdy mia³a byæ bez znaku lub na odwrót
        // Patrz SIGNED, UNSIGNED, SIGNED_NOT_CHANGE.
const int ERR_RANGE=            ERR_SIGNED-1;
        // Zmienna poza zakresem. W wyniku opracji zmienna przyjmie wartoæ za du¿¹ dodatni¹ lub za ma³¹
        // ujemn¹ wartoæ
const int ERR_REDEF=               ERR_RANGE-1;
        // Pewna sta³a zmieni³a swoj¹ wartoæ lub próbowano wykonaæ czynnoæ zmieniaj¹c¹ wartoæ
        // obiektu oznaczonaego jako sta³y
const int ERR_NOT_FIND=            ERR_REDEF-1;
        // Nie znaleziono oczekiwanej wartoci
const int ERR_BAD_VALUE=           ERR_NOT_FIND-1;
        // Wartoæ któr¹ przekazano do dalszego przetwarzania jest nie w³aciwa.
        // Nie okrela siê ¿adnych bli¿szych informacji. Poprostu co nie tak z wartoci¹
const int ERR_NOT_VALUE=           ERR_BAD_VALUE-1;
        // Podczas przetwarzania okaza³o siê ¿e zmienna przekazana do przetwarzania choæ posiada
        // poprawn¹ strukturê nie pozwala okreliæ wartoci np pusty napis przekazany do obliczenia
        // wartoci liczbowej
const int ERR_BAD_DEF=             ERR_NOT_VALUE-1;
        // Wyra¿enie definiuj¹ce wartoæ jest nie poprawne. Nie okrelono przyczyny niepoprawnoci
        // Mo¿e to byæ z powodu z³ej sk³adni, z³ej liczby nawiasów lub niezdefiniowania jednego
        // ze sk³adników wyra¿enia
const int ERR_CALC_LATER =         ERR_BAD_DEF-1;
        // Podczas pobierania wartoæi symbolicznej u¿ywanej do obliczenia wartoci wyra¿enia
        // okaza³o siê ¿e choæ jest zdefiniowana to nie mo¿na by³o okreliæ jej wartoci i obliczenie
        // wyra¿enia nale¿y od³o¿yæ zwracaj¹c ten b³¹d
const int ERR_NULLFU      =        ERR_CALC_LATER-1;
        // Ten b³¹d zwraca funkcja która zosta³a zdefiniowana ale jedyne co robi to zwraca wartoæ
const int ERR_MATHOP       =       ERR_NULLFU-1;
        // B³¹d powsta³y podczas próby wykonania podstawowej operacji matemetycznej
const int ERR_DIV_0       =        ERR_MATHOP-1;
        // dzielenie przez zero
const int ERR_NOT_OPEN    =        ERR_DIV_0-1;
        // Nie otwarto, nie uruchomiono, nie otrzymano dostêpu do pliku, portu urz¹dzenia
const int ERR_NOT_CREATE   =       ERR_NOT_OPEN-1;
        // Oznacza nie tylko ¿e czegoœ nie by³o nie da³o siê otworzyæ ale te¿ ¿e mimo poprednich bêdów
        // nie powiod³a siê próba utworzenia
const int ERR_EOD           =      ERR_NOT_CREATE-1;
        // Plik zawiera nie pe³ne dane, Ÿle sformatowane lub z innego powodu podczas jego przetwarzania
        // osi¹gniêto koniec w nienaturalnych okolicznoœciach. Podczas przeszukiwania zbioru dotarto do koñca
const int ERR_FATAL          =     ERR_EOD-1;
const int ERR_THREAD_STOP     =    ERR_FATAL-1;
        // Awaryjne zakoñczenie w¹tku. W¹tek przerwano mimo trwania pracy (obliczeñ)
const int ERR_EOF              =   ERR_THREAD_STOP-1;
}

//##############################################################################
template <class KEY, class FIRST, class SECOND>
class three
{
public:
  KEY key;
  FIRST first;
  SECOND second;
  three(){/*...*/};
  three(KEY k,FIRST f,SECOND s)
  {
    key=k;
    first=f;
    second=s;
  };
  ~three(){/*...*/};
};

template <class KEY, class FIRST, class SECOND>
inline three<KEY,FIRST,SECOND> make_three(const KEY &k, const FIRST &f, const SECOND &s)
{
  return three<KEY,FIRST,SECOND>(k,f,s);
};

//##############################################################################
class CWyj
{
public:
  three<size_t , size_t, std::string> w;
  CWyj(size_t nr_,size_t par_,string kom_);
  ~CWyj(){/*...*/};
  three<size_t,size_t,string> get();
};

//##############################################################################
class eNFun
{
/*
 * Wyj¹tek zg³aszany przez wszystkie funkcje które z jakiegoœ powodu
 * nie zosta³y dokoñczone lub zosta³y uznane za niedokoñczone
 * a wykorzystane w programie
 */
public:
  eNFun(const string &funkcja_,const string &plik_,size_t wiersz_);
  string Co();
private:
  string funkcja;
  string plik;
  size_t wiersz;

};

typedef unsigned long                id_t;   // unikalna wartoœæ - identyfikator

typedef stack<double>                std_t;
typedef stack<string>                sts_t;

typedef set<double>                  sed_t;
typedef set<int>                     sei_t;
typedef set<size_t>                  ser_t;
typedef set<string>                  ses_t;

typedef multiset<double>             msed_t;
typedef multiset<int>                msei_t;
typedef multiset<size_t>             mser_t;
typedef multiset<string>             mses_t;

typedef vector<double>               vd_t;
typedef vector<int>                  vi_t;
typedef vector<size_t>               vr_t;
typedef vector<string>               vs_t;

typedef map<string,double>           msd_t;
typedef map<string,int>              msi_t;
typedef map<string,size_t>           msr_t;
typedef map<string,string>           mss_t;
typedef map<size_t,double>           mrd_t;
typedef map<size_t,int>              mri_t;
typedef map<size_t,size_t>           mrr_t;
typedef map<size_t,string>           mrs_t;

typedef multimap<string,double>      mmsd_t;
typedef multimap<string,int>         mmsi_t;
typedef multimap<string,size_t>      mmsr_t;
typedef multimap<string,string>      mmss_t;
typedef multimap<size_t,double>      mmrd_t;
typedef multimap<size_t,int>         mmri_t;
typedef multimap<size_t,size_t>      mmrr_t;
typedef multimap<size_t,string>      mmrs_t;



namespace old
{
typedef map<string,pair<string,double> >ms_sd;
}


#endif
