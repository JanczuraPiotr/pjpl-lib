//#include <limits>
#include <string>
#include <fstream>
#include <cstdlib>
#include <dir.h>
//#include <cerrno>
#include <math>
using namespace  std;

#include "napisy.h"

//==============================================================================
void Add(string &str_,const string &s_,size_t start_,char c_)
{
  if(start_<=str_.size()){
  /*
   * dodawany napis wstawiany jest w obrÍbie istniejπcego
   */
    if(start_<str_.size()){
      str_.insert(start_,s_);
    }else{
     str_+=s_;
    }
  }else{
  /*
   * dodawany napis ma byÊ dopisany "poza" buf brakujπcπ przestszeÒ tworzymy znakami c_.
   */
    if(start_==string::npos)
      start_=str_.size();
    string stmp;
    stmp.resize(start_-str_.size(),c_);
    str_+=stmp+s_;
  }
};
//==============================================================================
size_t d2s(string &str_,double d_,size_t round_,size_t poz_,char c_)
{
  int dec,sig;
  string s;
  s=ecvt(d_,1000,&dec,&sig);  // nie zaokrπglam aby znaÊ pozycje kropki
  round_+=dec;
  s=ecvt(d_,round_,&dec,&sig);
  if(dec==0){
    s.insert(0,".");
  }else if(dec<0){
    dec*= -1;
    s.insert(0,"0",dec);
    s.insert(0,".");
  }else if((size_t)dec<s.size()){
    s.insert(dec,".");
  }
  if(sig){
    s.insert(0,"-");
  };
  if(poz_>0 && s.size()<poz_){
    str_.append(poz_-s.size(),c_);
  }
  str_+=s;
  return s.size();
}
//==============================================================================
size_t i2s(string &str_,int liczba_,size_t poz_,char c_)
{
  char liczba[20];
  size_t i=0;

  itoa(liczba_,liczba,10);
  while(liczba[i]!='\0')++i;
  if(poz_<1){
    str_+=liczba;
    return i;
  }

  if(i<poz_){
    str_.append(poz_-i,c_);
  }
  str_+=liczba;
  return i;
};
//==============================================================================
err_t FileToString(string &buf,const string &path)
{//04-03-05
  ifstream file(path.c_str());
  if(!file)
    return ERR_FILE_OPEN;
  string str;
  char c;
  while(file){
    file.get(c);
    if(file.bad()){
      file.close();
      return ERR_FILE_READ;
    }
    if(file.eof()){
      file.close();
      return OK;
    }
    buf+=c;
  }
  file.close();
  return OK;
};
//==============================================================================
size_t Find(const string &source_,const string &find_,size_t start_,bool sep_)
{//03-08-05
  if(start_>=source_.size()){
    return size_m;
  }

//  size_t ix;
//  size_t sz;
  size_t st;
  string source=source_.substr(start_);
  string find=find_;

  char *c;

  for(c=&(source[0]);*c!='\0';c++){
    *c=(char)toupper(*c);
  }
  for(c=&(find[0]);*c!='\0';c++){
    *c=(char)toupper(*c);
  }
  st=source.find(find);
  if(st==size_m)
    return size_m;
  if(sep_){
    if(st!=0){
    /*
     * jeøeli find zaczyna siÍ na poczπtku source to jest z tej strony odseparowany
     */
      if(
          !isspace(source[st-1])
          &&
          !(
            ispunct(source[st-1])
            &&
            source[st-1]!='_'
          )
        )
        return size_m;
    }

    if(st+find.size()==source.size()){
    /*
     * Jeøeli find koÒczy siÍ na koÒcu source to jest z tej strony odseparowany
     */
      return st;
    }

    if(
        !isspace(source[st+find.size()])
        &&
        !(
          ispunct(source[st+find.size()])
          &&
          source[st+find.size()]!='_'
        )
      )
      return size_m;
  }
  return st;
}
//==============================================================================
err_t GetInt(const string &buf,int &out_,int signed_)
{//01-01-08
  size_t ix=0;
  string s=buf;
  int waga=1;
  int h=1;
  int sig=1;

  while(isspace(s[ix])) ++ix;
  if(s[ix]=='+'){
    sig=1;
    ++ix;
    while(isspace(s[ix])) ++ix;
  }else if(s[ix]=='-'){
    sig=-1;
    ++ix;
    while(isspace(s[ix])) ++ix;
  }
  s.erase(0,ix);
  ix=0; // usuniÍto poczπtkowy fragment napisu, wiÍc znak przesunπ≥ siÍ na pczπtek napisu
  if(s[ix]=='0'&&(s[ix+1]=='x'||s[ix+1]=='X')){
  /*
   * liczba w zapisie szesnastkowym
   */
    ix+=2;
    s.erase(0,ix); // odetnij przedrostkowy symbol liczby szesnastkowej
    ix=0;
    while(isxdigit(s[ix]))++ix;
    size_t i=ix;
    while(s[ix]=='\t'||s[ix]==' ')++ix;
    if(s[ix]!='\0')
      return ERR;
    if(i!=ix)
      s.erase(i);
  }else if((s[s.size()-1]=='h')||(s[s.size()-1]=='H')){
    if(isalpha(s[ix]))  //jako pierwszy znak liczby w zapisie szesnastkowym musi byÊ liczba
      return ERR;
    s.erase(s.size()-1);// odetnij przyrostkowy symbol liczby szesnastkowej
    ix=0;
    while(isxdigit(s[ix]))++ix;
    while(s[ix]=='\t'||s[ix]==' ')++ix;
    if(s[ix]!='\0')
      return false;
  }else if((s[s.size()-1]=='b')||(s[s.size()-1]=='B')){
    ix=s.size()-2;
    waga=1;
    out_=0;
    for(;ix<size_m;--ix){//strasznie g≥upie : && ix<size_m!!!!! a moøe jednak nie
      if(s[ix]=='1'){
        out_+=waga;
      }else if(s[ix]!='0'){
        out_=0.0;
        return ERR;
      }
      waga*=2;
    }
    return OK;
  }else{
    while(isdigit(s[ix]))++ix;
    while(s[ix]=='\t'||s[ix]==' ')++ix;
    if(s[ix]!='\0')
      return ERR;
    out_=atoi(s.c_str())*sig;
    return OK;
  };
  out_=0;
  for(ix=s.size()-1 ; ; ){
    if(s[ix]>='0'&&s[ix]<='9')        h=s[ix]-'0';
    else if(s[ix]>='a'&&s[ix]<='f')   h=s[ix]-'a'+10;
    else if(s[ix]>='A'&&s[ix]<='F')   h=s[ix]-'A'+10;
    else return ERR;
    h=h*waga; //*
    out_+=h;  // * ten kawa≥ek jest podejøany
    waga*=16; //*
    if(ix==0)
      break;
    else
      --ix;
  }
  out_*=sig;
  if((signed_==SIGNED)&&(out_>=INT_MAX))
    out_=INT_MAX-out_;
  return OK;
};
//=============================================================================
bool Log(const string plik,const string &log,bool add)
{
  ofstream file;
  string s;
  if(add)
    file.open(plik.c_str(),ios::app);
  else
    file.open(plik.c_str(),ios::out);
  if(file){
    file<<log.c_str();
  }else{
    return false;
  }
  file.close();
  return true;
}
//==============================================================================
string i2s(int i)
{//01-10-24
  char ac_number[30];
  itoa(i,ac_number,10);
  return string(ac_number);
}
//==============================================================================
string r2s(size_t i)
{//01-10-24
  string s;
  int dec,sig;
  s=ecvt(i,30,&dec,&sig);
  s.erase(dec);
  return s;
}
//=============================================================================
err_t s2d(const string &s,double &d)
{//04-03-07
  (s);
  (d);
  return ERR_FUN;
}
//=============================================================================
err_t StringToFile(const string &buf,const string &path)
{
  if(path.size()==0)
    return ERR_PAR_BAD;
  ofstream file(path.c_str());
  if(!file)
    return ERR_FILE_OPEN;
  file<<buf.c_str();
  if(!file)
    return ERR_FILE_WRITE;
  file.close();
  return OK;
};

//##############################################################################
// class CFileConfig

