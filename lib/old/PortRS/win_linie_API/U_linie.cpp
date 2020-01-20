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
  hPort=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TF_Linie::BTN_OtworzPortClick(TObject *Sender)
{
  hPort=CreateFile(EDT_Port->Text.c_str(),      // Nazwa otwieranego portu
                GENERIC_READ|GENERIC_WRITE,     // Port otwarty do odczytu i zapisu
                0,                              // Port bez wielodostêpu
                NULL,                           // Bez zabezpieczeñ
                OPEN_EXISTING,                  // Otwieramy istniej¹ce urz¹dzenie
                0,
                NULL);
  if(hPort == INVALID_HANDLE_VALUE){
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
  EscapeCommFunction(hPort,CLRDTR);
  EscapeCommFunction(hPort,CLRRTS);
  CloseHandle(hPort);
  hPort = NULL;
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
    EscapeCommFunction(hPort,SETDTR);
  }else{
    EscapeCommFunction(hPort,CLRDTR);
  }
}
//---------------------------------------------------------------------------
void __fastcall TF_Linie::CKB_RTSClick(TObject *Sender)
{
  if(CKB_RTS->Checked == true){
    EscapeCommFunction(hPort,SETRTS);
  }else{
    EscapeCommFunction(hPort,CLRRTS);
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
  GetCommModemStatus(hPort,&Stan);

  RB_StanCTS->Checked = Stan & MS_CTS_ON;
  RB_StanDSR->Checked = Stan & MS_DSR_ON;
  RB_StanRI->Checked = Stan & MS_RING_ON;
  RB_StanDCD->Checked = Stan & MS_RLSD_ON;
}
//---------------------------------------------------------------------------
void __fastcall TF_Linie::FormClose(TObject *Sender, TCloseAction &Action)
{
  CloseHandle(hPort);
}
//---------------------------------------------------------------------------

