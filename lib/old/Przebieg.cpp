//---------------------------------------------------------------------------
#pragma hdrstop
#include <math.h>
#include "przebieg.h"
#include "algorytmy.h"
//==============================================================================
CPrzebieg::CPrzebieg(CSignalBuffor *Source_,int i_in_s_,
                     int i_szerokosc_,int i_wysokosc_,
                     int i_s_zaczep_x_,int  i_s_zaczep_y_,int i_s_szerokosc_,int i_s_wysokosc_)
:CSignalTarget(Source_,i_in_s_)
//==============================================================================
{//1999-12-21
  b_kursor_l_move=  b_kursor_p_move=  b_kursor_g_move=
  b_kursor_d_move=  b_os_x_move=      b_os_y_move=
  b_przebieg_move=  false;
  b_unknown_move=b_mouse_down=false;
  b_zoom_auto=false;
  i_szerokosc_old=i_szerokosc;
  i_wysokosc_old=i_wysokosc;
  i_szerokosc=i_szerokosc_;
  i_wysokosc=i_wysokosc_;
  i_skala_x=i_skala_y=1;
  if(i_s_szerokosc_==0)
    i_s_szerokosc=i_szerokosc;
  else
    i_s_szerokosc=i_s_szerokosc_;
  if(i_s_wysokosc_==0)
    i_s_wysokosc=i_wysokosc_;
  else
    i_s_wysokosc=i_s_wysokosc_;
  i_os_x_p=i_s_wysokosc_/2;
  i_os_x=i_s_wysokosc_-1-i_os_x_p;
  i_os_y=0;
  i_s_zaczep_x=i_s_zaczep_x_;
  i_s_zaczep_y=i_s_zaczep_y_;
  SetZaczep(i_s_zaczep_x,i_s_zaczep_y);
  i_przedz_hor_count=MAX_PRZEDZ_HOR_COUNT; //
  i_przedz_ver_count=MAX_PRZEDZ_VER_COUNT; //
  i_siatka_hor_count=MAX_SIATKA_HOR_COUNT; //
  i_siatka_ver_count=MAX_SIATKA_VER_COUNT; //liczba linii w danym kierunku
  i_siatka_dx=i_s_szerokosc/i_przedz_hor_count;
  i_siatka_dy=i_s_wysokosc/i_przedz_ver_count;
  i_siatka_x=i_os_x%i_siatka_dx;
  i_siatka_y=i_os_y%i_siatka_dy;
  Set_f_delta_t(1);   Set_f_delta_tmin(1);   Set_f_delta_tmax(1);
  Set_f_delta_v(1);   Set_f_delta_vmin(1);   Set_f_delta_vmax(1);
  Set_f_T(f_delta_t*(i_s_szerokosc-1));
  Set_f_vmin(0);
  Set_f_vmax(f_delta_v*(i_s_wysokosc-1)+Get_f_vmin());
  Set_f_th(f_T);
  Set_f_tl(0);
  Set_f_vh(f_vmax);
  Set_f_vl(f_vmin);
  Set_i_kursor_l(0);
  Set_i_kursor_p(i_s_szerokosc);
  Set_i_kursor_g(i_s_wysokosc);
  Set_i_kursor_d(0);
  Set_f_delta_v(1);
  PrzeliczGrafike();
  //paf_buf_old=NULL;
  //i_buf_old_rozmiar=0;
  i_in_s=i_s_szerokosc;
  paf_in=new float[i_in_s];
  for(int i_in_i=0;i_in_i<i_in_s;i_in_i++)
   paf_in[i_in_i]=0;//po utworzeniu objekt rysuje sygna³ o wartoœci = 0
  b_kursor=b_osie=b_siatka=b_opis=b_ciagly=true;
  przebieg_styl=os_styl=siatka_styl=kursor_styl=psSolid;
  i_lbl_dt_x=i_szerokosc-230;           i_lbl_dt_y  =3;
  i_dt_x    =i_szerokosc-210;           i_dt_y      =3;
  i_lbl_dv_x=i_szerokosc-170;           i_lbl_dv_y  =3;
  i_dv_x    =i_szerokosc-150;           i_dt_y      =3;
  i_lbl_T_x =i_szerokosc-110;           i_lbl_T_y   =3;
  i_T_x     =i_szerokosc-100;           i_T_y       =3;
  i_lbl_f_x =i_szerokosc-60;            i_lbl_f_y   =3;
  i_f_x     =i_szerokosc-50;            i_f_y       =3;
  i_lbl_tl_x=i_szerokosc-190;           i_lbl_tl_y  =i_wysokosc-25;
  i_tl_x    =i_szerokosc-170;           i_tl_y      =i_wysokosc-25;
  i_lbl_th_x=i_szerokosc-130;           i_lbl_th_y  =i_wysokosc-25;
  i_th_x    =i_szerokosc-110;           i_th_y      =i_wysokosc-25;
  i_lbl_vl_x=i_szerokosc-190;           i_lbl_vl_y  =i_wysokosc-12;
  i_vl_x    =i_szerokosc-170;           i_vl_y      =i_wysokosc-12;
  i_lbl_vh_x=i_szerokosc-130;           i_lbl_vh_y  =i_wysokosc-12;
  i_vh_x    =i_szerokosc-110;           i_vh_y      =i_wysokosc-12;
  i_lbl_tlth_x=i_szerokosc-70;          i_lbl_tlth_y=i_wysokosc-25;
  i_tlth_x  =i_szerokosc-40;            i_tlth_y    =i_wysokosc-25;
  i_lbl_vlvh_x=i_szerokosc-70;          i_lbl_vlvh_y=i_wysokosc-12;
  i_vlvh_x  =i_szerokosc-40;            i_vlvh_y    =i_wysokosc-12;
  i_opis_hor_y  =0;                 i_opis_ver_x    =5;
  i_jednostka_v_x=5,        i_jednostka_v_y=i_wysokosc-36,
  i_jednostka_T_x=5,        i_jednostka_T_y=i_wysokosc-24,
  i_jednostka_f_x=5,        i_jednostka_f_y=i_wysokosc-12;
  ac_jednostka_T[0]=' ';    ac_jednostka_T[1]='s';  ac_jednostka_T[2]='\0';
  ac_jednostka_v[0]=' ';    ac_jednostka_v[1]='V';  ac_jednostka_v[2]='\0';
  ac_jednostka_f[0]=' ';    ac_jednostka_f[1]='H';  ac_jednostka_f[2]='z';  ac_jednostka_f[3]='\0';
  PrzeliczGrafike();
};//CPrzebieg::CPrzebieg()