//=============================================================================
err_t CFileConfig::Init(const string & root_name_)
{//01-11-01;
  char *path_buf;
  mss_t::iterator mss_it;

  path_buf=getcwd(0,-1);
  if(!path_buf){
    return ERR_FILE_OPEN;
  }
  bin_path=path_buf;
  free(path_buf);
  root_name=root_name_;
  ReadConfig();

  for(mss_it=mss_cfg.begin();mss_it!=mss_cfg.end();mss_it++){
  /*
   * Przeglπda klucze w poszukiwaniu napisu DIR_... i wywo≥uje metode CreateDirectory()
   * ktÛra utworzy katalog DIR_... gdyby nie istnia≥
   */
    if(Find(mss_it->first,"dir_",0,false)!=size_m){
      //CreateDirectory(mss_it->second);
      mkdir(mss_it->second.c_str());
    }
  }
  if(GetOption("CLEAR_LOG")!=0){
  /*
   * Plik konfiguracyjny zawiera obcjÍ nakazujπ czyszczenie pliku z logami po kaødym starcie programu
   */
    ofstream file;
    string s=bin_path+"\\"+root_name+".log";
    file.open(s.c_str(),ios::out);
    file.close();
  }

  return OK;
}
//=============================================================================
err_t CFileConfig::GetConfig(const string &key,int &i_val)
{//01-11-01
  msi_t::iterator msi_it;
  msi_it=msi_cfg.find(key);
  if(msi_it!=msi_cfg.end()){
    i_val=msi_it->second;
    return OK;
  }
  return ERR_NOT_FIND;
}
//=============================================================================
err_t CFileConfig::GetConfig(const string &key,string &s_val)
{//01-11-01
  mss_t::iterator mss_it;
  mss_it=mss_cfg.find(key);
  if(mss_it!=mss_cfg.end()){
    s_val=mss_it->second;
    return OK;
  }
  return ERR_NOT_FIND;
}
//=============================================================================
int CFileConfig::GetOption(const string &key)
{//01-11-01
  msi_t::iterator msi_it;
  msi_it=msi_cfg.find(key);
  if(msi_it!=msi_cfg.end()){
    return msi_it->second;
  }
  return size_m2;
}
//=============================================================================
err_t CFileConfig::ReadConfig()
{//01-11-01

  string file;
  string key;
  string s_val;
  int i_val;
  size_t fi=0;
  size_t fsz;
  size_t fst;
  err_t err;
  string s=bin_path+"\\"+root_name+".cfg";

  if((err=FileToString(file,s))!=OK)
    return  err;

  fsz=file.size();
  while(fi<fsz){
    while(isspace(file[fi]) && fi<fsz)fi++;
    if(file[fi]=='#'){
    /*
     * Odnaleziono poczπtek komentarza. KoÒczy siÍ wraz z koÒcem wiersza
     */
      while(file[fi]!='\n' && fi<fsz)fi++;
    }else{
    /*
     * Jako pierwszy wystπpi≥ znak mogπcy budowaÊ identyfikator. Przejdü do koÒca tego ciπgu
     * i jeøeli jest poprawny pobierz go jako nazwÍ zmiennej. Po nazwie zmiennej wystÍpuje znak '='.
     * Znak ten moøe znajdowaÊ siÍ pomiÍdzy znakami bia≥ymi. Potem musi wystπpiÊ ciπg okreúlajπcy
     * wartoúÊ pobranej nazwy zmiennej.
     */
      fst=fi;// tu rozpoczyna siÍ nazwa definiowanego parametru
      while((isalnum(file[fi])||file[fi]=='_') && fi<fsz)fi++;
      key=file.substr(fst,fi-fst);
      // teraz szuka znaku '='
      while(isspace(file[fi])&&fi<fsz)fi++;
      if(file[fi++]!='=')
        return old::ERR_BAD_DEF;// po nazwie zmiennej musi byÊ znak '='
      while(isspace(file[fi])&&fi<fsz)fi++;
      if(fi>=fsz)
        return old::ERR_BAD_DEF;//po znaku '=' wystπpi≥ koniec pliku
      if(file[fi]=='\"'){
      /*
       * Po znaku '=' moøe wystπiÊ znak ". bÍdzie to oznaczaÊ øe zminna key jest typy string
       */
        fst=++fi;
        while(file[fi]!='\"' && file[fi]!='\n' &&  fi<fsz)fi++;
        if(file[fi]!='\"')
          return old::ERR_BAD_DEF;
        s_val=file.substr(fst,fi-fst);
        fi++;
        mss_cfg.insert(make_pair(key,s_val));
        key="";s_val="";
      }else{
      /*
       * Zmienna ktÛrπ obecnie przetwarzamy jest typu int
       */
        fst=fi;
        //  while((isalnum(file[fi])||file[fi]=='_') && fi<fsz)fi++;
        while(isdigit(file[fi]) && fi<fsz)fi++;
        s_val=file.substr(fst,fi-fst);
        if((err=GetInt(s_val,i_val,SIGNED))!=OK)
          return err;
        msi_cfg.insert(make_pair(key,i_val));
        key="";s_val="";
      }
      while(isspace(file[fi])&&fi<fsz)fi++;
    }
  }
  return OK;
}
//=============================================================================
err_t CFileConfig::SaveConfig()
{//01-11-01
  string file;
  string key;
  string s_val;
  string s=bin_path+"\\"+root_name+".cfg";
  size_t fi;
  size_t fsz;
  size_t fst=0;(fst);
  err_t err;
  mss_t::iterator mss_it;
  msi_t::iterator msi_it;

  if((err=old::FileRead(file,s))!=OK)
    return  err;
  fsz=file.size();
  for(mss_it=mss_cfg.begin();mss_it!=mss_cfg.end();mss_it++){
    fi=file.find(mss_it->first);
    while((isalnum(file[fi])||file[fi]=='_') && fi<fsz)fi++;
    while(isspace(file[fi])&&fi<fsz)fi++;
    if(file[fi++]!='=')
      return old::ERR_BAD_DEF;
    while(isspace(file[fi])&&fi<fsz)fi++;
      fst=++fi;//pierwszy znak wymieniany znajduje siÍ za znakiem :"
    while(file[fi]!='\"' && file[fi]!='\n' &&  fi<fsz)fi++;
      // tu moøe powstaÊ b≥πd gdy ktoú wpisze tekst zawiniÍty na kolejne wiersze !!!!!!!!!!
    file.replace(fst,fi-fst,mss_it->second);
  }
  for(msi_it=msi_cfg.begin();msi_it!=msi_cfg.end();msi_it++){
    s_val="";
    old::AddAsInt(s_val,msi_it->second,size_m);
    fi=file.find(msi_it->first);
    while((isalnum(file[fi])||file[fi]=='_') && fi<fsz)fi++;
    while(isspace(file[fi])&&fi<fsz)fi++;
    if(file[fi++]!='=')
      return old::ERR_BAD_DEF;
    while(isspace(file[fi])&&fi<fsz)fi++;
    fst=fi;
    while((isalnum(file[fi])||file[fi]=='_') && fi<fsz)fi++;
    file.replace(fst,fi-fst,s_val);
  }

  old::FileWrite(file,bin_path+"\\"+root_name+".cfg");
  return OK;
}
//=============================================================================
err_t CFileConfig::SetConfig(const string &key,int &i_val)
{//01-11-01
  msi_t::iterator msi_it;
  msi_it=msi_cfg.find(key);
  if(msi_it!=msi_cfg.end()){
    msi_it->second=i_val;
    return OK;
  }
  return ERR_NOT_FIND;
}
//=============================================================================
err_t CFileConfig::SetConfig(const string &key,string &s_val)
{//01-11-01
  mss_t::iterator mss_it;
  mss_it=mss_cfg.find(key);
  if(mss_it!=mss_cfg.end()){
    mss_it->second=s_val;
    return OK;
  }
  return ERR_NOT_FIND;
}


















//##############################################################################
// obszar przestarza≥y

//==============================================================================
err_t old::AddAsBin(string &buf,int number_,size_t pos_)
//==============================================================================
{//01-10-23
  size_t sz=numeric_limits<unsigned int>::digits;
  string s(sz,'0');
  unsigned int bit=1;
  size_t i;
  size_t ii=31;

  for(i=1;i<=sz;i++,(bit=bit<<1)){
    if(number_ & bit){
      s[sz-i]='1';
      ii=sz-i;
    }
  }
  if(ii>23){
    ii=24;
  }else if(ii>15){
    ii=16;
  }else{
    ii=0;
  }
  s.erase(0,ii);
  Add(buf,s+"B",pos_);
  return OK;
}

//==============================================================================
int old::AddAsHex(string &buf,int number_,int digit_,int signed_,int typ_,size_t pos_)//++
//==============================================================================
{//01-02-22
  char ac_number[30];
  char ac_digit[30];
  int number_s=0;
  int number_i;
  int digit_s=digit_+1;
  int digit_i;

  if( (digit_ % 2) != 0) // liczba cyfr musi byÊ parzysta bo najmniejsza wartoúÊ hex zajmuje dwa znaki
      digit_++;
  if((number_<0) && (signed_==UNSIGNED)) // oczekiwano liczby bez znaku a jej wartoúÊ jest ujemna
    return ERR_SIGNED;
  itoa(number_,ac_number,16);
  while(ac_number[number_s++]!='\0')/*...*/;
  for(digit_i=0;digit_i<digit_s;digit_i++)
    ac_digit[digit_i]='0';
  if(number_>=0){
  /*
   * Sprawdzenie czy liczba mieúci siÍ w zadanej precyzji
   */
    if((number_s-1) > digit_)
      return ERR_RANGE;
  }else{
  /*
   * Sprawdzenie czy liczba mieúci siÍ w zadanej precyzji. Poniewaø jest to liczba ujemna w sapisie
   * szesnastkowym bardziej znaczoπce znaki to "f". Aby zmienna mieúci≥a siÍ w przyjÍtym zakresie
   * znak inny niø "f" nie moøe wystπpiÊ na digit_ bardziej znaczπcych pozycjach.
   */
    int tt=number_s-1-digit_;
    for(number_i=0;number_i<tt;number_i++){
      if((ac_number[number_i]!='F')&&(ac_number[number_i]!='f'))
        return ERR_RANGE;
    }
  }
  for(digit_i=digit_s-1,number_i=number_s-1;digit_i>=0 && number_i>=0;digit_i--,number_i--)
    ac_digit[digit_i]=ac_number[number_i];
  switch(typ_)
  {
    case HEX_C:
      for(digit_i=digit_s-1;digit_i> -1;digit_i--)
        ac_digit[digit_i+2]=ac_digit[digit_i];
      ac_digit[0]='0';
      ac_digit[1]='x';
    break;
    case HEX_ASM:
      ac_digit[digit_s-1]='h';
      ac_digit[digit_s++]='\0';
      if(ac_digit[0]<'0'||ac_digit[0]>'9'){
        for(digit_i=digit_s-1;digit_i> -1;digit_i--)
          ac_digit[digit_i+1]=ac_digit[digit_i];
        ac_digit[0]='0';
      };
    break;
    case ENDIAN_BIG:
      for(digit_i=0;digit_i<((digit_s-1)/2);digit_i+=2){
        ac_number[0]=ac_digit[digit_i];
        ac_number[1]=ac_digit[digit_i+1];
        ac_digit[digit_i]=ac_digit[digit_s-1-digit_i-2];
        ac_digit[digit_i+1]=ac_digit[digit_s-1-digit_i-1];
        ac_digit[digit_s-1-digit_i-2]=ac_number[0];
        ac_digit[digit_s-1-digit_i-1]=ac_number[1];
      };
    break;
  };
  if(pos_ > buf.size()){
    if(pos_==size_m)
      pos_=buf.size();
    buf.insert(pos_,ac_digit);
  }else{
    buf.insert(pos_,ac_digit);
  }
  return 0;
};

