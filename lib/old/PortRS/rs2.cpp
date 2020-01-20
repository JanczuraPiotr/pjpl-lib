#include <iostream.h>
#include <cstring.h>
#include <conio.h>
#include "..\include\rs232.h"
#include "..\include\typy.h"

typedef char teraz;
CRS232 com;
main()
{
  size_t p;
  cout<<"numer portu (1,2,3,4) : ?"<<endl;
  cin>>p;
  switch(p){
    case 1:      p=COM1;    break;
    case 2:      p=COM2;    break;
    case 3:      p=COM3;    break;
    case 4:      p=COM4;    break;
    default :
      cout<<" z³y numer portu"<<endl;
      return 0;
  }
  if(ERR_NODEV==com.open(p)){
    cout<<"error CRS232::open()"<<endl;
    return 0;
  }
  size_t sz=1000;
  size_t res=0;
  teraz buf[1000];
  size_t buf_ix=0;
  memset(buf,'\0',sz);
  char str[1000];
  size_t str_ix=0;
  size_t wskop;
  size_t wskwy;
  memset(str,'\0',sz);
  do{
    res=com.read((par_t*)buf,sz);
    if(res)
      cout<<"buf po com.read(...) = "<<buf<<endl;
    while(res--){
      com.ioctl(DAJ_WSKAZNIK_WYPELNIENIA,(par_t)&wskwy);
      cout<<"wskaznik wypelnienia : "<<wskwy<<endl;
//      com.ioctl(DAJ_WSKAZNIK_WYPELNIENIA,(par_t)&wskop);
//      cout<<"wskaznik oproznienia : "<<wskop<<endl;

      if((str[str_ix++]=buf[buf_ix++])=='\n'){
        cout<<"skompletowano napis : str = "<<str;
        memset(str,'\0',str_ix);
        str_ix=0;
        cout<<"pobiera kolejny ciag"<<endl;
      }
    }
    memset(buf,'\0',buf_ix);
    buf_ix=0;
  }while(!kbhit());
  if(com.close()!=OK)
    cout<<"blad podczas zamkniecia portu"<<endl;
}