//CPrzebieg::~CPrzebieg()
//{//1999-01-01
//  delete [] paf_in;
//};//CPrzebieg::~CPrzebieg()

//==============================================================================
void CPrzebieg::SetRozmiar(int i_szerokosc_,int _i_wysokosc)
//==============================================================================
{//1999-11-27
  i_szerokosc_old=i_szerokosc;
  i_wysokosc_old=i_wysokosc;
  i_szerokosc=i_szerokosc_;
  i_wysokosc=_i_wysokosc;
};//CPrzebieg::NowyBuf()

//==============================================================================
void CPrzebieg::ReSetRozmiar(int i_szerokosc_,int _i_wysokosc)
//==============================================================================
{//1999-11-27
  SetRozmiar(i_szerokosc_,_i_wysokosc);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_f_podstawa(float f_podstawa_)
//==============================================================================
{
  f_podstawa=f_podstawa_;
  Set_f_delta_t(f_podstawa/i_siatka_dx);
};

//==============================================================================
void CPrzebieg::ReSet_f_podstawa(float f_podstawa_)
//==============================================================================
{
  Set_f_podstawa(f_podstawa_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_f_delta_t(float f_delta_t_)
//==============================================================================
{//1999-11-27
  f_delta_t=f_delta_t_;
  f_T=f_delta_t*(i_s_szerokosc-1);
  f_f=1/f_T;
  f_tl=i_kursor_l*f_delta_t;
  f_th=i_kursor_p*f_delta_t;
  f_tlth=f_th-f_tl;
};//inline void CPrzebieg::Set_t(int _t)

//==============================================================================
void CPrzebieg::ReSet_f_delta_t(float f_delta_t_)
//==============================================================================
{//1999-11-27
  Set_f_delta_t(f_delta_t_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_f_delta_tmin(float f_delta_tmin_)
//==============================================================================
{//1999-11-27
  f_delta_tmin=f_delta_tmin_;
  //
  //
  //Set_delta_t(delta_tmin); //nowa delta_t powinna byæ najbli¿sza starej
  //
  //
};//CPrzebieg::Set_delta_tmin()

//==============================================================================
void CPrzebieg::ReSet_f_delta_tmin(float f_delta_tmin_)
//==============================================================================
{//1999-11-27
  Set_f_delta_tmin(f_delta_tmin_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_f_delta_tmax(float f_delta_tmax_)
//==============================================================================
{//1999-11-27
  f_delta_tmax=f_delta_tmax_;
};//CPrzebieg::Set_delta_tmax()

//==============================================================================
void CPrzebieg::ReSet_f_delta_tmax(float f_delta_tmax_)
//==============================================================================
{//1999-11-27
  Set_f_delta_tmax(f_delta_tmax_);
  PrzeliczGrafike();
};

//==============================================================================
inline void CPrzebieg::Set_f_delta_v(float f_delta_v_)
//==============================================================================
{//1999-11-27
  int i;
  f_delta_v=f_delta_v_;
  f_vh=i_kursor_g_p*f_delta_v;
  f_vl=i_kursor_d_p*f_delta_v;
  f_vlvh=f_vh-f_vl;
  f_skala_v=1/f_delta_v;

};//inline void CPrzebieg::Set_v(int _v)

//==============================================================================
void CPrzebieg::ReSet_f_delta_v(float f_delta_v_)
//==============================================================================
{//1999-11-27
  Set_f_delta_v(f_delta_v_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_f_czulosc(float f_czulosc_)
//==============================================================================
{//2000-03-14
  f_czulosc=f_czulosc_;
  Set_f_delta_v(/*i_siatka_dy*/f_czulosc/i_siatka_dy);
};//void CPrzebieg::Set_f_czulosc()

//==============================================================================
void CPrzebieg::ReSet_f_czulosc(float f_czulosc_)
//==============================================================================
{//2000-03-14
  Set_f_czulosc(f_czulosc_);
  PrzeliczGrafike();
};//void CPrzebieg::ReSet_f_czulosc()

//==============================================================================
inline void CPrzebieg::Set_f_delta_vmin(float f_delta_vmin_)
//==============================================================================
{//1999-11-27
  f_delta_vmin=f_delta_vmin_;
  //
  //Zmieni³y siê : delta_vsr i delta_vmax
  //
};//CPrzebieg::Set_delta_vmin()

//==============================================================================
inline void CPrzebieg::ReSet_f_delta_vmin(float f_delta_vmin_)
//==============================================================================
{//1999-11-27
  Set_f_delta_vmin(f_delta_vmin_);
  PrzeliczGrafike();
};

//==============================================================================
inline void CPrzebieg::Set_f_delta_vmax(float f_delta_vmax_)
//==============================================================================
{//1999-11-27
  f_delta_vmax=f_delta_vmax_;
  //
  // Zmieni³y siê : vsr i vmin
  //
};//CPrzebieg::Set_vmax()

//==============================================================================
inline void CPrzebieg::ReSet_f_delta_vmax(float f_delta_vmax_)
//==============================================================================
{//1999-11-27
  Set_f_delta_vmax(f_delta_vmax_);
  PrzeliczGrafike();
};

//==============================================================================
inline void CPrzebieg::Set_f_T(float f_T_)
//==============================================================================
{//1999-11-27
  f_T=f_T_;
  f_delta_t=f_T/(i_s_szerokosc-1);
  f_f=1/f_T;
};//inline void CPrzebieg::Set_T(int _T)

//==============================================================================
inline void CPrzebieg::ReSet_f_T(float f_T_)
//==============================================================================
{//1999-11-27
  Set_f_T(f_T_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_f_vmax(float f_vmax_)
//==============================================================================
{//1999-11-27
  f_vmax=f_vmax_;
  //v=vmax/s_wysokosc;
};//void CPrzebieg::Set_V(float _V)

//==============================================================================
void CPrzebieg::ReSet_f_vmax(float f_vmax_)
//==============================================================================
{//1999-11-27
  Set_f_vmax(f_vmax_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_f_vmin(float f_vmin_)
//==============================================================================
{//1999-11-27
  f_vmin=f_vmin_;
};//void CPrzebieg::Set_vmin(float _vmin)

//==============================================================================
inline void CPrzebieg::ReSet_f_vmin(float f_vmin_)
//==============================================================================
{//1999-11-27
  Set_f_vmin(f_vmin_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_i_kursor_l(int i_kursor_l_)
//==============================================================================
{//1999-12-02
  if(i_kursor_l_>=i_kursor_p)
    i_kursor_l_=i_kursor_p-1;
  if(i_kursor_l_<=0)
    i_kursor_l_=0;
  i_kursor_l=i_kursor_l_;
  f_tl=i_kursor_l*f_delta_t;
  f_tlth=f_th-f_tl;
};

//==============================================================================
void CPrzebieg::Inc_i_kursor_l()
//==============================================================================
{//1999-12-02
  Set_i_kursor_l(i_kursor_l+1);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Dec_i_kursor_l()
//==============================================================================
{//1999-12-02
  Set_i_kursor_l(i_kursor_l-1);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::ReSet_i_kursor_l(int i_kursor_l_)
//==============================================================================
{//1999-12-01
  Set_i_kursor_l(i_kursor_l_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_i_kursor_p(int i_kursor_p_)
//==============================================================================
{//1999-12-01
  if(i_kursor_p_<=i_kursor_l)
    i_kursor_p_=i_kursor_l+1;
  if(i_kursor_p_>=i_s_szerokosc-1)
    i_kursor_p_=i_s_szerokosc-1;
  i_kursor_p=i_kursor_p_;
  f_th=i_kursor_p*f_delta_t;
  f_tlth=f_th-f_tl;
};

//==============================================================================
void CPrzebieg::Inc_i_kursor_p()
//==============================================================================
{//1999-12-02
  Set_i_kursor_p(i_kursor_p+1);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Dec_i_kursor_p()
//==============================================================================
{//1999-12-02
  Set_i_kursor_p(i_kursor_p-1);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::ReSet_i_kursor_p(int i_kursor_p_)
//==============================================================================
{//1999-12-01
  Set_i_kursor_p(i_kursor_p_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_i_kursor_g(int _i_kursor_g_p)
//==============================================================================
{//1999-12-03
  if(_i_kursor_g_p<=i_kursor_d_p)
    _i_kursor_g_p=i_kursor_d_p+1;
  if(_i_kursor_g_p>=i_s_wysokosc)
    _i_kursor_g_p=i_s_wysokosc-1;
  i_kursor_g_p=_i_kursor_g_p;
  i_kursor_g=i_s_wysokosc-1-i_kursor_g_p;
  f_vh=i_kursor_g_p*f_delta_v;
  f_vlvh=f_vh-f_vl;
};

//==============================================================================
void CPrzebieg::Inc_i_kursor_g()
//==============================================================================
{//1999-12-02
  Set_i_kursor_g(i_kursor_g_p+1);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Dec_i_kursor_g()
//==============================================================================
{//1999-12-02
  Set_i_kursor_g(i_kursor_g_p-1);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::ReSet_i_kursor_g(int i_kursor_g_)
//==============================================================================
{//1999-12-01
  Set_i_kursor_g(i_kursor_g_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_i_kursor_d(int i_kursor_d_p_)
//==============================================================================
{//1999-12-03
  if(i_kursor_d_p_>=i_kursor_g_p)
    i_kursor_d_p_=i_kursor_g_p-1;
  if(i_kursor_d_p_<0)
    i_kursor_d_p_=0;
  i_kursor_d_p=i_kursor_d_p_;
  i_kursor_d=i_s_wysokosc-1-i_kursor_d_p;
  f_vl=i_kursor_d_p*f_delta_v;
  f_vlvh=f_vh-f_vl;
};

//==============================================================================
void CPrzebieg::Inc_i_kursor_d()
//==============================================================================
{//1999-12-02
  Set_i_kursor_d(i_kursor_d_p+1);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Dec_i_kursor_d()
//==============================================================================
{//1999-12-02
  Set_i_kursor_d(i_kursor_d_p-1);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::ReSet_i_kursor_d(int i_kursor_d_)
//==============================================================================
{//1999-12-01
  Set_i_kursor_d(i_kursor_d_);
  PrzeliczGrafike();
};

//==============================================================================
inline void CPrzebieg::Set_f_f(float f_f_)
//==============================================================================
{//1999-11-27
  f_f=f_f_;
  f_T=1/f_f;
  f_delta_t=f_T/i_s_szerokosc;
};//inline void CPrzebieg::Set_f(int _f)

//==============================================================================
inline void CPrzebieg::ReSet_f_f(float f_f_)
//==============================================================================
{//1999-11-27
  Set_f_f(f_f_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_f_th(float f_th_)
//==============================================================================
{//1999-11-27
  if(f_th_<=f_tl)
    f_th=f_tl+f_delta_t;
  else
    f_th=f_th_;
  i_kursor_p=f_th/f_delta_t;
};//inline void CPrzebieg::Set_th(int _th)

//==============================================================================
void CPrzebieg::ReSet_f_th(float f_th_)
//==============================================================================
{//1999-11-27
  Set_f_th(f_th_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_f_tl(float f_tl_)
//==============================================================================
{//1999-11-27
  if(f_tl_>=f_th)
    f_tl=f_tl_-f_delta_t;
  else
    f_tl=f_tl_;
  i_kursor_l=f_tl/f_delta_t;
};//inline void CPrzebieg::Set_tl(int _tl)

//==============================================================================
void CPrzebieg::ReSet_f_tl(float f_tl_)
//==============================================================================
{//1999-11-27
  Set_f_tl(f_tl_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_f_vh(float f_vh_)
//==============================================================================
{//1999-11-27
  if(f_vh_<=f_vl)
    f_vh=f_vh_+f_delta_v;
  else
    f_vh=f_vh_;
  i_kursor_g=(i_s_wysokosc-1)-f_vh/f_delta_v;
};//inline void CPrzebieg::Set_vh(int _vh)

//==============================================================================
void CPrzebieg::ReSet_f_vh(float f_vh_)
//==============================================================================
{//1999-11-27
  Set_f_vh(f_vh_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_f_vl(float f_vl_)
//==============================================================================
{//1999-11-27
  if(f_vl_>=f_vh)
    f_vl=f_vl_-f_delta_v;
  else
    f_vl=f_vl_;
  i_kursor_d=(i_s_wysokosc-1)-f_vl/f_delta_v;
};//inline void CPrzebieg::Set_vl(int _Vl)

//==============================================================================
void CPrzebieg::ReSet_f_vl(float f_vl_)
//==============================================================================
{//1999-11-27
  Set_f_vl(f_vl_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_i_os_x(int i_os_x_p_)
//==============================================================================
{//1999-11-27
  if(i_os_x_p_<0)
    i_os_x_p_=0;
  i_os_x_p=i_os_x_p_;
  i_os_x=i_s_wysokosc-1-i_os_x_p;
};//inline void CPrzebieg::Set_os_x(int _os_x)

//==============================================================================
void CPrzebieg::ReSet_i_os_x(int i_os_x_)
//==============================================================================
{//1999-11-27
  Set_i_os_y(i_os_x_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_i_os_y(int i_os_y_)
//==============================================================================
{//1999-11-27
  if(i_os_y_>=i_s_szerokosc)
    i_os_y_=i_s_szerokosc-1;
  i_os_y=i_os_y_;
};//inline void CPrzebieg::Set_os_y(int _os_y)

//==============================================================================
void CPrzebieg::ReSet_i_os_y(int i_os_y_)
//==============================================================================
{//1999-11-27
  Set_i_os_y(i_os_y_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_i_siatka_dx(int i_siatka_dx_)
//==============================================================================
{//1999-11-27
  i_siatka_dx=i_siatka_dx_;
  i_siatka_x=i_os_y%i_siatka_dx;
};//inline void CPrzebieg::Set_siatka_dx(int _siatka_dx)

//==============================================================================
void CPrzebieg::ReSet_i_siatka_dx(int i_siatka_dx_)
//==============================================================================
{//1999-11-27
  Set_i_siatka_dx(i_siatka_dx_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::Set_i_siatka_dy(int i_siatka_dy_)
//==============================================================================
{//1999-11-27
  i_siatka_dy=i_siatka_dy_;
  i_siatka_y=i_os_x%i_siatka_dy;
};//void CPrzebieg::Set_siatka_dy(int _siatka_dy)

//==============================================================================
void CPrzebieg::ReSet_i_siatka_dy(int i_siatka_dy_)
//==============================================================================
{//1999-11-27
  Set_i_siatka_dy(i_siatka_dy_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::SetPolozenie(int i_s_zaczep_x_,int i_s_zaczep_y_,int i_s_szerokosc_,int i_s_wysokosc_)
//==============================================================================
{//1999-11-27
  i_s_zaczep_x=i_s_zaczep_x_;
  i_s_zaczep_y=i_s_zaczep_y_;
  i_s_szerokosc=i_s_szerokosc_;
  i_s_wysokosc=i_s_wysokosc_;
  i_s_koniec_x=i_s_zaczep_x+i_s_szerokosc;
  i_s_koniec_y=i_s_zaczep_y+i_s_wysokosc;
};//void CPrzebieg::Set_SXSY()

//==============================================================================
void CPrzebieg::ReSetPolozenie(int i_s_zaczep_x_,int i_s_zaczep_y_,int i_s_szerokosc_,int i_s_wysokosc_)
//==============================================================================
{//1999-11-27
  SetPolozenie(i_s_zaczep_x_,-i_s_zaczep_y,i_s_szerokosc_,i_s_wysokosc_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::SetZaczep(int i_s_zaczep_x_,int i_s_zaczep_y_)
//==============================================================================
{//1990-11-27
  i_s_zaczep_x=i_s_zaczep_x_;
  i_s_zaczep_y=i_s_zaczep_y_;
  i_s_koniec_x=i_s_zaczep_x+i_s_szerokosc;
  i_s_koniec_y=i_s_zaczep_y+i_s_wysokosc;
};//inline void CPrzebieg::SetZaczep()

//==============================================================================
void CPrzebieg::ReSetZaczep(int i_s_zaczep_x_,int i_s_zaczep_y_)
//==============================================================================
{//1999-11-27
  SetZaczep(i_s_zaczep_x_,i_s_zaczep_y_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::SetSRozmiar(int i_s_szerokosc_,int i_s_wysokosc_)
//==============================================================================
{//1999-11-27
  i_s_szerokosc=i_s_szerokosc_;
  i_s_wysokosc=i_s_wysokosc_;
  i_s_koniec_x=i_s_zaczep_x+i_s_szerokosc;
  i_s_koniec_y=i_s_zaczep_y+i_s_wysokosc;
};//inline void CPrzebieg::SetSRozmiar(int _s_szerokosc,int _s_wysokosc)

//==============================================================================
void CPrzebieg::ReSetSRozmiar(int i_s_szerokosc_,int i_s_wysokosc_)
//==============================================================================
{//1999-11-27
  SetSRozmiar(i_s_szerokosc_,i_s_wysokosc_);
  PrzeliczGrafike();
};

//==============================================================================
void CPrzebieg::PrzeliczSygnal()
//==============================================================================
{
  LiczbaNaNapis(f_T,ac_T,DLUGOSC_OPISU,false);        LiczbaNaNapis(f_f,ac_f,DLUGOSC_OPISU,false);
  LiczbaNaNapis(f_delta_t,ac_dt,DLUGOSC_OPISU,false);     LiczbaNaNapis(f_delta_v,ac_dv,DLUGOSC_OPISU,false);
  //LiczbaNaZakres(T,ac_T,DLUGOSC_OPISU,false);     LiczbaNaZakres(f,ac_f,DLUGOSC_OPISU,false);
  //LiczbaNaZakres(delta_t,ac_dt,DLUGOSC_OPISU,false);  LiczbaNaZakres(delta_v,ac_dv,DLUGOSC_OPISU,false);
};//CPrzebieg::PrzeliczSygnal

//==============================================================================
void CPrzebieg::PrzeliczGrafike()
//==============================================================================
{//1999-01-01
  PrzeliczOXY();
  PrzeliczSygnal();
  PrzeliczSiatke();
  PrzeliczKursory();
  PrzeliczPolozenie();
  PrzeliczOkno();
  OdswierzGrafike();
};//CPrzebieg::PrzeliczGrafike

//==============================================================================
inline void CPrzebieg::PrzeliczSiatke()
//==============================================================================
{//2000-03-10
  //siatka zale¿y od po³o¿enia uk³adu wspó³rzêdnych i zmiennych siatka_dx i siatka_dy.
  char pc_tmp_opis[128];
  int i_tmp_opis_index,i_opis_index;
  char c;

  i_siatka_dx=i_s_szerokosc/i_przedz_hor_count;
  i_siatka_dy=i_s_wysokosc/i_przedz_ver_count;
  i_siatka_x=i_os_y%i_siatka_dx;
  i_siatka_y=i_os_x%i_siatka_dy;
  i_tmp_opis_index=0;
  ac_jednostka_T[0]=ZakresLiczy(f_delta_t*i_s_szerokosc);
  for(i_index_hor=0;i_index_hor<i_siatka_hor_count;i_index_hor++){
    i_opis_hor_x[i_index_hor]=i_siatka_dx*i_index_hor+i_siatka_x;
    f_wartosc_hor[i_index_hor]=(i_opis_hor_x[i_index_hor]-i_os_y)*f_delta_t;
    if(f_wartosc_hor[i_index_hor]==0)
      i_index_os_y=i_index_hor;
    LiczbaNaZakres(f_wartosc_hor[i_index_hor],
                   ac_opis_hor[i_index_hor],
                   DLUGOSC_OPISU_SIATKI-2,
                   ac_jednostka_T[0],
                   false);
  }
  ac_jednostka_v[0]=ZakresLiczy(f_delta_v*i_s_wysokosc);
  for(i_index_ver=0;i_index_ver<i_siatka_ver_count;i_index_ver++){
    i_opis_ver_y[i_index_ver]=i_siatka_dy*i_index_ver+i_siatka_y+i_s_zaczep_y;
    f_wartosc_ver[i_index_ver]=(i_s_wysokosc-1-(i_opis_ver_y[i_index_ver]-i_s_zaczep_y)-i_os_x_p)*f_delta_v;
    LiczbaNaZakres(f_wartosc_ver[i_index_ver],
                   ac_opis_ver[i_index_ver],
                   DLUGOSC_OPISU_SIATKI,
                   ac_jednostka_v[0],
                   true);
  }
};//CPrzebieg::PrzeliczSiatke()

//==============================================================================
inline void CPrzebieg::PrzeliczKursory()
//==============================================================================
{//2000-02-24
  f_tl=(i_kursor_l-i_os_y)*f_delta_t;
  f_th=(i_kursor_p-i_os_y)*f_delta_t;
  f_tlth=f_th-f_tl;
  f_vh=(i_kursor_g_p-i_os_x_p)*f_delta_v;
  f_vl=(i_kursor_d_p-i_os_x_p)*f_delta_v;
  f_vlvh=f_vh-f_vl;

  LiczbaNaZakres(f_T,ac_T,DLUGOSC_OPISU,ac_jednostka_T[0],false);
  ac_jednostka_f[0]=LiczbaNaNapis(f_f,ac_f,DLUGOSC_OPISU,false);
  LiczbaNaZakres(f_th,ac_th,DLUGOSC_OPISU,ac_jednostka_T[0],false);
  LiczbaNaZakres(f_tl,ac_tl,DLUGOSC_OPISU,ac_jednostka_T[0],false);
  LiczbaNaZakres(f_vh,ac_vh,DLUGOSC_OPISU,ac_jednostka_v[0],true);
  LiczbaNaZakres(f_vl,ac_vl,DLUGOSC_OPISU,ac_jednostka_v[0],true);
  LiczbaNaZakres(f_tlth,ac_tlth,DLUGOSC_OPISU,ac_jednostka_T[0],false);
  LiczbaNaZakres(f_vlvh,ac_vlvh,DLUGOSC_OPISU,ac_jednostka_v[0],true);
};//CPrzebieg::PrzeliczKursory()

//==============================================================================
inline void CPrzebieg::PrzeliczPolozenie()
//==============================================================================
{//1999-01-01
};//CPrzebieg::PrzeliczPolozenie()

//==============================================================================
inline void CPrzebieg::PrzeliczOXY()
//==============================================================================
{//1999-01-01
};//CPrzebieg::PrzeliczOXY

//==============================================================================
void CPrzebieg::PrzeliczOkno()
//==============================================================================
{//1999-01-01
};//CPrzebieg::PrzeliczOkno

//==============================================================================
void CPrzebieg::Przelicz_f()
//==============================================================================
{//1999-10-27
};//void CPrzebieg::Przelicz_f()

//==============================================================================
void CPrzebieg::Przelicz_vsr()
//==============================================================================
{//1999-10-26
};//void CPrzebieg::Przelicz_vsr()

//==============================================================================
void CPrzebieg::Przelicz_vsk()
//==============================================================================
{//1999-10-26
};//void CPrzebieg::Przelicz_vsk()

//==============================================================================
void CPrzebieg::Kursory()
//==============================================================================
{//1999-10-19
  if(b_kursor==0)
    b_kursor=1;
  else
    b_kursor=0;
  OdswierzGrafike();
};//CPrzebieg::Kursor()

//==============================================================================
void CPrzebieg::Osie()
//==============================================================================
{//1999-10-19
  if(b_osie==0)
    b_osie=1;
  else
    b_osie=0;
  OdswierzGrafike();
};//CPrzebieg::Osie()

//==============================================================================
void CPrzebieg::Siatka()
//==============================================================================
{//1999-10-19
  if(b_siatka==0)
    b_siatka=1;
  else
    b_siatka=0;
  OdswierzGrafike();
};//CPrzebieg::Siatka()

//==============================================================================
void CPrzebieg::Opis()
//==============================================================================
{//1999-10-19
  if(b_opis==0)
    b_opis=1;
  else
    b_opis=0;
  OdswierzGrafike();
};//CPrzebieg::Opis()

//==============================================================================
void CPrzebieg::Ciagly()
//==============================================================================
{//1999-11-01
  if(b_ciagly==0)
    b_ciagly=1;
  else
    b_ciagly=0;
  OdswierzGrafike();
};//void CPrzebieg::Ciagly()

//==============================================================================
void CPrzebieg::MouseDown(int i_down_x_,int i_down_y_)
//==============================================================================
{//1999-12-09
  b_mouse_down=true;
  /*
   * Je¿eli mysz naciœniêto w pobli¿u +-MARGINES_UCHWYTU pixele od elementu to jest on przesówany
   * W przypadku naciœnieæia myszy w pobli¿u kursora i osi przesówany bêdzie tylko kursor
   * Jeœli mysz zostanie naciœniêta w pobli¿u dwóch kursorów przecinaj¹cych siê to s¹ przesówane obydwa.
   * Je¿eli naciœniêto mysz w pobli¿u dwóch kursorów równoleg³ych tak ¿e obydwa mog¹ byæ przesówane
   * to przesuniêty zostanie ten w kierunku którego odbywa siê ruch.
   */
  if((i_down_x_>=i_s_zaczep_x&&i_down_x_<=i_s_koniec_x)&&(i_down_y_>=i_s_zaczep_y&&i_down_y_<=i_s_koniec_y))
    MouseDownEkran(i_down_x_-i_s_zaczep_x,i_down_y_-i_s_zaczep_y);
};

//==============================================================================
void CPrzebieg::MouseMove(int i_dx_,int i_dy_)
//==============================================================================
{//1999-12-09
  if((i_dx_>=i_s_zaczep_x&&i_dx_<=i_s_koniec_x)&&(i_dy_>=i_s_zaczep_y&&i_dy_<=i_s_koniec_y))
    MouseMoveEkran(i_dx_-i_s_zaczep_x,i_dy_-i_s_zaczep_y);
};

//==============================================================================
void CPrzebieg::MouseUp()
//==============================================================================
{//1999-12-09
  b_mouse_down=false;
  b_kursor_l_move=b_kursor_p_move=b_kursor_g_move=b_kursor_d_move=
  b_os_x_move=b_os_y_move=b_przebieg_move=false;
};

//==============================================================================
void CPrzebieg::MouseDownEkran(int i_down_x_,int i_down_y_)
//==============================================================================
{//1999-12-09
  //czy mysz uchwyci³a kursor_l
  if((i_kursor_l-MARGINES_UCHWYTU<=i_down_x_)&&(i_kursor_l+MARGINES_UCHWYTU>=i_down_x_))
    b_kursor_l_move=b_kursor&&true;
  //czy mysz uchwyci³a kursor_p
  if((i_kursor_p-MARGINES_UCHWYTU<=i_down_x_)&&(i_kursor_p+MARGINES_UCHWYTU>=i_down_x_)){
    b_kursor_p_move=b_kursor&&true;
    //korekcja przeciw uchwyceniu dwóch pionowych kursorów
    if(b_kursor_p_move==b_kursor_l_move){
      if(i_kursor_l+i_down_x_==i_kursor_p-i_down_x_){
        b_unknown_move=true;
      };
      if(i_down_x_-i_kursor_l<i_kursor_p-i_down_x_)
        b_kursor_p_move=b_kursor&&false;
      else
        b_kursor_l_move=b_kursor&&false;
    };
  };
  //czy mysz uchwyci³a kursor_g
  if((i_kursor_g-MARGINES_UCHWYTU<=i_down_y_)&&(i_kursor_g+MARGINES_UCHWYTU>=i_down_y_))
    b_kursor_g_move=b_kursor&&true;
  //czy mysz uchwyci³a kursor_d
  if((i_kursor_d-MARGINES_UCHWYTU<=i_down_y_)&&(i_kursor_d+MARGINES_UCHWYTU>=i_down_y_)){
    b_kursor_d_move=b_kursor&&true;
    //korekcja przeciw uchwyceniu dwóch poziomych kursorów
    if(b_kursor_d_move==b_kursor_g_move){
      if(i_kursor_g+i_down_y_==i_kursor_d-i_down_y_){
        b_unknown_move=true;
      };
      if(i_down_y_-i_kursor_g<i_kursor_d-i_down_y_)
        b_kursor_d_move=b_kursor&&false;
      else
        b_kursor_g_move=b_kursor&&false;
    };
  };

  if(!b_kursor_l_move&&!b_kursor_p_move&&!b_kursor_g_move&&!b_kursor_d_move){
  //czy mysz uchwyci³a os_x - podobne czynnoœci jak na kursorze: kursor_g i kursor_d
    if((i_os_x-MARGINES_UCHWYTU<=i_down_y_)&&(i_os_x+MARGINES_UCHWYTU>=i_down_y_))
      b_os_x_move=b_osie&&true;
  //czy mysz uchwyci³a os_y - podobne czynnoœci jak na kursorze: kursor_l i kursor_p
    if((i_os_y-MARGINES_UCHWYTU<=i_down_x_)&&(i_os_y+MARGINES_UCHWYTU>=i_down_x_))
      b_os_y_move=b_osie&&true;
  //czy mysz uchwyci³a sygna³
  }

  //wykonanie pierwszych czynnoœci po uchwyceniu kursorów
  if(b_unknown_move){
  }else{
    if(b_kursor_l_move){
      Set_i_kursor_l(i_down_x_);
    }
    if(b_kursor_p_move){
      Set_i_kursor_p(i_down_x_);
    }
    if(b_kursor_g_move){
      Set_i_kursor_g(i_s_wysokosc-1-i_down_y_);
    }
    if(b_kursor_d_move){
      Set_i_kursor_d(i_s_wysokosc-1-i_down_y_);
    }
    if(b_os_x_move){
      Set_i_os_x(i_s_wysokosc-1-i_down_y_);
    }
    if(b_os_y_move){
      Set_i_os_y(i_down_x_);
    }
    PrzeliczGrafike();
  }
};

//==============================================================================
void CPrzebieg::MouseMoveEkran(int i_dx_,int i_dy_)
//==============================================================================
{//1999-12-09
  if(b_mouse_down){
    if(b_unknown_move){
    }else{
      if(b_kursor_l_move){
        Set_i_kursor_l(i_dx_);
      }
      if(b_kursor_p_move){
        Set_i_kursor_p(i_dx_);
      }
      if(b_kursor_g_move){
        Set_i_kursor_g(i_s_wysokosc-1-i_dy_);
      }
      if(b_kursor_d_move){
        Set_i_kursor_d(i_s_wysokosc-1-i_dy_);
      }
      if(b_os_x_move){
        Set_i_os_x(i_s_wysokosc-1-i_dy_);
      }
      if(b_os_y_move){
        Set_i_os_y(i_dx_);
      }
      PrzeliczGrafike();
    };
  };
};

//==============================================================================
void CPrzebieg::RysujEkran()
//==============================================================================
{//1999-01-01
};//CPrzebieg::Ryduj()

//==============================================================================
void CPrzebieg::Czyszczenie()
//==============================================================================
{//2000-02-24
};//void CPrzebieg::Czyszczenie()

//==============================================================================
void CPrzebieg::OdswierzGrafike()
//==============================================================================
{//2000-02-24
  Czyszczenie();
  RysujPrzebieg();
  if(b_siatka)        RysujSiatke();
  if(b_osie)          RysujOsie();
  if(b_kursor)        RysujKursory();
  if(b_opis)          RysujOpis();
  //RysujPrzebieg();
  RysujEkran();
};//void CPrzebieg::OdswierzGrafike()

//==============================================================================
inline void CPrzebieg::RysujPrzebieg()
//==============================================================================
{//1999-01-01
};

//==============================================================================
inline void CPrzebieg::RysujSiatke()
//==============================================================================
{//1999-01-01
};

//==============================================================================
inline void CPrzebieg::RysujKursory()
//==============================================================================
{//1999-01-01
};

//==============================================================================
inline void CPrzebieg::RysujOpis()
//==============================================================================
{//1999-01-01
};

//==============================================================================
inline void CPrzebieg::RysujOsie()
//==============================================================================
{//1999-01-01
};
//---------------------------------------------------------------------------