//==============================================================================
void old::AddAsInt(string &buf,int number_,size_t pos_)//++
//==============================================================================
{//00-12-13
  char ac_number[30];

  itoa(number_,ac_number,10);
  if(pos_ > buf.size()){
    if(pos_==size_m)
      pos_=buf.size();
    buf.insert(pos_,ac_number);
  }else{
    buf.insert(pos_,ac_number);
  }
};

//==============================================================================
err_t old::cena(string &s)
//==============================================================================
{
  size_t i=0;
  size_t sz=s.size();
  string s_tmp;
  size_t kropka=0;

  for( ; isspace(s[i])&&i<sz;i++)/*...*/;
  if(s[i]=='+'){
    i++;
  }
  if(s[i]=='-'){
    s_tmp+=s[i];
    i++;
  }
  for( ; isspace(s[i])&&i<sz;i++)/*...*/;
  /*
   * Tu moøe byÊ tylko , lub liczby  jeøeli jest coú innego to to nie jest zapis ceny
   */
  if(s[i]==',' || s[i]=='.'){//przecinek lub kropka bez liczb poprzedzajπcych
    s_tmp+="0.";
    kropka=i++;
    kropka++;
  }
  while(isdigit(s[i])&&i<sz){
    s_tmp+=s[i++];
  }
  if(s[i]==',' || s[i]=='.'){
    s_tmp+=".";
    kropka=i++;
  }
  while(isdigit(s[i]) && i<sz){
    s_tmp+=s[i];
    i++;
  }
  if(i<sz){
    return ERR_BAD_VALUE;
  }
  s=s_tmp;
  double d=atof(s_tmp.c_str());
  s=d2s(d,2);
  if((kropka=s.find("."))!=string::npos){
    s[kropka]=',';
    if(kropka==0)
      s.insert(0,"0");
  }else{
    s+=",00";
  }

  return OK;
}

//==============================================================================
err_t old::cena(string &s,double &d)
//==============================================================================
{
  size_t i=0;
  size_t sz=s.size();
  string s_tmp;
  size_t kropka=0;

  for( ; isspace(s[i])&&i<sz;i++)/*...*/;
  if(s[i]=='+'){
    i++;
  }
  if(s[i]=='-'){
    s_tmp+=s[i];
    i++;
  }
  for( ; isspace(s[i])&&i<sz;i++)/*...*/;
  /*
   * Tu moøe byÊ tylko , lub liczby  jeøeli jest coú innego to to nie jest zapis ceny
   */
  if(s[i]==',' || s[i]=='.'){//przecinek lub kropka bez liczb poprzedzajπcych
    s_tmp+="0.";
    kropka=i++;
    kropka++;
  }
  while(isdigit(s[i])&&i<sz){
    s_tmp+=s[i++];
  }
  if(s[i]==',' || s[i]=='.'){
    s_tmp+=".";
    kropka=i++;
  }
  while(isdigit(s[i]) && i<sz){
    s_tmp+=s[i];
    i++;
  }
  if(i<sz){
    return ERR_PAR_BAD;
  }
  if(kropka && (s_tmp.size()>kropka+3) ){
    s_tmp.erase(kropka+3);
  }
  s=s_tmp;
  d=atof(s_tmp.c_str());
  s=d2s(d,2);
  if((kropka=s.find("."))!=string::npos){
    s[kropka]=',';
    if(kropka==0)
      s.insert(0,"0");
  }else{
    s+=",00";
  }

  return OK;
}

const char *polchar="\0 _0123456789Aa•πBbCc∆ÊDdEe ÍFfGgHhIiJjKkLl£≥MmNn—ÒOo”ÛPpQqRrSsåúTtUuVvWwXxYyZzØøèü!\"#$%&()*+-./?:;<=>?@[\\]^`'{|}~";
const char polsz=112;
//==============================================================================
int old::csort(const string &lv,const string &pv)
//==============================================================================
{
  const char *cl=&(lv[0]);
  const char *cp=&(pv[0]);
  size_t lvi=0;
  size_t pvi=0;

  while((*cl==*cp) && *cl!='\0' && *cp!='\0'){
    cl++;
    cp++;
  };

  while(*cp!=polchar[pvi] && pvi<polsz) ++pvi;
  while(*cl!=polchar[lvi] && lvi<polsz) ++lvi;

  if(lvi<pvi){
    return 1;
  }else if(lvi==pvi){
    return 0;
  }else{
    return -1;
  }
}

//==============================================================================
bool old::cs(const string &s_lv,const string &s_pv)
//==============================================================================
{//01-05-06
  string::const_iterator lv_it =s_lv.begin();
  string::const_iterator pv_it =s_pv.begin();
  if(s_pv.size() != s_lv.size())
    return false;
  while(lv_it!=s_lv.end() && pv_it!=s_pv.end()){
    if(my_toupper(*lv_it)!=my_toupper(*pv_it))
      return false;//(my_toupper(*lv_it)<my_toupper(*pv_it)) ? 0 : 0 ;
    lv_it++;
    pv_it++;
  }
  return true;//(s_lv.size() < s_pv.size() ) ? -1 : 1;
}

//==============================================================================
bool old::csu(const string &s_lv,const string &s_pv)
//==============================================================================
{//01-05-06
  string::const_iterator lv_it =s_lv.begin();
  string::const_iterator pv_it =s_pv.begin();
  if(s_pv.size() != s_lv.size())
    return false;
  while(lv_it!=s_lv.end() && pv_it!=s_pv.end()){
    if(my_toupper(*lv_it)!=*pv_it)
      return false;//(my_toupper(*lv_it)<my_toupper(*pv_it)) ? 0 : 0 ;
    lv_it++;
    pv_it++;
  }
  return true;//(s_lv.size() < s_pv.size() ) ? -1 : 1;
}

//==============================================================================
size_t old::csdorozny(const string &lv,const string &pv)
//==============================================================================
{
  size_t i=0;
  do{
    if(lv[i]!=pv[i])
      break;
    i++;
  }while(i<lv.size()&&i<pv.size());
  return i;
}

//==============================================================================
size_t old::csudorozny(const string &lv,const string &pv)
//==============================================================================
{
  size_t i=0;
  do{
    if(my_toupper(lv[i])!=my_toupper(pv[i]))
      break;
    i++;
  }while(i<lv.size()&&i<pv.size());
  return i;
}

//==============================================================================
string old::d2s(double d,int round_)
//==============================================================================
{
  int dec,sig;
  string s;
  s=ecvt(d,1000,&dec,&sig);  // nie zaokrπglam aby znaÊ pozycje kropki
  if(round_>-1){
    round_+=dec;
    if(s[round_]<='5')
      s[round_]=0;
    s=ecvt(d,round_,&dec,&sig);
  }
  if(dec==0){
    s.insert(0,".");
  }else if(dec<0){
    dec*= -1;
    s.insert(0,"0",dec);
    s.insert(0,".");
  }else{
    s.insert(dec,".");
  }
  if(sig)
    s.insert(0,"-");
  return s;
}


//==============================================================================
void old::DelSpaceFlank(string &buf)//++
//==============================================================================
{//00-06-11
  DelSpaceLeft(buf);
  DelSpaceRight(buf);
};

//==============================================================================
void old::DelSpaceLeft(string &buf)//++
//==============================================================================
{//00-12-08;01-10-18
  if(buf.size()==0)
    return;
  size_t i=0;
  size_t sz=buf.size();
  for(;isspace(buf[i])&&i<sz;i++)/*...*/;
  buf.erase(0,i);
};

//==============================================================================
void old::DelSpaceRight(string &buf)//++
//==============================================================================
{//00-12-08;01-10-18
  if(buf.size()==0)
    return;
  size_t i=buf.size()-1;

  for(;isspace(buf[i]);i--)/*...*/;
  buf.erase(i+1);
};

//==============================================================================
err_t old::FileRead(string &buf,const string &path_)
//==============================================================================
{
  const size_t rozmiar_buf=1024;
  (rozmiar_buf);
  if(path_.size()==0)
    return ERR;
  char tmp_buf[rozmiar_buf];
  ifstream file(path_.c_str());

  if(file){
      for(;!file.eof();){
        file.getline(tmp_buf,rozmiar_buf,'\n');
        buf+=tmp_buf;
        buf+="\n";
      }
    file.close();
  }else{
    return ERR_NOT_OPEN;
  }
  return OK;
};

//==============================================================================
err_t old::FileWrite(string &buf,const string &path_)
//==============================================================================
{
  if(path_.size()==0)
    return ERR;
  ofstream file(path_.c_str());

  if(file){
    file<<buf.c_str();
  }else{
    return ERR_NOT_OPEN;
  }
  file.close();
  return OK;
}

