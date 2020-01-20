#ifndef NAPISY_H
#define NAPISY_H

#include <ctype>
//#include <list>
//#include <vector>
#include <set>
#include <string>
#include "gold.h"

using namespace std;

void Add(string &str_,const string &ns_,size_t start_=string::npos,char c_=' ');
/*
 * Dodaje napis do istniej�cego umieszczaj�c jego pierwszy znak na pozycji start_. Wi�rze si� to z
 * konieczno�ci� powi�kszenia bufora. Je�eli index start_ zachodzi na stary napis to zostaje zmodyfikowana
 * jego warto�� tak by nast�pi�o rzeczywiste dodanie napisu a nie nadpisanie. Je�eli mi�dzy pozycj�
 * start_ a ko�cem macierzystego napisu istnieje nie wykorzystana przestrze� wype�niona zostanie znakiem c_.
 *we:
 * str_: napis do kt�rego ma by� dodany nowy tekst
 * ns_: napis dodawany do tego napisu
 * start_: indeks pozycji na, kt�rej umieszczony zostanie pierwszy znak dodawanego napisu. Zmienna ta jest
 *   modyfikowana gdy wskazuje na pozycj� wewn�trz tego napisu.
 * c_: znak kt�rym zostanie wype�niony nie wyko�ystany obszar pomi�dzy ko�cem tego napisu a pierwszym
 *   znakiem dodawanego.
 */
err_t cena(const string &s, size_t &i,double &d){};// propozycja
err_t cena(const double &d, string &s){};
size_t d2s(string &str_,double d_,size_t round_,size_t poz_=0,char c_='0');
/*
 * Przekszta�ca liczb� typu double w string. Je�eli round >0 to zaokr�gla ilo�� miejsc po przecinku
 * do tej ilo�ci. Gdy round == 0 wynik nie jest zaokr�glany. Zmienna poz_ powinna zawiewra� d�ugo�� ca�ego
 * ci�gu po przetworzeniu liczby d_. Je�eli liczba jest kr�tsza od poz_ to ci�g uzupe�niany jest odpowiedni�
 * ilo�ci� znak�w c_. Je�eli liczba jest d�u�sza nie dzieje si� nic. Warto�� zwracana informuje o d�ugo�ci
 * liczby, nie uwzgl�dnia znak�w wiod�cych. Gdy ta warto�� jest wi�ksza od poz_ wnioskujemy �e liczba
 * jest d�u�sza od przewidzianego rozmiaru.
 */
size_t i2s(string &str_,int val_,size_t poz_=0,char c_='0');
/*
 * Tekstow� posta� liczby val_ dopisuje do buf_. Je�eli poz_ jest wi�ksza od 0 to zwracany napis
 * b�dzie dope�niany wiod�cymi znakami przekazanymi w c_ tak by osi�gn�� ilo�� liczb przekazanych w poz_.
 * Funkcja zwraca ilo�� znak�w tworz�cych liczb�, nie uwzg�dnia znak�w wiod�cych.
 */
string i2s(int i);
/*
 * zamienia int na string nie zwracaj�c b��du.
 */
err_t FileToString(string &buf,const string &path);
/*
 * Przepisuje plik tekstowy path do buf
 * Zwracane b��dy:
 * ERR_FILE_OPEN
 * ERR_FILE_READ
 */
err_t GetInt(const string &buf,int &out_,int signed_);
/*
 * Je�eli jest to mo�liwe funkcja przetworzy wewn�trzny napis i zwr�ci go w zmiennej out_.
 * Napis musi sk�ada� si� z jednego wyrazu zbudowanego ze znak�w 0..9 i a..f. Funkcja rozpoznaje
 * r�wnie� oznaczenia 0x i h dla liczb szesnastkowych
 *we:
 * signed_: informuje czy ma wymusza� tworzenie liczb ze znakiem gdy na przyk�ad napis wygl�da tak: 0xf2
 * czy traktowa� tak�liczb� jak bez znaku
 * signed_==SIGNED - ze znakiem jak sugeruje napis
 * signed_==UNSIGNED - liczba jest bez znaku
 *wy:      jeszcze nie prawda
 * je�eli <0 to jaki� b��d:
 * ERR_SIGNED - zmiena jest ujemna a w wywo�aniu metody zarz�dano UNSIGNED
 * ERR_RENGE - zmiennej number_ nie da si� przedstawi� na ilo�ci cyfr okre�lonej przez digit_
 */
