//---------------------------------------------------------------------------
#ifndef PRZEBIEG_H
#define PRZEBIEG_H

//---------------------------------------------------------------------------
#include <string>

#define MARGINES_UCHWYTU        2
#define DLUGOSC_OPISU           7
#define DLUGOSC_OPISU_SIATKI    7
#define MAX_SIATKA_HOR_COUNT    11
#define MAX_SIATKA_VER_COUNT    11
#define MAX_PRZEDZ_HOR_COUNT    MAX_SIATKA_HOR_COUNT-1
#define MAX_PRZEDZ_VER_COUNT    MAX_SIATKA_VER_COUNT-1

class CPrzebieg
{
protected:
  int i_szerokosc,i_wysokosc,
        // Obie warto�ci odnosz� si� do ca�ego okna oscyloskopu
      i_szerokosc_old,i_wysokosc_old,
      i_s_zaczep_x,
        // wsp�rz�dna rodzica zawieraj�ca lewy g�rny r�g okna sygna�u
      i_s_zaczep_y,
        // wsp�rz�dna rodzica zawieraj�ca prawy g�rny r�g okna sygna�u
      i_s_szerokosc,i_s_wysokosc,
        // Rozmiar wewn�trznego ekranu sygnalu. Je�eli ekran nie wy�wietla
        // informacji tekstowych na marginesie to warto�ci te mog� pokrywa� si� z ca�ym obszarem ekranu
      i_s_koniec_x,i_s_koniec_y,
      i_kursor_l,i_kursor_p,i_kursor_g,i_kursor_d,i_kursor_g_p,i_kursor_d_p,
        // wsp�rz�dne kursor�w na ekranie sygna�u
      i_os_x,i_os_x_p,i_os_y,
        // �rodek uk�adu wsp�rz�dnych na ekranie sygna�u
      i_skala_x,i_skala_y;
  //*?!*/   marg_l,marg_p,marg_g,marg_d;
        // Rozmiary margines�w przeznaczonych na opisy. Pole do wy�wietlania
        // pozostanie wykrojone z szeroko�ci i wysoko�ci ekranu przez marginesy.
  bool b_kursor,b_osie,b_siatka,b_opis,b_ciagly,
         //informuj� czy rysowa� dany element
       b_kursor_l_move,b_kursor_p_move,b_kursor_g_move,b_kursor_d_move,
       b_os_x_move,b_os_y_move,b_przebieg_move,b_unknown_move,b_mouse_down,
       b_zoom_auto;//je�eli "prawda" dostosuje nades�ane dane by wype�ni�y ekran

  float f_delta_t,      // aktualny przyrost czasu na pr�bk�
        f_delta_tinc,   // warto�� o jak� mo�e zmienia� si� delta_t
        f_delta_tmin,   // najmniejszy mo�liwy do ustawienia przyrost czasu na pr�bk�
        f_delta_tmax,   // najwiekszy mo�liwy do ustawienia przyrost czasu na pr�bk�
        f_delta_v,      // przyrost napi�cia na pr�bke
        f_delta_vinc,   // warto�� o jak� mo�e zmienia� si� delta_v
        f_delta_vmin,   // najmniejszy mo�liwy do ustawienia przyrost napiecia na pr�bk�
        f_delta_vmax,   // najwiekszy mo�liwy do ustawienia przyrost napiecia na pr�bk�
        f_skala_v,
        f_skala_t,
        f_T,            // okres sygna�u
        f_vmax,         // zakres napi��
        f_vmin,//-"-
        f_f,            // cz�stotliwo�� sygna�u f=1/T
        f_th,           // kursor na wi�kszej czasowej
        f_tl,           // kursor na mniejszej czasowej
        f_vh,           // kursor na wy�szym napi�ciu
        f_vl,           // kursor na mniejszym napi�ciu
        f_tlth,         // przyrost czasu pomi�dzy kursorami
        f_vlvh,         // przyrost napiecia pomiedzy kursorami
        f_s_os_x,f_s_os_y,//wsp�rz�dne �rodka uk�adu wsp�rz�dnych na sygnale
        f_czulosc,
        f_podstawa;

  //Wsp�rz�dne opis�w
  int   i_T_x,      i_T_y,      i_lbl_T_x,  i_lbl_T_y,
        i_f_x,      i_f_y,      i_lbl_f_x,  i_lbl_f_y,
        i_dt_x,     i_dt_y,     i_lbl_dt_x, i_lbl_dt_y,
        i_dv_x,     i_dv_y,     i_lbl_dv_x, i_lbl_dv_y,
        i_th_x,     i_th_y,     i_lbl_th_x, i_lbl_th_y,
        i_tl_x,     i_tl_y,     i_lbl_tl_x, i_lbl_tl_y,
        i_vh_x,     i_vh_y,     i_lbl_vh_x, i_lbl_vh_y,
        i_vl_x,     i_vl_y,     i_lbl_vl_x, i_lbl_vl_y,
        i_tlth_x,   i_tlth_y,   i_lbl_tlth_x,   i_lbl_tlth_y,
        i_vlvh_x,   i_vlvh_y,   i_lbl_vlvh_x,   i_lbl_vlvh_y,
        i_jednostka_T_x,        i_jednostka_T_y,
        i_jednostka_v_x,        i_jednostka_v_y,
        i_jednostka_f_x,        i_jednostka_f_y;