//==============================================================================
size_t old::FiltrDaty(string &data_)
//==============================================================================
{//03-05-22
/*
 * Naleøy poprawiÊ funkcje aby kontrolowa≥a czy podane liczby jako numery miesiecy i
 * dni wystÍpujπ w podanej kofiguracji (lata przestÍpne)
 */
  size_t i=0;
  if(data_.size()>10){
  /*
   * Data moøe byÊ zapisana rozwlekle np: _19999_-_ 02-_31_ gdzie _ oznacza spacje.
   * naleøy wiÍc zpakowaÊ ca≥y napis
   */
    old::Pack(data_);
  }

  for( ; i<4 ; ++i){
  /*
   * Rok musi zawieraÊ cztery liczby. Jeøeli nie zawiera czterech iczb to data uwaøana jest za b≥Ídnπ.
   */
    if(!isdigit(data_[i]))
      return size_m;
  };
  /*++i;*/  // RRRR-
  if(data_[i]!='-')
    return size_m;
  ++i;  // RRRR-M
  if(data_[i]=='0'){
    ++i; // RRRR-MM
    if(!isdigit(data_[i+1])){
      return size_m;
    }
  }else if(data_[i]=='1'){
    ++i; // RRRR-MM
    if(data_[i+1]!='0' && data_[i+1]!='1' && data_[i+1]!='2'){
      return size_m;
    }
  }else{
    return size_m;
  }
  ++i;  // RRRR-MM-
  if(data_[i]!='-')
    return 0;
  ++i;  // RRRR-MM-D
  switch(data_[i]){
    case '0':
    case '1':
    case '2':
      ++i; // RRRR-MM-DD
      if(!isdigit(data_[i]))
        return data_.size();
    break;
    case '3':
      ++i;  // RRRR-MM-DD
      switch(data_[i]){
        case '0':
    case '1':
    break;
    default:
      return data_.size();
      }
    break;
    default: // w numerze dnia wystπpi≥uy za duøe liczby
      return data_.size();
  }
  return 0;
}

//==============================================================================
size_t old::Find(const string &s_source_,const string &s_find_,size_t start,bool sep_)
//==============================================================================
{//01-09-05;01-11-10
  size_t ix;
  size_t sz;
  size_t st;
  string s_source=s_source_;
  string s_find=s_find_;

  if(start>=s_source_.size()){
    return size_m;
  }
  for(ix=0,sz=s_source.size();ix<sz;ix++){
    s_source[ix]=static_cast<char>(my_toupper(s_source[ix]));
  }
  for(ix=0,sz=s_find.size();ix<sz;ix++){
    s_find[ix]=static_cast<char>(my_toupper(s_find[ix]));
  }
  st=s_source.find(s_find,start);
  if(st==size_m)
    return size_m;
  if(sep_){
    if(st!=0){
    /*
     * jeøeli find zaczyna siÍ na poczπtku source to jest z tej strony odseparowany
     */
      if(
          !isspace(s_source[st-1])
          &&
          !(
            ispunct(s_source[st-1])
            &&
            s_source[st-1]!='_'
          )
        )
        return size_m;
    }

    if(st+s_find.size()==s_source.size()){
    /*
     * Jeøeli find koÒczy siÍ na koÒcu source to jest z tej strony odseparowany
     */
      return st;
    }

    if(
        !isspace(s_source[st+s_find.size()])
        &&
        !(
          ispunct(s_source[st+s_find.size()])
          &&
          s_source[st+s_find.size()]!='_'
        )
      )
      return size_m;
  }
  return st;
}

//==============================================================================
string old::GetBlock(const string &s_,size_t &ix_)
//==============================================================================
{
  size_t st=ix_;
  size_t ix=ix_;
  size_t sz=s_.size();
  size_t naw_ct=0;

  switch(s_[ix]){
    case '(':case'{':case'[': naw_ct++; st=++ix; break;
  }
  if(naw_ct){
    do{
      switch(s_[ix]){
        case '(':case'{':case'[': naw_ct++; break;
        case ')':case'}':case']': naw_ct--; break;
      }
      ix++;
    }while(naw_ct!=0 && (ix<sz));
  }else{
    while((my_isalnum(s_[ix])||s_[ix]!='_') && (ix < sz) ) ix++;
  };
  for(ix_=ix;isspace(s_[ix_]) && (ix_<sz);ix_++)/*...*/;
  return s_.substr(ix_,st-ix);
}

//==============================================================================
err_t old::GetDouble(string s_,double &out_,int signed_)
//==============================================================================
{//01-07-01
  string s;
  size_t s_st=0;
  size_t s_sp=s_.size()-1;
  size_t s_ix;
  int waga=1;
  int h;
  int sig=1;

  while(isspace(s_[s_sp])){ // pomijamy tylne znaki
    if(s_sp==0)
      return ERR_NOT_VALUE;
    else
      s_sp--;
  }
  while(isspace(s_[s_st])){
    s_st++;
    if(s_st==s_sp)
      return ERR_NOT_VALUE;
  }
  switch(s_[s_st]){ // trafiono na znak liczby
    case '-':
      sig= -1;
    case '+':
      s_st++;
  }
  if(isspace(s_[s_st]))  // spacje pomiÍdzy znakami a resztπ liczby
    s_st++;
  if(s_st>s_sp)
    return ERR_BAD_VALUE;
  while(isspace(s_[s_st])){
    if(s_st==s_sp)
      return ERR_NOT_VALUE;
    else
      s_st++;
  }
  if(s_[s_st]=='0'&&(s_[s_st+1]=='x'||s_[s_st+1]=='X')){
    s_st+=2;
  }else if((s_[s_sp]=='h')||(s_[s_sp]=='H')){
    s_sp--;
  }else if((s_[s_sp]=='B')||(s_[s_sp]=='b')){
    s_ix= --s_sp;
    waga=1;
    out_=0.0;
    for(;s_st<=s_ix && s_ix!=size_m;s_ix--){//strasznie g≥upie : && s_ix!=size_m!!!!!
      if(s_[s_ix]=='1'){
        out_+=waga;
      }else if(s_[s_ix]!='0'){
        out_=0.0;
        return ERR;
      }
      waga*=2;
    }
    return OK;
  }else{
    s_.erase(0,s_st);
    char *ep=0;
    out_=strtod(s_.c_str(),&ep)*sig;
    if(out_ == HUGE_VAL || out_== -HUGE_VAL){
//      if(errno==ERANGE)
        return ERR_RANGE;
    }else if(ep!=0&&!cs(ep,"")){
      return ERR;
    };
    return OK;
  };
  out_=0.0;
  if(s_sp>=s_st){
    s=s_.substr(s_st,(s_sp-s_st)+1);
    s_sp-=s_st;
  }else{
    return ERR_BAD_VALUE;
  }
  s_ix = s_sp+1;// To +1 jeden dlatego bo nie potrafiÍ inaczej zaprogramowaÊ indeksowania
  while(s_ix -- >0){
    if(s[s_ix]>='0'&&s[s_ix]<='9')
      h=s[s_ix]-'0';
    else if(s[s_ix]>='a'&& s[s_ix]<='f')
      h=s[s_ix]-'a'+10;
    else if(s[s_ix]>='A'&& s[s_ix]<='F')
      h=s[s_ix]-'A'+10;
    else return ERR_BAD_VALUE;
    h=h*waga; //*
    out_+=h;  // * ten kawa≥ek jest podejøany
    waga*=16; //*
  };
  out_*=sig;
  if((signed_==SIGNED)&&(out_>=INT_MAX))
    out_=INT_MAX-out_;
  return OK;
};

//==============================================================================
string old::GetExpr(const string &buf,size_t &st_)
//==============================================================================
{
  (buf);
  (st_);
  return "GetExpr(...) w budowie";
};


//==============================================================================
err_t old::GetInt(const string &buf,int &out_,int signed_)
//==============================================================================
{//01-01-08
  size_t ix=0;
  string s=buf;
  Pack(s);
  int waga=1;
  int h=1;
  int sig=1;

  NextNoWhite(s,ix);
  if(s[ix]=='+'){
    sig=1;
    s.erase(0,ix+1);
  }
  if(s[ix]=='-'){
    sig=-1;
    s.erase(0,ix+1);
  }
  ix=0;
  NextNoWhite(s,ix);
  if(s[ix]=='0'&&(s[ix+1]=='x'||s[ix+1]=='X')){
    ix++;
    s.erase(0,ix+1);
    ix=0;
    while(isxdigit(s[ix]))ix++;
    while(s[ix]=='\t'||s[ix]==' ')ix++;
    if(s[ix]!='\0')
      return ERR;
  }else if((s[s.size()-1]=='h')||(s[s.size()-1]=='H')){
    if(my_isalpha(s[ix]))
      return ERR;
    s.erase(s.size()-1);
    ix=0;
    if(!isxdigit(s[ix]))
      return ERR;
    while(isxdigit(s[ix]))ix++;
    while(s[ix]=='\t'||s[ix]==' ')ix++;
    if(s[ix]!='\0')
      return false;
  }else if((s[s.size()-1]=='B')||(s[s.size()-1]=='b')){
    ix= s.size()-2;
    waga=1;
    out_=0;
    for(;ix<size_m;ix--){//strasznie g≥upie : && ix<size_m!!!!! a moøe jednak nie
      if(s[ix]=='1'){
        out_+=waga;
      }else if(s[ix]!='0'){
        out_=0.0;
        return ERR;
      }
      waga*=2;
    }
    return OK;
  }else{
    while(isdigit(s[ix]))ix++;
    while(s[ix]=='\t'||s[ix]==' ')ix++;
    if(s[ix]!='\0')
      return ERR;
    out_=atoi(s.c_str())*sig;
    return OK;
  };
  out_=0;
  for(ix=s.size()-1 ; ; ){
    if(s[ix]>='0'&&s[ix]<='9')        h=s[ix]-'0';
    else if(s[ix]>='a'&&s[ix]<='f')   h=s[ix]-'a'+10;
    else if(s[ix]>='A'&&s[ix]<='F')   h=s[ix]-'A'+10;
    else return ERR;
    h=h*waga; //*
    out_+=h;  // * ten kawa≥ek jest podejøany
    waga*=16; //*
    if(ix==0)
      break;
    else
      ix--;
  }
  out_*=sig;
  if((signed_==SIGNED)&&(out_>=INT_MAX))
    out_=INT_MAX-out_;
  return OK;
};