size_t Find(const string &source_,const string &find_,size_t start_,bool sep_);
/*
 * Szuka napisu find_ w napisie source_ nie zwracaj�c uwagi na wielko�� liter. Funkcja powsta�a
 * w�a�nie z tego powodu poniewa� metoda find klasy string rozru�nia wielko�� znak�w.
 * Je�eli napis nie zostanie znaleniony zwraca warto�� size_m a je�eli zosta� znaleziony
 * zwraca pozycje pierwszego znalezionego znaku w przeszukiwanym tek�cie.
 * we:
 *  start_: pozcja od kt�rej rozpocz�� szukanie tekstu find
 *  sep_  : je�eli true to odnaleziony napis musi by� ograniczony znakami bia�ymi
 *          lub interpunkcyjnymi lub pocz�tkiem i ko�cem napisu
 *          je�eli false to napis mo�e by� cz�ci� innego wyrazu
 * wy:
 *  return - pozycja pierwszego znaku szukanego tekstu w tekscie przeszukiwanym
 *  if reurn==size_m nie znaleziono
 */
bool Log(const string plik,const string &log,bool add=true);
string r2s(size_t i); 
err_t s2d(const string &s,double &d);
/*
 * Przekszta�ca podany napis "s" w liczb� typu double.
 * Podany napis mo�e by� liczb� o mniejszej precyzji ale musi by� liczb� w zapisie dziesi�tnym
 */
err_t StringToFile(const string &buf,const string &path);
/*
 * Zapisuje napis do pliku.
 * Mo�e zwr�ci� rodzaje b��d�w:
 * ERR_PAR_BAD - w przypadku gdy podano z�� scie�k� dost�pu
 * ERR_FILE_OPEN - w przypadku nie mo�no�ci otwarcia pliku
 * ERR_FILE_WRITE - w przypadku b��du podczas zapisu do pliku
 */
string ul2s(size_t i);

//##############################################################################
class CFileConfig
{
protected:
  mss_t mss_cfg;
    // Mapa zawieraj�ca tekstowe parametry konfiguracyjne
  msi_t msi_cfg;
    // Mapa zawieraj�ca parametry konfiguracyjne typu int
  string root_name;
    // G��wna nazwa wyko�ystywana do nazywania plik�w programu jego skryptu konfiguracyjnego itp
    // rozr�nianie odbywa si� przez rozszerzenie.
    // Np: bin_path+"\\"+root_name+".exe"
    //     bin_path+"\\"+root_name+".log"
    //     bin_path+"\\"+root_name+".cfg"
  string bin_path;
    // Scie�ka do katalogu w kt�rym znajduje si� g��wny plik programu
public:
  CFileConfig(){/*...*/};
  ~CFileConfig(){/*...*/};

  err_t Init(const string & root_name_);
  /*
   * Podaje do wn�trza obiektu  cz�� root plik�w
   * Wywo�ywana jest metoda ReadCfg(). Je�eli w pliku konfiguracyjnym zjajduj� si� klucze rozpoczynaj�ce
   * si� od ci�gu "dir_" to wszystkie te katalogi zostan� utworzone je�eli nie istniej�. Je�eli
   * konfiguracja tego wymaga czyszczony jest plik z logami po poprzedniej pracy programu.
   */
  err_t GetConfig(const string &key,int &i_val);
  err_t GetConfig(const string &key,string &s_val);
  /*
   * Pobiera z pliku konfiguracyjnego warto�� klucza : "key". Je�eli nie znajdzie podanego klucza zwraca
   * b��d ERR_NOT_FIND.
   */
  int GetOption(const string &key);
  /*
   * Zwraca warto�� klucza "key" dla przypadku gdy jego warto�� jest typu int. W przypadku wyst�pienia b��du
   * zwraca size_m2.
   */
  err_t SetConfig(const string &key,int &i_val);
  err_t SetConfig(const string &key,string &s_val);
  /*
   * Zapisuje dane do pliku konfiguracyjnego. Klucze mog� mie� warto�ci int lub string ale w pliku
   * w pliku configuracyjnym s� to zawsze napisy.
   */
private:
  err_t ReadConfig();
  /*
   * Odczytuje plik konfiguracyjmny i wype�nia mapy mss_cfg i msi_cfg.
   */
  err_t SaveConfig();
  /*
   * Zapisuje do pliku konfiguracyjnego zmienione warto�ci parametr�w przechowywanych w mapach ..._cfg
   */
};