  char  ac_T[DLUGOSC_OPISU+1],          ac_f[DLUGOSC_OPISU+1],
        ac_dt[DLUGOSC_OPISU+1],         ac_dv[DLUGOSC_OPISU+1],
        ac_th[DLUGOSC_OPISU+1],         ac_tl[DLUGOSC_OPISU+1],
        ac_vh[DLUGOSC_OPISU+1],         ac_vl[DLUGOSC_OPISU+1],
        ac_tlth[DLUGOSC_OPISU+1],       ac_vlvh[DLUGOSC_OPISU+1],
        ac_jednostka_T[3],          ac_jednostka_v[3],
        ac_jednostka_f[4];

  int   i_siatka_dx,            // odst�p pomi�dzy pionowymi liniami siatki
        i_siatka_dy,            // odst�p pomi�dzy poziomymi liniami siatki
        i_siatka_x,             // wsp�rz�dne pierwszej piopnowej linii siatki
        i_siatka_y,             // wsp�rzedne pierwszej poziomej linii siatki
        i_siatka_hor_count,     // liczba linii w kierunku poziomym - lini pionowych
        i_siatka_ver_count,     // liczba linii w kierunku pionowym - linii poziomych
        i_opis_hor_y,           // wsp�rz�dna x dla opis�w poziomych lini siatki
        i_opis_ver_x,           // wsp�rz�dna y dla opis�w pionowych lini siatki
        i_opis_hor_x[MAX_SIATKA_HOR_COUNT],// warto�ci dla wsp�rz�dnej y opis�w poziomych linii
        i_opis_ver_y[MAX_SIATKA_VER_COUNT],// warto�ci dla wsp�rz�dnej x opis�w pionowych linii
        i_przedz_hor_count,     // liczba pe�nych przedzia��w w kierunku pionowym (odst�p pomi�dzy liniami)
        i_przedz_ver_count,     // liczba pe�nych przedzia��w w kierunku poziomym (odst�p pomi�dzy liniami)
        i_index_hor,            // d o przemieszczania si� w poziomie w czasie rysowania poziomych linii
        i_index_ver,            // do przemieszczania si� w pionie w czasie rysowania pionowych linii
        i_index_os_y;       // index dla tabeli i_opis_hor_x elementu zawieraj�cego warto�� 0
  float f_wartosc_hor[MAX_SIATKA_HOR_COUNT],
        f_wartosc_ver[MAX_SIATKA_VER_COUNT];

  char  ac_opis_hor[MAX_SIATKA_HOR_COUNT][DLUGOSC_OPISU_SIATKI+1],// pewna liczba napis�w opisujacych parametry siatki
        ac_opis_ver[MAX_SIATKA_VER_COUNT][DLUGOSC_OPISU_SIATKI+1];// wska�nik pomocniczy