//==============================================================================
int old::GetIntH(const string &buf,int &out_,int signed_)//++
//==============================================================================
{
  size_t ix=0;
  int waga=1;
  int h=1;
  int sig=1;

  ix=0;
  NextNoWhite(buf,ix);
  out_=0;
  for(ix=buf.size()-1;;){
    if     (buf[ix]>='0'&&buf[ix]<='9')   h=buf[ix]-'0';
    else if(buf[ix]>='a'&&buf[ix]<='f')   h=buf[ix]-'a'+10;
    else if(buf[ix]>='A'&&buf[ix]<='F')   h=buf[ix]-'A'+10;
    else return ERR;
    h=h*waga; //*
    out_+=h;  // * ten kawa≥ek jest podejøany
    waga*=16; //*
    if(ix==0)
      break;
    else
      ix--;
  }
  out_*=sig;
  if((signed_==SIGNED)&&(out_>=INT_MAX))
    out_=INT_MAX-out_;
  return OK;
};


//==============================================================================
string old::GetProgr(const string &buf,size_t &sta_ix_,size_t &sto_ix_)//++
//==============================================================================
{//00-08-18
  if(buf.size()==0)
    return "";
  size_t ix;
  size_t sz=buf.size();

  if(sta_ix_>=sz)
    return "";
  ix=sta_ix_;
  while(ix<sz && isspace(buf[ix]))ix++;//Gdyby zaczÍto od pustego miejsca
    sta_ix_=ix;
  NextProgr(buf,ix);
  sta_ix_=ix;
  while(ix<sz && my_isalnum(buf[ix])||buf[ix]=='_')ix++;
  sto_ix_=ix;
  return buf.substr(sta_ix_,(sto_ix_-sta_ix_));//Get(buf,sta_ix_,sto_ix_);
}

//==============================================================================
err_t old::GetULong(const string & str, unsigned long & l_)
//==============================================================================
{
  char *stop;
  if(str=="")
    return ERR_BAD_VALUE;
  l_=strtoul(str.c_str(),&stop,10);
  if(l_==numeric_limits<unsigned long>::max())
    return ERR_RANGE;
  if(*stop!='\0')
    return ERR_BAD_VALUE;
  return OK;
}

//==============================================================================
string old::i2s(int i)
//==============================================================================
{//01-10-24
  char ac_number[30];
  itoa(i,ac_number,10);
  return string(ac_number);
}

//==============================================================================
bool old::Nul(const string &buf)
//==============================================================================
{//01-05-07
  if(buf.size()==0){
    return true;
  }else{
    size_t si=0;
    do{
      if(my_isgraph(buf[si]))
        return false;
    }while(++si<buf.size());
    return true;
  }
};

//==============================================================================
char old::PrevAlpha(const string &buf,size_t &i_)
//==============================================================================
{//01-02-27
  if(buf.size()==0)
    return '\0';
  if(i_>=buf.size())
    i_=buf.size()-1;
  do{
    if(my_isalpha(buf[i_]))
      return buf[i_];
  }while(i_-- > 0);
  i_=string::npos;
  return '\0';
};

//==============================================================================
char old::NextAlpha(const string &buf,size_t &i_)
//==============================================================================
{//01-02-27
  if(buf.size()==0)
    return '\0';
  size_t buf_s=buf.size();
  for(;i_<buf_s;i_++){
    if(my_isalpha(buf[i_]))
      return buf[i_];
  }
  i_=string::npos;
  return '\0';
};

//==============================================================================
char old::PrevProgr(const string &buf,size_t &i_)
//==============================================================================
{//01-02-27
  if(buf.size()==0)
    return '\0';
  if(i_>=buf.size())
    i_=buf.size()-1;
  do{
    if(my_isalnum(buf[i_])||buf[i_]=='_')
      return buf[i_];
  }while(i_-- >0);
  i_=string::npos;
  return '\0';
};

//==============================================================================
char old::NextProgr(const string &buf,size_t &i_)//++
//==============================================================================
{//01-02-27
  if(buf.size()==0)
    return '\0';
  size_t buf_s=buf.size();
  for(;i_<buf_s;i_++){
    if(my_isalnum(buf[i_])||buf[i_]=='_')
      return buf[i_];
  }
  i_=string::npos;
  return '\0';
};

//==============================================================================
char old::PrevPrint(const string &buf,size_t &i_)
//==============================================================================
{//01-02-27
  if(buf.size()==0)
    return '\0';
  if(i_>=buf.size())
    i_=buf.size()-1;
  do{
    if(my_isprint(buf[i_]))
      return buf[i_];
  }while(i_-- >0);
  i_=string::npos;
  return '\0';
};

//==============================================================================
char old::NextPrint(const string &buf,size_t &i_)
//==============================================================================
{//01-02-27
  if(buf.size()==0)
    return '\0';
  size_t buf_s=buf.size();
  for(;i_<buf_s;i_++){
    if(my_isprint(buf[i_]))
      return buf[i_];
  }
  i_=string::npos;
  return '\0';
};

//==============================================================================
char old::PrevWhite(const string &buf,size_t &i_)
//==============================================================================
{//01-02-27
  if(buf.size()==0)
    return '\0';
  if(i_>=buf.size())
    i_=buf.size()-1;
  do{
    if(isspace(buf[i_]))
      return buf[i_];
  }while(i_-- >0);
  i_=string::npos;
  return '\0';
};

//==============================================================================
char old::NextWhite(const string &buf,size_t &i_)//+
//==============================================================================
{//01-02-27
  if(buf.size()==0)
    return '\0';
  size_t buf_s=buf.size();
  for(;i_<buf_s;i_++){
    if(isspace(buf[i_]))
      return buf[i_];
  }
  i_=string::npos;
  return '\0';
};

//==============================================================================
char old::PrevSpace(const string &buf,size_t &i_)
//==============================================================================
{//01-02-27
  if(buf.size()==0)
    return '\0';
  if(i_>=buf.size())
    i_=buf.size()-1;
  do{
    if(buf[i_]==' '||buf[i_]=='\t')
      return buf[i_];
  }while(i_-- >0);
  i_=string::npos;
  return '\0';
};

//==============================================================================
char old::NextSpace(const string &buf,size_t &i_)
//==============================================================================
{//01-02-27
  if(buf.size()==0)
    return '\0';
  size_t buf_s=buf.size();
  for(;i_<buf_s;i_++){
    if(buf[i_]==' '||buf[i_]=='\t')
      return buf[i_];
  }
  i_=string::npos;
  return '\0';
};

//==============================================================================
char old::PrevNoWhite(const string &buf,size_t &i_)//++
//==============================================================================
{//01-05-07
  if(buf.size()==0)
    return '\0';
  if(i_>=buf.size())
    i_=buf.size()-1;
  do{
    if(my_isgraph(buf[i_]))
      return buf[i_];
  }while(i_-- > 0);
  i_=string::npos;
  return '\0';
};

//==============================================================================
char old::NextNoWhite(const string &buf,size_t &i_)//+
//==============================================================================
{//01-05-07
  size_t buf_s=buf.size();
  if(buf.size()==0||i_>=buf_s)
    return '\0';
  for(;i_<buf_s;i_++){
    if(my_isgraph(buf[i_]))
      return buf[i_];
  };
  i_=string::npos;
  return '\0';
};

//##############################################################################
//##############################################################################

int old::ispl(int c){
          switch(c){
            case 'π': case 'Ê': case 'Í': case '≥': case 'Ò': case 'Û': case 'ú': case 'ü': case 'ø':
              return 1;
          };
          return 0;
        };

int old::isPL(int c){
          switch(c){
            case '•': case '∆': case ' ': case '£': case '—': case '”': case 'å': case 'è': case 'Ø':
              return 1;
          };
          return 0;
        };
int old::my_isalpha(int c){
          if(isalpha(c))
            return 1;
          if(ispl(c)||isPL(c))
            return 1;
          return 0;
        };
int old::my_isalnum(int c){
          if(isalnum(c))
            return 1;
          if(ispl(c)||isPL(c))
            return 1;
          return 0;
        };
int old::my_islower(int c){
          if(isalpha(c))
            return 1;
          if(ispl(c))
            return 1;
          return 0;
        };
int old::my_isupper(int c){
          if(isalpha(c))
            return 1;
          if(isPL(c))
            return 1;
          return 0;
        };
int old::my_tolower(int c){
          switch(c){
            case '•': case 'π': return 'π';
            case '∆': case 'Ê': return 'Ê';
            case ' ': case 'Í': return 'Í';
            case '£': case '≥': return '≥';
            case '—': case 'Ò': return 'Ò';
            case '”': case 'Û': return 'Û';
            case 'å': case 'ú': return 'ú';
            case 'è': case 'ü': return 'ü';
            case 'Ø': case 'ø': return 'ø';
          }
          return tolower(c);
        };
