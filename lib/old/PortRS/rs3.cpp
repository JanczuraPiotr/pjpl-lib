#include <iostream.h>
#include <cstring.h>
#include <conio.h>

#include "..\include\typy.h"
#include "..\include\rs232.h"

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
      cout<<" zly numer portu"<<endl;
      return 0;
  }
  if(ERR_NODEV==com.open(p)){
    cout<<"error CRS232::open()"<<endl;
    return 0;
  }

  string s;
  ubyte_t stan;
  do{
    cout<<endl<<endl;
    delay(1000);
    com.ioctl(SWITCH_DTR4);
    com.ioctl(SWITCH_RTS7);
    com.ioctl(DAJ_DSR6, (par_t)&stan);
    cout<<"Stan DSR : "<< (bool)stan<<endl;
    com.ioctl(DAJ_CTS8, (par_t)&stan);
    cout<<"Stan CTS : "<< (bool)stan<<endl;
    com.ioctl(DAJ_RI9, (par_t)&stan);
    cout<<"Stan RI  : "<< (bool)stan<<endl;
    com.ioctl(DAJ_DCD1, (par_t)&stan);
    cout<<"Stan DCD : "<< (bool)stan<<endl;
  }while(!kbhit());
  com.close();
}
