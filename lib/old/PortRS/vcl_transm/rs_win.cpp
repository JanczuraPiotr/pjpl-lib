//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <string>
#include "rs_win.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  sz=1000;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TMR_OdczytTimer(TObject *Sender)
{
  res=com.read((par_t*)buf,sz);
  if(res)
    MEM_Odbior->Lines->Add("buf po com.read(...) = "+AnsiString(buf));
  while(res--){
    if((str[str_ix++]=buf[buf_ix++])=='\n'){
      MEM_Odbior->Lines->Add("skompletowano napis : str = "+AnsiString(str));
      memset(str,'\0',str_ix);
      str_ix=0;
      MEM_Odbior->Lines->Add("pobiera kolejny ciag");
    }
  }
  memset(buf,'\0',buf_ix);
  buf_ix=0;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  com.close();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::MEM_WysylkaKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  string str;
  switch(Key){
    case VK_RETURN:
    str=MEM_Wysylka->Lines->Strings[MEM_Wysylka->Lines->Count-1].c_str();
    str+='\n';
    memcpy(buf,str.c_str(),str.length());
    res=com.write((par_t*)buf,str.length());
    com.ioctl(WYSLIJ_ZNAK,'#');
    memset(buf,'\0',sz);
    break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BTN_OtworzClick(TObject *Sender)
{
  com.close();
  int port;
  AnsiString as=CBX_Wybor->Text;
  if(as=="COM1")
    port=1;
  else if(as=="COM2")
    port=2;
  else if(as=="COM3")
    port=3;
  else if(as=="COM4")
    port=4;
  if(ERR_NODEV==com.open(port))
    Application->MessageBox("Nie otwarto portu","B³¹d",0);
  res=0;
  buf_ix=0;
  memset(buf,'\0',sz);
  str_ix=0;
  memset(str,'\0',sz);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::BTN_ZamknijClick(TObject *Sender)
{
  com.close();
}

//---------------------------------------------------------------------------
