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
 * Dodaje napis do istniej¹cego umieszczaj¹c jego pierwszy znak na pozycji start_. Wi¹rze siê to z
 * koniecznoœci¹ powiêkszenia bufora. Je¿eli index start_ zachodzi na stary napis to zostaje zmodyfikowana
 * jego wartoœæ tak by nast¹pi³o rzeczywiste dodanie napisu a nie nadpisanie. Je¿eli miêdzy pozycj¹
 * start_ a koñcem macierzystego napisu istnieje nie wykorzystana przestrzeñ wype³niona zostanie znakiem c_.
 *we:
 * str_: napis do którego ma byæ dodany nowy tekst
 * ns_: napis dodawany do tego napisu
 * start_: indeks pozycji na, której umieszczony zostanie pierwszy znak dodawanego napisu. Zmienna ta jest
 *   modyfikowana gdy wskazuje na pozycjê wewn¹trz tego napisu.
 * c_: znak którym zostanie wype³niony nie wyko¿ystany obszar pomiêdzy koñcem tego napisu a pierwszym
 *   znakiem dodawanego.
 */
err_t cena(const string &s, size_t &i,double &d){};// propozycja
err_t cena(const double &d, string &s){};
size_t d2s(string &str_,double d_,size_t round_,size_t poz_=0,char c_='0');
/*
 * Przekszta³ca liczbê typu double w string. Je¿eli round >0 to zaokr¹gla iloœæ miejsc po przecinku
 * do tej iloœci. Gdy round == 0 wynik nie jest zaokr¹glany. Zmienna poz_ powinna zawiewraæ d³ugoœæ ca³ego
 * ci¹gu po przetworzeniu liczby d_. Je¿eli liczba jest krótsza od poz_ to ci¹g uzupe³niany jest odpowiedni¹
 * iloœci¹ znaków c_. Je¿eli liczba jest d³u¿sza nie dzieje siê nic. Wartoœæ zwracana informuje o d³ugoœci
 * liczby, nie uwzglêdnia znaków wiod¹cych. Gdy ta wartoœæ jest wiêksza od poz_ wnioskujemy ¿e liczba
 * jest d³u¿sza od przewidzianego rozmiaru.
 */
size_t i2s(string &str_,int val_,size_t poz_=0,char c_='0');
/*
 * Tekstow¹ postaæ liczby val_ dopisuje do buf_. Je¿eli poz_ jest wiêksza od 0 to zwracany napis
 * bêdzie dope³niany wiod¹cymi znakami przekazanymi w c_ tak by osi¹gn¹æ iloœæ liczb przekazanych w poz_.
 * Funkcja zwraca iloœæ znaków tworz¹cych liczbê, nie uwzgêdnia znaków wiod¹cych.
 */
string i2s(int i);
/*
 * zamienia int na string nie zwracaj¹c b³êdu.
 */
err_t FileToString(string &buf,const string &path);
/*
 * Przepisuje plik tekstowy path do buf
 * Zwracane b³êdy:
 * ERR_FILE_OPEN
 * ERR_FILE_READ
 */
err_t GetInt(const string &buf,int &out_,int signed_);
/*
 * Je¿eli jest to mo¿liwe funkcja przetworzy wewnêtrzny napis i zwróci go w zmiennej out_.
 * Napis musi sk³adaæ siê z jednego wyrazu zbudowanego ze znaków 0..9 i a..f. Funkcja rozpoznaje
 * równie¿ oznaczenia 0x i h dla liczb szesnastkowych
 *we:
 * signed_: informuje czy ma wymuszaæ tworzenie liczb ze znakiem gdy na przyk³ad napis wygl¹da tak: 0xf2
 * czy traktowaæ tak¹liczbê jak bez znaku
 * signed_==SIGNED - ze znakiem jak sugeruje napis
 * signed_==UNSIGNED - liczba jest bez znaku
 *wy:      jeszcze nie prawda
 * je¿eli <0 to jakiœ b³¹d:
 * ERR_SIGNED - zmiena jest ujemna a w wywo³aniu metody zarz¹dano UNSIGNED
 * ERR_RENGE - zmiennej number_ nie da siê przedstawiæ na iloœci cyfr okreœlonej przez digit_
 */
