//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "U_linie.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TF_Linie *F_Linie;
//---------------------------------------------------------------------------
__fastcall TF_Linie::TF_Linie(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TF_Linie::BTN_OtworzPortClick(TObject *Sender)
{

  if(ERR_NODEV==com.open(COM2)){
    Application->MessageBox("Nie otwarto portu","B³¹d",MB_OK);
    return ;
  }
  CKB_DTR->Enabled = false;
  CKB_RTS->Enabled = false;
  CKB_PrzelaczajDTR->Enabled = true;
  CKB_PrzelaczajRTS->Enabled = true;
  TMR_PrzelaczajRTS->Enabled = true;
  TMR_PrzelaczajDTR->Enabled = true;
  TMR_SprawdzajLinie->Enabled = true;
  BTN_OtworzPort->Enabled = false;
  BTN_ZamknijPort->Enabled = true;
  EDT_Port->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TF_Linie::BTN_ZamknijPortClick(TObject *Sender)
{
  com.close();
  CKB_DTR->Enabled = false;
  CKB_RTS->Enabled = false;
  CKB_PrzelaczajDTR->Enabled = false;
  CKB_PrzelaczajRTS->Enabled = false;
  TMR_PrzelaczajRTS->Enabled = false;
  TMR_PrzelaczajDTR->Enabled = false;
  TMR_SprawdzajLinie->Enabled = false;
  BTN_OtworzPort->Enabled = true;
  BTN_ZamknijPort->Enabled = false;
  EDT_Port->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TF_Linie::CKB_PrzelaczajDTRClick(TObject *Sender)
{
  if(CKB_PrzelaczajDTR->Checked == true){
    CKB_DTR->Enabled = false;
    TMR_PrzelaczajDTR->Enabled = true;
  }else{
    TMR_PrzelaczajDTR->Enabled = false;
    CKB_DTR->Enabled = true;
  }

}
//---------------------------------------------------------------------------
void __fastcall TF_Linie::CKB_PrzelaczajRTSClick(TObject *Sender)
{
  if(CKB_PrzelaczajRTS->Checked == true){
    CKB_RTS->Enabled = false;
    TMR_PrzelaczajRTS->Enabled = true;
  }else{
    TMR_PrzelaczajRTS->Enabled = false;
    CKB_RTS->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TF_Linie::CKB_DTRClick(TObject *Sender)
{
  if(CKB_DTR->Checked == true){
    com.ioctl(HI_DTR4);
  }else{
    com.ioctl(LO_DTR4);
  }
}
//---------------------------------------------------------------------------
void __fastcall TF_Linie::CKB_RTSClick(TObject *Sender)
{
  if(CKB_RTS->Checked == true){
    com.ioctl(HI_RTS7);
  }else{
    com.ioctl(LO_RTS7);
  }
}
//---------------------------------------------------------------------------
void __fastcall TF_Linie::TMR_PrzelaczajDTRTimer(TObject *Sender)
{
  if(CKB_DTR->Checked == true){
    CKB_DTR->Checked = false;
  }else{
    CKB_DTR->Checked = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TF_Linie::TMR_PrzelaczajRTSTimer(TObject *Sender)
{
  if(CKB_RTS->Checked == true){
    CKB_RTS->Checked = false;
  }else{
    CKB_RTS->Checked = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TF_Linie::TMR_SprawdzajLinieTimer(TObject *Sender)
{
  com.ioctl(DAJ_LINIE_WE,(par_t)&stan);
  RB_StanCTS->Checked = stan & LINIA_CTS;
  RB_StanDSR->Checked = stan & LINIA_DSR;
  RB_StanRI->Checked = stan & LINIA_RI;
  RB_StanDCD->Checked = stan & LINIA_DCD;
}
//---------------------------------------------------------------------------
void __fastcall TF_Linie::FormClose(TObject *Sender, TCloseAction &Action)
{
  com.close();
}
//---------------------------------------------------------------------------