  int i_przebieg_color,i_os_color,i_siatka_color,i_kursor_color,i_tlo_color,i_rysowanie_color,
      i_przebieg_styl,i_os_styl,i_siatka_styl,i_kursor_styl;
public:
  CPrzebieg(CSignalBuffor *_Source,int _i_in_s,
            int _i_szerokosc,int _i_wysokosc,
            int _i_s_zaczep_x=0, int _i_s_zaczep_y=0,int _i_s_szerokosc=0,int _i_s_wysokosc=0);
    //_szerokosc i _wysokosc ustawiaj� rozmiar ca�ego okna ekranu _s..._... oke�laj� po�o�enie ekranu
    //wy�wietlaj�cego sygna�
  #ifdef WIN32
  //virtual __fastcall ~TPrzebieg(){};
  #else
  ~TPrzebieg();
  #endif
  void ReSetRozmiar(int _i_szerokosc,int _i_wysokosc);
    /*
    Dzia�nie:
      Zmienia rozmiar ekranu oscyloskopu nadaj�� mu rozmiary podane w wywo�aniu
    */
  void ReSet_f_podstawa(float _f_podstawa);
  void ReSet_f_delta_t(float _f_delta_t);//-
  void ReSet_f_czulosc(float _f_czulosc);
  float Get_f_delta_t(){/*1999-11-01*/return f_delta_t;};
  void ReSet_f_delta_tmin(float _delta_tmin);
  float Get_f_delta_tmin(){/*1999-11-26*/ return f_delta_tmin;};
  void ReSet_f_delta_tmax(float _delta_tmax);//-
  float Get_f_delta_tmax(){/*1999-11-26*/ return f_delta_tmax;};
  void ReSet_f_delta_v(float _delta_v);//-
  float Get_f_delta_v(){/*1999-11-01*/return f_delta_v;};
  void ReSet_f_delta_vmin(float _delta_vmin);//-
  float Get_f_delta_vmin(){/*1999-11-26*/ return f_delta_vmin;};
  void ReSet_f_delta_vmax(float _delta_vmax);//-
  float Get_f_delta_vmax(){/*1999-11-26*/ return f_delta_vmax;}
  void ReSet_f_T(float _f_T);//-
  float Get_f_T(){/*1999-11-01*/return f_T;};//-
  void ReSet_f_vmax(float _f_vmax);//-
  float Get_f_vmax(){/*1999-11-05*/return f_vmax;};
  void ReSet_f_vmin(float _f_vmin);//-
  float Get_f_vmin(){/*1999-11-06*/return f_vmin;};
  void ReSet_i_kursor_l(int _i_kursor_l);//-
  void Inc_i_kursor_l();//-
  void Dec_i_kursor_l();//-
  int Get_i_kursor_l(){/*1999-12-01*/return i_kursor_l;};
  void ReSet_i_kursor_p(int _i_kursor_p);//-
  void Inc_i_kursor_p();//-
  void Dec_i_kursor_p();//-
  int Get_i_kursor_p(){/*1999-12-01*/return i_kursor_p;};
  void ReSet_i_kursor_g(int _i_kursor_g_p);//-
  void Inc_i_kursor_g();//-
  void Dec_i_kursor_g();//-
  int Get_i_kursor_g(){/*1999-12-01*/return i_kursor_g_p;};
  void ReSet_i_kursor_d(int _i_kursor_d_p);//-
  void Inc_i_kursor_d();//-
  void Dec_i_kursor_d();//-
  int Get_i_kursor_d(){/*1999-12-01*/return i_kursor_d_p;};
  void ReSet_f_f(float _f_f);//-
  float Get_f_f(){/*1999-11-01*/return f_f;};
  void ReSet_f_th(float _f_th);//-
  float Get_f_th(){/*1999-11-01*/return f_th;};
  void ReSet_f_tl(float _tl);//-
  float Get_f_tl(){/*1999-11-01*/return f_tl;};
  void ReSet_f_vh(float _f_vh);//-
  float Get_f_vh(){/*1999-11-01*/return f_vh;};
  void ReSet_f_vl(float _f_vl);//-
  float Get_f_vl(){/*1999-11-01*/return f_vl;};
  float Get_f_vlvh(){/*1999-12-03*/return f_vlvh;};
  float Get_f_tlth(){/*1999-12-03*/return f_tlth;};
  void ReSet_i_os_x(int _i_os_x_p);//-
  int Get_i_os_x(){/*1999-11-01*/return i_os_x_p;};
  /*
   * Zwraca wsp�rz�dn� osi X we wsp�rz�dnych liczon� wewn�trz sygna�u (nie ekranowych wykorzystywanych
   * przez funkcjie rys�j�ce)
   */
  void ReSet_i_os_y(int _i_os_y);//-
  int Get_i_os_y(){/*1999-11-01*/return i_os_y;};//-
  void ReSet_i_siatka_dx(int _i_siatka_dx);//-
  int Get_i_siatka_dx(){/*1999-11-01*/return i_siatka_dx;};//-
  void ReSet_i_siatka_dy(int _i_siatka_dy);//-
  int Get_i_siatka_dy(){/*1999-11-01*/return i_siatka_dy;};//-
  void ReSetPolozenie(int _i_s_zaczep_x,int _i_s_zaczep_y,int _i_s_szerokosc,int _i_s_wysokosc);//-
  void ReSetZaczep(int _i_s_zaczep_x,int _i_s_zaczep_y);//-
  void ReSetSRozmiar(int _i_s_szerokosc,int _i_s_wysokosc);//-
  virtual void RysujEkran();
  /*
   * Wykonuje ostateczn� operacj� umieszczenia przebiegu na ekranie. Nie rysuje �adnego z element�w.
   * Kopiuje jedynie bufor z zapami�tanym wygl�dem przebiegu na ekran. Jest wywo�ywany przez aplikacj�
   * gdy wyst�pi konieczno�� od�wierzenia jego widoku oraz przez metod� OdswierzGrafike() tego obiektu
   * gdy zmienione zosta�y jakie� elementy.
   */

/*
**  Poni�sze metody odpowiedzialne s� za prze��czanie obiekty w stan
**  wy�wietlania lub nie odpowiednich element�w graficznych.
*/
  void Kursory();
  void Osie();
  void Siatka();
  void Opis();
  void Ciagly();

