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
//     return "nie rozpoznany b³¹d";
//   case ERR_SIGNED:
//     return "Liczba otrzymana w wyniku przetwarzania posiada znak gdy mia³a byæ bez znaku";
   case old::ERR_RANGE:
     return "Zmienna poza zakresem.";
//   case ERR_REDEF:
//     return "Pewna sta³a zmieni³a swoj¹ wartoœæ";
   case old::ERR_NOT_FIND:
     return "Nie znaleziono oczekiwanej wartoœci";
//   case ERR_BAD_VALUE:
//     return  "Wartoœæ któr¹ przekazano do dalszego przetwarzania jest nie w³aœciwa, ma z³¹ strukture.";
//   case ERR_NOT_VALUE:
//     return "Zmienna choæ posiada poprawn¹ strukturê nie pozwala okreœliæ wartoœci np pusty napis";
//   case ERR_BAD_DEF:
//     return "Wyra¿enie definiuj¹ce wartoœæ jest nie poprawne.";
//   case ERR_NULLFU:
//     return "Funkcja która zosta³a zdefiniowana ale jedyne co robi to zwraca wartoœæ";
   case old::ERR_MATHOP:
     return "B³¹d powsta³y podczas próby wykonania podstawowej operacji matemetycznej";
//   case ERR_CALC_LATER:
//     return "Wartoœæ przekazana do obliczenia jest wyra¿eniem którego sk³adowe jeszcze nie s¹ wysnaczone";
   case old::ERR_THREAD_STOP:
    return "Awaryjne zakoñczenie w¹tku. W¹tek przerwano mimo trwania pracy (obliczeñ)";
  }
  return "nie zdefionawana wartoœæ zmiennej err";
};