int old::my_toupper(int c){
          switch(c){
            case 'π': case '•': return '•';
            case 'Ê': case '∆': return '∆';
            case 'Í': case ' ': return ' ';
            case '≥': case '£': return '£';
            case 'Ò': case '—': return '—';
            case 'Û': case '”': return '”';
            case 'ú': case 'å': return 'å';
            case 'ü': case 'è': return 'è';
            case 'ø': case 'Ø': return 'Ø';
          }
          return toupper(c);
        };
int old::my_isprint(int c){
          if(isprint(c))
            return 1;
          if(ispl(c)||isPL(c))
            return 1;
          return 0;
        };
int old::my_isgraph(int c){
          if(isgraph(c))
            return 1;
          if(ispl(c)||isPL(c))
            return 1;
          return 0;
        };
//##############################################################################
//##############################################################################


//==============================================================================
void old::Pack(string &buf)
//==============================================================================
{//01-05-07;00-07-28
  if(buf.size()==0)
    return;
  size_t si=0;

  do{
    if(isspace(buf[si]))
      buf.erase(si,1);
    else
      si++;
  }while(buf.size()>si);
};

//==============================================================================
string old::Param(const string &buf,size_t &ix_)
//==============================================================================
{//02-02-28
 (buf);
 (ix_);
/*  if(buf.size()==0)
    return "";
  int naw=0;
  size_t sz=buf.size();
  size_t ix;

  if(sz<=ix_)
    return "";
  while(isspace(buf[ix_]) && ix_<sz)ix_++;//Gdyby zaczÍto od pustego miejsca
  ix=ix_;
  do{
    if(buf[ix_]=='(')
      naw++;
    if(buf[ix_]==')')
      naw--;
  }while(buf[ix_]!=','&& buf[ix_]!=';' && ix_<sz && naw >=0 );
  if(ix_<sz){
    sz=ix_-1;
    while(isspace(buf[sz]))sz--;
  }
  return buf.substr(ix,sz-ix_+1);
*/
  return "ERROR : Funkcja Param() nie jest utworzona";
};

//==============================================================================
string old::Read(const string &buf,size_t &ix_,string s_lim_="+-*:/;,. (){}[]\t\n\r\f")
//==============================================================================
{//02-02-06;00-01-01
  if(buf.size()==0)
    return "";

  size_t buf_st;
  size_t buf_sz=buf.size();
  string s_out;

  NextNoWhite(buf,ix_);
  buf_st=ix_;
  for( ; ix_<buf_sz;ix_++)
    if(s_lim_.find(buf[ix_])!=string::npos)
      break;
  s_out=buf.substr(buf_st,ix_-buf_st); // na pozycji ix_ jest znak nie naleø±cy do pobieranego napisu
  return s_out;
}

//==============================================================================
string old::Shift(string &buf,size_t sw=WITH_LIM,string s_=" .,\t\n\r\f")
//==============================================================================
{//01-05-05
  if(buf.size()==0)
    return "";
  size_t buf_ix=0;
  size_t buf_st;
  size_t buf_sz=buf.size();
  string s_new;

  NextNoWhite(buf,buf_ix);
  buf_st=buf_ix;
  for(;buf_ix<buf_sz;buf_ix++){
    if( s_.find(buf[buf_ix])!=string::npos)
      break;
  }
  if(buf_ix<buf_sz){
    s_new=buf.substr(buf_st,buf_ix-buf_st);
    if(sw==WITH_LIM)
      buf_ix++;
    buf.erase(0,buf_ix);
  }else{
    s_new=buf;
    buf.erase();
  }
  return s_new;
}

//==============================================================================
string old::ShiftToken(string &buf)
//==============================================================================
{//01-05-25
  size_t start=0;
  size_t stop=0;
  string ret = Token(buf,start,stop);
  buf.erase(0,stop);
  return ret;
}

//==============================================================================
string old::ShiftParam(string &s_)
//==============================================================================
{
  size_t st=0,sp=0;
  string s;

  NextNoWhite(s_,st);
  sp=s_.find(",",st);
  if(sp==string::npos)
    sp=s_.size()-1;
  else
    sp--; // nie chcemy by index wskazywa≥ na przecinek
  PrevNoWhite(s_,sp);
  s=s_.substr(st,(sp-st)+1); // wysuniÍty parametr
  // oczyszczmy ürÛd≥o :
  st=s_.find(",",sp);
  if(st==string::npos){
    s_.erase();
  }else{
    st++;
    NextNoWhite(s_,st);
    s_.erase(0,st);
  }
  return s;
}

//==============================================================================
string old::Token(const string &s,size_t &st,size_t &sp)
//==============================================================================
{//01-11-18
  if(st>=s.size())
    return "";
  size_t ix;
  size_t sz=s.size();

  while(isspace(s[st]) && st<sz)st++;
  if(st>=sz)
    return "";
  sp=ix=st;
  if(ispunct(s[ix]) && s[ix]!='_' && s[ix]!='.'){
  /*
   * Wszystkie symbole prÛcz wyrÛønionych zawsze samodzielnie tworzπ token np: ! @ # $ % $ & * ( )
   */
    sp=st+1;
    return s.substr(st,1);
  }
  if(my_isalpha(s[ix])||s[ix]=='_'){
    while(my_isalnum(s[ix])||s[ix]=='_'&&ix<sz)ix++;
    sp=ix;
    return s.substr(st,sp-st);
  }
  // nie odwiedzono bloku po wyøej czyli na pierwszym miejscu jest liczba lub '.'
  if(isdigit(s[ix])){
    while(isdigit(s[ix])&&ix<sz)ix++;
    if(ix>=sz){
      sp=ix;
      return s.substr(st,sp-st);
    }
    if((s[ix]=='e'||s[ix]=='E')&&(s[ix+1]=='+'||s[ix+1]=='-')&&isdigit(s[ix+2])){//wyklucza 123e+123
    }else{
      if(my_isalpha(s[ix])||s[ix]=='_'){
        while(my_isalnum(s[ix])||s[ix]=='_'&& ix<sz)ix++;
        if(ix>=sp||isspace(s[ix])||ispunct(s[ix])){
          sp=ix;
          return s.substr(st,sp-st);
        }
      }
    }
    if(isspace(s[ix])){
      sp=ix;
      return s.substr(st,sp-st);
    }
    if(ispunct(s[ix])&&s[ix]!='.'){
      sp=ix;
      return s.substr(st,sp-st);
    }
  }
  sp=ix;
    // Jeøeli przeskoczono po ciπgu liczb to te wartoúci majπ rÛønπ wartoúÊ.
  if(s[ix]=='.'){
  /*
   * Kropka moøe wystπpiÊ po ciπgu liczb lub jako pierwszy znak w tokenie (ix==st).
   * Jeøeli po '.' nie ma liczby||e||E to koniec na pozycji sp
   */
    ix++;
    while(isdigit(s[ix])&&ix<sz)ix++;
    if(sp+1==ix){
    /*
     * Potraktowanie znakÛw jako liczb nie posune≥o nas do przodu a po kropce tylko one mog≥y kontynuowaÊ
     * token ktÛry zaczπ≥ siÍ na pozycji st.
     * Kropka jest tokenem gdy s[st]=='.' w przeciwnym wypadku kropka ogranicza token.
     */
      if(sp==st)
        sp=ix;
      return s.substr(st,sp-st);
    }
  }
  if(sp!=ix){
  /*
   * By≥a kropka a w bloku obs≥ugi kropki odnaleziono liczby.
   * Gdy po liczbach spacja to np: 123.456
   * Gdy po liczbach interpujnct ale nie kropka i nie podkreúlenie to token koÒczy siÍ przed sp
   */
    if(isspace(s[ix])){//ta spacja moøe pojawiÊ siÍ po 123.
      sp=ix;
      return s.substr(st,sp-st);
    }
    if(s[ix]=='.'||s[ix]=='_'){
      return s.substr(st,sp-st);
    }
    if(s[ix]!='e'&&s[ix]!='E'){
      sp=ix;
      return s.substr(st,sp-st);
    }
  }
  if((s[ix]=='e'||s[ix]=='E')&&(s[ix+1]=='+'||s[ix+1]=='-')&&isdigit(s[ix+2])){
    ix+=2;
    if(!isdigit(s[ix])){
      if(sp==st)
       sp=st+1;
      return s.substr(st,sp-st);
    }
    while(isdigit(s[ix])&&ix<sz)ix++;
    sp=ix;
    return s.substr(st,sp-st);
  }else{
    if(sp==st)
     sp=st+1;
    return s.substr(st,sp-st);
  }

}

//==============================================================================
string old::Transfer(string &s_,size_t st_,size_t sp_)
//==============================================================================
{
  string s;
  if(st_>=s_.size())
    return "";
  if(sp_>=s_.size()){
    sp_==s_.size()-1;
    s=s_.substr(st_);
    s_.erase(st_);
  }else{
    s=s_.substr(st_,sp_-st_+1);
    s_.erase(st_,sp_-st_+1);
  }
  return s;
}

//==============================================================================
void old::my_toupper(string &s_)
//==============================================================================
{
  for(size_t i=0,sz=s_.size();i<sz;i++)
    s_[i]=static_cast<char>(my_toupper(s_[i]));
}

//==============================================================================
string old::Transfer(string &s_,size_t st_,char c_)
//==============================================================================
{
  string s;

  if(st_>=s_.size())
    return "";
  size_t sp=s_.find(c_,st_);
  if(sp==string::npos)
    return "";
  s=s_.substr(st_,sp-st_);
  s_.erase(st_,sp-st_+1);
  return s;
}

