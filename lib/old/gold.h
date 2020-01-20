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
// sta�e matematyczne
//const double pi=3.1415926535897932385;
//const double e =2.7182818284590452354;

//------------------------------------------------------------------------------
// wymiary, rozmiary, domylne wartoci powstaj�cych zmiennych
const size_t size_m=numeric_limits<size_t>::max();

namespace old
{
  #define size_m2                 size_m/2
  #define DEFAULT_MAX_BUF_SIZE    8192
  #define DEFAULT_BUF_SIZE        256
  #define DEFAULT_MIN_BUF_SIZE    32
  #define DEFAULT_MAX_STR_SIZE    512
  #define DEFAULT_STR_SIZE        128
        // domylny rozmiar bufor�w przeznaczonych na napisy
};

//------------------------------------------------------------------------------
// parametry prze��czaj�ce (prze��czniki)
namespace old
{
#define NUL                     0
#define DEL_POS_START           NUL+1
#define NO_DEL_POS_START        NUL+2
        // Dotyczy usuwania danych z bufor�w. Metoda otrzymuj�ca lub odnajduj�ca samodzielnie warto�
        // w buforze mo�e potrzebowa� informacj� czy ma usun�� t� pozycje czy jest ona traktowana jako
        // granica usuwania.
#define DEL_LEFT                NUL+3
#define DEL_RIGHT               NUL+4
        // Dotyczy usuwania danych z bufor�w. Metody mog� usuwa� dane z bufor�w w kierunku rosn�cych
        // lub malej�cych indeks�w. Podanie jednej z tych wartoci naka�e usun�� elementy w kierunku
        // malej�cych index�w (DEL_LEFT) lub rosn�cych (DEL_RIGHT).
#define DEL_POS_STOP            NUL+5
#define NO_DEL_POS_STOP         NUL+6
        // Dotyczy usuwania danych z bufor�w. Metoda otrzymuj�ca a zw��szcza odnajduj�ca samodzielnie
        // pozycje zmykaj�cego elementu kasowany podzbi�r mo�e go potraktowa� jako granic� kasowania
        // lub ostatni element us�wanego podzbioru. Powy�sze zmienne s�u�a poinformowaniu metody o
        // post�powaniu z ostatnim elementem
#define SIGNED                  NUL+7
#define UNSIGNED                NUL+8
#define SIGNED_NOT_CHANGE       NUL+9
        // Gdy b�d� wykonywane operacje na zmiennych szczeg�lnie podczas r�nych konwersji mo�e mie�
        // znaczenie znak przetwarzanej zmiennej. Je�li warto� mo�e posiada� znak zezwalamy na to
        // parametrem SIGNED. Gdy warto� po przetworzeniunie mo�e posiada� znaku przekazujemy do
        // metody UNSIGNED. J�eli zmienna w wyniku operacji nie powinna zmieni� znaku ustawiamy
        // w wywo��niu metody parametr SIGNED_NOT_CHANGE.
        // Patrz: ERR_SIGNED
#define WITH_LIM                SIGNED_NOT_CHANGE+1
#define NO_WITH_LIM             WITH_LIM+1
        // Tam gdzie przetwarzanie odbywa si� na jakim przedziale to jego granica wejdzie do
        // przetwarzanego przedzia�u gdy podany zostanie w wywo�aniu parametr WITH_LIM.
        // Je�eli parametr znajduj�cy si� na granicy nie jest przedmioem zainteresowa�, nie mo�e ulec
        // zmianie podczas przetwarzania poda� warto� NO_WITH_LIM

};

//------------------------------------------------------------------------------
// komunikaty o b��dach
typedef int err_t;
string GetErrStr(err_t err_);
enum {
  OK,                   // Poprawnie
  ERR,                  // Dowolny nie okre�lony b��d (mo�e nie znany w miejscu wyst�pienia)
                        // Mo�na u�ywa� te� tam gdzie wystarcza proste poinformpwamoie o niepowodzeniu
  ERR_FILE,             // Pocz�tek sekcji b��d�w dotycz�cych pracy z plikami
  ERR_FILE_DATA,        // Dane umieszczone w pliku maj� z�y format
  ERR_FILE_OPEN,        // Nie powiod�a si� pr�ba otwarcia pliku (urz�dzenia-zasobu)
  ERR_FILE_READ,        // B��d podzczas odczytu danych. Prawdopodobnie osi�gni�to koniec
                        // pliku w przed pobraniem oczekiwanej ilo�ci danych
  ERR_FILE_WRITE,       // B��d zapisu do pliku. Prawdopodobnie nie by�o mo�liwe zapisanie 
                        // do pliku wymaganej ilo�ci danych
  ERR_FILE_CLOSE,       // Co� nie tak z zamkni�ciem plku (urz�dzenia)
  ERR_EOD,              // End Of Data - Koniec danych. Informuje �e wywo�anie funkcji dla 
                        // operacji na danych odby�o si� gdy brak jest danych. Mo�e to nast�pi� gdy 
                        // obecne wywo�anie jest kolejnym a poprzednie poprawnie przesz�y po ca�ym 
                        // zbiorze i zako�czy�y pobieranie danych
  ERR_NOT_FIND,
  ERR_NUM,              // Pocz�tek sekcji komunikat�w dotycz�cych przetwarzania liczb.
  ERR_NUM_RANGE_IN,     // Zmienna kt�r� przekazano do przetwarzania posiada za du�� dodatni� 
                        // lub za ma�� ujemn� warto�� wymagan� do przeprowadzenia oblicze�.
  ERR_NUM_RANGE_OUT,    // Podczas olicze� wyprodukowano warto�� kt�ra nie mie�ci si� w oczekiwanym zakresie
  ERR_PAR_BAD,          // Parametr metody nie nadaje si� do przetwarzania     
  ERR_SRC_BAD,          // Dane wej�ciowe podczas przetwarzania okaza�y si� niepoprawne
  ERR_FUN               // Zwracany gdy wywo�ywana funkcja uznana jest za niedoko�czon�
};

