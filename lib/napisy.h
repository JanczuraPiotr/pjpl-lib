
#include <algorithm>
#ifndef NAPISY_H
#define NAPISY_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <set>
#include <string>
#include <map>
#include <string>
#include <cstring>
#include <fstream>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <vector>
#include <stack>


namespace pjpl {
namespace wstr {

const std::vector<std::string> limToken = {
    "=" ,
    "=[",
    "![",
    "!=",
    ">=",
    "<=",
    "&&",
    "and",
    "||",
    "or"
};
const std::vector<std::string> operators = {
    "=[", // dla "=[1,2,3]"
    "![", // dla "![1,2,3]"

    "&&",
    "and",
    "||",
    "or",
    "!=",
    ">=",
    "<=",

    "<",
    ">",
    "!",
    "+",
    "-",
    "*",
    "/",
    "=",
    "^", // potęga

    "___unary__minus___",
    "___unary__plus___"
};

std::string toString(const std::string &source);
std::string fromString(const std::string &str);
/**
 * Wskazuje na pierwszą pozycję wewnątrz subject za znalezionym tokenem.
 * @param subject
 * @param token
 * @param start
 * @return pozycja w tekście za szukanym tokenem lub std::string::npos
 */
std::string::size_type after(const std::string &subject, const std::string &token, std::string::size_type start);
/**
 * Zwraca token z listy tokens jeżeli zaczyna się bezpośrednio na pozycji startPos
 * @param exp
 * @param startPos
 * @param operators
 * @return
 */
std::string adjustToken(const std::string &exp, size_t startPos, const std::vector<std::string> &tokens);
/**
 * Zwraca token z listy tokens jeżeli zaczyna się bezpośrednio na pozycji startPos
 * @param exp
 * @param startPos
 * @param operators
 * @return
 */
std::string adjustNearestToken(const std::string &exp, size_t &start, size_t &stop, const std::vector<std::string> &tokens);

std::string between(
        const std::string &subject
        , const std::string &leftLim
        , const std::string &rightLim
        , std::size_t &start
        , std::size_t &cursor
        , bool trim = false );
/*
 * Zwraca true gdy napis jest "" lub zawiera tylko znaki białe.
 */
bool empty(const std::string &buf);

/*
 * Wywoływanie funkcji:
 * we:
 *  str: napis rozkładany na tokeny
 *  start: zmienna przechowująca pozycję na której rozpoczyna się analizę std::stringu wstr
 *      Przy powrocie zawiera nową wartość jeśli start przesunął się ze względu na znaki białe
 *  stop: po powrocie wskazuje na następną pozycję za ostatnim znakiem rozpoznanego tokenu.
 *  between zwróci napis ograniczony znakami between np "napis" lub od pozycji start do znaku between
 *          gdy between == '\0' wykonana zostanie metoda Token(const std::string &wstr,size_t &start,size_t &stop)
 * return:
 *  jeżeli rozpoznano token zwraca token a jeżeli nie rozpoznano zwraca ""
 *
 * Opis:
 * Token:
 * - pojedynczy symbol
 * - to co znajduje się pomiędzy tym symbolem lub spacją a kolejnym symbolem lub spacją
 * - dwa znaki interpunkcyjne '.' i '_' (kropka i podkreślenie) zalicza się do znaków alfanumerycznych
 *   (liczby i litery) gdy:
 *   '_': styka się choć jednym bokiem z liczbą lub literą.
 *   '.': ma po prawej stronie liczbę
 * - liczba naukowa
 */
std::string token(const std::string &str,size_t &start,size_t &stop, wchar_t between);
/*
 * Wywoływanie funkcji:
 * we:
 *  str: napis rozkładany na tokeny
 *  st: zmienna przechowująca pozycję na której rozpoczyna się analizę std::stringu wstr
 *      Przy powrocie zawiera nową wartość jeśli start przesunął się ze względu na znaki białe
 *  sp: po powrocie wskazuje na następną pozycję za ostatnim znakiem rozpoznanego tokenu.
 * return:
 *  jeżeli rozpoznano token zwraca token a jeżeli nie rozpoznano zwraca ""
 *
 * Opis:
 * Token:
 * - pojedynczy symbol
 * - to co znajduje się pomiędzy tym symbolem lub spacją a kolejnym symbolem lub spacją
 * - dwa znaki interpunkcyjne '.' i '_' (kropka i podkreślenie) zalicza się do znaków alfanumerycznych
 *   (liczby i litery) gdy:
 *   '_': styka się choć jednym bokiem z liczbą lub literą.
 *   '.': ma po prawej stronie liczbę
 * - liczba naukowa
 */
std::string token(const std::string &str,size_t &start,size_t &stop);

std::string trim(const std::string &buf);
std::string trimLeft(const std::string &buf);
std::string trimRight(const std::string &buf);
/*
 * Czyta napis z napisu source i zwraca go na wyjście. Białe znaki wiodące ani kończące nie są dodawane do wyniku.
 * Jeżeli napis lim nie zostanie znaleziony zwracana jest pod łańcuch od start do końca subject.
 * @param source - napis źródłowy
 * @param start  - Index znaku od którego rozpoczyna się wyszukiwanie.
 * @param stop   - pozycja znaku na której zakończono wyszukiwanie
 *                 top wskazuje na pozycję za tą na której kończy się napis graniczny lim.
 *                 Gdy stop = source.length() to osiągnięto koniec napisu source.
 * @param lim    - Napis którego pierwszy znak jest pierwszym znakiem za zwracanym napisem.
 * @return
 */
std::string read(const std::string &source, size_t &start, size_t &stop, const std::string &lim);
/**
 * @param string tekst do podziału i umieszczenia w tablicy
 * @param rozdzielnik znak/string rozdzielający nie przetestowane co się dzieje gdy string
 * @return
 */
std::vector<std::string> split(const std::string& string, const std::string& rozdzielnik, bool trim = false);
}

namespace str {

/**
 * Wskazuje na pierwszą pozycję wewnątrz subject za znalezionym tokenem.
 * @param subject
 * @param token
 * @param start
 * @return pozycja w tekście za szukanym tokenem lub std::string::npos
 */
std::string::size_type after(const std::string &subject, const std::string &token, std::string::size_type start);

std::string between(
        const std::string &subject
        , const std::string &leftLim
        , const std::string &rightLim
        , std::size_t &start
        , std::size_t &cursor
        , bool trim = false );

/*
 * Czyta napis z napisu source i zwraca go na wyjście. Białe znaki wiodące ani kończące nie są dodawane do wyniku.
 * Jeżeli napis lim nie zostanie znaleziony zwracana jest podłańcuch od start do końca subject.
 * @param source - napis źródłowy
 * @param start  - Index znaku od którego rozpoczyna się wyszukiwanie.
 * @param stop   - pozycja znaku na której zakończono wyszukiwanie
 *                 top wskazuje na pozycję za tą na której kończy się napis graniczny lim.
 *                 Gdy stop = source.length() to osiągnięto koniec napisu source.
 * @param lim    - Napis którego pierwszy znak jest pierwszym znakiem za zwracanym napisem.
 * @return
 */
std::string read(const std::string &source, size_t &start, size_t &stop, const std::string &lim);

std::string trim(const std::string &buf);
std::string trimLeft(const std::string &buf);
std::string trimRight(const std::string &buf);
}

//    const std::string limStr = "+-*:/;,.(){}[]\t\n\r";
//    const std::string interpunct=":;<=>?!\"#$%&'()*+,-./[\\]^_`{|}~"; // std::ispunct(c) without '@'
const std::vector<std::string>  limCharVec = {
"~",
//"`",
"!",
//"@",
//"#",
//"$",
//"%",
"^",
"&",
"*",
"(",
")",
"-",
"+",
"=",
"{",
"}",
"[",
"]",
"|",
"\\",
":",
";",
"\"",
"'",
"<",
">",
",",
".",
"?",
"/",

//        " "
//        "\n"
//        "\t"
//        "\r"
//        "\f"

};

//    const std::vector<std::string> limToken = {
//        "=" ,
//        "=[",
//        "![",
//        "!=",
//        ">=",
//        "<=",
//        "&&",
//        "and",
//        "||",
//        "or"
//    };

//    const std::vector<std::string> operators = {
//        "=[", // dla "=[1,2,3]"
//        "![", // dla "![1,2,3]"
//
//        "&&",
//        "and",
//        "||",
//        "or",
//        "!=",
//        ">=",
//        "<=",
//
//        "<",
//        ">",
//        "!",
//        "+",
//        "-",
//        "*",
//        "/",
//        "=",
//        "^", // potęga
//
//        "___unary__minus___",
//        "___unary__plus___"
//    };

/**
 * Data z teraz: Y-m-d H-M-S
 * @return
 */
std::string now();

std::string trim(std::string &str);

/**
 * Zwraca token z listy tokens jeżeli zaczyna się bezpośrednio na pozycji startPos
 * @param exp
 * @param startPos
 * @param operators
 * @return
 */
std::string adjustToken(const std::string &exp, const size_t startPos, const std::vector<std::string> &tokens);
std::string adjustNearestToken(const std::string &exp, size_t &start, size_t &stop, const std::vector<std::string> &tokens);

bool ispunct(char c);
std::string join(const std::vector<int> &v, char connector);
std::string join(const std::vector<std::string> &v, char connector);


/*
 * Czyta napis z napisu wstr i zwraca go na wyjście. Białe znaki wiodące ani kończące nie są dodawane do wyniku.
 * @param wstr - napis źródłowy
 * @param start  - Index znaku od którego rozpoczyna się wyszukiwanie.
 * @param stop - pozycja znaku na której zakończono wyszukiwanie
 *      - ponieważ znaleziono znak graniczny z listy lim lub koniec wstr
 *      - stop wskazuje na pozycję za tą na której znajduje się znak z listy lim. Gdy stop = std::string::npos to jednocześnie osiągnięto koniec wstr
 * @param lim - Napis zawierający napisy , które wyznaczają granicę przeszukiwania. Granicę wyznacza pierwszy dopasowany napis.
 * @return token pomiędzy start a znak z listy lim oczyszczony z białych znaków brzegowych
 */
std::string Read(const std::string &str, size_t &start, size_t &stop, const std::vector<std::string> &lim = pjpl::limCharVec);
/*
 * Wywoływanie funkcji:
 * we:
 *  wstr: napis rozkładany na tokeny
 *  st: zmienna przechowująca pozycję na której rozpoczyna się analizę std::string wstr
 *      Przy powrocie zawiera nową wartość jeśli start przesunął się ze względu na znaki białe
 *  sp: po powrocie wskazuje na następną pozycję za ostatnim znakiem rozpoznanego tokenu.
 * return:
 *  jeżeli rozpoznano token zwraca token a jeżeli nie rozpoznano zwraca ""
 *
 * Opis:
 * Token:
 * - pojedynczy symbol
 * - to co znajduje się pomiędzy tym symbolem lub spacją a kolejnym symbolem lub spacją
 * - dwa znaki interpunkcyjne '.' i '_' (kropka i podkreślenie) zalicza się do znaków alfanumerycznych
 *   (liczby i litery) gdy:
 *   '_': styka się choć jednym bokiem z liczbą lub literą.
 *   '.': ma po prawej stronie liczbę
 * - liczba naukowa
 */
std::string Token(const std::string &str,size_t &start,size_t &stop);
/*
 * Wywoływanie funkcji:
 * we:
 *  wstr: napis rozkładany na tokeny
 *  start: zmienna przechowująca pozycję na której rozpoczyna się analizę std::string wstr
 *      Przy powrocie zawiera nową wartość jeśli start przesunął się ze względu na znaki białe
 *  stop: po powrocie wskazuje na następną pozycję za ostatnim znakiem rozpoznanego tokenu.
 *  between zwróci napis ograniczony znakami between np "napis" lub od pozycji start do znaku between
 *          gdy between == '\0' wykonana zostanie metoda Token(const std::string &wstr,size_t &start,size_t &stop)
 * return:
 *  jeżeli rozpoznano token zwraca token a jeżeli nie rozpoznano zwraca ""
 *
 * Opis:
 * Token:
 * - pojedynczy symbol
 * - to co znajduje się pomiędzy tym symbolem lub spacją a kolejnym symbolem lub spacją
 * - dwa znaki interpunkcyjne '.' i '_' (kropka i podkreślenie) zalicza się do znaków alfanumerycznych
 *   (liczby i litery) gdy:
 *   '_': styka się choć jednym bokiem z liczbą lub literą.
 *   '.': ma po prawej stronie liczbę
 * - liczba naukowa
 */
std::string Token(const std::string &str,size_t &start,size_t &stop, char between);

/**
 * @param string tekst do podziału i umieszczenia w tablicy
 * @param rozdzielnik znak/string rozdzielający nie przetestowane co się dzieje gdy string
 * @return
 */
std::vector<std::string> split( const std::string& string, const std::string& rozdzielnik, bool trim = false);
std::vector<std::string> split(const std::string& s, char delimiter);

//-----------------------------------------------------------------------------

namespace old {
    std::string DelSpaceFlank(std::string &buf);
    std::string DelSpaceLeft(std::string &buf);
    std::string DelSpaceRight(std::string &buf);
}
}


#endif