//==============================================================================
string old::Transfer(string &s_,char c_,size_t sp_)
//==============================================================================
{
  string s;
  size_t st;
  if(sp_>=s_.size())
    sp_=s_.size()-1;
  st=s_.find(c_);
  if(st>sp_ || st==string::npos)
    return "";
  s=s_.substr(st+1,sp_-st);
  s_.erase(st,(sp_-st)+1);
  return s;
}

//##############################################################################
//      CLASS Expr
//##############################################################################

//==============================================================================
err_t old::TExpr::Correct()
//==============================================================================
{
  size_t naw=size_m;
    // zmienna jest ustawiona na indeks nastÍpnego znaku po obecnie przetwarzanym gdy wystπpienie tam
    // (lub po ciπgu znakÛw bia≥ych) nawiasu '(' wymusza wstawienie operatora mnoøenia '*'
  size_t op=size_m;
    // Jeøeli op!=size_m to systπpienie operatora "+" lub "-" na pozycji op musi byÊ zastπione
    // litera≥ami odpowiednio : "___op__plus___" lub "___op__minus___". Wykonuje siÍ to dlatego øe
    // kaødy kolejny operator w ciπgu jest opratorem jednoargumentowym a to musi byÊ odpowiednio oznaczone
  ix=0;

  DelSpaceRight(infix);
  while(isspace(infix[ix]) && ix<infix.size())ix++;
  if(IsOp()){
  /*
   * Na wypadek gdyby jako pierwszy element ca≥ego wyraøenia pojawi≥ siÍ operator minus.
   * Ustawienie op na wartoúÊ !size_m informuje øe na tej pozycji jest kolejny operator czyli operator
   * jednoargumetowy. DziÍki tej modyfikacji wewnπtrz pÍtli g≥Ûwnej metody obrana zostanie trasa modyfikacji
   * operatora jednoargumentowego.
   */
    if(infix[ix]=='-' || infix[ix]=='+'){
      op=ix;
    }else
      return ERR_BAD_VALUE;
  }

  while(ix<infix.size()){
    while(isspace(infix[ix]) && ix<infix.size())ix++;
    if(IsOp()){
      naw=size_m;
        // jeøeli wystπpi≥ operator to nie ma obawy o z≥π budowÍ nawiasÛw. Jeøeli by≥o ) to teraz jest
        // np )* lub )+ co daje pewnoúÊ øe przynajmniej na razie nie wystπpi )(
      if(op==size_m){
      /*
       * Znaleziono opeator ale jest to pierwszy operator w cyklu i nie wiadomo czy wystÍpuje
       * jakiú minus zaraz po tym znaku. PrzesÛwamy siÍ na nastÍpny znak i zaznaczamy øe tam moøe byÊ
       * drugi operator.
       */
        op= ++ix;
        while(my_isalpha(infix[ix]) && ix<infix.size())ix++;
      }else{
      /*
       * Znaleziono operator ktÛry jest drugim w kolejnoúci.
       */
        if(infix[ix]=='-'){
          infix.replace(ix,1," ___op__minus___ ");
          ix+=17;//dlugoúÊ tego ^ napisu
        }else if(infix[ix]=='+'){
          infix.replace(ix,1," ");
          ix++;
        }else{
          return ERR_BAD_VALUE;
        }
        op=ix;
          // Teraz wstawiony operator ___op__... jest tym ktÛry "rzuca" podejøenie na nastÍpny element
          // wyraøenia dlatego nie moøna uznaÊ øe skoro skoorygowano budowÍ operatora jedno arumentowego
          // juø jest wszystko w potrzπdku. Moøe zdarzyÊ siÍ coú takiego ..*+-()
      }
    }else if(infix[ix]==')'){
    /*
     * Znaleziono zamkniÍty nawias ale nie wiadomo czy wystÍpuje jakiú otwierajπcy nawias zaraz po nim czy
     * jest tam operator. PrzesÛwamy siÍ na nastÍpny znak i zaznaczamy øe tam moøe byÊ otwierajπcy nawias.
     * Inaczej rzecz ujmujπc w≥πczamy alarm na wypadek wystπienia znaku "("
     */
      naw= ++ix;
    }else if(infix[ix]=='('){
    /*
     * Znaleziono nawias ktÛry jest otwierajπcy. Jeøeli jest to kolejny nawias otwierajπcy lub po
     * operatorze to wszystko jest ok.
     */
      if(naw!=size_m){
      /*
       * O! Nie znaleziono øadnego operatora pomiÍdzy parπ nawiasÛw )( lub litera≥em a nawiasem np 2(.
       * Inaczej : nie znaleziono øadnego operatora przed "(". Naleø wyczuliÊ uwagÍ na moøliwoúÊ wstawienia
       * operaora jednoargumentowego po otwrtym nawiasie co jest ca≥kowicie poprawne dla "+" i "-"
       */
        infix.insert(ix,"*");
        naw=size_m;
        ix++;
          // przesuwajπc siÍ o jednπ pozycjÍ trafiamy na ten sam nawias "(" co zbliø nas do zapÍtlenia,
          // jednak po tym bloku wystÍpuje ponownie operacja zwiekszania ix ktÛra jest wykonywana zawsze
          // po znalezieniu "("
      }
      op= ++ix;
        // Ta operacja przypisania wykonywana po kaødym odnalezieniu "(" poniewaø dopuszczalna jest
        // konstrukcja typu (-(...)...
    }else{
    /*
     * Na tej pozycji nie ma : operatora, ")" ani "(".
     * Jest litera≥ bÍdπcy liczbπ lub nazwπ zmiennej. Przed tym litera≥em musi byÊ operator lub "("
     * czyli naw != size_m. Jeøeli naw!=size_m wstawiÊ "*" i przejúÊ na nastÍpny znak po literale przed
     * ktÛrym wstawiono "*". Wy≥πczamy op. Nie wy≥πczamy naw poniewaø moøliwa jest konstrukcja :
     * ") liczba (" ktÛrπ musimy zamieniÊ na ")*liczba*("
     */
      if(naw!=size_m){
      /*
       * Znaleziony znak jest pierwszym po ")" (spacje ominiÍto) poniewaø nie jest to operator ani ')'
       * naleøy wstawiÊ '*'
       * np ...)3+2 -> ...)*3+2
       * przypadek:  ...)(2*...  -> ...)*(2*
       * obs≥ugoiwany jest przez warunek  infix[ix]=='('
       */
        infix.insert(ix,"*");
        ix++; // powrÛt na poczπtek odczytanego litera≥u.
        Token(infix,ix,ix);
        naw=ix;
        op=size_m;
      }else{
        Token(infix,ix,ix);
        op=size_m;
        naw=ix;
      }
    }
  }
  return OK;
}

//==============================================================================
err_t old::TExpr::d_Calculate(ms_sd *def_,double &d_val_)
//==============================================================================
{//01-04-27;01-04-11
  size_t ix=0;
  size_t st;
  size_t sp=infix.size()-1;
  d_val_=0;
  def=def_;

  while(isspace(infix[ix]))
    if(++ix>sp)  // znak o indexie sp teø jest brany pod uwagÍ
      return ERR_NOT_VALUE;
  st=ix;
  ix=sp;
  while(isspace(infix[ix]))
    if(--ix<st)
      return ERR_NOT_VALUE;

  return expr(d_val_);
};

//==============================================================================
err_t old::TExpr::f_Calculate(ms_sd *def_,float &f_val_)
//==============================================================================
{//01-05-05
  double d=0.0;

  err_t err=d_Calculate(def_,d);
  if(err!=OK)
    return err;

  if(numeric_limits<float>::min()<d && numeric_limits<float>::max()>d){
    f_val_=d;
    return OK;
  }else{
    return ERR_RANGE;
  }
}

//==============================================================================
err_t old::TExpr::i_Calculate(ms_sd *def_,int &i_val_)
//==============================================================================
{//01-05-05
  double d=0.0;

  err_t err=d_Calculate(def_,d);
  if(err!=OK)
    return err;
  if(numeric_limits<int>::min()<d && numeric_limits<int>::max()>d){
    i_val_=d;
    return OK;
  }else{
    return ERR_RANGE;
  }
//  return ERR_NULLFU;
};