//-----------------------------------------------------------------------------



namespace old
{
////////////////////////////////////////////////////////////////////////////////
//      WSTAWIENIE
////////////////////////////////////////////////////////////////////////////////
int AddAsBin(string &buf,int number_,size_t pos_);
/*
 * Dodaje liczb� : "number_" na ko�cu napisu : "buf". String przybiera form� 011010011B gdzie ilo��
 * zer i jedynek koniecznych do poprwanego przedstawienia warto��i jest dope�niana zerami wiod�cymi
 * do pe�nego rozmiaru typu mieszcz�cego t� warto�� np warto�� 1 do 00000001B a 256 0000000100000000B
 *we:
 * buf : napis do kt�rego ma by� dodana liczba w zapisie binarnym
 * number_ : liczba dodawana w zapisie binarnym
 * pos_ : pozycja na kt�rej wstawiony zostanie number_. Je�eli pos_>buf.size() to napis  b�dzie
 * dodany.
 *wy:
 * je�eli <0 to b��d
 */
#define HEX_C 0
#define HEX_ASM 1
#define HEX_NULL 2
#define ENDIAN_BIG 4
int AddAsHex(string &buf,int number_,int digit_,int signed_,int typ_, size_t pos_);
/*
 * dodaje liczb� na ko�cu napisu zapisuj�c j� w formacie szesnastkowym u�ywaj�c do tego ilo�� pozycji
 * okre�lonej zmienn� digit_
 *we:
 * number_: liczba do zapisania
 * digit_: ilo�� cyfr przeznaczona na zapis liczby
 * signed_: podan� warto�� _number traktuj jako ze znakiem nawet gdy _signed==SIGNED
 *          gdy _signed==UNSIGNED a _number <0 zwr�� b��d
 * typ_: HEX_C - liczba zostanie zapisana w stylu j�zyka C : 0xa45f
 *       HEX_ASM - liczba zostanie zapisana w stylu assemblera : 0a45fh
 *       HEX_NULL - poprostu : a45f
 * pos_: pozycja na kt�r� zostanie wstawiony string reprezentuj�cy przetworzon� liczb�
 *       je�eli pos > buf.size() to napis b�dzie dodany
 *wy:
 * je�eli <0 to jaki� b��d:
 * ERR_SIGNED - zmiena jest ujemna a w wywo�aniu metody zarz�dano UNSIGNED
 * ERR_RENGE - zmiennej _number nie da si� przedstawi� na ilo�ci cyfr okre�lonej przez _digit
 */
void AddAsInt(string &buf,int number_,size_t pos_);
/*
 * wstawia liczb� na pozycji pos_ buforu buf.
 */
err_t cena(string &s);
err_t cena(string &s,double &d);
/*
 * s musi mie� tak� budow� by da� si� przedstawi� w postaci ceny XXXXXX,XX. Je�eli nie to pr�buje poprawi�
 * jej budow�. Je�eli budowa jest poprawna zwraca w d liczb� odpowiednio zaokr�glon� a w s skoorygowan�
 * posta� ceny. Je�eli nie ERR_PAR_BAD.
 */
string d2s(double d,int round);
/*
 * Prezekszta�ca liczb� typu double w string. Je�eli round >0 to zaokr�gla ilo�� miejsc po przecinku
 * do tej ilo�ci. Gdy (round < 0) wynik nie jest zaokr�glany.
 */

size_t FiltrDaty(string &data_);
/*
 * Sprawdza czy data zapisana jest w poprawnej formie. Format daty : RRRR-MM-DD
 * Nie poprawno�ci w stylu 1-1-1 poprawiane s� na 2001-01-01.
 * je�eli data jest poprawna zwraca warto�� wi�ksz� ni� rozmiar dekstu je�eli data jest b��dna
 * zwraca indeks pierwszego niepoprawnego znaku.
 */

void New(string &buf,const string &s_,const string &t_);
/*
 * czyta podnapis z napisu s_ do napotkania kt�regokolwiek ze znak�w tworz�cego napis t_.
 * Je�eli nie podano napisu t_ kopiowany jest ca�y napis s_.
 * Funkcja zwraca d�ugo�� napisu. Je�eli zwr�ci warto�� 0 nie skopiowano �adnych danych.
 * Warto�ci ujemne informuj� o b��dzie.
 */
err_t FileRead(string &buf,const string &path_);
/*
 * Odzczytuje plik tekstowy i zapisuje go w ca�o�ci do jednego stringu : buf
 */
err_t FileWrite(string &buf,const string &path_);
/*
 * Zapisuje zawarto�� stringu buf do pliku file_
 */
string GetBlock(const string &s,size_t &ix_);
/*
 * Pobiera tekst stanowi�cy spuj� ca�o��.
 * Je�eli pierwszym znakiem jest otwarty nawias to funkcja zwraca jego wn�trze.
 * Je�eli pierwszym znakiem jest alnum lub '_' to zrwaca string do pierwszego znaku nie b�d�cego alnum lub '_'
 * je�eli napotka znaki bia�e opuszcza je i post�puje zgodnie z przedstawionymi zasadami
 * Je�eli nie otworzono nawiasu to znaki nie b�d�ce alnum lub '_' ko�cz� blok
 * Je�eli napotka co� innego nic nie zwraca
 */
err_t GetDouble(string s_, double &out_,int signed_);
/*
 * Je�eli jest to mo�liwe funkcja przetworzy wen�trzny napis i zwr�ci go w zmiennej out_.
 * Napis musi sk�ada� si� z jednego wyrazu zbudowanego ze znak�w 0..9 i a..f. Funkcja rozpoznaje
 * r�wnie� oznaczenia 0x i h dla liczb szesnastkowych
 *we:
 * signed_: informuje czy ma wymusza� tworzenie liczb ze znakiem gdy na przyk�ad napis wygl�da tak: 0xf2
 * czy traktowa� tak� liczb� jak bez znaku
 * signed_==SIGNED - ze znakiem jak sugeruje napis
 * signed_==UNSIGNED - liczba jest bez znaku
 *wy:      jeszcze nie prawda
 * je�eli <0 to jaki� b��d:
 * ERR_SIGNED - zmiena jest ujemna a w wywo�aniu metody zarz�dano UMSIGNED
 * ERR_RENGE - zmiennej number_ nie da si� przedstawi� na ilo�ci cyfr okre�lonej przez digit_
 */
string GetExpr(const string &buf,size_t &st_);
/*
 * Pobiera z buf ci�g string b�d�cy wyra�eniem z�o�onym.
 * Je�eli wya�enie umieszczone jest w nawiasie zwraca string znajduj�cy si� wewn�trz nawiasu
 * bez przednich i tylnych znak�w bia�ych. parametr st_ ustawiany jest na pierwsz� pozycj� po
 * wyra�eniu ale te� za nawiasem gdy wyra�enie umieszczone by�o w nawiasie.
 */
err_t GetInt(const string &buf,int &out_,int signed_);
/*
 * Je�eli jest to mo�liwe funkcja przetworzy wewn�trzny napis i zwr�ci go w zmiennej out_.
 * Napis musi sk�ada� si� z jednego wyrazu zbudowanego ze znak�w 0..9 i a..f. Funkcja rozpoznaje
 * r�wnie� oznaczenia 0x i h dla liczb szesnastkowych
 *we:
 * signed_: informuje czy ma wymusza� tworzenie liczb ze znakiem gdy na przyk�ad napis wygl�da tak: 0xf2
 * czy traktowa� tak�liczb� jak bez znaku
 * signed_==SIGNED - ze znakiem jak sugeruje napis
 * signed_==UNSIGNED - liczba jest bez znaku
 *wy:      jeszcze nie prawda
 * je�eli <0 to jaki� b��d:
 * ERR_SIGNED - zmiena jest ujemna a w wywo�aniu metody zarz�dano UMSIGNED
 * ERR_RENGE - zmiennej number_ nie da si� przedstawi� na ilo�ci cyfr okre�lonej przez digit_
 */
err_t GetIntH(const string &buf,int &out_,int signed_);
/*
 * Tak jak funkcja GetInt() lecz buf musi zawiera� napis przedstawiaj�cy liczb� szesnastkow� ale bez
 * oznacze� przedrostka 0x i przyrostka h. Funkcja przeznaczona jest do operowania na liczbach
 * szesnastkowych w obr�bie wewn�trznych struktur przetwa�aj�cych dane.
 */
string GetProgr(const string &buf,size_t &sta_ix_,size_t &sto_ix_);
/*
 * Tak jak GetWord() lecz wyrazem jest ci�g znak�w alpha+digit+_
 */
err_t GetULong(const string & str, unsigned long &l_);

//string GetWord(const string &buf,int start_);
/*
 * Zwraca s�owo zaczynaj�ce si� pierwszym znakiem alpha na pozycji lub po _start a ko�czoc� na ostatnim znaku
 * tego ci�gu znak�w alfabetu
 */

int ispl(int c);
int isPL(int c);
int my_isalpha(int c);
int my_isalnum(int c);
int my_islower(int c);
int my_isupper(int c);
int my_tolower(int c);
int my_toupper(int c);
int my_isprint(int c);
int my_isgraph(int c);

void my_toupper(string &s_);


string i2s(int i);
char PrevAlpha(const string &buf,size_t &i_);
char NextAlpha(const string &buf,size_t &i_);
/*
 * Rozpoczynaj�c na pozycji _i metoda przegl�da bufor w poszukiwaniu pisanego znaku.
 *we: i_
 * pozycja od kt�rej nale�y zacz�� przeszukiwanie
 *wy: i_
 * -1: dotarto do ko�cz napisu i nie znaleziono �adnego pisanego znaku
 * >=_i: pozycja na kt�rej wyst�puje kolejny znak
 */
char PrevProgr(const string &buf,size_t &i_);
char NextProgr(const string &buf,size_t &i_);
char PrevPrint(const string &buf,size_t &i_);
char NextPrint(const string &buf,size_t &i_);
char PrevWhite(const string &buf,size_t &i_);
char NextWhite(const string &buf,size_t &i_);
char PrevSpace(const string &buf,size_t &i_);
char NextSpace(const string &buf,size_t &i_);
char PrevNoWhite(const string &buf,size_t &i_);
char NextNoWhite(const string &buf,size_t &i_);

bool cs(const string &s_lv,const string &s_pv);
/*
 * Por�wnuje nie uwzgl�dniaj�c wielko�ci liter.
 *wy:
 * true gdy r�wne
 */
int csort(const string &s_lv,const string &s_pv);
/*
 * if return >0 klejno�� parametr�w zgodna z kolejno�ci� napis�w
 * if return == 0 napisy r�wne
 * if return <0 kolejno�� parametr�w nie zgodna z kolejno�ci� napis�w
 * Do por�wnania stosowana jest taplica polchar
 */
bool csu(const string &s_lv,const string &s_pv);
/*
 * Por�wnuje nie uwzgl�dniaj�c wielko�ci liter. Jednak zak�ada �e drugi znak sk�ada si� tylko z du�ych liter.
 * To poto by nie potrzebnie nie powi�ksza� znak�w dla tekstu podanego bezpo�rednio - nie przez zmienn�
 *wy:
 * true gdy r�wne
 */
size_t csdorozny(const string &lv,const string &pv);
/*
 * Por�wnuje dwa stringi zwracaj�c indeks pierwszego znaku na kt�rym oba napisy zaczynaj� si� r�ni�
 */
size_t csudorozny(const string &lv,const string &pv);
/*
 * Por�wnuje dwa stringi zwracaj�c indeks pierwszego znaku na kt�rym oba napisy zaczynaj� si� r�ni�.
 * funkcja podnosi wszystkie znaki przed por�wnaniem
 */
size_t Find(const string &s_source_,const string &s_find_,size_t start,bool sep_);
/*
 * Szuka napisu s_find_ w napisie s_source_ nie zwracaj�c uwagi na wielko�� liter. Funkcja powsta�a
 * w�a�nie z tego powodu poniewa� metoda find klasy string rozru�nia wielko�� znak�w.
 * Je�eli napis nie zostanie znaleniony zwraca warto�� size_m a je�eli zosta� znaleziony
 * zwraca pozycje pierwszego znalezionego znaku w przeszukiwanym tek�cie.
 * we:
 *  start: pozcja od kt�rej rozpocz�� szukanie tekstu find
 *  sep_ : je�eli true to odnaleziony napis musi by� ograniczony znakami bia�ymi
 *         lub interpunkcyjnymi lub pocz�tkiem i ko�cem napisu
 *         je�eli false to napis mo�e by� cz�ci� innego wyrazu
 * wy:
 *  return - pozycja pierwszego znaku szukanego tekstu w tekscie przeszukiwanym
 *  if reurn==size_m nie znaleziono
 */
void DelSpaceFlank(string &buf);
void DelSpaceLeft(string &buf);
void DelSpaceRight(string &buf);
void Pack(string &buf);
/*
 *dzia�anie:
 *  Us�wa z napisu wszystkie znaki bia�e.
 */
string Param(const string &buf,size_t &ix_);
/*
 * Rozpoczyna przetwarzanie na podanej pozycji i ko�czy przecinkiem lub znakiem pierwszym zamkni�tym
 * nawiasem bez pary. Po wyj�ciu z funkcji iX_ zawiera pozycj� pierwszego nie przetworzonego znaku.
 * Zwr�cony napis pozbawiony jest bia�ych znak�w bocznych.
 */
string Read(const string &s_,size_t &ix_,string s_lim);
/*
 * Czyta podnapis z napisu s_ i zwraca go na wyjscie. Bia�e znaki wiod�ce nie s� dodawane do wyniku.
 * Zmienna ix_ wskazuje na pierwszy znak za odczytanym napisem.
 * ix_ - Index pierwszego znaku branego do przetwarzania.
 *       Po wykonaniu funkcji ix_ zawiera index pierwszego nie przetworzonego znaku
 *       lub string::npos gdy dosz�o do ko�ca napisu
 * s_lim - Napis zawieraj�cy znaki kt�re wyznaczaj� granic� przeszukiwania
 */
string Shift(string &buf,size_t sw,string s_);
/*
 * wys�wa z napisu ci�g znak�w (podnapis) rozpoczynaj�cy si� na pozycji 0 a ograniczonym dowolnym ze znak�w
 * wchodz�cym w sk�ad napisu s_. Znaki tworz�ce napis t_ s� us�wane z tego napisu pocz�wszy od
 * pierwszego znaku po wysuni�tym napisie a� do pierwszego znaku nie nale��cego do napisu t_.
 * WITH_LIM
 * NO_WITH_LIM
 */
string ShiftToken(string &buf);
/*
 * Wys�wa z napisu podan� ilo�� znak�w. Je�eli nie ma podanej ilo�ci znak�w w napisie zwraca  "\0"
 */
string ShiftParam(string &s_);
/*
 * wys�wa z podanego napisu wszystko od jego pocz�tku do napotkania przecinka.
 * Napis zwr�cony przez funkcj� oczyszczony jest z bocznych spacji. Z napisu wej�ciowego us�wany
 * jest przecinek oraz przednie spacje.
 */
string Token(const string &str,size_t &st,size_t &sp);
/*
 * Wywo�ywanie funkcji:
 * we:
 *  str: napis rozk�adany na tokeny
 *  st: zmienna przechowuj�ca pozycj� na kt�rej rozpoczyna si� analiz� stringu str
 *      Przy powrocie zawiera now� warto�� je�li start przesun�� si� ze wzgl�du na znaki bia�e
 *  sp: po powrocie wskazuje na nast�n� pozycj� za ostatnim znakiem rozpoznanego tokenu.
 * return:
 *  je�eli rozpoznano token zwraca go lub ""
 *
 * Opis:
 * Token:
 * - pojedynczy symbol
 * - to co znajduje si� pomi�dzy tym symbolem lub spacj� a kolejnym symbolem lub spacj�
 * - dwa znaki interpunkcyjne '.' i '_' (kropka i podkre�lenie) zalicza si� do znak�w alphanumerycznych
 *   (liczby i litery) gdy:
 *   '_': styka si� cho� jednym bokiem z liczb� lub liter�.
 *   '.': ma po prawej stronie liczb�
 * - liczba naukowa
 * Podzia� na tokeny:
 *
 */
void ToUpper(string &s_);
/*
 * zamienia na du�e wszystkie znaki napisu s_
 */
string Transfer(string &s_,size_t st_=0,size_t sp_=string::npos);
/*
 * Zabiera podnapis z napisu s_ i przenosi go na wyj�cie.
 * st_ - index pierwszego zabieranego znaku
 * sp_ - index ostatniego zabieranego znaku
 */
string Transfer(string &s_,size_t st_=0,char c_=' ');
/*
 * Zabiera podnapis z napisu s_ i przenosi go na wyj�cie.
 * st_ - index pierwszego zabieranego znaku
 * c_  - znak na kt�rym ma si� zako�czy� pobierany tekst
 */
string Transfer(string &s_,char c_,size_t sp_=string::npos);
/*
 * Zabiera podnapis z napisu s_ i przenosi go na wyj�cie.
 * c_ - szukany od pocz�tku napisu znak od kt�rego ma si� rozpocz�� pobieranie napisu
 * sp_ - pozycja ostaniego znaku pobieranego tekstu
 */
///////////////////////////////////////////////////////////////////////////////
//      INLINE
///////////////////////////////////////////////////////////////////////////////
bool Nul(const string &buf);
/*
 * Zwraca true gdy napis jest "" lub zawiera tylko znaki bia�e.
 */

//##############################################################################
class TExpr
//##############################################################################
{
protected:
  string infix;
  size_t ix;
    // wskazuje na pozycje znaku nast�pnego do przetworzenia
  vs_t postfix;
  old::ms_sd *def;
public:
  TExpr(){infix="";};
  TExpr(const string &s_):infix(s_){
        };
  TExpr &operator = ( const string &s_){
          if(infix != s_)  {
            infix=s_;
          };
          return *this;
        };
  err_t d_Calculate(ms_sd *def_,double &d_val_);
  err_t f_Calculate(ms_sd *def_,float &f_val_);
  err_t i_Calculate(ms_sd *def_,int &i_val_);
protected:
  err_t Correct();
  /*
   * Przed obliczeniem warto�ci wyra�enia nale�y skorygowa� oprawno�� zapisu. Poniewa� u�ytkownik
   * mo�e u�y� zapisu np: 5+ -(4+2)... lub np ...+7)(5*34)... jako poprawnych matematycznie lecz nie
   * przystosowanych do przetwarzania odwrotn� notacj� polsk�. Aby mo�na by�o dalej przetwarza� ten
   * string nale�y konstrukcje pierwszego typu zast�pi� w miejsce "-" wstawi� "(0-1)*" czyli
   * 5+(0-1)*(4+2)... . W przypadku drugim zast�pujemy "...) (..." napisem : "...)*(..." i mamy
   * ...+7)*(5*34)...".
   */
  err_t expr(double &d_val_);
  bool InLong(double d_);
  /*
   * Sprawdza czy warto�� double mo�na przekszta�ci� na long. Jest to do�� trudne do spe�nienia
   * ale podczas przetwarzania wyra�e� zawieraj�cych operatory arytmetyczne konieczne. Tworz�c
   * wyra�enie zawieraj�cych operaory logiczne nale�y pami�ta� by nie dochodzi�o do tworzenia
   * warto�ci ujemnych.
   */
  bool IsOp(const string &op);
  bool IsOp();
  /*
   * Zwraca true gdy ci�g lub pojecynczy znak jest operatorem np + lub and
   */
  err_t OP(double &d_lv,const string & op_, double d_pv);
  /*
   * Metoda wykonyje zapisan� operacj� op_ na ziennych dlv i dpv.
   * Metoda ma kontrolowa� poprawno�� wykonania operacji ale na razie tego nie robi
   */
  bool OP12(const string &op1,const string &op2);
  /*
   * Metoda dokonuje testu pierwsze�stwa wykonania dw�ch operacji. Je�eli ich kolejno��
   * odpowiada przyj�tym regu�om w matematyce zwraca true je�eli nie zwraca false.
   */
  size_t PO(const string &op);
  /*
   * Zwraca warto�� liczbow� priorytetu operatora
   */
};

err_t d_Calculate(const string &s_, ms_sd *def_,double &d_val_);
err_t f_Calculate(const string &s_, ms_sd *def_,float &f_val_);
err_t i_Calculate(const string &s_, ms_sd *def_,int &i_val_);

//##############################################################################
class CFG
//##############################################################################
{
private:
  string scrypt;
    // tre�� pliku konfiguracyjnego
  string path;
    // �cie�ka dost�pu wraz z nazw� pliku
public:
  CFG(){scrypt="";path="";};
  CFG(const string &scrypt_,const string &path_){scrypt=scrypt_;path=path_;};
  ~CFG(){};
  void Init(const string &scrypt_,const string &path_){scrypt=scrypt_;path=path_;};
  err_t Get(const string &key_,string &val_);
  err_t Get(const string &key_,int &val_);
  err_t Read();
  err_t Save();
  void Set(const string &key_,const string &val_);
  void Set(const string &key_,int val_);
};


};

#endif