  void MouseDown(int _i_down_x,int _i_down_y);
  void MouseMove(int _i_dx,int _i_dy);
  void MouseUp();

protected:
  void MouseDownEkran(int _i_down_x,int _i_down_y);//-
  void MouseMoveEkran(int _i_dx,int _i_dy);//-
  void SetRozmiar(int _i_szerokosc,int _i_wysokosc);//-
  void Set_f_czulosc(float _f_czulosc);
  void Set_f_delta_t(float _f_delta_t);//-
  void Set_f_delta_tmin(float _f_delta_tmin);//-
  void Set_f_delta_tmax(float _f_delta_tmax);//-
  void Set_f_delta_v(float _f_delta_v);//-
  void Set_f_delta_vmin(float _f_delta_vmin);//-
  void Set_f_delta_vmax(float _f_delta_vmax);//-
  void Set_f_T(float _f_T);//-
  void Set_f_vmax(float _f_vmax);//-
  void Set_f_vmin(float _f_vmin);//-
  void Set_i_kursor_l(int _i_kursor_l);//-
  void Set_i_kursor_p(int _i_kursor_p);//-
  void Set_i_kursor_g(int _i_kursor_g);//-
  void Set_i_kursor_d(int _i_kursor_d);//-
  void Set_f_f(float _f_f);//-
  void Set_f_th(float _f_th);//-
  void Set_f_tl(float _f_tl);//-
  void Set_f_vh(float _f_vh);//-
  void Set_f_vl(float _f_Vl);//-
  void Set_i_os_x(int _i_os_x_p);//-
  void Set_i_os_y(int _i_os_y);//-
  void Set_i_siatka_dx(int _i_siatka_dx);//-
  void Set_i_siatka_dy(int _i_siatka_dy);//-
  void Set_f_podstawa(float _f_podstawa);
  void Set_i_OXY(int _i_osx=0,int _i_osy=0);
  void SetPolozenie(int _i_s_zaczep_x,int _i_s_zaczep_y,int _i_s_szerokosc,int _i_s_wysokosc);//-
  void SetZaczep(int _i_s_zaczep_x,int _i_s_zaczep_y);//-
  void SetSRozmiar(int _i_s_szerokosc,int _i_s_wysokosc);//-
  void PrzeliczSygnal();
  /*
   * Jest metod� wykonywan� po wprowadzeniu do obiektu nowych danych w metodzie NowyBuf() je�eli Ekran
   * wy�wietla przebieg wraz z kursorami itp. nale�y j� pokry� by oblicza�a warto�ci wyznaczane przez te
   * elementy. Metoda powinna zwraca� uwag� na zmienne BOOL odpowiadaj�ce za wy�wietlanie tych element�w
   * i oblicza� w�a�ciwe im dane tylko gdy s� te elementy rysowane
   */
  virtual void PrzeliczGrafike();
  // Wywo�ywana zawsze przy jakichkolwiek zmianach w rozmiarze lub wygl�dzie okna przez metody dokonuj�ce
  // tych zmian. Zadeklarowane poni�ej metody Przelicz...() wywo�ywane s� tylko w tej metodzie
  virtual void PrzeliczSiatke();
   // Przeliczy na punkty pomiarowe w przebiegu wsp�rz�dne x,y i dx,dy
  virtual void PrzeliczKursory();
  /*
   * Przeliczy na punkty pomiarowe w przebiegu ws�rz�dne kursor�w
   */
  virtual void PrzeliczPolozenie();
  /*
   * Prezeliczy wsp�rz�dne okna wewn�trznego w oknie g��wnym. B�dzie potrzebna gdy okno b�dzie posiada�o
   * zmienny rozmiar. Mo�e nic nie robi�.
   */
  virtual void PrzeliczOXY();
  /*
   * Przeliczy na punkty pomiarowe w przebiegu podzia�k� ok�adu
   */
  virtual void PrzeliczOkno();
  virtual void Przelicz_f();//-
  virtual void Przelicz_vsr();//-
  virtual void Przelicz_vsk();//-
/*
**poni�aze metody stanowi� tre�� metody Rysuj lecz s� puste nale�y wype�ni� te metody funkcjami rysuj�cymi
**odpowiednimi dla platformy na kt�r� implementowana jest ta klasa
*/

  virtual void Refresh(){OdswierzGrafike();};
  virtual void Czyszczenie();//obiekty graficzne na kt�rych rysowany jest przebieg
  virtual void OdswierzGrafike();
  virtual void RysujPrzebieg();
  virtual void RysujSiatke();
  virtual void RysujOpis();
  virtual void RysujKursory();
  virtual void RysujOsie();

};//class clPrzebieg


#endif