//==============================================================================
err_t old::TExpr::expr(double &d_)
//==============================================================================
{//01-05-04;01-11-28
  sts_t stos;
  std_t tmp;
  double d=0.0;
  string token;
  err_t err;
  size_t tokst=0,toksp=0;

  if(Nul(infix))
    return OK;
  if((err=Correct())!=OK)
    return err;
  ix=0;
  stos.push("(");
  infix+=")";

  while(!stos.empty()){
  /*
   * Przebudowa na zapis przyrostkowy (notacja polska)
   */
    tokst=ix;
    token=Token(infix,tokst,toksp);
    ix=toksp;
    if(IsOp(token)){
      while(OP12(stos.top(),token)){
        postfix.push_back(stos.top());
        stos.pop();
      }
      stos.push(token);
    }else if(token[0]=='('){
      stos.push(token);
    }else if(token[0]==')'){
      while(stos.top()!="("){
        postfix.push_back(stos.top());
        stos.pop();//usuwanie operatora
      };
      stos.pop();//usuwanie nawiasu "("
    }else{
      postfix.push_back(token);
    }
  };

  long llv,lpv;
  double dlv=0.0,dpv=0.0;

  for(vs_t::iterator vs_it=postfix.begin();vs_it!=postfix.end();vs_it++){
    token= *vs_it;
    if(token[0]=='*'){
      dpv=tmp.top();tmp.pop();
      dlv=tmp.top();tmp.pop();
      tmp.push(dlv * dpv);
    }else if(token[0]=='/'){
      dpv=tmp.top();tmp.pop();
      dlv=tmp.top();tmp.pop();
      if(dpv==0)
        return ERR_DIV_0;
      tmp.push(dlv / dpv);
    }else if(token[0]=='+'){
      dpv=tmp.top();tmp.pop();
      dlv=tmp.top();tmp.pop();
      tmp.push(dlv + dpv);
    }else if(token[0]=='-'){
      dpv=tmp.top();tmp.pop();
      dlv=tmp.top();tmp.pop();
      tmp.push(dlv - dpv);
    }else if(token[0]=='^'){
      dpv=tmp.top();tmp.pop();
      dlv=tmp.top();tmp.pop();
      tmp.push(pow(dlv,dpv));
    }else if(csu(token,"AND")){
      dpv=tmp.top();tmp.pop();
      dlv=tmp.top();tmp.pop();
      if(!InLong(dlv) || !InLong(dpv))
        return ERR_MATHOP;
      llv=static_cast<long>(dlv);
      lpv=static_cast<long>(dpv);
      llv &= lpv;
      tmp.push(llv);
    }else if(csu(token,"OR")){
      dpv=tmp.top();tmp.pop();
      dlv=tmp.top();tmp.pop();
      if(!InLong(dlv) || !InLong(dpv))
        return ERR_MATHOP;
      llv=static_cast<long>(dlv);
      lpv=static_cast<long>(dpv);
      llv |= lpv;
      tmp.push(llv);
    }else if(csu(token,"XOR")){
      dpv=tmp.top();tmp.pop();
      dlv=tmp.top();tmp.pop();
      if(!InLong(dlv) || !InLong(dpv))
        return ERR_MATHOP;
      llv=static_cast<long>(dlv);
      lpv=static_cast<long>(dpv);
      llv ^= lpv;
      tmp.push(llv);
    }else if(csu(token,"NOT")){
      dpv=tmp.top();tmp.pop();
      if(InLong(dpv))
        return ERR_MATHOP;
      lpv=static_cast<long>(dpv<0 ? dpv-0.5 : dpv+0.5);
      dpv= ~lpv;
      tmp.push(dpv);
    }else if(cs(token,"___op__minus___")){
      dpv=tmp.top();tmp.pop();
      dpv*= -1;
      tmp.push(dpv);
    }else if(GetDouble(token,d,SIGNED)==OK){
    /*
     * Liczby z tablicy postfix trafiajπ na stos w takiej kolejnoúci jak sπ pobierane
     * a pobierane sπ przez operatory matematyczne odczytywane z tablicy postfix.
     */
      tmp.push(d);
    }else{
    /*
     * Tu musi byÊ liczba lub litera≥ definiujπcy jakπú wartoúÊ na mapie ms_sd_EQU.
     * Jeøeli to podejúcie siÍ nie powiedzie naleøy zwrÛciÊ b≥πd.
     */
     ms_sd::iterator ms_sd_it;
      for(ms_sd_it=def->begin();ms_sd_it!=def->end();++ms_sd_it){
        if(cs(token,ms_sd_it->first)){
          if(ms_sd_it->second.first.size()!=0){
            return ERR_CALC_LATER;
          }else{
            d=ms_sd_it->second.second;
            break;
          }
        }
      }
      if(ms_sd_it==def->end())
        return ERR_BAD_VALUE;
      tmp.push(d);
    }
  }
  d_=tmp.top();
  tmp.pop();
  return OK;
};

//==============================================================================
bool old::TExpr::InLong(double d_)
//==============================================================================
{
  long d=static_cast<long>(d_<0 ? d_-0.5 : d_+0.5);
  if( (d_-d) != 0)
    return false;
  if(d_<0){
    if(numeric_limits<long>::min()>d_){
       return false;
    }
  }else{
    if(numeric_limits<long>::max()<d_){
      return false;
    }
  }
  return true;
}

//==============================================================================
bool old::TExpr::IsOp(const string &op)
//==============================================================================
{
  if(op=="+"||op=="-"||op=="*"||op=="^"||op=="/"||
     csu(op,"AND")||csu(op,"OR")||csu(op,"XOR")||csu(op,"NOT")||
        cs(op,"___op__minus___"))
    return true;
  return false;
}

//==============================================================================
bool old::TExpr::IsOp()
//==============================================================================
{//01-11-10
  switch(infix[ix]){
    case '+': case '-': case '*': case '/': case '^': return true;
  }
  if(Find(infix,"and",ix,true)==ix || Find(infix,"or",ix,true)==ix ||
     Find(infix,"xor",ix,true)==ix || Find(infix,"not",ix,true)==ix||
     Find(infix,"___op__minus___",ix,true)==ix){
    return true;
  }
  return false;
}

//==============================================================================
bool old::TExpr::OP12(const string &op1,const string &op2)
//==============================================================================
{//01-09-26;01-11-13
  if(IsOp(op1) && !IsOp(op2))
    return true;
  if(!IsOp(op1))
    return false;
  return PO(op1) >= PO(op2) ? true : false;
}

//==============================================================================
size_t old::TExpr::PO(const string &op)
//==============================================================================
{//01-11-13
  if(op=="+" || op=="-"){
    return 12;
  }else if(op=="*" || op=="/"){
    return 13;
  }else if(op=="^"){
    return 14;
  }else if(csu(op,"AND")){
    return 8;
  }else if(csu(op,"XOR")){
    return 7;
  }else if(csu(op,"OR")){
    return 6;
  }else if(csu(op,"NOT")){
    return 15;
  }else if(cs(op,"___op__minus___")){
    return 15;
  }else{
    return 0;
  }
}

//==============================================================================
err_t old::d_Calculate(const string &s_, ms_sd *def_,double &d_val_)
//==============================================================================
{
  TExpr expr(s_);
  return expr.d_Calculate(def_,d_val_);
};

//==============================================================================
err_t old::f_Calculate(const string &s_, ms_sd *def_,float &f_val_){
//==============================================================================
  TExpr expr(s_);
  return expr.f_Calculate(def_,f_val_);
};

//==============================================================================
err_t old::i_Calculate(const string &s_, ms_sd *def_,int &i_val_){
//==============================================================================
  TExpr expr(s_);
  return expr.i_Calculate(def_,i_val_);
};

//##############################################################################
//      CLASS CFG
//##############################################################################

//==============================================================================
err_t old::CFG::Get(const string &key_,string &val_)
//==============================================================================
{
  size_t ix;
  size_t st;
  size_t sz=scrypt.size();
  if((st=Find(scrypt,key_,0,true))==size_m)
    return ERR_NOT_FIND;

  /*
   * Po odnalezieniu nazwy parametru szukamy znaku bia≥ego lub '='
   * poz naku bia≥ym musi byÊ '='. Po '=' mogπ byÊ znaki bia≥e a po niech musi byÊ
   * napis bÍdπcy tekstowπ reprezentacjπ liczby int.
   * Dalej moøe byÊ koniec wiersza poprzedzonego bia≥ymi znakami. Przed koÒcem wiersz
   * moøe wystπpiÊ komentaø czyli : " spacje # komentaø spacje \n"
   */
    ix=st;
    while((my_isalnum(scrypt[ix])||scrypt[ix]=='_') && ix<sz)ix++;
    while(isspace(scrypt[ix]))ix++;
    if(scrypt[ix++]!='=')
      return old::ERR_BAD_DEF;
    while(isspace(scrypt[ix]))ix++;
    st=ix;
    while((my_isalnum(scrypt[ix])||scrypt[ix]=='_') && (ix<sz && scrypt[ix]!='#'))ix++;
    val_=scrypt.substr(st,ix-st);
  return OK;
};

//==============================================================================
err_t old::CFG::Get(const string &key_,int &val_)
//==============================================================================
{
  size_t ix;
  size_t st;
  size_t sz=scrypt.size();
  string s_val;
  err_t err;
  if((st=Find(scrypt,key_,0,true))==size_m)
    return ERR_NOT_FIND;

  /*
   * Po odnalezieniu nazwy parametru szukamy znaku bia≥ego lub '='
   * poz naku bia≥ym musi byÊ '='. Po '=' mogπ byÊ znaki bia≥e a po niech musi byÊ
   * napis bÍdπcy tekstowπ reprezentacjπ liczby int.
   * Dalej moøe byÊ koniec wiersza poprzedzonego bia≥ymi znakami. Przed koÒcem wiersz
   * moøe wystπpiÊ komentaø czyli : " spacje # komentaø spacje \n"
   */
    ix=st;
    while((my_isalnum(scrypt[ix])||scrypt[ix]=='_') && ix<sz)ix++;
    while(isspace(scrypt[ix]))ix++;
    if(scrypt[ix++]!='=')
      return old::ERR_BAD_DEF;
    while(isspace(scrypt[ix]))ix++;
    st=ix;
    while((my_isalnum(scrypt[ix])||scrypt[ix]=='_') && (ix<sz && scrypt[ix]!='#'))ix++;
    s_val=scrypt.substr(st,ix-st);
    if((err=GetInt(s_val,val_,SIGNED))!=OK)
      return err;
  return OK;
};

//==============================================================================
err_t old::CFG::Read()
//==============================================================================
{
  return FileRead(scrypt,path);
};

//==============================================================================
err_t old::CFG::Save()
//==============================================================================
{
  return FileRead(scrypt,path);
};

//==============================================================================
void old::CFG::Set(const string &key_,const string &val_)
//==============================================================================
{
  (key_);
  (val_);
};

//==============================================================================
void old::CFG::Set(const string &key_,int val_)
//==============================================================================
{
  (key_);
  (val_);
};
