//---------------------------------------------------------------------------
#ifndef rs_winH
#define rs_winH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "rs232.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TComboBox *CBX_Wybor;
        TLabel *Label1;
        TTimer *TMR_Odczyt;
        TPageControl *PageControl1;
        TTabSheet *TS_Wysylka;
        TTabSheet *TS_Odbior;
        TMemo *MEM_Wysylka;
        TMemo *MEM_Odbior;
        TButton *BTN_Otworz;
        TButton *BTN_Zamknij;
        void __fastcall TMR_OdczytTimer(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall MEM_WysylkaKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall BTN_OtworzClick(TObject *Sender);
        void __fastcall BTN_ZamknijClick(TObject *Sender);
private:	// User declarations
  CRS232 com;
  size_t sz;
  size_t res;
  char buf[1000];
  size_t buf_ix;
  char str[1000];
  size_t str_ix;

  DWORD Errors;
  COMSTAT ComStat;
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
