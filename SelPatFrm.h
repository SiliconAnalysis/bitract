//---------------------------------------------------------------------------

#ifndef SelPatFrmH
#define SelPatFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TSelPatForm : public TForm
{
__published:	// IDE-managed Components
    TBitBtn *OKBitBtn;
    TBitBtn *CancelBitBtn;
    TEdit *PatEdit;
    TLabel *Label1;
private:	// User declarations
public:		// User declarations
    __fastcall TSelPatForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelPatForm *SelPatForm;
//---------------------------------------------------------------------------
#endif
