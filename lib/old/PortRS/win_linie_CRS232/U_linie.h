//---------------------------------------------------------------------------

#ifndef U_linieH
#define U_linieH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "trayicon.h"

#include "typy.h"
#include "rs232.h"
//---------------------------------------------------------------------------
class TF_Linie : public TForm
{
__published:	// IDE-managed Components
        TCheckBox *CKB_PrzelaczajDTR;
          // gdy zaznaczony linia DTR prze³¹czana jest automatycznie
        TCheckBox *CKB_PrzelaczajRTS;
          // gdy zaznaczony linia RTS prze³¹czana jest automatycznie
        TCheckBox *CKB_DTR;
          // pozwala sterowaæ rêcznie lini¹ DTR gdy CKB_PrzelaczajDTR odznaczony
        TCheckBox *CKB_RTS;
          // pozwala seteowaæ rêcznie lini¹ RTS gdy CKB_PrzelaczajRTS odznaczony
        TRadioButton *RB_StanDSR;
        TRadioButton *RB_StanCTS;
        TRadioButton *RB_StanRI;
        TRadioButton *RB_StanDCD;
          // wszystkie RB_... pokazuj¹ stan odpowiedniej linii
        TTimer *TMR_PrzelaczajRTS;
          // gdy CKB_PrzelaczajRTS zaznaczony ten zegar prze³¹cza liniê RTS
        TTimer *TMR_PrzelaczajDTR;
          // gdy CKB_PrzelaczajDTR zaznaczony ten zegar prze³¹cza liniê DTR
        TTimer *TMR_SprawdzajLinie;
          // sprawdza stan linii wejœciowych
        TEdit *EDT_Port;
          // nazwa portu
        TButton *BTN_OtworzPort;
        TButton *BTN_ZamknijPort;
        void __fastcall CKB_PrzelaczajDTRClick(TObject *Sender);
        void __fastcall CKB_PrzelaczajRTSClick(TObject *Sender);
        void __fastcall CKB_DTRClick(TObject *Sender);
        void __fastcall BTN_OtworzPortClick(TObject *Sender);
        void __fastcall CKB_RTSClick(TObject *Sender);
        void __fastcall TMR_PrzelaczajDTRTimer(TObject *Sender);
        void __fastcall TMR_SprawdzajLinieTimer(TObject *Sender);
        void __fastcall TMR_PrzelaczajRTSTimer(TObject *Sender);
        void __fastcall BTN_ZamknijPortClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
  HANDLE hPort;
  ubyte_t stan;
  CRS232 com;
public:		// User declarations
        __fastcall TF_Linie(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TF_Linie *F_Linie;
//---------------------------------------------------------------------------
#endif
