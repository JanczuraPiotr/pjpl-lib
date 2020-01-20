#include "gold.h"


//==============================================================================
CWyj::CWyj(size_t nr_,size_t par_,std::string kom_)
{
  w.key=nr_;
  w.first=par_;
  w.second=kom_;
}
//==============================================================================
eNFun::eNFun(const string &funkcja_,const string &plik_,size_t wiersz_)
{
  funkcja=funkcja_;
  plik=plik_;
  wiersz=wiersz_;
}
//==============================================================================
string eNFun::Co()
{
  int dec,sig;
  string s;
  s=ecvt(wiersz,30,&dec,&sig);
  return string(funkcja+" "+plik+" "+s);
}



//=============================================================================
string GetErrStr(int err_)
//=============================================================================
{//01-05-03
  switch(err_){
   case OK:
     return "Wszystko OK!";
//   case ERR_UNKN:
//     return "nie rozpoznany b��d";
//   case ERR_SIGNED:
//     return "Liczba otrzymana w wyniku przetwarzania posiada znak gdy mia�a by� bez znaku";
   case old::ERR_RANGE:
     return "Zmienna poza zakresem.";
//   case ERR_REDEF:
//     return "Pewna sta�a zmieni�a swoj� warto��";
   case old::ERR_NOT_FIND:
     return "Nie znaleziono oczekiwanej warto�ci";
//   case ERR_BAD_VALUE:
//     return  "Warto�� kt�r� przekazano do dalszego przetwarzania jest nie w�a�ciwa, ma z�� strukture.";
//   case ERR_NOT_VALUE:
//     return "Zmienna cho� posiada poprawn� struktur� nie pozwala okre�li� warto�ci np pusty napis";
//   case ERR_BAD_DEF:
//     return "Wyra�enie definiuj�ce warto�� jest nie poprawne.";
//   case ERR_NULLFU:
//     return "Funkcja kt�ra zosta�a zdefiniowana ale jedyne co robi to zwraca warto��";
   case old::ERR_MATHOP:
     return "B��d powsta�y podczas pr�by wykonania podstawowej operacji matemetycznej";
//   case ERR_CALC_LATER:
//     return "Warto�� przekazana do obliczenia jest wyra�eniem kt�rego sk�adowe jeszcze nie s� wysnaczone";
   case old::ERR_THREAD_STOP:
    return "Awaryjne zako�czenie w�tku. W�tek przerwano mimo trwania pracy (oblicze�)";
  }
  return "nie zdefionawana warto�� zmiennej err";
};