namespace old
{
const int ERR=                  0;
const int ERR_SIGNED=           ERR-1;
        // Liczba otrzymana w wyniku przetwarzania posiada znak gdy mia�a by� bez znaku lub na odwr�t
        // Patrz SIGNED, UNSIGNED, SIGNED_NOT_CHANGE.
const int ERR_RANGE=            ERR_SIGNED-1;
        // Zmienna poza zakresem. W wyniku opracji zmienna przyjmie warto� za du�� dodatni� lub za ma��
        // ujemn� warto�
const int ERR_REDEF=               ERR_RANGE-1;
        // Pewna sta�a zmieni�a swoj� warto� lub pr�bowano wykona� czynno� zmieniaj�c� warto�
        // obiektu oznaczonaego jako sta�y
const int ERR_NOT_FIND=            ERR_REDEF-1;
        // Nie znaleziono oczekiwanej wartoci
const int ERR_BAD_VALUE=           ERR_NOT_FIND-1;
        // Warto� kt�r� przekazano do dalszego przetwarzania jest nie w�aciwa.
        // Nie okrela si� �adnych bli�szych informacji. Poprostu co nie tak z wartoci�
const int ERR_NOT_VALUE=           ERR_BAD_VALUE-1;
        // Podczas przetwarzania okaza�o si� �e zmienna przekazana do przetwarzania cho� posiada
        // poprawn� struktur� nie pozwala okreli� wartoci np pusty napis przekazany do obliczenia
        // wartoci liczbowej
const int ERR_BAD_DEF=             ERR_NOT_VALUE-1;
        // Wyra�enie definiuj�ce warto� jest nie poprawne. Nie okrelono przyczyny niepoprawnoci
        // Mo�e to by� z powodu z�ej sk�adni, z�ej liczby nawias�w lub niezdefiniowania jednego
        // ze sk�adnik�w wyra�enia
const int ERR_CALC_LATER =         ERR_BAD_DEF-1;
        // Podczas pobierania warto�i symbolicznej u�ywanej do obliczenia wartoci wyra�enia
        // okaza�o si� �e cho� jest zdefiniowana to nie mo�na by�o okreli� jej wartoci i obliczenie
        // wyra�enia nale�y od�o�y� zwracaj�c ten b��d
const int ERR_NULLFU      =        ERR_CALC_LATER-1;
        // Ten b��d zwraca funkcja kt�ra zosta�a zdefiniowana ale jedyne co robi to zwraca warto�
const int ERR_MATHOP       =       ERR_NULLFU-1;
        // B��d powsta�y podczas pr�by wykonania podstawowej operacji matemetycznej
const int ERR_DIV_0       =        ERR_MATHOP-1;
        // dzielenie przez zero
const int ERR_NOT_OPEN    =        ERR_DIV_0-1;
        // Nie otwarto, nie uruchomiono, nie otrzymano dost�pu do pliku, portu urz�dzenia
const int ERR_NOT_CREATE   =       ERR_NOT_OPEN-1;
        // Oznacza nie tylko �e czego� nie by�o nie da�o si� otworzy� ale te� �e mimo poprednich b�d�w
        // nie powiod�a si� pr�ba utworzenia
const int ERR_EOD           =      ERR_NOT_CREATE-1;
        // Plik zawiera nie pe�ne dane, �le sformatowane lub z innego powodu podczas jego przetwarzania
        // osi�gni�to koniec w nienaturalnych okoliczno�ciach. Podczas przeszukiwania zbioru dotarto do ko�ca
const int ERR_FATAL          =     ERR_EOD-1;
const int ERR_THREAD_STOP     =    ERR_FATAL-1;
        // Awaryjne zako�czenie w�tku. W�tek przerwano mimo trwania pracy (oblicze�)
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
 * Wyj�tek zg�aszany przez wszystkie funkcje kt�re z jakiego� powodu
 * nie zosta�y doko�czone lub zosta�y uznane za niedoko�czone
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

typedef unsigned long                id_t;   // unikalna warto�� - identyfikator

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
