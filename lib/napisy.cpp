#include "napisy.hpp"

namespace pjpl {

namespace wstr {

std::string toString(const std::string &source) {
    std::string s(source.begin(), source.end());
    return s;
}

std::string fromString(const std::string &str) {
    std::string temp(str.length(),L' ');
    std::copy(str.begin(), str.end(), temp.begin());
    return temp;
}

std::string::size_type after(const std::string &subject, const std::string &token, std::string::size_type start) {
    if (start < subject.length()) {
        std::string::size_type pos = subject.find(token, start);
        if (pos < subject.length()) {
            return pos + token.length();
        } else {
            return std::string::npos;
        }
    }
    return std::string::npos;
}

std::string adjustToken(const std::string &str, size_t startPos, const std::vector<std::string> &tokens) {
    for (auto &it : tokens ) {
        if (str.find(it, startPos) == startPos) {
            return it;
        }
    }

    return "";
}

std::string adjustNearestToken(const  std::string &str, size_t &start, size_t &stop, const std::vector<std::string> &tokens) {
    stop = std::string::npos;
    if (str.size() == 0) {
        return "";
    }

    std::string find = "";
    size_t findNow;
    size_t ix = start;
    size_t sz = str.size();

    while (ix < sz && isspace(str[ix])) {
        ++ix;
    }
    start = ix;

    for ( auto &it : tokens) {
        findNow = str.find(it, start);
        if (findNow < stop) {
            stop = findNow;
            find = it;
        };
    };

    return find;
}

std::string between(
        const std::string &subject
        , const std::string &leftLim
        , const std::string &rightLim
        , std::size_t &start
        , std::size_t &cursor
        , bool trim)
{
    if ( subject.length() == 0 || start >= subject.length()) {
        return "";
    }

    std::size_t _start = subject.find(leftLim, start);

    if (_start == std::string::npos) {
        return "";
    }

    _start += leftLim.length();
    std::size_t _stop = subject.find(rightLim, _start);
    std::string out;
    if (_stop == std::string::npos) {
        out = subject.substr(_start);
    } else {
        out = subject.substr(_start, _stop - _start);
        cursor = _stop + rightLim.length();
    }
    start = _start;
    if (trim) {
        return pjpl::wstr::trim(out);
    } else {
        return out;
    }
}

bool empty(const std::string &buf)
{
    if (buf.size() == 0) {
        return true;
    } else {
        size_t si = 0;
        do {
            if (std::isgraph(buf[si])) {
                return false;
            }
        } while (++si < buf.size());
        return true;
    }
}

std::string token(const std::string &str, size_t &start, size_t &stop, wchar_t between) {
    size_t sz = str.size();
    size_t stop_;

    while (start < sz && isspace(str[start])) {
        ++start;
    }
    if (between != '\0') {
        if (str[start] != between) {
            return "";
        }
        while (start < sz && str[start] != between) {
            ++start;
        }
        if (start >= sz) {
            return "";
        }
        stop_ = ++start;
        while (stop_ < sz && str[stop_] != between) {
            ++stop_;
        }
        if (stop_ >= sz) {
            return "";
        }
        std::string ret = str.substr(start , stop_ - start);
        stop = ++stop_;
        return pjpl::wstr::trim(ret);
    } else {
        if (start >= sz) {
            return "";
        }
        return pjpl::wstr::token(str, start, stop);
    }
}

std::string token(const std::string &s, size_t &start, size_t &stop)
{
    if (start >= s.size()) {
        return "";
    }

    std::string operat = pjpl::wstr::adjustToken(s, start, operators);
    if (operat.length() > 0) {
        stop = start + operat.length();
        return operat;
    }

    size_t ix;
    size_t sz = s.size();

    while (start < sz && std::isspace(s[start])) {
        start++;
    }
    if (start >= sz) {
        return "";
    }
    ix = start;
    if (::ispunct(s[ix]) && s[ix] != '_' && s[ix] != '.') {
        /*
         * Wszystkie symbole prócz wyr?ionych zawsze samodzielnie tworzą token np: ! @ # $ % $ & * ( )
         */
        stop = start + 1;
        return s.substr(start, 1);
    }
    if (std::isalpha(s[ix]) || s[ix] == '_') {
        while ( (std::isalnum(s[ix]) || s[ix] == '_' ) &&  ( ix < sz) )ix++;
        stop = ix;
        return s.substr(start, stop - start);
    }
    // nie odwiedzono bloku po wyżej czyli na pierwszym miejscu jest liczba lub '.'
    if (isdigit(s[ix])) {
        while (ix < sz && isdigit(s[ix]))ix++;
        if (ix >= sz) {
            stop = ix;
            return s.substr(start, stop - start);
        }
        if ((s[ix] == 'e' || s[ix] == 'E')&&(s[ix + 1] == '+' || s[ix + 1] == '-') && isdigit(s[ix + 2])) {//wyklucza 123e+123
        } else {
            if (std::isalpha(s[ix]) || s[ix] == '_') {
                while ( (ix < sz) && ( std::isalnum(s[ix]) || s[ix] == '_' ) )ix++;
                if (ix >= stop || isspace(s[ix]) || ::ispunct(s[ix])) {
                    stop = ix;
                    return s.substr(start, stop - start);
                }
            }
        }
        if (isspace(s[ix])) {
            stop = ix;
            return s.substr(start, stop - start);
        }
        if (::ispunct(s[ix]) && s[ix] != '.') {
            stop = ix;
            return s.substr(start, stop - start);
        }
    }
    stop = ix;
    // Jeżeli przeskoczono po ciągu liczb to te wartości mają różną wartość
    if (s[ix] == '.') {
        /*
         * Kropka może wystąpić po ciągu liczb lub jako pierwszy znak w tokenie (ix==st).
         * Jeżeli po '.' nie ma liczby||e||E to koniec na pozycji sp
         */
        ix++;
        while (ix < sz && isdigit(s[ix]))ix++;
        if (stop + 1 == ix) {
            /*
             * Potraktowanie znaków jako liczb nie posunęło nas do przodu a po kropce tylko one mogły kontynuować
             * token który zaczął się na pozycji st.
             * Kropka jest tokenem gdy s[st]=='.' w przeciwnym wypadku kropka ogranicza token.
             */
            if (stop == start)
                stop = ix;
            return s.substr(start, stop - start);
        }
    }
    if (stop != ix) {
        /*
         * Była kropka a w bloku obsługi kropki odnaleziono liczby.
         * Gdy po liczbach spacja to np: 123.456
         * Gdy po liczbach interpunct ale nie kropka i nie podkreślenie to token kończy się przed sp
         */
        if (isspace(s[ix])) {//ta spacja może pojawić się po 123.
            stop = ix;
            return s.substr(start, stop - start);
        }
        if (s[ix] == '.' || s[ix] == '_') {
            return s.substr(start, stop - start);
        }
        if (s[ix] != 'e' && s[ix] != 'E') {
            stop = ix;
            return s.substr(start, stop - start);
        }
    }
    if ((s[ix] == 'e' || s[ix] == 'E')&&(s[ix + 1] == '+' || s[ix + 1] == '-') && isdigit(s[ix + 2])) {
        ix += 2;
        if (!isdigit(s[ix])) {
            if (stop == start)
                stop = start + 1;
            return s.substr(start, stop - start);
        }
        while (ix < sz && isdigit(s[ix]))ix++;
        stop = ix;
        return s.substr(start, stop - start);
    } else {
        if (stop == start)
            stop = start + 1;
        return s.substr(start, stop - start);
    }

}

std::string trim(const std::string &str)
{
    return trimRight(trimLeft(str));
}

std::string trimLeft(const std::string &buf)
{
    if (buf.size() == 0)
        return "";
    size_t i = 0;
    size_t sz = buf.size();
    for (;i < sz && isspace(buf[i]); i++) { /*...*/ };
    return buf.substr(i);
}

std::string trimRight(const std::string &buf)
{
    if (buf.size() == 0)
        return "";
    size_t i = buf.size() - 1;

    for (; std::isspace(buf[i]); i--) { /*...*/ };
    return buf.substr(0, i + 1);
}

std::string read(const std::string &source, size_t &start, size_t &stop, const std::string &lim)
{
    if (source.size() == 0) {
        return "";
    }
    std::string::size_type source_length = source.length();
    if(start >= source_length) {
        stop = source_length;
        return "";
    }

    std::string::size_type end = source.find(lim, start);
    std::string out;
    if (end != std::string::npos) {
        out = source.substr(start , end - start);
        stop = end + lim.length();
    } else {
        out = source.substr(start);
        stop =  source_length;
    }

    return pjpl::wstr::trim(out);
}

std::vector<std::string> split( const std::string& str, const std::string& rozdzielacz, bool trim) {
    std::vector<std::string> temp;
    if ( rozdzielacz.empty() ) {
        temp.push_back( str );
        return temp;
    }
    typedef std::string::const_iterator iter;
    const iter::difference_type f_size( std::distance( rozdzielacz.begin(), rozdzielacz.end() ) );
    iter i( str.begin() );
    std::string token;
    for ( iter pos; ( pos = std::search( i , str.end(), rozdzielacz.begin(), rozdzielacz.end() ) ) != str.end(); ) {
        token = std::string( i, pos );
        if (rozdzielacz.find(token) == std::string::npos) {
            if (trim){
                token = pjpl::wstr::trim(token);
            }
            temp.push_back( token );
        }
        std::advance( pos, f_size );
        i = pos;
    }
    token = std::string( i, str.end() );
    if (rozdzielacz.find(token) == std::string::npos) {
        temp.push_back( token );
    }
    return temp;
}


}

// namespace pjpl::wstr
//------------------------------------------------------------------------------
// namespace pjpl::str

namespace str {

std::string::size_type after(const std::string &subject, const std::string &token, std::string::size_type start) {
    if (start < subject.length()) {
        std::string::size_type pos = subject.find(token, start);
        if (pos < subject.length()) {
            return pos + token.length();
        } else {
            return std::string::npos;
        }
    }
    return std::string::npos;
}

std::string between(
        const std::string &subject
        , const std::string &leftLim
        , const std::string &rightLim
        , std::size_t &start
        , std::size_t &cursor
        , bool trim)
{
    if ( subject.length() == 0 || start >= subject.length()) {
        return "";
    }

    std::size_t _start = subject.find(leftLim, start);

    if (_start == std::string::npos) {
        return "";
    }

    _start += leftLim.length();
    std::size_t _stop = subject.find(rightLim, _start);
    std::string out;
    if (_stop == std::string::npos) {
        out = subject.substr(_start);
    } else {
        out = subject.substr(_start, _stop - _start);
        cursor = _stop + rightLim.length();
    }
    start = _start;
    if (trim) {
        return pjpl::str::trim(out);
    } else {
        return out;
    }
}

std::string read(const std::string &source, size_t &start, size_t &stop, const std::string &lim)
{
    if (source.size() == 0) {
        return "";
    }
    std::string::size_type source_length = source.length();
    if(start >= source_length) {
        stop = source_length;
        return "";
    }

    std::string::size_type end = source.find(lim, start);
    std::string out;
    if (end != std::string::npos) {
        out = source.substr(start , end - start);
        stop = end + lim.length();
    } else {
        out = source.substr(start);
        stop =  source_length;
    }

    return pjpl::str::trim(out);
}

std::string trim(const std::string &str)
{
    return trimRight(trimLeft(str));
}

std::string trimLeft(const std::string &buf)
{
    if (buf.size() == 0)
        return "";
    size_t i = 0;
    size_t sz = buf.size();
    for (;i < sz && isspace(buf[i]); i++) { /*...*/ };
    return buf.substr(i);
}

std::string trimRight(const std::string &buf)
    {
        if (buf.size() == 0)
            return "";
        size_t i = buf.size() - 1;

        for (; std::isspace(buf[i]); i--) { /*...*/ };
        return buf.substr(0, i + 1);
    }

}


//------------------------------------------------------------------------------
// namespace pjpl

bool ispunct(char c) {
    return ::ispunct(c);
}

std::string join(const std::vector<int> &v, char connector) {
    std::string s;
    for (auto it = v.begin(); it < v.end(); ++it) {
        s += std::to_string(*it);
        if ( (it + 1) != v.end()) {
            s += connector;
        }
    }
    return s;
}

std::string join(const std::vector<std::string> &v, char connector) {
    std::string s;
    for (auto it = v.begin(); it < v.end(); ++it) {
        s += *it;
        if ( (it + 1) != v.end()) {
            s += connector;
        }
    }
    return s;
}

std::vector<std::string> split( const std::string& str, const std::string& rozdzielacz, bool trim) {
    std::vector<std::string> temp;
    if ( rozdzielacz.empty() ) {
        temp.push_back( str );
        return temp;
    }
    typedef std::string::const_iterator iter;
    const iter::difference_type f_size( std::distance( rozdzielacz.begin(), rozdzielacz.end() ) );
    iter i( str.begin() );
    std::string token;
    for ( iter pos; ( pos = std::search( i , str.end(), rozdzielacz.begin(), rozdzielacz.end() ) ) != str.end(); ) {
        token = std::string( i, pos );
        if (rozdzielacz.find(token) == std::string::npos) {
            if (trim){
                old::DelSpaceFlank(token);
            }
            temp.push_back( token );
        }
        std::advance( pos, f_size );
        i = pos;
    }
    token = std::string( i, str.end() );
    if (rozdzielacz.find(token) == std::string::npos) {
        temp.push_back( token );
    }
    return temp;
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::string old::DelSpaceFlank(std::string &str)
{
    DelSpaceLeft(str);
    DelSpaceRight(str);
    return str;
}

std::string old::DelSpaceLeft(std::string &buf)
{
    if (buf.size() == 0)
        return "";
    size_t i = 0;
    size_t sz = buf.size();
    for (; isspace(buf[i]) && i < sz; i++) { /*...*/ };
    buf.erase(0, i);
    return buf;
}

std::string old::DelSpaceRight(std::string &buf)
{
    if (buf.size() == 0)
        return "";
    size_t i = buf.size() - 1;

    for (; isspace(buf[i]); i--) { /*...*/ };
    buf.erase(i + 1);
    return buf;
}

}