size_t Find(const string &source_,const string &find_,size_t start_,bool sep_);
/*
 * Szuka napisu find_ w napisie source_ nie zwracaj¹c uwagi na wielkoœæ liter. Funkcja powsta³a
 * w³aœnie z tego powodu poniewa¿ metoda find klasy string rozru¿nia wielkoœæ znaków.
 * Je¿eli napis nie zostanie znaleniony zwraca wartoœæ size_m a je¿eli zosta³ znaleziony
 * zwraca pozycje pierwszego znalezionego znaku w przeszukiwanym tekœcie.
 * we:
 *  start_: pozcja od której rozpocz¹æ szukanie tekstu find
 *  sep_  : je¿eli true to odnaleziony napis musi byæ ograniczony znakami bia³ymi
 *          lub interpunkcyjnymi lub pocz¹tkiem i koñcem napisu
 *          je¿eli false to napis mo¿e byæ czêœci¹ innego wyrazu
 * wy:
 *  return - pozycja pierwszego znaku szukanego tekstu w tekscie przeszukiwanym
 *  if reurn==size_m nie znaleziono
 */
bool Log(const string plik,const string &log,bool add=true);
string r2s(size_t i); 
err_t s2d(const string &s,double &d);
/*
 * Przekszta³ca podany napis "s" w liczbê typu double.
 * Podany napis mo¿e byæ liczb¹ o mniejszej precyzji ale musi byæ liczb¹ w zapisie dziesiêtnym
 */
err_t StringToFile(const string &buf,const string &path);
/*
 * Zapisuje napis do pliku.
 * Mo¿e zwróciæ rodzaje b³êdów:
 * ERR_PAR_BAD - w przypadku gdy podano z³¹ scie¿kê dostêpu
 * ERR_FILE_OPEN - w przypadku nie mo¿noœci otwarcia pliku
 * ERR_FILE_WRITE - w przypadku b³êdu podczas zapisu do pliku
 */
string ul2s(size_t i);

//##############################################################################
class CFileConfig
{
protected:
  mss_t mss_cfg;
    // Mapa zawieraj¹ca tekstowe parametry konfiguracyjne
  msi_t msi_cfg;
    // Mapa zawieraj¹ca parametry konfiguracyjne typu int
  string root_name;
    // G³ówna nazwa wyko¿ystywana do nazywania plików programu jego skryptu konfiguracyjnego itp
    // rozró¿nianie odbywa siê przez rozszerzenie.
    // Np: bin_path+"\\"+root_name+".exe"
    //     bin_path+"\\"+root_name+".log"
    //     bin_path+"\\"+root_name+".cfg"
  string bin_path;
    // Scie¿ka do katalogu w którym znajduje siê g³ówny plik programu
public:
  CFileConfig(){/*...*/};
  ~CFileConfig(){/*...*/};

