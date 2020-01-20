#include <iostream.h>
#include <cstring.h>
#include "..\include\rs232.h"
#include "..\include\typy.h"

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
  unsigned char buf[100];
  string str;

  while(str!="exit\n"){
    cin>>str;
    str+='\n';
    if(str=="czysc\n"){
      com.ioctl(CZYSC_BUFORY);
    }else{
      memcpy(buf,str.c_str(),str.length());
      com.write((par_t*)buf,str.length());
    }
  };
  if(com.close()!=OK)
    cout<<"blad podczas zamkniecia portu"<<endl;
}