  err_t Init(const string & root_name_);
  /*
   * Podaje do wnêtrza obiektu  czêœæ root plików
   * Wywo³ywana jest metoda ReadCfg(). Je¿eli w pliku konfiguracyjnym zjajduj¹ siê klucze rozpoczynaj¹ce
   * siê od ci¹gu "dir_" to wszystkie te katalogi zostan¹ utworzone je¿eli nie istniej¹. Je¿eli
   * konfiguracja tego wymaga czyszczony jest plik z logami po poprzedniej pracy programu.
   */
  err_t GetConfig(const string &key,int &i_val);
  err_t GetConfig(const string &key,string &s_val);
  /*
   * Pobiera z pliku konfiguracyjnego wartoœæ klucza : "key". Je¿eli nie znajdzie podanego klucza zwraca
   * b³¹d ERR_NOT_FIND.
   */
  int GetOption(const string &key);
  /*
   * Zwraca wartoœæ klucza "key" dla przypadku gdy jego wartoœæ jest typu int. W przypadku wyst¹pienia b³êdu
   * zwraca size_m2.
   */
  err_t SetConfig(const string &key,int &i_val);
  err_t SetConfig(const string &key,string &s_val);
  /*
   * Zapisuje dane do pliku konfiguracyjnego. Klucze mog¹ mieæ wartoœci int lub string ale w pliku
   * w pliku configuracyjnym s¹ to zawsze napisy.
   */
private:
  err_t ReadConfig();
  /*
   * Odczytuje plik konfiguracyjmny i wype³nia mapy mss_cfg i msi_cfg.
   */
  err_t SaveConfig();
  /*
   * Zapisuje do pliku konfiguracyjnego zmienione wartoœci parametrów przechowywanych w mapach ..._cfg
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
 * Dodaje liczbê : "number_" na koñcu napisu : "buf". String przybiera formê 011010011B gdzie iloœæ
 * zer i jedynek koniecznych do poprwanego przedstawienia wartoœæi jest dope³niana zerami wiod¹cymi
 * do pe³nego rozmiaru typu mieszcz¹cego t¹ wartoœæ np wartoœæ 1 do 00000001B a 256 0000000100000000B
 *we:
 * buf : napis do którego ma byæ dodana liczba w zapisie binarnym
 * number_ : liczba dodawana w zapisie binarnym
 * pos_ : pozycja na której wstawiony zostanie number_. Je¿eli pos_>buf.size() to napis  bêdzie
 * dodany.
 *wy:
 * je¿eli <0 to b³¹d
 */
#define HEX_C 0
#define HEX_ASM 1
#define HEX_NULL 2
#define ENDIAN_BIG 4
int AddAsHex(string &buf,int number_,int digit_,int signed_,int typ_, size_t pos_);
/*
 * dodaje liczbê na koñcu napisu zapisuj¹c j¹ w formacie szesnastkowym u¿ywaj¹c do tego iloœæ pozycji
 * okreœlonej zmienn¹ digit_
 *we:
 * number_: liczba do zapisania
 * digit_: iloœæ cyfr przeznaczona na zapis liczby
 * signed_: podan¹ wartoœæ _number traktuj jako ze znakiem nawet gdy _signed==SIGNED
 *          gdy _signed==UNSIGNED a _number <0 zwróæ b³¹d
 * typ_: HEX_C - liczba zostanie zapisana w stylu jêzyka C : 0xa45f
 *       HEX_ASM - liczba zostanie zapisana w stylu assemblera : 0a45fh
 *       HEX_NULL - poprostu : a45f
 * pos_: pozycja na któr¹ zostanie wstawiony string reprezentuj¹cy przetworzon¹ liczbê
 *       je¿eli pos > buf.size() to napis bêdzie dodany
 *wy:
 * je¿eli <0 to jakiœ b³¹d:
 * ERR_SIGNED - zmiena jest ujemna a w wywo³aniu metody zarz¹dano UNSIGNED
 * ERR_RENGE - zmiennej _number nie da siê przedstawiæ na iloœci cyfr okreœlonej przez _digit
 */
void AddAsInt(string &buf,int number_,size_t pos_);
/*
 * wstawia liczbê na pozycji pos_ buforu buf.
 */
err_t cena(string &s);
err_t cena(string &s,double &d);
/*
 * s musi mieæ tak¹ budowê by daæ siê przedstawiæ w postaci ceny XXXXXX,XX. Je¿eli nie to próbuje poprawiæ
 * jej budowê. Je¿eli budowa jest poprawna zwraca w d liczbê odpowiednio zaokr¹glon¹ a w s skoorygowan¹
 * postaæ ceny. Je¿eli nie ERR_PAR_BAD.
 */
string d2s(double d,int round);
/*
 * Prezekszta³ca liczbê typu double w string. Je¿eli round >0 to zaokr¹gla iloœæ miejsc po przecinku
 * do tej iloœci. Gdy (round < 0) wynik nie jest zaokr¹glany.
 */

size_t FiltrDaty(string &data_);
/*
 * Sprawdza czy data zapisana jest w poprawnej formie. Format daty : RRRR-MM-DD
 * Nie poprawnoœci w stylu 1-1-1 poprawiane s¹ na 2001-01-01.
 * je¿eli data jest poprawna zwraca wartoœæ wiêksz¹ ni¿ rozmiar dekstu je¿eli data jest b³êdna
 * zwraca indeks pierwszego niepoprawnego znaku.
 */

void New(string &buf,const string &s_,const string &t_);
/*
 * czyta podnapis z napisu s_ do napotkania któregokolwiek ze znaków tworz¹cego napis t_.
 * Je¿eli nie podano napisu t_ kopiowany jest ca³y napis s_.
 * Funkcja zwraca d³ugoœæ napisu. Je¿eli zwróci wartoœæ 0 nie skopiowano ¿adnych danych.
 * Wartoœci ujemne informuj¹ o b³êdzie.
 */
err_t FileRead(string &buf,const string &path_);
/*
 * Odzczytuje plik tekstowy i zapisuje go w ca³oœci do jednego stringu : buf
 */
err_t FileWrite(string &buf,const string &path_);
/*
 * Zapisuje zawartoœæ stringu buf do pliku file_
 */
string GetBlock(const string &s,size_t &ix_);
/*
 * Pobiera tekst stanowi¹cy spuj¹ ca³oœæ.
 * Je¿eli pierwszym znakiem jest otwarty nawias to funkcja zwraca jego wnêtrze.
 * Je¿eli pierwszym znakiem jest alnum lub '_' to zrwaca string do pierwszego znaku nie bêd¹cego alnum lub '_'
 * je¿eli napotka znaki bia³e opuszcza je i postêpuje zgodnie z przedstawionymi zasadami
 * Je¿eli nie otworzono nawiasu to znaki nie bêd¹ce alnum lub '_' koñcz¹ blok
 * Je¿eli napotka coœ innego nic nie zwraca
 */
err_t GetDouble(string s_, double &out_,int signed_);
/*
 * Je¿eli jest to mo¿liwe funkcja przetworzy wenêtrzny napis i zwróci go w zmiennej out_.
 * Napis musi sk³adaæ siê z jednego wyrazu zbudowanego ze znaków 0..9 i a..f. Funkcja rozpoznaje
 * równie¿ oznaczenia 0x i h dla liczb szesnastkowych
 *we:
 * signed_: informuje czy ma wymuszaæ tworzenie liczb ze znakiem gdy na przyk³ad napis wygl¹da tak: 0xf2
 * czy traktowaæ tak¹ liczbê jak bez znaku
 * signed_==SIGNED - ze znakiem jak sugeruje napis
 * signed_==UNSIGNED - liczba jest bez znaku
 *wy:      jeszcze nie prawda
 * je¿eli <0 to jakiœ b³¹d:
 * ERR_SIGNED - zmiena jest ujemna a w wywo³aniu metody zarz¹dano UMSIGNED
 * ERR_RENGE - zmiennej number_ nie da siê przedstawiæ na iloœci cyfr okreœlonej przez digit_
 */
string GetExpr(const string &buf,size_t &st_);
/*
 * Pobiera z buf ci¹g string bêd¹cy wyra¿eniem z³o¿onym.
 * Je¿eli wya¿enie umieszczone jest w nawiasie zwraca string znajduj¹cy siê wewn¹trz nawiasu
 * bez przednich i tylnych znaków bia³ych. parametr st_ ustawiany jest na pierwsz¹ pozycjê po
 * wyra¿eniu ale te¿ za nawiasem gdy wyra¿enie umieszczone by³o w nawiasie.
 */
err_t GetInt(const string &buf,int &out_,int signed_);
/*
 * Je¿eli jest to mo¿liwe funkcja przetworzy wewnêtrzny napis i zwróci go w zmiennej out_.
 * Napis musi sk³adaæ siê z jednego wyrazu zbudowanego ze znaków 0..9 i a..f. Funkcja rozpoznaje
 * równie¿ oznaczenia 0x i h dla liczb szesnastkowych
 *we:
 * signed_: informuje czy ma wymuszaæ tworzenie liczb ze znakiem gdy na przyk³ad napis wygl¹da tak: 0xf2
 * czy traktowaæ tak¹liczbê jak bez znaku
 * signed_==SIGNED - ze znakiem jak sugeruje napis
 * signed_==UNSIGNED - liczba jest bez znaku
 *wy:      jeszcze nie prawda
 * je¿eli <0 to jakiœ b³¹d:
 * ERR_SIGNED - zmiena jest ujemna a w wywo³aniu metody zarz¹dano UMSIGNED
 * ERR_RENGE - zmiennej number_ nie da siê przedstawiæ na iloœci cyfr okreœlonej przez digit_
 */
err_t GetIntH(const string &buf,int &out_,int signed_);
/*
 * Tak jak funkcja GetInt() lecz buf musi zawieraæ napis przedstawiaj¹cy liczbê szesnastkow¹ ale bez
 * oznaczeñ przedrostka 0x i przyrostka h. Funkcja przeznaczona jest do operowania na liczbach
 * szesnastkowych w obrêbie wewnêtrznych struktur przetwa¿aj¹cych dane.
 */
string GetProgr(const string &buf,size_t &sta_ix_,size_t &sto_ix_);
/*
 * Tak jak GetWord() lecz wyrazem jest ci¹g znaków alpha+digit+_
 */
err_t GetULong(const string & str, unsigned long &l_);

//string GetWord(const string &buf,int start_);
/*
 * Zwraca s³owo zaczynaj¹ce siê pierwszym znakiem alpha na pozycji lub po _start a koñczocê na ostatnim znaku
 * tego ci¹gu znaków alfabetu
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
 * Rozpoczynaj¹c na pozycji _i metoda przegl¹da bufor w poszukiwaniu pisanego znaku.
 *we: i_
 * pozycja od której nale¿y zacz¹æ przeszukiwanie
 *wy: i_
 * -1: dotarto do koñcz napisu i nie znaleziono ¿adnego pisanego znaku
 * >=_i: pozycja na której wystêpuje kolejny znak
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
 * Porównuje nie uwzglêdniaj¹c wielkoœci liter.
 *wy:
 * true gdy równe
 */
int csort(const string &s_lv,const string &s_pv);
/*
 * if return >0 klejnoœæ parametrów zgodna z kolejnoœci¹ napisów
 * if return == 0 napisy równe
 * if return <0 kolejnoœæ parametrów nie zgodna z kolejnoœci¹ napisów
 * Do porównania stosowana jest taplica polchar
 */
bool csu(const string &s_lv,const string &s_pv);
/*
 * Porównuje nie uwzglêdniaj¹c wielkoœci liter. Jednak zak³ada ¿e drugi znak sk³ada siê tylko z du¿ych liter.
 * To poto by nie potrzebnie nie powiêkszaæ znaków dla tekstu podanego bezpoœrednio - nie przez zmienn¹
 *wy:
 * true gdy równe
 */
size_t csdorozny(const string &lv,const string &pv);
/*
 * Porównuje dwa stringi zwracaj¹c indeks pierwszego znaku na którym oba napisy zaczynaj¹ siê ró¿niæ
 */
size_t csudorozny(const string &lv,const string &pv);
/*
 * Porównuje dwa stringi zwracaj¹c indeks pierwszego znaku na którym oba napisy zaczynaj¹ siê ró¿niæ.
 * funkcja podnosi wszystkie znaki przed porównaniem
 */
size_t Find(const string &s_source_,const string &s_find_,size_t start,bool sep_);
/*
 * Szuka napisu s_find_ w napisie s_source_ nie zwracaj¹c uwagi na wielkoœæ liter. Funkcja powsta³a
 * w³aœnie z tego powodu poniewa¿ metoda find klasy string rozru¿nia wielkoœæ znaków.
 * Je¿eli napis nie zostanie znaleniony zwraca wartoœæ size_m a je¿eli zosta³ znaleziony
 * zwraca pozycje pierwszego znalezionego znaku w przeszukiwanym tekœcie.
 * we:
 *  start: pozcja od której rozpocz¹æ szukanie tekstu find
 *  sep_ : je¿eli true to odnaleziony napis musi byæ ograniczony znakami bia³ymi
 *         lub interpunkcyjnymi lub pocz¹tkiem i koñcem napisu
 *         je¿eli false to napis mo¿e byæ czêœci¹ innego wyrazu
 * wy:
 *  return - pozycja pierwszego znaku szukanego tekstu w tekscie przeszukiwanym
 *  if reurn==size_m nie znaleziono
 */
void DelSpaceFlank(string &buf);
void DelSpaceLeft(string &buf);
void DelSpaceRight(string &buf);
void Pack(string &buf);
/*
 *dzia³anie:
 *  Usówa z napisu wszystkie znaki bia³e.
 */
string Param(const string &buf,size_t &ix_);
/*
 * Rozpoczyna przetwarzanie na podanej pozycji i koñczy przecinkiem lub znakiem pierwszym zamkniêtym
 * nawiasem bez pary. Po wyjœciu z funkcji iX_ zawiera pozycjê pierwszego nie przetworzonego znaku.
 * Zwrócony napis pozbawiony jest bia³ych znaków bocznych.
 */
string Read(const string &s_,size_t &ix_,string s_lim);
/*
 * Czyta podnapis z napisu s_ i zwraca go na wyjscie. Bia³e znaki wiod¹ce nie s¹ dodawane do wyniku.
 * Zmienna ix_ wskazuje na pierwszy znak za odczytanym napisem.
 * ix_ - Index pierwszego znaku branego do przetwarzania.
 *       Po wykonaniu funkcji ix_ zawiera index pierwszego nie przetworzonego znaku
 *       lub string::npos gdy dosz³o do koñca napisu
 * s_lim - Napis zawieraj¹cy znaki które wyznaczaj¹ granicê przeszukiwania
 */
string Shift(string &buf,size_t sw,string s_);
/*
 * wysówa z napisu ci¹g znaków (podnapis) rozpoczynaj¹cy siê na pozycji 0 a ograniczonym dowolnym ze znaków
 * wchodz¹cym w sk³ad napisu s_. Znaki tworz¹ce napis t_ s¹ usówane z tego napisu pocz¹wszy od
 * pierwszego znaku po wysuniêtym napisie a¿ do pierwszego znaku nie nale¿¹cego do napisu t_.
 * WITH_LIM
 * NO_WITH_LIM
 */
string ShiftToken(string &buf);
/*
 * Wysówa z napisu podan¹ iloœæ znaków. Je¿eli nie ma podanej iloœci znaków w napisie zwraca  "\0"
 */
string ShiftParam(string &s_);
/*
 * wysówa z podanego napisu wszystko od jego pocz¹tku do napotkania przecinka.
 * Napis zwrócony przez funkcjê oczyszczony jest z bocznych spacji. Z napisu wejœciowego usówany
 * jest przecinek oraz przednie spacje.
 */
string Token(const string &str,size_t &st,size_t &sp);
/*
 * Wywo³ywanie funkcji:
 * we:
 *  str: napis rozk³adany na tokeny
 *  st: zmienna przechowuj¹ca pozycjê na której rozpoczyna siê analizê stringu str
 *      Przy powrocie zawiera now¹ wartoœæ jeœli start przesun¹³ siê ze wzglêdu na znaki bia³e
 *  sp: po powrocie wskazuje na nastên¹ pozycjê za ostatnim znakiem rozpoznanego tokenu.
 * return:
 *  je¿eli rozpoznano token zwraca go lub ""
 *
 * Opis:
 * Token:
 * - pojedynczy symbol
 * - to co znajduje siê pomiêdzy tym symbolem lub spacj± a kolejnym symbolem lub spacj±
 * - dwa znaki interpunkcyjne '.' i '_' (kropka i podkreœlenie) zalicza siê do znaków alphanumerycznych
 *   (liczby i litery) gdy:
 *   '_': styka siê choæ jednym bokiem z liczb¹ lub liter¹.
 *   '.': ma po prawej stronie liczbê
 * - liczba naukowa
 * Podzia³ na tokeny:
 *
 */
void ToUpper(string &s_);
/*
 * zamienia na du¿e wszystkie znaki napisu s_
 */
string Transfer(string &s_,size_t st_=0,size_t sp_=string::npos);
/*
 * Zabiera podnapis z napisu s_ i przenosi go na wyjœcie.
 * st_ - index pierwszego zabieranego znaku
 * sp_ - index ostatniego zabieranego znaku
 */
string Transfer(string &s_,size_t st_=0,char c_=' ');
/*
 * Zabiera podnapis z napisu s_ i przenosi go na wyjœcie.
 * st_ - index pierwszego zabieranego znaku
 * c_  - znak na którym ma siê zakoñczyæ pobierany tekst
 */
string Transfer(string &s_,char c_,size_t sp_=string::npos);
/*
 * Zabiera podnapis z napisu s_ i przenosi go na wyjœcie.
 * c_ - szukany od pocz¹tku napisu znak od którego ma siê rozpocz¹æ pobieranie napisu
 * sp_ - pozycja ostaniego znaku pobieranego tekstu
 */
///////////////////////////////////////////////////////////////////////////////
//      INLINE
///////////////////////////////////////////////////////////////////////////////
bool Nul(const string &buf);
/*
 * Zwraca true gdy napis jest "" lub zawiera tylko znaki bia³e.
 */

//##############################################################################
class TExpr
//##############################################################################
{
protected:
  string infix;
  size_t ix;
    // wskazuje na pozycje znaku nastêpnego do przetworzenia
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
   * Przed obliczeniem wartoœci wyra¿enia nale¿y skorygowaæ oprawnoœæ zapisu. Poniewa¿ u¿ytkownik
   * mo¿e u¿yæ zapisu np: 5+ -(4+2)... lub np ...+7)(5*34)... jako poprawnych matematycznie lecz nie
   * przystosowanych do przetwarzania odwrotn¹ notacj¹ polsk¹. Aby mo¿na by³o dalej przetwarzaæ ten
   * string nale¿y konstrukcje pierwszego typu zast¹piæ w miejsce "-" wstawiæ "(0-1)*" czyli
   * 5+(0-1)*(4+2)... . W przypadku drugim zastêpujemy "...) (..." napisem : "...)*(..." i mamy
   * ...+7)*(5*34)...".
   */
  err_t expr(double &d_val_);
  bool InLong(double d_);
  /*
   * Sprawdza czy wartoœæ double mo¿na przekszta³ciæ na long. Jest to doœæ trudne do spe³nienia
   * ale podczas przetwarzania wyra¿eñ zawieraj¹cych operatory arytmetyczne konieczne. Tworz¹c
   * wyra¿enie zawieraj¹cych operaory logiczne nale¿y pamiêtaæ by nie dochodzi³o do tworzenia
   * wartoœci ujemnych.
   */
  bool IsOp(const string &op);
  bool IsOp();
  /*
   * Zwraca true gdy ci¹g lub pojecynczy znak jest operatorem np + lub and
   */
  err_t OP(double &d_lv,const string & op_, double d_pv);
  /*
   * Metoda wykonyje zapisan¹ operacjê op_ na ziennych dlv i dpv.
   * Metoda ma kontrolowaæ poprawnoœæ wykonania operacji ale na razie tego nie robi
   */
  bool OP12(const string &op1,const string &op2);
  /*
   * Metoda dokonuje testu pierwszeñstwa wykonania dwóch operacji. Je¿eli ich kolejnoœæ
   * odpowiada przyjêtym regu³om w matematyce zwraca true je¿eli nie zwraca false.
   */
  size_t PO(const string &op);
  /*
   * Zwraca wartoœæ liczbow¹ priorytetu operatora
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
    // treœæ pliku konfiguracyjnego
  string path;
    // œcie¿ka dostêpu wraz z nazw¹ pliku
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
